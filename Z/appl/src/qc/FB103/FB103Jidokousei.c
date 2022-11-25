/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FFB103Jidokousei.c								*/
/*		�T�v		�F�����Z������									*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		J.Iijima		Create					*/
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include "FB103Jidokousei.h"

/********************************************************************/
/*	�֐���		�FkekkaUpdate()										*/
/*	�@�\�T�v	�F�������ʏ��X�V									*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv		�v���O�����Ǘ��\����		*/
/*	 ��Q����   �FCtrlkka*	pCtrlkka	�R���g���[�����ʊǗ����	*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
kekkaUpdate
(
	 PENV		pEnv
	,Ctrlkka*	pCtrlkka
)
{
	/*
	*	���[�J���ϐ���`
	*/
	Kekka		key;
	Kekka*		arrayOut;
	int			numOut;
	int			index;
	int			rc;
	double		factor;
	double		base;
	double		kouiseiKekka;

	//�v���O�����J�n���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_NON,  "Start Function");

	/*
	*	������
	*/
	factor	= atof(pCtrlkka->facter);	
	base	= atof(pCtrlkka->base); 


	/*
	*	�������ʏ��X�V����
	*/
	
	//�����������Z�b�g
	memset(&key, 0, sizeof(Kekka));
	strcpy(key.knskisymd, pCtrlkka->knskisymd);
	strcpy(key.knsgrp, pCtrlkka->knsgrp);
	strcpy(key.kmkcd, pCtrlkka->kmkcd);
	strcpy(key.bskkbn, pCtrlkka->bskkbn);
	strcpy(key.bsklne, pCtrlkka->bsklne);
	strcpy(key.bskgok, pCtrlkka->bskgok);
	key.bskseq = pCtrlkka->bskseq;
	key.ctrlno = pCtrlkka->ctrlno;

	//�������ʏ�������
	rc = FKekkaSelectByKey(&key, &arrayOut, &numOut);
	if(rc == HRC_SQL_NOT_FOUND)
	{
		//�Y���f�[�^�������ꍇ
		mcrPutTrace(pEnv, TRCKIND_TRACE, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_NON,  "�����Z���Ώۂ̃f�[�^�͂���܂���B");
		return(ERROR_CODE_NORMAL);

	}
	else if(rc != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_DB,  "�������ʏ��̌����Ɏ��s���܂����B");
		return(ERROR_DB_ERROR);
	}
	
	for(index = 0; index < numOut; index++)
	{
		//�Z�����ʂ��v�Z
		//	�R���g���[�����ʏ��̃t�@�N�^�[ �~ �������ʏ��̐��f�[�^ �{ �R���g���[�����ʏ��̃x�[�X
		kouiseiKekka = factor * atof(arrayOut[index].rawdata) + base;

		//�������ʏ����X�V
		snprintf(arrayOut[index].knskka1, 12, "%f", kouiseiKekka);
		rc = FKnskkaUpdate(&arrayOut[index]);
		if(rc != 0)
		{
			mcrPutTrace(pEnv, TRCKIND_ERROR, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_DB,  "�������ʏ��̍X�V�Ɏ��s���܂����B");
			ZbmlFree(arrayOut);
			return(ERROR_DB_ERROR);
		}
	}

	ZbmlFree(arrayOut);

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	�֐���		�FctrlknrUpdate()									*/
/*	�@�\�T�v	�F�R���g���[���Ǘ����X�V							*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv		�v���O�����Ǘ��\����		*/
/*	 ��Q����   �FCtrlkka*	pCtrlkka	�R���g���[�����ʊǗ����	*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
ctrlknrUpdate
(
	 PENV		pEnv
	,Ctrlkka*	pCtrlkka
)
{
	/*
	*	���[�J���ϐ���`
	*/
	Ctrlknr		key;
	int			rc;

	//�g���[�X�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "ctrlknrUpdate", "", MYAPP_LOG_ERRCODE_NON,  "Start Function");

	/*
	*	�R���g���[���Ǘ����X�V����
	*/
	
	//�����������Z�b�g
	memset(&key, 0, sizeof(Ctrlknr));
	strcpy(key.knskisymd, pCtrlkka->knskisymd);
	strcpy(key.bskkbn, pCtrlkka->bskkbn);
	strcpy(key.bskgok, pCtrlkka->bskgok);
	key.ctrlno = pCtrlkka->ctrlno;

	//�X�V
	rc = FKtflgUpdate(&key);
	if(rc != 0 && rc != HRC_SQL_NOT_FOUND)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "ctrlknrUpdate", "", MYAPP_LOG_ERRCODE_DB,  "�R���g���[���Ǘ����̍X�V�Ɏ��s���܂����B");
		return(ERROR_DB_ERROR);
	}

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	�֐���		�FjidouKousei()										*/
/*	�@�\�T�v	�F�����Z������										*/
/* 	����		�F													*/
/*	 ��P����   �FPENV		pEnv	�v���O�����Ǘ��\����			*/
/*	�o��		�F													*/
/*   ����F0														*/
/*	 �ُ�F0�ȊO													*/
/********************************************************************/
int
jidouKousei
(
	PENV	pEnv
)
{
	/*
	*	���[�J���ϐ���`
	*/
	Ctrlkka*	arrayOut;
	int			numOut;
	int			index;
	int			rc;

	//�g���[�X�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "jidouKousei", "", MYAPP_LOG_ERRCODE_NON,  "Start Function");

	/*
	*	������
	*/
	
	/*
	*	�R���g���[�����ʏ��e�[�u������
	*/
	rc = FCtrlkkkaSelectAll(&arrayOut, &numOut);
	if(rc == HRC_SQL_NOT_FOUND)
	{
		//�Y���f�[�^�������ꍇ
		mcrPutTrace(pEnv, TRCKIND_TRACE, "jidouKousei", "", MYAPP_LOG_ERRCODE_NON,  "�����Z���Ώۂ̃f�[�^�͂���܂���B");
		return(ERROR_CODE_NORMAL);

	}
	else if(rc != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "jidouKousei", "", MYAPP_LOG_ERRCODE_DB,  "�R���g���[�����̌����Ɏ��s���܂����B");
		return(ERROR_DB_ERROR);
	}

	/*
	*	�Z�����X�V
	*/
	for(index = 0; index < numOut; index++)
	{
		//�������ʏ����X�V
		rc = kekkaUpdate(pEnv, &arrayOut[index]);
		if(rc != 0)
		{
			ZbmlFree(arrayOut);
			return(rc);		
		}

		//�R���g���[���Ǘ��e�[�u���X�V
		rc = ctrlknrUpdate(pEnv, &arrayOut[index]);
		if(rc != 0)
		{
			ZbmlFree(arrayOut);
			return(rc);		
		}

		//�R���g���[�����ʏ��e�[�u���X�V
		rc = FKsidhUpdate(&arrayOut[index]);
		if(rc != 0)
		{
			ZbmlFree(arrayOut);
			return(rc);		
		}
	}

	ZbmlFree(arrayOut);

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


	/*
	*	������
	*/

	//�v���O�����Ǘ��\���̏�����
	memset(pEnv, 0, sizeof(ENV));

	//���O�t�@�C���I�[�v��
	rc = ZbmlOpenLog(LOGINIFILE);
	if(rc != 0)
	{
		return(ERROR_CODE_LOG_OPEN_ERROR);
	}
	
	//���O��񏉊����ݒ�
    memset(&pEnv->stLogMem, '\0', sizeof(pEnv->stLogMem)) ;
	
	//�v���O�������Z�b�g
	strcpy(pEnv->stLogMem.pcAppName, APP_NAME);

	//�v���O�����J�n���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "�����Z�������N��");

	//�R�}���h���C�������`�F�b�N
	//	����2�����Ƀp�����[�^�t�@�C���̃p�X�����͂���Ă��Ȃ���΃G���[
	if(argc != 2)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "�R�}���h���C���������s���ł��B");
		return(ERROR_CODE_CMD_PRM_ERROR);
	}

	//�p�����[�^�t�@�C���I�[�v��
	pEnv->bp = ZbmlPrmOpen(argv[1]) ;
	if(pEnv->bp == NULL)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_OPEN_ERROR);
	}
	
	/*
	*	�p�����[�^�擾
	*/
	
	//�f�[�^�x�[�X���擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_NAME, pEnv->cDbName) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//�c�a���[�U�h�c�擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_USER_ID, pEnv->cDbUserId) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//�c�a�p�X���[�h�擾
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_PASSWORD, pEnv->cDbPassword) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "�p�����[�^�̎擾�Ɏ��s���܂����B");
		return(ERROR_CODE_PRM_GET_ERROR);
	}

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

	//�g���[�X���O�o��
	mcrPutTrace(pEnv, TRCKIND_TRACE, "mainFunction", "T", MYAPP_LOG_ERRCODE_NON,  "Start Function.");
	
	/*
	*	������
	*/
	
	
	/*
	*	�����Z������
	*/
	rc = jidouKousei(pEnv);
	if(rc)
	{
		//���[���o�b�N
		ZdbRollback();

		mcrPutTrace(pEnv, TRCKIND_ERROR, "mainFunction", "", MYAPP_LOG_ERRCODE_NON,  "�����Z�������Ɏ��s���܂����B");
		return(ERROR_FUNC_ERROR);
	}
	
	//�R�~�b�g
	ZdbCommit();

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

	/*
	*	�f�[�^�x�[�X�ڑ�
	*/
	rc = ZdbConnect(Env.cDbName, Env.cDbUserId, Env.cDbPassword);
	if(rc != 0)
	{
		mcrPutTrace(&Env, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,  "�f�[�^�x�[�X�̐ڑ��Ɏ��s���܂����B");
		return(ERROR_CODE_DB_CONNECT_ERROR);
	}

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
	//�f�[�^�x�[�X�ؒf
	ZdbDisConnect();
	
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
