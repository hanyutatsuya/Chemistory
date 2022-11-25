/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKkafltmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kkafltmst_h_
#define _Kkafltmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kkafltmst {
	char    knsgrp[17];
	char    kmkcd[8];
	char    fltkka[25];
	char    minval[13];
	char    maxval[13];
	char    knskka1[13];
	char    knskka2[25];
	char    knskka2kbn[3];
	char    kkahskcd[4];
	char    hjkka[25];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kkafltmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKkafltmstSelectAll( Kkafltmst** arrayOut, int* numOut );
long ZdbKkafltmstSelectKey( Kkafltmst* pKey, Kkafltmst** arrayOut, int* numOut );
long ZdbKkafltmstInsert( Kkafltmst* rec );
long ZdbKkafltmstUpdate( Kkafltmst* rec );
long ZdbKkafltmstDelete( Kkafltmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
