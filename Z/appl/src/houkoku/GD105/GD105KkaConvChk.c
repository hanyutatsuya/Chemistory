/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD105KkaConvChk.c								*/
/*		�T�v		�F���ʕ񍐃t�@�C���쐬����						*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  2.00    2009/05/19      K.Moriya        ���ʕϊ��}�X�^�Ή�      */
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <time.h>
#include <errno.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "GD105Main.h"
#include "GD105KkaConvChk.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
struct stcLogMember	gstLogMem;


/******************************************************************************/
/*�@�� �� ���@�FGD105KkaConvChk()											  */
/*�@�@�\�T�v�@�F���ʕϊ��`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKekka		*pKekka			���ʏ��\����					  */
/*�@�@��Q�����FKkaconvmst	*pKkaconvmst	���ʕϊ��}�X�^�\����			  */
/*�@�@��R�����Fchar		*pSstcd			�{�݃R�[�h						  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	 : ����I��(0)									  */
/*�@�@�@�@�@�@		RTN_NG	 : �ُ�I��(-1)									  */
/*�@�@�@�@�@�@		RTN_SKIP : �����X�L�b�v(-2)								  */
/******************************************************************************/
int GD105KkaConvChk(Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pSstcd)
{
	Kanjya		keyKanjya;				/* ���ҏ��\����                           */
	Kanjya		*pKanjya = NULL;		/* ���ҏ��\����                           */
	Kenzok		keyKenzok;				/* ���̑������\����                       */
	Kenzok		*pKenzok = NULL;		/* ���̑������\����                       */
//	Kkaconvmst	keyKkaconvmst;			/* ���ʕϊ��}�X�^�\����                     */
	Kkaconvknr	sKkaconvknr;			/* ���ʕϊ��Ǘ����\����                   */
	Kkaconvknr	*pKkaconvknr = NULL;	/* ���ʕϊ��Ǘ����\����                   */
	KekkaConv	sKekkaConv;				/* ���ʕϊ��X�V�p�\����                     */
	KekkaConv	*pKekkaConv = NULL;		/* ���ʕϊ��X�V�p�\����                     */
	int			iRet;					/* �e��`�F�b�N���^�[���l                   */
	int			iRetKbn;				/* �敪�L��̍��ڃ`�F�b�N���^�[���l(�敪�p) */
	int			iRetChk;				/* �`�F�b�N���ʒl                           */
	int			iMstChkCnt = 0;			/* �}�X�^�̃`�F�b�N���ڐ�                   */
	int			numOut;					/* SQL�����p                                */
	char		tmp[32+1];				/* �������ꎞ�ޔ�p�ϐ�                     */
	char		cShiki0;				/* �������̓�1�o�C�g��                      */
	char		cDtnrtts[8+1];			/* �f�[�^���͒S���җp�ϐ�                   */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105KkaConvChk - �J�n" );
#endif
	/**************************************************************/
	/* SQL�pKEY���ݒ�                                           */
	/**************************************************************/
	/* �f�[�^���͒S����   */
	memset(cDtnrtts, 0, sizeof(cDtnrtts));
	strcpy(cDtnrtts, "GD105CNV");

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� �f�[�^���͒S����" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cDtnrtts = [%s]", cDtnrtts );
#endif

	/* ���ҏ��L�[       */
	memset(&keyKanjya, 0, sizeof(Kanjya));
	strcpy(keyKanjya.utkymd, pKekka->utkymd);			/* ��t��       */
	strcpy(keyKanjya.irino, pKekka->irino);				/* �˗���No     */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� ���ҏ��L�[" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKanjya.utkymd  = [%s]", keyKanjya.utkymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKanjya.irino   = [%s]", keyKanjya.irino );
#endif

	/* ���̑������L�[   */
	memset(&keyKenzok, 0, sizeof(Kenzok));
	strcpy(keyKenzok.sriymd, pKekka->sriymd);			/* ������       */
	strcpy(keyKenzok.kntno, pKekka->kntno);				/* ����No       */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� ���̑������L�[" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKenzok.sriymd  = [%s]", keyKenzok.sriymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKenzok.kntno   = [%s]", keyKenzok.kntno );
#endif

//	memset(&keyKkaconvmst, 0, sizeof(Kkaconvmst));
//	strcpy(keyKkaconvmst.knsgrp, pKekka->knsgrp);		/* �����O���[�v */
//	strcpy(keyKkaconvmst.kmkcd, pKekka->kmkcd);			/* ���ڃR�[�h   */
//	strcpy(keyKkaconvmst.sstcd, pKekka->sstcd);			/* �{�݃R�[�h   */
//	strcpy(keyKkaconvmst.kaiymd, pKekka->knskisymd);	/* �����J�n��   */

#ifdef _DEBUG
	/* ���ʏ��L�[ */
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� ���ʏ��L�[" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->knskisymd = [%s]", pKekka->knskisymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->kntno     = [%s]", pKekka->kntno );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->knsgrp    = [%s]", pKekka->knsgrp );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->kmkcd     = [%s]", pKekka->kmkcd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->knssu     = [%d]", pKekka->knssu );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->sstcd     = [%s]", pKekka->sstcd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pSstcd            = [%s]", pSstcd );
#endif

	/**************************************************************/
	/* ���擾                                                   */
	/**************************************************************/
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� �ŐV��������̊��ҏ��擾�֐�" );
#endif

	/* �ŐV��������̊��ҏ��擾�֐� */
	/* �� �󂯓��A�˗���No�ōŐV��������No�̊��ҏ����擾����B  */
	iRet = dGD105_KANJYA_Sel_latestZSSDINO( &keyKanjya, &pKanjya, &numOut );
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    dGD105_KANJYA_Sel_latestZSSDINO iRet = [%d]", iRet );
#endif
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND )
	{
		//�ُ�I��
		//���O�o��
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KANJYA_Sel_latestZSSDINO ERROR [%d]", iRet );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		return RTN_NG;
	}
	/* �������ʂ�0���̏ꍇ�A���ʕϊ����������̏����ɏ悹��B(�t�@�C���쐬�֍s��) */
	else if (numOut == 0)
	{
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KANJYA_Sel_latestZSSDINO - Not Found" );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		return RTN_SKIP;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    KANJYA numOut = [%d]", numOut );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� �ŐV��������̌��̑������擾�֐�" );
#endif

	/* �ŐV��������̌��̑������擾�֐� */
	/* �� �������A����No�ōŐV��������No�̌��̑��������擾����B */
	iRet = dGD105_KENZOK_Sel_latestZSSDINO( &keyKenzok, &pKenzok, &numOut );
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    dGD105_KENZOK_Sel_latestZSSDINO iRet = [%d]", iRet );
#endif
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND )
	{
		//�ُ�I��
		//���O�o��
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KENZOK_Sel_latestZSSDINO ERROR [%d]", iRet );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_NG;
	}
	/* �������ʂ�0���̏ꍇ�A���ʕϊ����������̏����ɏ悹��B(�t�@�C���쐬�֍s��) */
	else if (numOut == 0)
	{
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KENZOK_Sel_latestZSSDINO - Not Found" );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    KENZOK numOut = [%d]", numOut );
#endif


	/**************************************************************/
	/*                                                            */
	/* �e��f�[�^�`�F�b�N                                         */
	/*                                                            */
	/**************************************************************/

	/* �� ���ʋ敪�`�F�b�N �� */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ������ ���ʋ敪�`�F�b�N ������" );
#endif

	memset(tmp, 0, sizeof(tmp));
	if (pKkaconvmst->sbtkbn != GD105_DATA_SPACE)
	{
		tmp[0] = pKkaconvmst->sbtkbn;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->sbtkbn ==> tmp = [%s]", tmp );
#endif

	/* ������ GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* �`�F�b�N�������͂���̏ꍇ */
	if ( strlen(tmp) != 0 )
	{
		/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
		iMstChkCnt++;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->sbtkbn     = [%c]", pKanjya->sbtkbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->sbtkbn = [%c]", pKkaconvmst->sbtkbn );
