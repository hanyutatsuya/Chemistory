/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FXbarm.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Xbarm_h_
#define _Xbarm_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Xbarm {
	char    knskisymd[11];
	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
	sqlint32  pltno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  bskseqst;
	sqlint32  bskseqed;
	short   pltseqst;
	short   pltseqed;
	short   pltsu;
	char    xbarmkka[25];
	char    xbarmjtkbn;
	char    xbarmjkflg;
	char    ksndh[27];
}	Xbarm;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbXbarmSelectAll( Xbarm** arrayOut, int* numOut );
long ZdbXbarmSelectKey( Xbarm* pKey, Xbarm** arrayOut, int* numOut );
long ZdbXbarmInsert( Xbarm* rec );
long ZdbXbarmUpdate( Xbarm* rec );
long ZdbXbarmDelete( Xbarm* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
