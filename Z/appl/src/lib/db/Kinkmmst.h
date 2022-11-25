/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKinkmmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kinkmmst_h_
#define _Kinkmmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kinkmmst {
	char    kmkcd[8];
	char    smpcd[8];
	char    seccd[3];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kinkmmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKinkmmstSelectAll( Kinkmmst** arrayOut, int* numOut );
long ZdbKinkmmstSelectKey( Kinkmmst* pKey, Kinkmmst** arrayOut, int* numOut );
long ZdbKinkmmstInsert( Kinkmmst* rec );
long ZdbKinkmmstUpdate( Kinkmmst* rec );
long ZdbKinkmmstDelete( Kinkmmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
