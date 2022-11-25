/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FWsseqknri.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Wsseqknri_h_
#define _Wsseqknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Wsseqknri {
	char    knskisymd[11];
	char    knsgrp[11];
	sqlint32  kmkcd;
	sqlint32  ctrlno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  knsseqsu;
	char    wsseqjkflg;
	char    ksndh[27];
}	Wsseqknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbWsseqknriSelectAll( Wsseqknri** arrayOut, int* numOut );
long ZdbWsseqknriSelectKey( Wsseqknri* pKey, Wsseqknri** arrayOut, int* numOut );
long ZdbWsseqknriInsert( Wsseqknri* rec );
long ZdbWsseqknriUpdate( Wsseqknri* rec );
long ZdbWsseqknriDelete( Wsseqknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
