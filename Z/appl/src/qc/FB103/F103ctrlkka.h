/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FF103ctrlkka.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-27                    Create
 **********************************************************************/
#ifndef _F103ctrlkka_h_
#define _F103ctrlkka_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ctrlkka {
	char	knskisymd[11];
	char	bskkbn[5];
	char	bsklne[5];
	char	bskgok[7];
	char	knsgrp[17];
	char	kmkcd[8];
	char	nbkmkcd[8];
	long	ctrlno;
	char	ctrlsbt[21];
	short	ctrlsbteda;
	char	ctrllbl[3];
	char	tstrflg;
	char	asyrckid[11];
	short	asyrckpos;
	long	knsseq;
	long	bskseq;
	short	bthno;
	long	bthrckjbn;
	char	syklotno[21];
	char	sktti[25];
	char	knzti[25];
	char	knztistflg;
	char	sktdh[27];
	short	ctrljti;
	char	chkzmflg;
	char	facter[13];
	char	base[13];
	char	kosijt;
	char	kositts[9];
	char	kosidh[27];
	char	ksndh[27];
}	Ctrlkka;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long FCtrlkkkaSelectAll( Ctrlkka** arrayOut, int* numOut );
long FKsidhUpdate( Ctrlkka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
