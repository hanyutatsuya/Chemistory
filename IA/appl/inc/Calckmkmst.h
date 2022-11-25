/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FCalckmkmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Calckmkmst_h_
#define _Calckmkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Calckmkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    sstcd[8];
	char    zaicd[5];
	char    ksnsk[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Calckmkmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCalckmkmstSelectAll( Calckmkmst** arrayOut, int* numOut );
long ZdbCalckmkmstSelectKey( Calckmkmst* pKey, Calckmkmst** arrayOut, int* numOut );
long ZdbCalckmkmstInsert( Calckmkmst* rec );
long ZdbCalckmkmstUpdate( Calckmkmst* rec );
long ZdbCalckmkmstDelete( Calckmkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
