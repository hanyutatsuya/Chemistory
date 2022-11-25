/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FCheckHist.c
 *     �@�\�T�v  �F�q�X�g�O�������������E�ŕp�`�F�b�N���s��
 **********************************************************************/

/********************************************************************/
/*  Ver.     Date           Name           History                  */
/* -----------------------------------------------------------------*/
/*  1.00     2007-04-12                    Create                   */
/* -----------------------------------------------------------------*/
/*  Ver.     Date           Name           History                  */
/* -----------------------------------------------------------------*/
/*  2.00     2008-10-09     K.Ameno        �����Z���Ή�����         */
/********************************************************************/

/********************************************************************/
/*  �C���N���[�h�錾                                                */
/********************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <math.h>
#include "bml_base.h"
#include "FD103.h"

/********************************************************************/
/*  �֐���      �FNihoCheck()                                       */
/*  �@�\�T�v    �F������`�F�b�N                                    */
/*  ����        �F                                                  */
/*   ��P����   �FKTLIST*   kt      �����Ώۃ`���l���f�[�^          */
/*   ��Q����   �Fint*      hist    �q�X�g�i�[��					*/
/*  �o��        �F                                                  */
/*   ����FRTN_OK                                                   */
/*   �ُ�FRTN_NG                                                   */
/********************************************************************/
int NihoCheck(KTLIST* kt, int* hist)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
	int i;
	int down = 0;

    /* �g���[�X���O�o�� */
    strcpy( func_nm, "NihoCheck" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ������`�F�b�N�ł̓q�X�g�O�����̗��[�͎g�p���Ȃ� */
	for (i = 2; i < (kt->hstkaikyu - 1); i++) {
		if (hist[i-1] > hist[i])
			down = 1;
		if ((hist[i-1] < hist[i]) && down == 1) {
    		LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
			return RTN_NG;
		}
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return RTN_OK;
}

/********************************************************************/
/*  �֐���      �FSaihinCheck()                                     */
/*  �@�\�T�v    �F�ŕp�`�F�b�N                                      */
/*  ����        �F                                                  */
/*   ��P����   �FKTLIST*   kt         �����Ώۃ`���l���f�[�^       */
/*   ��Q����   �Fint*      histBefore �q�X�g�i�[��i�Z���O�j		*/
/*   ��Q����   �Fint*      histAfter  �q�X�g�i�[��i�Z����j		*/
/*  �o��        �F                                                  */
/*   ����FRTN_OK                                                   */
/*   �ُ�FRTN_NG                                                   */
/*   double�^���m�̔�r�����Ă������߁A�C��                         */
/********************************************************************/
int SaihinCheck(KTLIST* kt, int* histBefore, int* histAfter)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* �֐����� */
	int    i;
	int    in;
	int    max;
	double srange;
	double erange;
	int    ret_srange;
	int    ret_erange;
	int    SaihinCheck_keta = 4 /* ���m�ȋK�肪�����悤�Ȃ̂ŁA���ʒl��萄�� */;

    /*�g���[�X���O�o�� */
    strcpy( func_nm, "SaihinCheck" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �Z���O�ŕp�`�F�b�N */
	in  = -1;
	max =  0;
	srange = kt->hstkjntn;
	/* 2009-03-13     H.Sekiya */
	/* �蓮�Z����ʂƏ������Ⴄ�̂ŉ�ʂɍ��킹�� */
	/* erange = srange; */
	erange = srange - ( 1 / pow(10, (double)kt->sstnksu));
	for (i = 0; i < kt->hstkaikyu; i++) {
		/* 2009-03-13     H.Sekiya */
		/* �蓮�Z����ʂƏ������Ⴄ�̂ŉ�ʂɍ��킹�� */
		/* srange = erange; */
		/* erange = srange + kt->hstkzmhb; */
		srange = erange + ( 1 / pow(10, (double)kt->sstnksu));
		erange = srange + kt->hstkzmhb - ( 1 / pow(10, (double)kt->sstnksu));

		/* if ((kt->shrnglwhf <= srange) && (erange <= kt->shrnghihf)) { */
		ret_srange = chkLowHigh(srange, kt->shrnglwhf, SaihinCheck_keta);
		ret_erange = chkLowHigh(erange, kt->shrnghihf, SaihinCheck_keta);
		if (((ret_srange == 0) || (ret_srange == 1)) && ((ret_erange == 0) || (ret_erange == 2))) {
			/* �͈͓� */
			if ((in < 0) || max < histBefore[i]) {  /* max <= �Ŕ͈͓��f�[�^�D�� */
				max = histBefore[i];
				in  = 1;
			}
		} else {
			/* �͈͊O */
			if ((in < 0) || max <= histBefore[i]) { /* max <= �Ŕ͈͊O�f�[�^�D�� */
				max = histBefore[i];
				in  = 0;
			}
		}
		sprintf(G_msg, "BEFORE srange[%f] ret_srange[%d] erange[%f] ret_erange[%d] in[%d] max[%d] histBefore[%d]) \n", srange,ret_srange,erange,ret_erange,in,max,histBefore[i]);
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	if (in < 1) {
    	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
		return RTN_NG;
	}

	/* �Z����ŕp�`�F�b�N */
	in  = -1;
	max =  0;
	srange = kt->hstkjntn;
	/* 2009-03-13     H.Sekiya */
	/* �蓮�Z����ʂƏ������Ⴄ�̂ŉ�ʂɍ��킹�� */
	/* erange = srangei; */
	erange = srange - ( 1 / pow(10, (double)kt->sstnksu));
	for (i = 0; i < kt->hstkaikyu; i++) {
		/* 2009-03-13     H.Sekiya */
		/* �蓮�Z����ʂƏ������Ⴄ�̂ŉ�ʂɍ��킹�� */
		/* srange = erange; */
		/* erange = srange + kt->hstkzmhb; */
		srange = erange + ( 1 / pow(10, (double)kt->sstnksu));
		erange = srange + kt->hstkzmhb - ( 1 / pow(10, (double)kt->sstnksu));

		/* if ((kt->shrnglwhb <= srange) && (erange <= kt->shrnghihb)) { */
        ret_srange = chkLowHigh(srange, kt->shrnglwhb, SaihinCheck_keta);
        ret_erange = chkLowHigh(erange, kt->shrnghihb, SaihinCheck_keta);
		if (((ret_srange == 0) || (ret_srange == 1)) &&  ((ret_erange == 0) || (ret_erange == 2))) {
			/* �͈͓� */
			if ((in < 0) || max < histAfter[i]) {  /* max <= �Ŕ͈͓��f�[�^�D�� */
				max = histAfter[i];
				in  = 1;
			}
		} else {
			/* �͈͊O */
			if ((in < 0) || max <= histAfter[i]) { /* max <= �Ŕ͈͊O�f�[�^�D�� */
				max = histAfter[i];
				in  = 0;
			}
		}
        sprintf(G_msg, "AFTER srange[%f] ret_srange[%d] erange[%f] ret_erange[%d] in[%d] max[%d] histAfter[%d]) \n", srange,ret_srange,erange,ret_erange,in,max,histAfter[i]);
        LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	if (in < 1) {
    	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
		return RTN_NG;
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return RTN_OK;
}

