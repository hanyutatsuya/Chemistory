/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FAD105Buntekai.c								*/
/*		�T�v		�F�������W�J����								*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/01/19		E.Osada			Create					*/
/*  2.01	2006/10/24		INTEC  			����OK���I�[�_�쐬		*/
/*  2.01	2006/12/16		YOON  			SQL ERROR �C��			*/
/*  3.02    2007/04/12      INTEC           Buntekai -803�̌㑱�ǉ� */
/*  4.01                    k.moriya        �V�t�����e�B�A�Ή�      */
/*  4.02    2009/03/24      h.sekiya        �D�揇�̐ݒ�s��Ή�  */
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include "AD105Buntekai.h"

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/


/******************************************************************************/
/* Define��`                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif
#define NYO_KNSGRP "0003"
//  �t���O��`
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
BUNCHU_STSCODE	gintErrorCode ;
static	char	*gpToken ;		//sFncTrFileToken�p�ÓI�|�C���^
struct stcLogMember      gstLogMem ;
iconv_t     G_ic;
extern int g_iJdkmk;
extern Jdkmkmst *g_strJdkmk;
extern Sysknrmst *g_strSysknr;
osada(struct bunchuEnv *pEnv)
{
}
/******************************************************************************/
/*  �� �� ���@�FinitFunction()												  */
/*  �@�\�T�v�@�F���������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int
initFunction( argc, argv, pEnv )
int					 argc ;
char				*argv[] ;
struct bunchuEnv	*pEnv ;
{
	char	 cPrmBuf[256] ;
	char    *lc_login ;

	/***
	 ***	������	
	 ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;
	//	�v���O�������ϐ�������
	memset ( pEnv , '\0', sizeof ( struct bunchuEnv ) ) ;

	/***
	 ***	���O�I�[�v��
	 ***/
	if( ZbmlOpenLog( MYAPP_LOGINIFILE ) != 0 ) {
		return( -1 );
	}

    //  ���O��񏉊��ݒ�
    memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
    if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
        strcpy ( gstLogMem.pcLoginId, lc_login ) ;
    }
    strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

    //  �J�n���O�o��
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "�v���O�����N��" ) ;

	/***
	 ***	�����`�F�b�N	
	 ***/
	//	�������`�F�b�N	
	if ( argc != 2 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_USEGE ;
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�R�}���h�p�����[�^�Ɍ�肪����܂�" ) ;
		return ( -1 ) ;
	}

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C�����ޔ�
	pEnv->pcFielNamePRM = argv[1] ;

	//	�p�����[�^�t�@�C���I�[�v��
	pEnv->bp = ZbmlPrmOpen ( pEnv->pcFielNamePRM ) ;
	if ( pEnv->bp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_FILE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZZbmlPrmOpen", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	//	�������f�B���N�g��
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_BUNCHU,
						pEnv->cDirBunchu ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�������f�B���N�g��(����)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_BUNCHU_OK,
						pEnv->cDirBunchuOK ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�������f�B���N�g��(�G���[)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_BUNCHU_NG,
						pEnv->cDirBunchuNG ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	// �g���[No���t�@�C���i�[�f�B���N�g
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_TRAY,
						pEnv->cDirTryinfo ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//�g���[No���t�@�C���i�[�f�B���N�g��(����)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_TRAY_OK,
						pEnv->cDirTryinfoOK ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//�g���[No���t�@�C���i�[�f�B���N�g��(�G���[)
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_TRAY_NG,
						pEnv->cDirTryinfoNG ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	���O�f�B���N�g��
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DIR_LOG, 
						pEnv->cDirLog ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�f�o�b�O���O�t�@�C��
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_DBG, 
						pEnv->cDebugLogName ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�g���[�X���O�t�@�C��
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_TR, 
						pEnv->cTraceLogName ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�A�N�Z�X���O�t�@�C��
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_ACS, 
						pEnv->cAccessLogName ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�G���[���O�t�@�C��
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_FILE_ERR, 
						pEnv->cErrorLogName ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_SHM_KEY, cPrmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	pEnv->shm_Key = atoi ( cPrmBuf ) ;
	//	SLEEPSEC�擾
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_SLEEP_SEC, cPrmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	pEnv->sleep_Sec= atoi ( cPrmBuf ) ;
	//�X�V��ID
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_UP_ID, 
						pEnv->cUpdateId ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//�X�V�Җ�
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_UP_NM, 
						pEnv->cUpdateName ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//���s���[�h
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_PROC_MD, cPrmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	pEnv->proc_mode= atoi ( cPrmBuf ) ;
	//DB����
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_DB,
						pEnv->sDbName ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//DB���O�C��ID
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_UID,
						pEnv->sDbUser ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//DB�p�X���[�h
	if ( ZbmlPrmGetVal ( pEnv->bp, BUNCHU_PRM_PWD,
						pEnv->sDbPswd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//�ߓn�����{�R�[�h
	if( ZbmlPrmGetVal( pEnv->bp, BUNCHU_PRM_LBCD,
						pEnv->sLbcd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//�ߓn���T�e���C�g�R�[�h
	if( ZbmlPrmGetVal( pEnv->bp, BUNCHU_PRM_STCD,
						pEnv->sSateid ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}
	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pEnv->bp ) ;

	// �\�[�g�L�[���̎擾
	if( (pEnv->pSortNo = AgetSortInfo(&pEnv->pSort)) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_PRM_GET ;
		return ( -1 ) ;
	}

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( pEnv ) < 0 ) {
		return ( -1 ) ;
	}

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "initFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "End Function" ) ;
	return ( 0 ) ; 
}
/******************************************************************************/
/*  �� �� ���@�FmainFunction()												  */
/*  �@�\�T�v�@�F���C�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int
mainFunction( pEnv )
struct bunchuEnv	*pEnv ;
{

	int				  li_idx, ret;
	int				  li_stopFlg ;

	DIR				 *lt_dp ;
	struct dirent	**lpst_dirBuf ;

	int				  li_fileCnt ;
	char			  lc_fileName[1024] ;
	struct stat		  lst_statBuf ;
	char	sFileOK[1024], sFileNG[1024];
	char	sDttm[128];

	Flbun	  lst_trInfo ;

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Main Function");

    //if( ret = ZdbConnect( "labokns", "nxtgene", "nxtgene" ) ) [
    if( ret = ZdbConnect( pEnv->sDbName, pEnv->sDbUser, pEnv->sDbPswd ) ) {
        printf("DB connect error (%d)", ret);
        return( -1 );
    }

	G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	//�}�X�^���O�ǂݍ���
	int nRet = 0;
	nRet = GetMstDate();
	if(nRet == 0)
	{	//2007-04-02 YOON �G���[�����ǉ�
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Master Tables do not setup and exit program");
		exit(1);
	} 

	/***
	 ***	�������f�B���N�g���Ď�	
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	while ( 1 ) {

		/***
		 *** �t�@�C�����擾
		 ***/
		if ( ( li_fileCnt = scandir ( pEnv->cDirBunchu, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  alphasort ) ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = BUNCHU_STSCODE_ERR_DIR;
			return ( -1 ) ;
		}
		li_idx = 0 ;
		if( li_fileCnt ) {
			//�g���[�X���O
			memset(sDttm, 0, sizeof(sDttm));
			nowdateget1( sDttm );
    		sFncPutLog ( TRCKIND_OPT, "", "", 0,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�����J�n(%s) �t�@�C����(%d)", sDttm, li_fileCnt);
		}
		while ( li_idx < li_fileCnt ) {
			sprintf (lc_fileName, "%s/%s",pEnv->cDirBunchu, lpst_dirBuf[li_idx]->d_name ) ;

    		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"File GET [%s]", lpst_dirBuf[li_idx]->d_name );

			if ( stat ( lc_fileName, &lst_statBuf ) < 0 ) {
				//	�ُ�I��	LOG
				gintErrorCode = BUNCHU_STSCODE_ERR_DIR;
				return ( -1 ) ;
			}
			memset(sFileOK, 0, sizeof(sFileOK));
			memset(sFileNG, 0, sizeof(sFileNG));
			//�ʏ�t�@�C���̂ݏ������s��
			if ( S_ISREG ( lst_statBuf.st_mode ) ) 
			{
				ret = sFncTrFileRead ( pEnv, lc_fileName, &lst_trInfo );
				if ( ret < 0 ) {
					sprintf(sFileOK,"%s/%s",pEnv->cDirBunchuNG,lpst_dirBuf[li_idx]->d_name);
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__,
                	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                	"MOVE File POS [%s], DIRECTORY [%s]", sFileOK,pEnv->cDirBunchuNG);
				} else {
					sprintf(sFileOK,"%s/%s",pEnv->cDirBunchuOK,lpst_dirBuf[li_idx]->d_name);
				}
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "mainFunction", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "MOVE File RET:<%d>,POS [%s]",ret, sFileOK);

				//	���
				free ( lpst_dirBuf[li_idx] ) ;
				// �t�@�C���ړ�
				if( rename( lc_fileName, sFileOK) < 0 ) {
//					printf("rename error %s -> %s\n", lc_fileName, sFileOK);
					sFncPutLog ( TRCKIND_OPT, __FILE__, "mainFunction", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"rename error %s -> %s\n", lc_fileName, sFileOK);
					return( -1 );
				}
			}
			/***
		 	*** ��~�R�}���h�m�F
		 	***/
			if ( sFncShmGet ( pEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				break ;
			}
			li_idx ++ ;
		}

		if( li_fileCnt ) {
			//�g���[�X���O
			memset(sDttm, 0, sizeof(sDttm));
			nowdateget1( sDttm );
    		sFncPutLog ( TRCKIND_OPT, "", "", 0,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�����I��(%s)", sDttm);
		}

		/***
	 	*** ��~�R�}���h�m�F
	 	***/
		if( li_stopFlg != 1 ) {
			if ( sFncShmGet ( pEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
		}
		if ( li_stopFlg == 1 ) {
			break ;
		}

		/***
		 *** �X���[�v
		 ***/
		sleep ( pEnv->sleep_Sec ) ;
	}

	iconv_close( G_ic );

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FendFunction()												  */
/*  �@�\�T�v�@�F�I�������֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct	env *   	�v���O�������\���́B		 			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
void
endFunction( pEnv )
struct bunchuEnv	*pEnv ;
{
	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");
	/***
	 ***	���L�������폜	
	 ***/
	if ( sFncShmDel ( pEnv ) < 0 ) {
		return ;
	}
	
	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "endFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");
	return ;
}
/******************************************************************************/
/*  �� �� ���@�FdBunCrTryfile()				 								  */
/*  �@�\�T�v�@�F�g���[��t�����t�@�C���쐬								  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *					�������							  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
dBunCrTryfile(pst_Env, strKenPos, iKenPos)
struct bunchuEnv    *pst_Env;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//TRAY *strKenPos;
RACK *strKenPos;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
int	iKenPos;
{
	char	sysdate[128], systime[128];
	char	sTryFilenmTMP[128], sTryFilenmDAT[128];
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//	char	sBuf[2048], sBuf1[1024];
	char	sBuf[9];
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	int		i, j;
	FILE	*fp;

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");

	memset(sBuf, 0, sizeof(sBuf));
	for( i=0; i < iKenPos ;++i ) {
		memset(sysdate, 0, sizeof(sysdate));
		memset(systime, 0, sizeof(systime));
		memset(sTryFilenmTMP, 0, sizeof(sTryFilenmTMP));
		memset(sTryFilenmDAT, 0, sizeof(sTryFilenmDAT));
		memset(systime, 0, sizeof(systime));

		nowdateget(sysdate, systime);

// 2008-01-07 �V�t�����e�B�A�Ή� INS START
		memset(sBuf, 0, sizeof(sBuf));
		sprintf(sBuf, "%08d", atoi((strKenPos+i)->sRackID));
// 2008-01-07 �V�t�����e�B�A�Ή� INS END
		if( pst_Env->sPutDir ) {
/* BUG 2006.04.06
			sprintf(sTryFilenmTMP, "%s/%s/TR_%s%s_%s.tmp", pst_Env->cDirTryinfo, pst_Env->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
			sprintf(sTryFilenmDAT, "%s/%s/TR_%s%s_%s.dat", pst_Env->cDirTryinfo, pst_Env->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
*/
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//			sprintf(sTryFilenmTMP, "%s/%s/TR_%s%s_%s.tmp", pst_Env->cDirTryinfo
//				,(strKenPos+i)->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
//			sprintf(sTryFilenmDAT, "%s/%s/TR_%s%s_%s.dat", pst_Env->cDirTryinfo
//				,(strKenPos+i)->sPutDir, &sysdate[2], systime, (strKenPos+i)->sTryID);
			sprintf(sTryFilenmTMP, "%s/%s/RK_%s%s_%08s.tmp", pst_Env->cDirTryinfo, (strKenPos+i)->sPutDir, &sysdate[2], systime, sBuf);
			sprintf(sTryFilenmDAT, "%s/%s/RK_%s%s_%08s.dat", pst_Env->cDirTryinfo, (strKenPos+i)->sPutDir, &sysdate[2], systime, sBuf);
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
		} else {
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//			sprintf(sTryFilenmTMP, "%s/TR_%s%s_%s.tmp", pst_Env->cDirTryinfo, &sysdate[2], systime, (strKenPos+i)->sTryID);
//			sprintf(sTryFilenmDAT, "%s/TR_%s%s_%s.dat", pst_Env->cDirTryinfo, &sysdate[2], systime, (strKenPos+i)->sTryID);
			sprintf(sTryFilenmTMP, "%s/RK_%s%s_%08s.tmp", pst_Env->cDirTryinfo, &sysdate[2], systime, sBuf);
			sprintf(sTryFilenmDAT, "%s/RK_%s%s_%08s.dat", pst_Env->cDirTryinfo, &sysdate[2], systime, sBuf);
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
		}
	
		if( (fp = fopen(sTryFilenmTMP, "w")) == NULL ) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Fail Directory:%s",sTryFilenmTMP);
			//���O�o��
			return( -1 );
		}
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//		//sprintf(sBuf, "%s,%s", (strKenPos+i)->sTryID, (strKenPos+i)->sStDate);
//		fprintf(fp, "%s,%s", (strKenPos+i)->sTryID, (strKenPos+i)->sStDate);
//		for( j=1; j <= MAXPOSOLD ;++j ) {
		fprintf(fp, "%s,%s", (strKenPos+i)->sRackID, (strKenPos+i)->sStDate);
		for( j=1; j <= MAXPOS ;++j ) {
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
		//	memset(sBuf1, 0, sizeof(sBuf1));
		//	sprintf(sBuf1, ",%s,%s,%s,%s", 
			fprintf(fp, ",%s,%s,%s,%s", 
				(strKenPos+i)->strPosInfo[j].sUkeDate, (strKenPos+i)->strPosInfo[j].sKentaiID,
				(strKenPos+i)->strPosInfo[j].sIraiNo, (strKenPos+i)->strPosInfo[j].sKenSybt);
		//	strcat(sBuf, sBuf1);
		}
		fprintf(fp, ",%4.4s/%2.2s/%2.2s %2.2s:%2.2s:%2.2s\n", 
				sysdate, &sysdate[4], &sysdate[6], systime, &systime[2], &systime[4]);
		fclose(fp);

// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunCrTryfile", __LINE__,
//                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//                 "Toray Directory:%s",sTryFilenmDAT);
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Tray Directory:%s",sTryFilenmDAT);
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END

		//�t�@�C�����ύX
		if( rename( sTryFilenmTMP, sTryFilenmDAT ) < 0 ) {
// 2008-01-07 �V�t�����e�B�A�Ή� INS START
			//���O�o��
			sFncPutLog ( TRCKIND_OPT, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "Rename Error:[%s] --> [%s]", sTryFilenmTMP, sTryFilenmDAT);
// 2008-01-07 �V�t�����e�B�A�Ή� INS END
		}

// 2008-01-07 �V�t�����e�B�A�Ή� DEL (BD301�Ɉڍs) START
//		memset(sBuf1, 0, sizeof(sBuf1));
//		memset(sBuf1, ' ', 16);
//		//����WS���R�[�h�̓o�^
//		if( insWsseqknri((strKenPos+i)->sStDate, sBuf1, (strKenPos+i)->sTryID,
//				(strKenPos+i)->iKntSuu, (strKenPos+i)->iMinSeq, (strKenPos+i)->iMaxSeq ) < 0 ) {
//			return( -1 );
//		}
// 2008-01-07 �V�t�����e�B�A�Ή� DEL (BD301�Ɉڍs) END
	}

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunCrTryfile", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return( 0 );
}
/******************************************************************************/
/*  �� �� ���@�FdBunchu_ins()				 								  */
/*  �@�\�T�v�@�F�������쐬����											  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *					�������							  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
dBunchu_ins(pst_Env, lc_recBuf, strKenPos, iKenPos, sFLname, iFLcnt)
struct bunchuEnv    *pst_Env;
char	*lc_recBuf;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//TRAY **strKenPos;
RACK **strKenPos;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
int		*iKenPos;
char	*sFLname;
int		iFLcnt;
{
	FILE	*fp;
	Flbun *pBunchu;			//�������ʏ��t�@�C���\����
	Bunchu	strBunchuTB, pBunW;	//�������ʏ��e�[�u���\����
	Kanjya	strKanjyaTB;	//���ҏ��e�[�u��KEY�\����
	Kanjya	*pKanjya = NULL;		//���ҏ��e�[�u���i�[�\����
	Irai	strIraiTB;		//�˗����e�[�u��KEY�\����
	Irai	*pIrai = NULL;			//�˗����e�[�u���i�[�\����
	Irai	*pIrai2 = NULL;			//�˗����e�[�u���i�[�\���� 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� �ǉ�
	Irai	pIraiW;			//�˗����e�[�u���i�[�\����
	Irai	pIraiW1 ;			//�˗����e�[�u���i�[�\����
	Irai	pIraiW2 ;			//�˗����e�[�u���i�[�\���� 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� �ǉ�
	Kenorder pOrder;		//�����I�[�_�e�[�u���i�[�\����
	//Kenorder *pOrder = NULL;		//�����I�[�_�e�[�u���i�[�\����
	Realchk	*pReal = NULL;		//�����`�F�b�N�i�[�\����
	char	buf[1024], buf1[1024], buf2[128];		//���[�N
	BmlDate	today;
	char	sDay[20], sysdate[128], systime[128];
	char	*pKmkCd, *pKmkCd1;
	int		i, num, iIrai, j, iOrder, cnt, iHit, k,l,m;
	long	ret;
	char	sWknsgrp[17], sWknsStart[11];
	char 	tmpiraino[12] = {0,};
	TRAY *pTray;
	RACK *pRack;			// 2008-01-07 �V�t�����e�B�A�Ή� �ǉ�
	char ialloc, iPoint;
	int		iWs, iEda;
	Sysknrmst strSyskn, *pSyskn = NULL;
	int		iSkipFlg;
	int iRet;
	char	sWork[10];
	char	sWork1[10];
	int		iJidoFlg;
	int 	iOldFlg;
	char	sKjNo[10];
	int		iOya;
	int		iOdrMkFlg;
//YOON 2007-02-17
	int 	iDBBunUpflg = 1; //�����X�V�t���O(chkBunchu�֐��Ŏg���܂��B)
	char	sKeito[3];
	char	sBkfkkbn;
	char	cOdrssflg;
	int		iKetasu;
	int		iFukuFlg;
	Ninsiki	strNinsiki;
	int 	sakitukeFileFlg;	//��t���t�@�C���쐬(0:���Ȃ�,1:����)
	int 	iBgroupFlg;			// 3.02 ADD Bgroup=='3'(0:<>'3',1:='3')
	int 	iDupFlg;			// 3.02 ADD -803�㑱�����Ή�(0:���Ȃ�,1:����)
	int		iKmkCd;				// 2008-01-07 �V�t�����e�B�A�Ή� �ǉ�
	int		iMotokenFlg;		// 2008-01-07 �V�t�����e�B�A�Ή� �ǉ�
	char	cId2[11];			// 2008-03-24 �V�t�����e�B�A�Ή� �ǉ�
	int		iId2pos;			// 2008-03-24 �V�t�����e�B�A�Ή� �ǉ�

	Bunchu *pBunF = NULL;
	Ninsiki strNin; /* �F���e�[�u���i�[�\���� */
	int iCnt;

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");
	pKmkCd = (lc_recBuf + BUNCHU_KMK_ADR);
	pBunchu = (Flbun *)lc_recBuf;

	//�t�@�C���T�C�Y�`�F�b�N
	if( strlen(lc_recBuf) != BUNCHU_FILE_SIZE ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�������t�@�C���G���[(�T�C�Y�`�F�b�N) %d", strlen(lc_recBuf) );
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", "", "", "",
				"", "�������t�@�C���G���[(�T�C�Y�`�F�b�N)[ %d ]", strlen(lc_recBuf));
		ZdbRollback();
		return( 10 );
	}

	//�����t�@�C�����ʎq�`�F�b�N(�w�b�_�[���R�[�h)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_HED, 2) ) {
		//�g���[�X���O
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(�w�b�_�[���R�[�h)");
		return( 0 );
	}
	//�����t�@�C�����ʎq�`�F�b�N(�I�����R�[�h)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_STP, 2) ) {
		//�g���[�X���O
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(�I�����R�[�h)");
		return( 0 );
	}
	//�����t�@�C�����ʎq�`�F�b�N
	if( !(!memcmp(pBunchu->sDataSybt, BUNCHU_SYBT, 2) || 
		!memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_END, 2)) ) {
		memset(buf, 0, sizeof(buf));
		memcpy(buf, pBunchu->sDataSybt, 2);
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�������t�@�C���G���[(���ʎq) %s", buf);
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", "", "", "",
				"", "�������t�@�C���G���[(���ʎq)[%s]", buf);
		ZdbRollback();
		return( 10 );
	}
	
	//�����t�@�C�����ʎq�`�F�b�N(����END)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_END, 2) ) {
		memset(buf2, 0, sizeof(buf2));
		memcpy(buf2, pBunchu->sTranId, sizeof(pBunchu->sTranId));
		if( dBunEnd( pst_Env, buf2 ) < 0 ) {
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "dBunEnd ���s");
			ZdbRollback();
			return( -1 );
		}

		//�R�~�b�g
		ZdbCommit();

		//�g���[�X���O
    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(����END)");
		return( 0 );
	}

	iSkipFlg = ialloc = 0;

	//�n���m�F
	memset(sKeito, 0, sizeof(sKeito));
	if( !memcmp(pBunchu->sTranId, "SDATA0", 6) ) {
		memcpy(sKeito, "U0", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA1", 6) ) {
		memcpy(sKeito, "A1", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA2", 6) ) {
		memcpy(sKeito, "A2", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA3", 6) ) {
		memcpy(sKeito, "B1", 2 );
	} else if( !memcmp(pBunchu->sTranId, "SDATA4", 6) ) {
		memcpy(sKeito, "B2", 2 );
	}

	//�������t�擾
	memset(&today, 0, sizeof(BmlDate));
	memset(sDay, 0, sizeof(sDay));
	memset(sysdate, 0, sizeof(sysdate));
	ZbmlDateGetToday(&today);
	ZbmlDateAsString(&today, sDay);
	ZbmlChgAPDate(sysdate, sDay);

	memset(buf, 0, sizeof(buf));
	memset(buf1, 0, sizeof(buf1));
	memset(&strBunchuTB, 0, sizeof(Bunchu));
	memset(&strKanjyaTB, 0, sizeof(Kanjya));
	memset(&strIraiTB, 0, sizeof(Irai));
	
	//BML��t�N���� YYYYMMDD �� YYYY-MM-DD�ɕϊ�
	memcpy(buf, pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
	//ZbmlChgDBDate( buf1, buf, sizeof(buf)-1);
	sprintf(buf1, "%4.4s-%2.2s-%2.2s", buf, &buf[4],&buf[6]);
	strcpy(strBunchuTB.utkymd, buf1);
	strcpy(strKanjyaTB.utkymd, buf1);
	strcpy(strIraiTB.utkymd, buf1);
	//�˗���No
	if( pst_Env->proc_mode ) {
		//������
		memcpy(strIraiTB.irino, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
	} else {
		//�ߓn��
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		memcpy(buf, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
		sprintf(buf1,"00%-3.3s%-6.6s", &buf[0], &buf[5]);
		strcpy(strBunchuTB.irino, buf1);
		strcpy(strKanjyaTB.irino, buf1);
		strcpy(strIraiTB.irino, buf1);

    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�˗���No�ϊ� %s -> %s", buf, strBunchuTB.irino);
	}


	//��������No�@0�Œ�
	strBunchuTB.zssdino = 0;
	//�������@�V�X�e���Ǘ��}�X�^����擾
	ret = getShoribi(pst_Env->sLbcd, pst_Env->sSateid, strBunchuTB.sriymd);
	if( ret == 0 ) {
	//if( (ret = getShoribi(pst_Env->sLbcd, pst_Env->sSateid, strBunchuTB.sriymd)) == 0 ) {
		strcpy(strBunchuTB.sriymd, sDay);
	}
	//����No
	if( pst_Env->proc_mode ) {
		//������
		memcpy(strBunchuTB.kntno, pBunchu->sKentaiNo, sizeof(pBunchu->sKentaiNo));
		strcat(strBunchuTB.kntno, "00");
	} else {
		//�ߓn��
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		ZbmlInfocpy(buf, pBunchu->sKentaiNo, sizeof(pBunchu->sKentaiNo)+1);
		sprintf(buf1,"00%-3.3s%-6.6s", &buf[0], &buf[5]);
    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"����No %s", buf, strBunchuTB.irino);

		//�}�Ԃ��Ȃ��ꍇ��9���ł���̂�0��ǉ�
		if( strlen(buf1) < 11 ) strcat(buf1, "00");

		strcpy(strBunchuTB.kntno, buf1);

    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"����No�ϊ� %s -> %s", buf, strBunchuTB.kntno);

		memset(buf, 0, sizeof(buf));
		memcpy(buf, pBunchu->sWS, sizeof(pBunchu->sWS));
		if( !memcmp(buf, "0151", 4) || !memcmp(buf, "0152", 4) ) 
		{
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//			if( (pBunchu->sMotoKenRk[0] == 'X') || (pBunchu->sMotoKenRk[0] == 'Y') 
			if( (pBunchu->sMotoKenRk[0] == 'V') || (pBunchu->sMotoKenRk[0] == 'X') || (pBunchu->sMotoKenRk[0] == 'Y') 
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
				|| (pBunchu->sMotoKenRk[0] == 'Z') ) 
			{
				/* 2006-04-23 ���̏����폜
				memcpy( &strBunchuTB.kntno[9], "00", 2);
				*/
			} 
			else 
			{
				//�ǂݔ�΂��`�F�b�N�P
				memset(buf1, 0, sizeof(buf1));
				memcpy(buf1, &strBunchuTB.kntno[9], 2);
				iEda = atoi(buf1) % 2;	
				if( !memcmp(buf, "0151", 4) ) {
					if( (atoi(buf1) > 0) && (iEda == 0) ) {
						//�}�ԊԈႢ
    					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�}�ԊԈႢ �˗���No(%s) ����No(%s)", strBunchuTB.irino, strBunchuTB.kntno);
/*
						sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
							strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
							"", "�}�ԊԈႢ WS[%s]", buf);
*/
						iSkipFlg = 1;
						ZdbRollback();
						return( 11 );
					}
				} else {
					if( (atoi(buf1) == 0) && (iEda != 0) ) {
						//�}�ԊԈႢ
    					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�}�ԊԈႢ �˗���No(%s) ����No(%s)", strBunchuTB.irino, strIraiTB.kntno);
/*
						sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
							strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
							"", "�}�ԊԈႢ WS[%s]", buf);
*/
						iSkipFlg = 1;
						ZdbRollback();
						return( 11 );
					}
				}
			}
		}

		//�ǂݔ�΂��`�F�b�N�Q
		if( !memcmp(buf, "0952", 4) || !memcmp(buf, "0959", 4)) {
			if( memcmp(pBunchu->sTranId, "SDATA0", sizeof(pBunchu->sTranId)) ) {
				if( (pBunchu->sMotoKenRk[0] == ' ') || (pBunchu->sMotoKenRk[0] == 'Z') ) {
    				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�f�[�^�X�L�b�v �˗���No(%s) ����No(%s)", strBunchuTB.irino, strIraiTB.irino);
/*
					sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
						strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
						"", "��W�J�f�[�^ WS[%s]", buf);
*/
					iSkipFlg = 1;
					ZdbRollback();
					return( 10 );
				}
			}
		}
		//memcpy(strBunchuTB.kntno, pBunchu->sKentaiNo, sizeof(pBunchu->sKentaiNo));
		//strcat(strBunchuTB.kntno, "00");
	}
	//�T���v�����O�R�[�h
	memcpy(strBunchuTB.smpcd, pBunchu->sWS, sizeof(pBunchu->sWS));
	//�T���v�����O�R�[�h���ʒuNo�@0�Œ�
	strBunchuTB.smpcditno = 0;
	memset(sWork, 0, sizeof(sWork));
	memset(sWork1, 0, sizeof(sWork1));
	//�`�F�b�N����
	//memcpy(sWork1, pBunchu->sKenChkChar, sizeof(pBunchu->sKenChkChar));
	//sj2euc(sWork, sWork1, sizeof(strBunchuTB.chkmj));
	memcpy(strBunchuTB.chkmj, pBunchu->sKenChkChar, sizeof(pBunchu->sKenChkChar));
	//memcpy(strBunchuTB.chkmj, pBunchu->sKenChkChar, sizeof(strBunchuTB.chkmj));
	//�g���[ID
	// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
	//memcpy(strBunchuTB.trid, pBunchu->sRackId, sizeof(pBunchu->sRackId));
	memcpy(strBunchuTB.trid, TRID_BLANK, sizeof(pBunchu->sRackId));
	//�g���[�|�W�V����
	//memset(buf, 0, sizeof(buf));
	//memcpy(buf, pBunchu->sIchi, sizeof(pBunchu->sIchi));
	//strBunchuTB.trpos = atoi(buf);
	strBunchuTB.trpos = 0;
	// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	if( strBunchuTB.trpos == 0 ) {	//�|�W�V����0�̓I�[�_�쐬���Ȃ�
    	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�f�[�^�X�L�b�v(�|�W�V�����O) �˗���No(%s) ����No(%s)", 
			strBunchuTB.irino, strBunchuTB.kntno);
/*
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strIraiTB.kntno, strIraiTB.irino, "", "��I�[�_�쐬(�|�W�V�����O)");
		iSkipFlg = 1;
*/
	}


	//�A�b�Z�C���b�NID
	memcpy(strBunchuTB.asyrckid, pBunchu->sRackId, sizeof(pBunchu->sRackId));
	// 2008-01-07 �V�t�����e�B�A�Ή� DEL START
	//memset(strBunchuTB.asyrckid, ' ', sizeof(pBunchu->sRackId));
	// 2008-01-07 �V�t�����e�B�A�Ή� DEL END
	//�A�b�Z�C���b�N�|�W�V����
	memset(buf, 0, sizeof(buf));
	memcpy(buf, pBunchu->sIchi, sizeof(pBunchu->sIchi));
	strBunchuTB.asyrckpos = atoi(buf);


	//�����̃��b�NID
	memset(buf2, 0, sizeof(buf2));
	memset(buf2, ' ', sizeof(pBunchu->sMotoKenRk));
	//�I�[���X�y�[�X�Ɛ擪��'Z'�̏ꍇ�͕ҏW���Ȃ�
	/* 2006-04-06 ���̏����폜
	if( !( !memcmp(pBunchu->sMotoKenRk, buf2, sizeof(pBunchu->sMotoKenRk)) && (pBunchu->sMotoKenRk[0] == 'Z')) ) {
		memset(buf2, 0, sizeof(buf2));
		memcpy(buf2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
		switch(buf2[0]) {
		case 'x':
		case 'X':
			sprintf(strBunchuTB.id2, "XXXX%s", &buf2[4]);
			break;
		case 'y':
		case 'Y':
			sprintf(strBunchuTB.id2, "YYYY%s", &buf2[4]);
			break;
		default:
			memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
			break;
		}
	}
	*/
	// DEL E.Osada 2006-09-12
//#if 0
//	/* ���� 2006-08-27 */
//	if( !memcmp(pBunchu->sMotoKenRk, buf2, sizeof(pBunchu->sMotoKenRk)) ) {
//		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//            "pBunchu->sMotoKenRk (%s),buf2(%s)"pBunchu->sMotoKenRk, buf2);
//		
//		iSkipFlg = 1;
//		ZdbRollback();
//		return( 10 );
//	}
//	//
//#endif

	// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
	//memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
	iMotokenFlg = 0 ;
	//�����̃��b�NID���I�[���X�y�[�X�̏ꍇ�͂��̂܂܂�ݒ�
	if( !memcmp(pBunchu->sMotoKenRk, buf2, sizeof(pBunchu->sMotoKenRk)) )
	{
		memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
		iMotokenFlg = 2 ;
	}
	//�����̃��b�NID���I�[�����l�̏ꍇ(2ID)�́A'____0000'��ݒ�
	else if( !sFncChkDigit( pBunchu->sMotoKenRk ) )
	{
		memcpy(strBunchuTB.id2, TRID_BLANK, sizeof(pBunchu->sMotoKenRk));
		iMotokenFlg = 1 ;
	} else {
		memcpy(strBunchuTB.id2, pBunchu->sMotoKenRk, sizeof(pBunchu->sMotoKenRk));
	}
	// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	//�����̃|�W�V����
	memset(buf, 0, sizeof(buf));
	memcpy(buf, pBunchu->sMotoKenPos, sizeof(pBunchu->sMotoKenPos));
	// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
	//strBunchuTB.id2pos = atoi(buf);
	//�����̃��b�NID���I�[�����l or �I�[���X�y�[�X�̏ꍇ(2ID)�́A0��ݒ�
	if( iMotokenFlg ) {
		strBunchuTB.id2pos = 0;
	} else {
		strBunchuTB.id2pos = atoi(buf);
	}
	// 2008-01-07 �V�t�����e�B�A�Ή� UPD END

	// 2008-03-10 �V�t�����e�B�A�Ή� UPD START
	//���ҏ��m�F
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"���ҏ��m�F");

	if( (ret = ABunKnjSel(&strKanjyaTB, &pKanjya, &cnt)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT KANJYA[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		return( -1 );
	}
	if( cnt == 0 ) {
		//���ҏ�񂪖����ꍇ�̓X�L�b�v
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"���ҏ�� NOT FOUND BML��t��(%s) �˗���No(%s)", strIraiTB.utkymd, strIraiTB.irino ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strIraiTB.kntno, strIraiTB.irino, "", "���ҏ�񖳂�");
		ZdbRollback();
		return 12;
	}
//	//���ʋ敪
//	strBunchuTB.sbtkbn = pBunchu->sSexKbn[0];
//	//�N��
//	memcpy(strBunchuTB.age, pBunchu->sAge, sizeof(pBunchu->sAge));
//	//�N��敪
//	strBunchuTB.agekbn = pBunchu->sAgeKbn[0];
//	//�{�݃R�[�h
//	memcpy(strBunchuTB.sstcd, pBunchu->sSisetuCd, sizeof(pBunchu->sSisetuCd));
//	//�c�Ə��R�[�h
//	memcpy(strBunchuTB.ecd, pBunchu->sEigyoCd, sizeof(pBunchu->sEigyoCd));
	//���ʋ敪
	strBunchuTB.sbtkbn = pKanjya->sbtkbn;
	//�N��
	memcpy(strBunchuTB.age, pKanjya->age, sizeof(pKanjya->age));
	//�N��敪
	strBunchuTB.agekbn = pKanjya->agekbn;
	//�{�݃R�[�h
	memcpy(strBunchuTB.sstcd, pKanjya->sstcd, sizeof(pKanjya->sstcd));
	//�c�Ə��R�[�h
	memcpy(strBunchuTB.ecd, pKanjya->ecd, sizeof(pKanjya->ecd));
	// 2008-03-10 �V�t�����e�B�A�Ή� UPD END
	//�����@ID�@�X�y�[�X
	memset(strBunchuTB.bckid, ' ', sizeof(strBunchuTB.bckid)-1);
	//��ԃt���O
	strBunchuTB.jtflg = pBunchu->sStsFlg[0];
	//�������
	strBunchuTB.knssyr = pBunchu->sKnsSyrui[0];
	//�����t���O
	strBunchuTB.tknflg = pBunchu->sChiKenFlg[0];
	//����E�ً}�t���O
	strBunchuTB.ttkkflg = pBunchu->sKnkyFlg[0];
	//��������
	strBunchuTB.bnckka = pBunchu->sBunKekka[0];

	//�A�t������s���ő����Ă����������͎�荞�܂Ȃ��B 2016/06/10 ADD
	if( !strncmp(strBunchuTB.smpcd, NYO_KNSGRP, 4) && (strBunchuTB.bnckka == 'G') ){
    	sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�A�d���� �s�����̃X�L�b�v �˗���No(%s) ����No(%s)", strBunchuTB.irino, strIraiTB.irino);
		iSkipFlg = 1;
		ZdbRollback();
		return( 10 );
	}

	//����OK�̂��̂̂݃I�[�_�쐬����ׂ̔��f
	if( (strBunchuTB.bnckka == '0') || (strBunchuTB.bnckka == '4') ) {
		iOdrMkFlg = 0;		//����OK�F�I�[�_�쐬
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "����OK�F�I�[�_�쐬 iOdrMkFlg(%d)",iOdrMkFlg);
	} 
	else if( strBunchuTB.bnckka == '1' ) 
	{
		iOdrMkFlg = 2;		//�����{���F�I�[�_�쐬���Ȃ�
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�����{���F�I�[�_�쐬���Ȃ� iOdrMkFlg(%d)",iOdrMkFlg);
	} else {
		iOdrMkFlg = 1;		//����OK�łȂ��F�I�[�_���Ȃ�
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "����OK�łȂ��F�I�[�_���Ȃ� iOdrMkFlg(%d)",iOdrMkFlg);
	}
	//�\�[�g�L�[�@0�Œ�
	strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);

// 2008-03-10 �V�t�����e�B�A�Ή� DEL START
// ���̐��ʋ敪����ݒ肷�钼�O�Ɉړ�
//	//���ҏ��m�F
//	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//		"���ҏ��m�F");
//
//	if( (ret = ABunKnjSel(&strKanjyaTB, &pKanjya, &cnt)) < 0 ) {
//		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			"SELECT KANJYA[SQLCODE=%d]", ret ) ;
//		ZdbRollback();
//		return( -1 );
//	}
//	if( cnt == 0 ) {
//		//���ҏ�񂪖����ꍇ�̓X�L�b�v
//		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			"���ҏ�� NOT FOUND BML��t��(%s) �˗���No(%s)", strIraiTB.utkymd, strIraiTB.irino ) ;
//		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
//			strIraiTB.kntno, strIraiTB.irino, "", "���ҏ�񖳂�");
//		ZdbRollback();
//		return 12;
//	}
// 2008-03-10 �V�t�����e�B�A�Ή� DEL END

	// ���ҏ��̔��l2����{�A���ҏW
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "���ҏ��̔��l2����{�A���ҏW");
	memset(buf, 0, sizeof(buf));
	iHit = j = 0;
	memset(buf, 0, sizeof(buf));
	for( i=0; i < sizeof(pKanjya->bko2) ;++i ) {
		if( pKanjya->bko2[i] != '!' ) {
				buf[j++] = pKanjya->bko2[i];
		} else {
			switch(iHit) {
			case 0:		//�{�A����
				memcpy(strBunchuTB.tntme, buf, sizeof(pBunchu->sChikuTm));
				break;
			case 1:		//�{�A���ԒP��
				strBunchuTB.tntni = buf[0];
				break;
			case 2:		//�{�A��
				memcpy(strBunchuTB.tnryo, buf, sizeof(pBunchu->sChikuRyo));
				break;
			case 3:		//�{�A�ʋ敪�i���肦�Ȃ��I�H�j
				strBunchuTB.tnryotni = buf[0];
				break;
			}
			memset(buf, 0, sizeof(buf));
			iHit++;
			j = 0;
		}
	}
	if( iHit == 3 ) {
		//�{�A�ʋ敪
		strBunchuTB.tnryotni = buf[0];
	}

	//��������No�擾
	strIraiTB.zssdino = pKanjya->zssdino;
	strBunchuTB.zssdino = pKanjya->zssdino;

	//�˗����e�[�u���擾
	if( (ret = ABunIriSel(&strIraiTB, &pIrai, &iIrai)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT IRAI[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( 0 );
	}
	if( iIrai == 0 ) {
		//�˗���񂪖���
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�˗���� NOT FOUND BML��t��(%s) �˗���No(%s) ��������No(%d) ���ڃR�[�h(%s)",
			strBunchuTB.utkymd, strBunchuTB.irino, strBunchuTB.zssdino, strIraiTB.kmkcd ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strBunchuTB.kntno, strBunchuTB.irino, "", "�˗���񖳂�");
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		// Update 2007.04.05 return( 10 );
		return( 12 );
	}

// 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� INS START
	//�˗����R�s�[
	memset(&pIraiW2, 0, sizeof(Irai));
	memcpy(&pIraiW2, pIrai, sizeof(Irai));
	memcpy(pIraiW2.smpcd, strBunchuTB.smpcd, sizeof(strBunchuTB.smpcd));
	//�˗����e�[�u�����獀�ڃR�[�h�̂ݎ擾 (select key:utkymd, irino, smpcd)
	if( (ret = ABunIriKmkCdSel(&pIraiW2, &pIrai2, &iKmkCd)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT IRAI[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( 0 );
	}
	if( iKmkCd == 0 ) {
		//�˗����ɍ��ڃR�[�h������
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�˗���� NOT FOUND BML��t��(%s) �˗���No(%s) ��������No(%d) ���ڃR�[�h(%s)",
			strBunchuTB.utkymd, strBunchuTB.irino, strBunchuTB.zssdino, strIraiTB.kmkcd ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
			strBunchuTB.kntno, strBunchuTB.irino, "", "�˗���񖳂�");
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}

		return( 12 );
	}
//sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//    "iKmkCd <%d>",iKmkCd);
//for( i=0; i < iKmkCd ;++i ) {
//	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//	    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//	    "KmkCd <%s>",(pIrai2+i)->kmkcd);
//}
// 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� INS END

	// 3.02 ADD STA
	iBgroupFlg = 0;
	iDupFlg = 0;
	// 3.02 ADD END

	if(iOdrMkFlg == 0)	
			sakitukeFileFlg = 1;
	else
			sakitukeFileFlg = 0;
	iOrder = 0;
	iOldFlg = iOdrMkFlg;
	//���ڃR�[�h��INSERT����
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "���ڃR�[�h��INSERT���� iOdrMkFlg <%d>",iOdrMkFlg);

// 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� UPD START
//	for( i=0; i < BUNCHU_KMK_MAX ;++i ) {
	for( i=0; i < iKmkCd ;++i ) {
// 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� UPD END
		iOdrMkFlg = iOldFlg;
// 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� UPD START
//		pKmkCd1 = pKmkCd + (i * BUNCHU_KMK_SZ);
		pKmkCd1 = (pIrai2+i)->kmkcd;
//sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//    "pKmkCd1 <%s>",pKmkCd1);
// 2008-01-07 ���ڃR�[�h 64���ڈȏ�Ή� UPD END
		memset(buf2, 0, sizeof(buf2));
		memcpy(buf2, pKmkCd1, BUNCHU_KMK_SZ);
		if( pKmkCd1 == NULL ) {
			//���O�o��
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
            	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            	"pKmkCd1 == NULL");
			ZdbRollback();
			return(-1);
		}
		//�˗�TB����̏��Ɣ�ׂ�
		if( !memcmp(buf2, "       ", BUNCHU_KMK_SZ) ) {
			//�X�y�[�X�������珈���X�L�b�v
			continue;
		}
		//���ڃR�[�h����
		for( k=0; k < iIrai ;++k ) {
			if( !memcmp((pIrai+k)->kmkcd, buf2, 7) ) {
				//�q�b�g�I�I
				//pIraiW = (pIrai+k);
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"��v���鍀�ڃR�[�h����(%s)",buf2);
				break;
			}
		}
		if( k >= iIrai ){
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"��v���鍀�ڃR�[�h�Ȃ�(%s)",buf2);
			continue;
		}

		if( (pIrai+k)->odrssflg == 'F' ) {
			//���Ɏ��������ōς݂̈׃X�L�b�v
			continue;
		}

		strBunchuTB.bnckka = pBunchu->sBunKekka[0];

		//�����O���[�v�W�J
		memset(sWknsgrp, 0, sizeof(sWknsgrp));
		//���ڃ}�X�^����
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"���ڃ}�X�^����");
		if( (ret = ABunGetKnsgrp(&strBunchuTB, pKanjya, buf2, sWknsgrp)) < 0 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���ڃ}�X�^ NOT FOUND ���ڃR�[�h(%s) �T���v�����O�R�[�h(%s) �J�n�N����(%s)",
				buf2, strBunchuTB.smpcd, strBunchuTB.sriymd ) ;
   			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				"���ڃ}�X�^�Ȃ� IRINO(%s) KNTNO(%s)", strBunchuTB.irino, strBunchuTB.kntno);
			ZdbRollback();
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			ZdbRollback();
			return(10);
		}
		if( ret == 0 ) {
			//���ڃ}�X�^�Ɍ����O���[�v�����݂��Ȃ��ꍇ�̓X�L�b�v
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���ڃ}�X�^ NOT FOUND ���ڃR�[�h(%s) �T���v�����O�R�[�h(%s) �J�n�N����(%s)",
				buf2, strBunchuTB.smpcd, strBunchuTB.sriymd ) ;
			sFuncPutErrlist(pst_Env,sFLname,iFLcnt,strBunchuTB.sriymd,strBunchuTB.utkymd, 
				strBunchuTB.kntno, strBunchuTB.irino, buf2, "���ڃ}�X�^����");
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			ZdbRollback();
			return( 10 );
		}
