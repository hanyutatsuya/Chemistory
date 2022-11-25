/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FA205ninsiki.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _A205ninsiki_h_
#define _A205ninsiki_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Ninsiki {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    chkmj[5];
	char    asyrckid[11];
	short   asyrckpos;
	char    id2[11];
	short   id2pos;
	char    id3[11];
	short   id3pos;
	char    fuksuhn;
	char    ksndh[27];
	char    trkdh[27];
}	Ninsiki;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ABunNnskIns( Ninsiki* rec );
long ABunNinUp( Ninsiki* rec );
long ABunNinUpAll( Ninsiki* rec );
long ABunNinSelKey( Ninsiki* pKey, Ninsiki** arrayOut, int* numOut );
#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
