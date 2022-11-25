/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKenpos.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Kenpos_h_
#define _Kenpos_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kenpos {
	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knndh[27];
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    rakitjho;
	char    rakitjhossi[7];
	char    ksndh[27];
	char    trkdh[27];
}	Kenpos;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKenposSelectAll( Kenpos** arrayOut, int* numOut );
long ZdbKenposSelectKey( Kenpos* pKey, Kenpos** arrayOut, int* numOut );
long ZdbKenposInsert( Kenpos* rec );
long ZdbKenposUpdate( Kenpos* rec );
long ZdbKenposDelete( Kenpos* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
