/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FFD101IjouChk.c								*/
/*		�T�v		�F���x�Ǘ��ُ�`�F�b�N							*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		J.Iijima		Create					*/
/*  1.01	2006/04/20		INTEC   		Update��������ǂݍ���*/
/*                                          SHM-KEY�A�\���̌�����   */
/*  1.02    2006/12/15      INTEC           SELECT���s���鎞�����@  */
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <sys/ipc.h>					// 1.01 INTEC ADD
#include <sys/shm.h>					// 1.01 INTEC ADD
#include <errno.h>						// 1.01 INTEC ADD
#include "bml_base.h"
#include "FD101IjouChk.h"

//���[�v����p�t���O(0:���[�v��~�A1:���[�v�p��)
static int gloopFlag;

/********************************************************************/
/*	�֐���		�FhandleSignal()									*/
/*	�@�\�T�v	�F���[�v�̏I���v�����Z�b�g							*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
void
handleSignal
(
	int sig 
)
{
	gloopFlag = 0;
}

/********************************************************************/
/*	�֐���		�FsleepFunction()									*/
/*	�@�\�T�v	�F�w��b���X���[�v									*/
/* 	����		�F													*/
/*	 ��P����   �F													*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
void
sleepFunction
(
	int second
)
{
	int cnt;

	//�g���[�X���O�o��
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sleepFunction", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//�v���Z�X�̏I���v���ɑΉ����邽��
	//�P�b���ƂɃX���[�v����
	for(cnt = 0; cnt < second; cnt++)
	{
		if(gloopFlag == 0)
		{
			return;
		}

		sleep(1);
	}
}

/*:KH-------------------------------------------------------------------------*/
/*:K  �֐���   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  �@�\�T�v : �����ϐ���W�J����                                         */
/*----------------------------------------------------------------------------*/
/*:I  ����     : char    *src_cp  : �W�J�O������                              */
/*:O  �o��     : ����             : ����                                      */
/*:R  �߂�l   : char *           : �W�J�㕶����                              */
/*:C  ���L���� :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char		*src_cp;
{
static char	value[256];     			/* �W�J�㕶���� */
    char	*dst_cp;        			/* �W�J�㕶���� */
    char	buf[256];       			/* �����ϐ� */
    char	*env_cp;        			/* �����ϐ� */

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0 
                && *src_cp != ' ' && *src_cp != '\t' 
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

    return( value );
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *   	���L�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int		sFncShmCrt ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;

	//�g���[�X���O�o��
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sFncShmCrt", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//	�擾
	stcShm->shm_Id = shmget ( (key_t)stcShm->shm_Key, 
					MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
	if ( stcShm->shm_Id < 0 ) {
		//	�ُ�I��	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "���L�������̎擾(shmget)�Ɏ��s���܂����B");
		return ( RTN_NG ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
		 MYAPP_LOG_ERRCODE_APP,"���L�������̃A�^�b�`(shmat)�Ɏ��s���܂����B");
		return ( RTN_NG ) ;
	}

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "���L�������̒l�ݒ�(shmdt)�Ɏ��s���܂����B");
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *   	���L�������\����                          */
/*�@ ��Q���� �Fint *   				�l							 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int		sFncShmGet ( stcShm, pshmData )
struct		SHM		*stcShm;
int			*pshmData ;
{
	int		*shmData ;

	//�g���[�X���O�o��
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sFncShmGet", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "���L�������̑���(shmget)�Ɏ��s���܂����B");
		return ( RTN_NG ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "���L�������̑���(shmget)�Ɏ��s���܂����B");
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *   	���L�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int		sFncShmDel ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;

	//�g���[�X���O�o��
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sFncShmDel", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//	�폜	
	if ( shmctl ( stcShm->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "���L�������̑���(shmget)�Ɏ��s���܂����B");
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/********************************************************************/
/*	�֐���		�FcheckCtrljti()									*/
/*	�@�\�T�v	�F�R���g���[����ԃ`�F�b�N							*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	 ��Q����	�FCtrlkka*	pCtrlkka								*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
checkCtrljti
(
	 PENV		pEnv
	,Ctrlkka*	pCtrlkka
)
{
	/*
	*	���[�J���ϐ���`
	*/
	Ctrlijhmst		key;
	Ctrlijhmst*		arrayOut;
	int				numOut;
	int				rc;
	int				kyoyosu;
	
	//�g���[�X���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "checkCtrljti", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	memset(&key, 0, sizeof(Ctrlijhmst));
	strcpy(key.bskkbn, pCtrlkka->bskkbn);
	strcpy(key.nbkmkcd, pCtrlkka->nbkmkcd);
	strcpy(key.kaiymd, pCtrlkka->knskisymd);		// 1.01 INTEC ADD
	
	rc = FCtrlijhmstSelectByKey(&key, &arrayOut, &numOut);

	if(rc != 0){
		{
			char	buf[1024];
			memset(buf, '\0', sizeof( buf ));
			sprintf(buf, "�R���g���[���ُ픻��}�X�^�̌����Ɏ��s���܂����B"
						"���͋@�敪�F%s �������ڃR�[�h%s ret[%d]", 
					key.bskkbn, key.nbkmkcd, rc);
			mcrPutTrace(pEnv, TRCKIND_WARNING, "checkCtrljti", "", 
				MYAPP_LOG_ERRCODE_DB, buf);
		}
		
		return(rc);
	}
	
	/*
	*	�R���g���[�����ʏ��̃R���g���[����ԃR���g���[���ُ픻��}�X�^��
	*	���e�͈͊O�̏ꍇ�́A�R���g���[���ُ�ɂ���B
	*/
	kyoyosu = atoi(&arrayOut->kyuhniflg);
	if( kyoyosu < abs(pCtrlkka->ctrljti) ){
		return(CV_ABNORMAL);
	}
	
	ZbmlFree(arrayOut);
	
	return(CV_NORMAL);
}


