/******************************************************************************/
/*                                                                            */
/*     �a�l�k�l���������V�X�e��                                               */
/*                                                                            */
/*     �V�X�e�����F������                                                     */
/*     �t�@�C�����FKskbrmst2.h                                                 */
/*     �@�\�T�v  �F                                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*  Ver.     Date           Name           History                            */
/* ---------------------------------------------------------------------------*/
/*  1.00     2006-04-11                    Create                             */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/
#ifndef _Kskbrmst2_h_
#define _Kskbrmst2_h_

#include "bml_DBCom.h"

/*--------------------------------------*/
/* �e�[�u���\���̒�` */

typedef struct _Kskbrmst {
	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    ksbr[16];
	char    kmin[21];
	char    kmax[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
	/* add 20070606 waj �{�݃R�[�h�ǉ� */
	char    sstcd[8];
}	Kskbrmst;

/*--------------------------------------*/
/* �֐��v���g�^�C�v */

#ifdef __cplusplus
extern "C" {
#endif

long ZdbKskbrmstSelectAll( Kskbrmst** arrayOut, int* numOut );
long ZdbKskbrmstSelectKey( Kskbrmst* pKey, Kskbrmst** arrayOut, int* numOut );
long ZdbKskbrmstInsert( Kskbrmst* rec );
long ZdbKskbrmstUpdate( Kskbrmst* rec );
long ZdbKskbrmstDelete( Kskbrmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
