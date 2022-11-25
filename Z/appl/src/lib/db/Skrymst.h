/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FSkrymst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Skrymst_h_
#define _Skrymst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Skrymst {
	char    skerr[4];
	char    skry[21];
	char    tkhkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Skrymst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSkrymstSelectAll( Skrymst** arrayOut, int* numOut );
long ZdbSkrymstSelectKey( Skrymst* pKey, Skrymst** arrayOut, int* numOut );
long ZdbSkrymstInsert( Skrymst* rec );
long ZdbSkrymstUpdate( Skrymst* rec );
long ZdbSkrymstDelete( Skrymst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
