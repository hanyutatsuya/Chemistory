/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FBscmtmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Bscmtmst_h_
#define _Bscmtmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Bscmtmst {
	sqlint32  bscmtcd;
	sqlint32  gyono;
	char    bscmt[101];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Bscmtmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbBscmtmstSelectAll( Bscmtmst** arrayOut, int* numOut );
long ZdbBscmtmstSelectKey( Bscmtmst* pKey, Bscmtmst** arrayOut, int* numOut );
long ZdbBscmtmstInsert( Bscmtmst* rec );
long ZdbBscmtmstUpdate( Bscmtmst* rec );
long ZdbBscmtmstDelete( Bscmtmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
