/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKekkafree.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kekkafree_h_
#define _Kekkafree_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kekkafree {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knsgrp[17];
	char    kmkcd[8];
	short   knssu;
	short   knssueda;
	char    frsb;
	char    freetext[16385];
	char    ssssflg;
	char    ssknsflg;
	char    dtnrtts[9];
	char    dtnrdh[27];
	char    ksndh[27];
}	Kekkafree;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKekkafreeSelectAll( Kekkafree** arrayOut, int* numOut );
long ZdbKekkafreeSelectKey( Kekkafree* pKey, Kekkafree** arrayOut, int* numOut );
long ZdbKekkafreeInsert( Kekkafree* rec );
long ZdbKekkafreeUpdate( Kekkafree* rec );
long ZdbKekkafreeDelete( Kekkafree* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