//YOON 2007-02-01�@�֐��̒��ŏ����Ă��܂��B
//		if( ret == 2 ) {
//			sFuncPutErrlist(pst_Env,sFLname,iFLcnt,strBunchuTB.sriymd,strBunchuTB.utkymd, 
//				strBunchuTB.kntno, strBunchuTB.irino, buf2, "���ڃ}�X�^����");
//		}
		
		//YOON 2007-02-01
		if( ret == 3 ) {
			iOdrMkFlg = 1;				//�I�[�_���Ȃ�
   			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�����敪���R���� iOdrMkFlg��<1>�ɕύX");
			//YOON
			sakitukeFileFlg = 0;
			// 3.02 ADD -803�㑱�������f�p
			iBgroupFlg = 1;
		}
		//�����O���[�v�ݒ�
		memcpy((pIrai+k)->knsgrp, sWknsgrp, 16);
		//�n���ݒ�
		memcpy(strBunchuTB.bckid, sKeito, 2);
		//�������ڃR�[�h
		memset(strBunchuTB.kmkcd, 0, sizeof(strBunchuTB.kmkcd));
		memcpy(strBunchuTB.kmkcd, pKmkCd1, BUNCHU_KMK_SZ);

		//�\�[�g�L�[�Čv�Z
		strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);

		iFukuFlg = 0;
		//�������Z�[�u
		memset(&pBunW, 0, sizeof(Bunchu));
		memcpy(&pBunW, &strBunchuTB, sizeof(Bunchu));

		//�˗�.�I�[�_�쐬�󋵃t���O�X�V
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�˗�.�I�[�_�쐬�󋵃t���O�X�V odrssflg:<%c>",(pIrai+k)->odrssflg);
		if( (pIrai+k)->odrssflg == ' ' ) {	//�˗����������
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�˗����������");
			if( iOdrMkFlg == 0 ) {
				(pIrai+k)->odrssflg = '2';
			} else if( iOdrMkFlg == 2 ) {
				(pIrai+k)->odrssflg = '1';
				//�����{�t���OON ADD 2006-07-17 E.Osada
				memset(&strNinsiki, 0, sizeof(Ninsiki));
				strcpy(strNinsiki.utkymd, strBunchuTB.utkymd);
				strcpy(strNinsiki.sriymd, strBunchuTB.sriymd);
				strcpy(strNinsiki.irino, strBunchuTB.irino);
				strcpy(strNinsiki.kntno, strBunchuTB.kntno);
				strNinsiki.zssdino = strBunchuTB.zssdino;
				if( (ret = ABunNinUpAll( &strNinsiki )) < 0 ) {
					//�G���[���O�o��
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE NINSIKI(W)[%s %s %s %s %s] [SQLCODE=%d]", 
						strBunchuTB.sriymd, strBunchuTB.utkymd, 
						strIraiTB.kntno, strIraiTB.irino, (pIrai+k)->kmkcd, ret);
					ZdbRollback();
					return( -1 );
				}
				//
			} else {
				(pIrai+k)->odrssflg = '1';
			}
		} else {	//�˗��͊��ɕ����W�J�������s���Ă���
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�����{���m�F irino:%s,kmkcd:%s",(pIrai+k)->irino,(pIrai+k)->kmkcd);
			// �����{���m�F
			//if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0) )
			memset(sWork, 0, sizeof(sWork));
			ZbmlInfocpy(sWork, (pIrai+k)->smpcd, sizeof((pIrai+k)->smpcd));
			if( !strcmp(strBunchuTB.smpcd, sWork) ) 
			{ // �T���v�����O�R�[�h�`�F�b�N
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�T���v�����O�R�[�h�`�F�b�N");

				/* 2.01 ADD STA /////////////////////////////////////////////
				// ����NG->WS�o��->����OK�̏ꍇ�́AOK�̃I�[�_���쐬����
				// -> �擾�����˗����.�I�[�_�쐬�׸ނ��w�����(=1)�ɒu��
				if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0) ) { */
				/*  4.02 ��L�̑Ή��ł͕���NG�̌��ʂ��Č��ɉ���Ă���ƑʖڂȂ̂ŁA������ǉ�
					  (�����H���敪�� A (����)�ȊO�̏ꍇ �� WS����x�͏o�͂��Ă���)  */
				if( ( ((pIrai+k)->odrssflg == '2') || !((pIrai+k)->ksktkbn == 'A') ) && (iOdrMkFlg == 0) ) {
					if( cntBunchuOk( &strBunchuTB ) == 0 ) 
					{
						// ����OK�̕������ʏ�񂪑��݂��Ȃ�->�I�[�_�쐬
						(pIrai+k)->odrssflg = '1';
				
						//YOON 2007-02-15 odrssflg�𗘗p���Ȃ��B
						iDBBunUpflg = 0;						
				
						//2006-12-13 YOON ���̈������O�o��
						if(strcmp(strIraiTB.irino,tmpiraino))
						{
						sFncPutLog(TRCKIND_ERROR, __FILE__
							, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"����NG->WS�o��->����OK [%s %s kntno(%s) irino(%s) kmkcd(%s)]", 
							strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
							strcpy(tmpiraino,strIraiTB.irino);
						}
					}
				}
				// 2.01 ADD END /////////////////////////////////////////////

				/* 2007-08-07 Nagata ///////////////////////////////////////////////////////
				����NG �� WS�쐬 �� �񕪒��@�̏ꍇ�͌ォ�痈���������ʂ𕡐��{�����Ƃ���
				if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0) ) {
				if( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0 || iOdrMkFlg == 1) ) { */
				/* 4.02 ��L�̑Ή��ł͕���NG�̌��ʂ��Č��ɉ���Ă���ƑʖڂȂ̂ŁA������ǉ�
						(�����H���敪������ȊO�Ŏ������񕪒��̏ꍇ)  */
				if( ( ((pIrai+k)->odrssflg == '2') && (iOdrMkFlg == 0 || iOdrMkFlg == 1) ) ||
						(!((pIrai+k)->ksktkbn == 'A') && iOdrMkFlg == 1) ) {
					//�����{���I�I
					strBunchuTB.bnckka = '1';
					//�����{�t���O�X�V
					if( (ret = ABunSelKey( &strBunchuTB, &pBunF, &iCnt )) < 0 ) {
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
										 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										 "�������SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)",
										 strBunchuTB.irino, strBunchuTB.kntno, strBunchuTB.kmkcd, ret);
					}
					if( iCnt > 0 ) {
						memset(&strNin, 0, sizeof(Ninsiki));
						strcpy(strNin.utkymd, pBunF->utkymd);
						strcpy(strNin.sriymd, pBunF->sriymd);
						strcpy(strNin.irino, pBunF->irino);
						strcpy(strNin.kntno, pBunF->kntno);
						strNin.zssdino = pBunF->zssdino;
						if( (ret = ABunNinUp( &strNin )) < 0 ) {
								sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
											 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
											 "�F�����SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)",
											 strBunchuTB.irino, strBunchuTB.kntno, strBunchuTB.kmkcd, ret);
						}
					}
	
					//�\�[�g�L�[�Čv�Z
					strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);
					iOdrMkFlg = 3;
				} 
				else 
				{
					if( ((pIrai+k)->odrssflg == '1') && (iOdrMkFlg == 0) ) {
						//�ォ�番���n�j�������̂ŃI�[�_���s����
						(pIrai+k)->odrssflg = '2';
						iOdrMkFlg = 0;
					} else {
						sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�����{��� fileno(%d) odrssflg(%c) kntno(%s) kmkcd(%s) smpcdI(%s) smpcdB(%s)",
							iFLcnt, pIraiW.odrssflg, strBunchuTB.kntno, (pIrai+k)->kmkcd,
							(pIrai+k)->smpcd, strBunchuTB.smpcd);
					}
					iFukuFlg = 1;
					//�����{�D��x�m�F
					// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, (pIrai+k)->knsgrp )) < 0 ) [
						/*DEBUG STA --------------------------------------------*/
						sFncPutLog ( TRCKIND_DEBUG, __FILE__
							, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"chkBunchu IN 1 [%d][%s %s %s %s %s]", 
							iDBBunUpflg,
							strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
						/*DEBUG END --------------------------------------------*/
					//YOON 2007-02-15
					if((iRet = chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
						(pIrai+k)->knsgrp,iDBBunUpflg)) < 0 ) 
					{
						sFncPutLog ( TRCKIND_DEBUG, __FILE__
                            , "dBunchu_ins", __LINE__,
                            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "chkBunchu ���s");
						ZdbRollback();
						return( -1 );
					}
					if( iOdrMkFlg != 0 ) {
						if( (pIrai+k)->odrssflg != '2' )
							(pIrai+k)->odrssflg = '1';
						// CHG E.Osada 2006-08-30
						//if( iRet == 1 ) [
						if( iRet != 2 ) {
							iOdrMkFlg = 1;
						} else {
							//�����{���Ώۂ̏ꍇ�͕������ʂ�'1'���Z�b�g 2006-06-13 E.osada
							strBunchuTB.bnckka = '1';
							//�\�[�g�L�[�Čv�Z
							strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, 
													strBunchuTB.bnckka);
							iOdrMkFlg = 3;
						}
					}
				}
			} else {
				//�T���v�����O�R�[�h���Ⴄ�̂ŃI�[�_���쐬(06/04/16�Ŕ��������p�^�[��)
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�T���v�����O�R�[�h�Ⴂ fileno(%d) ssflg(%c) kntno(%s) kmkcd(%s) smpcd1(%s) smpcd2(%s)",
					iFLcnt, pIraiW.odrssflg, strBunchuTB.kntno, strBunchuTB.kmkcd, sWork, strBunchuTB.smpcd);
				if( iOdrMkFlg == 0 ) {
					(pIrai+k)->odrssflg = '2';
				} else {
					(pIrai+k)->odrssflg = '1';
				}
//�T���v�����O�R�[�h������Ă���ꍇ�͕����{���ł͂Ȃ�
#if 0
				//�����{�t���OON ADD 2006-07-17 E.Osada
				//�T���v�����O�R�[�h������Ă��Ă��F�����ɂ�"W"���Z�b�g����
				memset(&strNinsiki, 0, sizeof(Ninsiki));
				strcpy(strNinsiki.utkymd, strBunchuTB.utkymd);
				strcpy(strNinsiki.sriymd, strBunchuTB.sriymd);
				strcpy(strNinsiki.irino, strBunchuTB.irino);
				strcpy(strNinsiki.kntno, strBunchuTB.kntno);
				strNinsiki.zssdino = strBunchuTB.zssdino;
				if( (ret = ABunNinUp( &strNinsiki )) < 0 ) {
					//�G���[���O�o��
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE NINSIKI(W)[%s %s %s %s %s] [SQLCODE=%d]", 
						strBunchuTB.sriymd, strBunchuTB.utkymd, 
						strIraiTB.kntno, strIraiTB.irino, (pIrai+k)->kmkcd, ret);
					ZdbRollback();
					return( -1 );
				}
#endif
			}
		}
	
		strcpy((pIrai+k)->knsgrp, sWknsgrp);
		strcpy((pIrai+k)->sriymd, strBunchuTB.sriymd);
		
		//�����J�n���擾
		memset(sWknsStart, 0, sizeof(sWknsStart));
		//YOON 2007-02-01
		//getKnsKaisibi((pIrai+k)->knsgrp, strBunchuTB.sriymd, sWknsStart);
		getShoribi(pst_Env->sLbcd, pst_Env->sSateid,sWknsStart);
		strcpy((pIrai+k)->knskisyymd, sWknsStart);

		//�˗����R�s�[
		memset(&pIraiW, 0, sizeof(Irai));
		memcpy(&pIraiW, (pIrai+k), sizeof(Irai));
		
		//�˗��e�[�u���X�V
		if( iOdrMkFlg != 3 ) {
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�˗��e�[�u���X�V iOdrMkFlg:%d",iOdrMkFlg);

			if( (ret = ABunKnsgrpUpdate( &pIraiW )) < 0 ) {
				if( ret != -803 ) {
					//�G���[���O�o��
					sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
						strBunchuTB.utkymd, 
						strIraiTB.kntno, strIraiTB.irino, (pIrai+k)->kmkcd, 
						"�˗����X�V�G���[[%d] KNSGRP[%s]", 
						ret, (pIrai+k)->knsgrp);
					ZdbRollback();
					if( pIrai != NULL ) {
						ZbmlFree(pIrai);
						pIrai = NULL;
					}
					if( pKanjya != NULL ) {
						ZbmlFree(pKanjya);
						pKanjya = NULL;
					}
// 2008-01-07 �V�t�����e�B�A�Ή� INS START
					if( pIrai2 != NULL ) {
						ZbmlFree(pIrai2);
						pIrai2 = NULL;
					}
// 2008-01-07 �V�t�����e�B�A�Ή� INS END
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE IRAI[%s %s %s %s] [SQLCODE=%d]", 
						strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
						strBunchuTB.kmkcd, ret );
					ZdbRollback();
					return( 10 );
				}
			}
		}

		l = 0;
		//pIraiW1 = NULL;
		iOya = 0;
		iSkipFlg = 1;
		while(1) 
		{
			if(iSkipFlg == 1) 
			{
				// 2008-03-24 �V�t�����e�B�A�Ή� INS START
				//���̑����e�[�u������ID2���擾
				if( iMotokenFlg == 1 )
				{
					sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"���̑����e�[�u������ID2���擾");

					// ID2�����������ꍇ�A�������ʏ��e�[�u����INSERT����ID2, ID2POS������������
					memset(cId2, 0, sizeof(cId2));
					ret = AZokuSelId2(strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.zssdino, cId2, &iId2pos);

					if( ret == HRC_SQL_NORMAL )
					{
						sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�������ʃt�@�C���f�[�^        [id2 = '%s', id2pos = %d]", 
							strBunchuTB.id2, strBunchuTB.id2pos );

						sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"���̑����e�[�u������ID2���擾 [id2 = '%s', id2pos = %d] BUNCHU[UTKYMD='%s', IRINO='%s', ZSSDINO=%d, SRIYMD='%s', KNTNO='%s', SMPCD='%s', KMKCD='%s']",
							cId2, iId2pos, strBunchuTB.utkymd, strBunchuTB.irino, strBunchuTB.zssdino, strBunchuTB.sriymd,
							strBunchuTB.kntno, strBunchuTB.smpcd, strBunchuTB.kmkcd);

						// ID2, ID2POS������������
						memcpy(strBunchuTB.id2, cId2, sizeof(cId2));
						strBunchuTB.id2pos = iId2pos;
						//�\�[�g�L�[�Čv�Z
						strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, strBunchuTB.bnckka);
					} else {
						if( ret < 0 )
						{
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							sFncPutLog(TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"SELECT KENZOK[%s %s %d] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.zssdino, ret );
							ZdbRollback();
							return( 10 );
						}
						else if( ret == HRC_SQL_NOT_FOUND )
						{
							sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"���̑����e�[�u���Ƀ��R�[�h��������Ȃ��̂ŁAID2�ύX�Ȃ�");
						} else {
							sFncPutLog(TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"���̑����e�[�u�� SELECT ret[%d]", ret);
						}
					}
				}
				// 2008-03-24 �V�t�����e�B�A�Ή� INS END
				
				ABunchuChk(&strBunchuTB);
				//�������ʏ��e�[�u����INSERT
				sFncPutLog(TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�������ʏ��e�[�u����INSERT");
				if( (ret = ABunBunIns(&strBunchuTB)) != HRC_SQL_NORMAL ) 
				{
					if( ret != -803 ) {	//2006-04-23 BUGG FIX
						if( pIrai != NULL ) {
							ZbmlFree(pIrai);
							pIrai = NULL;
						}
						if( pKanjya != NULL ) {
							ZbmlFree(pKanjya);
							pKanjya = NULL;
						}
						// 2008-01-07 �V�t�����e�B�A�Ή� INS START
						if( pIrai2 != NULL ) {
							ZbmlFree(pIrai2);
							pIrai2 = NULL;
						}
						// 2008-01-07 �V�t�����e�B�A�Ή� INS END
						sFncPutLog(TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"INSERT BUNCHU[%s %s %s %s] [SQLCODE=%d]", 
							strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
							strBunchuTB.kmkcd, ret );
						ZdbRollback();
						return(10);
					} else {
						//����OK�̏ꍇ��UPDATE����
						sFncPutLog(TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
                            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "iOdrMkFlg<%d==0>�Ȃ番��OK�̏ꍇ��UPDATE����",iOdrMkFlg);
						if( iOdrMkFlg == 0 ) {
							if( (ret=ABunUpdate( &strBunchuTB )) != HRC_SQL_NORMAL ) {
								if( pIrai != NULL ) {
									ZbmlFree(pIrai);
									pIrai = NULL;
								}
								if( pKanjya != NULL ) {
									ZbmlFree(pKanjya);
									pKanjya = NULL;
								}
								// 2008-01-07 �V�t�����e�B�A�Ή� INS START
								if( pIrai2 != NULL ) {
									ZbmlFree(pIrai2);
									pIrai2 = NULL;
								}
								// 2008-01-07 �V�t�����e�B�A�Ή� INS END
								sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"INSERT BUNCHU[%s %s %s %s] [SQLCODE=%d]", 
									strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
									strBunchuTB.kmkcd, ret );
								ZdbRollback();
								return(10);
							}
						} else {
							// 3.02 ADD STA
							// ���O���̑Ή� bgroup=='3' AND bnckka=='OK' -> UPDATE
							if (( iBgroupFlg == 1 )
								&& (( strBunchuTB.bnckka=='0' )||(strBunchuTB.bnckka=='4' ))){
								sFncPutLog(TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"���O�Ή� UPDATE BUNCHU[%s %s %s %s]", 
									strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
									strBunchuTB.kmkcd );
								// -803�Ή����s����FLG�Z�b�g(KENZOK,NINSIKI�����l�̍l�����s������)
								iDupFlg=1;
								if( (ret=ABunUpdate( &strBunchuTB )) != HRC_SQL_NORMAL ) {
									if( pIrai != NULL ) {
										ZbmlFree(pIrai);
										pIrai = NULL;
									}
									if( pKanjya != NULL ) {
										ZbmlFree(pKanjya);
										pKanjya = NULL;
									}
									// 2008-01-07 �V�t�����e�B�A�Ή� INS START
									if( pIrai2 != NULL ) {
										ZbmlFree(pIrai2);
										pIrai2 = NULL;
									}
									// 2008-01-07 �V�t�����e�B�A�Ή� INS END
									sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
										"INSERT BUNCHU[%s %s %s %s] [SQLCODE=%d]", 
										strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
										strBunchuTB.kmkcd, ret );
									ZdbRollback();
									return(10);
								}
							} else {
							// 3.02 ADD END

								if( pIrai != NULL ) {
									ZbmlFree(pIrai);
									pIrai = NULL;
								}
								if( pKanjya != NULL ) {
									ZbmlFree(pKanjya);
									pKanjya = NULL;
								}
								// 2008-01-07 �V�t�����e�B�A�Ή� INS START
								if( pIrai2 != NULL ) {
									ZbmlFree(pIrai2);
									pIrai2 = NULL;
								}
								// 2008-01-07 �V�t�����e�B�A�Ή� INS END
								//�G���[�t�@�C���ɏ�������
								sFncPutLog(TRCKIND_WARNING,__FILE__,"dBunchu_ins",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"INSERT BUNCHU[������:%s ����:%s smpcd:%s kmkcd:%s] [SQLCODE=%d]", 
									strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd,
									strBunchuTB.kmkcd, ret ); 
								ZdbRollback();
								return(8);
							} // 3.02 ADD
						}
					}
				}
				//YOON 2007-02-19
				if( iOdrMkFlg == 3 ) {
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�����̂ݍ쐬���[�h(iOdrMkFlg=%d)",iOdrMkFlg);
					break;		//�����̂ݍ쐬���[�h
				}
				if( iOdrMkFlg == 0 ) 
				{		
					//�����I�[�_���쐬
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
                        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "�����I�[�_���쐬(iOdrMkFlg:%d)",iOdrMkFlg);
					if( (ret = AbufInsOrder(pst_Env, &pIraiW, &strBunchuTB, pKanjya, &pOrder)) < 0 ) {
						if( ret != -803 ) {
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
								strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino,
								"", "�����I�[�_���쐬�G���[");
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"INSERT KENORDER[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						} else {
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strBunchuTB.kntno, strBunchuTB.irino, buf2, "�����I�[�_�d��");
						}
					}
					//�����`�F�b�N���쐬
					if( AbunInsChk(pst_Env, &pOrder,  pKanjya) < 0 ) {
						if( ret != -803 ) {
							//�G���[���O�o��
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strIraiTB.kntno, strIraiTB.irino, buf2, "�����I�[�_�ǉ��G���[[%d]", ret);
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"INSERT REALCHK[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						} else {
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strBunchuTB.kntno, strBunchuTB.irino, buf2, "�����`�F�b�N�d��");
						}
					}
				}
			}
			iSkipFlg = 0;
			//���ɖ߂�
			//if( pIraiW1 != NULL ) pIraiW = pIraiW1;
			memset(&pIraiW, 0, sizeof(Irai));
			memcpy(&pIraiW, (pIrai+k), sizeof(Irai));
			//�����˗���������
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�����˗���������");

			for( ; l < g_iJdkmk ;++l ) {
				if( !memcmp(pIraiW.knsgrp, (g_strJdkmk+l)->knsgrp, 16) &&
					!memcmp(pIraiW.kmkcd, (g_strJdkmk+l)->kmkcd, 7) &&
					(memcmp(pIraiW.sriymd, (g_strJdkmk+l)->kaiymd, 10) >= 0) )
					break;
			}

			if( l < g_iJdkmk ) {
				//�擾�˗��̒��Ɋ܂܂�Ă��邩���m�F
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�擾�˗��̒��Ɋ܂܂�Ă��邩���m�F");
	
				for( m=0; m < iIrai ;++m ) {
					if( !memcmp((pIrai+m)->kmkcd,  (g_strJdkmk+l)->jkmkcd, 7) ){
						//pIraiW1 = pIraiW;
						//pIraiW = pIrai+m;
						//�����ς݋L��������ꍇ�͏����X�L�b�v
						if( (pIrai+m)->odrssflg == 'F' ) {
							iSkipFlg = 2;
							break;
						}
/*
						if( iOdrMkFlg == 0 ) [
							(pIrai+m)->odrssflg = '2';
						] else [
							(pIrai+m)->odrssflg = '1';
						]
*/
						//���ɖ߂�
						memset(&strBunchuTB, 0, sizeof(Bunchu));
						memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));
						(pIrai+m)->odrssflg = pIraiW.odrssflg;
						strcpy((pIrai+m)->sriymd, strBunchuTB.sriymd);
						strcpy((pIrai+m)->knskisyymd, sWknsStart);
						memcpy((pIrai+m)->knsgrp, (g_strJdkmk+l)->jknsgrp, 16);

						memset(&pIraiW, 0, sizeof(Irai));
						memcpy(&pIraiW, (pIrai+m), sizeof(Irai));
						(pIrai+m)->odrssflg = 'F';	//�����������B
						memcpy(strBunchuTB.kmkcd, (g_strJdkmk+l)->jkmkcd, 7);
						iSkipFlg = 1;
						if( iFukuFlg == 1 ) {
							//�����{�D��x�m�F
							// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, pIraiW.knsgrp )) < 0 ) [
							/*DEBUG STA -----------------------------------------------*/
							sFncPutLog ( TRCKIND_DEBUG, __FILE__
								, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"chkBunchu IN �����˗��������� [%d][%s %s %s %s %s]", 
								iDBBunUpflg,
								strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
							/*DEBUG END -----------------------------------------------*/
							//YOON 2007-02-15
							if((iRet = chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
								pIraiW.knsgrp,iDBBunUpflg)) < 0 ) {
								sFncPutLog ( TRCKIND_DEBUG, __FILE__
                                	, "dBunchu_ins", __LINE__,
                                	EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                                	"chkBunchu IN �����G�[��");
								ZdbRollback();
								return( -1 );
							}
							if( iOdrMkFlg != 0 ) {
								if( pIraiW.odrssflg != '2' )
									pIraiW.odrssflg = '1';
								// CHG E.Osada 2006-08-30
								//if( iRet == 1 ) [
								if( iRet != 2 ) {
									iOdrMkFlg = 1;
								} else {
									//�����{���Ώۂ̏ꍇ�͕������ʂ�'1'���Z�b�g 2006-06-13 E.osada
									strBunchuTB.bnckka = '1';
									//�\�[�g�L�[�Čv�Z
									strBunchuTB.srtkey=AbunGetSort(pst_Env,strBunchuTB.id2, 
												strBunchuTB.bnckka);
									iOdrMkFlg = 3;
								}
							}
						}
						break;
					}
				}
