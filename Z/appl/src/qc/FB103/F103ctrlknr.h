/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FF103ctrlknr.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-27                    Create
 **********************************************************************/
#ifndef _F103ctrlknr_h_
#define _F103ctrlknr_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ctrlknr {
	char	knskisymd[11];
	char	bskkbn[5];
	char	bsklne[5];
	char	bskgok[7];
	long	ctrlno;
	char	ctrlhdflg;
	char	ctrlktflg;
	char	ksndh[27];
}	Ctrlknr;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long FKtflgUpdate( Ctrlknr* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