#endif

		/* �`�F�b�N�֐���Return�l��ݒ�                   */
		/* �`�F�b�N�Ώ�  �FiRetChk == GD105_CONVCHK_OK(1) */
		/* �`�F�b�N�ΏۊO�FiRetChk == GD105_CONVCHK_NG(0) */
		iRetChk = GD105ConvChkSbtkbn( pKanjya->sbtkbn, tmp[0] );
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���������������������������������������� GD105ConvChkSbtkbn iRetChk = [%d]", iRetChk );
#endif

	/* �����܂łŏ�����HIT���Ȃ��ꍇ�A���̃`�F�b�N�����𔲂��� */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105ConvChkSbtkbn - HIT���Ȃ��̂� Return�I�I" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* �� �N��`�F�b�N �� */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ������ �N��`�F�b�N ������" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->age);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->age ==> tmp = [%s]", tmp );
#endif

	/* ������ GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* �`�F�b�N�������͂���̏ꍇ */
	if (strlen(tmp) != 0)
	{
		/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') ���ǂ������f����ׂɑޔ� */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0          = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->age     = [%s]", pKanjya->age );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->age = [%s]", pKkaconvmst->age );
#endif

		/* �`�F�b�N�֐���Return�l��ݒ�                   */
		/* �`�F�b�N�Ώ�  �FiRet == GD105_CONVCHK_OK(1) */
		/* �`�F�b�N�ΏۊO�FiRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkAge( pKanjya->age, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���������������������������������������� GD105ConvChkAge iRet = [%d]", iRet );
#endif

		/* �� �N��敪�`�F�b�N �� */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ������ �N��敪�`�F�b�N ������" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->agekbn != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->agekbn;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->agekbn ==> tmp = [%s]", tmp );
#endif

		/* �`�F�b�N�������͂���̏ꍇ */
		if ( strlen(tmp) != 0 )
		{
			/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKanjya->agekbn     = [%c]", pKanjya->agekbn );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->agekbn = [%c]", pKkaconvmst->agekbn );
#endif

			/* �`�F�b�N�֐���Return�l��ݒ�                   */
			/* �`�F�b�N�Ώ�  �FiRetKbn == GD105_CONVCHK_OK(1) */
			/* �`�F�b�N�ΏۊO�FiRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkAgekbn( pKanjya->agekbn, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"���������������������������������������� GD105ConvChkAgekbn iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"�A"!=" �̏ꍇ�� NAND���Z(AND���Z�̔��])���� */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"�A"=="�A"<<"�A">>"�A"<="�A">="�̏ꍇ�� AND���Z���� */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���������������������������������������� GD105ConvChkAge & Agekbn iRetChk = [%d]", iRetChk );
#endif

	/* �����܂łŏ�����HIT���Ȃ��ꍇ�A���̃`�F�b�N�����𔲂��� */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105ConvChkAge & Agekbn - HIT���Ȃ��̂� Return�I�I" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* �� �g���`�F�b�N �� */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ������ �g���`�F�b�N ������" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->sc);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->sc ==> tmp     = [%s]", tmp );
#endif

	/* ������ GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* �`�F�b�N�������͂���̏ꍇ */
	if (strlen(tmp) != 0)
	{
		/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
		iMstChkCnt++;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->sc     = [%s]", pKanjya->sc );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->sc = [%s]", pKkaconvmst->sc );
#endif

		/* �`�F�b�N�֐���Return�l��ݒ�                   */
		/* �`�F�b�N�Ώ�  �FiRet == GD105_CONVCHK_OK(1) */
		/* �`�F�b�N�ΏۊO�FiRet == GD105_CONVCHK_NG(0) */
		iRetChk = GD105ConvChkSc( pKanjya->sc, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���������������������������������������� GD105ConvChkSc iRetChk = [%d]", iRetChk );
#endif
	}

	/* �����܂łŏ�����HIT���Ȃ��ꍇ�A���̃`�F�b�N�����𔲂��� */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105ConvChkSc - HIT���Ȃ��̂� Return�I�I" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* �� �̏d�`�F�b�N �� */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ������ �̏d�`�F�b�N ������" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->tj);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->tj ==> tmp = [%s]", tmp );
#endif

	/* ������ GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* �`�F�b�N�������͂���̏ꍇ */
	if (strlen(tmp) != 0)
	{
		/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') ���ǂ������f����ׂɑޔ� */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0         = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->tj     = [%s]", pKanjya->tj );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tj = [%s]", pKkaconvmst->tj );
#endif

		/* �`�F�b�N�֐���Return�l��ݒ�                   */
		/* �`�F�b�N�Ώ�  �FiRet == GD105_CONVCHK_OK(1) */
		/* �`�F�b�N�ΏۊO�FiRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkTj( pKanjya->tj, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���������������������������������������� GD105ConvChkTj iRet = [%d]", iRet );
#endif

		/* �� �̏d�敪�`�F�b�N �� */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ������ �̏d�敪�`�F�b�N ������" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->tjtni != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->tjtni;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tjtni ==> tmp = [%s]", tmp );
#endif

		/* �`�F�b�N�������͂���̏ꍇ */
		if ( strlen(tmp) != 0 )
		{
			/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKanjya->tjtni     = [%c]", pKanjya->tjtni );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->tjtni = [%c]", pKkaconvmst->tjtni );
#endif

			/* �`�F�b�N�֐���Return�l��ݒ�                   */
			/* �`�F�b�N�Ώ�  �FiRetKbn == GD105_CONVCHK_OK(1) */
			/* �`�F�b�N�ΏۊO�FiRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkTjtni( pKanjya->tjtni, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"���������������������������������������� GD105ConvChkTjtni iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"�A"!=" �̏ꍇ�� NAND���Z(AND���Z�̔��])���� */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"�A"=="�A"<<"�A">>"�A"<="�A">="�̏ꍇ�� AND���Z���� */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���������������������������������������� GD105ConvChkTj & Tjtni iRetChk = [%d]", iRetChk );
