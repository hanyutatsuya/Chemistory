/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FA205wsseq.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _A205wsseq_h_
#define _A205wsseq_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Wsseqknri {
	sqlint32 wstbnknr;
	char    knskisymd[11];
	char    knsgrp[17];
	char    wssbt[11];
	sqlint32  wsno;
	sqlint32  knsseqst;
	sqlint32  knsseqed;
	sqlint32  knsseqsu;
	char    ksktkbn;
	char    dtnrtts[9];
	char    ksndh[27];
}	Wsseqknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long A205wsAllSel( Wsseqknri** arrayOut, int* numOut );
long A205wsInsert( Wsseqknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
