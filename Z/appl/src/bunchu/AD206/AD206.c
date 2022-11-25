/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FAD206.c                                                      */
/* �@�T�@�@�@�v�F�������ʕϊ�����                                             */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2007/06/01     YOON           �V�K�쐬                           */
/*  2.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
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

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

#include "AD206.h"

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
MYAPP_STSCODE			 gintErrorCode ;
MYAPP_SYSTEM_VERSION	 gtSystemVersion ;
static	char			*gpToken ;			//	sFncTrFileToken�p�ÓI�|�C���^
struct stcLogMember		 gstLogMem ;		//	���O�o�͏��

int g_nKinkmmst;
struct S_KINKMMST *g_strKinkmmst ;

int g_iSyaknr;
Sysknrmst *g_strSysknr = NULL;
/* �`�F�b�N�����z�� */
static char *moji[] = {
    "��","��","��","��","Ƹ","Ͳ","ն","��","��","��","��","´","��","ؽ","��",
    "��","��","��","��","��","��","��","��","��","·","п","��","��","��","��",
    "��","��","��","Ͻ","Ⱥ","��","��","��","��","��","��","շ","��","��","��",
    "��","��","��","��","��","��","��","��","��","��","��","Ѽ","��","��","��",
    "��","��","��","��","��","��","ʽ","��","��","Ƽ","��","��","��","��","��",
    "��","̶","��","��","��","��","��","��","��","��","��","��","��","��","��",
    "��","��","��","��","��","��","��","��","μ","��","��","Ž","��","��","��",
    "��","��","��","��","̷","��","��","��","��","��","��","��","��","ʹ","��",
    "��","��","��","��","��","Ƕ","��","��","��","��","��","��","ƽ","��","��",
    "��","��","��","��","ʼ","��","��","��","Լ","��","��","��","ּ","��","��",
    "��","��","��","��","ظ","��","��","̴","��","��","��","��","��","��","��",
    "��","��","��","��","��","��","��","��","��","��","��","��","��","��","��",
    "��","��","��","��","��","��","��","��","ķ","��","��","��","��","��","��","��","��"
    };
/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
//	�g���[�E���b�N�R�t�����֘A�֐�
static	char*	sFncTrFileToken ( char * ) ;

//	�t�@�C���폜
static	void	sDelOrderFile ( char *, char *, char *, char * ) ;

//	���L����������֐�
static	int		sFncShmCrt ( struct appEnv * ) ;
static	int		sFncShmGet ( struct appEnv * , int *) ;
static	int		sFncShmDel ( struct appEnv * ) ;

//	�R�[���o�b�N�֐�
static	int		sFncFileCompar ( struct dirent **, struct dirent ** )  ;
static	int		sFncFileFillter ( struct dirent * ) ;

//	���̑�
static	int		sFncFileRename ( char *, char *, char *, char * ) ;

//	�g���[�X�p
static	void	_sFncEnvDip ( struct appEnv * ) ;

extern long KinkmmstSelectKey( char *,struct  S_KINKMMST** arrayOut, int* numOut );
//extern int selectIRAI(char *utkymd,char *irino,char *smpcd,
//		struct S_IRAI ** pRecv,int *pRecCnt);
extern int selectIRAI(char *utkymd,char *irino,char *smpcd,char *kmkcd,
		int *nLotno,int *pRecCnt);
extern int selectKANJYA(char *utkymd, char *irino,struct S_KANJYA *pRecv,int *pRecCnt);
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
initFunction( argc, argv, pAppEnv )
int					 argc ;
char				*argv[] ;
struct appEnv	*pAppEnv ;
{
	char	 lc_prmBuf[256] ;
	long	 ll_retSts ;
	char	*lc_login ;

    /***
     ***    �����`�F�b�N
     ***/
	if ( argc != 2 ) {
		fprintf ( stderr, 
			"%s(Line:%d) : There is an error in a command parameter\n", 
			MYAPP_APP_NAME,__LINE__ ) ;
		return ( -1 ) ;
	}

