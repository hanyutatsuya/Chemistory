/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FTschkmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Tschkmst_h_
#define _Tschkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Tschkmst {
	char    kmkcdzen[8];
	char    kmkcdgo[8];
	char    tskchktyp;
	char    maxval[21];
	char    minval[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Tschkmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbTschkmstSelectAll( Tschkmst** arrayOut, int* numOut );
long ZdbTschkmstSelectKey( Tschkmst* pKey, Tschkmst** arrayOut, int* numOut );
long ZdbTschkmstInsert( Tschkmst* rec );
long ZdbTschkmstUpdate( Tschkmst* rec );
long ZdbTschkmstDelete( Tschkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
