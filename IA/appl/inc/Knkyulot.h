/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FKnkyulot.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _Knkyulot_h_
#define _Knkyulot_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Knkyulot {
	char    knskisymd[11];
	char    seccd[3];
	short   kkirilotno;
	char    jsndh[27];
	char    hkkdh[27];
	char    ksndh[27];
}	Knkyulot;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKnkyulotSelectAll( Knkyulot** arrayOut, int* numOut );
long ZdbKnkyulotSelectKey( Knkyulot* pKey, Knkyulot** arrayOut, int* numOut );
long ZdbKnkyulotInsert( Knkyulot* rec );
long ZdbKnkyulotUpdate( Knkyulot* rec );
long ZdbKnkyulotDelete( Knkyulot* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
