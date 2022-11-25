/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FApllog.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Apllog_h_
#define _Apllog_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Apllog {
	char    sydate[11];
	char    sytime[9];
	char    tracekbn;
	char    pcname[33];
	sqlint32  proccessid;
	char    loginid[9];
	char    wkupapp[33];
	char    srcname[33];
	char    funcname[33];
	sqlint32  getline;
	char    procflg[3];
	char    errcode[9];
	char    message[1025];
}	Apllog;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbApllogSelectAll( Apllog** arrayOut, int* numOut );
long ZdbApllogSelectKey( Apllog* pKey, Apllog** arrayOut, int* numOut );
long ZdbApllogInsert( Apllog* rec );
long ZdbApllogUpdate( Apllog* rec );
long ZdbApllogDelete( Apllog* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
