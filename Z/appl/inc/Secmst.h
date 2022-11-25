/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FSecmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Secmst_h_
#define _Secmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Secmst {
	char    seccd[3];
	char    secnm[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Secmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbSecmstSelectAll( Secmst** arrayOut, int* numOut );
long ZdbSecmstSelectKey( Secmst* pKey, Secmst** arrayOut, int* numOut );
long ZdbSecmstInsert( Secmst* rec );
long ZdbSecmstUpdate( Secmst* rec );
long ZdbSecmstDelete( Secmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
