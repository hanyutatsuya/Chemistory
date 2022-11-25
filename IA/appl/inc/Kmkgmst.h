/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKmkgmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kmkgmst_h_
#define _Kmkgmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kmkgmst {
	char    kmkgrp[17];
	char    kmkgrpnm[41];
	char    kmkgrprs[21];
	char    knsgrp[17];
	char    kmkcd[8];
	short   hyjijn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kmkgmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKmkgmstSelectAll( Kmkgmst** arrayOut, int* numOut );
long ZdbKmkgmstSelectKey( Kmkgmst* pKey, Kmkgmst** arrayOut, int* numOut );
long ZdbKmkgmstInsert( Kmkgmst* rec );
long ZdbKmkgmstUpdate( Kmkgmst* rec );
long ZdbKmkgmstDelete( Kmkgmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
