/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FMemst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Memst_h_
#define _Memst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Memst {
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    bsknm[41];
	char    bskrs[21];
	char    goknm[21];
	sqlint32  sktmax;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Memst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbMemstSelectAll( Memst** arrayOut, int* numOut );
long ZdbMemstSelectKey( Memst* pKey, Memst** arrayOut, int* numOut );
long ZdbMemstInsert( Memst* rec );
long ZdbMemstUpdate( Memst* rec );
long ZdbMemstDelete( Memst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
