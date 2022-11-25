/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FF101ctrlijhmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-27                    Create
 **********************************************************************/
#ifndef _F101ctrlijhmst_h_
#define _F101ctrlijhmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ctrlijhmst {
	char	bskkbn[5];
	char	nbkmkcd[8];
	short	ctrlhnsu;
	char	kyuhniflg;
	short	sjhnsu;
	char	kaiymd[11];
	char	haiymd[11];
	char	hnktntid[9];
	char	ksndh[27];
}	Ctrlijhmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long FCtrlijhmstSelectByKey( Ctrlijhmst* pKey, Ctrlijhmst** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
