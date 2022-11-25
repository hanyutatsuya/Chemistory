/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKnsseqknri.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-23                    Create
 **********************************************************************/
#ifndef _Knsseqknri_h_
#define _Knsseqknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Knsseqknri {
	char    knskisymd[11];
	char    knsgrp[17];
	char    traykbn;
	char    wssbt[11];
	sqlint32  wsno;
	sqlint32  knsseqmax;
	sqlint32  sytrymax;
	char    ksndh[27];
}	Knsseqknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnsseqknriSelectAll( Knsseqknri** arrayOut, int* numOut );
long ZdbKnsseqknriSelectKey( Knsseqknri* pKey, Knsseqknri** arrayOut, int* numOut );
long ZdbKnsseqknriInsert( Knsseqknri* rec );
long ZdbKnsseqknriUpdate( Knsseqknri* rec );
long ZdbKnsseqknriDelete( Knsseqknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
