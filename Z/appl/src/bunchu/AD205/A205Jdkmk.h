/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FA205Jdkmkmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _A205Jdkmk_h_
#define _A205Jdkmk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Jdkmkmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    jknsgrp[17];
	char    jkmkcd[8];
	char    hhkumflg;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Jdkmkmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long A205JdkmkSelKey( Jdkmkmst* pKey, Jdkmkmst** arrayOut, int* numOut );
long A205JdkmkSelAll( Jdkmkmst** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
