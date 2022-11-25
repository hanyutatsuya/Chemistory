/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKkahskmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Kkahskmst_h_
#define _Kkahskmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kkahskmst {
	char    kkahskcd[4];
	char    kkahsknm[17];
	char    kkahsknmj[33];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Kkahskmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKkahskmstSelectAll( Kkahskmst** arrayOut, int* numOut );
long ZdbKkahskmstSelectKey( Kkahskmst* pKey, Kkahskmst** arrayOut, int* numOut );
long ZdbKkahskmstInsert( Kkahskmst* rec );
long ZdbKkahskmstUpdate( Kkahskmst* rec );
long ZdbKkahskmstDelete( Kkahskmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
