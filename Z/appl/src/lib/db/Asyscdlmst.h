/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FAsyscdlmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Asyscdlmst_h_
#define _Asyscdlmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Asyscdlmst {
	char    knsgrp[17];
	char    asystartymd[11];
	char    asyendymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Asyscdlmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbAsyscdlmstSelectAll( Asyscdlmst** arrayOut, int* numOut );
long ZdbAsyscdlmstSelectKey( Asyscdlmst* pKey, Asyscdlmst** arrayOut, int* numOut );
long ZdbAsyscdlmstInsert( Asyscdlmst* rec );
long ZdbAsyscdlmstUpdate( Asyscdlmst* rec );
long ZdbAsyscdlmstDelete( Asyscdlmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
