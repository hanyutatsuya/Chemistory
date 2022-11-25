/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FXbarmmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Xbarmmst_h_
#define _Xbarmmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Xbarmmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    minval[11];
	char    minart[11];
	char    avgval[11];
	char    maxart[11];
	char    maxval[11];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Xbarmmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXbarmmstSelectAll( Xbarmmst** arrayOut, int* numOut );
long ZdbXbarmmstSelectKey( Xbarmmst* pKey, Xbarmmst** arrayOut, int* numOut );
long ZdbXbarmmstInsert( Xbarmmst* rec );
long ZdbXbarmmstUpdate( Xbarmmst* rec );
long ZdbXbarmmstDelete( Xbarmmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
