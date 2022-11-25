/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FLD106.c                                                      */
/* �@�T�@�@�@�v�F�X�g�b�J�[�y�����z                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     �F��O�K       �V�K�쐬                           */
/*  1.01     2006/12/16   YOON JONG JIN    �G���[�ǉ�                         */
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
#include "bml_DBCom.h"
#include "bml_dbrc.h"

#include "sql.h"

#include "LD106.h"
#include "LD106_db.h"

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
MYAPP_STSCODE		 gintErrorCode ;
struct stcLogMember	 gstLogMem ;		//	���O�o�͏��

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�t�@�C���E�f�[�^�x�[�X�o�͊֐�

//	���L����������֐�
static	int	sFncShmCrt() ;
static	int	sFncShmGet( int *) ;
static	int	sFncShmDel() ;

static  void	endFunction();

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

	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( &pAppEnv , '\0', sizeof( pAppEnv ) ) ;

	//	�p�����[�^�t�@�C�����ޔ�
	pAppEnv.pcFielNamePRM = argv[1] ;

	//	�p�����[�^�t�@�C���I�[�v��	
	pAppEnv.bp = ZbmlPrmOpen ( pAppEnv.pcFielNamePRM ) ;		
	if ( pAppEnv.bp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pAppEnv.pcFielNamePRM ) ;
		return ( -1 ) ;
	}
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv.shm_Key = atoi ( lc_prmBuf ) ;
	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_NAME, pAppEnv.cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_USER, pAppEnv.cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_PASSWD, pAppEnv.cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
        //      �v�Z���ڎ擾�͈�
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DATE_RANGE, lc_prmBuf ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DATE_RANGE ) ;
		return ( -1 ) ;
	}
	pAppEnv.DateRange = atoi ( lc_prmBuf ) ;
        //      ���b�N�t�@�C���BLD101(�����G���[�`�F�b�N���쐬) �N���g���K�[�B�ŏ��̏������I�������쐬�B
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_LOCK_FILE, pAppEnv.cLockFile ) != 0 ) {
		//      �ُ�I��        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_LOCK_FILE ) ;
		return ( -1 ) ;
	}
	//	SLEEP�擾
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SLEEP_MIN, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
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
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
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
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B			*/
/*  �o�@�@�́@�F								*/
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/********************************************************************************/
int
mainFunction()
{
	int	li_stopFlg = 0;

	int	ret = 0;
	int	min = 0;
	int	cnt_recalc = 0;
	int	cnt_calcmst = 0;
	int	cnt_calcrec = 0;
	int	max_recalc = 0;
	int	max_calcmst = 0;
	int	max_calcrec = 0;
	char	serch_date_from[11];
	char	serch_date_to[11];

	FILE	*fp = NULL ;

	my_stSYSKNR	pSysKnr; 	//
	my_stCALC	*pCalc;		/* �v�Z����� */
	my_stCALCSYSMST	*pCalcsysmst;	/* �v�Z�}�X�^��� */

	/***
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {
		/* 1�����Ƃɒ�~�R�}���h���m�F���Ȃ���ݒ肳�ꂽ���ԃX���[�v */
		for ( min=0; min < pAppEnv.SleepMin; min++ ) {
			/* ��~�R�}���h�m�F */
			if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
				return( RET_STOP );
			}
			if ( li_stopFlg == 1 ) {
				return ( RET_OK ) ;
			}
			/* �V�X�e���Ǘ��}�X�^�擾 */
			if ( ZdbSelSysKnr( &pSysKnr ) !=  RET_OK ){
				return( RET_STOP );
			}
			/* �����d�m�c�����Ă���ꍇ�A�����J�n�`�F�b�N���s�� */
			if ( strcmp( pSysKnr.bchendflg , "1" ) == 0 ) {
				/* �����������n�܂��Ă�����I�� */
				if ( strcmp( pSysKnr.unyflg , "1" ) == 0 ) {
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "���������̊J�n���m�F���܂����B");
					return ( RET_OK ) ;
				}
			}
			sleep ( 60 ) ;
		}

		/* �V�X�e���Ǘ��}�X�^�擾 */
		if ( ZdbSelSysKnr( &pSysKnr ) !=  RET_OK ){
			return( RET_STOP );
		}
		/* �����d�m�c�����Ă��Ȃ��ꍇ�A�������J�n���Ȃ� */
		if ( strcmp( pSysKnr.bchendflg , "1" ) != 0 ) {
			continue;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "�����C���Ώہ@�Čv�Z�����J�n" ) ;

		/* ������ */
		pCalc = NULL ;
		pCalcsysmst = NULL;
		/* �����C�� �Čv�Z�Ώۏ�� �擾���� */
		ret = ZdbSelCalc( &pCalc, &max_recalc ) ;
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
			return( RET_STOP );
		}
		/* �����C���Ώہ@�Čv�Z���� */
		for ( cnt_recalc = 0; cnt_recalc < max_recalc; cnt_recalc++ ){
			/* �Čv�Z�����̎��s */
			ret = sFncCalc( &pCalc[cnt_recalc] );
			if ( ret ==  RET_OK ){
				/* �Čv�Z�ς݃t���O�̍X�V */
				ret = ZdbUpdRecalc( &pCalc[cnt_recalc] );
				if ( ret !=  RET_OK ){
					return( RET_STOP );
				}
			} 
			else if( ret !=  RET_CONTINUITY ){
				return( RET_STOP );
			}
			ZdbCommit() ;
		}
		if( pCalc != NULL){
			ZbmlFree( pCalc );
		}
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			     "�����C���Ώہ@�Čv�Z�������� [%d��]", max_recalc ) ;

		/* ���T�e���C�g���ʌv�Z�p�}�X�^��� �擾���� */
		ret = ZdbSelCalcsysmst( pSysKnr.kjnsriymd, &pCalcsysmst, &max_calcmst ) ;
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
			return( RET_STOP );
		}
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "���T�e���C�g���ځ@�v�Z�����J�n" ) ;
		/* �}�X�^�̌��������[�v */	
		for ( cnt_calcmst = 0; cnt_calcmst < max_calcmst; cnt_calcmst++ ){
			/* ������ */
			pCalc = NULL ;
			max_calcrec = 0;
			sFncGetdate( serch_date_from, pSysKnr.kjnsriymd, pAppEnv.DateRange );
			if ( strcmp ( pCalcsysmst[cnt_calcmst].hkkbn , "1") == 0 ) {
				sFncGetdate( serch_date_to, pSysKnr.kjnsriymd, -1 );
			}
			else {
				sprintf( serch_date_to, "%-10.10s", pSysKnr.kjnsriymd );
			}
			/* �}�X�^������ ���T�e���C�g���ʌv�Z�Ώۏ�� �擾���� */
			ret = ZdbSelCalcOther( serch_date_from, serch_date_to, &pCalcsysmst[cnt_calcmst], &pCalc, &max_calcrec ) ;
			if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
				return( RET_STOP );
			} else if ( ret == HRC_SQL_NOT_FOUND ){
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     	"���T�e���C�g���ځ@�v�Z�Ώۖ��� [knsgrp:%s kmkcd:%s zaicd:%s] ", pCalcsysmst[cnt_calcmst].knsgrp, pCalcsysmst[cnt_calcmst].kmkcd, pCalcsysmst[cnt_calcmst].zaicd ) ;
				continue ;
			}
			/* ���T�e���C�g���ڌv�Z�����̎��s */
			for ( cnt_calcrec = 0; cnt_calcrec < max_calcrec; cnt_calcrec++ ){
				ret = sFncCalc( &pCalc[cnt_calcrec] );
				if ( ret == RET_STOP ){
					return( RET_STOP );
				}

				ZdbCommit() ;
			}
			if( pCalc != NULL){
				ZbmlFree( pCalc );
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "���T�e���C�g���ځ@�v�Z�������� [knsgrp:%s kmkcd:%s zaicd:%s] ", pCalcsysmst[cnt_calcmst].knsgrp, pCalcsysmst[cnt_calcmst].kmkcd, pCalcsysmst[cnt_calcmst].zaicd ) ;
		}

		// LD106���b�N�t�@�C�����쐬(���������ɂĎg�p)
		if( ( fp = fopen( pAppEnv.cLockFile, "w" ) ) == NULL ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "���b�N�t�@�C���̍쐬�Ɏ��s���܂����B[%s]", pAppEnv.cLockFile ) ;
		}
		fclose( fp );
	}

	if( pCalcsysmst != NULL){
		ZbmlFree( pCalcsysmst );
	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ��  �FsFncCalc							*/
/*  �@�\�T�v  �F�����C���Čv�Z�Ώہ@�擾�֐�					*/
/*  ��    ��  �F								*/
/*   ��P���� �Fstruct my_stCALC  *pCalc    : �����`�F�b�N���			*/
/*  �o    ��  �F�Ȃ�								*/
/*  ���A���  �FINT								*/
/*		RET_OK		: ����						*/
/*		RET_STOP	: ���s						*/
/*		RET_CONTINUITY	: �X�V���ʂȂ�					*/
/******************************************************************************/
int
sFncCalc( pCalc )
my_stCALC	*pCalc;
{
	my_stKEKKA	*pCalcKka;	/* ���ʏ�� */
	my_stKJNMST	pKjnmst;

	int	ret = RET_OK ;

	char	pKsnsk[128] ;
	char	pKnsflg[1+1] ;
	int	KekkaNoneFlg = 0;	/* INSERT �� UPDATE ���𐧌䂷��t���O */
	int	KekkaOtherFlg = 0;	/* �v�Z���ڃ}�X�^���ǂ���ɑ��݂��邩���䂷��t���O */
	int	i = 0;
	int	cntKka = 0;
	int	flg = RET_CONTINUITY;	/* �v�Z���ʂ��X�V�ł����ꍇ�� RET_OK */

	/* �������� */
	pCalcKka = NULL ;

	/* ���ʏ����擾���� */
	ret = ZdbSelKekka( pCalc, &pCalcKka, &cntKka );
	if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
		return( RET_STOP );
	}
	if( cntKka == 0 ){
		KekkaNoneFlg = -1;
		/* ���ʏ�񂪂Ȃ��ꍇ�̓I�[�_�[��񂩂�K�v�ȏ����擾���� */
		ret = ZdbSelKenorderKekka( pCalc, &pCalcKka, &cntKka );
		if( ret != RET_OK || cntKka == 0 ){
			return( RET_STOP );
		}
	}

	for (i = 0; i < cntKka ; i++) {
		/* �R�����g���ʂ������Ă���ꍇ�́A�v�Z���Ȃ� */
		if ( strncmp( pCalcKka[i].knskka2kbn, "  ", 2 ) != 0 ){
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "�R�����g���ʓo�^�ς� utkymd: %s irino:%s kmkcd:%s knskka2kbn:%s]",
				     pCalcKka[i].utkymd, pCalcKka[i].irino, pCalcKka[i].kmkcd, pCalcKka[i].knskka2kbn ) ;
			continue;
		}

		/* ���������� */
		memset( pKsnsk, '\0', sizeof( pKsnsk ) );
		memset( pKnsflg, '\0', sizeof( pKnsflg ) );

		/* ��l�}�X�^�̎擾 */
	        ret = ZdbSelKjnmst(&pCalcKka[i], &pKjnmst);
		if ( ret != HRC_SQL_NORMAL ){
			return( RET_STOP );
		}

		/* �v�Z�����擾���� */
		ret = ZdbGetKsnsk( &pCalcKka[i], pKsnsk, &KekkaOtherFlg );
		if ( ret != HRC_SQL_NORMAL ){
			if ( ret == HRC_SQL_NOT_FOUND ){
				continue;	
			}
			else {
				return( RET_STOP );
			}
		}

		/* �Čv�Z���s�� */
		ret = KeisanChk( pCalc, pKsnsk, &pCalcKka[i] , pKnsflg , pKjnmst.kjsstnksu , KekkaOtherFlg );
		if( ret != RET_OK ){
			if( ret == RET_CONTINUITY ){
				continue;	
			}
			else {
				return( RET_STOP );
			}
		}

		/* ���ʃt�B���^�`�F�b�N */
		ret = filterChk( &pCalcKka[i], &pKjnmst );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* ��l�`�F�b�N */
		ret = kjnChk( &pCalcKka[i], &pKjnmst );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* �Č������W�`�F�b�N */
		ret = rngChk( pCalc, &pCalcKka[i] );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* BML�p�j�b�N�`�F�b�N */
		ret = BmlPanicChk( pCalc, &pCalcKka[i] );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* �������`�F�b�N */
		ret = KnsPanicChk( pCalc, &pCalcKka[i] );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* �v�Z���ʂ��܂��o�^����ĂȂ��ꍇ�� INSERT */
		if( KekkaNoneFlg == -1 ){
			ret = ZdbInsCalcKekka( &pCalcKka[i], pKnsflg );
			if( ret == RET_OK ){
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					     "�v�Z���ʁ@�V�K�o�^[utkymd:%s irino:%s kmkcd:%s knskka:%s]",
					     pCalcKka[i].utkymd, pCalcKka[i].irino, pCalcKka[i].kmkcd, pCalcKka[i].knskka1 ) ;
				flg = RET_OK;
			} else if( ret != RET_CONTINUITY ){
				return( RET_STOP );
			} else {
				/* �������Ɍ��ʂ������Ă��ďd���G���[�ɂȂ����ꍇ�� */ 
				/* �㑱������ UPDATE ���s���B*/
				KekkaNoneFlg = 0;
			}
		}
		/* ���Ɍv�Z���ʂ��o�^����Ă����ꍇ�� UPDATE */
		if( KekkaNoneFlg == 0 ){
			ret = ZdbUpdCalcKekka( &pCalcKka[i], pKnsflg );
			if( ret == RET_OK ){
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					     "�v�Z���ʁ@�X�V[utkymd:%s irino:%s kmkcd:%s knskka:%s]",
					     pCalcKka[i].utkymd, pCalcKka[i].irino, pCalcKka[i].kmkcd, pCalcKka[i].knskka1 ) ;
				flg = RET_OK;
			} else {
				return( RET_STOP );
			}
		}
	}
	if( pCalcKka != NULL ){
		ZbmlFree( pCalcKka );
	}
	return( flg );
}