#endif

	/* �����܂łŏ�����HIT���Ȃ��ꍇ�A���̃`�F�b�N�����𔲂��� */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105ConvChkTj & Tjtni - HIT���Ȃ��̂� Return�I�I" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* �� �~�A���ԃ`�F�b�N �� */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ������ �~�A���ԃ`�F�b�N ������" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->tntme);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->tntme ==> tmp  = [%s]", tmp );
#endif

	/* ������ GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* �`�F�b�N�������͂���̏ꍇ */
	if (strlen(tmp) != 0)
	{
		/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') ���ǂ������f����ׂɑޔ� */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0            = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKenzok->tntme     = [%s]", pKenzok->tntme );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tntme = [%s]", pKkaconvmst->tntme );
#endif

		/* �`�F�b�N�֐���Return�l��ݒ�                */
		/* �`�F�b�N�Ώ�  �FiRet == GD105_CONVCHK_OK(1) */
		/* �`�F�b�N�ΏۊO�FiRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkTntme( pKenzok->tntme, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���������������������������������������� GD105ConvChkTntme iRet = [%d]", iRet );
#endif

		/* �� �~�A���ԋ敪�`�F�b�N �� */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ������ �~�A���ԋ敪�`�F�b�N ������" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->tntni != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->tntni;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tntni ==> tmp = [%s]", tmp );
#endif

		/* �`�F�b�N�������͂���̏ꍇ */
		if ( strlen(tmp) != 0 )
		{
			/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKenzok->tntni     = [%c]", pKenzok->tntni );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->tntni = [%c]", pKkaconvmst->tntni );
#endif

			/* �`�F�b�N�֐���Return�l��ݒ�                   */
			/* �`�F�b�N�Ώ�  �FiRetKbn == GD105_CONVCHK_OK(1) */
			/* �`�F�b�N�ΏۊO�FiRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkTntni( pKenzok->tntni, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"���������������������������������������� GD105ConvChkTntni iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"�A"!=" �̏ꍇ�� NAND���Z(AND���Z�̔��])���� */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"�A"=="�A"<<"�A">>"�A"<="�A">="�̏ꍇ�� AND���Z���� */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���������������������������������������� GD105ConvChkTn & Tntni iRetChk = [%d]", iRetChk );
#endif

	/* �����܂łŏ�����HIT���Ȃ��ꍇ�A���̃`�F�b�N�����𔲂��� */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105ConvChkTn & Tntni - HIT���Ȃ��̂� Return�I�I" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* �� �~�A�ʃ`�F�b�N �� */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ������ �~�A�ʃ`�F�b�N ������" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->tnryo);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->tnryo ==> tmp  = [%s]", tmp );
#endif

	/* ������ GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* �`�F�b�N�������͂���̏ꍇ */
	if (strlen(tmp) != 0)
	{
		/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') ���ǂ������f����ׂɑޔ� */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0            = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKenzok->tnryo     = [%s]", pKenzok->tnryo );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tnryo = [%s]", pKkaconvmst->tnryo );
#endif

		/* �`�F�b�N�֐���Return�l��ݒ�                   */
		/* �`�F�b�N�Ώ�  �FiRet == GD105_CONVCHK_OK(1) */
		/* �`�F�b�N�ΏۊO�FiRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkTnryo( pKenzok->tnryo, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���������������������������������������� GD105ConvChkTnryo iRet = [%d]", iRet );
#endif

		/* �� �~�A�ʋ敪�`�F�b�N �� */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ������ �~�A�ʋ敪�`�F�b�N ������" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->tnryotni != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->tnryotni;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tnryotni ==> tmp = [%s]", tmp );
#endif

		/* �`�F�b�N�������͂���̏ꍇ */
		if ( strlen(tmp) != 0 )
		{
			/* �}�X�^�Ƀ`�F�b�N�������͂���Ȃ̂ŃC���N�������g */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKenzok->tnryotni     = [%c]", pKenzok->tnryotni );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->tnryotni = [%c]", pKkaconvmst->tnryotni );
#endif

			/* �`�F�b�N�֐���Return�l��ݒ�                   */
			/* �`�F�b�N�Ώ�  �FiRetKbn == GD105_CONVCHK_OK(1) */
			/* �`�F�b�N�ΏۊO�FiRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkTnryotni( pKenzok->tnryotni, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"���������������������������������������� GD105ConvChkTnryotni iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"�A"!=" �̏ꍇ�� NAND���Z(AND���Z�̔��])���� */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"�A"=="�A"<<"�A">>"�A"<="�A">="�̏ꍇ�� AND���Z���� */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���������������������������������������� GD105ConvChkTnryo & Tnryotni iRetChk = [%d]", iRetChk );
#endif

	/* �����܂łŏ�����HIT���Ȃ��ꍇ�A���̃`�F�b�N�����𔲂��� */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105ConvChkTnryo & Tnryotni - HIT���Ȃ��̂� Return�I�I" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/**************************************************************/
	/*                                                            */
	/* ���ʃR�����g��                                             */
	/* �� �����܂Ń`�F�b�N��ʂ��Ă����ꍇ�́A�X�V�Ώ�            */
	/*    �������A1���`�F�b�N��ʂ��ĂȂ�����(iMstChkCnt = 0)   */
	/*    �͑ΏۊO                                                */
	/*                                                            */
	/**************************************************************/
	/* ���Ȃ��Ƃ�1�̓`�F�b�N��ʂ��Ă����ꍇ */
	if (iMstChkCnt > 0)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� ���ʃR�����g�������ɓ���" );
#endif

		/* ���ʕϊ��Ǘ����e�[�u���p�\���̐ݒ�                                        */
		/* �� �R�����g������O�Ɍ��݂̏������ʕϊ��Ǘ����e�[�u���p�\���̂Ɋi�[���� */
		memset(&sKkaconvknr, 0, sizeof(sKkaconvknr));
		sKkaconvknr.no = pKkaconvmst->no;							/* ���ʕϊ��}�X�^��NO */

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    sKkaconvknr.no       = [%d]", sKkaconvknr.no );
#endif

		memcpy(sKkaconvknr.hnktntid, cDtnrtts, sizeof(sKkaconvknr.hnktntid));	/* �ύX�S���҂h�c     */

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    sKkaconvknr.hnktntid = [%s]", sKkaconvknr.hnktntid );
#endif

		pKkaconvknr = &sKkaconvknr;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvknr->no       = [%d]", pKkaconvknr->no );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvknr->hnktntid = [%s]", pKkaconvknr->hnktntid );

		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105SetKkaconvknr  - �O" );
#endif

		iRet = GD105SetKkaconvknr( pKkaconvknr, pKekka, pKanjya, pKenzok, pSstcd );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105SetKkaconvknr  - �� (iRet = [%d])", iRet );

		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� dGD105InsKkaconvknr - �O" );
#endif

		/* ���ʕϊ��Ǘ����e�[�u����INSERT                                      */
		/* �� �R�����g������O�Ɍ��݂̏������ʕϊ��Ǘ����e�[�u����INSERT���� */
		iRet = dGD105InsKkaconvknr( pKkaconvknr );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� dGD105InsKkaconvknr - �� (iRet = [%d])", iRet );
