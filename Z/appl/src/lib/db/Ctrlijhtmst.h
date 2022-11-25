/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FCtrlijhtmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Ctrlijhtmst_h_
#define _Ctrlijhtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ctrlijhtmst {
	char    bskkbn[5];
	char    nbkmkcd[8];
	short   ctrlhnsu;
	char    kyuhniflg;
	short   sjhnsu;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Ctrlijhtmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlijhtmstSelectAll( Ctrlijhtmst** arrayOut, int* numOut );
long ZdbCtrlijhtmstSelectKey( Ctrlijhtmst* pKey, Ctrlijhtmst** arrayOut, int* numOut );
long ZdbCtrlijhtmstInsert( Ctrlijhtmst* rec );
long ZdbCtrlijhtmstUpdate( Ctrlijhtmst* rec );
long ZdbCtrlijhtmstDelete( Ctrlijhtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
