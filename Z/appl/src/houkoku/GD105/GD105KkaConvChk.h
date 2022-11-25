/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FGD105KkaConvChk.h								*/
/*		�T�v		�F�񍐃f�[�^�t�@�C���쐬�w�b�_�[�t�@�C��		*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ---------------------------------------------------------------- */
/*  2.00	2009/05/19		K.Moriya		���ʕϊ��}�X�^�Ή�		*/
/********************************************************************/
#ifndef _GD105KkaConvChk_h
#define _GD105KkaConvChk_h

/********************************************************************/
/*  �C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "GD105Kanjya.h"
#include "GD105Kenzok.h"
#include "GD105KekkaConv.h"
#include "GD105Kkaconvmst.h"
#include "GD105Kkaconvknr.h"

/******************************************************************************/
/* Define��`																  */
/******************************************************************************/

//�f�[�^���ʎq
#define GD105_SSTCD_LOOP_CNT		2
#define GD105_CALC_KEY				2
#define GD105_SSTCD_ALL_ZERO		"0000000"
#define GD105_NULL					'\0'
#define GD105_SPACE_MARK			'@'
#define GD105_EXCLAMATION_MARK		'!'
#define GD105_CONVCHK_OK			1
#define GD105_CONVCHK_NG			0
#define GD105_CONVCHK_SKIP			-1

/******************************************************************************/
/* �\���̒�`																  */
/******************************************************************************/
/* ���ʕϊ��}�X�^�������W�J�p�\���� */
typedef struct _Calc {
	char	cShiki[2+1];
	char	cFrom[15+1];
	char	cTo[15+1];
} Calc;

/******************************************************************************/
/* �O���[�o���錾															  */
/******************************************************************************/
// extern

/******************************************************************************/
/* �v���g�^�C�v�錾															  */
/******************************************************************************/
/* ���ʕϊ��`�F�b�N�֐� */
int GD105KkaConvChk(Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pSstcd);
/* ���ʋ敪�`�F�b�N */
int GD105ConvChkSbtkbn(char cKanjyaSbtkbn, char cKkaconvmstSbtkbn);
/* �N��`�F�b�N */
int GD105ConvChkAge(char *pKanjyaAge, char *pKkaconvmstAge);
/* �N��敪�`�F�b�N */
int GD105ConvChkAgekbn(char cKanjyaAgekbn, char cKkaconvmstAgekbn);
/* �g���`�F�b�N */
int GD105ConvChkSc(char *pKanjyaSc, char *pKkaconvmstSc);
/* �̏d�`�F�b�N */
int GD105ConvChkTj(char *pKanjyaTj, char *pKkaconvmstTj);
/* �̏d�敪�`�F�b�N */
int GD105ConvChkTjtni(char cKanjyaTjtni, char cKkaconvmstTjtni);
/* �~�A���ԃ`�F�b�N */
int GD105ConvChkTntme(char *pKenzokTntme, char *pKkaconvmstTntme);
/* �~�A���ԋ敪�`�F�b�N */
int GD105ConvChkTntni(char cKenzokTntni, char cKkaconvmstTntni);
/* �~�A�ʃ`�F�b�N */
int GD105ConvChkTnryo(char *pKenzokTnryo, char *pKkaconvmstTnryo);
/* �~�A�ʋ敪�`�F�b�N */
int GD105ConvChkTnryotni(char cKenzokTnryotni, char cKkaconvmstTnryotni);
/* ���ʕϊ��Ǘ����e�[�u���p�\���̐ݒ� */
int GD105SetKkaconvknr(Kkaconvknr *pKkaconvknr, Kekka *pKekka, Kanjya *pKanjya, Kenzok *pKenzok, char *pSstcd);
/* ���ʏ��e�[�u���X�V�p�\���̐ݒ� */
int GD105SetKekkaConv(KekkaConv *pKekkaConv, Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pDtnrtts);
/* ���ʕϊ��}�X�^�������W�J */
int GD105CalcConv(Calc *pCalc, char *pstrCalc);
/* ���l���ǂ����`�F�b�N */
int GD105IsNumeric(const char *pstrTarget);
/* ���������l�`�F�b�N(����) */
int GD105NumChk(Calc *pCalc, char *pstrNum);
/* �g�����֐� */
void GD105Trim(char *dst, char *src);
#endif
/** End of File ***************************************************************/