#endif

		if ( iRet != HRC_SQL_NORMAL )
		{
			//�ُ�I��
			//���O�o��
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_INS, MYAPP_LOG_ERRCODE_NON,
						"dGD105InsKkaconvknr ERROR [%d]", iRet );

			// ���[���o�b�N
			ZdbRollback();

			if (pKanjya != NULL)
			{
				ZbmlFree( pKanjya );
				pKanjya = NULL;
			}

			if (pKenzok != NULL)
			{
				ZbmlFree( pKenzok );
				pKenzok = NULL;
			}

			return RTN_NG;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105SetKekkaConv   - �O" );
#endif

		/* ���ʏ��e�[�u���X�V�p�\���̐ݒ�     */
		/* �� pKkaconvmst��pKekkaConv�ɐݒ肷�� */
		memset(&sKekkaConv, 0, sizeof(sKekkaConv));
		pKekkaConv = &sKekkaConv;
	
		iRet = GD105SetKekkaConv( pKekkaConv, pKekka, pKkaconvmst, cDtnrtts );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105SetKekkaConv   - �� (iRet = [%d])", iRet );

		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� dGD105UpdKekkaConv  - �O" );
#endif

		/* ���ʃe�[�u�����R�����g������                          */
		/* �� ���ʃt�B���^�ϊ����ꂽ���Ɠ�����Ԃ�UPDATE���邱�� */
		iRet = dGD105UpdKekkaConv( pKekkaConv );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� dGD105UpdKekkaConv  - �� (iRet = [%d])", iRet );
#endif

		if ( iRet != HRC_SQL_NORMAL )
		{
			//�ُ�I��
			//���O�o��
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						"dGD105UpdKekkaConv ERROR [%d]", iRet );

			// ���[���o�b�N
			ZdbRollback();

			if (pKanjya != NULL)
			{
				ZbmlFree( pKanjya );
				pKanjya = NULL;
			}

			if (pKenzok != NULL)
			{
				ZbmlFree( pKenzok );
				pKenzok = NULL;
			}

			return RTN_NG;
		}

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105KkaConvChk - �ϊ�����ŏI��" );
#endif

		return RTN_OK;
	}
	/* 1���`�F�b�N��ʂ�Ȃ������ꍇ                                      */
	/* �� �}�X�^�Ƀ��R�[�h�͂��邪�A�`�F�b�N������1���ݒ肳��Ă��Ȃ��ꍇ */
	else
	{
		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�� GD105KkaConvChk - �ϊ��Ȃ��ŏI��" );
#endif

		return RTN_SKIP;
	}
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkSbtkbn()										  */
/*�@�@�\�T�v�@�F���ʋ敪�`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar cKanjyaSbtkbn			���ҏ��̐��ʋ敪				  */
/*�@�@��Q�����Fchar cKkaconvmstSbtkbn		���ʕϊ��}�X�^�̐��ʋ敪		  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkSbtkbn(char cKanjyaSbtkbn, char cKkaconvmstSbtkbn)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkSbtkbn - �J�n" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKanjyaSbtkbn     = [%c]", cKanjyaSbtkbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstSbtkbn = [%c]", cKkaconvmstSbtkbn );
#endif

	if (cKanjyaSbtkbn == cKkaconvmstSbtkbn)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� ���ʋ敪�Ń`�F�b�N�ΏۂɂȂ���" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkSbtkbn - �I��" );
#endif

	return iRet;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkAge()											  */
/*�@�@�\�T�v�@�F�N��`�F�b�N�֐�											  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *pKanjyaAge			���ҏ��̔N��					  */
/*�@�@��Q�����Fchar *pKkaconvmstAge		���ʕϊ��}�X�^�̔N��			  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkAge(char *pKanjyaAge, char *pKkaconvmstAge)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* ���茳�̒l�p */
	char	cTmp2[32+1];	/* �������p     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkAge - �J�n" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKanjyaAge        = [%s]", pKanjyaAge );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstAge    = [%s]", pKkaconvmstAge );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKanjyaAge);
	/* ���茳���X�y�[�X��������A'@' �ɕϊ����� */
	/* �� ��{�I�� '@' �� "==" �̏ꍇ�����B     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1�ɒl�������Ă���ꍇ */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �J�n" );
#endif

		/* cTmp1�����l���ǂ������f */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �I�� iRet = [%d]", iRet );
#endif

		/* cTmp1�����l�ł͂Ȃ��ꍇ */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�� pKanjyaAge�����l�ł͂Ȃ� - �I��" );
#endif

			/* �������������`�F�b�N�ΏۊO�Ƃ��Ĕ����� */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstAge);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* ���ʕϊ��}�X�^�������W�J */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* ���������l�`�F�b�N */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkAge - �I��" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkAgekbn()										  */
/*�@�@�\�T�v�@�F�N��敪�`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar cKanjyaAgekbn			���ҏ��̔N��敪				  */
/*�@�@��Q�����Fchar cKkaconvmstAgekbn		���ʕϊ��}�X�^�̔N��敪		  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkAgekbn(char cKanjyaAgekbn, char cKkaconvmstAgekbn)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkAgekbn - �J�n" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKanjyaAgekbn     = [%c]", cKanjyaAgekbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstAgekbn = [%c]", cKkaconvmstAgekbn );
#endif

	if (cKanjyaAgekbn == cKkaconvmstAgekbn)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� �N��敪�Ń`�F�b�N�ΏۂɂȂ���" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkAgekbn - �I��" );
#endif

	return iRet;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkSc()											  */
/*�@�@�\�T�v�@�F�g���`�F�b�N�֐�											  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *pKanjyaSc				���ҏ��̐g��					  */
/*�@�@��Q�����Fchar *pKkaconvmstSc			���ʕϊ��}�X�^�̐g��			  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkSc(char *pKanjyaSc, char *pKkaconvmstSc)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* ���茳�̒l�p */
	char	cTmp2[32+1];	/* �������p     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkSc - �J�n" );


	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKanjyaSc      = [%s]", pKanjyaSc );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstSc  = [%s]", pKkaconvmstSc );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKanjyaSc);
	/* ���茳���X�y�[�X��������A'@' �ɕϊ����� */
	/* �� ��{�I�� '@' �� "==" �̏ꍇ�����B     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1�ɒl�������Ă���ꍇ */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �J�n" );
#endif

		/* cTmp1�����l���ǂ������f */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �I�� iRet = [%d]", iRet );
#endif

		/* cTmp1�����l�łȂ��ꍇ */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�� pKanjyaSc�����l�łȂ� - �I��" );
#endif

			/* �������������`�F�b�N�ΏۊO�Ƃ��Ĕ����� */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstSc);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* ���ʕϊ��}�X�^�������W�J */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* ���������l�`�F�b�N */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkSc - �I��" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkTj()											  */
/*�@�@�\�T�v�@�F�̏d�`�F�b�N�֐�											  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *pKanjyaTj				���ҏ��̑̏d					  */
/*�@�@��Q�����Fchar *pKkaconvmstTj			���ʕϊ��}�X�^�̑̏d			  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkTj(char *pKanjyaTj, char *pKkaconvmstTj)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* ���茳�̒l�p */
	char	cTmp2[32+1];	/* �������p     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTj - �J�n" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKanjyaTj        = [%s]", pKanjyaTj );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstTj    = [%s]", pKkaconvmstTj );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKanjyaTj);
	/* ���茳���X�y�[�X��������A'@' �ɕϊ����� */
	/* �� ��{�I�� '@' �� "==" �̏ꍇ�����B     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1�ɒl�������Ă���ꍇ */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �J�n" );
