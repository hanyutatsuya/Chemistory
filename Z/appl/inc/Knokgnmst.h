/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKnokgnmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Knokgnmst_h_
#define _Knokgnmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Knokgnmst {
	char    userid[9];
	char    systemid[11];
	char    sykiokflg;
	char    nrykokflg;
	char    sysiokflg;
	char    sntnokflg;
	char    knjaokflg;
	char    generalflg[101];
	char    staymd[11];
	char    endymd[11];
	char    trkymd[11];
	char    hnkymd[11];
}	Knokgnmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnokgnmstSelectAll( Knokgnmst** arrayOut, int* numOut );
long ZdbKnokgnmstSelectKey( Knokgnmst* pKey, Knokgnmst** arrayOut, int* numOut );
long ZdbKnokgnmstInsert( Knokgnmst* rec );
long ZdbKnokgnmstUpdate( Knokgnmst* rec );
long ZdbKnokgnmstDelete( Knokgnmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