/*
				if( iSkipFlg = 2 ) {
					iSkipFlg = 0;
					break;
				}
*/
				if( !iSkipFlg ) {
					//pIraiW1 = pIraiW;
					//���ɖ߂�
					memset(&strBunchuTB, 0, sizeof(Bunchu));
					memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));
					memcpy(strBunchuTB.kmkcd, (g_strJdkmk+l)->jkmkcd, 7);
					memcpy(pIraiW.kmkcd, (g_strJdkmk+l)->jkmkcd, 7);
					memcpy(pIraiW.oyakmkcd, (g_strJdkmk+l)->jkmkcd, 7);
					memcpy(pIraiW.knsgrp, (g_strJdkmk+l)->jknsgrp, 16);
					pIraiW.irihsmkbn = '2';
					pIraiW.srinycd = '2';
					pIraiW.bkfkkbn = '0';
					//��lNo�擾
					memset(sKjNo, 0, sizeof(sKjNo));
					iKetasu = 0;
					if( GetKjnNo(pIraiW.kmkcd, pIraiW.stsrcd,pKanjya->age,pKanjya->agekbn,
							pIraiW.sriymd, sKjNo, &iKetasu) == 1) {
						strcpy(pIraiW.kjno, sKjNo);
					}
					if( iFukuFlg == 1 ) {
						//�����{�D��x�m�F
						// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, pIraiW.knsgrp )) < 0 ) [
						/*DEBUG STA ---------------------------------------------------*/
						sFncPutLog ( TRCKIND_DEBUG, __FILE__
							, "dBunchu_ins", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"chkBunchu IN �˗��֘A [%d][%s %s %s %s %s]", 
							iDBBunUpflg,
							strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
						/*DEBUG END ---------------------------------------------------*/
						//YOON 2007-02-15
						if((iRet = chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
							pIraiW.knsgrp,iDBBunUpflg)) < 0 ) {
							sFncPutLog ( TRCKIND_DEBUG, __FILE__
                                    , "dBunchu_ins", __LINE__,
                                    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                                    "chkBunchu IN �����G�[��");
							ZdbRollback();
							return( -1 );
						}
						if( iOdrMkFlg != 0 ) {
							if( pIraiW.odrssflg != '2' )
								pIraiW.odrssflg = '1';
							// CHG E.Osada 2006-08-30
							//if( iRet == 1 ) [
							if( iRet != 2 ) {
								iOdrMkFlg = 1;
							
							} else {
								//�����{���Ώۂ̏ꍇ�͕������ʂ�'1'���Z�b�g 2006-06-13 E.osada
								strBunchuTB.bnckka = '1';
								//�\�[�g�L�[�Čv�Z
								strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, 
											strBunchuTB.bnckka);
								iOdrMkFlg = 3;
							}
						}
					}
					
					//�擾�˗��ɂȂ��ꍇ��INSERT����
					if( (ret = A105insIrai(&pIraiW)) < 0 ) {
						if( ret != -803 ) {
							//�G���[���O�o��
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, strBunchuTB.utkymd, 
							strIraiTB.kntno, strIraiTB.irino, buf2, "�����I�[�_�ǉ��G���[[%d]", ret);
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"INSERT IRAI[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						}
					}
					iSkipFlg = 1;
				} else if( iSkipFlg == 1 ) {
					//�˗��e�[�u���X�V
					if( (ret = ABunKnsgrpUpdate( &pIraiW )) < 0 ) {
						if( ret != -803 ) {
							//�G���[���O�o��
							sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
								strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino, 
								(pIrai+k)->kmkcd, "�˗����X�V�G���[[%d] KNSGRP[%s]", 
								ret, (pIrai+k)->knsgrp);
							ZdbRollback();
							if( pIrai != NULL ) {
								ZbmlFree(pIrai);
								pIrai = NULL;
							}
							if( pKanjya != NULL ) {
								ZbmlFree(pKanjya);
								pKanjya = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS START
							if( pIrai2 != NULL ) {
								ZbmlFree(pIrai2);
								pIrai2 = NULL;
							}
							// 2008-01-07 �V�t�����e�B�A�Ή� INS END
							sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"UPDATE IRAI[%s %s %s %s] [SQLCODE=%d]", 
								strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
								strBunchuTB.kmkcd, ret );
							return( 10 );
						}
					}
				}
				++l;
			}

			if( !iSkipFlg & !iOya ) {
				//�e�q�֌W�̏ꍇ�͐e���W�J����			
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�e�q�֌W�̏ꍇ�͐e���W�J���� iOdrMkFlg:%d",iOdrMkFlg);
				if( memcmp(pIraiW.kmkcd, pIraiW.oyakmkcd, 7) ) 
				{
					//�擾�˗��̒��Ɋ܂܂�Ă���e�����o��
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�擾�˗��̒��Ɋ܂܂�Ă���e�����o��");
				
					for( m=0; m < iIrai ;++m ) {
						if( !memcmp((pIrai+m)->kmkcd,  pIraiW.oyakmkcd, 7) ){
							//pIraiW1 = pIraiW;
							//pIraiW = pIrai+m;
							//memcpy(pIraiW->kmkcd, pIraiW1->oyakmkcd, 7);
							//memcpy(pIraiW->knsgrp, pIraiW1->knsgrp, 16);
							//�����ς݋L��������ꍇ�͏����X�L�b�v
							if( (pIrai+m)->odrssflg == 'F' ) {
								iSkipFlg = 0;
								break;
							}
							//���ɖ߂�
							memset(&strBunchuTB, 0, sizeof(Bunchu));
							memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));
							memcpy((pIrai+m)->knsgrp, sWknsgrp, 16);
							if( iOdrMkFlg == 0 ) {
								(pIrai+m)->odrssflg = '2';
							} else {
								(pIrai+m)->odrssflg = '1';
							}
							strcpy((pIrai+m)->knskisyymd, sWknsStart);
							memset(&pIraiW, 0, sizeof(Irai));
							memcpy(&pIraiW, (pIrai+m), sizeof(Irai));
							(pIrai+m)->odrssflg = 'F';	//�����������B
							memcpy(strBunchuTB.kmkcd, pIraiW.kmkcd, 7);
							iSkipFlg = 1;
							break;
						}
					}
					if( iSkipFlg == 1 ) {
						if( iFukuFlg == 1 ) {
							//�����{�D��x�m�F
							// 2.01 DELL if( (iRet = chkBunchu( pst_Env, iOdrMkFlg, &strBunchuTB, pIraiW.knsgrp )) < 0 ) [
							/*DEBUG STA ----------------------------------------------*/
							sFncPutLog ( TRCKIND_DEBUG, __FILE__
								, "dBunchu_ins", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
								"chkBunchu IN �e�q�֌W [%d][%s %s %s %s %s]", 
								iDBBunUpflg,
								strBunchuTB.sriymd, strBunchuTB.utkymd, 
								strIraiTB.kntno, strIraiTB.irino,(pIrai+k)->kmkcd );
							/*DEBUG END ----------------------------------------------*/
							//YOON 2007-02-15
							if((iRet=chkBunchu(pst_Env,iOdrMkFlg,&strBunchuTB, 
								pIraiW.knsgrp,iDBBunUpflg)) < 0 ) {
								sFncPutLog ( TRCKIND_DEBUG, __FILE__
                                    , "dBunchu_ins", __LINE__,
                                    EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                                    "chkBunchu IN �����G���[");							
	
								ZdbRollback();
								return( -1 );
							}
							if( iOdrMkFlg != 0 ) {
								if( pIraiW.odrssflg != '2' )
									pIraiW.odrssflg = '1';
								// CHG E.Osada 2006-08-30
								//if( iRet == 1 ) [
								if( iRet != 2 ) {
									iOdrMkFlg = 1;
								} else {
									//�����{���Ώۂ̏ꍇ�͕������ʂ�'1'���Z�b�g 2006-06-13 E.osada
									strBunchuTB.bnckka = '1';
									//�\�[�g�L�[�Čv�Z
									strBunchuTB.srtkey = AbunGetSort(pst_Env, strBunchuTB.id2, 
												strBunchuTB.bnckka);
									iOdrMkFlg = 3;
								}
							}
						}
						//�˗��e�[�u���X�V
						if( (ret = ABunKnsgrpUpdate( &pIraiW )) < 0 ) {
							if( ret != -803 ) {
								//�G���[���O�o��
								sFuncPutErrlist(pst_Env, sFLname, iFLcnt, strBunchuTB.sriymd, 
									strBunchuTB.utkymd, strIraiTB.kntno, strIraiTB.irino, 
									pIraiW.kmkcd, "�˗����X�V�G���[[%d] KNSGRP[%s]", 
									ret, pIraiW.knsgrp);
								ZdbRollback();
								if( pIrai != NULL ) {
									ZbmlFree(pIrai);
									pIrai = NULL;
								}
								if( pKanjya != NULL ) {
									ZbmlFree(pKanjya);
									pKanjya = NULL;
								}
								// 2008-01-07 �V�t�����e�B�A�Ή� INS START
								if( pIrai2 != NULL ) {
									ZbmlFree(pIrai2);
									pIrai2 = NULL;
								}
								// 2008-01-07 �V�t�����e�B�A�Ή� INS END
								sFncPutLog(TRCKIND_WARNING,__FILE__,"dBunchu_ins",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
									"UPDATE IRAI[%s %s %s %s] [SQLCODE=%d]", 
									strBunchuTB.sriymd,strBunchuTB.kntno,strBunchuTB.smpcd, 
									strBunchuTB.kmkcd, ret );
								return( 10 );
							}
						}
					}
				}
			}
			if( !iSkipFlg )
			{
				break;
			}
		}
		//�R�~�b�g ���\UP�̂��ߎ��s 2006-06-22 E.Osada
