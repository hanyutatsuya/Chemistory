/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FKoseiKaHi.sqc                                                */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2007/04/08     INTEC.INC      CREATE                             */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/10/09     K.Ameno        �����Z���Ή�                       */
/*  2.01     2009/03/13     H.Sekiya       double�^�̔�r���@�C��             */
/******************************************************************************/

/******************************************************************************/
/* �C���N���|�h�錾                                                           */
/******************************************************************************/
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sqlca.h>
#include    <math.h>
#include    "FD103.h"

/*********************************************************************/
/* �}���`������p(chk_kousei.c)                                      */
/* �������� ��                                                       */
static  void    stat_calc( x,y,zz )
/*********************************************************************
*fc
*     ���v�����p�v�Z�֐�
*rt
*nt
    �{�����ɂĂm ���w ���x ���i�w�E�x�j ���w�E�w ���x�E�x
    ���v�Z���\���̂̎����G���A�֊i�[���܂��B
    �A���A�w or �x �����l�łȂ��ꍇ�͑ΏۂƂ��܂���B
*ag
*********************************************************************/
char        *x;     /* [i] �w�l */
char        *y;     /* [i] �x�l */
TOUKEI_CALC *zz;    /* [o] ���v�p�\���̂̃|�C���^ */
{
    double  dx;
    double  dy;

    dx  =   ( double )atof( x );
    dy  =   ( double )atof( y );

    zz->n   =   zz->n + 1;

    zz->sumx    =   zz->sumx + dx;
    zz->sumy    =   zz->sumy + dy;
    zz->sumxy   =   zz->sumxy + ( dx * dy );
    zz->sumxx   =   zz->sumxx + ( dx * dx );
    zz->sumyy   =   zz->sumyy + ( dy * dy );

}

static  void    kousei_func( zz,place,a,b )
/*********************************************************************
*fc
*     �Z���W���v�Z�֐�
*rt
*nt
    �Z���p�t�@�N�^�|(a)�A�x�|�X(b) �����ߏo�͂���B

    �t�@�N�^�|�F
                �@�@�@�@�@�@�@�@�@�@���x�E���w
        �@�@�@�@���i�w�E�x�j�@�|    �|�|�|�|�|
        �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�m
        �`�@���@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
         �@�@�@�@�@�@�@�@�@�@�@�@�@�i���w�j^�Q
         �@�@�@�@���i�w^�Q�j�@�|�@�@�|�|�|�|�|
        �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�m

    �x�|�X�F
        �a�@���@AVE�i�x�j�@�|�@�`�EAVE�i�w�j
        �i�x�|�X�́A���ڂ̏����_�����ɕҏW���s�Ȃ��B�j

    �i���A���ꂪ�O�̏ꍇ�́ACHK_lst_hensyu() �ɂ����� a=1.00 b=0 �ɕҏW
    ���邽�߁A"********","********"��ݒ肵�Ă����B")

*ag
*********************************************************************/
TOUKEI_CALC zz;         /* [i] ���v�p�\����   */
int         place;      /* [i] �����_����     */
char        *a;         /* [o] �Z���t�@�N�^�| */
char        *b;         /* [o] �Z���x�|�X     */
{

    double  da;
    double  db;
    double    bunbo;

    bunbo    = zz.sumxx -  ( pow(zz.sumx,2.0) / ( zz.n + 1.0 ) ) ;

    if( bunbo == 0 ){

        sprintf(a,"********");
        sprintf(b,"********");
        return;

    }else{

        da = ( zz.sumxy - ( zz.sumx * zz.sumy )/( zz.n + 1.0 ) ) / bunbo;
        db = zz.sumy/( zz.n + 1.0 ) - da * ( zz.sumx / ( zz.n + 1.0 ) );

    }

    /* �����_�����ҏW */
    sprintf(a,"%8.*f",2    ,da);
    sprintf(b,"%8.*f",place,db);

    /* -0.0�Ή� */
    if( atof(a) == 0 ){
        da = 0;
        sprintf(a,"%8.*f",2    ,da);
    }
    if( atof(b) == 0 ){
        db = 0;
        sprintf(b,"%8.*f",place,db);
    }

}
/* �����܂� ��                                                      */
/* �}���`������p(chk_kousei.c)                                     */
/********************************************************************/

