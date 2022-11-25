/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FChk100mst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Chk100mst_h_
#define _Chk100mst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Chk100mst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Chk100mst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbChk100mstSelectAll( Chk100mst** arrayOut, int* numOut );
long ZdbChk100mstSelectKey( Chk100mst* pKey, Chk100mst** arrayOut, int* numOut );
long ZdbChk100mstInsert( Chk100mst* rec );
long ZdbChk100mstUpdate( Chk100mst* rec );
long ZdbChk100mstDelete( Chk100mst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
