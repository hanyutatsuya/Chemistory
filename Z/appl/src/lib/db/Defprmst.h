/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FDefprmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Defprmst_h_
#define _Defprmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Defprmst {
	char    compnm[21];
	char    tyhyoid[21];
	char    prntrnm[21];
	char    cstno;
	char    hnktntid[9];
	char    ksndh[27];
}	Defprmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbDefprmstSelectAll( Defprmst** arrayOut, int* numOut );
long ZdbDefprmstSelectKey( Defprmst* pKey, Defprmst** arrayOut, int* numOut );
long ZdbDefprmstInsert( Defprmst* rec );
long ZdbDefprmstUpdate( Defprmst* rec );
long ZdbDefprmstDelete( Defprmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
