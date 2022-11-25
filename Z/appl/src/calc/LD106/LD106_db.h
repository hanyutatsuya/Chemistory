/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FLD106.h                                                      */
/* �@�T�@�@�@�v�F�p�����[�^�擾�w�b�_                                         */
/******************************************************************************/
/*  Ver.	���t		���O		�C�����e			*/
/* -------------------------------------------------------------------------- */
/*  0.00	2006/01/15	BML.Inc		�V�K�쐬			*/
/******************************************************************************/
#ifndef _LD106_db_h
#define _LD106_db_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

#include "LD106.h"
/******************************************************************************/
/* DB�p�\���̒�`                                                             */
/******************************************************************************/

//	�V�X�e���Ǘ��}�X�^���\����
typedef struct  _stSYSKNR 
{
        char    kjnsriymd[10+1];	// ������N����
        char    iriendflg[1+1];		// �˗�END�t���O
        char    bchendflg[1+1];		// ����END�t���O
        char    unyflg[1+1];		// �^�p�t���O
} my_stSYSKNR ;

typedef struct _stCALC
{
	char	utkymd[10+1];	// 1  �a�l�k��t�N����
	char	irino[11+1];	// 2  �˗����m��
	char	knsgrp[16+1];	// 3  �����O���[�v
	char	kmkcd[7+1];	// 4  ���ڃR�[�h
	char	sstcd[7+1];	// 5  �{�݃R�[�h
	char	zrcd[4+1];	// 6  �ޗ��R�[�h
	char	sc[5+1];	// 7  �g��
	char	tj[5+1];	// 8  �̏d
	char	tjtni[1+1];	// 9  �̏d�敪
	char	sbtkbn[1+1];	// 10 ���ʋ敪
	char	age[3+1];	// 11 �N��
	char	agekbn[1+1];	// 12 �N��敪
	char	tntme[4+1];	// 13 �~�A����
	char	tntni[1+1];	// 14 �~�A���ԋ敪
	char	tnryo[5+1];	// 15 �~�A��
	char	tnryotni[1+1];	// 16 �~�A�ʋ敪
} my_stCALC ;

typedef struct _stCALCSYSMST
{
	char	knsgrp[16+1];
	char	kmkcd[7+1];
	char	sstcd[7+1];
	char	zaicd[4+1];
	char	hkkbn[1+1];
	char	ksnsk[128+1];
	char	kaiymd[10+1];
	char	haiymd[10+1];
	char	hnktntid[8];
	char	ksndh[26+1];
} my_stCALCSYSMST ;

typedef struct _stKEKKA
{
	char		knskisymd[10+1];
	char		sriymd[10+1];
	char		kntno[13+1];
	char		kntketflg;
	char		knsgrp[16+1];
	char		kmkcd[7+1];
	short		knssu;
	short		knssueda;
	char		irihsmkbn;
	char		irikbn;
	char		ksktkbn;
	char		utkymd[10+1];
	char		irino[11+1];
	char		iriketflg;
	short		zssdino;
	char		sstcd[7+1];
	char		trid[10+1];
	short		trpos;
	char		asyrckid[10+1];
	short		asyrckpos;
	char		oyakmkcd[7+1];
	char		seccd[2+1];
	char		bkfkkbn;
	char		smpcd[7+1];
	char		bskkbn[4+1];
	char		bsklne[4+1];
	char		bskgok[6+1];
	sqlint32	bskseq;
	char		bskerrsts[2+1];
	char		sktdh[26+1];
	char		nbkmkcd[7+1];
	char		tstrflg;
	char		zrcd[4+1];
	char		ysnlbl[2+1];
	char		kjno[3+1];
	char		fkhkknohjkbn;
	char		tbkjno[3+1];
	char		tbkjflg;
	char		htkfkhms[24+1];
	char		skflg;
	char		tskflg[2+1];
	char		tktflg[2+1];
	char		jisksbr[15+1];
	char		kkflg;
	char		kkiriflg;
	short		kkirilotno;
	char		hsykflg;
	char		hskflg;
	char		hhkkflg;
	char		rawdata[20+1];
	char		knskka1[12+1];
	char		knskka2[24+1];
	char		knskka2kbn[2+1]; 
	char		kkahskcd[3+1];
	char		hjkka[24+1];
	char		sdi[3+1];
	char		kkacmt1[5+1];
	char		kkacmt2[5+1];
	char		kkajkcd;
	char		pncrgflg;
	char		knspncrgflg; 
	char		kkaksflg;
	char		kkassflg;
	char		ijkbnm;
	char		ijkbnf;
	char		ijkbnn;
	char		tbijkbnm;
	char		tbijkbnf;
	char		tbijkbnn;
	char		nbdolbl[2+1];
	char		nbdoerr[3+1];
	char		ykdolbl[2+1];
	char		ykdoerr[3+1];
	char		etclbl[2+1];
	char		etcerr[3+1];
	sqlint32	ctrlno;
	sqlint32	knsseq;
	short		bthno;
	sqlint32	pltno;
	sqlint32	pltseq;
	char		dtnrtts[8+1];
	char		dtnrdh[26+1];
	char		knskrdh[26+1];
	char		hkkdh[26+1];
	char		hkkkbdh[8+1];
	char		zkhkkyymd[10+1];
	char		zkhkkytme[4+1];
	char		frkkaflg;
	char		gzbsflg;
	char		hsiflg;
	char		kkaysnflg;
	char		tnyrkflg;
	char		siyflg;
	char		knsflg;
	char		renjicflg;
	char		soukn1flg;
	char		kanrenflg;
	char		bunkkuflg;
	char		kesseiflg;
	char		rirekiflg;
	char		syougoflg;
	char		keisanflg;
	char		per100flg;
	char		tousekflg;
	char		kisyakflg;
	char		kouseiflg;
	char		syoungflg;
	char		soukn2flg;
	char		fukaptflg;
	char		yobiflg01;
	char		tobiflg02;
	char		yobiflg03;
	char		yobiflg04;
	char		yobiflg05;
	char		skrycda[3+1];
	char		skrycdb[3+1];
	char		skrycdc[3+1];
	char		ksndh[26+1];
	char		trkdh[26+1];
	char		skkka[24+1];
} my_stKEKKA;