	/***
	 ***	���O�I�[�v��
	 ***/
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		printf("LogOpen Error(Line:%d)\n",__LINE__);
		return ( -1 ) ;
	}
	char *array = NULL;
	ZbmlRealloc( array, (10 )); 
	//	���O��񏉊��ݒ�
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	�J�n���O�o��
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����N��" ) ;

	/***
	 ***	������	
	 ***/
	//	�G���[�X�e�[�^�X�ύX
	gintErrorCode = 0 ;

	//	�v���O�������ϐ�������
	memset ( pAppEnv , '\0', sizeof ( struct appEnv ) ) ;

	/***
	 ***	�����`�F�b�N	
	if ( argc != 2 ) {
		gintErrorCode = MYAPP_STSCODE_ERR_USEGE ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "initFunction", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�R�}���h�p�����[�^�Ɍ�肪����܂�" ) ;
		return ( -1 ) ;
	}
	 ***/

	/***
	 ***	�p�����[�^�t�@�C�����ޔ�
	 ***/
	//	�p�����[�^�t�@�C�����ޔ�
	pAppEnv->pcFielNamePRM = argv[1] ;

	//	�p�����[�^�t�@�C���I�[�v��	
	pAppEnv->bp = ZbmlPrmOpen ( pAppEnv->pcFielNamePRM ) ;		
	if ( pAppEnv->bp == NULL ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", pAppEnv->pcFielNamePRM ) ;
		return ( -1 ) ;
	}

	//	��M���
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_BUNCHU,
						pAppEnv->cDirNR_Col ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_BUNCHU) ;
		return ( -1 ) ;
	}
	//	��M�������
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_BUNCHU_OK, 
						pAppEnv->cDirNR_ColOk ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_BUNCHU_OK ) ;
		return ( -1 ) ;
	}
	//	��M����G���[
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_BUNCHU_ERR, 
						pAppEnv->cDirNR_ColErr ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_BUNCHU_ERR ) ;
		return ( -1 ) ;
	}

    // �g���[No���t�@�C���i�[�f�B���N�g
    if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_TRAY_INFO,
                        pAppEnv->cDirTryinfo ) != 0 ) {
        //  �ُ�I��    LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DIR_TRAY_INFO ) ;
        return ( -1 ) ;
    }
    //�g���[No���t�@�C���i�[�f�B���N�g��(����)
    if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_TRAY_INFO_OK,
                        pAppEnv->cDirTryinfoOK ) != 0 ) {
        //  �ُ�I��    LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�g���[No���t�@�C���i�[�f�B���N�g��(����)�擾���s");
        return ( -1 ) ;
    }
