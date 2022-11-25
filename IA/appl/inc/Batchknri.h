/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FBatchknri.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Batchknri_h_
#define _Batchknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Batchknri {
	char    knskisymd[11];
	char    bskkbn[11];
	char    bsklne[11];
	char    bskgok[6];
	char    bskmjno[6];
	char    knsgrp[11];
	sqlint32  bthno;
	char    lotno[11];
	char    bthjkflg;
	char    ksndh[27];
}	Batchknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbBatchknriSelectAll( Batchknri** arrayOut, int* numOut );
long ZdbBatchknriSelectKey( Batchknri* pKey, Batchknri** arrayOut, int* numOut );
long ZdbBatchknriInsert( Batchknri* rec );
long ZdbBatchknriUpdate( Batchknri* rec );
long ZdbBatchknriDelete( Batchknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
