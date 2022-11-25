/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FXeerrmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Xeerrmst_h_
#define _Xeerrmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Xeerrmst {
	short   errflg;
	char    flgsbt[11];
	char    errname[33];
	short   sksri;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Xeerrmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXeerrmstSelectAll( Xeerrmst** arrayOut, int* numOut );
long ZdbXeerrmstSelectKey( Xeerrmst* pKey, Xeerrmst** arrayOut, int* numOut );
long ZdbXeerrmstInsert( Xeerrmst* rec );
long ZdbXeerrmstUpdate( Xeerrmst* rec );
long ZdbXeerrmstDelete( Xeerrmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