#endif

		/* cTmp1�����l���ǂ������f */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �I�� iRet = [%d]", iRet );
#endif

		/* cTmp1�����l�łȂ��ꍇ */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�� pKanjyaTj�����l�łȂ� - �I��" );
#endif

			/* �������������`�F�b�N�ΏۊO�Ƃ��Ĕ����� */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstTj);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* ���ʕϊ��}�X�^�������W�J */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* ���������l�`�F�b�N */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTj - �I��" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkTjtni()											  */
/*�@�@�\�T�v�@�F�̏d�敪�`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar cKanjyaTjtni			���ҏ��̑̏d�敪				  */
/*�@�@��Q�����Fchar cKkaconvmstTjtni		���ʕϊ��}�X�^�̑̏d�敪		  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkTjtni(char cKanjyaTjtni, char cKkaconvmstTjtni)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTjtni - �J�n" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKanjyaTjtni     = [%c]", cKanjyaTjtni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstTjtni = [%c]", cKkaconvmstTjtni );
#endif

	if (cKanjyaTjtni == cKkaconvmstTjtni)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� �̏d�敪�Ń`�F�b�N�ΏۂɂȂ���" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTjtni - �I��" );
#endif

	return iRet;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkTntme()											  */
/*�@�@�\�T�v�@�F�~�A���ԃ`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *pKenzokTntme			���̑������̒~�A����			  */
/*�@�@��Q�����Fchar *pKkaconvmstTntme		���ʕϊ��}�X�^�̒~�A����		  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkTntme(char *pKenzokTntme, char *pKkaconvmstTntme)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* ���茳�̒l�p */
	char	cTmp2[32+1];	/* �������p     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTntme - �J�n" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKenzokTntme     = [%s]", pKenzokTntme );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstTntme = [%s]", pKkaconvmstTntme );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKenzokTntme);
	/* ���茳���X�y�[�X��������A'@' �ɕϊ����� */
	/* �� ��{�I�� '@' �� "==" �̏ꍇ�����B     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1�ɒl�������Ă���ꍇ */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �J�n" );
#endif

		/* cTmp1�����l���ǂ������f */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �I�� iRet = [%d]", iRet );
#endif

		/* cTmp1�����l�łȂ��ꍇ */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�� pKenzokTntme�����l�łȂ� - �I��" );
#endif

			/* �������������`�F�b�N�ΏۊO�Ƃ��Ĕ����� */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstTntme);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* ���ʕϊ��}�X�^�������W�J */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* ���������l�`�F�b�N */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTntme - �I��" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkTntni()											  */
/*�@�@�\�T�v�@�F�~�A���ԋ敪�`�F�b�N�֐�									  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar cKenzokTntni			���ҏ��̒~�A���ԋ敪			  */
/*�@�@��Q�����Fchar cKkaconvmstTntni		���ʕϊ��}�X�^�̒~�A���ԋ敪	  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkTntni(char cKenzokTntni, char cKkaconvmstTntni)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTntni - �J�n" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKenzokTntni     = [%c]", cKenzokTntni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstTntni = [%c]", cKkaconvmstTntni );
#endif

	if (cKenzokTntni == cKkaconvmstTntni)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� �~�A���ԋ敪�Ń`�F�b�N�ΏۂɂȂ���" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTntni - �I��" );
#endif

	return iRet;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkTnryo()											  */
/*�@�@�\�T�v�@�F�~�A�ʃ`�F�b�N�֐�											  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *pKenzokTnryo			���̑������̒~�A��			  */
/*�@�@��Q�����Fchar *pKkaconvmstTnryo		���ʕϊ��}�X�^�̒~�A��			  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkTnryo(char *pKenzokTnryo, char *pKkaconvmstTnryo)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* ���茳�̒l�p */
	char	cTmp2[32+1];	/* �������p     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTnryo - �J�n" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKenzokTnryo        = [%s]", pKenzokTnryo );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstTnryo    = [%s]", pKkaconvmstTnryo );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKenzokTnryo);
	/* ���茳���X�y�[�X��������A'@' �ɕϊ����� */
	/* �� ��{�I�� '@' �� "==" "!=" �̏ꍇ�����B     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1�ɒl�������Ă���ꍇ */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �J�n" );
#endif

		/* cTmp1�����l���ǂ������f */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - �I�� iRet = [%d]", iRet );
#endif

		/* cTmp1�����l�łȂ��ꍇ */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�� pKenzokTnryo�����l�łȂ� - �I��" );
#endif

			/* �������������`�F�b�N�ΏۊO�Ƃ��Ĕ����� */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstTnryo);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* ���ʕϊ��}�X�^�������W�J */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* ���������l�`�F�b�N */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTnryo - �I��" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105ConvChkTnryotni()										  */
/*�@�@�\�T�v�@�F�~�A�ʋ敪�`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar cKenzokTnryotni		���ҏ��̒~�A�ʋ敪			  */
/*�@�@��Q�����Fchar cKkaconvmstTnryotni	���ʕϊ��}�X�^�̒~�A�ʋ敪		  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105ConvChkTnryotni(char cKenzokTnryotni, char cKkaconvmstTnryotni)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTnryotni - �J�n" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKenzokTnryotni     = [%c]", cKenzokTnryotni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstTnryotni = [%c]", cKkaconvmstTnryotni );
#endif

	if (cKenzokTnryotni == cKkaconvmstTnryotni)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� �~�A�ʋ敪�Ń`�F�b�N�ΏۂɂȂ���" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105ConvChkTnryotni - �I��" );
#endif

	return iRet;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105SetKkaconvknr()										  */