//		ZdbCommit();
//		 sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//                "COMMIT");
		//�����ς݋L��������B
		(pIrai+k)->odrssflg = 'F';

	}
	//���ɖ߂�
	memset(&strBunchuTB, 0, sizeof(Bunchu));
	memcpy(&strBunchuTB, &pBunW, sizeof(Bunchu));

	//���̑������쐬
	// 3.02 UPD ���O�Ή�-803�̔����AbunInsZokusei�ɂčs��
	//if( (ret = AbunInsZokusei(pst_Env, &strBunchuTB, pKanjya)) < 0 ) [
	if( (ret = AbunInsZokusei(pst_Env, &strBunchuTB, pKanjya, iDupFlg )) < 0 ) {
		if( ret != -803 ) {
			sFuncPutErrlist(pst_Env,sFLname,iFLcnt,strBunchuTB.sriymd, strBunchuTB.utkymd, 
				strIraiTB.kntno, strIraiTB.irino, buf2, "���̑������ǉ��G���[[%d]", ret);
			ZdbRollback();
			if( pIrai != NULL ) {
				ZbmlFree(pIrai);
				pIrai = NULL;
			}
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			// 2008-01-07 �V�t�����e�B�A�Ή� INS START
			if( pIrai2 != NULL ) {
				ZbmlFree(pIrai2);
				pIrai2 = NULL;
			}
			// 2008-01-07 �V�t�����e�B�A�Ή� INS END
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"INSERT KENZOK[%s %s %s %s] [SQLCODE=%d]", 
				strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
				strBunchuTB.kmkcd, ret );
			return( 10 );
		}
	}

	//�F�����쐬
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"�F�����쐬 ����(1)�Ɠ���(%d)�Ȃ�iOdrMkFlg��(2)�ɃZ�b�g",iFukuFlg);
	iOldFlg = iOdrMkFlg;
	if( iFukuFlg == 1 ){	
 
		iOdrMkFlg = 2;
	}
	// 3.02 UPD ���O�Ή�-803�̔����AbunInsZokusei�ɂčs��
	//if( (ret = AbunInsNinsiki(pst_Env, &strBunchuTB, iOdrMkFlg)) < 0 ) [
	if( (ret = AbunInsNinsiki(pst_Env, &strBunchuTB, iOdrMkFlg, iDupFlg )) < 0 ) {
		if( ret != -803 ) {
			sFuncPutErrlist(pst_Env, sFLname,iFLcnt,strBunchuTB.sriymd, strBunchuTB.utkymd, 
				strIraiTB.kntno, strIraiTB.irino, buf2, "�F�����ǉ��G���[[%d]", ret);
			ZdbRollback();
			if( pIrai != NULL ) {
				ZbmlFree(pIrai);
				pIrai = NULL;
			}
			if( pKanjya != NULL ) {
				ZbmlFree(pKanjya);
				pKanjya = NULL;
			}
			// 2008-01-07 �V�t�����e�B�A�Ή� INS START
			if( pIrai2 != NULL ) {
				ZbmlFree(pIrai2);
				pIrai2 = NULL;
			}
			// 2008-01-07 �V�t�����e�B�A�Ή� INS END
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"INSERT NINSIKI[%s %s %s %s] [SQLCODE=%d]", 
				strBunchuTB.sriymd, strBunchuTB.kntno, strBunchuTB.smpcd, 
				strBunchuTB.kmkcd, ret );
			return( 10 );
		}
	}

	iOdrMkFlg = iOldFlg;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"iOdrMkFlg(%d)==0�Ȃ�g���[�����b�N���ҏW����",iOdrMkFlg);

