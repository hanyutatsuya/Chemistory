/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FRrkchkmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Rrkchkmst_h_
#define _Rrkchkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Rrkchkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    krnkmk1[8];
	char    krnkmk2[8];
	char    krnkmk3[8];
	char    krnkmk4[8];
	char    krnkmk5[8];
	char    sstcd[8];
	short   week;
	char    sktlow[11];
	char    skthigh[11];
	char    kyukbn;
	char    kyulow[11];
	char    kyuhigh[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Rrkchkmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbRrkchkmstSelectAll( Rrkchkmst** arrayOut, int* numOut );
long ZdbRrkchkmstSelectKey( Rrkchkmst* pKey, Rrkchkmst** arrayOut, int* numOut );
long ZdbRrkchkmstInsert( Rrkchkmst* rec );
long ZdbRrkchkmstUpdate( Rrkchkmst* rec );
long ZdbRrkchkmstDelete( Rrkchkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
