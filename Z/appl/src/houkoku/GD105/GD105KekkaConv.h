/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FGD105KekkaConv.h
 *     �@�\�T�v  �F
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-19     K.Moriya       ���ʕϊ��}�X�^�Ή�
 **********************************************************************/
#ifndef _GD105KekkaConv_h_
#define _GD105KekkaConv_h_

#include "bml_DBCom.h"

/*--------------------------------------
// �e�[�u���\���̒�`
*/
typedef struct _KekkaConv {
    char    knskisymd[10+1];
    char    sriymd[10+1];
    char    kntno[13+1];
    char    knsgrp[16+1];
    char    kmkcd[7+1];
    short   knssu;
    short   knssueda;
    char    knskka1[12+1];
    char    knskka2[24+1];
    char    knskka2kbn[2+1];
    char    kkahskcd[3+1];
    char    dtnrtts[8+1];
    char    skkka[24+1];
}   KekkaConv;

/*--------------------------------------
 * �֐��v���g�^�C�v
 */
#ifdef __cplusplus
extern "C" {
#endif

long dGD105UpdKekkaConv( KekkaConv* rec );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