//	if( !iOdrMkFlg ) 
// Upd 2007.05.10 waj
//	if( sakitukeFileFlg) 
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//	if( (!iOdrMkFlg) && (iBgroupFlg == 0) )
//	{	//�����G���[�̏ꍇ�̓I�[�_�쐬���Ȃ�
//		//�g���[�����b�N���ҏW����(�����@�ւ̐�t����񑗐M�p)
//		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
//			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			"�g���[�����b�N���ҏW����(�����@�ւ̐�t����񑗐M�p");
//		if( *strKenPos != NULL ) {
//			for( i=0; i < *iKenPos ;++i ) {
//				if( !strcmp((*strKenPos+i)->sTryID, strBunchuTB.trid) ) {
//					ialloc = 1;
//					iPoint = i;
//					pTray = *strKenPos;
//					break;
//				}
//				if( ialloc == 1 ) break;
//			}
//		}
//		if( ialloc == 0 ) {
//			//*strKenPos = (TRAY *)ZbmlRealloc((TRAY *)*strKenPos, sizeof(TRAY) * (*iKenPos + 1));
//			*strKenPos = (TRAY *)realloc((TRAY *)*strKenPos, sizeof(TRAY) * (*iKenPos + 1));
//			*iKenPos += 1;
//			iPoint = *iKenPos - 1;
//			pTray = *strKenPos;
//			memset((pTray+iPoint), 0, sizeof(TRAY));
//			strcpy((pTray+iPoint)->sTryID, strBunchuTB.trid);
//			ZbmlChgAPDate((pTray+iPoint)->sStDate, strBunchuTB.sriymd);
//			// Upd 2007.05.10 waj
//			// strcpy((pTray+iPoint)->sPutDir, pst_Env->sPutDir);
//			{ // �����Ő�t���t�@�C���i�[�f�B���N�g�����g���C��񂩂�擾���ݒ肷��
//			    Trmst   strTr,  *pTr = NULL;
//				int		num = 0;
//
//			    memset(&strTr, 0, sizeof(Trmst));
//			    memcpy(strTr.trhdid, strBunchuTB.trid, 4);
//			    strcpy(strTr.kaiymd,  strBunchuTB.sriymd);
//			    if( ret = A105trmstSelectKey(&strTr, &pTr, &num) != 0 ) {
//			        sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
//			            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//			            "SELECT Trmst[SQLCODE=%d]", ret ) ;
//			        return( -1 );
//			    }
//        		strcpy(pst_Env->sPutDir, pTr->filskdir);
//				strcpy((pTray+iPoint)->sPutDir, pst_Env->sPutDir);
//		        ZbmlFree(pTr);
//		        pTr = NULL;
//			}
//			strcpy((pTray+iPoint)->sPutDir, pst_Env->sPutDir);
//			(pTray+iPoint)->iMaxSeq = 0;
//			(pTray+iPoint)->iMinSeq = 99999;
//			(pTray+iPoint)->iKntSuu = 0;
//			for ( i=0; i < MAXPOSOLD+1 ;++i ) {
//				memset( (pTray+iPoint)->strPosInfo[i].sUkeDate, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sUkeDate)-1);
//				memset( (pTray+iPoint)->strPosInfo[i].sKentaiID, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sKentaiID)-1);
//				memset( (pTray+iPoint)->strPosInfo[i].sIraiNo, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sIraiNo)-1);
//				memset( (pTray+iPoint)->strPosInfo[i].sKenSybt, ' ', 
//						sizeof((pTray+iPoint)->strPosInfo[i].sKenSybt)-1);
//			}
//		}
//		(pTray+iPoint)->iKntSuu += 1;
//		if( (pTray+iPoint)->iMaxSeq <= pOrder.knsseq )
//			(pTray+iPoint)->iMaxSeq = pOrder.knsseq;
//		if( (pTray+iPoint)->iMinSeq >= pOrder.knsseq )
//			(pTray+iPoint)->iMinSeq = pOrder.knsseq;
//		ZbmlStrCpy((pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sUkeDate, 
//			pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
//		ZbmlStrCpy((pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKentaiID, strBunchuTB.kntno, sizeof(strBunchuTB.kntno)-1);
//		ZbmlStrCpy((pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sIraiNo, strIraiTB.irino, sizeof(strIraiTB.irino)-1);
//		(pTray+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKenSybt[0] = pBunchu->sKnsSyrui[0];
//	}
	if( (!iOdrMkFlg) && (iBgroupFlg == 0) )
	{	//�����G���[�̏ꍇ�̓I�[�_�쐬���Ȃ�
		//�g���[�����b�N���ҏW����(�����@�ւ̐�t����񑗐M�p)
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�g���[�����b�N���ҏW����(�����@�ւ̐�t����񑗐M�p)");
		if( *strKenPos != NULL ) {
			for( i=0; i < *iKenPos ;++i ) {
				if( !strcmp((*strKenPos+i)->sRackID, strBunchuTB.asyrckid) ) {
					ialloc = 1;
					iPoint = i;
					pRack = *strKenPos;
					break;
				}
				if( ialloc == 1 ) break;
			}
		}
		if( ialloc == 0 ) {
			*strKenPos = (RACK *)realloc((RACK *)*strKenPos, sizeof(RACK) * (*iKenPos + 1));
			*iKenPos += 1;
			iPoint = *iKenPos - 1;
			pRack = *strKenPos;
			memset((pRack+iPoint), 0, sizeof(RACK));
			strcpy((pRack+iPoint)->sRackID, strBunchuTB.asyrckid);
			ZbmlChgAPDate((pRack+iPoint)->sStDate, strBunchuTB.sriymd);
			{ // �����Ő�t���t�@�C���i�[�f�B���N�g�������b�N�Ǘ��}�X�^����擾���ݒ肷��
			    Rkmst   strRk,  *pRk = NULL;
				int		num = 0;

				memset(&strRk, 0, sizeof(Rkmst));
				memcpy(strRk.smpcd, strBunchuTB.smpcd, 4);
				strcpy(strRk.kaiymd,  strBunchuTB.sriymd);
				if( ret = A105rkmstSelectKey(&strRk, &pRk, &num) != 0 ) {
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"SELECT Rkmst[SQLCODE=%d]", ret ) ;
					return( -1 );
			    }
				strcpy(pst_Env->sPutDir, pRk->filskdir);
				strcpy((pRack+iPoint)->sPutDir, pst_Env->sPutDir);
				ZbmlFree(pRk);
				pRk = NULL;
			}
			strcpy((pRack+iPoint)->sPutDir, pst_Env->sPutDir);
			(pRack+iPoint)->iMaxSeq = 0;
			(pRack+iPoint)->iMinSeq = 99999;
			(pRack+iPoint)->iKntSuu = 0;
			for ( i=0; i < MAXPOS+1 ;++i ) {
				memset( (pRack+iPoint)->strPosInfo[i].sUkeDate, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sUkeDate)-1);
				memset( (pRack+iPoint)->strPosInfo[i].sKentaiID, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sKentaiID)-1);
				memset( (pRack+iPoint)->strPosInfo[i].sIraiNo, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sIraiNo)-1);
				memset( (pRack+iPoint)->strPosInfo[i].sKenSybt, ' ', 
						sizeof((pRack+iPoint)->strPosInfo[i].sKenSybt)-1);
			}
		}
		(pRack+iPoint)->iKntSuu += 1;
		if( (pRack+iPoint)->iMaxSeq <= pOrder.knsseq )
			(pRack+iPoint)->iMaxSeq = pOrder.knsseq;
		if( (pRack+iPoint)->iMinSeq >= pOrder.knsseq )
			(pRack+iPoint)->iMinSeq = pOrder.knsseq;
		ZbmlStrCpy((pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sUkeDate, 
			pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
		ZbmlStrCpy((pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKentaiID, strBunchuTB.kntno, sizeof(strBunchuTB.kntno)-1);
		ZbmlStrCpy((pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sIraiNo, strIraiTB.irino, sizeof(strIraiTB.irino)-1);
		(pRack+iPoint)->strPosInfo[strBunchuTB.asyrckpos].sKenSybt[0] = pBunchu->sKnsSyrui[0];
	}
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	//�R�~�b�g
	ZdbCommit();
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"TRANSACTION COMMIT");

	// ADD E.Osada 2006-09-16
	if( pIrai != NULL ) {
		ZbmlFree(pIrai);
		pIrai = NULL;
	}
	if( pKanjya != NULL ) {
		ZbmlFree(pKanjya);
		pKanjya = NULL;
	}
// 2008-01-07 �V�t�����e�B�A�Ή� INS START
	if( pIrai2 != NULL ) {
		ZbmlFree(pIrai2);
		pIrai2 = NULL;
	}
// 2008-01-07 �V�t�����e�B�A�Ή� INS END
	//
	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	//fclose(fp);

	return(0);
}
/******************************************************************************/
/*  �� �� ���@�FsFncTrFileRead()			 								  */
/*  �@�\�T�v�@�F�������ʏ��Ǎ�							  	 			  */
/*	���L����  �F��Q������free												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct bunchuEnv *   	�v���O�������\����		 	      */
/*�@ ��Q���� �Fchar *  	 			�������ʏ��t�@�C����	 			  */
/*�@ ��R���� �FFlbun *  	 			�������ʏ����i�[�\����			  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static	int
sFncTrFileRead ( pst_Env, pc_trFileName, pst_trInfo )
struct bunchuEnv	*pst_Env ;
char				*pc_trFileName ;
Flbun  		*pst_trInfo ;
{
	FILE	*lfp ;
	char	 lc_recBuf[BUNCHU_RECV_RECSIZE+1] ;
	char	sTrFileName[1024];
	char	*lpc_p ;
	char	 lcbuf[256] ;
	int		 li_idx, iRet, i, ilen, iRecCnt;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//	TRAY *strKenPos;
	RACK *strKenPos;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	int		iKenPos;
	int 	iLine;
	char	sDttm[128];

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function filename=%s", pc_trFileName);

	// 2008-02-18 �t�@�C���̃N���[�Y�������Ă��Ȃ��ӏ��������������̂Œǉ�

	//	�t�@�C���I�[�v��	
	lfp  = fopen ( pc_trFileName, "r" ) ;
	if ( lfp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_FR_FILE ;
		return ( -1 ) ;
	}

	memset(sTrFileName, 0, sizeof(sTrFileName));
	ilen = strlen(pc_trFileName);
	for( i=ilen; i >= 0 ;--i ) {
		if( pc_trFileName[i] == '/' ) {
			++i;
			memcpy(sTrFileName, &pc_trFileName[i], ilen - i);
			break;
		}
	}
	strKenPos = NULL;
	iKenPos = iLine = 0;
	memset(lc_recBuf, 0, BUNCHU_FILE_SIZE);

	memset(sDttm, 0, sizeof(sDttm));
	nowdateget1( sDttm );
   	sFncPutLog ( TRCKIND_OPT, "", "", 0,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "    START(%s) �y%s�z", sDttm, sTrFileName);
	iRecCnt = 0;
	//	�ǂݍ���
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		iLine++;
		if((iRet=dBunchu_ins(pst_Env,lc_recBuf,&strKenPos,&iKenPos,sTrFileName,iLine))<0){
			//2006-12-14 YOON
			AerrFilePut4( pst_Env,lc_recBuf,sTrFileName);
			if ( lfp != NULL ) {
				//	�t�@�C���N���[�Y
				fclose ( lfp ) ;
			}
			return(iRet);
		}

		if( iRet == 10 ) {
			if( AerrFilePut1(pst_Env, lc_recBuf) < 0 ) {
				if ( lfp != NULL ) {
					//	�t�@�C���N���[�Y	
					fclose ( lfp ) ;
				}
				return( -1 );
			}
		} else if( iRet == 11 ) {
			if( AerrFilePut2(pst_Env, lc_recBuf) < 0 ) {
				if ( lfp != NULL ) {
					//	�t�@�C���N���[�Y	
					fclose ( lfp ) ;
				}
				return( -1 );
			}
		} else if( iRet == 8 ) {
			if( AerrFilePut3(pst_Env, lc_recBuf) < 0 ) {
				if ( lfp != NULL ) {
					//	�t�@�C���N���[�Y	
					fclose ( lfp ) ;
				}
				return( -1 );
			}
		} else {
			if( iRet ) {
				if( AerrFilePut(pst_Env, lc_recBuf) < 0 ) {
					if ( lfp != NULL ) {
						//	�t�@�C���N���[�Y	
						fclose ( lfp ) ;
					}
					return( -1 );
				}
			}
		}
		++iRecCnt;
		memset(lc_recBuf, 0, BUNCHU_FILE_SIZE+1);
	}
	memset(sDttm, 0, sizeof(sDttm));
	nowdateget1( sDttm );
   	sFncPutLog ( TRCKIND_OPT, __FILE__, "", __LINE__,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "    END(%s)   �y%s RECORD No %d �z", sDttm, sTrFileName, iRecCnt);

	if( iKenPos == 0 ){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "iKenPos��0�Ɠ����ł��̂�0��Ԃ��܂��B");

		if ( lfp != NULL ) {
			//	�t�@�C���N���[�Y	
			fclose ( lfp ) ;
		}

		return( 0 );
	}
	
	//�g���[No�t�@�C���쐬(�ߓn��)
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
         "�g���[No�t�@�C���쐬(�ߓn��)");
	if( dBunCrTryfile(pst_Env, strKenPos, iKenPos) < 0 ) {
		//�G���[���O�o��
	}
	ZbmlFree(strKenPos);

	//	�t�@�C���N���[�Y	
	fclose ( lfp ) ;

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stockerEnv *   	�v���O�������\����		 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static	char*
sFncTrFileToken ( pString, pBuf )
char	*pString ;
char	*pBuf ;
{
	char	*p ;
	int		 liLen ;
	int		 liIdx ;

	*pBuf = '\0' ;
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		p = pString ;	
	}
//loging ( "%s\n", p ) ;
/***
	if ( ( liLen = strlen ( p ) ) <= 0 ) {
		return ( NULL ) ;
	}
***/
	if (  *p == '\0' || *p == '\n' || *p == '\r' ) {
		return ( NULL ) ;
	}

	liIdx = 0 ;	
	while ( 1 ) {
	//fprintf ( stderr, "%c\n", *(p+liIdx) ) ;
		if ( *(p+liIdx) == ','  || 
			 *(p+liIdx) == '\0' || 
			 *(p+liIdx) == '\n' || 
			 *(p+liIdx) == '\r'  ) {
			break ;
		}	
		liIdx ++ ;
	}
	if ( liIdx > 0 ) {
		memset ( pBuf, '\0', liIdx + 1 ) ;
		memcpy ( pBuf, p, liIdx ) ;
	}
	if ( *(p+liIdx) == ',' ) {
		gpToken =  p + liIdx + 1 ;
	} 
	else {
		gpToken =  p + liIdx ;
	}
	return ( gpToken ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stockerEnv *   	�v���O�������\����		 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmCrt ( pEnv )
struct bunchuEnv	*pEnv ;
{
	int		*shmData ;

	//	�擾
	pEnv->shm_Id = shmget ( (key_t)pEnv->shm_Key, 
							BUNCHU_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pEnv->shm_Id < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_GET ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_AT ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_DT ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stockerEnv *   	�v���O�������\���́B		 	      */
/*�@ ��Q���� �Fint *   				�l							 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmGet ( pEnv, pshmData )
struct bunchuEnv	*pEnv ;
int					*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pEnv->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_AT ;
		return ( -1 ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

loging ( "stocker : ���L������[GET] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData ) ;
	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_DT ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stockerEnv *   	�v���O�������\���́B		 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmDel ( pEnv )
struct bunchuEnv	*pEnv ;
{
	int		*shmData ;

loging ( "bunchu : ���L������[DEL] shmKey[%d]-ID[%d]\n", pEnv->shm_Key, pEnv->shm_Id) ;
	//	�폜	
	if ( shmctl ( pEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = BUNCHU_STSCODE_ERR_SHM_DEL ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  �� �� ���@�FsFncFileFillter()			 								  */
/*  �@�\�T�v�@�F�t�@�C���t�B���^�[�y�R�[���o�b�N�֐��z		  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct dirent *   	�f�B���N�g���\����				 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	�ΏۊO�t�@�C��										  */
/*					 1	�Ώۃt�@�C��										  */
/******************************************************************************/
static	int
sFncFileFillter ( pdirEnt ) 
struct dirent *pdirEnt ;
{
		int		li_len ;

		//�����񒷃`�F�b�N
		li_len = strlen ( pdirEnt->d_name )  ;
		if ( li_len  < 5 ) {
			return ( 0 ) ;
		}

/*
		//���ʃ`�F�b�N
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND, 
					  strlen ( BUNCHU_RECV_KIND ) ) != 0 ) {
			return ( 0 ) ;
		}
*/
		//�g���q�`�F�b�N
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(BUNCHU_RECV_SFX)]), 
					  BUNCHU_RECV_SFX, 
					  strlen ( BUNCHU_RECV_SFX ) ) != 0 ) {
			return ( 0 ) ;
		}

		return ( 1 ) ;
}

