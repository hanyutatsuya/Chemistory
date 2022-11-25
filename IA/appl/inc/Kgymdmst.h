/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKgymdmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kgymdmst_h_
#define _Kgymdmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kgymdmst {
	char    kgymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kgymdmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKgymdmstSelectAll( Kgymdmst** arrayOut, int* numOut );
long ZdbKgymdmstSelectKey( Kgymdmst* pKey, Kgymdmst** arrayOut, int* numOut );
long ZdbKgymdmstInsert( Kgymdmst* rec );
long ZdbKgymdmstUpdate( Kgymdmst* rec );
long ZdbKgymdmstDelete( Kgymdmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