//    //�g���[No���t�@�C���i�[�f�B���N�g��(�G���[)
//    if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DIR_TRAY_INFO_NG,
//                        pAppEnv->cDirTryinfoNG ) != 0 ) {
//        //  �ُ�I��    LOG
//		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
//		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
//				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//				 	 "�g���[No���t�@�C���i�[�f�B���N�g��");
//       return ( -1 ) ;
//    }


	//	���L�������L�[�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv->shm_Key = atoi ( lc_prmBuf ) ;
	//	SLEEPSEC�擾
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_SLEEP_SEC, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_SLEEP_SEC ) ;
		return ( -1 ) ;
	}
	pAppEnv->sleep_Sec= atoi ( lc_prmBuf ) ;
	//	�f�[�^�x�[�X��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_NAME, 
						pAppEnv->cDb_Name ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X���[�U
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_USER, 
						pAppEnv->cDb_User ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	�f�[�^�x�[�X�p�X���[�h
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_DB_PASSWD, 
						pAppEnv->cDb_Passwd ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
	//	�t�@�C���Ǎ����g���C��
	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_FILE_RETRY, lc_prmBuf ) != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�p�����[�^���擾�ł��܂���ł���[%s]", MYAPP_PRM_FILE_RETRY ) ;
		return ( -1 ) ;
	}
	pAppEnv->fileRetry = atoi ( lc_prmBuf ) ;
	//	�o�[�W�������i������Ή��j	
//DEL	gtSystemVersion = MYAPP_SYSTEM_NEW ;
//DEL	if ( ZbmlPrmGetVal ( pAppEnv->bp, MYAPP_PRM_VERSION, 
//DEL						pAppEnv->cVersion ) != 0 ) {
//DEL		gtSystemVersion = MYAPP_SYSTEM_OLD ;
//DEL	}

	//	�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose ( pAppEnv->bp ) ;

	/***
	 ***	���L����������	
	 ***/
	if ( sFncShmCrt ( pAppEnv ) < 0 ) {
		return ( -1 ) ;
	}

	/***
	 ***	�f�[�^�x�[�X�I�[�v��
	 ***/
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ZdbConnect", __LINE__,
		 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "�f�[�^�x�[�X�I�[�v�����܂�[DB=%s USER=%s PASS=%s]"
		, pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	ll_retSts = ZdbConnect( pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "�f�[�^�x�[�X�I�[�v���Ɏ��s���܂���[DB=%s USER=%s PASS=%s]", pAppEnv->cDb_Name, pAppEnv->cDb_User, pAppEnv->cDb_Passwd ) ;
		return ( -1 ) ;
	}

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
mainFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int					  li_retSts ;
	long				  ll_retSts ;

	int					  li_idx ;	
	int					  li_stopFlg ;

	int 				  li_of_idx;

	//	�f�B���N�g����� 
	DIR					 *lt_dp ;
	struct dirent		**lpst_dirBuf ;

	//	�g���[���b�N���֘A
	int					  li_fileCnt ;				

	FILE *fp;
	char recBuf[128] = {0,};
	int lRet =0;


//�V�X�e���Ǘ��}�X�^
	g_strSysknr = NULL;
	g_iSyaknr = 0;

	if( g_strSysknr != NULL ) {
        ZbmlFree(g_strSysknr);
        g_strSysknr = NULL;
    }

	if( (lRet = ABunSyskanSelKey(&g_strSysknr, &g_iSyaknr)) < 0 ) {
        sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�V�X�e���Ǘ��}�X�^ SQL ERROR(%d)",lRet);
        return 0;
    }

    if(g_iSyaknr != 1){
        sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�V�X�e���Ǘ��}�X�^ �����ԈႢ�܂��B(%d)",g_iSyaknr);
        return 0;
    }

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "while start", __LINE__,
		 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		 "File Dir<%s>\n",pAppEnv->cDirNR_Col);

	while ( 1 ) 
	{

		if ( ( li_fileCnt = scandir ( pAppEnv->cDirNR_Col, 
									  &lpst_dirBuf,
									  (void*)sFncFileFillter,
					   				  (void*)sFncFileCompar ) ) < 0 ) {
			//	�ُ�I��	LOG
			gintErrorCode = MYAPP_STSCODE_ERR_DIR;
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "scandir", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "�ً}�������ʏ��t�@�C���̎擾�Ɏ��s���܂���" ) ;
			return ( -1 ) ;
		}

		li_idx = 0 ;
		stOUTPUT_DATA stOutput;
		memset(&stOutput,0,sizeof(stOUTPUT_DATA));
		stOutput.nPos = MYAPP_KMKCD_START_POS;

		char filename[1024] = {0,};
		for ( li_idx = 0 ; li_idx < li_fileCnt ; li_idx ++ ) {

			sprintf(filename,"%s/%s",pAppEnv->cDirNR_Col,lpst_dirBuf[li_idx]->d_name);
			//fp  = fopen ( lpst_dirBuf[li_idx]->d_name, "r" ) ;
			fp  = fopen ( filename, "r" ) ;
			if ( fp == NULL ) {
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "FILE Open ERROR Directory:<%s>",filename);
				return(0);
			}
			sFncPutLog ( TRCKIND_OPT, __FILE__, "fopen", __LINE__,
				 	 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 	 "�t�@�C���I�[�v��<%s>",filename);


			FILE *fp_out;
			char Chkfilename[1024] = {0,};
			int nBreakFlg = 0;
			int nOseq  = 1;					// ADD 2007.06.27
			char sOutChgFlg[2];				// ADD 2007.06.27
			memset(sOutChgFlg,0,sizeof(sOutChgFlg));
			sOutChgFlg[0]='0';	

			// OUTPUT FILE NAME CHK_INPUTFILENAME_nOseq.dat
			//		1FILE���̏����I���܂ł́AINPUT_DIR�Ƀt�@�C���o�͂���
			sprintf(Chkfilename,"%s/%s_%s_%03d.dat"
				,pAppEnv->cDirNR_Col
				,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, nOseq );
			fp_out  = fopen ( Chkfilename, "aw" ) ;
			if(fp_out == NULL)
			{
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "FILE Open ERROR Directory:<%s>",Chkfilename);
				return(0);
			}

			stOutput.fp = fp_out;
			//  �ǂݍ���
			while(1){
				memset(recBuf,0,sizeof(recBuf));
				nBreakFlg =fgets ( recBuf, sizeof( recBuf ), fp );

				if(nBreakFlg== 0) 
				{
					break;
				}
				lRet = strlen(recBuf);
				if(lRet != MYAPP_RECV_RECSIZE)
				{
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "read", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "���R�[�h�T�C�Y�����v���܂���B<%d>",lRet);
					
					break;
				}
					
				// 1INPUT -> TrayID����1OUTPUT
				// lRet = procFile(pAppEnv,lpst_dirBuf[li_idx]->d_name,recBuf,&stOutput);
				lRet = procFile(pAppEnv,lpst_dirBuf[li_idx]->d_name,recBuf,&stOutput,sOutChgFlg);
				if(lRet == 0){
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "procFile", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "DB�������T���Ȃ��B");
					break;
				}

				// FILE OUTPUT BREAK CHECK
				if ( sOutChgFlg[0] == '1' ){
					// file close
					fclose (stOutput.fp);	
					sFncPutLog ( TRCKIND_DEBUG, __FILE__, "fclose", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "����t�@�C���������܂����B<output:%s>",Chkfilename );
					// next file open
					sOutChgFlg[0] = '0';
					nOseq++;
					sprintf(Chkfilename,"%s/%s_%s_%03d.dat"
						,pAppEnv->cDirNR_Col
						,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, nOseq );
					fp_out  = fopen ( Chkfilename, "aw" ) ;
					if(fp_out == NULL)
					{
						sFncPutLog ( TRCKIND_ERROR, __FILE__, "fopen", __LINE__,
							 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							 "FILE Open ERROR Directory:<%s>",Chkfilename);
						break;
					}
					stOutput.fp = fp_out;
				}

			}

			fclose ( fp ) ;
			if(nBreakFlg == 0){

				//����I��
				//	LAST 1 RECORD
				fwrite(&stOutput,MYAPP_PNC_MAX_SIZE,1,stOutput.fp);
				memset(&stOutput,0,MYAPP_PNC_MAX_SIZE);
				stOutput.nPos = MYAPP_KMKCD_START_POS;
				memset(stOutput.KeyKntno,0,sizeof(stOutput.KeyKntno));
				memset(stOutput.KeyEda,0,sizeof(stOutput.KeyEda));
				
				fclose (stOutput.fp);	
				sFncPutLog ( TRCKIND_DEBUG, __FILE__, "fclose", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					 "����t�@�C���������܂����B<output:%s>",Chkfilename );

				// INPUT FILE  -> OK
				sFncFileRename ( pAppEnv->cDirNR_Col,lpst_dirBuf[li_idx]->d_name 
						, pAppEnv->cDirNR_ColOk,lpst_dirBuf[li_idx]->d_name );

				// OUTPUT -> OUTPUT DIR
				for ( li_of_idx=1; li_of_idx <= nOseq; li_of_idx++ ){
					sprintf(Chkfilename,"%s_%s_%03d.dat"
						,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, li_of_idx );
					sFncFileRename ( pAppEnv->cDirNR_Col,Chkfilename
							, pAppEnv->cDirTryinfo, Chkfilename );
					sFncPutLog ( TRCKIND_OPT, __FILE__, "rename", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "����t�@�C���������܂����B<MOVE:%s%s>",
							pAppEnv->cDirTryinfo, Chkfilename );
				}
			}
			else{

				fclose (stOutput.fp);	

				// �G���[��INPUT �͂��̂܂܂̃f�B���N�g���Ɏc��
				// �G���[��OUTPUT �͍폜����
				for ( li_of_idx=1; li_of_idx <= nOseq; li_of_idx++ ){
					sprintf(Chkfilename,"%s/%s_%s_%03d.dat"
						,pAppEnv->cDirNR_Col
						,MYAPP_SEND_KIND_CH, lpst_dirBuf[li_idx]->d_name, li_of_idx );
					remove(Chkfilename);
					sFncPutLog ( TRCKIND_ERROR, __FILE__, "remove", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						 "REMOVE FILE<%s>",Chkfilename);
				}
			}
		}

		/***
		 *** ��~�R�}���h�m�F
		 ***/
		if ( sFncShmGet ( pAppEnv, &li_stopFlg ) == 0 ) {
			if ( li_stopFlg == 1 ) {
				break ;
			}
		}

		/***
		 *** �X���[�v
		 ***/
		sleep ( pAppEnv->sleep_Sec ) ;
	}

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
endFunction( pAppEnv )
struct appEnv	*pAppEnv ;
{
	/***
	 ***	�f�[�^�x�[�X�N���[�Y
	 ***/
	ZdbDisConnect() ;