/*�@�@�\�T�v�@�F���ʕϊ��Ǘ����e�[�u���p�\���̐ݒ�֐�					  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKkaconvknr	*pKkaconvknr	���ʕϊ��Ǘ����				  */
/*�@�@��Q�����FKekka		*pKekka			���ʏ��						  */
/*�@�@��R�����FKanjya		*pKanjya		���ҏ��						  */
/*�@�@��S�����FKenzok		*pKenzok		���̑������					  */
/*�@�@��T�����Fchar		*pSstcd			�{�݃R�[�h						  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��(0)									  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��(-1)									  */
/******************************************************************************/
int GD105SetKkaconvknr(Kkaconvknr *pKkaconvknr, Kekka *pKekka, Kanjya *pKanjya, Kenzok *pKenzok, char *pSstcd)
{
	char	cBuf[2];
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKkaconvknr", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105SetKkaconvknr - �J�n" );
#endif

	/* ���ʕϊ��Ǘ����e�[�u���p�\���̐ݒ� */
	memcpy(pKkaconvknr->knskisymd, pKekka->knskisymd, sizeof(pKkaconvknr->knskisymd));		/* �����J�n��     */
	memcpy(pKkaconvknr->sriymd, pKekka->sriymd, sizeof(pKkaconvknr->sriymd));				/* ������         */
	memcpy(pKkaconvknr->kntno, pKekka->kntno, sizeof(pKkaconvknr->kntno));					/* ����No         */
	memcpy(pKkaconvknr->knsgrp, pKekka->knsgrp, sizeof(pKkaconvknr->knsgrp));				/* �����O���[�v   */
	memcpy(pKkaconvknr->kmkcd, pKekka->kmkcd, sizeof(pKkaconvknr->kmkcd));					/* ���ڃR�[�h     */
	pKkaconvknr->knssu = pKekka->knssu;														/* ������       */
	memset(cBuf, 0, sizeof(cBuf));
	sprintf(cBuf, "%c", pKekka->kkassflg);
	pKkaconvknr->hkksu = atoi(cBuf);														/* �񍐉�       */
	memcpy(pKkaconvknr->sstcd, pSstcd, sizeof(pKkaconvknr->sstcd));							/* �{�݃R�[�h     */
	memcpy(pKkaconvknr->utkymd, pKekka->utkymd, sizeof(pKkaconvknr->utkymd));				/* ��t��         */
	memcpy(pKkaconvknr->irino, pKekka->irino, sizeof(pKkaconvknr->irino));					/* �˗���No       */
	memcpy(pKkaconvknr->knskka1, pKekka->knskka1, sizeof(pKkaconvknr->knskka1));			/* �������ʂP     */
	memcpy(pKkaconvknr->knskka2, pKekka->knskka2, sizeof(pKkaconvknr->knskka2));			/* �������ʂQ     */
	memcpy(pKkaconvknr->knskka2kbn, pKekka->knskka2kbn, sizeof(pKkaconvknr->knskka2kbn));	/* �������ʂQ�敪 */
	memcpy(pKkaconvknr->kkahskcd, pKekka->kkahskcd, sizeof(pKkaconvknr->kkahskcd));			/* �������ʕ⑫   */
	memcpy(pKkaconvknr->skkka, pKekka->skkka, sizeof(pKkaconvknr->skkka));					/* �Ɖ��       */
	pKkaconvknr->sbtkbn = pKanjya->sbtkbn;													/* ���ʋ敪       */
	memcpy(pKkaconvknr->age, pKanjya->age, sizeof(pKkaconvknr->age));						/* �N��           */
	pKkaconvknr->agekbn = pKanjya->agekbn;													/* �N��敪       */
	memcpy(pKkaconvknr->sc, pKanjya->sc, sizeof(pKkaconvknr->sc));							/* �g��           */
	memcpy(pKkaconvknr->tj, pKanjya->tj, sizeof(pKkaconvknr->tj));							/* �̏d           */
	pKkaconvknr->tjtni = pKanjya->tjtni;													/* �̏d�敪       */
	memcpy(pKkaconvknr->tntme, pKenzok->tntme, sizeof(pKkaconvknr->tntme));					/* �~�A����       */
	pKkaconvknr->tntni = pKenzok->tntni;													/* �~�A���ԋ敪   */
	memcpy(pKkaconvknr->tnryo, pKenzok->tnryo, sizeof(pKkaconvknr->tnryo));					/* �~�A��         */
	pKkaconvknr->tnryotni = pKenzok->tnryotni;												/* �~�A�ʋ敪     */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKkaconvknr", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105SetKkaconvknr - �I��" );
#endif

	return RTN_OK;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105SetKekkaConv()											  */
