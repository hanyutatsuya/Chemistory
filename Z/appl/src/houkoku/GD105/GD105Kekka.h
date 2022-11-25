/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FGD105Kekka.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-07                    Create
 *  1.01     2007-06-14     waj            ���x�A�b�v�̂��ߕs�v�ȍ��ڂ��폜
 *  2.00     2009-05-19     K.Moriya       ���ʕϊ��}�X�^�Ή�
 **********************************************************************/
#ifndef _GD105Kekka_h_
#define _GD105Kekka_h_

#include "bml_DBCom.h"
#include "GD105Hkkknri.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _Kekka {
    char    knskisymd[11];
    char    sriymd[11];
    char    kntno[14];
    char    knsgrp[17];
    char    kmkcd[8];
    short   knssu;
    short   knssueda;
    char    utkymd[11];
    char    irino[12];
    char    sstcd[8];
    char    oyakmkcd[8];
    char    seccd[3];
    char    smpcd[8];
    char    bskkbn[5];
    char    bskgok[7];
    char    zrcd[5];
    char    kjno[4];
    char    skflg;
    char    kkflg;
    short   kkirilotno;
    char    hsykflg;
    char    hskflg;
    char    hhkkflg;
    char    knskka1[13];
    char    knskka2[25];
    char    knskka2kbn[3];
    char    kkahskcd[4];
    char    sdi[4];
    char    kkacmt1[6];
    char    kkacmt2[6];
    char    kkajkcd;
    char    pncrgflg;
    char    kkaksflg;
    char    kkassflg;
    char    ijkbnm;
    char    ijkbnf;
    char    ijkbnn;
    sqlint32  ctrlno;
    sqlint32  knsseq;
    sqlint32  pltno;
    char    hkkdh[27];
    char    knsflg;
    char    ksndh[27];
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� START */
    char    skkka[24+1];
/* 2.00 2009.05.19 ���ʕϊ��}�X�^�Ή� END */
}   Kekka;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long ZdbKekkaGD105SelectByCtrlNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut );
long ZdbKekkaGD105SelectByPltNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut );
long ZdbKekkaGD105SelectByKnsSeq( Hkkknri* pKey, Kekka** arrayOut, int* numOut );
long ZdbKekkaGD105SelectByIriNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut );
long ZdbKekkaGD105SelectByKntNo( Hkkknri* pKey, Kekka** arrayOut, int* numOut );
long ZdbKekkaGD105Update( Kekka* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