	/***
	 ***	���L�������폜	
	 ***/
	sFncShmDel ( pAppEnv ) ;

	/***
	 ***	���O�N���[�X
	 ***/
	//	�J�n���O�o��
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "�v���O�����I��" ) ;
	ZbmlCloseLog() ;
	exit(9);	
	return ;
}

/******************************************************************************/
/*  �� �� ���@�FprocFile()                                                    */
/*  �@�\�T�v�@�F������O��̃X�y�[�X���폜����                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *      �ҏW������                                        */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
/*  ���L����  �F���ꌟ�̔ԍ��ɂ����ẮA�T���v�����O�R�[�h���K����v����Ƃ���*/
/*              �O��ŁA����̍��ڂ݂̂�KINKMMST���SELECT���A�T���v�����O�R�[*/
/*              �h���擾����B�܂��A�ً}SUN����M�����������ʃt�@�C���ɂ��� */
/*              ���ڃR�[�h�́A�W�J������AD205���ň˗������擾����B       */
/******************************************************************************/
//int procFile(struct appEnv *pAppEnv,char *filename,char *sRecv,stOUTPUT_DATA *stOutput)
int procFile(struct appEnv *pAppEnv,char *filename,char *sRecv,stOUTPUT_DATA *stOutput, char *sOutChgFlg)
{
	char kmkcd[8] = {0,};
	char edaban[3] = {0,};					// ADD
	stINPUT_DATA stINPUT;
	memset(&stINPUT,0,sizeof(stINPUT_DATA));
    int cur=0;

/*** �t�@�C����������\���̂֓W�J ***/
	memcpy( stINPUT.utkymd, sRecv + cur, 8 );				/* ��t���t �擾 						*/
	cur += 8;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.kntno, sRecv + cur, 11 );				/* ����No �擾 							*/
	cur += 11;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.eda, sRecv + cur, 2 );					/* �\�� �擾 							*/
	cur += 2;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.sincode, sRecv + cur, 7 );				/* �e���ڃR�[�h �擾 					*/
	cur += 7;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.kmkcd, sRecv + cur, 7 );				/* ���ڃR�[�h �擾 						*/
	cur += 7;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.wscd, sRecv + cur, 4 );					/* WS�R�[�h �擾 						*/
	cur += 4;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.scheduleno, sRecv + cur, 4 );			/* SEQ�ԍ� �擾 						*/
	cur += 4;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.motorackid, sRecv + cur, 8 );			/* �����b�NID �擾 						*/
	cur += 8;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.motorackpos, sRecv + cur, 2 );			/* ���|�W�V���� �擾 					*/
	cur += 2;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.bunchurackid, sRecv + cur, 8 );			/* ���b�NID �擾 						*/
	cur += 8;												/* ��M�t�@�C���|�C���^��READ�������ړ� */
	memcpy( stINPUT.bunchurackpos, sRecv + cur, 2 );		/* �|�W�V���� �擾 						*/
	cur += 2;												/* ��M�t�@�C���|�C���^��READ�������ړ� */

	char rackpos[4] = {0,};
	sprintf(rackpos,"%03d",atoi(stINPUT.bunchurackpos));

