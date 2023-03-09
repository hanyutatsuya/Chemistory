/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FRkmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2008-01-07                    Create
 **********************************************************************/
#ifndef _Rkmst_h_
#define _Rkmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Rkmst {
	char    smpcd[8];
	char    rksbt;
	char    rknm[21];
	short   rkknhsu;
	short   trrcksu;
	char    filskdir[129];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Rkmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbRkmstSelectAll( Rkmst** arrayOut, int* numOut );
long ZdbRkmstSelectKey( Rkmst* pKey, Rkmst** arrayOut, int* numOut );
long ZdbRkmstInsert( Rkmst* rec );
long ZdbRkmstUpdate( Rkmst* rec );
long ZdbRkmstDelete( Rkmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/