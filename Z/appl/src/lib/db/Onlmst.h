/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FOnlmst.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#ifndef _Onlmst_h_
#define _Onlmst_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Onlmst {
	short   oncode;
	char    kbn[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	short   protocol;
	char    wsname[17];
	short   opentype;
	sqlint32  portno;
	char    onpath[129];
	short   approtocol;
	sqlint32  errorlevel;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
}	Onlmst;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbOnlmstSelectAll( Onlmst** arrayOut, int* numOut );
long ZdbOnlmstSelectKey( Onlmst* pKey, Onlmst** arrayOut, int* numOut );
long ZdbOnlmstInsert( Onlmst* rec );
long ZdbOnlmstUpdate( Onlmst* rec );
long ZdbOnlmstDelete( Onlmst* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