/*** 64���ڐ����Ή� ��ʂ���̗v��(�t�@�C��)�𖳎����āAIRAI��񂩂獀�ڂ���� -> ***/
	if(stOutput->nPos == MYAPP_KMKCD_START_POS){	/* ���񏈗���AnPos���f�N�������g���Ĕ���Ɏg�p */
		//���񏈗��|�������Ȃ�	*/
	}
	else if( strcmp(stOutput->KeyKntno,stINPUT.kntno)==0
//	&& strcmp(stOutput->KeyEda,stINPUT.eda) ==0
		&& strncmp(stOutput->utkymd,stINPUT.utkymd,sizeof(stOutput->utkymd)) ==0
		&& strncmp(stOutput->altuseiRackID,stINPUT.bunchurackid,sizeof(stOutput->altuseiRackID)) ==0
		&& strncmp(stOutput->iti1,rackpos,sizeof(stOutput->iti1)) == 0)
	{	//�������̔ԍ�	*/
		memset(kmkcd,0,sizeof(kmkcd));
		memcpy(kmkcd, stINPUT.kmkcd, 7);				/* ���ڃR�[�h���擾 */

/*		memcpy(stOutput->kmkcd[stOutput->nPos] , kmkcd, 7);	*//* �擾�������ڃR�[�h���o�͐��SET */
	/* ���ڃR�[�h�͐ݒ肵�Ȃ� */
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"���ڒǉ�[%d],<����:%s>",stOutput->nPos, kmkcd);
/*		stOutput->nPos --;*//* �J�E���g���Ȃ� */
		return 1;
	}
	else
	{	//�V�������̔ԍ�
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"FILE WRITE");
		fwrite(stOutput,MYAPP_PNC_MAX_SIZE,1,stOutput->fp);

		// ADD bunchurackid ���ς������o�̓t�@�C���𕪂���
		if (strncmp(stOutput->altuseiRackID,stINPUT.bunchurackid,sizeof(stOutput->altuseiRackID))!=0 ){
			sOutChgFlg[0] = '1';
		}

		// �o�͌n�̏�����
		memset(stOutput,0,MYAPP_PNC_MAX_SIZE);
		stOutput->nPos = MYAPP_KMKCD_START_POS;
		memset(stOutput->KeyKntno,0,sizeof(stOutput->KeyKntno));
		memset(stOutput->KeyEda,0,sizeof(stOutput->KeyEda));
	}
/*** 64���ڐ����Ή� ��ʂ���̗v��(�t�@�C��)�𖳎����āAIRAI��񂩂獀�ڂ���� <- ***/

	//  ��{�����L�[�ݒ�
	char utkymd[12] = {0,};
	char irino[12] = {0,};
	int nRecCnt =0;
	int lRet =0;
	struct S_KANJYA sKanjya;

	sprintf ( utkymd , "%4.4s-%2.2s-%2.2s",						/* ��t���t�̎擾 */
		  stINPUT.utkymd,&stINPUT.utkymd[4],&stINPUT.utkymd[6]);

	sprintf (irino,"00%-3.3s%-4.4s00",stINPUT.kntno, &stINPUT.kntno[5]);
																/* ����No����˗���No�̎擾(00xxxxxxx00�`��) */

	if(strcmp(g_strSysknr->kkkjsriymd,utkymd) != 0){
	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "�V�X�e���Ǘ��}�X�^�ً̋}�������(%s)�Ǝ�t��(%s)���Ⴂ�܂��B"
			,g_strSysknr->kkkjsriymd,utkymd);
		return 0;
	}

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "���ҏ��e�[�u������<��t��:%s><�˗�NO:%s>",utkymd,irino);

	lRet=selectKANJYA(utkymd,irino,&sKanjya,&nRecCnt);

	if(lRet == MYAPP_SQL_DEADLOCK || lRet== MYAPP_SQL_DUPLICATION)
	{

		//  ���[���o�b�N
	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
	}
	else if(lRet<0){

		sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
	}

	// �����C���l����1���ȏ����������\������
	//if(nRecCnt != 1)[
	if(nRecCnt < 1){
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "���҃e�[�u���̒��Ō�������Ȃ� <���̔ԍ�:%s>",irino);
		return 0;
	}

	g_strKinkmmst= NULL;
    g_nKinkmmst = 0;
/*** �������ʃt�@�C���̍��ڂ���ً}���ڃ}�X�^�̃T���v�����O�R�[�h���擾���� --> ***/
	sprintf(kmkcd,"%s",stINPUT.kmkcd);					/* �������ʂ��獀�ڃR�[�h���擾 */
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�ً}���ڃ}�X�^����<���ڃR�[�h:%s>",kmkcd);
	lRet = KinkmmstSelectKey(kmkcd, &g_strKinkmmst,&g_nKinkmmst);	/* �ً}���ڃ}�X�^SELECT */

	if(lRet == MYAPP_SQL_DEADLOCK || lRet== MYAPP_SQL_DUPLICATION)
    {

		sFncPutLog ( TRCKIND_ERROR, __FILE__, "KinkmmstSelectKey", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�ً}�}�X�^SQL ERROR(%d)",lRet);
        ZdbRollback () ;
        endFunction( pAppEnv );
    }
	else if(lRet<0){

        sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "SELECT ERROR(%d)",lRet);
        ZdbRollback () ;
        endFunction( pAppEnv );
    }

	if(g_nKinkmmst<= 0){
        sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "�ً}���ڃ}�X�^�e�[�u���̒��Ō�������Ȃ� ");
        return 0;
    }

	char tmp_smpcd[8] = {0,};
	strcpy(tmp_smpcd,g_strKinkmmst[0].smpcd);		/*	�ً}���ڃ}�X�^����擾�����T���v�����O�R�[�h���R�s�[ */
	free(g_strKinkmmst);							/* SELECT���� Free */

