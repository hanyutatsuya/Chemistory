/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FTrrakhmzk.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Trrakhmzk_h_
#define _Trrakhmzk_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Trrakhmzk {
	char    knskisymd[11];
	char    bnctrid[11];
	short   bnctrpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    jhstksk;
	char    knsstflg;
	char    ksndh[27];
}	Trrakhmzk;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbTrrakhmzkSelectAll( Trrakhmzk** arrayOut, int* numOut );
long ZdbTrrakhmzkSelectKey( Trrakhmzk* pKey, Trrakhmzk** arrayOut, int* numOut );
long ZdbTrrakhmzkInsert( Trrakhmzk* rec );
long ZdbTrrakhmzkUpdate( Trrakhmzk* rec );
long ZdbTrrakhmzkDelete( Trrakhmzk* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
