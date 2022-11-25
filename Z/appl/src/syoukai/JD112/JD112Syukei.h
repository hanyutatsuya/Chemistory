/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FJD112Syukei.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-23                    Create
 *  1.01     2006-04-26     H.Suyama       BSKLNE�ǉ�
 *  1.03     2006-06-17     INTEC          �o��SEQ��10���P�ʂɍ쐬
 **********************************************************************/
#ifndef _JD112Syukei_h_
#define _JD112Syukei_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _JD112Syukei {
/* 1.03 DELL
DEL	char		jikan[3];
*/
	char		jikan[27];
	char		skflg;
	sqlint32	count;
	char		bskkbn[5];
	char		bskgok[7];
	char		bsklne[5];
}	JD112Syukei;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbJD112SelectCountA( char *pFromDh, char *ToDh, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountB( char *pFromDh, char *ToDh, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountC( char *pFromDh, char *ToDh, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountD( char *pFromDh, char *ToDh, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountE( char *pFromDh, char *ToDh, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountFGHIJ( char *pFromDt, char *pToDt, char *pWkupApp, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountKM( char *pFromDh, char *ToDh, char cKnsJkFlg, JD112Syukei** arrayOut, int* numOut );
long ZdbJD112SelectCountL( char *pFromDh, char *ToDh, JD112Syukei** arrayOut, int* numOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