/*�@�@�\�T�v�@�F���ʏ��e�[�u���X�V�p�\���̐ݒ�֐�						  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FKekkaConv	*pKekkaConv		�X�V�p���ʏ��					  */
/*�@�@��Q�����FKekka		*pKekka			���ʏ��						  */
/*�@�@��R�����FKkaconvmst	*pKkaconvmst	���ʕϊ��}�X�^���				  */
/*�@�@��S�����Fchar		*pDtnrtts		�f�[�^���͒S����				  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��(0)									  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��(-1)									  */
/******************************************************************************/
int GD105SetKekkaConv(KekkaConv *pKekkaConv, Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pDtnrtts)
{
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKekkaConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105SetKekkaConv - �J�n" );
#endif

	/* �X�V�Ώۂ̌��ʏ��L�[ */
	memcpy(pKekkaConv->knskisymd, pKekka->knskisymd, sizeof(pKekka->knskisymd));	/* �����J�n��       */
	memcpy(pKekkaConv->sriymd, pKekka->sriymd, sizeof(pKekka->sriymd));				/* ������           */
	memcpy(pKekkaConv->kntno, pKekka->kntno, sizeof(pKekka->kntno));				/* ����No           */
	memcpy(pKekkaConv->knsgrp, pKekka->knsgrp, sizeof(pKekka->knsgrp));				/* �����O���[�v     */
	memcpy(pKekkaConv->kmkcd, pKekka->kmkcd, sizeof(pKekka->kmkcd));				/* ���ڃR�[�h       */
	pKekkaConv->knssu = pKekka->knssu;												/* ������         */
	pKekkaConv->knssueda = pKekka->knssueda;										/* �����񐔎}��     */

	/* �t�@�C���쐬�p�\���̍X�V�����ݒ� */
	memcpy(pKekka->knskka1, pKkaconvmst->knskka1, sizeof(pKekka->knskka1));						/* �������ʂP       */
	memcpy(pKekka->knskka2, pKkaconvmst->knskka2, sizeof(pKekka->knskka2));						/* �������ʂQ       */
	memcpy(pKekka->knskka2kbn, pKkaconvmst->knskka2kbn, sizeof(pKekka->knskka2kbn));			/* �������ʂQ�敪   */
	memcpy(pKekka->kkahskcd, pKkaconvmst->kkahskcd, sizeof(pKekka->kkahskcd));					/* �������ʕ⑫     */
//	memcpy(pKekka->dtnrtts, pDtnrtts, sizeof(pKekka->dtnrtts));									/* �f�[�^���͒S���� */
	memcpy(pKekka->skkka, pKkaconvmst->hjkka, sizeof(pKekka->skkka));							/* �Ɖ��         */

	/* �e�[�u���s�i�p�\���̐ݒ� */
	memcpy(pKekkaConv->knskka1, pKkaconvmst->knskka1, sizeof(pKekkaConv->knskka1));				/* �������ʂP       */
	memcpy(pKekkaConv->knskka2, pKkaconvmst->knskka2, sizeof(pKekkaConv->knskka2));				/* �������ʂQ       */
	memcpy(pKekkaConv->knskka2kbn, pKkaconvmst->knskka2kbn, sizeof(pKekkaConv->knskka2kbn));	/* �������ʂQ�敪   */
	memcpy(pKekkaConv->kkahskcd, pKkaconvmst->kkahskcd, sizeof(pKekkaConv->kkahskcd));			/* �������ʕ⑫     */
	memcpy(pKekkaConv->dtnrtts, pDtnrtts, sizeof(pKekkaConv->dtnrtts));							/* �f�[�^���͒S���� */
	memcpy(pKekkaConv->skkka, pKkaconvmst->hjkka, sizeof(pKekkaConv->skkka));					/* �Ɖ��         */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKekkaConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105SetKekkaConv - �I��" );
#endif

	return RTN_OK;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105CalcConv()												  */
/*�@�@�\�T�v�@�F���ʕϊ��}�X�^�������W�J�֐�								  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FCalc *pCalc			��������W�J�����\����					  */
/*�@�@��Q�����Fchar *pstrCalc		������									  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		RTN_OK	: ����I��										  */
/*�@�@�@�@�@�@		RTN_NG	: �ُ�I��										  */
/******************************************************************************/
int GD105CalcConv(Calc *pCalc, char *pstrCalc)
{
	int		iLoopCnt;	/* pstrCalc�̕����񒷕��̃��[�v�J�E���^ */
	int		iCalcCnt;	/*  */
	int		iFromToFlg;	/* cFrom�ɐݒ肩�AcTo�ɐݒ肩�̃t���O */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CalcConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105CalcConv - �J�n" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CalcConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pstrCalc      = [%s]", pstrCalc );
#endif

	/* ��������ݒ�(BW�A==�A<<�A>=�Ȃ�) */
	memcpy(pCalc->cShiki, pstrCalc, GD105_CALC_KEY); 

	iCalcCnt = 0;
	iFromToFlg = 0;
	for (iLoopCnt = GD105_CALC_KEY; iLoopCnt < strlen(pstrCalc); iLoopCnt++)
	{
		/* �������̍Ō�Ȃ烋�[�v������ */
		if (pstrCalc[iLoopCnt] == GD105_NULL)
		{
			break;
		}
		/* �R�����Ȃ�(BW�A!B�̏ꍇ)�i�[����ϐ���cFrom����cTo�ɐ؂�ւ��� */
		else if (pstrCalc[iLoopCnt] == ':')
		{
			iCalcCnt = 0;
			iFromToFlg = 1;
			continue;
		}
		
		/* �������̎��̐��l���i�[(�ʏ�͂�����ɐݒ肳���) */
		if (iFromToFlg == 0)
		{
			pCalc->cFrom[iCalcCnt++] = pstrCalc[iLoopCnt];
		}
		/* "BW"�A"!B" �̏ꍇ�̂�cTo�ɐݒ� */
		else
		{
			pCalc->cTo[iCalcCnt++] = pstrCalc[iLoopCnt];
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CalcConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105CalcConv - �I��" );
#endif

	return RTN_OK;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105IsNumeric()											  */
/*�@�@�\�T�v�@�F���l���f�֐�												  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fconst char *pstrTarget	���l�`�F�b�N���镶����				  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : ���l�łȂ�											  */
/*�@�@�@�@�@�@		1 : ���l												  */
/******************************************************************************/
int GD105IsNumeric(const char *pstrTarget)
{
	int nResult = 0;
	int nIndex;

	/* pstrTarget�����l���ǂ������f���� */
	if (NULL != (void *) pstrTarget)
	{
		/* Trim start         */
		for (nIndex = 0; isspace(*(pstrTarget + nIndex)); nIndex++);

		if ((int) *(pstrTarget + nIndex) == '-')
		{
			for (++nIndex; isspace(*(pstrTarget + nIndex)); nIndex++);
		}

		/* Integer part       */
		for ( ; isdigit(*(pstrTarget + nIndex)); nIndex++);

		if ((int) *(pstrTarget + nIndex) == '.')
		{
			/* uner decimal point */
			for (++nIndex; isspace(*(pstrTarget + nIndex)); nIndex++);
		}

		/* Trim end           */
		for ( ; isspace(*(pstrTarget + nIndex)); nIndex++);

		if ((int) *(pstrTarget + nIndex) == GD105_NULL)
		{
			nResult = 1;
		}
	}

	return nResult;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105NumChk()												  */
/*�@�@�\�T�v�@�F���������l�`�F�b�N�֐�										  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����FCalc *pCalc			��������W�J�����\����					  */
/*�@�@��Q�����Fchar *pstrNum		��r������								  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�Fint															  */
/*�@�@�@�@�@�@		0 : �`�F�b�N�����ΏۊO									  */
/*�@�@�@�@�@�@		1 : �`�F�b�N�����Ώ�									  */
/******************************************************************************/
int GD105NumChk(Calc *pCalc, char *pstrNum)
{
	int		iRetChk = 0;
	char	cBuf[15+1];

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105NumChk - �J�n" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  �� pstrNum = [%s]", pstrNum );
#endif

	/* �ꎞ�̈�ɑޔ� */
	memset(cBuf, 0, sizeof(cBuf));
	sprintf(cBuf, "%s", pstrNum);

	/* �� �͈͎w��̏ꍇ || �͈͎w��ȊO �� */
	if (memcmp(pCalc->cShiki, "BW", sizeof(pCalc->cShiki) - 1) == 0 || memcmp(pCalc->cShiki, "!B", sizeof(pCalc->cShiki) - 1) == 0)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105NumChk - [BW || !B] �Ń`�F�b�N" );
		if (memcmp(pCalc->cShiki, "BW", sizeof(pCalc->cShiki) - 1) == 0)
		{
			if (cBuf[0] == GD105_SPACE_MARK)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    pCalc->cFrom[%d] <= cBuf[%c] <= pCalc->cTo[%d] ??",
							atoi(pCalc->cFrom), cBuf[0], atoi(pCalc->cTo) );
			}
			else
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    pCalc->cFrom[%d] <= cBuf[%d] <= pCalc->cTo[%d] ??",
							atoi(pCalc->cFrom), atoi(cBuf), atoi(pCalc->cTo) );
			}
		}
		else
		{
			if (cBuf[0] == GD105_SPACE_MARK)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    cBuf[%c] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%c] ??",
							cBuf[0], atoi(pCalc->cFrom), atoi(pCalc->cTo), cBuf[0] );
			}
			else
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    cBuf[%d] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%d] ??",
							atoi(cBuf), atoi(pCalc->cFrom), atoi(pCalc->cTo), atoi(cBuf) );
			}
		}
#endif

		if (cBuf[0] == GD105_SPACE_MARK)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� iRetChk = 0 ��ݒ�" );
#endif
			iRetChk = 0;
		}
		else if ( (atoi(pCalc->cFrom) <= atoi(cBuf)) && (atoi(cBuf) <= atoi(pCalc->cTo)) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� iRetChk = 1 ��ݒ�" );
#endif

			/* �`�F�b�N�����Ώ� */
			iRetChk = 1;
		}

#ifdef _DEBUG
		if (memcmp(pCalc->cShiki, "BW", sizeof(pCalc->cShiki) - 1) == 0)
		{
			if (iRetChk == 1)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  �� GD105NumChk - [BW] �Ń`�F�b�N�ΏۂɂȂ���" );
			}
		}
		else
		{
			if (iRetChk == 0)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  �� GD105NumChk - [!B] �Ń`�F�b�N�ΏۂɂȂ���" );
			}
		}
#endif
	}
//	/* �� �͈͎w��ȊO�̏ꍇ �� */
//	else if (memcmp(pCalc->cShiki, "!B", sizeof(pCalc->cShiki) - 1) == 0)
//	{
//#ifdef _DEBUG
//		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					"  �� GD105NumChk - [!B] �Ń`�F�b�N" );
//		if (cBuf[0] == GD105_SPACE_MARK)
//		{
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"    cBuf[%c] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%c] ??",
//						cBuf[0], atoi(pCalc->cFrom), atoi(pCalc->cTo), cBuf[0] );
//		}
//		else
//		{
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"    cBuf[%d] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%d] ??",
//						atoi(cBuf), atoi(pCalc->cFrom), atoi(pCalc->cTo), atoi(cBuf) );
//		}
//#endif
//
//		/* cBuf �� '@' �̏ꍇ */
//		if (cBuf[0] == GD105_SPACE_MARK)
//		{
//#ifdef _DEBUG
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"  �� GD105NumChk - [!B] �Ń`�F�b�N�ΏۂɂȂ���" );
//#endif
//
//			/* �`�F�b�N�����Ώ� */
//			iRetChk = 1;
//		}
//		/* cBuf �����l�̏ꍇ */
//		else if ( (atoi(cBuf) < atoi(pCalc->cFrom)) || (atoi(pCalc->cTo) < atoi(cBuf)) )
//		{
//#ifdef _DEBUG
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"  �� GD105NumChk - [!B] �Ń`�F�b�N�ΏۂɂȂ���" );
//#endif
//
//			/* �`�F�b�N�����Ώ� */
//			iRetChk = 1;
//		}
//	}
	/* �� �������ꍇ || �������Ȃ��ꍇ �� */
	else if (memcmp(pCalc->cShiki, "==", sizeof(pCalc->cShiki) - 1) == 0 || memcmp(pCalc->cShiki, "!=", sizeof(pCalc->cShiki) - 1) == 0)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105NumChk - [== || !=] �Ń`�F�b�N" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom[%s] == cBuf[%s] ?? || pCalc->cFrom[%s] != cBuf[%s] ??",
					pCalc->cFrom, cBuf, pCalc->cFrom, cBuf );
#endif

		if ( memcmp(pCalc->cFrom, cBuf, sizeof(cBuf)) == 0 )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� GD105NumChk - [==] �Ń`�F�b�N�ΏۂɂȂ���" );