/********************************************************************
    �t�@�N�^�E�x�|�X�̏�ԃ`�F�b�N
      double�^���m�̔�r�����Ă������߁A�듮�씭���B
      ��r���@���C������
    0:    ����
    1:    �Z���\
    2:    �đ���
    3:    �Z���W���v�Z�s�\
*********************************************************************/
static int lst_hantei(
KTLIST *kt, char* fact, char* base)
{

    char    func_nm[MYAPP_LEN_FNCNM+1];             /* �֐����� */
    double  fc,fc1,fc2;        /* �t�@�N�^�| */
    double  bs,bs1,bs2;        /* �x�|�X     */
	int     ret_fc;
	int     ret_bs;

    /* �������� */
    strcpy( func_nm, "lst_hantei" );

    if (strncmp(fact,"*",1) == 0){
        fc = 1.00;
        bs = 0.00;
        sprintf(fact, "%8.*f", 2, fc);
        sprintf(base, "%8.*f", kt->sstnksu, bs);
        return(3);
    }

    int     flgF, flgB;
    fc  = fabs(1.0 - (double)atof(fact)); /* �t�@�N�^(a) �� 1.0 - fact �̐�Βl */
    fc1 = (double)atof(kt->facterjd1);    /* CTRLMST�F�t�@�N�^�[����1 */
    fc2 = (double)atof(kt->facterjd2);    /* CTRLMST�F�t�@�N�^�[����2 */
    bs  = (double)atof(base);             /* �x�[�X(a) (VB�ł͐�Βl�����߂Ă��Ȃ�) */
    bs1 = (double)atof(kt->basejd1);      /* CTRLMST�F�x�[�X����1 */
    bs2 = (double)atof(kt->basejd2);      /* CTRLMST�F�x�[�X����2 */

	/* �t�@�N�^���� */
	ret_fc = chkLowHigh(fc1, fc, 2);
	/* �t�@�N�^���� : CTRLMST�F�t�@�N�^�[����1 >= �t�@�N�^(a) */
	if ((ret_fc == 0) || (ret_fc == 1)) {
		flgF = 0;
	} else if (ret_fc == 2) {
		 ret_fc = chkLowHigh(fc2, fc, 2);
		/* �t�@�N�^�Z���Ώ� : CTRLMST�F�t�@�N�^�[����1 < �t�@�N�^(a) <= CTRLMST�F�t�@�N�^�[����2 */
		if ((ret_fc == 0) || (ret_fc == 1)) {
			flgF = 1;
	    } else if (ret_fc == 2) {
		/* �t�@�N�^�đ��� : CTRLMST�F�t�@�N�^�[����2 < �t�@�N�^(a) */
			flgF = 2;
		} else {
		/* �t�@�N�^�Z���ُ� */
			flgF = 3;
		}
	} else {
	/* �t�@�N�^�Z���ُ� */
		flgF = 3;
	}

	/* �x�[�X���� */
	ret_bs = chkLowHigh(bs1, bs, 2);
	/* �x�[�X���� : CTRLMST�F�x�[�X����1 >= �x�[�X(a) */
	if ((ret_bs == 0) || (ret_bs == 1)) {
		flgB = 0;
	} else if (ret_bs == 2) {
		ret_bs = chkLowHigh(bs2, bs, 2);
		/* �x�[�X�Z���Ώ�  CTRLMST�F�x�[�X����1 < �x�[�X(a) <= CTRLMST�F�x�[�X����2 */
		if ((ret_bs == 0) || (ret_bs == 1)) {
			flgB = 1;
		 } else if (ret_bs == 2) {
		/* �x�[�X�đ��� : CTRLMST�F�x�[�X����2 < �x�[�X(a) */
			flgB = 2;
		} else {
		/* �t�@�N�^�Z���ُ� */
			flgB = 3;
		}
	/* �x�[�X�Z���ُ� */
	} else {
		flgB = 3;
	}

//	/* �t�@�N�^���� */
//	/* CTRLMST�F�t�@�N�^�[����1 >= �t�@�N�^(a) */
//	if (fc1 >= fc)
//		/* �t�@�N�^���� */
//	flgF = 0;
//	/* CTRLMST�F�t�@�N�^�[����1 < �t�@�N�^(a) <= CTRLMST�F�t�@�N�^�[����2 */
//	else
//	if ( && (fc <= fc2))
//		/* �t�@�N�^�Z���Ώ� */
//		flgF = 1;
//	/* CTRLMST�F�t�@�N�^�[����2 < �t�@�N�^(a) */
//	else
//	if (fc2 < fc)
//		/* �t�@�N�^�đ��� */
//		flgF = 2;
//	else
//		/* �t�@�N�^�Z���ُ� */
//		flgF = 3;
//
//	/* �x�[�X���� */
//	/* CTRLMST�F�x�[�X����1 >= �x�[�X(a) */
//	if (bs1 >= bs)
//		/* �x�[�X���� */
//		flgB = 0;
//	/* CTRLMST�F�x�[�X����1 < �x�[�X(a) <= CTRLMST�F�x�[�X����2 */
//	else
//	if ((bs1 < bs) && (bs <= bs2))
//		/* �x�[�X�Z���Ώ� */
//		flgB = 1;
//	/* CTRLMST�F�x�[�X����2 < �x�[�X(a) */
//	else
//	if (bs2 < bs)
//		/* �x�[�X�đ��� */
//		flgB = 2;
//	else
//		/* �x�[�X�Z���ُ� */
//		flgB = 3;

        {/* DEBUG WRITE */
			sprintf(G_msg, "�t�@�N�^[%f] �t�@�N�^�����P[%f] �t�@�N�^�����Q[%f] �t�@�N�^�t���O�%d] �x�[�X[%f] �x�[�X�����P[%f] �x�[�X�����Q[%f] �x�[�X�t���O[%d]\n", fc, fc1, fc2, flgF, bs, bs1, bs2, flgB);
            LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        }

	/* �t�@�N�^�E�x�[�X�̔��茋�ʂ��烌���W�̔�����s�� */
	/* �t�@�N�^���큕�x�[�X���� */
	if ((flgF == 0) && (flgB == 0)) {
		return (0); /* ���� */
	/* (�t�@�N�^���� or �t�@�N�^�Z���Ώ�) and (�x�[�X���� or �x�[�X�Z���Ώ�) */
	} else if (((flgF == 0) || (flgF == 1)) && ((flgB == 0) || (flgB == 1))) {
		return (1); /* �Z���\ */
	/* �t�@�N�^�đ��� or �x�[�X�đ��� �� �d�l���ł́A�t�@�N�^�đ��� and �x�[�X�đ��� �ǂ����H */
	} else if ((flgF == 2) || (flgB == 2)) {
		return (2); /* �đ��� */
	} else {
		return (3); /* �Z���m�f */
	}
	
	return (0);
}