/********************************************************************/
/*	�֐���		�FcheckSeidoKanri()									*/
/*	�@�\�T�v	�F���x�Ǘ��ُ�`�F�b�N								*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
checkSeidoKanri
(
	PENV	pEnv
)
{
	/*
	*	���[�J���ϐ���`
	*/
	Ctrlkka*		arrayOut;
	int				numOut;
	int				rc;
	int				index;
	char			buf[256];
	
	/*
	*	������
	*/
	//�g���[�X���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

/* 1.01 INTEC DELL SELECT MAX ��ini�t�@�C���ݒ��
DEL	rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, 100);
*/
	rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, pEnv->sel_Max);
	if(rc == 100){
		mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
			MYAPP_LOG_ERRCODE_NON, "�Y���f�[�^������܂���B");
		// 1.01 ADD INTEC	�O�̂��߂�free
		if( arrayOut != NULL ){
			free( arrayOut );
		}

		return(ERROR_CODE_NORMAL);
	}
	else if(rc != 0){
		//�g���[�X���O�o��

		//==> 2007.01.09 Kim Jinsuk SQLCODE �o�� 
		sprintf(buf, "SQLCODE [%d] �R���g���[�����ʏ��̌����Ɏ��s���܂���", rc);
		mcrPutTrace(pEnv, TRCKIND_ERROR, "checkSeidoKanri", "", 
			MYAPP_LOG_ERRCODE_DB,buf);
		//mcrPutTrace(pEnv, TRCKIND_ERROR, "checkSeidoKanri", "", 
		//	MYAPP_LOG_ERRCODE_DB,"�R���g���[�����ʏ��̌����Ɏ��s���܂����B");
		//<== 2007.01.09 Kim Jinsuk SQLCODE	�o��	

		// 1.01 ADD INTEC	�O�̂��߂�free
		//==> 2006.12.15 Kim Jinsuk SELECT�@���s���鎞�@����
		if( arrayOut != NULL ){
			free( arrayOut );
		}
		//<== 2006.12.15 Kim Jinsuk SELECT�@���s���鎞�@����
		
		return(rc);
	}
	
	do{
		
		for(index=0; index<numOut; index++){
			
			/*
			*	�R���g���[���ُ픻��}�X�^���A���͋@�敪�E�������ڃR�[�h��
			*	�������A���e�͈̓t���O�𔻒肷��B
			*/
			rc = checkCtrljti(pEnv, &arrayOut[index]);

			if(rc == CV_NORMAL){
				/* �`�F�b�N�ς� */
				arrayOut[index].chkzmflg	= '1';
			}
			else{
				/* �R���g���[���ُ� */
				arrayOut[index].chkzmflg	= '2';
			}
			
			// INTEC ADD DEBUG LOG OUT
//			sprintf(buf,"index[%d] --->���e�͈̓t���O���� rc[%d] flg[%c]"
//					,index,rc,arrayOut[index].chkzmflg );
//			mcrPutTrace(pEnv, TRCKIND_DEBUG, "checkSeidoKanri", "", 
//					MYAPP_LOG_ERRCODE_NON,buf );

			/* �R���g���[�����ʏ��X�V */
			rc = FCtrlUpdate(&arrayOut[index]);
			if(rc != 0){
				// 1.01 INTEC ADD LOG OUT
				memset( buf, '\0', sizeof( buf ));
				sprintf( buf, "�R���g���[�����ʏ��̍X�V�Ɏ��s���܂����B"
					"�J�n��[%s]���͋@[%s]���@[%s]����[%s]CTRLNO[%d]"
					, arrayOut[index].knskisymd	,arrayOut[index].bskkbn
					, arrayOut[index].bskgok	,arrayOut[index].kmkcd
					, arrayOut[index].ctrlno );
				mcrPutTrace(pEnv, TRCKIND_WARNING, "checkSeidoKanri", "", 
						MYAPP_LOG_ERRCODE_NON, buf );
				// mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
				//		MYAPP_LOG_ERRCODE_NON, 
				//		"�R���g���[�����ʏ��̍X�V�Ɏ��s���܂����B");

				// 1.01 INTEC DEL �P�����s���Ă��������p��
				// ZbmlFree(arrayOut);
				continue;
			}
			
			//�R�~�b�g
			ZdbCommit();
			
		}

		ZbmlFree(arrayOut);

/* 1.01 INTEC DELL		
DEL		rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, 100);
*/
		rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, pEnv->sel_Max);
		if(rc == 100){
			mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
				MYAPP_LOG_ERRCODE_NON, "�Y���f�[�^������܂���B");
			// 1.01 ADD INTEC	�O�̂��߂�free
			
			if( arrayOut != NULL ){
				free( arrayOut );
			}
			break;
		}
		else if(rc != 0){

			//==> 2007.01.09 Kim Jinsuk SQLCODE �o��
			//�g���[�X���O�o��
			sprintf(buf, "SQLCODE [%d] �R���g���[�����ʏ��̌����Ɏ��s���܂����B", rc);
			mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
				MYAPP_LOG_ERRCODE_NON, buf); 
			
			//mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
			//	MYAPP_LOG_ERRCODE_NON, 
			//	"�R���g���[�����ʏ��̌����Ɏ��s���܂����B");
			// 1.01 ADD INTEC	�O�̂��߂�free
			//<== 2007.01.09 Kim Jinsuk SQLCODE �o��

			//==> 2006.12.15 Kim Jinsuk SELECT ���s����Ƃ��@����
			if( arrayOut != NULL ){
				free( arrayOut );
			}
			//<== 2006.12.15 Kim Jinsuk SELECT ���s����Ƃ��@����

			return(rc);
		}

	} while(!rc);

	// 1.01 ADD INTEC	�O�̂��߂�free
	if( arrayOut != NULL ){
		free( arrayOut );
	}

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	�֐���		�FinitFunction()									*/
/*	�@�\�T�v	�F����������										*/
/* 	����		�F													*/
/*	 ��P����   �Fint		argc	�p�����[�^��					*/
/*	 ��Q����	�Fchar**	argv	�p�����[�^�l					*/
/*	 ��R����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
initFunction
(
	 int	argc
	,char**	argv
	,PENV	pEnv
)
{
	/*
	*	���[�J���ϐ���`
	*/
	int		rc;
	char	tmp[12];

	/*
	*	������
	*/

	//�v���O�����Ǘ��\���̏�����
	memset(pEnv, 0, sizeof(ENV));

	//���O�t�@�C���I�[�v��
	//rc = ZbmlOpenLog( LOGINIFILE );
	rc = ZbmlOpenLog( EnvRef(LOGINIFILE) );
	if(rc != 0)
	{
		return(ERROR_CODE_LOG_OPEN_ERROR);
	}
	
	//���O��񏉊����ݒ�
    memset(&pEnv->stLogMem, '\0', sizeof(pEnv->stLogMem)) ;
	
	//�v���O�������Z�b�g
	strcpy(pEnv->stLogMem.pcAppName, APP_NAME);

	//�v���O�����J�n���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "���x�Ǘ��ُ�`�F�b�N�����N��");

	//�R�}���h���C�������`�F�b�N
	//	����2�����Ƀp�����[�^�t�@�C���̃p�X�����͂���Ă��Ȃ���΃G���[
	if(argc != 2)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�R�}���h���C���������s���ł��B");
		return(ERROR_CODE_CMD_PRM_ERROR);
	}

	//�p�����[�^�t�@�C���I�[�v��
	pEnv->bp = ZbmlPrmOpen(argv[1]) ;
	if(pEnv->bp == NULL)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
		 MYAPP_LOG_ERRCODE_NON,"�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_OPEN_ERROR);
	}
	
	/*
	*	�p�����[�^�擾
	*/
	
	//�f�[�^�x�[�X���擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_NAME, pEnv->cDbName) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//�c�a���[�U�h�c�擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_USER_ID, pEnv->cDbUserId) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//�c�a�p�X���[�h�擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_PASSWORD, pEnv->cDbPassword) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//�X���[�v����(�b)���擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_SLEEP_SEC, tmp) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	//�X���[�v
	pEnv->sleepInterval = atoi(tmp);
	
	// 1.01 SHM_KEY GET
	if(ZbmlPrmGetVal(pEnv->bp, PRM_SHM_KEY, tmp) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	// SHM_KEY
	pEnv->shm_Key = atoi(tmp);
	
	// 1.01 �R���g���[�����ʏ��@SELECT�ő匏��
	if(ZbmlPrmGetVal(pEnv->bp, PRM_SEL_MAX, tmp) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	// SEL_MAX
	pEnv->sel_Max = atoi(tmp);
	
	//�p�����[�^�t�@�C���N���[�Y	
	ZbmlPrmClose(pEnv->bp);

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	�֐���		�FmainFunction()									*/
/*	�@�\�T�v	�F���C������										*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
mainFunction
(
	PENV	pEnv
)
{
	/*
	*	���[�J���ϐ���`
	*/
	int		rc;
	struct  SHM stcShm;                 // 1.01 �I�����f���L������
    int     li_stopFlg = 0;             // 1.01 �I�����f

	//�g���[�X���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "mainFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "Start Function.");
	
	/*
	*	������
	*/
	
    // 1.01 ���L����������
	stcShm.shm_Key = pEnv->shm_Key;
    if( sFncShmCrt ( &stcShm ) < 0 ) {
		char ebuf[10];
		sprintf( ebuf, "shmkey[%d]", errno );
		mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
			ebuf);
		mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
			"���L�����������Ɏ��s���܂����B");
        return( ERROR_FUNC_ERROR );
    }
	
	/* 1.01 INTEC ADD  DB CONNECT�� FOR���̊O�Ŏ��s
	*	�f�[�^�x�[�X�ڑ�
	*/
	rc = ZdbConnect(pEnv->cDbName, pEnv->cDbUserId, pEnv->cDbPassword);
	if(rc != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
			"�f�[�^�x�[�X�̐ڑ��Ɏ��s���܂����B");
		return(ERROR_CODE_DB_CONNECT_ERROR);
	}

	/*
	*	���x�Ǘ��ُ�`�F�b�N����
	*/
	//���[�v����p�̃t���O��(1:���s���ɃZ�b�g)
	gloopFlag = 1;
	//�V�O�i���n���h�����Z�b�g
	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);

	
	while(gloopFlag)
	{

		/* 1.01 INTEC DELL
		*	�f�[�^�x�[�X�ڑ�
		*/
		// rc = ZdbConnect(pEnv->cDbName, pEnv->cDbUserId, pEnv->cDbPassword);
		// if(rc != 0)
		// {
		// 	mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
		// 		"�f�[�^�x�[�X�̐ڑ��Ɏ��s���܂����B");
		// 	return(ERROR_CODE_DB_CONNECT_ERROR);
		//}

		//���x�Ǘ��ُ�`�F�b�N
		rc = checkSeidoKanri(pEnv);
		if(rc)
		{

			//==> Test Code 2006.12.15 Kim Jinsuk SELECT ���s����Ƃ�����
			//mcrPutTrace(pEnv, TRCKIND_ERROR, "mainFunction", "", 
			//	MYAPP_LOG_ERRCODE_NON,  
			//	"����B�B�B�B�G���[");
			//<== Test Code 2006.12.15 Kim Jinsuk SELECT���s����Ƃ�����

			//���[���o�b�N
			ZdbRollback();

			mcrPutTrace(pEnv, TRCKIND_ERROR, "mainFunction", "", 
				MYAPP_LOG_ERRCODE_NON,  
				"���x�Ǘ��ُ�`�F�b�N�����Ɏ��s���܂����B");

			
			return(ERROR_FUNC_ERROR);

		}
		
		//�R�~�b�g
		// 1.01 INTEC DELL	commit ��checkSeidoKanri���Ŏ��{
		// ZdbCommit();

		//�f�[�^�x�[�X�ؒf
/* 1.01 INTEC DELL	DISCONNECT �� ���߂�FOR���̊O�Ŏ��s
DEL		ZdbDisConnect();
*/

		// 1.01 INTEC ADD STA
        //------------------
        // �I�����f
        //------------------
            // ���L�������擾
        if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
			mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
				"���L�������擾�Ɏ��s���܂����B");
            break;
        }
        if( li_stopFlg == 1 ){
            // TRACE
			mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
				"�I���w�����o�����߁A�������I�����܂��B");
            break;
        }
		// 1.01 INTEC ADD END

		sleepFunction(pEnv->sleepInterval);
	}

	// 1.01 INTEC ADD �f�[�^�x�[�X�ؒf
	ZdbDisConnect();

	//  1.01 INTEC ADD ���L�������폜
	sFncShmDel ( &stcShm ) ;

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	�֐���		�FendFunction()										*/
/*	�@�\�T�v	�F�I������											*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
endFunction
(
	PENV	pEnv
)
{
	/*
	*	���[�J���ϐ���`
	*/

	//�g���[�X���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "endFunction", "", MYAPP_LOG_ERRCODE_NON,  "Start Function.");

	/*
	*	������
	*/

	// 1.01 INTEC ADD LOG CLOSE
	ZbmlCloseLog( );

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	�֐���		�Fmain()											*/
/*	�@�\�T�v	�F�����Z���������C��								*/
/* 	����		�F													*/
/*	 ��P����   �Fint		argc	�p�����[�^��					*/
/*	 ��Q����	�Fchar**	argv	�p�����[�^�l					*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F1�ȏ�													*/
/********************************************************************/
int 
main
(
	 int	argc
	,char** argv
)
{
	/*
	*	���[�J���ϐ���`
	*/
	ENV		Env;	
	int		rc;

	/*
	*	����������
	*/
	rc = initFunction(argc, argv, &Env);
	if(rc != ERROR_CODE_NORMAL)
	{
		fprintf(stderr, "jidokousei : Error initFunction [%d]\n", rc);
		return(rc);
	}

	// 1.01 INTEC ADD
	// 		.sqc�ɍ\���̂�n������
	memcpy( &stEnv,	&Env, sizeof( ENV ));

	/*
	*	���C������
	*/
	rc = mainFunction(&Env);
	if(rc != ERROR_CODE_NORMAL)
	{
		//�f�[�^�x�[�X�ؒf
		ZdbDisConnect();
		fprintf(stderr, "jidokousei : Error mainFunction [%d]\n", rc);
		return(rc);
	}
	
	/*
	*	�I������
	*/
	rc = endFunction(&Env);
	if(rc != ERROR_CODE_NORMAL)
	{
		fprintf(stderr, "jidokousei : Error endFunction [%d]\n", rc);
		return(rc);
	}

	return(ERROR_CODE_NORMAL);
}
/** End of File ***************************************************************/
