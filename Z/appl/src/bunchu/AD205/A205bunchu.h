/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FA205bunchu.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _A205bunchu_h_
#define _A205bunchu_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Bunchu {
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sriymd[11];		//������
	char    kntno[14];		//����No
	char    kntketflg;
	char    smpcd[8];
	char    kmkcd[8];
	short   smpcditno;
	char    chkmj[5];
	char    trid[11];		//�g���[ID
	short   trpos;			//�g���[�|�W�V����
	char    asyrckid[11];	//�A�b�Z�C���b�NID
	short   asyrckpos;		//�A�b�Z�C���b�N�|�W�V����
	char    id2[11];
	short   id2pos;
	char    sbtkbn;
	char    age[4];
	char    agekbn;
	char    tntme[5];		//�{�A����
	char    tntni;			//�{�A���ԋ敪
	char    tnryo[6];		//�{�A��
	char    tnryotni;		//�{�A�ʋ敪
	char    sstcd[8];		//�{�݃R�[�h
	char    ecd[4];
	char    bckid[4];
	char    jtflg;
	char    knssyr;
	char    tknflg;
	char    ttkkflg;
	char    bnckka;
	short   srtkey;
	char    ksndh[27];
	char    trkdh[27];
}	Bunchu;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ABunSelKey( Bunchu* pKey, Bunchu** arrayOut, int* numOut );
long ABunBunIns( Bunchu* rec );
long ABunUpdate( Bunchu* rec );

// Add 2007.05.08 waj
long ABunSelAllKey( Bunchu* pKey, Bunchu** arrayOut );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
