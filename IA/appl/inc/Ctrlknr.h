/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FCtrlknr.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Ctrlknr_h_
#define _Ctrlknr_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ctrlknr {
	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	sqlint32  ctrlno;
	char    ctrlhdflg;
	char    ctrlktflg;
	char    ksndh[27];
}	Ctrlknr;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlknrSelectAll( Ctrlknr** arrayOut, int* numOut );
long ZdbCtrlknrSelectKey( Ctrlknr* pKey, Ctrlknr** arrayOut, int* numOut );
long ZdbCtrlknrInsert( Ctrlknr* rec );
long ZdbCtrlknrUpdate( Ctrlknr* rec );
long ZdbCtrlknrDelete( Ctrlknr* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
