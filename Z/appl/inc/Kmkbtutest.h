/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKmkbtutest.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kmkbtutest_h_
#define _Kmkbtutest_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kmkbtutest {
	char    knskisymd[11];
	char    knsgrp[17];
	char    kmkcd[8];
	sqlint32  iriallsu;
	sqlint32  irijsnsu;
	sqlint32  kensasu;
	sqlint32  stadsu;
	sqlint32  ctrlsu;
	sqlint32  testsu;
	sqlint32  savysu;
	sqlint32  kbrtsu;
	sqlint32  kstatsu;
	char    ksndh[27];
}	Kmkbtutest;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKmkbtutestSelectAll( Kmkbtutest** arrayOut, int* numOut );
long ZdbKmkbtutestSelectKey( Kmkbtutest* pKey, Kmkbtutest** arrayOut, int* numOut );
long ZdbKmkbtutestInsert( Kmkbtutest* rec );
long ZdbKmkbtutestUpdate( Kmkbtutest* rec );
long ZdbKmkbtutestDelete( Kmkbtutest* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
