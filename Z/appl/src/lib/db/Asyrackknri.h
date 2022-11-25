/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FAsyrackknri.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Asyrackknri_h_
#define _Asyrackknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Asyrackknri {
	char    knskisymd[11];
	char    asyrckid[11];
	char    knskbn[3];
	char    rakbri[3];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	short   bthno;
	sqlint32  bthrckjbn;
	char    id2[11];
	char    id3[11];
	char    lnetndh[27];
	char    lnehsdh[27];
	char    rakjtflg;
	char    ksndh[27];
}	Asyrackknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbAsyrackknriSelectAll( Asyrackknri** arrayOut, int* numOut );
long ZdbAsyrackknriSelectKey( Asyrackknri* pKey, Asyrackknri** arrayOut, int* numOut );
long ZdbAsyrackknriInsert( Asyrackknri* rec );
long ZdbAsyrackknriUpdate( Asyrackknri* rec );
long ZdbAsyrackknriDelete( Asyrackknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