/******************************************************************************/
/*  �� �� ���@�FendFunction()							*/
/*  �@�\�T�v�@�F�I�������֐�							*/
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 	*/
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����							*/
/* �@�@�@�@�@�@�@-1     : ���s							*/
/******************************************************************************/
void
endFunction()
{
	/*	���b�N�t�@�C���폜 */
	remove( pAppEnv.cLockFile ) ;

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
/*  �� �� ���@�FsFncGetdate()                                                   */
/*  �@�\�T�v�@�F���t���Z�֐�                                                    */
/*  ���@�@�́@�F                                                              */
/*�@ ��Q���� �Fchar *  ����t������( yyyy-mm-dd )                            */
/*�@ ��R���� �Fint     ��������(���ʂɎw�肷��Ɖ�����B�|�w��ŉ����O�ƂȂ�)  */
/*  �o�@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *  �擾���t������( yyyy-mm-dd )                            */
/******************************************************************************/
void sFncGetdate( newdate, date, days )
char *newdate ;
char *date ;
int days ;
{
	int y, m, d;

	sscanf(date, "%d-%d-%d", &y, &m, &d);
	struct tm tm = { 0, 0, 0, d, m-1, y-1900 };
	time_t time = mktime(&tm) + 86400 * days;
	struct tm *ltime = localtime(&time);

	sprintf(newdate, "%d-%02d-%02d", ltime->tm_year+1900, ltime->tm_mon+1, ltime->tm_mday);
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
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			*/
/*  �o�@�@�́@�F                                                                */
/*  ���A���@�Fint								*/
/*		 0	����							*/
/*		-1	�ُ�							*/
/********************************************************************************/
static int
sFncShmCrt()
{
	int	*shmData ;

	//	�擾
	pAppEnv.shm_Id = shmget ( (key_t)pAppEnv.shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv.shm_Id < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
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
/*�@ ��P���� �Fstruct appEnv *	�v���O�������\����	 			*/
/*�@ ��Q���� �Fint *   	�l						*/
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
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
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
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
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "daemon�N�����s" ) ;
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