typedef struct _stKjnmst {
	char		kmkcd[8];
	char		kjno[4];
	char		kjsdino[3];
	char		zrcd[5];
	char		agerngkbn[3];
	char		etckbn[4];
	char		nichilw[6];
	char		nichihi[6];
	char		kjnmlw[9];
	char		kjnmhi[9];
	char		kjnflw[9];
	char		kjnfhi[9];
	char		kjnelw[9];
	char		kjnehi[9];
	char		genmlw[9];
	char		genmhi[9];
	char		genflw[9];
	char		genfhi[9];
	char		genelw[9];
	char		genehi[9];
	short		kjsstnksu;
	char		kjnmhkn[25];
	char		kjnmhkj[25];
	char		kjnfhkn[25];
	char		kjnfhkj[25];
	char		kjnohkn[25];
	char		kjnohkj[25];
	char		lwm1[9];
	char		lwm2[9];
	char		kjm1[9];
	char		kjm2[9];
	char		him1[9];
	char		him2[9];
	char		lwf1[9];
	char		lwf2[9];
	char		kjnnaf1[9];
	char		kjnnaf2[9];
	char		hif1[9];
	char		hif2[9];
	char		lwe1[9];
	char		lwe2[9];
	char		kje1[9];
	char		kje2[9];
	char		hie1[9];
	char		hie2[9];
	char		tankn[17];
	char		tankj[17];
	char		stjyken[61];
	char		kymstjn;
	char		kaiymd[11];
	char		haiymd[11];
	char		hnktntid[9];
	char		ksndh[27];
} my_stKJNMST;

typedef struct _stRngchkmst {
	char		hnikbn;
	char		knsgrp[17];
	char		kmkcd[8];
	char		zaicd[5];
	char		sstcd[8];
	char		sbt;
	char		ssa;
	char		zen_kyoyou;
	char		hrng[21];
	char		lrng[21];
	char		kaiymd[11];
	char		haiymd[11];
	char		hnktntid[9];
	char		ksndh[27];
} my_stRNGCHKMST;

typedef struct _stKkafltmst {
        char		knsgrp[17];
        char		kmkcd[8];
        char		fltkka[25];
        char		minval[13];
        char		maxval[13];
        char		knskka1[13];
        char		knskka2[25];
        char		knskka2kbn[3];
        char		kkahskcd[4];
        char		hjkka[25];
        char		kaiymd[11];
        char		haiymd[11];
        char		hnktntid[9];
        char		ksndh[27];
        char		sstcd[8];
        char		tkykbn[2];
} my_stKKAFLTMST;

#endif
/** End of File *********************************************************/
