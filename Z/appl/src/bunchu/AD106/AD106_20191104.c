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
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include "AD106.h"

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

	int				  li_fileCnt, iLen ;
	char			  lc_fileName[1024] ;
	char			  buf[1024] ;
	struct stat		  lst_statBuf ;
	char	sFileOK[1024], sFileNG[1024];
	char	sDttm[128];

	int		iSeqCnt, iSeqCnt1;
	Flbun	  lst_trInfo ;
	int		iRet;

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "mainFunction", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function");

    //if( ret = ZdbConnect( "labokns", "nxtgene", "nxtgene" ) ) {
    if( ret = ZdbConnect( pEnv->sDbName, pEnv->sDbUser, pEnv->sDbPswd ) ) {
        printf("DB connect error (%d)", ret);
        return( -1 );
    }

	G_ic = iconv_open( "EUC-JP", "SHIFT-JIS" );

	/***
	 ***	�������f�B���N�g���Ď�	
	 ***		�i�v���[�v
	 ***		��~�R�}���h�ŏI��
	 ***/
	iSeqCnt = 0;
	iSeqCnt1 = 0;
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
		while ( li_idx < li_fileCnt ) {
			sprintf ( lc_fileName, "%s/%s", pEnv->cDirBunchu, lpst_dirBuf[li_idx]->d_name ) ;

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
			if( iSeqCnt == 9999 ) iSeqCnt = 0;
			if ( S_ISREG ( lst_statBuf.st_mode ) ) {
				if ( (iRet = sFncTrFileRead ( pEnv, lc_fileName, &lst_trInfo, &iSeqCnt, &iSeqCnt1 )) < 0 ) {
					sprintf(sFileOK, "%s/%s", pEnv->cDirBunchuOK, lpst_dirBuf[li_idx]->d_name);
				} else {
					sprintf(sFileOK, "%s/%s", pEnv->cDirBunchuOK, lpst_dirBuf[li_idx]->d_name);
				}
				//	���
				free ( lpst_dirBuf[li_idx] ) ;
				// �t�@�C���ړ�
				if( memcmp(lpst_dirBuf[li_idx]->d_name, "CHK", 3) ) {
					if( rename( lc_fileName, sFileOK) < 0 ) {
						printf("rename error %s -> %s\n", lc_fileName, sFileOK);
						return( -1 );
					}
				} else if( iRet == 0) {
					sprintf(sFileOK, "%s/%s", pEnv->cDirTryinfo, lpst_dirBuf[li_idx]->d_name);
					if( rename( lc_fileName, sFileOK) < 0 ) {
						printf("rename error %s -> %s\n", lc_fileName, sFileOK);
						return( -1 );
					}
					memset(buf, 0, sizeof(buf));
					iLen = strlen(sFileOK) - 3;
					strcpy(buf, sFileOK);
					memcpy(&buf[iLen], "dat", 3);
					if( rename( sFileOK, buf) < 0 ) {
						printf("rename error %s -> %s\n", lc_fileName, sFileOK);
						return( -1 );
					}
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

		if ( li_stopFlg == 1 ) {
			break ;
		} else {
			if ( sFncShmGet ( pEnv, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				break ;
			}
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
void
nowdateget( char *sysdate, char *systime )
{
        struct tm       *newtime ;
        long    ltime ;

        time( &ltime) ;
        newtime = localtime( &ltime ) ;
        sprintf( sysdate, "%04d%02d%02d", newtime->tm_year+1900,
                                newtime->tm_mon+1, newtime->tm_mday ) ;
        sprintf( systime, "%02d%02d%02d", newtime->tm_hour,
                                newtime->tm_min, newtime->tm_sec ) ;

        return ;
}
void
nowdateget1( char *sysdate )
{
        struct tm       *newtime ;
        long    ltime ;

        time( &ltime) ;
        newtime = localtime( &ltime ) ;
        sprintf( sysdate, "%04d-%02d-%02d %02d:%02d:%02d",
                          newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday,
                          newtime->tm_hour, newtime->tm_min, newtime->tm_sec ) ;
        return ;
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
TRAY **strKenPos;
int		*iKenPos;
char	*sFLname;
int		iFLcnt;
{
	FILE	*fp;
	Flbun *pBunchu;			//�������ʏ��t�@�C���\����
	Kanjya	strKanjyaTB;	//���ҏ��e�[�u��KEY�\����
	Kanjya	*pKanjya = NULL;		//���ҏ��e�[�u���i�[�\����
	Irai	strIraiTB;		//�˗����e�[�u��KEY�\����
	Irai	*pIrai = NULL;			//�˗����e�[�u���i�[�\����
	char	buf[1024], buf1[1024], buf2[128];		//���[�N
	BmlDate	today;
	char	sDay[20], sysdate[128], systime[128];
	char	*pKmkCd, *pKmkCd1;
	int		i, num, iIrai, j, iOrder, cnt, iHit;
	long	ret;
	char	sWknsgrp[17];
	char ialloc, iPoint;
	int		iWs, iEda;
	int		iSkipFlg;
	char	sWork[10];
	char	sWork1[10];
	int		iJidoFlg;
	int 	iOldFlg;
	char	sKjNo[10];
	int		iOya;
	int		iOdrMkFlg;

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
		return( -1 );
	}

	//�����t�@�C�����ʎq�`�F�b�N(�w�b�_�[���R�[�h)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_HED, 2) ) {
		//�g���[�X���O
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(�w�b�_�[���R�[�h)");
		return( 1 );
	}
	//�����t�@�C�����ʎq�`�F�b�N(�I�����R�[�h)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_STP, 2) ) {
		//�g���[�X���O
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(�I�����R�[�h)");
		return( 1 );
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
		return( -1 );
	}
	
	//�����t�@�C�����ʎq�`�F�b�N(����END)
	if( !memcmp(pBunchu->sDataSybt, BUNCHU_SYBT_END, 2) ) {

		//�g���[�X���O
    	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function(����END)");
		return( 1 );
	}

		//�g���[ID���X�y�[�X�̏ꍇ�͖������ɕ����W�J�����ɂ܂킷
	if( !memcmp(pBunchu->sRackId, "        ", sizeof(pBunchu->sRackId)) ) {
		return( 2 );
	}
	iSkipFlg = ialloc = 0;

	memset(&strIraiTB, 0, sizeof(Irai));
	memset(&strKanjyaTB, 0, sizeof(Kanjya));
	//BML��t�N���� YYYYMMDD �� YYYY-MM-DD�ɕϊ�
	memcpy(buf, pBunchu->sUkebiBML, sizeof(pBunchu->sUkebiBML));
	sprintf(buf1, "%4.4s-%2.2s-%2.2s", buf, &buf[4],&buf[6]);
	strcpy(strIraiTB.utkymd, buf1);
	strcpy(strKanjyaTB.utkymd, buf1);
	//�˗���No
	if( pst_Env->proc_mode ) {
		//������
		memcpy(strIraiTB.irino, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
		memcpy(strKanjyaTB.irino, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
	} else {
		//�ߓn��
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		memcpy(buf, pBunchu->sIraiNo, sizeof(pBunchu->sIraiNo));
		sprintf(buf1,"00%-3.3s%-6.6s", &buf[0], &buf[5]);
		strcpy(strIraiTB.irino, buf1);
		strcpy(strKanjyaTB.irino, buf1);
	}

	//���ҏ��m�F
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
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", strKanjyaTB.utkymd, 
			"", strIraiTB.irino, "", "���ҏ�񖳂�");
		return 2;
	}
	
	//��������No�擾
	strIraiTB.zssdino = pKanjya->zssdino;

	//�˗����e�[�u���擾
	strcpy(strIraiTB.kmkcd, buf2);
	if( (ret = ABunIriSel(&strIraiTB, &pIrai, &iIrai)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"SELECT IRAI[SQLCODE=%d]", ret ) ;
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( -1 );
	}
	if( iIrai == 0 ) {
		//�˗���񂪖���
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunchu_ins", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�˗���� NOT FOUND BML��t��(%s) �˗���No(%s) ��������No(%d) ���ڃR�[�h(%s)",
			strIraiTB.utkymd, strIraiTB.irino, strIraiTB.zssdino, strIraiTB.kmkcd ) ;
		sFuncPutErrlist(pst_Env, sFLname, iFLcnt, "", "", 
			strIraiTB.kntno, strIraiTB.irino, buf2, "�˗���񖳂�");
		ZdbRollback();
		if( pKanjya != NULL ) {
			ZbmlFree(pKanjya);
			pKanjya = NULL;
		}
		return( 2 );
	}

	if( pIrai != NULL ) {
		ZbmlFree(pIrai);
		pIrai = NULL;
	}
	if( pKanjya != NULL ) {
		ZbmlFree(pKanjya);
		pKanjya = NULL;
	}

	//�R�~�b�g
	ZdbCommit();

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunchu_ins", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return(0);
}
int
BunFilePut(pst_Env, sBunTenFl, lc_recBuf)
struct bunchuEnv    *pst_Env;
char	*sBunTenFl;
char	*lc_recBuf;
{
	FILE	*fp;

	if( (fp = fopen(sBunTenFl,"a")) == NULL ) {
		return -1;
	}

	if( fputs(lc_recBuf, fp) == EOF ) {
		return -1;
	}

	fclose(fp);

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
sFncTrFileRead ( pst_Env, pc_trFileName, pst_trInfo, iSeqCnt, iSeqCnt1 )
struct bunchuEnv	*pst_Env ;
char				*pc_trFileName ;
Flbun  		*pst_trInfo ;
int			*iSeqCnt;
int			*iSeqCnt1;
{
	FILE	*lfp ;
	char	 lc_recBuf[BUNCHU_RECV_RECSIZE+1] ;
	char	sTrFileName[1024];
	char	*lpc_p ;
	char	 lcbuf[256] ;
	int		 li_idx, iRet, i, ilen, iRecCnt;
	TRAY *strKenPos;
	int		iKenPos;
	int 	iLine;
	char	sDttm[128];
	Flbun	*strBun;
	char	sTray[11], sTray1[11], sTray2[11];
	int		iErrFlg;
	int		iSkip;
	char    sSysdate[128], sSystime[128];
	char	sBunTenFl[BUNCHU_FILE_SIZE];
	char	sBunTenFl1[BUNCHU_FILE_SIZE];
	char	sTmpFl[BUNCHU_FILE_SIZE];
	char	sTmpFl1[BUNCHU_FILE_SIZE];
	char	sNgFl[BUNCHU_FILE_SIZE];
	char	sSpFl[BUNCHU_FILE_SIZE];
	char	sSpFl1[BUNCHU_FILE_SIZE];
	int		iSpCnt;
	int 	iSpaceFlg;

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "Start Function filename=%s", pc_trFileName);

    memset(sDttm, 0, sizeof(sDttm));
    nowdateget1( sDttm );
    sFncPutLog ( TRCKIND_OPT, "", "", 0,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
         "    START(%s) �y%s�z", sDttm, pc_trFileName);


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

	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));
	nowdateget(sSysdate, sSystime);
	memset(sNgFl, 0, sizeof(sNgFl));
	sprintf(sNgFl, "%s/NG%s.dat", pst_Env->cDirBunchuNG, sSysdate);
	iRecCnt = 0;
	iErrFlg = 0;
	iSkip = 0;
	iLine = 0;
	iSpCnt = 0;
	*iSeqCnt1 += 1;
	if( *iSeqCnt1 > 99999 ) *iSeqCnt1 = 1;
	memset(sSpFl, 0, sizeof(sSpFl));
	memset(sSpFl1, 0, sizeof(sSpFl1));
	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));
	nowdateget(sSysdate, sSystime);
	sprintf(sSpFl, "%s/HIBUN%s%s%04d.tmp", pst_Env->cDirTryinfo, sSysdate, sSystime, *iSeqCnt1);
	sprintf(sSpFl1, "%s/HIBUN%s%s%04d.dat", pst_Env->cDirTryinfo, sSysdate, sSystime, *iSeqCnt1);
	//	�ǂݍ���
	memset(sTray,0,sizeof(sTray));
	memset(sTray1,0,sizeof(sTray1));
	while ( fgets ( lc_recBuf, sizeof ( lc_recBuf ), lfp ) != NULL ) {
		strBun = (Flbun *)lc_recBuf;
		if( iLine == 0 ) {
			memset(sBunTenFl, 0, sizeof(sBunTenFl));
			memset(sTmpFl, 0, sizeof(sTmpFl));
			memset(sTmpFl1, 0, sizeof(sTmpFl1));
			memset(sSysdate, 0, sizeof(sSysdate));
			memset(sSystime, 0, sizeof(sSystime));
			nowdateget(sSysdate, sSystime);
			*iSeqCnt += 1;
			sprintf(sBunTenFl, "CHK%s%s%04d.tmp", sSysdate, sSystime, *iSeqCnt);
			sprintf(sBunTenFl1, "CHK%s%s%04d.dat", sSysdate, sSystime, *iSeqCnt);
			sprintf(sTmpFl, "%s/%s", pst_Env->cDirBunchu, sBunTenFl);
		}
		iLine++;
		if( memcmp(strBun->sRackId, "        ", sizeof(strBun->sRackId)) ) {
			memset(sTray2, 0, sizeof(sTray2));
			memcpy(sTray2, strBun->sRackId, sizeof(strBun->sRackId));
			if( (iErrFlg == 1) && !memcmp(sTray, sTray2, sizeof(strBun->sRackId)) ) {
				if( memcmp(sTrFileName, "CHK", 3) ) {
					if( BunFilePut(pst_Env, sTmpFl, lc_recBuf) < 0 ) {
						return( -1 );
					}
					iSkip = 1;
				}
				continue;
			}
		}
		if( (iRet = dBunchu_ins(pst_Env, lc_recBuf, &strKenPos, &iKenPos, sTrFileName, iLine)) < 0 ) {
			if( BunFilePut(pst_Env, sNgFl, lc_recBuf) < 0 ) {
				return( -1 );
			}
			return( iRet );
		}

		//�w�b�_���R�[�h�y�уg���[ID���X�y�[�X�̏ꍇ�͖������ɕ����W�J�����ɂ܂킷
		if( (iRet == 1) || !memcmp(strBun->sRackId, "        ", sizeof(strBun->sRackId)) ) {
			if( memcmp(sTrFileName, "CHK", 3) ) {
				if( BunFilePut(pst_Env, sTmpFl, lc_recBuf) < 0 ) {
					return( -1 );
				}
			}
			iSkip = 1;
			continue;
		}

		strBun = (Flbun *)lc_recBuf;
		memset(sTray1, 0, sizeof(sTray1));
		memcpy(sTray1, strBun->sRackId, sizeof(strBun->sRackId));
		if( iSpaceFlg && (strlen(sTray) != 0) && memcmp(sTray, sTray1, sizeof(strBun->sRackId)) ) {
			memset(sTmpFl1, 0, sizeof(sTmpFl1));
			//�t�@�C���ړ�
			if( iErrFlg == 0 ) {
				if( memcmp(sTrFileName, "CHK", 3) ) {
					sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
					rename(sTmpFl, sTmpFl1);
					memset(sTmpFl, 0, sizeof(sTmpFl));
					memset(sTmpFl1, 0, sizeof(sTmpFl1));
					sprintf(sTmpFl, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
					sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl1);
					//2007-04-06 rename���ɃX���[�v
					sleep ( 1 ) ;
					rename(sTmpFl, sTmpFl1);
				}
			}
			memset(sBunTenFl, 0, sizeof(sBunTenFl));
			memset(sTmpFl, 0, sizeof(sTmpFl));
			memset(sSysdate, 0, sizeof(sSysdate));
			memset(sSystime, 0, sizeof(sSystime));
			nowdateget(sSysdate, sSystime);
			*iSeqCnt += 1;
			sprintf(sBunTenFl, "CHK%s%s%04d.tmp", sSysdate, sSystime, *iSeqCnt);
			sprintf(sBunTenFl1, "CHK%s%s%04d.dat", sSysdate, sSystime, *iSeqCnt);
			sprintf(sTmpFl, "%s/%s", pst_Env->cDirBunchu, sBunTenFl);
			//memcpy(sTray1, strBun->sRackId, sizeof(strBun->sRackId));
			iErrFlg = 0;
			iSkip = 0;
			memcpy(sTray, strBun->sRackId, sizeof(strBun->sRackId));
		}
		if( strlen(sTray) == 0 ) {
			memcpy(sTray, strBun->sRackId, sizeof(strBun->sRackId));
		}
		if( memcmp(sTrFileName, "CHK", 3) ) {
			if( BunFilePut(pst_Env, sTmpFl, lc_recBuf) < 0 ) {
				return( -1 );
			}
		}
		iSkip = 1;
		if( iRet == 0 ) {
			iErrFlg = 0;
		} else {
			iErrFlg = 1;
		}
		++iRecCnt;
		memset(lc_recBuf, 0, BUNCHU_FILE_SIZE+1);
	}
	if( iSkip && !iErrFlg ) {
		if( memcmp(sTrFileName, "CHK", 3) ) {
			sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
			rename(sTmpFl, sTmpFl1);
			memset(sTmpFl, 0, sizeof(sTmpFl));
			memset(sTmpFl1, 0, sizeof(sTmpFl1));
			sprintf(sTmpFl, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl);
			sprintf(sTmpFl1, "%s/%s", pst_Env->cDirTryinfo, sBunTenFl1);
			//2007-04-06 rename���ɃX���[�v
			sleep ( 1 ) ;
			rename(sTmpFl, sTmpFl1);
		}
	}
	if( iSpCnt ) {
		rename(sSpFl, sSpFl1);
	}
	//	�t�@�C���N���[�Y	
	fclose ( lfp ) ;

    memset(sDttm, 0, sizeof(sDttm));
    nowdateget1( sDttm );
    sFncPutLog ( TRCKIND_OPT, "", "", 0,
         EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
         "    END(%s)   �y%s RECORD No %d �z", sDttm, sTrFileName, iRecCnt);

	//�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncTrFileRead", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "End Function");

	return ( iErrFlg );
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
loging ( "stocker : ���L������[CRT] shmKey[%d]-ID[%d]-Data[%d]-Add[%x]\n", pEnv->shm_Key, pEnv->shm_Id, *shmData, shmData ) ;

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
		//���ʃ`�F�b�N("BUN")
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND, 
					  strlen ( BUNCHU_RECV_KIND ) ) == 0 ) {
			return ( 1 ) ;
		}
		//���ʃ`�F�b�N("CHK")
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND1, 
					  strlen ( BUNCHU_RECV_KIND ) ) == 0 ) {
			return ( 1 ) ;
		}
		//���ʃ`�F�b�N("HIBUN")
		if ( memcmp ( pdirEnt->d_name, 
					  BUNCHU_RECV_KIND2, 
					  strlen ( BUNCHU_RECV_KIND ) ) == 0 ) {
			return ( 1 ) ;
		}
/*
		//�g���q�`�F�b�N
		if ( memcmp ( &(pdirEnt->d_name[li_len-strlen(BUNCHU_RECV_SFX)]), 
					  BUNCHU_RECV_SFX, 
					  strlen ( BUNCHU_RECV_SFX ) ) != 0 ) {
			return ( 1 ) ;
		}
*/
		return ( 0 ) ;
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
	fprintf ( stderr, "bunchu : endFunction [%d]\n", gintErrorCode ) ;
}

/** End of File ***************************************************************/
