/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FTrayknri.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Trayknri_h_
#define _Trayknri_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Trayknri {
	char    knskisymd[11];
	char    trid[11];
	char    uktrdh[27];
	char    uktrtts[9];
	char    instkdh[27];
	char    instkno[11];
	short   instksu;
	char    outstkdh[27];
	char    outstkno[11];
	short   outsksu;
	char    ksndh[27];
}	Trayknri;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbTrayknriSelectAll( Trayknri** arrayOut, int* numOut );
long ZdbTrayknriSelectKey( Trayknri* pKey, Trayknri** arrayOut, int* numOut );
long ZdbTrayknriInsert( Trayknri* rec );
long ZdbTrayknriUpdate( Trayknri* rec );
long ZdbTrayknriDelete( Trayknri* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
