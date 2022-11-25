/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FChksbtmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Chksbtmst_h_
#define _Chksbtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Chksbtmst {
	char    chksbt[3];
	char    chkkmmn[21];
	short   chktmg;
	short   chkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Chksbtmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbChksbtmstSelectAll( Chksbtmst** arrayOut, int* numOut );
long ZdbChksbtmstSelectKey( Chksbtmst* pKey, Chksbtmst** arrayOut, int* numOut );
long ZdbChksbtmstInsert( Chksbtmst* rec );
long ZdbChksbtmstUpdate( Chksbtmst* rec );
long ZdbChksbtmstDelete( Chksbtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