/******************************************************************************/
/*  �� �� ��  �FKoseiKaHi                                                     */
/*  �@�\�T�v  �F�Z���۔���                                                  */
/*  ��    ��  �F                                                              */
/*   ��P���� �FKTLIST * allKt	: �Z���Ώۃ��X�g                              */
/*   ��Q���� �Fint      tPos	: �Z���Ώۃ��X�g�Y���f�[�^�ʒu                */
/*   ��R���� �Fint      pPos	: �Z���Ώۃ��X�g�O�R���g���[���ʒu            */
/*   ��S���� �FATKSTS * at		: �����Z�����                                */
/*   ��T���� �Fint      kensu  : �Z���Ώۃ��X�g����                          */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRH_NORMAL    ����I��                                         */
/*            �FRH_KOUSEI	 �Z���Ώ�                                         */
/*            �FKOUSEI_IJOU  �ُ�I��                                         */
/******************************************************************************/
int KoseiKaHi(
	KTLIST*	allKt,
	int		tPos,
	int		pPos,
	ATKSTS* at,
	int*    histCnt,
	int		kensu)
{
    char    	func_nm[MYAPP_LEN_FNCNM+1];             /* �֐����� */
	TOUKEI_CALC zz;    									/* ���v�p�\���� */
	KTLIST* 	kt		= allKt+tPos;					/* �ΏۃR���g���[�� */
	KTLIST* 	prevKt	= allKt+pPos;					/* �O�R���g���[�� */
    int     	ret		= RH_NORMAL;
	int			top		= 0;
	int			next	= 0;
	int			pos;
	
	char		fact[9];
	char		base[9];

    /* �������� */
    strcpy( func_nm, "KoseiKaHi" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	if (kt->ctrlno - 1 != prevKt->ctrlno) {
		/* �R���g���|���ԍ����A�ԂɂȂ��Ă��Ȃ� */
		/* ����ł͓��Ƀ`�F�b�N�ΏۂƂ͂��Ȃ� */
	}

	/* �O�̃R���g���|�����ُ�Ȃ��Ώ� */
	if (prevKt->nonecnt != 0 || prevKt->ngcnt != 0) {
		/* autokosiflg(�����Z���Ώۃt���O) = '0' (�Z���ΏۊO) */
		/* causecd(�Z���ΏۊO���R�R�[�h)   = KSTS_CTRLNG (4)  */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_CTRLNG);

        sprintf(G_msg, "�O�̃R���g���|�����ُ�i%s,%s,%d�j�F%d",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno,prevKt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		/* KOUSEI_IJOU (3) */
		return KOUSEI_IJOU;
	}

	/* �q�X�g�K�����`�F�b�N : �K�����͂T�ȏ�łȂ��Ɣ��菈�����o���Ȃ� */
	if (kt->hstkaikyu < 5) {
		/* autokosiflg(�����Z���Ώۃt���O) = '0' (�Z���ΏۊO) */
		/* causecd(�Z���ΏۊO���R�R�[�h)   = KSTS_HIST (5)    */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_HIST);

        sprintf(G_msg, "�q�X�g�K�������T�����i%s,%s,%d�j�F%d",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno,kt->hstkaikyu);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		/* KOUSEI_IJOU (3) */
		return KOUSEI_IJOU;
	}

	/* �����W���� */

	/* �W�v */
	/* �Z���ΏۃR���g���[���y�эZ���Ώ�(�O)�R���g���[���̑���l�� */
	/* ���ϒl(�����`���l���̂���)�̏W�v���`���l���ōs�� */
	/* X���R���g���[������l�Ƃ��AY�𕽋ϒl�Ƃ����ꍇ�̈ȉ��̑��a���Ƃ�B */
	/* �� ��X�A��Y�A��(X�EY)�A��(X�EX)�A��(Y�EY) */
	{
		/* ���v�����\���̏����� */
		memset(&zz, 0, sizeof(zz));

		/* �܂��͑O�R���g���[������ */
		top  = SearchTopControlPosition(allKt, pPos, 0);
		next = SearchNextControlPosition(allKt, pPos, kensu, 0);
		for (pos = top; pos < next; pos++)
			/* void stat_calc(x, y, zz)                           */
			/* (i)x  : ����l(�R���g���[���̑���l)               */
			/* (i)y  : ���ϒl(�R���g���[���}�X�^�e�[�u���̕��ϒl) */
			/* (o)zz : �W�v�p�\����                               */
			stat_calc((allKt+pos)->sktti, (allKt+pos)->ctrlx, &zz);

		/* �����đΏۃR���g���[�������� */
		top  = SearchTopControlPosition(allKt, tPos, 0);
		next = SearchNextControlPosition(allKt, tPos, kensu, 0);
		for (pos = top; pos < next; pos++)
			/* void stat_calc(x, y, zz)                           */
			/* (i)x  : ����l(�R���g���[���̑���l)               */
			/* (i)y  : ���ϒl(�R���g���[���}�X�^�e�[�u���̕��ϒl) */
			/* (o)zz : �W�v�p�\����                               */
			stat_calc((allKt+pos)->sktti, (allKt+pos)->ctrlx, &zz);
	}

	/* �Z���W���Z�o */
	/* ��L�̏W�v�ŎZ�o�����W�v�l(zz)�Ə����_����(�����`���l���̂���)�Ńt�@�N�^�y�уx�[�X���Z�o����B */
	memset(fact, 0, sizeof(fact));
	memset(base, 0, sizeof(base));
	/* void kousei_func(zz, place, a, b)                 */
	/* (i)zz    : �W�v�l                                 */
	/* (i)place : �����_����(�R���g���[���}�X�^�e�[�u��) */
	/* (o)a     : �t�@�N�^                               */
	/* (o)b     : �x�[�X                                 */
	kousei_func(&zz, kt->sstnksu, fact, base);
	at->facter = atof(fact);
	at->base   = atof(base);

/* #	ifdef DEBUG_DET */
	{/* DEBUG WRITE */
		sprintf(G_msg, "�Z���W�� %s %s %s %d : FACTER = %8.2f BASE = %8.*f\n",
				 kt->bskkbn, kt->bskgok, kt->nbkmkcd, kt->ctrlno, at->facter, kt->sstnksu, at->base);
        LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
/* #	endif */

	/* ���� */
	ret = lst_hantei(kt, fact, base);

	switch (ret) {
	case 0: /* ���� */
#	ifdef DEBUG_HIST
		/* �q�X�g�֘A�`�F�b�N�̂��ߋ����I�ɐ���f�[�^���Z���ΏۂƂ��ď������� */
        sprintf(G_msg, "�Z���Ώ� DEBUG HIST�i%s,%s,%d�j",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_KOUSEI (1) */
		return RH_KOUSEI;
#	endif
		/* ����l�̂��ߍZ���ΏۊO */
		/* autokosiflg(�����Z���Ώۃt���O) = '0' (�Z���ΏۊO) */
		/* causecd(�Z���ΏۊO���R�R�[�h)   = KSTS_NORMAL (1)  */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_NORMAL);

        sprintf(G_msg, "����l�̂��ߍZ���ΏۊO�i%s,%s,%d�j",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_NORMAL (0) */
		return RH_NORMAL;
	case 1:
		/* �Z���Ώ� */
        sprintf(G_msg, "�Z���Ώہi%s,%s,%d�j",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_KOUSEI (1) */
		return RH_KOUSEI;
	case 2:
		/* �Č����K�v�ȃf�[�^�̂��߁A�����̓X�L�b�v�i���񏈗��ɂ܂킷�j */
        sprintf(G_msg, "�Č����K�v�ȃf�[�^�i%s,%s,%d�j",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_SAIKEN (2) */
		return RH_SAIKEN;
	case 3: /* �Z���ُ� */
	default:
		/* �Z���ُ�E���̑� */
		/* autokosiflg(�����Z���Ώۃt���O) = '0' (�Z���ΏۊO)  */
		/* causecd(�Z���ΏۊO���R�R�[�h)   = KSTS_FB_CALC (8)  */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_FB_CALC);

        sprintf(G_msg, "�Z���ُ�E���̑��i%s,%s,%d�j",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* KOUSEI_IJOU (3) */
        return KOUSEI_IJOU;
	}

	/* ���ۂɂ͒ʂ�Ȃ� */
    LogOut(LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__);
	/* RH_NORMAL (0) */
	return RH_NORMAL;
}

/**********************************************************************/
/*	�� �� ��	�FchkLowHigh                                          */
/*	�@�\�T�v	�Fdouble�^�̒l�̑召�`�F�b�N                          */
/*	 ��P����	:double	: hikaku1	: ��r�ΏۂP                      */
/*	 ��Q����	:double	: hikaku2	: ��r�ΏۂQ                      */
/*	 ��R����	:int	: ketasu	: ��r����Ώۂ̌���              */
/*   �߂�l		: 0 : ��r�ΏۂP �� ��r�ΏۂQ                        */
/*				: 1 : ��r�ΏۂP �� ��r�ΏۂQ                        */
/*				: 2 : ��r�ΏۂP �� ��r�ΏۂQ                        */
/**********************************************************************/
int chkLowHigh(
	double	hikaku1,
	double	hikaku2,
    int     ketasu)
{
	int val1;
	int val2;
	int ret;

	char    func_nm[MYAPP_LEN_FNCNM+1];             /* �֐����� */

	/* �������� */
	strcpy( func_nm, "chkLowHigh" );

	/* ���� + 1 �̈ʂŎl�̌ܓ�����int�^�ɕϊ� */
	val1 = (int)floor((hikaku1 * pow(10, ketasu)) + 0.5);
	val2 = (int)floor((hikaku2 * pow(10, ketasu)) + 0.5);

	/* ��r���ʂ�Ԃ� */
	if (val1 == val2)
        ret = 0;
	else
	if (val1 > val2)
		ret = 1;
	else
	if (val1 < val2)
		ret = 2;
	else
		ret = 3;

	{/* DEBUG WRITE */
		sprintf(G_msg, "��r�����%d] ��r��[%f]����r��[%d] ��r��[%f]����r��[%d] ���^�[���%d]\n", ketasu, hikaku1, val1, hikaku2, val2, ret);
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}

	return ret;

}
