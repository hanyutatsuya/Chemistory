/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FCtrlsbtmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Ctrlsbtmst_h_
#define _Ctrlsbtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ctrlsbtmst {
	char    bskkbn[5];
	char    ctrlsbt[21];
	char    stirckid[11];
	short   stirckpos;
	char    ctrliti;
	short   ctrlcnt;
	short   ctrlstart;
	short   ctrlitv;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Ctrlsbtmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCtrlsbtmstSelectAll( Ctrlsbtmst** arrayOut, int* numOut );
long ZdbCtrlsbtmstSelectKey( Ctrlsbtmst* pKey, Ctrlsbtmst** arrayOut, int* numOut );
long ZdbCtrlsbtmstInsert( Ctrlsbtmst* rec );
long ZdbCtrlsbtmstUpdate( Ctrlsbtmst* rec );
long ZdbCtrlsbtmstDelete( Ctrlsbtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
