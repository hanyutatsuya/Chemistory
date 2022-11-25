/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FEigmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Eigmst_h_
#define _Eigmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Eigmst {
	char    ecd[4];
	char    shcdfr[3];
	char    shcdto[3];
	char    skecd[4];
	char    skshcd[3];
	char    skcsnm[21];
	char    eigkn[21];
	char    eigkj[21];
	char    eitelno[13];
	char    eifaxno[13];
	char    yjhkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Eigmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbEigmstSelectAll( Eigmst** arrayOut, int* numOut );
long ZdbEigmstSelectKey( Eigmst* pKey, Eigmst** arrayOut, int* numOut );
long ZdbEigmstInsert( Eigmst* rec );
long ZdbEigmstUpdate( Eigmst* rec );
long ZdbEigmstDelete( Eigmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