#if 0	/* �������ʂ̍��ڂƈ˗��e�[�u���̐����`�F�b�N�́A���ڂ����Ȃ�(64���ڐ����Ή�) */
		/* �悤�ɕύX�����ׁA�s�v�B����Ĉȉ��̍폜!!!                                */
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�˗���񌟍�<utkymd:%s><irino:%s><smpcd:%s>"
			,utkymd, irino,tmp_smpcd);
	struct S_IRAI *pIrai = NULL;
	nRecCnt =0;
	int	nLotno=0;

	lRet=selectIRAI(utkymd, irino, tmp_smpcd, kmkcd, &nLotno, &nRecCnt);
	if(lRet == MYAPP_SQL_DEADLOCK || lRet== MYAPP_SQL_DUPLICATION)
	{

		//  ���[���o�b�N
	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
		
	}
	else if(lRet<0){

	 	sFncPutLog ( TRCKIND_ERROR, __FILE__, "", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			 "SELECT ERROR(%d)",lRet);
		ZdbRollback () ;
		endFunction( pAppEnv );
	}
	if(nRecCnt <= 0){
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "", __LINE__,
             EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
             "�˗��e�[�u���̒��Ō�������Ȃ� ");
		return 0;
	}
	// �ً}�˗����b�gNo�ޔ�
	sprintf( edaban, "%.02d", nLotno );
	
	free(pIrai);
#endif
	/* <--�����܂ŁA�˗��e�[�u���Q�ƃ��W�b�N���폜 -->*/

	// �`�F�b�N�����擾
	char strKntno[3]={0,};
	bmlConvBarcode(stINPUT.kntno,strKntno);

/*** Ver 2.00 ����No�̎�M�`����PNC�`��11���������ׁAeda�͎g�p���Ȃ��l�ɕύX ***/
/*	char barcd[12] = {0,}; */
/*	sprintf(barcd,"0%2.2s00%4.4s%2.2s" */
/*		,stINPUT.kntno, &stINPUT.kntno[2], stINPUT.eda);	 */
	// �}�Ԃ��󔒂̏ꍇ�ً͋}�˗����b�gNo��ҏW
/*	if(stINPUT.eda[0] == ' ' ){ */
/*		memcpy( &barcd[9], edaban, 2 );	*/
/*	}*/
/***																		 ***/
/*** �������ʃt�@�C���̈˗��͌��Ȃ� <-- ***/

	memset(stOutput,' ',MYAPP_PNC_MAX_SIZE);
	stOutput->nPos = MYAPP_KMKCD_START_POS;

	memcpy(stOutput->syokubetumozi ,"R1",2);
	memcpy(stOutput->transactionID ,"SDATA1",6);
	memcpy(stOutput->altuseiRackID ,stINPUT.bunchurackid,8);
	memcpy(stOutput->utkymd ,stINPUT.utkymd,8);
	memcpy(stOutput->iti1 ,rackpos,3);
	memcpy(stOutput->BMLutkymd ,stINPUT.utkymd,8);
/*	memcpy(stOutput->iraino ,barcd,11); */						/* kntno����_�C���N�g�Ɏ擾����悤�ɕύX */
	sprintf(stOutput->iraino,"%-9.9s00",stINPUT.kntno);			/* ����No����˗���No�̎擾(kntno�̎}�Ԃ��}�X�N) */
/*	memcpy(stOutput->kntno ,barcd,11); */						/* kntno����_�C���N�g�Ɏ擾����悤�ɕύX */
	memcpy(stOutput->kntno ,stINPUT.kntno,11);					/* ��M�f�[�^��kntno�����̂܂ܐݒ� */
	memcpy(stOutput->kntchkmozi ,strKntno,2);
	memcpy(stOutput->WS ," ",1);
	memcpy(stOutput->sbkbn ,sKanjya.sbtkbn,1);
	memcpy(stOutput->nrkbn ,sKanjya.agekbn,1);
	memcpy(stOutput->nr ,sKanjya.age,3);

	memcpy(stOutput->nyoutime ,sKanjya.bko2,4);
	memcpy(stOutput->nyoutime_tan ,&sKanjya.bko2[5],1);
	memcpy(stOutput->nyouryou ,&sKanjya.bko2[7],5);
	memcpy(stOutput->nyouryou_tan ,&sKanjya.bko2[13],1);

	memcpy(stOutput->sstcd ,sKanjya.sstcd,7);
	memcpy(stOutput->egyoucd ,sKanjya.ecd,3);
	memcpy(stOutput->motoRackID ,stINPUT.motorackid,8);
	sprintf(rackpos,"%03d",atoi(stINPUT.motorackpos));
	memcpy(stOutput->motoRackPos ,rackpos,3);
	memcpy(stOutput->wscd ,tmp_smpcd,4);

