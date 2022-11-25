/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FBssikka.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Bssikka_h_
#define _Bssikka_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Bssikka {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   bssino;
	short   gyono;
	char    bssidt[129];
	char    ksndh[27];
}	Bssikka;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbBssikkaSelectAll( Bssikka** arrayOut, int* numOut );
long ZdbBssikkaSelectKey( Bssikka* pKey, Bssikka** arrayOut, int* numOut );
long ZdbBssikkaInsert( Bssikka* rec );
long ZdbBssikkaUpdate( Bssikka* rec );
long ZdbBssikkaDelete( Bssikka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
