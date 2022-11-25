/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FCmtmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Cmtmst_h_
#define _Cmtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Cmtmst {
	char    cmcd[6];
	char    cmtkg[3];
	char    cmtnm[83];
	char    cmtnmj[81];
	char    knskka1[13];
	char    kkahskcd[4];
	char    akaden;
	char    ijouchi;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Cmtmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbCmtmstSelectAll( Cmtmst** arrayOut, int* numOut );
long ZdbCmtmstSelectKey( Cmtmst* pKey, Cmtmst** arrayOut, int* numOut );
long ZdbCmtmstInsert( Cmtmst* rec );
long ZdbCmtmstUpdate( Cmtmst* rec );
long ZdbCmtmstDelete( Cmtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