/*** 64���ڐ����Ή� ��ʂ���̗v��(�t�@�C��)�𖳎����āAIRAI��񂩂獀�ڂ���� ***/
/*	memcpy(stOutput->kmkcd[stOutput->nPos] ,stINPUT.kmkcd, 7);	*/

	memcpy(stOutput->bckID,"   ",3);
	memcpy(stOutput->jtflg," ",1);
	memcpy(stOutput->kssr,"1",1);
	memcpy(stOutput->tgennflg ," ",1);
	memcpy(stOutput->kkirflg ," ",1);
	memcpy(stOutput->btkka ,"0",1);
	memset(stOutput->Filler,' ',466);
	stOutput->Filler[466] = '0';
	stOutput->LF = '\n';

/*** 64���ڐ����Ή� ��ʂ���̗v��(�t�@�C��)�𖳎����āAIRAI��񂩂獀�ڂ���� -> ***/
	stOutput->nPos--;						/* ����Ƌ�ʂ���ׂɃf�N�������g�B����ȊO�ɂ͎g��Ȃ� */
	strcpy(stOutput->KeyKntno,stINPUT.kntno);	
	strcpy(stOutput->KeyEda,stINPUT.eda);	

	return 1;
}

/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()  			 									  */
/*  �@�\�T�v�@�F������O��̃X�y�[�X���폜����				  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ҏW������								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
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
	//strcpy ( gstLogMem.pcSrcName, pcSrcName ) ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	//gstLogMem.lLineNo = plLineNo ;
	strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
	strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***
	 ***	���O�o��
	 ***/
#ifdef _DEBUG_LOG
	printf("(%d)%s\n",plLineNo,gstLogMem.pcMsg);
#endif

	_ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
	return ;
	
}

////////////////////////////////////////////////////////////////////////////////
//  �� �� ���@�FbmlConvBarcode ()
//  �@�\�T�v�@�F�o�[�R�[�h���A���̃`�F�b�N�������擾����B
//  ���@�@�́@�F
//�@ ��P���� �Fchar *pIn_data �o�[�R�[�h
//  �o�@�@�́@�F�Ȃ�
//�@ ��P���� �Fchar *pOut_data ���̃`�F�b�N����
//  ���A���@�F int
//�@�@�@�@�@�@�@ RET_OK  : ����
// �@�@�@�@�@�@�@RET_ERR : �ُ�
////////////////////////////////////////////////////////////////////////////////
int bmlConvBarcode(char *pIn_data, char *pOut_data)
{
    char   ken[16];
    int    i,chk_flg;
    int    amr=0;
    int    ukentai = 0;

    ukentai = atoi(pIn_data);
    chk_flg = 0;

    memset(ken, 0x0, sizeof(ken));
    strcpy(ken, pIn_data);


    for(i=0; i<strlen(ken); i++){
        if(isdigit(ken[i]) == 0){   /* �����łȂ� */
            chk_flg=1;
            break;
        }
    }
    if(chk_flg == 1){
        strcpy(pOut_data,"    ");
        return(-1);
    }

    amr = ukentai % 197;
    strcpy(pOut_data,moji[amr]);

    return 1;
}