#endif

			/* �`�F�b�N�����Ώ� */
			iRetChk = 1;
		}
#ifdef _DEBUG
		if (memcmp(pCalc->cShiki, "==", sizeof(pCalc->cShiki) - 1) == 0)
		{
			if (iRetChk == 1)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  �� GD105NumChk - [==] �Ń`�F�b�N�ΏۂɂȂ���" );
			}
		}
		else
		{
			if (iRetChk == 0)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  �� GD105NumChk - [!=] �Ń`�F�b�N�ΏۂɂȂ���" );
			}
		}
#endif
	}
//	/* �� �������Ȃ��ꍇ �� */
//	else if (memcmp(pCalc->cShiki, "!=", sizeof(pCalc->cShiki) - 1) == 0)
//	{
//#ifdef _DEBUG
//		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					"  �� GD105NumChk - [!=] �Ń`�F�b�N" );
//		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					"    pCalc->cFrom[%s] != cBuf[%s] ??", pCalc->cFrom, cBuf );
//#endif
//
//		if ( memcmp(pCalc->cFrom, cBuf, sizeof(cBuf)) != 0 )
//		{
//#ifdef _DEBUG
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"  �� GD105NumChk - [!=] �Ń`�F�b�N�ΏۂɂȂ���" );
//#endif
//
//			/* �`�F�b�N�����Ώ� */
//			iRetChk = 1;
//		}
//	}
	/* �� ���傫���ꍇ(�������A'@'�ł͂Ȃ��ꍇ) �� */
	else if (memcmp(pCalc->cShiki, ">>", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105NumChk - [>>] �Ń`�F�b�N" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] > pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif

		if ( atoi(pCalc->cFrom) < atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� GD105NumChk - [>>] �Ń`�F�b�N�ΏۂɂȂ���" );
#endif

			/* �`�F�b�N�����Ώ� */
			iRetChk = 1;
		}
	}
	/* �� �����̏ꍇ(�������A'@'�ł͂Ȃ��ꍇ) �� */
	else if (memcmp(pCalc->cShiki, "<<", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105NumChk - [<<] �Ń`�F�b�N" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] < pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif


		if ( atoi(pCalc->cFrom) > atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� GD105NumChk - [<<] �Ń`�F�b�N�ΏۂɂȂ���" );
#endif

			/* �`�F�b�N�����Ώ� */
			iRetChk = 1;
		}
	}
	/* �� �ȏ�̏ꍇ(�������A'@'�ł͂Ȃ��ꍇ) �� */
	else if (memcmp(pCalc->cShiki, ">=", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105NumChk - [>=] �Ń`�F�b�N" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] >= pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif

		if ( atoi(pCalc->cFrom) <= atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� GD105NumChk - [>=] �Ń`�F�b�N�ΏۂɂȂ���" );
#endif

			/* �`�F�b�N�����Ώ� */
			iRetChk = 1;
		}
	}
	/* �� �ȉ��̏ꍇ(�������A'@'�ł͂Ȃ��ꍇ) �� */
	else if (memcmp(pCalc->cShiki, "<=", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  �� GD105NumChk - [<=] �Ń`�F�b�N" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] <= pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif

		if ( atoi(pCalc->cFrom) >= atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  �� GD105NumChk - [<=] �Ń`�F�b�N�ΏۂɂȂ���" );
#endif

			/* �`�F�b�N�����Ώ� */
			iRetChk = 1;
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�� GD105NumChk - �I�� iRetChk = [%d]", iRetChk );
#endif

	return iRetChk;
}

/******************************************************************************/
/*�@�� �� ���@�FGD105Trim()													  */
/*�@�@�\�T�v�@�F�w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[����	  */
/*�@���@�@�́@�F															  */
/*�@�@��P�����Fchar *dst		Trim��̕�����								  */
/*�@�@��Q�����Fchar *src		Trim�O�̕�����								  */
/*�@�o�@�@�́@�F�Ȃ�														  */
/*�@���A���@�F�Ȃ�														  */
/******************************************************************************/
void GD105Trim(char *dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != GD105_NULL; srcCnt ++)
	{
		/* src�̍������X�y�[�X�̏ꍇ�A������������܂Ői�� */
		if ((dstCnt == 0) && (src[srcCnt] == '\x20'))
		{
			continue;
		}

		dst[dstCnt++] = src[srcCnt];

		if (src[srcCnt] != '\x20')
		{
			Flg = dstCnt;
		}
	}

	/* �Ō�� '\0' ��t����                                        */
	/* �� src���S�ăX�y�[�X�̏ꍇ�Adst��NULL(dst[0] == '\0')�ƂȂ� */
	dst[Flg] = GD105_NULL;
}