/******************************************************************************/
/*  �� �� ���@�F_sFncEnvDip()				 								  */
/*  �@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z	  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stockerEnv *   	�v���O�������\���́B		 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static void
_sFncEnvDip( pEnv )
struct bunchuEnv	*pEnv ;
{
#if defined ( _TRACE )
	loging ( "########## Bunchu - _sFncEnvDip ##########\n" ) ;
	loging ( "\t�y���L�f�B���N�g���z\n" ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_DIR_BUNCHU,		pEnv->cDirBunchu ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_DIR_LOG,			pEnv->cDirLog ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_DBG,		pEnv->cDebugLogName ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_TR,		pEnv->cTraceLogName ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_ACS,		pEnv->cAccessLogName ) ;
	loging ( "\t%s : [%s]\n", BUNCHU_PRM_FILE_ERR,		pEnv->cErrorLogName ) ;
	loging ( "\t%s : [%d]\n", BUNCHU_PRM_SHM_KEY,        pEnv->shm_Key ) ;
	loging ( "\t%s : [%d]\n", BUNCHU_PRM_SLEEP_SEC,      pEnv->sleep_Sec ) ;
	loging ( "########## Bunchu - _sFncEnvDip ##########\n" ) ;
#endif
}
/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()                                                  */
/*  �@�\�T�v�@�F�A�v���P�[�V�������O�o��                                      */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *      �ҏW������                                        */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
/******************************************************************************/
void
sFncPutLog( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... )
{
    va_list  ap ;
    char     cMsg[1024] ;

    /***
     ***    ���O�����l�ݒ�
     ***/
    gstLogMem.eTrcKind = peTrcKind ;
    //strcpy ( gstLogMem.pcSrcName, pcSrcName ) ;
    strcpy ( gstLogMem.pcFncName, pcFncName ) ;
    //gstLogMem.lLineNo = plLineNo ;
    strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
    strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
    va_start ( ap, pcfmt ) ;
    vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
    va_end ( ap ) ;

    /***
     ***    ���O�o��
     ***/

#ifdef _DEBUG_
	printf("%d,%s\n",plLineNo,gstLogMem.pcMsg);
#endif

    _ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
    return ;

}
void
sFuncPutErrlist( struct bunchuEnv *pEnv, char *sFile, int iLine, char *sSyriymd, char *sUkeymd,
				char *sKntno, char *sIrino, char *sKomoku, char *pcfmt, ... )
{
	va_list	ap;
	char	pcMsg[512];
	FILE	*fp;
	char	sListFile[1024], sysdate[128], systime[128];

	memset(sListFile, 0, sizeof(sListFile));
	memset(sysdate, 0, sizeof(sysdate));
	memset(systime, 0, sizeof(systime));
	nowdateget( sysdate, systime );
	sprintf(sListFile, "%s/%s%s.log", pEnv->cDirLog, MYAPP_APP_NAME, sysdate);

	if( (fp = fopen(sListFile, "a") ) == NULL ) {
		fprintf(stderr, "�G���[���X�g: fopen(\"%s\") �G���[ %d %s\n", sListFile, errno);
		return;
	}

	memset(pcMsg, 0, sizeof(pcMsg));
	va_start(ap, pcfmt);
	vsprintf(pcMsg, pcfmt, ap);
	va_end(ap);

	fprintf(fp, "%s!%s!%d!%s!%s!%s!%s!%s!%s\n",
		SYBT_BUNCH, sFile, iLine, sSyriymd, sUkeymd, sKntno, sIrino, sKomoku, pcMsg );

	fclose(fp);

	return;
}
/******************************************************************************/
/*  �� �� ���@�FsFncChkDigit()												  */
/*  �@�\�T�v�@�F�����̃��b�NID���l�`�F�b�N�֐�								  */
/*  ���@�@�́@�F															  */
/*�@ ��P���� �Fchar * 		�`�F�b�N������									  */
/*  �o�@�@�́@�F															  */
/*  ���A���@�Fint															  */
/*					0		�I�[�����l										  */
/*					0�ȊO	���l�ȊO���������Ă���							  */
/******************************************************************************/
int
sFncChkDigit( pChkStr )
char	*pChkStr ;
{
	
	int		i, err ;
	char	cMotoRackId[11];

	// �ϐ�������
	err = 0 ;
	memset( cMotoRackId, 0, sizeof(cMotoRackId) );

	// �s�v�ȃX�y�[�X������
	ZbmlInfocpy( cMotoRackId, pChkStr, sizeof(cMotoRackId) );

	// ���l���ǂ����`�F�b�N
	for (i = 0; i < strlen(cMotoRackId); i++)
	{
		//���l�Ŗ����ꍇ
		if (cMotoRackId[i] < '0' || cMotoRackId[i] > '9')
		{
			err++ ;
		}
	}

	// �S�Đ��l�̏ꍇ�Aerr��'0'��Ԃ�
	// 1�ł����l�ȊO�̕���������ꍇ�Aerr�͂��̕�������Ԃ�
	return ( err ) ;

}
/********************************************************************/
/*	�֐���		�Fmain()											*/
/*	�@�\�T�v	�F�������W�J�������C��							*/
/* 	����		�F													*/
/*	 ��P����   �Fint	argc		�p�����[�^��					*/
/*	 ��Q����	�Fchar	*argv[]		�p�����[�^�l					*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F1�ȏ�													*/
/********************************************************************/
int 
main( argc, argv )
int		 argc ;
char	*argv[] ;
{

	struct bunchuEnv	 sEnv ;

	/***
	 ***	�o�b�N�O���E���h����
	 ***/
	if( daemon( 0, 1 ) < 0 ) {
		fprintf ( stderr, "bunchu : Error daemon() [%d]\n", errno );
		exit( 9 );
	}

	/***
	 ***	��������	
	 ***/
	if ( initFunction ( argc, argv, &sEnv )  != 0 ) {
		fprintf ( stderr, "bunchu : Error initFunction [%d]\n", gintErrorCode ) ;
		exit ( 9 ) ;
	}
	_sFncEnvDip ( &sEnv ) ;
	
	/***
	 ***	�又��	
	 ***/
	if ( mainFunction ( &sEnv )  != 0 ) {
		fprintf ( stderr, "bunchu : Error mainFunction [%d]\n", gintErrorCode ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������	
	 ***/
	endFunction ( &sEnv ) ;
}

/** End of File ***************************************************************/