/******************************************************************************/
/*  �� �� ���@�FsFncTrFileToken()			 								  */
/*  �@�\�T�v�@�F�g�[�N������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	������									 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fchar *														  */
/*					 NULL	�I�[											  */
/*					 NULL�ȊO	������										  */
/******************************************************************************/
static	char*
sFncTrFileToken ( pString )
char	*pString ;
{
	char	*p ;
	char	*pRet ;
	int		 liIdx ;

	//	����������|�C���^�[�ݒ�
	if ( pString == NULL ) {
		p = gpToken ;	
	}
	else {
		gpToken = pString ;
		p = pString ;	
	}

	//	�I�[�`�F�b�N�i�ŏI�J���}�ȍ~���Ō�̒l�Ǝ擾���邽�߁j	
	if ( p == NULL ) {
		return ( NULL ) ;
	}

	//	�g�[�N������
	gpToken = NULL ;	//�ŏI�J���}�ȍ~���Ō�̒l�Ǝ擾���邽��
	pRet = p ;
	while ( *p ) {
		if ( *p == ',' ) {
			*p  = '\0' ;
			gpToken =  p + 1 ;
			break  ;
		}	
		p++ ;
	}
	return ( pRet ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncFileRename()  			 								  */
/*  �@�\�T�v�@�F�t�@�C�����ړ�����							  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	�ړ����f�B���N�g��						 	      */
/*�@ ��Q���� �Fchar *   	�ړ����t�@�C����						 	      */
/*�@ ��R���� �Fchar *   	�ړ���f�B���N�g��						 	      */
/*�@ ��S���� �Fchar *   	�ړ���t�@�C��							 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncFileRename ( pc_fromDir, pc_fromFileName, pc_toDir, pc_toFileName )
char	*pc_fromDir ;
char	*pc_fromFileName ;
char	*pc_toDir ;
char	*pc_toFileName ;
{
	char	lc_fromPath[MYAPP_PATH_SIZE] ;
	char	lc_toPath[MYAPP_PATH_SIZE] ;

	sprintf ( lc_fromPath, "%s/%s", pc_fromDir, pc_fromFileName ) ;
	sprintf ( lc_toPath,   "%s/%s", pc_toDir,   pc_toFileName ) ;

	if ( rename ( lc_fromPath, lc_toPath ) < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "rename", __LINE__,
 	 	 			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
 	 	 			 "�t�@�C���̈ړ��Ɏ��s���܂���[%s->%s]", lc_fromPath, lc_toPath ) ;
		return ( -1 ) ;
	}
	
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmCrt ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	�擾
	pAppEnv->shm_Id = shmget ( (key_t)pAppEnv->shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv->shm_Id < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
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

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����		 		      */
/*�@ ��Q���� �Fint *   			�l							 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmGet ( pAppEnv, pshmData )
struct appEnv	*pAppEnv ;
int					*pshmData ;
{
	int		*shmData ;

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
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

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\���́B		 		      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
static int
sFncShmDel ( pAppEnv )
struct appEnv	*pAppEnv ;
{
	int		*shmData ;

	//	�폜	
	if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		//sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmctl", __LINE__,
		//		 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		//		 	 "���L�������̑���Ɏ��s���܂���" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	
/******************************************************************************/
/*  �� �� ���@�FsFncFileCompar()			 								  */
/*  �@�\�T�v�@�F�t�@�C������r�y�R�[���o�b�N�֐��z			  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *   	��r������								 	      */
/*�@ ��Q���� �Fchar *   	��r������								 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/******************************************************************************/
static	int
sFncFileCompar ( a, b ) 
struct dirent	**a ;
struct dirent	**b ;
{
		char	*p1 ;
		char	*p2 ;

		p1 = strchr ( (*a)->d_name, '_' ) ;
		if ( p1 == NULL ) {
			p1 = (*a)->d_name ;
		}
		p2 = strchr ( (*b)->d_name, '_' ) ;
		if ( p2 == NULL ) {
			p2 = (*b)->d_name ;
		}
		return ( strcoll ( p1, p2 ) ) ;
		
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
/*			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "scandir", __LINE__,*/
/*				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,*/
/*				 "�t�@�C���T�C�Y��5�ȉ��ł��B<%s>",pdirEnt->d_name);*/
			return ( 0 ) ;
		}

		//���ʃ`�F�b�N
			// OUTPUT�擪������ɍ��v������̂͑ΏۊO�Ƃ���
		if ( memcmp ( pdirEnt->d_name, 
					  MYAPP_SEND_KIND_CH, 
					  strlen ( MYAPP_SEND_KIND_CH ) ) == 0 ) {
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "scandir", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 "���ʃ`�F�b�N�ŊԈႢ�܂����B<��:%s><%s>",
				MYAPP_SEND_KIND_CH,pdirEnt->d_name);
			return ( 0 ) ;
		}

		return ( 1 ) ;
}
/******************************************************************************/
/*  �� �� ���@�F_sFncEnvDip()				 								  */
/*  �@�\�T�v�@�F�v���O�������ϐ��o�͊֐��y�g���[�X�p�z	  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *   	�v���O�������\����			 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����														  */
/******************************************************************************/
static void
_sFncEnvDip( pAppEnv )
struct appEnv	*pAppEnv ;
{
#if defined ( _TRACE )
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
	loging ( "\t�y���L�f�B���N�g���\���z\n" ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_BUNCHU,     pAppEnv->cDirNR_Col ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_BUNCHU_OK,  pAppEnv->cDirNR_ColOk ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_BUNCHU_ERR, pAppEnv->cDirNR_ColErr ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_NR_LOG,     pAppEnv->cDirNR_Log ) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_TRAY_INFO,     pAppEnv->cDirTryinfo) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_TRAY_INFO_OK,     pAppEnv->cDirTryinfoOK) ;
//	loging ( "\t%s : [%s]\n", MYAPP_PRM_DIR_TRAY_INFO_NG,     pAppEnv->cDirTryinfoNG) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SHM_KEY,        pAppEnv->shm_Key ) ;
	loging ( "\t%s : [%d]\n", MYAPP_PRM_SLEEP_SEC,      pAppEnv->sleep_Sec ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_NAME,        pAppEnv->cDb_Name ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_USER,        pAppEnv->cDb_User ) ;
	loging ( "\t%s : [%s]\n", MYAPP_PRM_DB_PASSWD,      pAppEnv->cDb_Passwd ) ;
	loging ( "########## Stocker - _sFncEnvDip ##########\n" ) ;
#endif
}
/******************************************************************************/
/*  �� �� ���@�Fmain()														  */
/*  �@�\�T�v�@�F���C���֐�													  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *pcLogName    	�y�C�Ӂz���O�t�@�C�������w�肷��B		  */
/*									��NULL���w�肵���ꍇ��INI�t�@�C�����	  */
/*									  ���O�����擾����B					  */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F  0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int 
main( argc, argv )
int		 argc ;
char	*argv[] ;
{

	struct appEnv	 sAppEnv ;

	/***
	 ***    �o�b�N�O���E���h���s
	 ***/
	if ( daemon ( 0, 1 ) < 0 ) {
		printf("���O�t�@�C�������w�肳��ĂȂ�");
		exit ( 9 ) ;
	}


	/***
	 ***	��������	
	 ***/
	if ( initFunction ( argc, argv, &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}
_sFncEnvDip ( &sAppEnv ) ;
	
	/***
	 ***	�又��	
	 ***/
	if ( mainFunction ( &sAppEnv )  != 0 ) {
		endFunction ( &sAppEnv ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	�I������	
	 ***/
	endFunction ( &sAppEnv ) ;
	exit(9);
}

/** End of File ***************************************************************/
