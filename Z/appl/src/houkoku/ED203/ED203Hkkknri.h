/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FED203Hkkknri.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-13                    Create
 **********************************************************************/
#ifndef _ED203Hkkknri_h_
#define _ED203Hkkknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Hkkknri {
	char    hkksjymd[11];
	sqlint32  hkksjno;
	char    hkkkbn;
	char    hkkjkn;
	char    knskisymd[11];
	char    utkymd[11];
	char    sriymd[11];
	char    knsgrp[17];
	char    kmkcd[8];
	char    bskkbn[5];
	char    bskgok[7];
	char    hkkjknst[21];
	char    hkkjkned[21];
	char    seccd[3];
	char    hkkflnm[51];
	char    hkksjtts[9];
	char    hkkdh[27];
	char    hkkstdh[27];
	char    hkkeddh[27];
	char    tnsstdh[27];
	char    tnseddh[27];
	sqlint32  hkkssknsu;
	sqlint32  hkkhrysu;
	char    ssnmtfilid[13];
	char    hkkjkflg[3];
	char    hkkerrcode[9];
	short   kkirilotno;
	char    ksndh[27];
}	Hkkknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbHkkknriED203SelectAll( Hkkknri** arrayOut, int* numOut );
long ZdbHkkknriED203Update( Hkkknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
