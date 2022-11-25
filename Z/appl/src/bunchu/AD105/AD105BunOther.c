/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FAD105Buntekai.c								*/
/*		�T�v		�F�������W�J����(���̑�����)					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/14		E.Osada			Create					*/
/*  2.01	2006/10/24		INTEC			chkBunchu�����ǉ�		*/
/*  2.02	2006/12/16		YOON			ERROR File �֐��ǉ�		*/
/*  3.02	2007/04/12		INTEC			Buntekai -803�̌㑱�ǉ�	*/
/*  3.03	2007/04/26		Nagata			��ܗp�D�惋�[�� �ǉ�	*/
/*  3.04	2007/07/20      Nagata			�������̖�ԃA�b�Z�C�Ή�*/
/*  4.01                    k.moriya        �V�t���Ή�              */
/*  4.02    2009/03/24      h.sekiya        �I�[�_�[�̌����H���敪��*/
/*                                          ����Œ�Ƃ���          */
/*  4.03    2014/06/23      h.sekiya        �����{�t���O�s��Ή�	*/
/********************************************************************/

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include "AD105Buntekai.h"

/****************************************************************************/
/* �C���N���[�h�錾                                                         */
/****************************************************************************/


/****************************************************************************/
/* Define��`                                                               */
/****************************************************************************/

/****************************************************************************/
/* �O���[�o���錾                                                           */
/****************************************************************************/
extern struct stcLogMember      gstLogMem ;
extern iconv_t     G_ic;
int	g_iSyaknr;
Sysknrmst *g_strSysknr = NULL;
int g_iKnsg;
Knsgmst *g_strKnsg = NULL;
//int g_iAsyscdl;
//Asyscdlmst *g_strAsyscdl = NULL;
int g_iRngchk;
Rngchkmst *g_strRngchk = NULL;
int g_iSkchk;
Skchkmst *g_strSkchk = NULL;
int g_iKrkmk;
Krkmkmst *g_strKrkmk = NULL;
int g_iKmk;
Kmkmst *g_strKmk = NULL;
int	g_iJdkmk;
Jdkmkmst *g_strJdkmk;
int g_iCalck;
Calckmkmst *g_strCalck;
// ADD E.Osada 2006-08-30
int chkYusen(struct bunchuEnv *pst_Env, Bunchu *chk0, Bunchu *chk1, char *sKnsgrp );
// ADD Nagata 2007-04-26
void trim(char *dst, char *src);
//
/****************************************************************************/
/*  �� �� ���@�FABunGetKnsgrp()												*/
/*  �@�\�T�v�@�F�����O���[�v�擾����										*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBunchu	*strBunchu   �������ʏ��\����						*/
/*	 ��Q���� �FKanjya	*strKanjya	 ���ҏ��\����							*/
/*	 ��R���� �Fchar	*sKmkcd		 ���ڃR�[�h								*/
/*	 ��S���� �Fchar	*sKnsgrp	�����O���[�v							*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int ABunGetKnsgrp( Bunchu *strBunchu, Kanjya *strKanjya, char *sKmkcd, char *sKnsgrp )
{
	Kmkmst strKmkmst, *pKmk = NULL;
	Knsgmst	strKnsgmst, *pKnsg = NULL;
	int	num, i, j, ret;
	char	sBuf[128];
	int iSflg, iNgFlg;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "ABunGetKnsgrp", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"Start Function kmkcd %s", sKmkcd) ;

	//�������ʂ𕪒��@�t�B�[���h�ɐݒ肷�� 2006-05-28 E.Osada
	memset(strBunchu->bckid, ' ', 3);
	strBunchu->bckid[2] = strBunchu->bnckka;
	//
	memset( &strKmkmst, 0, sizeof(Kmkmst));
	memset(strKmkmst.knsgrp, ' ', sizeof(strKmkmst.knsgrp)-1);
	strcpy(strKmkmst.kaiymd, strBunchu->sriymd);
	strcpy(strKmkmst.kmkcd, sKmkcd);
	strcpy(strKmkmst.smpcd, strBunchu->smpcd);

	iSflg = iNgFlg = 0;
	//�ϊ��O�˗���No�ɖ߂�
	memset(sBuf, 0, sizeof(sBuf));
	sprintf(sBuf, "%-3.3s00%-6.6s", &strBunchu->irino[2], &strBunchu->irino[5]);
// 2008.04.24 �W������(426)�ǉ� UPD START
// 2011.09.29 �W������(790)�ǉ� UPD START
// 2013.08.31 �W������(590)�ǉ� UPD START
// 2015.10.13 �W������(380,381)�ǉ� UPD START
	if( !memcmp(sBuf, "012", 3) || !memcmp(sBuf, "013", 3) || !memcmp(sBuf, "014", 3) ||
		!memcmp(sBuf, "020", 3) || !memcmp(sBuf, "090", 3) || !memcmp(sBuf, "403", 3) ||
		!memcmp(sBuf, "404", 3) || !memcmp(sBuf, "405", 3) || !memcmp(sBuf, "412", 3) ||
		!memcmp(sBuf, "426", 3) || !memcmp(sBuf, "490", 3) || !memcmp(sBuf, "590", 3) ||
		!memcmp(sBuf, "790", 3) || !memcmp(sBuf, "380", 3) || !memcmp(sBuf, "381", 3) ||
		!memcmp(sBuf, "528", 3) || !memcmp(sBuf, "784", 3) || !memcmp(sBuf, "786", 3) || !memcmp(sBuf, "787", 3) ||
		!memcmp(sBuf, "788", 3) || !memcmp(sBuf, "789", 3) || !memcmp(sBuf, "793", 3) || !memcmp(sBuf, "795", 3) ||
		!memcmp(sBuf, "796", 3) || !memcmp(sBuf, "797", 3) || !memcmp(sBuf, "798", 3) ||
		!memcmp(sBuf, "231", 3) || !memcmp(sBuf, "232", 3) || !memcmp(sBuf, "233", 3) ||
		!memcmp(sBuf, "234", 3) || !memcmp(sBuf, "235", 3) || !memcmp(sBuf, "236", 3) ||
		!memcmp(sBuf, "237", 3) || !memcmp(sBuf, "238", 3) || !memcmp(sBuf, "239", 3) ||
		!memcmp(sBuf, "240", 3) || !memcmp(sBuf, "241", 3) || !memcmp(sBuf, "434", 3) ) {
// 2008.04.24 �W������(426)�ǉ� UPD END
// 2011.09.29 �W������(790)�ǉ� UPD END
// 2013.08.31 �W������(590)�ǉ� UPD END
// 2015.10.13 �W������(380,381)�ǉ� UPD END
		iSflg = 1;
	}
	// 2006-05-10 �d�l�ǉ���
	if( (strBunchu->bnckka == '8') || (strBunchu->bnckka == '9') || (strBunchu->bnckka == 'A') ||
		// Update 2007.04.05 (strBunchu->bnckka == 'B') || (strBunchu->bnckka == 'C') ) {
		(strBunchu->bnckka == 'B') || (strBunchu->bnckka == 'C') ||
		(strBunchu->bnckka == 'D') || (strBunchu->bnckka == 'E') ||
		(strBunchu->bnckka == 'F') || (strBunchu->bnckka == 'G') ||
		(strBunchu->bnckka == 'H') ) {
		// 2007-07-20 �������̂��ԃA�b�Z�C������Ή�
		// �E���d�l
		//  �񕪒�(8,9,A,B,C)�̕������ʂɊY�����A���A�W�������łȂ����R�[�h�ɂ��āA�ȉ��̏������s���B
		//    �����P�D�T���v�����O�R�[�h�iWS�R�[�h�j = 54�i��ʌ����j�@�ɊY��
		//    �����Q�D���ǈ����i�������b�NID�̓��Q�� = "XX"�j�ɊY��
		//    �����R�D�������̈ȊO�i�������̂ł͂Ȃ� = �����t���O:553�o�C�g�ڂ��󔒁j
		//    �����S�D�������̈ȊO�i�������̂ł͂Ȃ� = �����t���O:551�o�C�g�ڂ��󔒁j
		//  ��L�̏����ɑS�ĊY���������R�[�h�́A�񕪒��ł͂Ȃ��A����NG�Ώۂ̌����O���[�v�Ƃ��Ĉ����B
		// �E�V�d�l
		//  �񕪒�(8,9,A,B,C)�̕������ʂɊY�����A���A�W�������łȂ����R�[�h�ɂ��āA�ȉ��̏������s���B
		//    �����D���ǈ����i�������b�NID�̓��Q�� = "XX"�j�ɊY��
		//  ��L�̏����ɑS�ĊY���������R�[�h�́A�񕪒��ł͂Ȃ��A����NG�Ώۂ̌����O���[�v�Ƃ��Ĉ����B
		// if( !memcmp(strBunchu->smpcd, "0054", 4) && !memcmp(strBunchu->id2, "XX", 2) &&
		//	(strBunchu->tknflg == ' ') && (strBunchu->jtflg == ' ') ) {
		//	iNgFlg = 1;
		// } 
// 2008-04-09 �V�t�����e�B�A�Ή� UPD START
//		if( !memcmp(strBunchu->id2, "XX", 2) ) {
		if( !memcmp(strBunchu->id2, "VV", 2) || !memcmp(strBunchu->id2, "XX", 2) ) {
// 2008-04-09 �V�t�����e�B�A�Ή� UPD END
			iNgFlg = 1;
		}
	}
	num = 0;
	//�������ڃ}�X�^����f�[�^�擾
	for( i=0; i < g_iKmk ;++i ) {
		if( !memcmp((g_strKmk+i)->kmkcd, sKmkcd, 7) && 
		    !memcmp((g_strKmk+i)->smpcd, strBunchu->smpcd, 4) && 
				(memcmp((g_strKmk+i)->kaiymd, strBunchu->sriymd, 10) <= 0) &&
				(memcmp((g_strKmk+i)->haiymd, strBunchu->sriymd, 10) >= 0) ) {
			strcpy(sKnsgrp, (g_strKmk+i)->knsgrp);
			++num;
// printf("a:sKmkcd[%s] strBunchu->smpcd[%s] strBunchu->sriymd[%s] sKnsgrp[%s] num[%d] \n",sKmkcd,strBunchu->smpcd,strBunchu->sriymd,sKnsgrp,num);
		}
	}
	if( num == 0 )	
		return( 0 );
	if( num == 1 ) {
		// 2007-04-12 INTEC ADD
		// �Y�����錟��G���P�ŁAbgroup=3�̏ꍇ
		//�����O���[�v�}�X�^�擾
		for( j=0; j < g_iKnsg ;++j ) {
			if( memcmp((g_strKnsg+j)->knsgrp, sKnsgrp, 16) == 0 ){
				if( (g_strKnsg+j)->bgroup == '3') {
					return(3);
				}
				break;
			}
		}
		// 2007-04-12 INTEC END
 
		return(1);
	}
	//�����O���[�v���������݂����ꍇ
	// ADD E.Osada 2006-09-12 
	// �������� 0,1,4,5,8,9,A,B,C �ȊO�̏ꍇ�͕���NG�Ƃ��ď�������
	if( (strBunchu->bnckka != '0') && (strBunchu->bnckka != '1') && (strBunchu->bnckka != '4') &&
		(strBunchu->bnckka != '5') &&
		(strBunchu->bnckka != '8') && (strBunchu->bnckka != '9') && (strBunchu->bnckka != 'A') &&
		// Update 2007.04.05 (strBunchu->bnckka != 'B') && (strBunchu->bnckka != 'C') ) {
		(strBunchu->bnckka != 'B') && (strBunchu->bnckka != 'C') &&
		(strBunchu->bnckka != 'D') && (strBunchu->bnckka != 'E') &&
		(strBunchu->bnckka != 'F') && (strBunchu->bnckka != 'G') &&
		(strBunchu->bnckka != 'H') ) {
			strBunchu->bnckka = '5';
	}
	// 
	for( i=0; i < g_iKmk ;++i ) {
		if( !(!memcmp((g_strKmk+i)->kmkcd, sKmkcd, 7) &&
            !memcmp((g_strKmk+i)->smpcd, strBunchu->smpcd, 4) &&
                (memcmp((g_strKmk+i)->kaiymd, strBunchu->sriymd, 10) <= 0) &&
                (memcmp((g_strKmk+i)->haiymd, strBunchu->sriymd, 10) >= 0)) ) {
			continue;
		}
// printf("b:sKmkcd[%s] strBunchu->smpcd[%s] strBunchu->sriymd[%s] sKnsgrp[%s] num[%d] \n",sKmkcd,strBunchu->smpcd,strBunchu->sriymd,sKnsgrp,num);
	//	if( !(!memcmp((g_strKmk+i)->kmkcd, sKmkcd, 7) && 
	//			(memcmp((g_strKmk+i)->kaiymd, strBunchu->sriymd, 10) <= 0)) ) {
	//		continue;
	//	}
		memset(&strKnsgmst, 0, sizeof(Knsgmst));
		strcpy(strKnsgmst.knsgrp, (g_strKmk+i)->knsgrp);
		strcpy(strKnsgmst.kaiymd, strBunchu->sriymd);
		ret = 0;
		//�����O���[�v�}�X�^�擾
		for( j=0; j < g_iKnsg ;++j ) {
			if( !(!memcmp((g_strKnsg+j)->knsgrp, strKnsgmst.knsgrp, 16) && 
				(memcmp((g_strKnsg+j)->kaiymd, strKnsgmst.kaiymd, 10) <= 0)) ) {
				continue;
			}
			ret = 0;
			//YOON 2007-02-01
			if( (g_strKnsg+j)->bgroup == '3') {
				ret = 3;	//bgrou��3�̏ꍇ�̏���
				strcpy(sKnsgrp, (g_strKnsg+j)->knsgrp);
				break;
			}
 
			switch(strBunchu->bnckka) {
			case '0':
			case '4':
/*
				if( (!memcmp(strKanjya->cdkbn1,"17",2)&&!memcmp(strBunchu->smpcd,"0054",4))|| 
					(iSflg && !memcmp(strBunchu->smpcd, "0054", 4)) ) [
					if( (((g_strKnsg+j)->bgroup == '1') && ((g_strKnsg+j)->knssbt == 'S')) ||
						(((g_strKnsg+j)->bgroup == '1') &&
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T'))) ) [
*/
				if( iSflg && !memcmp(strBunchu->smpcd, "0054", 4) ) {
					if( ((g_strKnsg+j)->bgroup == '1') && ((g_strKnsg+j)->knssbt == 'S') ) {
						ret = 1;
					}
				} else {
					if( ((g_strKnsg+j)->bgroup == '1') && 
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T')) ) {
						ret = 1;
					}
				}
				break;
			case '1':
			case '5':
/*
				if( !memcmp(strKanjya->cdkbn1, "17", 2)  || iSflg ) [
					if( (((g_strKnsg+j)->bgroup == '1') && ((g_strKnsg+j)->knssbt == 'S')) ||
						(((g_strKnsg+j)->bgroup == '1') &&
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T'))) ) [
				if( (!memcmp(strKanjya->cdkbn1,"17",2) &&!memcmp(strBunchu->smpcd, "0054", 4)) || 
*/
				if( iSflg && !memcmp(strBunchu->smpcd, "0054", 4) ) {
					if( ((g_strKnsg+j)->bgroup == '1') && ((g_strKnsg+j)->knssbt == 'S') ) {
						ret = 1;
					}
				} else {
					if( ((g_strKnsg+j)->bgroup == '1') && 
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T')) ) {
						ret = 1;
					}
				}
				break;
			case '8':
			case '9':
			case 'A':
			case 'B':
			case 'C':
			// Add 2007.04.05
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
/*
				if( !memcmp(strKanjya->cdkbn1, "17", 2) || iSflg ) [
					if( (((g_strKnsg+j)->bgroup == '0') && ((g_strKnsg+j)->knssbt == 'S')) ||
						(((g_strKnsg+j)->bgroup == '0') &&
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T'))) ) [
				if( (!memcmp(strKanjya->cdkbn1, "17", 2)&&!memcmp(strBunchu->smpcd, "0054", 4)) || 
*/
				if( iSflg && !memcmp(strBunchu->smpcd, "0054", 4) ) {
					//if( ((g_strKnsg+j)->bgroup == '1') && ((g_strKnsg+j)->knssbt == 'S') ) [
					if( ((g_strKnsg+j)->bgroup == '0') && 
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T')) ) {
						ret = 1;
					}
				} else {
					if( (iNgFlg == 1) && ((g_strKnsg+j)->bgroup == '1') && 
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T')) ) {
						ret = 1;
						//�������ʂ𕪒�NG�ɃZ�b�g����
						strBunchu->bnckka = '5';
						//
					} else if( (iNgFlg == 0) && ((g_strKnsg+j)->bgroup == '0') && 
						!(((g_strKnsg+j)->knssbt == 'S') || ((g_strKnsg+j)->knssbt == 'T')) ) {
						ret = 1;
					}
				}
				break;
			default:
				ret = -1;
				break;
			}
			if( ret == 1 ){
				strcpy(sKnsgrp, (g_strKnsg+j)->knsgrp);
				break;
			}
		}

		//YOON 2007-02-01
		if( ret == 1 || ret ==3) {
			break;
		}
	}
/*
	if( ret == 0 ) {
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"KNSGMST NOT FOUND iraiNo: %s kmk_cd: %s smpcd: %s", strBunchu->irino, strKmkmst.kmkcd, strBunchu->smpcd) ;
		strcpy(sKnsgrp, pKmk->knsgrp);
		ret = 2;
	}
*/

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "ABunGetKnsgrp", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"End Function %d", ret) ;

	return(ret);
}
/****************************************************************************/
/*  �� �� ���@�FAbunInsZokusei()											*/
/*  �@�\�T�v�@�F���̑����e�[�u���ǉ�										*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBunchu	*strBunchu   �������ʏ��\����						*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
//3.02 UPD int AbunInsZokusei( struct bunchuEnv *pst_Env, Bunchu *strBunchu, Kanjya *strKanjya )
int AbunInsZokusei( struct bunchuEnv *pst_Env, Bunchu *strBunchu, Kanjya *strKanjya, int iDupFLg )
{
	Kenzok	strKenzokuTB;
	long	ret;
	char	buf[1024];
	int		i, j, iHit;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbunInsZokusei", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"Start Function") ;

	memset(&strKenzokuTB, 0, sizeof(Kenzok));

	ZbmlStrCpy(strKenzokuTB.utkymd, strBunchu->utkymd, sizeof(strKenzokuTB.utkymd)-1);
	ZbmlStrCpy(strKenzokuTB.irino, strBunchu->irino, sizeof(strKenzokuTB.irino)-1);
	strKenzokuTB.iriketflg = ' ';
	strKenzokuTB.zssdino = strBunchu->zssdino;
	ZbmlStrCpy(strKenzokuTB.sriymd, strBunchu->sriymd, sizeof(strKenzokuTB.sriymd)-1);
	ZbmlStrCpy(strKenzokuTB.kntno, strBunchu->kntno, sizeof(strKenzokuTB.kntno)-1);
	strKenzokuTB.kntketflg = ' ';
	memset(strKenzokuTB.knsgslbcd, ' ', sizeof(strKenzokuTB.knsgslbcd)-1);
	strKenzokuTB.kntzssdino = 0;
	//memset(strKenzokuTB.knttcyymd, ' ', sizeof(strKenzokuTB.knttcyymd)-1);
	memset(strKenzokuTB.fszrgrp, ' ', sizeof(strKenzokuTB.fszrgrp)-1);
	memset(strKenzokuTB.irikntryo, ' ', sizeof(strKenzokuTB.irikntryo)-1);
	strKenzokuTB.irikntryotni = ' ';
	memset(strKenzokuTB.gnkntryo, ' ', sizeof(strKenzokuTB.gnkntryo)-1);
	strKenzokuTB.gnkntryotni = ' ';
	ZbmlStrCpy(strKenzokuTB.chkmj, strBunchu->chkmj, sizeof(strKenzokuTB.chkmj)-1);
	memset(strKenzokuTB.rucd, ' ', sizeof(strKenzokuTB.rucd)-1);
	memset(strKenzokuTB.ykcd, ' ', sizeof(strKenzokuTB.ykcd)-1);
	strKenzokuTB.htkfkiri = ' ';
	strKenzokuTB.ysnflg = ' ';
	strKenzokuTB.kntfrflg = ' ';
	memset(strKenzokuTB.ykzrcd, ' ', sizeof(strKenzokuTB.ykzrcd)-1);
	memset(strKenzokuTB.hzzrcd, ' ', sizeof(strKenzokuTB.hzzrcd)-1);
	strKenzokuTB.kntjtflg = ' ';
	strKenzokuTB.knttktkbn = ' ';
	strKenzokuTB.hbncflg = ' ';
	strKenzokuTB.kntzsssflg = ' ';
	ZbmlStrCpy(strKenzokuTB.stlkntzsssip, pst_Env->cUpdateId, sizeof(strKenzokuTB.stlkntzsssip)-1);
	ZbmlStrCpy(strKenzokuTB.stlkntzssssyaid, pst_Env->cUpdateName, sizeof(strKenzokuTB.stlkntzssssyaid)-1);
	strKenzokuTB.sklblflg = ' ';
	// ���ҏ��̔��l2����ޗ��R�[�h���̎���ҏW
	memset(buf, 0, sizeof(buf));
	iHit = j = 0;
	for( i=0; i < sizeof(strKanjya->bko1)-1 ; ++i ) {
		if( strKanjya->bko1[i] == 0 ) break;
		if( strKanjya->bko1[i] != '!' ) {
			buf[j++] = strKanjya->bko1[i];
		} else {
			switch(iHit) {
			case 0:		//�ޗ��R�[�h
				memcpy(strKenzokuTB.zrcd, buf, sizeof(strKenzokuTB.zrcd)-1);
				break;
			case 1:		//�̎�N����
				if( (buf[0] == 0) || (buf[0] == ' ') ) {
					strcpy(strKenzokuTB.ssymd, "1000-01-01");
				} else {
					sprintf(strKenzokuTB.ssymd, "%4.4s-%2.2s-%2.2s", buf, &buf[4], &buf[6] );
				}
				break;
			case 2:		//�̎掞���@�@���肦�Ȃ��H�I
				if( (buf[0] == 0) || (buf[0] == ' ') ) {
					strcpy(strKenzokuTB.sstme, "00:00:01");
				} else {
					sprintf(strKenzokuTB.sstme, "%2.2s:%2.2s:00", buf, &buf[2] );
				}
				break;
			}
			memset(buf, 0, sizeof(buf));
			iHit++;
			j = 0;
		}
	}
	if( iHit == 2 ) {
		//�̎掞��
		if( (buf[0] == 0) || (buf[0] == ' ') ) {
			strcpy(strKenzokuTB.sstme, "00:00:01");
		} else {
			sprintf(strKenzokuTB.sstme, "%2.2s:%2.2s:00", buf, &buf[2] );
		}
	}
	strKenzokuTB.tntni = strBunchu->tntni;
	ZbmlStrCpy(strKenzokuTB.tnryo, strBunchu->tnryo, sizeof(strKenzokuTB.tnryo)-1);
	ZbmlStrCpy(strKenzokuTB.tntme, strBunchu->tntme, sizeof(strKenzokuTB.tntme)-1);
	strKenzokuTB.tnryotni = strBunchu->tnryotni;
	memset(strKenzokuTB.ssbi, ' ', sizeof(strKenzokuTB.ssbi)-1);
	memset(strKenzokuTB.sshhu, ' ', sizeof(strKenzokuTB.sshhu)-1);
	memset(strKenzokuTB.hkflg, ' ', sizeof(strKenzokuTB.hkflg)-1);
	memset(strKenzokuTB.mkntno, ' ', sizeof(strKenzokuTB.mkntno)-1);
	memcpy(strKenzokuTB.id2, strBunchu->id2, sizeof(strKenzokuTB.id2)-1);
	strKenzokuTB.id2pos = strBunchu->id2pos;
	memcpy(strKenzokuTB.id3, strBunchu->id2, sizeof(strKenzokuTB.id2)-1);
	strKenzokuTB.id3pos = strBunchu->id2pos;
	memset(strKenzokuTB.sntrno, ' ', sizeof(strKenzokuTB.sntrno)-1);
	memset(strKenzokuTB.sntnno, ' ', sizeof(strKenzokuTB.sntnno)-1);
	strKenzokuTB.nstsgflg = ' ';
	strKenzokuTB.hknjk = ' ';

	AKenzokChk(&strKenzokuTB);
	
	if( (ret = AZokuInsert(&strKenzokuTB)) < 0 ) {
		if( ret == -803 ) {
			// 3.02 ADD STA
			if( iDupFLg == 1 ){
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsZokusei", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					"���O�Ή� UPDATE Kenzoku [%s %s]",
					strBunchu->sriymd, strBunchu->kntno );
				if( (ret = AZokuUpdate(&strKenzokuTB)) < 0 ) {
					// �G���[�ł����Ă�OK�Ƃ���RETURN����
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsZokusei", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
						"UPDATE Kenzoku[SQLCODE=%d]", ret ) ;
				}
			}
			// 3.02 ADD END
			ret = 0;
		} else {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsZokusei", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				"INSERT Kenzoku[SQLCODE=%d]", ret ) ;
		}
		return( ret );
	}

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbunInsZokusei", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"End Function") ;

	return( 0 );
}
/****************************************************************************/
/*  �� �� ���@�FAbunInsNinsiki()											*/
/*  �@�\�T�v�@�F���̔F���e�[�u���ǉ�										*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBunchu	*strBunchu   �������ʏ��\����						*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
//3.02 DEL int AbunInsNinsiki( struct bunchuEnv *pst_Env, Bunchu *strBunchu, int iFlg)
int AbunInsNinsiki( struct bunchuEnv *pst_Env, Bunchu *strBunchu, int iFlg, int iDupFLg )
{
	Ninsiki	strNinsikiTB;
	char	buf[1024];
	long	ret;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbunInsNinsiki", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"Start Function") ;

	memset(&strNinsikiTB, 0, sizeof(strNinsikiTB));

	strcpy(strNinsikiTB.utkymd, strBunchu->utkymd);
	strcpy(strNinsikiTB.irino, strBunchu->irino);
	strNinsikiTB.zssdino = strBunchu->zssdino;
	strcpy(strNinsikiTB.chkmj, strBunchu->chkmj);
	strcpy(strNinsikiTB.kntno, strBunchu->kntno);
	strcpy(strNinsikiTB.id2, strBunchu->id2);
	strNinsikiTB.id2pos = strBunchu->id2pos;
	strcpy(strNinsikiTB.id3, strBunchu->id2);
	strNinsikiTB.id3pos = strBunchu->id2pos;
	strcpy(strNinsikiTB.sriymd, strBunchu->sriymd);
	//ADD E.Osada 2006-09-13
	//�����������̏ꍇ�́A�����{�t���O�͗��ĂȂ�
	if( memcmp(strNinsikiTB.id2, "        ", 8) ) {
		//�����{�����Z�b�g 2006-05-28 E.Osada
		if( (strBunchu->bnckka == '1') || (iFlg == 2)) {
			strNinsikiTB.fuksuhn = 'W';
		} else {
			strNinsikiTB.fuksuhn = ' ';
		}
	} else {
		strNinsikiTB.fuksuhn = ' ';
	}
	//

	ANinsikiChk(&strNinsikiTB);
	
	if( (ret = ABunNnskIns(&strNinsikiTB)) < 0 ) {
		memset(buf, 0, sizeof(buf));
		if( ret == -803 ) {
			/* �d���G���[�����������ꍇ�́A�����{�t���O�̍X�V���s���B */
			if( strNinsikiTB.fuksuhn == 'W' ) {
				if( (ret = ABunNinUp(&strNinsikiTB)) < 0){
					// �G���[�ł����Ă�OK�Ƃ���RETURN����
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsNinsiki", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"UPDATE Ninsiki Fuku[SQLCODE=%d]", ret ) ;
				}
			}
			// 3.02 ADD STA
			if( iDupFLg == 1 ){
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsNinsiki", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					"���O�Ή� UPDATE Ninsiki [%s %s]",
					strBunchu->sriymd, strBunchu->kntno );
				if(( ret =  ANnskUpdate(&strNinsikiTB)) < 0 ) {
					// �G���[�ł����Ă�OK�Ƃ���RETURN����
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsNinsiki", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
						"UPDATE Ninsiki[SQLCODE=%d]", ret ) ;
				}
			}
			// 3.02 ADD END
			ret = 0;
		} else {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsNinsiki", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				"INSERT Ninsiki[SQLCODE=%d]", ret ) ;
		}
		return( ret );
	}

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbunInsNinsiki", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"End Function") ;

	return( 0 );
}
/****************************************************************************/
/*  �� �� ���@�FAbufInsOrder()												*/
/*  �@�\�T�v�@�F�����I�[�_�e�[�u���ǉ�										*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBunchu	*strBunchu   �������ʏ��\����						*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
//int AbufInsOrder( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, Kenorder **pOrder, int cnt)
int AbufInsOrder( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, Kenorder *pOrder)
{
	Trmst		strTr,	*pTr = NULL;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
	Rkmst		strRk,	*pRk = NULL;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	Kenorder	*pOd = NULL;
	Asyscdlmst		strAsy, *pAsy = NULL;
	BmlDate	today;
	char	buf[1024], buf1[1024], work[10], buf2[1024];
	int 	num, len, i, j, iHit;
	long	ret;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbufInsOrder", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"Start Function") ;
/*
	*pOrder = (Kenorder *)ZbmlRealloc(*pOrder, sizeof(Kenorder));
	pOd = *pOrder + cnt;
*/
	pOd = pOrder;
	memset(pOd, 0, sizeof(Kenorder));

/*
	//�����J�n��
	//�A�b�Z�C�X�P�W���[���擾
	memset(buf, 0, sizeof(buf));
	if( getKnsKaisibi(pIrai->knsgrp, pBun->sriymd, buf) == 0 ) {
		memset(&today, 0, sizeof(BmlDate));
		ZbmlDateGetToday(&today);
		ZbmlDateAsString(&today, buf);
		strcpy(pOd->knskisymd, buf);
		strcpy(pIrai->knskisyymd, buf);
	} else {
		strcpy(pIrai->knskisyymd, buf);
		strcpy(pOd->knskisymd, buf);
	}
*/
	//�����J�n���擾
    memset(buf, 0, sizeof(buf));
    //YOON 2007-02-01
	//getKnsKaisibi(pIrai->knsgrp, pBun->sriymd, buf);
	getShoribi(pst_Env->sLbcd,pst_Env->sSateid, buf);

	strcpy(pOd->knskisymd, buf);
	strcpy(pOd->sriymd, pBun->sriymd);			//������
	strcpy(pOd->kntno, pBun->kntno);			//����No
	strcpy(pOd->knsgrp, pIrai->knsgrp);			//�����O���[�v
	strcpy(pOd->kmkcd, pIrai->kmkcd);			//���ڃR�[�h
	pOd->knssu = 1;								//������
	pOd->knssueda = 0;							//�����񐔎}��
	pOd->irihsmkbn = pIrai->irihsmkbn;			//�������˗��敪
	pOd->irikbn = pIrai->irikbn;					//�˗��敪
	/* 4.02 �����W�J�Ŕ���������I�[�_�[�͏���Œ�Ƃ��� */
	/* pOd->ksktkbn = pIrai->ksktkbn;				//�����H���敪 */
	pOd->ksktkbn = 'A';
	strcpy(pOd->utkymd, pIrai->utkymd);			//BML��t�N����
	strcpy(pOd->irino, pIrai->irino);			//�˗���No
	pOd->zssdino = pIrai->zssdino;				//��������No
	strcpy(pOd->sstcd, pBun->sstcd);			//�{�݃R�[�h
	strcpy(pOd->trid, pBun->trid);				//�g���[ID
	pOd->trpos = pBun->trpos;					//�g���[�|�W�V����
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
	strcpy(pOd->asyrckid, pBun->asyrckid);		//�A�b�Z�C���b�NID
	pOd->asyrckpos = pBun->asyrckpos;			//�A�b�Z�C���b�N�|�W�V����
//	memset(pOd->asyrckid, ' ', sizeof(pOd->asyrckid)-1);
//	pOd->asyrckpos = 0;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	strcpy(pOd->oyakmkcd, pIrai->oyakmkcd);		//�e���ڃR�[�h
	strcpy(pOd->seccd, pIrai->seccd);			//�Z�N�V�����R�[�h
	pOd->bkfkkbn = pIrai->bkfkkbn;				//���敉�׋敪
	strcpy(pOd->smpcd, pIrai->smpcd);			//�T���v�����O�R�[�h
	//strcpy(pOd->zrcd, pIrai->stsrcd);			//�ޗ��R�[�h
	strcpy(pOd->ysnlbl, pIrai->ysnlbl);			//�D�惌�x��
	strcpy(pOd->kjno, pIrai->kjno);				//��lNo
	strcpy(pOd->tbkjno, pIrai->tbkjno);			//���ʊ�lNo
	pOd->tbkjflg = pIrai->tbkjflg;				//���ʊ�l�t���O
	strcpy(pOd->htkfkhms, pIrai->htkfkhms);		//���^���׎���
	//�W���t���O
	pOd->skflg = ' ';
	if( !memcmp(pKan->cdkbn1, "17", 2) ) {
		pOd->skflg = '1';
	} else {
		memset(buf, 0, sizeof(buf));
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%-3.3s00%-6.6s", &pOd->irino[2], &pOd->irino[5]);
// 2008.04.24 �W������(426)�ǉ� UPD START
// 2011.09.29 �W������(790)�ǉ� UPD START
// 2013.08.31 �W������(590)�ǉ� UPD START
// 2015.10.13 �W������(380,381)�ǉ� UPD START
		if( !memcmp(buf, "012", 3) || !memcmp(buf, "013", 3) || !memcmp(buf, "014", 3) ||
			!memcmp(buf, "020", 3) || !memcmp(buf, "090", 3) || !memcmp(buf, "403", 3) ||
			!memcmp(buf, "404", 3) || !memcmp(buf, "405", 3) || !memcmp(buf, "412", 3) ||
			!memcmp(buf, "426", 3) || !memcmp(buf, "490", 3) || !memcmp(buf, "590", 3) ||
			!memcmp(buf, "790", 3) || !memcmp(buf, "380", 3) || !memcmp(buf, "381", 3) ||
			!memcmp(buf, "528", 3) || !memcmp(buf, "784", 3) || !memcmp(buf, "786", 3) || !memcmp(buf, "787", 3) ||
			!memcmp(buf, "788", 3) || !memcmp(buf, "789", 3) || !memcmp(buf, "793", 3) || !memcmp(buf, "795", 3) ||
			!memcmp(buf, "796", 3) || !memcmp(buf, "797", 3) || !memcmp(buf, "798", 3) ||
			!memcmp(buf, "231", 3) || !memcmp(buf, "232", 3) || !memcmp(buf, "233", 3) ||
			!memcmp(buf, "234", 3) || !memcmp(buf, "235", 3) || !memcmp(buf, "236", 3) ||
			!memcmp(buf, "237", 3) || !memcmp(buf, "238", 3) || !memcmp(buf, "239", 3) ||
			!memcmp(buf, "240", 3) || !memcmp(buf, "241", 3) || !memcmp(buf, "434", 3) ) {
// 2008.04.24 �W������(426)�ǉ� UPD END
// 2011.09.29 �W������(790)�ǉ� UPD END
// 2013.08.31 �W������(590)�ǉ� UPD END
// 2015.10.13 �W������(380,381)�ǉ� UPD END
			pOd->skflg = '1';
		}
	}
	strcpy(pOd->tskflg, pIrai->tskflg);			//���̓t���O
	strcpy(pOd->tktflg, pIrai->tktflg);			//�����t���O
	strcpy(pOd->sc, pKan->sc);					//�g��
	strcpy(pOd->tj, pKan->tj);					//�̏d
	pOd->tjtni = pKan->tjtni;					//�̏d�敪
	pOd->sbtkbn = pKan->sbtkbn;					//���ʋ敪
	strcpy(pOd->birthday, pKan->birthday);		//���N����
	pOd->birthdaykbn = pKan->birthdaykbn;		//���N�����敪
	strcpy(pOd->age, pKan->age);				//�N��
	pOd->agekbn = pKan->agekbn;					//�N��敪
	strcpy(pOd->ytiksbr, pIrai->ytiksbr);		//�\���ߔ{��

	// ���ҏ��̔��l1����ޗ��R�[�h���̎���ҏW
	memset(buf, 0, sizeof(buf));
	iHit = j = 0;
	for( i=0; i < sizeof(pKan->bko1)-1 ; ++i ) {
		if( pKan->bko1[i] == 0 ) break;
		if( pKan->bko1[i] != '!' ) {
			buf[j++] = pKan->bko1[i];
		} else {
			switch(iHit) {
			case 0:		//�ޗ��R�[�h
				memcpy(pOd->zrcd, buf, sizeof(pOd->zrcd)-1);
				break;
			case 1:		//�̎�N����
				if( (buf[0] == 0) || (buf[0] == ' ') ) {
					strcpy(pOd->ssymd, "1000-01-01");
				} else {
					sprintf(pOd->ssymd, "%4.4s-%2.2s-%2.2s", buf, &buf[4], &buf[6] );
				}
				break;
			case 2:		//�̎掞���@�@���肦�Ȃ��H�I
				if( (buf[0] == 0) || (buf[0] == ' ') ) {
					strcpy(pOd->sstme, "00:00:01");
				} else {
					sprintf(pOd->sstme, "%2.2s:%2.2s:00", buf, &buf[2] );
				}
				break;
			}
			memset(buf, 0, sizeof(buf));
			iHit++;
			j = 0;
		}
	}
	if( iHit == 2 ) {
		//�̎掞��
		if( (buf[0] == 0) || (buf[0] == ' ') ) {
			strcpy(pOd->sstme, "00:00:01");
		} else {
			sprintf(pOd->sstme, "%2.2s:%2.2s:00", buf, &buf[2] );
		}
	}
	//strcpy(pOd->sstme, pKan->bko1);				//�̎掞��
	//strcpy(pOd->ssymd, pKan->bko2);				//�̎�N����
	strcpy(pOd->zrcd, pIrai->stsrcd);			//�ޗ�w�w�w�w܂͈˗����� 2006/04/11
	strcpy(pOd->tntme, pBun->tntme);			//�{�A����
	strcpy(pOd->tnryo, pBun->tnryo);			//�{�A��
	pOd->tntni = pBun->tntni;					//�{�A���ԋ敪
	pOd->tnryotni = pBun->tnryotni;				//�{�A�ʋ敪
	memset(pst_Env->sPutDir, 0, BUNCHU_DIR_SIZE);
	//����SEQ�v�Z
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//	memset(&strTr, 0, sizeof(Trmst));
//	memcpy(strTr.trhdid, pBun->trid, 4);
//	strcpy(strTr.kaiymd,  pBun->sriymd);
	memset(&strRk, 0, sizeof(Rkmst));
	memcpy(strRk.smpcd, pBun->smpcd, 4);
	strcpy(strRk.kaiymd,  pBun->sriymd);
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
//	UPD 2007.02.28 HAIYMD
//	if( ZdbTrmstSelectKey(&strTr, &pTr, &num) < 0 ) [
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//	if( A105trmstSelectKey(&strTr, &pTr, &num) < 0 ) {
	if( A105rkmstSelectKey(&strRk, &pRk, &num) < 0 ) {
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbufInsOrder", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"SELECT Trmst[SQLCODE=%d]", ret ) ;
		return( -1 );
	}
	if( num == 0) {
		pOd->knsseq = 1;
	} else {
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//		strcpy(pst_Env->sPutDir, pTr->filskdir);
//		ZbmlInfocpy(buf, pBun->trid, 11);
//		len = strlen(buf) - 4;
//		strcpy(buf1, &buf[len]);
//		len = atoi(buf1);
//		pOd->knsseq = len * pTr->trknhsu + pBun->trpos;
//		ZbmlFree(pTr);
//		pTr = NULL;
		strcpy(pst_Env->sPutDir, pRk->filskdir);
		pOd->knsseq = 0;
		ZbmlFree(pRk);
		pRk = NULL;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
	}

	//�d�l�ǉ��F����OK�ȊO���I�[�_���쐬����B�����󋵃t���O��'N'���Z�b�g
	if( (pBun->bnckka == '0') || (pBun->bnckka == '4') ) {
		pOd->knsjkflg = ' ';
	} else {
		pOd->knsjkflg = 'N';
	}
	//
	AKenorderChk(pOd);
	
	if( (ret = ABunOrdInsert(pOd)) < 0 ) {
		if( ret != -803 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbufInsOrder", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				"INSERT Kenorder irino(%s) knsgrp(%s) kmkcd(%s)[SQLCODE=%d]", 
				pOd->irino, pOd->knsgrp, pOd->kmkcd, ret ) ;
			return( ret );
		}
	}

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbufInsOrder", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"End Function") ;

	return( 0 );

}
/****************************************************************************/
/*  �� �� ���@�FAbunIndChk()												*/
/*  �@�\�T�v�@�F�����`�F�b�N�e�[�u���ǉ�									*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBunchu	*strBunchu   �I�[�_���\����						*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
//int AbunInsChk( struct bunchuEnv *pst_Env, Kenorder *pOrder, Kanjya *pKan, Realchk **pReal, int cnt)
int AbunInsChk( struct bunchuEnv *pst_Env, Kenorder *pOrder, Kanjya *pKan)
{
	Rngchkmst	strRng,	*pRng = NULL, strRngW;
	Skchkmst	strSkn, *pSkn = NULL;
	Krkmkmst	strKnr, *pKnr = NULL;
	Kskbrmst	strKsk, *pKsk = NULL;
	Kmkmst		strKmk, *pKmk = NULL;
	Calckmkmst	strCal, *pCal = NULL;
	Kenorder	*pOd = NULL;
	//Realchk		*pRe = NULL;
	Realchk		pRe;
	//Asymst		strAsy, *pAsy = NULL;
	BmlDate	today;
	char	buf[1024], buf1[1024];
	char	buf2[128];
	int		num, i, j, iHit;
	long	ret;
	char	sDate[20];
	char	sDate1[20];
	char	sDate2[20];
	int	iKeta;
	char	sKjNo[10];

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbunInsChk", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"Start Function") ;

	//�����擾
	memset(sKjNo, 0, sizeof(sKjNo));
	GetKjnNo(pOrder->kmkcd, pOrder->zrcd, pKan->age, pKan->agekbn, pOrder->sriymd,
				sKjNo, &iKeta);
		
/*
	*pReal = (Realchk *)ZbmlRealloc(*pReal, sizeof(Realchk));
	pOd = pOrder + cnt;
	pRe = *pReal + cnt;
*/
	pOd = pOrder;
	memset(&pRe, 0, sizeof(Realchk));

	strcpy(pRe.knskisymd, pOd->knskisymd);
	strcpy(pRe.sriymd, pOd->sriymd);
	strcpy(pRe.kntno, pOd->kntno);
	strcpy(pRe.knsgrp, pOd->knsgrp);
	strcpy(pRe.kmkcd,	pOd->kmkcd);
	pRe.knssu = pOd->knssu;
	pRe.knssueda = pOd->knssueda;
	strcpy(pRe.utkymd, pOd->utkymd);
	strcpy(pRe.irino, pOd->irino);
	pRe.zssdino = pOd->zssdino;
	strcpy(pRe.trid, pOd->trid);
	pRe.trpos = pOd->trpos;
	strcpy(pRe.asyrckid, pOd->asyrckid);
	pRe.asyrckpos = pOd->asyrckpos;

	//�����W�`�F�b�N�}�X�^
	memset(&strRng, 0, sizeof(strRng));
	strcpy(strRng.kaiymd, pOd->knskisymd);		//�J�n���ɓ����B
	strcpy(strRng.knsgrp, pOd->knsgrp);			//�����O���[�v
	strRng.sbt = '0';
	strRng.ssa = '1';
	//strRng.sbt = pKan->sbtkbn;					//����
	strRng.sbt = ' ';
	strRng.hnikbn = '1';						//�͈͋敪 �Č��l
	if( !memcmp(pOd->zrcd, "001 ", 4) || !memcmp(pOd->zrcd, "002 ", 4) ) {
		strcpy(strRng.zaicd, pOd->zrcd);				//�ޗ��R�[�h
	} else {
		strcpy(strRng.zaicd, "000 ");				//�ޗ��R�[�h
	}
	strcpy(strRng.sstcd, pOd->sstcd);	//�{�݃R�[�h
	strcpy(strRng.kmkcd, pOd->kmkcd);			//���ڃR�[�h
	//1.�w��{�݃R�[�h�œǍ���
	if( (ret = A105rngchkSelKey(&strRng, &pRng, &num)) < 0 ) {
	//if( (ret = ZdbRngchkmstSelectKey2(&strRng, &pRng, &num)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"SELECT Rngchkmst[SQLCODE=%d]", ret ) ;
		return( ret );
	}
	if( num == 0 ) {
		//2.�{�݃R�[�h "0000000" �œǍ���
		memset(strRng.sstcd, 0, sizeof(strRng.sstcd));
		memset(strRng.sstcd, '0', 7);
		if( (ret = A105rngchkSelKey(&strRng, &pRng, &num)) < 0 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				"SELECT Rngchkmst[SQLCODE=%d]", ret ) ;
			return( ret );
		}
		if( num == 0 ) {
			//3.�ޗ��R�[�h "000 " �œǍ���
			memset(strRng.zaicd, 0, sizeof(strRng.zaicd));
			strcpy(strRng.zaicd, "000 ");				//�ޗ��R�[�h
			if( (ret = A105rngchkSelKey(&strRng, &pRng, &num)) < 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					"SELECT Rngchkmst[SQLCODE=%d]", ret ) ;
				return( ret );
			}
		}
	}

	if( num != 0 ) {
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		for( i=0; i < num ;++i ) {
			memset(sDate, 0, sizeof(sDate));
			memset(sDate1, 0, sizeof(sDate1));
			memset(sDate2, 0, sizeof(sDate2));
			sprintf(sDate, "%4.4s%2.2s%2.2s", 
				(pRng+i)->kaiymd, &(pRng+i)->kaiymd[5], &(pRng+i)->kaiymd[8] );
			sprintf(sDate1, "%4.4s%2.2s%2.2s", 
				(pRng+i)->haiymd, &(pRng+i)->haiymd[5], &(pRng+i)->haiymd[8] );
			sprintf(sDate2, "%4.4s%2.2s%2.2s%2.2s%2.2s",
				(pRng+i)->ksndh, &(pRng+i)->ksndh[5], &(pRng+i)->ksndh[8],
				&(pRng+i)->ksndh[11],&(pRng+i)->ksndh[14] );
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%c%s%s%s%s%c%c%c%s%s%s%s%s%s", 
				(pRng+i)->hnikbn, (pRng+i)->knsgrp, (pRng+i)->kmkcd, 
				(pRng+i)->zaicd, (pRng+i)->sstcd, (pRng+i)->sbt, (pRng+i)->ssa, 
				(pRng+i)->zen_kyoyou, (pRng+i)->hrng, (pRng+i)->lrng,
				sDate, sDate1, (pRng+i)->hnktntid, sDate2);
			strcat(buf1, buf);
		}
		pRe.renjicflg = '1';
		strcpy(pRe.renjicpara, buf1);
		ZbmlFree(pRng);
		pRng = NULL;
//printf ("%s\n", pRe.renjicpara);
//} else {
//	pRe.renjicflg = '1';
//	strcpy(pRe.renjicpara, "1000,500");
	}

	//���փ`�F�b�N�}�X�^
	memset(&strSkn, 0, sizeof(Skchkmst));
	strcpy(strSkn.kaiymd, pOd->knskisymd);
	strcpy(strSkn.knsgrp, pOd->knsgrp);
	strcpy(strSkn.kmkcd, pOd->kmkcd);
	strcpy(strSkn.sstcd, pOd->sstcd);
	if( !memcmp(pOd->zrcd, "001 ", 4) || !memcmp(pOd->zrcd, "002 ", 4) ) {
		strcpy(strSkn.zaicd, pOd->zrcd);				//�ޗ��R�[�h
	} else {
		strcpy(strSkn.zaicd, "000 ");				//�ޗ��R�[�h
	}
	if( AD105sknchkSelKey(&strSkn, &pSkn, &num) < 0 ) {
	//if( ZdbSkchkmstSelectKey2(&strSkn, &pSkn, &num) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"SELECT Rngchkmst[SQLCODE=%d]", ret ) ;
		return( ret );
	}
	if( num != 0 ) {
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		memset(buf2, 0, sizeof(buf2));
		for( i=0; i < num ;++i ) {
/* 2006-06-08 E.Osada �d�l�ύX 
			memset(sDate, 0, sizeof(sDate));
			memset(sDate1, 0, sizeof(sDate1));
			memset(sDate2, 0, sizeof(sDate2));
			sprintf(sDate, "%4.4s%2.2s%2.2s", 
				(pSkn+i)->kaiymd, &(pSkn+i)->kaiymd[5], &(pSkn+i)->kaiymd[8] );
			sprintf(sDate1, "%4.4s%2.2s%2.2s", 
				(pSkn+i)->haiymd, &(pSkn+i)->haiymd[5], &(pSkn+i)->haiymd[8] );
			sprintf(sDate2, "%4.4s%2.2s%2.2s%2.2s%2.2s",
				(pSkn+i)->ksndh, &(pSkn+i)->ksndh[5], &(pSkn+i)->ksndh[8],
				&(pSkn+i)->ksndh[11],&(pSkn+i)->ksndh[14] );
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%s%s%s%s%d   !%s!%s%s%s%s",(pSkn+i)->knsgrp, (pSkn+i)->kmkcd, 
				(pSkn+i)->sstcd, (pSkn+i)->zaicd, (pSkn+i)->krknsgrp, (pSkn+i)->soukan,
				sDate, sDate1, (pSkn+i)->hnktntid, sDate2);
			strcat(buf1, buf);
*/
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%d   !%s!", (pSkn+i)->krknsgrp, (pSkn+i)->soukan);
			strcat(buf1, buf);
		}
		pRe.soukn1flg = '1';
		strcpy(pRe.soukn1para, buf1);
		ZbmlFree(pSkn);
		pSkn = NULL;
	}

	//�֘A�`�F�b�N
	memset(&strKnr, 0, sizeof(Krkmkmst));
	strcpy(strKnr.kaiymd, pOd->knskisymd);
	strcpy(strKnr.kmkcd, pOd->kmkcd);
	if( A105krkmkSelKey(&strKnr, &pKnr, &num) < 0 ) {
	//if( ZdbKrkmkmstSelectKey2(&strKnr, &pKnr, &num) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"SELECT Krkmkmst[SQLCODE=%d]", ret ) ;
		return( ret );
	}
	if( num != 0 ) {
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		for( i=0; i < num ;++i ) {
/* CHG 2006-08-06 E.Osada �֘A�捀�ڃR�[�h�݂̂��Z�b�g����
			memset(sDate, 0, sizeof(sDate));
			memset(sDate1, 0, sizeof(sDate1));
			memset(sDate2, 0, sizeof(sDate2));
			sprintf(sDate, "%4.4s%2.2s%2.2s", 
				(pKnr+i)->kaiymd, &(pKnr+i)->kaiymd[5], &(pKnr+i)->kaiymd[8] );
			sprintf(sDate1, "%4.4s%2.2s%2.2s", 
				(pKnr+i)->haiymd, &(pKnr+i)->haiymd[5], &(pKnr+i)->haiymd[8] );
			sprintf(sDate2, "%4.4s%2.2s%2.2s%2.2s%2.2s",
				(pKnr+i)->ksndh, &(pKnr+i)->ksndh[5], &(pKnr+i)->ksndh[8],
				&(pKnr+i)->ksndh[11],&(pKnr+i)->ksndh[14] );
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%s%s%s%s%s%s", (pKnr+i)->kmkcd, (pKnr+i)->krkmkcd, 
				sDate, sDate1, (pKnr+i)->hnktntid, sDate2);
			strcat(buf1, buf);
*/
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%s", (pKnr+i)->krkmkcd);
			strcat(buf1, buf);
		}
		pRe.kanrenflg = '1';
		strcpy(pRe.kanrenpara, buf1);
		ZbmlFree(pKnr);
		pKnr = NULL;
	}

	//��߃`�F�b�N �������Ńt���O���n�m
	pRe.kisyakflg = '1';

	//���їn���`�F�b�N
	memset(&strKmk, 0, sizeof(Kmkmst));
	strcpy(strKmk.kaiymd, pOd->knskisymd);
	strcpy(strKmk.knsgrp, pOd->knsgrp);
	strcpy(strKmk.kmkcd, pOd->kmkcd);
// UPD 2007.02.28 HAIYMD
//	if( ZdbKmkmstSelectKey(&strKmk, &pKmk, &num) < 0 ) [
	if( A105KmkmstSelKey(&strKmk, &pKmk, &num) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"SELECT Rngchkmst[SQLCODE=%d]", ret ) ;
		return( ret );
	}
	if( num != 0 ) {
		memset(buf, 0, sizeof(buf));
		memset(buf1, 0, sizeof(buf1));
		memset(buf2, 0, sizeof(buf2));
		for( i=0; i < num ;++i ) {
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%c%c",(pKmk+i)->nyuyouflg, (pKmk+i)->ksjhflg);
			strcat(buf1, buf);
		}
		pRe.kesseiflg = '1';
		if(pKmk->ksjhflg == '0') {
			pRe.kesseiflg = ' ';
		}
		strcpy(pRe.kesseipara, buf1);
		ZbmlFree(pKmk);
		pKmk = NULL;
	}

	//2006-06-08 E.Osada �d�l�ǉ��@�v�Z���ڃ}�X�^�ǉ�
	memset(&strCal, 0, sizeof(Calckmkmst));
	strcpy(strCal.knsgrp, pOd->knsgrp);			//�����O���[�v�R�[�h
	//strcpy(strCal.ksnsk, pOd->kmkcd);			//�����ڃR�[�h
	strcpy(strCal.kaiymd, pOd->knskisymd);		//�����J�n��
	if( !memcmp(pOd->zrcd, "001 ", 4) || !memcmp(pOd->zrcd, "002 ", 4) ) {
		strcpy(strCal.zaicd, pOd->zrcd);				//�ޗ��R�[�h
	} else {
		strcpy(strCal.zaicd, "000 ");				//�ޗ��R�[�h(���̑�)
	}
	strcpy(strCal.sstcd, pOd->sstcd);	//�{�݃R�[�h
	sprintf(strCal.ksnsk, "%%%s%%",  pOd->kmkcd);
	num = 0;
	//�擾�֐����Ăяo���B
	//YOON 2007-03-01
	if( A105CalckmkmstSelectKey2(&strCal, &pCal, &num) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"SELECT Calckmkmst[SQLCODE=%d]", ret ) ;
		return( ret );
	}

	iHit = 0;
	memset(buf, 0, sizeof(buf));
	memset(buf1, 0, sizeof(buf1));
	for( i=0; i < num ;++i ) 
	{
		/* ���ꍀ�ړ��ŕ����̃}�X�^���q�b�g�����ꍇ�A
			��Ƀq�b�g�������̂�D�� ( ���{�݃R�[�h �� 0000000 ) */
		if( !memcmp((pCal+i)->sstcd, strCal.sstcd, 7) ) {
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%s!%s!", (pCal+i)->kmkcd, (pCal+i)->ksnsk);
			iHit = 1;

		} else if( !memcmp((pCal+i)->sstcd, "0000000", 7) ) {
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%s!%s!", (pCal+i)->kmkcd, (pCal+i)->ksnsk);
			iHit = 1;

		}
		j = i +1;
		/* ���̃��R�[�h�̍��ڃR�[�h�`�F�b�N */
		if( j == num ){
			/* �ŏI���R�[�h�������ꍇ */
			strcat(buf1,buf);
			memset(buf, 0, sizeof(buf));

		} else if( memcmp((pCal+j)->kmkcd, (pCal+i)->kmkcd, 7) ) {
			/* ���ڃR�[�h���ς��ꍇ */
			strcat(buf1,buf);
			memset(buf, 0, sizeof(buf));

		}

	}
	if( iHit ) {
		pRe.keisanflg = '1';
		strcpy(pRe.keisanpara, buf1);
	}
	if( pCal != NULL ) {
		ZbmlFree(pCal);
		pCal = NULL;
	}

	//�����ݒ�
	sprintf(pRe.yobipara05, "%d", iKeta);

	ARealchkChk(&pRe);
	//�����`�F�b�N�e�[�u���쐬
	if( (ret = ABunRealInsert(&pRe)) < 0 ) {
		if( ret != -803 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "AbunInsChk", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				"INSERT Realchk[SQLCODE=%d]", ret ) ;
			return( ret );
		}
	}

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AbunInsChk", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		"End Function") ;

	return( 0 );
}
/****************************************************************************/
/*  �� �� ���@�Fnowdateget()												*/
/*  �@�\�T�v�@�F�V�X�e�����t�E�����̃Q�b�g									*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBunchu	*strBunchu   �I�[�_���\����						*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
void
nowdateget( char *sysdate, char *systime )
{
        struct tm       *newtime ;
        long    ltime ;

        time( &ltime) ;
        newtime = localtime( &ltime ) ;
        sprintf( sysdate, "%04d%02d%02d", newtime->tm_year+1900,
                                newtime->tm_mon+1, newtime->tm_mday ) ;
        sprintf( systime, "%02d%02d%02d", newtime->tm_hour,
                                newtime->tm_min, newtime->tm_sec ) ;

        return ;
}

void
nowdateget1( char *sysdttm )
{
        struct tm       *newtime ;
        long    ltime ;

        time( &ltime) ;
        newtime = localtime( &ltime ) ;
        sprintf( sysdttm, "%04d-%02d-%02d %02d:%02d:%02d", newtime->tm_year+1900,
                                newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour,
                                newtime->tm_min, newtime->tm_sec ) ;

        return ;
}
/****************************************************************************/
/*  �� �� ���@�FAerrFilePut()												*/
/*  �@�\�T�v�@�F�X�L�b�v��������t�@�C���Ɋi�[����						*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �Fstruct bunchuEnv *pEnv		���ϐ��\����					*/
/*�@ ��Q���� �Fchar *sData					�������f�[�^					*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int AerrFilePut( struct bunchuEnv *pEnv, char *sData )
{
	FILE *fp;
	char	sFileName[BUNCHU_FILE_SIZE];
	char	sSysdate[128], sSystime[128];;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"Start Function");

	memset(sFileName, 0, BUNCHU_FILE_SIZE);
	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));

	nowdateget(sSysdate, sSystime);
	//sprintf(sFileName, "%s/%s%s%s", pEnv->cDirBunchu, RETRY_NAME, sSysdate, BUNCHU_RECV_SFX);
	sprintf(sFileName, "%s/%s%s%s", pEnv->cDirBunchuNG, "R_BUN", sSysdate, BUNCHU_RECV_SFX);
	if( (fp = fopen(sFileName, "a")) == NULL ){
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d)", errno);
		return( -1 );
	}
	if( fputs( sData, fp) == EOF ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fputs ERROR(%d)", errno);
		return( -1 );
	}

	fclose(fp);

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"End Function");

	return(0);
}

/****************************************************************************/
/*  �� �� ���@�FAerrFilePut1()												*/
/*  �@�\�T�v�@�F�X�L�b�v��������t�@�C���Ɋi�[����(PART2)					*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �Fstruct bunchuEnv *pEnv		���ϐ��\����					*/
/*�@ ��Q���� �Fchar *sData					�������f�[�^					*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int AerrFilePut1( struct bunchuEnv *pEnv, char *sData )
{
	FILE *fp;
	char	sFileName[BUNCHU_FILE_SIZE];
	char	sSysdate[128], sSystime[128];;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut1", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"Start Function");

	memset(sFileName, 0, BUNCHU_FILE_SIZE);
	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));

	nowdateget(sSysdate, sSystime);
	sprintf(sFileName, "%s/%s%s%s", pEnv->cDirBunchuNG, RETRY_NAME, sSysdate, BUNCHU_RECV_SFX);
	if( (fp = fopen(sFileName, "a")) == NULL ){
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut1", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d) %s", errno, sFileName);
		return( -1 );
	}
	if( fputs( sData, fp) == EOF ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut1", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fputs ERROR(%d)", errno);
		return( -1 );
	}

	fclose(fp);

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut1", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"End Function");

	return(0);
}

/****************************************************************************/
/*  �� �� ���@�FAerrFilePut2()												*/
/*  �@�\�T�v�@�F�X�L�b�v��������t�@�C���Ɋi�[����(PART3)					*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �Fstruct bunchuEnv *pEnv		���ϐ��\����					*/
/*�@ ��Q���� �Fchar *sData					�������f�[�^					*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int AerrFilePut2( struct bunchuEnv *pEnv, char *sData )
{
	FILE *fp;
	char	sFileName[BUNCHU_FILE_SIZE];
	char	sSysdate[128], sSystime[128];;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut2", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"Start Function");

	memset(sFileName, 0, BUNCHU_FILE_SIZE);
	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));

	nowdateget(sSysdate, sSystime);
	sprintf(sFileName, "%s/%s%s%s", pEnv->cDirBunchuNG, SKIP_NAME, sSysdate, BUNCHU_RECV_SFX);
	if( (fp = fopen(sFileName, "a")) == NULL ){
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut1", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d) %s", errno, sFileName);
		return( -1 );
	}
	if( fputs( sData, fp) == EOF ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut1", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fputs ERROR(%d)", errno);
		return( -1 );
	}

	fclose(fp);

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut2", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"End Function");

	return(0);
}
/****************************************************************************/
/*  �� �� ���@�FAerrFilePut3()												*/
/*  �@�\�T�v�@�F�X�L�b�v��������t�@�C���Ɋi�[����(PART4)					*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �Fstruct bunchuEnv *pEnv		���ϐ��\����					*/
/*�@ ��Q���� �Fchar *sData					�������f�[�^					*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int AerrFilePut3( struct bunchuEnv *pEnv, char *sData )
{
	FILE *fp;
	char	sFileName[BUNCHU_FILE_SIZE];
	char	sSysdate[128], sSystime[128];;

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut3", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"Start Function");

	memset(sFileName, 0, BUNCHU_FILE_SIZE);
	memset(sSysdate, 0, sizeof(sSysdate));
	memset(sSystime, 0, sizeof(sSystime));

	nowdateget(sSysdate, sSystime);
	sprintf(sFileName, "%s/%s%s%s", pEnv->cDirBunchuNG, ERR_NAME, sSysdate, BUNCHU_RECV_SFX);
	if( (fp = fopen(sFileName, "a")) == NULL ){
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut3", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d) %s", errno, sFileName);
		return( -1 );
	}
	if( fputs( sData, fp) == EOF ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut3", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fputs ERROR(%d)", errno);
		return( -1 );
	}

	fclose(fp);

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut3", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"End Function");

	return(0);
}
/****************************************************************************/
/*  �� �� ���@�FAgetSortInfo()												*/
/*  �@�\�T�v�@�F�\�[�g�����t�@�C������\�[�g�����擾����					*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �FBUNSORT **strBun	�\�[�g�\����							*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int AgetSortInfo(BUNSORT **strBun )
{
	FILE *fp;
	char	buf[1024], buf1[10];
	BUNSORT *pBun = NULL;
	int		i, j, k, cnt, iHit, iSu;

	if( (fp = fopen(MYAPP_SORTINIFILE, "r")) == NULL ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "AgetSortInfo", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"fopen ERROR(%d)", errno);
		return( -1 );
	}

	memset(buf, 0, sizeof(buf));
	iSu = 0;
	for( i=0; fgets(buf, sizeof(buf), fp ) != NULL ;++i ) {
		// �擪��#�̓X�L�b�v����B
		if( (buf[0] == '#') || (buf[0] == '\n') ) {
			memset(buf, 0, sizeof(buf));
			continue;
		}
		//pBun = (BUNSORT *)ZbmlRealloc((BUNSORT *)pBun, sizeof(BUNSORT) * (iSu + 1));
		pBun = (BUNSORT *)realloc((BUNSORT *)pBun, sizeof(BUNSORT) * (iSu + 1));
		memset(pBun+iSu, 0, sizeof(BUNSORT));
		memcpy((pBun+iSu)->sData, buf, 4);
		memcpy((pBun+iSu)->sKey, &buf[5], 3);
		++iSu;
	}

	fclose(fp);

	*strBun = pBun;

	return( iSu );
}

//2006-12-14 YOON
/****************************************************************************/
/*  �� �� ���@�FAerrFilePut4()                                              */
/*  �@�\�T�v�@�F�X�L�b�v��������t�@�C���Ɋi�[����(PART4)                 */
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �Fstruct bunchuEnv *pEnv      ���ϐ��\����                  */
/*�@ ��Q���� �Fchar *sData                 �������f�[�^                  */
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����                                              */
/* �@�@�@�@�@�@�@-1     : ���s                                              */
/****************************************************************************/
int AerrFilePut4( struct bunchuEnv *pEnv, char *sData ,char *sFilename)
{
    FILE *fp;
    char    sFileName[BUNCHU_FILE_SIZE];
    char    sSysdate[128], sSystime[128];;

    //�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut4", __LINE__,
        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "Start Function");

    memset(sFileName, 0, BUNCHU_FILE_SIZE);
    memset(sSysdate, 0, sizeof(sSysdate));
    memset(sSystime, 0, sizeof(sSystime));

    nowdateget(sSysdate, sSystime);
    sprintf(sFileName, "%s/%s%s", pEnv->cDirBunchuNG, RETURN_NAME, sFilename);
    if( (fp = fopen(sFileName, "a")) == NULL ){
        sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut4", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "fopen ERROR(%d) %s", errno, sFileName);
        return( -1 );
    }
    if( fputs( sData, fp) == EOF ) {
        sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut4", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "fputs ERROR(%d)", errno);
        return( -1 );
    }

    fclose(fp);

    //�g���[�X���O
    sFncPutLog ( TRCKIND_TRACE, __FILE__, "AerrFilePut4", __LINE__,
        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "End Function");

    return(0);
}


/****************************************************************************/
/*  �� �� ���@�FAbunGetSort()												*/
/*  �@�\�T�v�@�F����TBL�Ɋi�[����\�[�g�L�[���Z�o����						*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int AbunGetSort(struct bunchuEnv *pst_Env, char *sId, char flg )
{
	int	i, cnt, iKey, iHit;
	char sBuf[10];
	BUNSORT *p;
	char	flg_tbl[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

	memset(sBuf, 0, sizeof(sBuf));
	memcpy(sBuf, sId, 4);
	cnt = pst_Env->pSortNo;

// 2008-01-07 �V�t�����e�B�A�Ή� UPD START
//	iKey = 900;
	iKey = 999;
// 2008-01-07 �V�t�����e�B�A�Ή� UPD END
	for( i=0; i < cnt ;++i ) {
		p = pst_Env->pSort + i;
		//�擪2����������悤�ɂ��� 2006-06-21 E.OSADA
		//if( !memcmp(sBuf, p->sData, 4) ) {
		if( !memcmp(sBuf, p->sData, 2) ) {
			iKey = atoi(p->sKey);
// 2008-01-07 �V�t�����e�B�A�Ή� DEL START
//			if( iKey == 999 ) iKey = 900;
// 2008-01-07 �V�t�����e�B�A�Ή� DEL END
			break;
		}
	}
	// ADD E.Osada 2006-09-03 
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//	if( !memcmp(sBuf, "XX", 2) || !memcmp(sBuf, "YY", 2) ) {
	if( !memcmp(sBuf, "VV", 2) || !memcmp(sBuf, "XX", 2) || !memcmp(sBuf, "YY", 2) ) {
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
		return( iKey );
	}
	//
	iHit = 0;
	for( i=0; flg_tbl[i] != '\0' ;++i ) {
		if ( flg == flg_tbl[i] ) {
			iHit = 1;
			break;
		}
	}
	if( iHit == 1 ) {
		if( i == 36) i = 40;
		iKey = iKey + i;
	}

	return( iKey );
}
/****************************************************************************/
/*  �� �� ���@�FdBunEnd()													*/
/*  �@�\�T�v�@�F�����G���h���m�F����										*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int dBunEnd( struct bunchuEnv *pst_Env, char *sTrId )
{
	Sysknrmst strSyskan, *pSyskan;
	int		num, i, j, iHit;
	char	buf[128], cEnd, cHit;
	long	lRet;
	char	chk[BUNCHU_END_NUM];

	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunEnd", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"Start Function");

	num = 0;
	pSyskan = NULL;
	if( (lRet = ABunSyskanSelKey(&pSyskan, &num)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunEnd", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�V�X�e���Ǘ��}�X�^SELECT�G���[(%d)", lRet);
		return( -1 );
	}
	if( num == 0) return( 0 );

	cHit = sTrId[BUNCHU_END_NUM];

	memset(chk, 0, sizeof(chk));
	//����END�m�F(�A)
	if( (cHit == '0') || strlen(pSyskan->bchend0dh) ) {
		chk[0] = '1';
	}
	//����END�m�F(�����P)
	if( (cHit == '1') || strlen(pSyskan->bchend1dh) ) {
		chk[1] = '1';
	}
	//����END�m�F(�����Q)
	if( (cHit == '2') || strlen(pSyskan->bchend2dh) ) {
		chk[2] = '1';
	}
	//����END�m�F(�����R)
	if( (cHit == '3') || strlen(pSyskan->bchend3dh) ) {
		chk[3] = '1';
	}
	//����END�m�F(�����S)
	if( (cHit == '4') || strlen(pSyskan->bchend4dh) ) {
		chk[4] = '1';
	}
	cEnd = '0';
	if( !memcmp(chk, BUNCHU_END_OK, BUNCHU_END_NUM) ) {
		cEnd = '1';
	}

	//�V�X�e���Ǘ��}�X�^�X�V
	if( (lRet = ABunSyskanUpdate( pst_Env->sLbcd, pst_Env->sSateid, cHit, cEnd )) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "dBunEnd", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�V�X�e���Ǘ��}�X�^�X�V�G���[(%d)", lRet);
		return( -1 );
	}
	
	//�g���[�X���O
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "dBunEnd", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"End Function");

	return( 0 );
}
/****************************************************************************/
/*  �� �� ���@�FGetKjnNo()													*/
/*  �@�\�T�v�@�F��lNo���擾����											*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int
GetKjnNo(  char *sKmkcd, char *sZrcd, char *sAge, char cAgkbn, char *stDate, 
			char *kjnno, int *iKeta )
//GetKjnNo(  Kenorder *pOrder, char *stDate, char *kjnno )
{
	Kjnmst strKjn, *pKjn;
	int	i, iCnt, iAge;
	long	lRet;
	int 	iRet;

	memset(&strKjn, 0, sizeof(Kjnmst));
	pKjn = NULL;
	strcpy(strKjn.kmkcd, sKmkcd);
	strcpy(strKjn.zrcd, sZrcd);
	strcpy(strKjn.kaiymd, stDate);
	iCnt = iRet = 0;

	iAge = 0;
	//�N��v�Z
	if( sAge[0] == 0 || !memcmp(sAge, "   ", 3) ) {
		iAge = 0;
	} else {
		iAge = atoi(sAge);
	}
	switch(cAgkbn) {
	case 'Y':
		iAge = iAge * 365;
		break;
	case 'M':
		iAge = iAge * 30;
		break;
	case 'W':
		iAge = iAge * 7;
		break;
	case 'D':
		iAge = iAge * 1;
		break;
	case 'Z':
		iAge = 99999;
		break;
	default:
		iAge = 0;
		break;
	}
	//��l�}�X�^����
	if( (lRet = ABunKjnNoSel(&strKjn, &pKjn, &iCnt)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "GetKjnNo", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"��l�}�X�^select�G���[kmkcd(%s) zrcd(%s) sqlcode(%d)", strKjn.kmkcd, strKjn.zrcd, lRet);
		return( -1 );
	}

	iRet = 0;
	strcpy(kjnno, "0  ");
	for( i=0; i < iCnt ;++i ) {
		strcpy(kjnno, (pKjn+i)->kjno);
		if( (atoi((pKjn+i)->nichilw) <= iAge) && (iAge <= atoi((pKjn+i)->nichihi)) ) {
			strcpy(kjnno, (pKjn+i)->kjno);
			iRet = 1;
			break;
		}
	}
	if( iRet ) {
		*iKeta = (pKjn+i)->kjsstnksu;
	}
	if( pKjn != NULL )
		ZbmlFree(pKjn);
	return( iRet );
}

/****************************************************************************/
/*  �� �� ���@�FABunJido()													*/
/*  �@�\�T�v�@�F�����������ڍ쐬����										*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int ABunJido( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, 
	Kenorder *pOrder, int iLine, int Nflg)
{
	Jdkmkmst strJdk, *pJdk = NULL;
	Irai	strIrai, *pIraiUp = NULL, *pIraiSv;
	int		iCnt, i, iRet;
	long	lRet;
	char 	sKjnNo[10];
	char	iOya;
	int	iIriCnt;
	int		iKetasu;
	char	*pId2;				// 2008-03-24 �V�t�����e�B�A�Ή� �ǉ�
	int		iId2pos;			// 2008-03-24 �V�t�����e�B�A�Ή� �ǉ�
	long	ret;

	memset(&strJdk, 0, sizeof(Jdkmkmst));
	strcpy(strJdk.knsgrp, pIrai->knsgrp);
	strcpy(strJdk.kmkcd, pIrai->kmkcd);
	strcpy(strJdk.kaiymd, pBun->sriymd);
	//�����������ڃ}�X�^�`�F�b�N
	if( (lRet = A105JdkmkSelKey(&strJdk, &pJdk, &iCnt)) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�����������ڃ}�X�^select�G���[(%d)", lRet);
		return( -1 );
	}
	if( iCnt == 0 ) {
		if( pJdk != NULL )
			ZbmlFree(pJdk);
		return( 0 );
	}
	for( i=0; i < iCnt ;++i ) {
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunJido", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"������������ ��knsgrp(%s) ��kmkcd(%s) �Vknsgrp(%s) �Vkmkcd(%s)", 
					 pIrai->knsgrp, pIrai->kmkcd, (pJdk+i)->jknsgrp, (pJdk+i)->jkmkcd );
		memset(&strIrai, 0, sizeof(Irai));
		strcpy(strIrai.utkymd, pIrai->utkymd);
		strcpy(strIrai.irino, pIrai->irino);
		strIrai.iriketflg = pIrai->iriketflg;
		strIrai.zssdino = pIrai->zssdino;
		strcpy(strIrai.knsgrp, (pJdk+i)->jknsgrp);
		strcpy(strIrai.kmkcd, (pJdk+i)->jkmkcd);
		strcpy( pOrder->knsgrp, (pJdk+i)->jknsgrp);
		strcpy( pOrder->kmkcd, (pJdk+i)->jkmkcd);
		memset(sKjnNo, 0, sizeof(sKjnNo));
		//��lNo�擾
		iKetasu = 0;
		if( (iRet = GetKjnNo(pIrai->kmkcd, pIrai->stsrcd, pKan->age, pKan->agekbn, 
			pOrder->knskisymd, sKjnNo, &iKetasu) ) == 1 ) {
			strcpy(strIrai.kjno, sKjnNo);
		} else {
			strcpy(strIrai.kjno, pIrai->kjno);
		}
		//strIrai.irihsmkbn = '2';
		strIrai.irihsmkbn = pIrai->irihsmkbn;
		strIrai.irikbn = pIrai->irikbn;
		strIrai.ksktkbn = pIrai->ksktkbn;
		strcpy(strIrai.sriymd, pIrai->sriymd);
		strcpy(strIrai.kntno, pIrai->kntno);
		//strcpy(strIrai.kntno, pBun->kntno);
		strIrai.kntketflg = pIrai->kntketflg;
		strcpy(strIrai.chkmj, pIrai->chkmj);
		strcpy(strIrai.stsrcd, pIrai->stsrcd);
		strcpy(strIrai.kmkrs, pIrai->kmkrs);
		strcpy(strIrai.oyakmkcd, (pJdk+i)->jkmkcd);
		strcpy(pOrder->oyakmkcd, (pJdk+i)->jkmkcd);
		strcpy(strIrai.smpcd, pIrai->smpcd);
		strcpy(strIrai.setkmkcd, pIrai->setkmkcd);
		strIrai.srinycd = '2';
		strcpy(strIrai.seccd, pIrai->seccd);
		strIrai.skchkflg = pIrai->skchkflg;
		strIrai.bkfkkbn = pIrai->bkfkkbn;
		strcpy(strIrai.ysnlbl, pIrai->ysnlbl);
		strIrai.skflg = pIrai->skflg;
		strIrai.tkflg = pIrai->tkflg;
		strIrai.sjflg = pIrai->sjflg;
		strIrai.jktkflg = pIrai->jktkflg;
		strIrai.fkhkknohjkbn = pIrai->fkhkknohjkbn;
		strcpy(strIrai.tbkjno, pIrai->tbkjno);
		strIrai.tbkjflg = pIrai->tbkjflg;
		strcpy(strIrai.htkfkhms, pIrai->htkfkhms);
		strcpy(strIrai.tskflg, pIrai->tskflg);
		strcpy(strIrai.tktflg, pIrai->tktflg);
		strIrai.bnckbn = pIrai->bnckbn;
		strIrai.nbnckbn = pIrai->nbnckbn;
		strcpy(strIrai.knskisyymd, pIrai->knskisyymd);
		strcpy(strIrai.knskryymd, pIrai->knskryymd);
		strcpy(strIrai.knskrytme, pIrai->knskrytme);
		strIrai.kkhkkflg = pIrai->kkhkkflg;
		strIrai.kkiriflg = pIrai->kkiriflg;
		strIrai.kkirilotno = pIrai->kkirilotno;
		strcpy(strIrai.kktoutkid, pIrai->kktoutkid);
		strIrai.knssu = pIrai->knssu;
		strIrai.odrssflg = '2';
		strcpy(strIrai.ytiksbr, pIrai->ytiksbr);
		strIrai.hhkjkflg = pIrai->hhkjkflg;
		if( pIraiUp != NULL ) {
			ZbmlFree(pIraiUp);
			pIraiUp = NULL;
		}
		//�܂���SELECT����
		iIriCnt = 0;
		if( (lRet = ABunIriSel(&strIrai, &pIraiUp, &iIriCnt)) < 0 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�˗����INSERT�G���[(%d)", lRet);
			return( -1 );
		}
		if( iIriCnt ) {
			//�����O���[�v���ݒ肳��Ă��Ȃ��ꍇ��Update
			strcpy(pIraiUp->knsgrp, strIrai.knsgrp);
			if( (lRet = ABunKnsgrpUpdate(pIraiUp)) < 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�˗����UPDATE�G���[(%d)", lRet);
				return( -1 );
			}
			if( Nflg != 2 ) {	//�����{�̏ꍇ�̓I�[�_�쐬���Ȃ�
				if( (lRet = AbufInsOrder(pst_Env, pIraiUp, pBun, pKan, pOrder)) < 0 ) {
					if( lRet != -803 ) {
						sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�d���I�[�_��� INSERT ERROR(%d) IRINO(%s) KNTNO(%s) KNSGRP(%s) KMKCD(%s), SQLCODE(%d)", 
							iLine, pOrder->irino, pOrder->kntno, pOrder->knsgrp, pOrder->kmkcd, lRet);
						return( -1 );
					}
				}
			}
		} else {
			//���݂��Ȃ���΃f�[�^���
			strIrai.irihsmkbn = '2';
			strIrai.odrssflg = '2';
			if( (lRet = A105insIrai( &strIrai )) < 0 ) {
				if( lRet != -803 ) {
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"�˗����INSERT�G���[(%d)", lRet);
					return( -1 );
				}
			}
			if( Nflg != 2 ) {	//�����{�̏ꍇ�̓I�[�_�쐬���Ȃ�
				if( (lRet = AbufInsOrder(pst_Env, &strIrai, pBun, pKan, pOrder)) < 0 ) {
					if( lRet != -803 ) {
						sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"�d���I�[�_��� INSERT ERROR(%d) IRINO(%s) KNTNO(%s) KNSGRP(%s) KMKCD(%s), SQLCODE(%d)", 
							iLine, pOrder->irino, pOrder->kntno, pOrder->knsgrp, pOrder->kmkcd, lRet);
						return( -1 );
					}
				}
			}
		}
		if( Nflg != 2 ) {	//�����{�̏ꍇ�̓I�[�_�쐬���Ȃ�
			//�����`�F�b�N�t�@�C��
			if( (lRet = AbunInsChk(pst_Env, pOrder,  pKan)) < 0 ) {
				if( lRet != -803 ) {
					sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"REALCHK��� INSERT ERROR(%d) IRINO(%s) KNTNO(%s) KNSGRP(%s) KMKCD(%s) SQLCODE(%d)", 
						iLine, pOrder->irino, pOrder->kntno, pOrder->knsgrp, pOrder->kmkcd, lRet);
					return( -1 );
				}
			}
		}
		//�������
		// 2008-03-24 �V�t�����e�B�A�Ή� INS START
		//���̑����e�[�u������ID2���擾
		sFncPutLog(TRCKIND_TRACE, __FILE__, "ABunJido", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"���̑����e�[�u������ID2���擾");

		// ID2�����������ꍇ�A�������ʏ��e�[�u����INSERT����ID2, ID2POS������������
		ret = AZokuSelId2(pBun->sriymd, pBun->kntno, pBun->zssdino, pId2, &iId2pos);
		sFncPutLog(TRCKIND_TRACE, __FILE__, "ABunJido", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"AZokuSelId2 ret[%d]", ret);
		if( ret == HRC_SQL_NORMAL )
		{
			sFncPutLog(TRCKIND_TRACE, __FILE__, "ABunJido", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"strBunchuTB���f�[�^ [pBun->id2='%s', pBun->id2pos=%d]", 
				pBun->id2, pBun->id2pos );

			memcpy(pBun->id2, pId2, sizeof(pId2));
			pBun->id2pos = iId2pos;

			sFncPutLog(TRCKIND_TRACE, __FILE__, "ABunJido", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"���̑����e�[�u������ID2���擾[id2 = '%s', id2pos = %d] BUNCHU[UTKYMD='%s', IRINO='%s', ZSSDINO=%d, SRIYMD='%s', KNTNO='%s', SMPCD='%s', KMKCD='%s']",
				pBun->id2, pBun->id2pos, pBun->utkymd, pBun->irino, pBun->zssdino, pBun->sriymd,
				pBun->kntno, pBun->smpcd, pBun->kmkcd);
		} else {
			if( ret < 0 )
			{
				sFncPutLog(TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"SELECT KENZOK[%s %s %d] [SQLCODE=%d]", 
					pBun->sriymd, pBun->kntno, pBun->zssdino, ret );
				return( 10 );
			}
			else if( ret == HRC_SQL_NOT_FOUND )
			{
				sFncPutLog(TRCKIND_TRACE, __FILE__, "ABunJido", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���̑����e�[�u���Ƀ��R�[�h��������Ȃ��̂ŁAID2�ύX�Ȃ�");
			} else {
				sFncPutLog(TRCKIND_TRACE, __FILE__, "ABunJido", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"���̑����e�[�u�� SELECT ret[%d]", ret);
			}
		}
		// 2008-03-24 �V�t�����e�B�A�Ή� INS END
		strcpy( pBun->kmkcd, (pJdk+i)->jkmkcd);
		if( (lRet = ABunBunIns(pBun)) < 0 ) {
			if( lRet != -803 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunJido", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�������INSERT ERROR LINE(%d) IRINO(%s) KNTNO(%s) KNSGRP(%s) KMKCD(%s) SQLCODE(%d)", 
					iLine, pOrder->irino, pOrder->kntno, pOrder->knsgrp, pOrder->kmkcd, lRet);
				return( -1 );
			}
		}
	}
	if( pIraiUp != NULL ) {
		ZbmlFree(pIraiUp);
		pIraiUp = NULL;
	}
	if( pJdk != NULL ) {
		ZbmlFree(pJdk);
		pJdk = NULL;
	}
	return( 0 );
}

/****************************************************************************/
/*  �� �� ���@�FADateChk()													*/
/*  �@�\�T�v�@�F���t�f�[�^�̐��������m�F����								*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int
ADateChk( char *sDate )
{
	char	sYYYY[5], sMM[3], sDD[3];
	int		iYYYY, iMM, iDD;
	
	memset(sYYYY, 0, sizeof(sYYYY));
	memset(sMM, 0, sizeof(sMM));
	memset(sDD, 0, sizeof(sDD));
	
	if( strlen(sDate) < 10 )
		return( -1 );
	
	memcpy(sYYYY, sDate, 4);
	memcpy(sMM, &sDate[5], 2);
	memcpy(sDD, &sDate[8], 2);

	iYYYY = atoi(sYYYY);
	iMM = atoi(sMM);
	iDD = atoi(sDD);
	
	//�N�`�F�b�N
	if( (iYYYY < 1000) || (iYYYY > 9999) )
		return( -1 );
	
	//���`�F�b�N
	if( (iMM < 1) || (iMM > 12) )
		return( -1 );
	
	//���`�F�b�N
	if( (iDD < 1) || (iDD > 31) )
		return( -1 );
		
	return( 0 );
}
/****************************************************************************/
/*  �� �� ���@�FATimeChk()													*/
/*  �@�\�T�v�@�F�����f�[�^�̐��������m�F����								*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int
ATimeChk( char *sTime )
{
	char	sHH[3], sMM[3], sSS[3];
	int		iHH, iMM, iSS;
	
	memset(sHH, 0, sizeof(sHH));
	memset(sMM, 0, sizeof(sMM));
	memset(sSS, 0, sizeof(sSS));
	
	if( strlen(sTime) < 10 )
		return( -1 );
	
	memcpy(sHH, sTime, 2);
	memcpy(sMM, &sTime[3], 2);
	memcpy(sSS, &sTime[6], 2);

	iHH = atoi(sHH);
	iMM = atoi(sMM);
	iSS = atoi(sSS);
	
	//���`�F�b�N
	if( (iHH < 0) || (iHH > 24) )
		return( -1 );
	
	//���`�F�b�N
	if( (iMM < 0) || (iMM > 59) )
		return( -1 );
	
	//�b�`�F�b�N
	if( (iSS < 0) || (iSS > 59) )
		return( -1 );
		
	return( 0 );
}
/****************************************************************************/
/*  �� �� ���@�FABunchuChk()												*/
/*  �@�\�T�v�@�F����TBL�@���t�E�����`�F�b�N									*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
void
ABunchuChk( Bunchu *pBunch )
{
	if( ADateChk(pBunch->utkymd) < 0 )
		memcpy(pBunch->utkymd, "1000-01-01", 10);
	if( ADateChk(pBunch->sriymd) < 0 )
		memcpy(pBunch->sriymd, "1000-01-01", 10);
}
/****************************************************************************/
/*  �� �� ���@�FABunchuChk()												*/
/*  �@�\�T�v�@�F���̑���TBL�@���t�E�����`�F�b�N								*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
void
AKenzokChk( Kenzok *pKenzok )
{
	if( ADateChk(pKenzok->utkymd) < 0 )
		memcpy(pKenzok->utkymd, "1000-01-01", 10);
	if( ADateChk(pKenzok->sriymd) < 0 )
		memcpy(pKenzok->sriymd, "1000-01-01", 10);
	if( ATimeChk(pKenzok->sstme) < 0 )
		memcpy(pKenzok->sstme, "00:00:01", 8);
	if( ADateChk(pKenzok->ssymd) < 0 )
		memcpy(pKenzok->ssymd, "1000-01-01", 10);
	if( ADateChk(pKenzok->msriymd) < 0 )
		memcpy(pKenzok->msriymd, "1000-01-01", 10);
}
/****************************************************************************/
/*  �� �� ���@�FANinsikiChk()												*/
/*  �@�\�T�v�@�F�F��TBL�@���t�E�����`�F�b�N									*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
void
ANinsikiChk( Ninsiki *pNinsiki )
{
	if( ADateChk(pNinsiki->utkymd) < 0 )
		memcpy(pNinsiki->utkymd, "1000-01-01", 10);
	if( ADateChk(pNinsiki->sriymd) < 0 )
		memcpy(pNinsiki->sriymd, "1000-01-01", 10);
}
/****************************************************************************/
/*  �� �� ���@�FAKenorderChk()												*/
/*  �@�\�T�v�@�F�����I�[�_TBL�@���t�E�����`�F�b�N							*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
void
AKenorderChk( Kenorder *pKen )
{
	if( ADateChk(pKen->knskisymd) < 0 )
		memcpy(pKen->knskisymd, "1000-01-01", 10);
	if( ADateChk(pKen->sriymd) < 0 )
		memcpy(pKen->sriymd, "1000-01-01", 10);
	if( ADateChk(pKen->utkymd) < 0 )
		memcpy(pKen->utkymd, "1000-01-01", 10);
	if( ATimeChk(pKen->sstme) < 0 )
		memcpy(pKen->sstme, "00:00:01", 8);
	if( ADateChk(pKen->ssymd) < 0 )
		memcpy(pKen->ssymd, "1000-01-01", 10);
}
/****************************************************************************/
/*  �� �� ���@�FARealchkChk()												*/
/*  �@�\�T�v�@�F�����`�F�b�NTBL�@���t�E�����`�F�b�N							*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
void
ARealchkChk( Realchk  *pReal )
{
	if( ADateChk(pReal->knskisymd) < 0 )
		memcpy(pReal->knskisymd, "1000-01-01", 10);
	if( ADateChk(pReal->sriymd) < 0 )
		memcpy(pReal->sriymd, "1000-01-01", 10);
	if( ADateChk(pReal->utkymd) < 0 )
		memcpy(pReal->utkymd, "1000-01-01", 10);
	
	//�p�����[�^�t�B�[���h�ɃX�y�[�X����
	if( strlen(pReal->renjicpara) == 0 ) {
		memset(pReal->renjicpara, ' ', 1);
	}
	if( strlen(pReal->soukn1para) == 0 ) {
		memset(pReal->soukn1para, ' ', 1);
	}
	if( strlen(pReal->kanrenpara) == 0 ) {
		memset(pReal->kanrenpara, ' ', 1);
	}
	if( strlen(pReal->bunkkupara) == 0 ) {
		memset(pReal->bunkkupara, ' ', 1);
	}
	if( strlen(pReal->kesseipara) == 0 ) {
		memset(pReal->kesseipara, ' ', 1);
	}
	if( strlen(pReal->rirekipara) == 0 ) {
		memset(pReal->rirekipara, ' ', 1);
	}
	if( strlen(pReal->syougopara) == 0 ) {
		memset(pReal->syougopara, ' ', 1);
	}
	if( strlen(pReal->keisanpara) == 0 ) {
		memset(pReal->keisanpara, ' ', 1);
	}
	if( strlen(pReal->per100para) == 0 ) {
		memset(pReal->per100para, ' ', 1);
	}
	if( strlen(pReal->tousekpara) == 0 ) {
		memset(pReal->tousekpara, ' ', 1);
	}
	if( strlen(pReal->kisyakpara) == 0 ) {
		memset(pReal->kisyakpara, ' ', 1);
	}
	if( strlen(pReal->kouseipara) == 0 ) {
		memset(pReal->kouseipara, ' ', 1);
	}
	if( strlen(pReal->syoungpara) == 0 ) {
		memset(pReal->syoungpara, ' ', 1);
	}
	if( strlen(pReal->soukn2para) == 0 ) {
		memset(pReal->soukn2para, ' ', 1);
	}
	if( strlen(pReal->fukaptpara) == 0 ) {
		memset(pReal->fukaptpara, ' ', 1);
	}
	if( strlen(pReal->yobipara01) == 0 ) {
		memset(pReal->yobipara01, ' ', 1);
	}
	if( strlen(pReal->yobipara02) == 0 ) {
		memset(pReal->yobipara02, ' ', 1);
	}
	if( strlen(pReal->yobipara03) == 0 ) {
		memset(pReal->yobipara03, ' ', 1);
	}
	if( strlen(pReal->yobipara04) == 0 ) {
		memset(pReal->yobipara04, ' ', 1);
	}
	if( strlen(pReal->yobipara05) == 0 ) {
		memset(pReal->yobipara05, ' ', 1);
	}
}
/****************************************************************************/
/*  �� �� ���@�Fsj2euc()													*/
/*  �@�\�T�v�@�FSJIS ��EUC�ϊ�												*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int     sj2euc( bufot, bufin, len )
char        bufot[];
char        bufin[];
int         len;
{
    char    func_nm[256+1];     /* �֐����� */
    int ret;
    size_t  w_szi;
    size_t  szi;
    size_t  szo;
    char    str_in[256+1];
    char    str_ot[256+1];
    char    *pstr_in = str_in;
    char    *pstr_ot = str_ot;

    strcpy( func_nm, "sj2euc" );

    //szi = w_szi = strlen( bufin );
    szi = w_szi = len;
    szo = sizeof( str_ot ) - 1;
    memset( str_in, 0x00, sizeof( str_in ) );
    memset( str_ot, 0x00, sizeof( str_ot ) );
    memcpy( str_in, bufin, szi );
    ret = iconv( G_ic, &pstr_in, &szi, &pstr_ot, &szo );

    // ERROR
/*
    if( ret == -1 ){
        sprintf( G_err, "%d", errno );
        sprintf( G_msg, "[%d]byte�������[%d]byte�ڃR�[�h�ϊ�����"
                "�G���[���������܂����B"
                ,w_szi, w_szi - szi );
        EditCsvMsg( G_msg );
        LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
    }
*/
    memcpy( bufot, str_ot, len - 1 );

    //LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( ret );
}
/****************************************************************************/
/*  �� �� ���@�FGetMstDate()												*/
/*  �@�\�T�v�@�F�}�X�^�f�[�^���������[�h									*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int GetMstDate()
{
	int	iSyaknr, iRet;
	Sysknrmst *strSysknr = NULL;
	int iKnsg;
	Knsgmst *strKnsg = NULL;;
	int iAsyscdl;
	Asyscdlmst *strAsyscdl = NULL;;
	int iRngchk;
	Rngchkmst *strRngchk = NULL;;
	int iSkchk;
	Skchkmst *strSkchk = NULL;;
	int iKrkmk;
	Krkmkmst *strKrkmk = NULL;;
	int iKmk;
	Kmkmst *strKmk = NULL;;
	int iJdkmk;
	Jdkmkmst *strJdkmk;
	int iCalck;
	Calckmkmst *strCalck;

	int i;
	int rec;
	iSyaknr = iKnsg = iAsyscdl = iRngchk = iSkchk = iKrkmk = iKmk = 0;
	g_iSyaknr = g_iKnsg = g_iRngchk = g_iSkchk = g_iKrkmk = g_iKmk = 0;
	g_strKnsg = NULL;
	
	//�V�X�e���Ǘ��}�X�^
	if( g_strSysknr != NULL ) {
		ZbmlFree(g_strSysknr);
		g_strSysknr = NULL;
	}
	if( (iRet = ABunSyskanSelKey(&strSysknr, &iSyaknr)) < 0 ) {
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"�V�X�e���Ǘ��}�X�^ SQL ERROR(%d)",iRet);
		return 0;
	}
	g_iSyaknr = iSyaknr;
	g_strSysknr = strSysknr;


	//YOON 2007-02-07
	if(iSyaknr != 1){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"�V�X�e���Ǘ��}�X�^ �����ԈႢ�܂��B(%d)",iSyaknr);
		return 0;
	}
	
	//(g_strSysknr+i)->kjnsriymd

	//�����O���[�v�}�X�^
	if( g_strKnsg != NULL ) {
		ZbmlFree(g_strKnsg);
		g_strKnsg = NULL;
	}
	if( (iRet = ZdbKnsgmstSelectAll(&strKnsg, &iKnsg)) < 0) {
		printf("SQL ERROR :%d\n",iRet);
	//	if( g_strSysknr != NULL ) {
	//		ZbmlFree(g_strSysknr);
	//		g_strSysknr = NULL;
	//	}
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"�����O���[�v�}�X�^(KNSGMST) SQL ERROR(%d)",iRet);
		return 0;
	}
	//g_iKnsg = iKnsg;
	//g_strKnsg = strKnsg;
	
	//YOON 2007-02-07
	for(i=0,rec=0;i<iKnsg;i++)
	{
		if(memcmp(g_strSysknr->kjnsriymd,(strKnsg+i)->kaiymd,10) >= 0 &&
			memcmp(g_strSysknr->kjnsriymd,(strKnsg+i)->haiymd,10) <= 0)
		{
//			g_strKnsg =(Knsgmst *) ZbmlRealloc((Knsgmst *)g_strKnsg,
//				 sizeof(Knsgmst)*(rec+1));
			g_strKnsg =(Knsgmst *) realloc(g_strKnsg,
				 sizeof(Knsgmst) *(rec+1));
            memset(g_strKnsg+rec,0,sizeof(Knsgmst));
            memcpy(g_strKnsg+rec,strKnsg+i,sizeof(Knsgmst));
			rec++;
		}else{
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				"�����O���[�v�}�X�^(KNSGMST) �J�n��(%s)�p�~��(%s)�̊Ԃɏ�����(%s)���Ȃ��B"
				,(strKnsg+i)->kaiymd
				,(strKnsg+i)->haiymd,g_strSysknr->kjnsriymd);
				
		}
	}
	g_iKnsg = rec;
	ZbmlFree(strKnsg);
	if(g_iKnsg <= 0)
		return 0;


	//�������ڃ}�X�^
	if(g_strKmk != NULL) {
		ZbmlFree(g_strKmk);
		g_strKmk = NULL;
	}
	if( ZdbKmkmstSelectAll(&strKmk, &iKmk) < 0 ) {
//		if( g_strSysknr != NULL ) {
//			ZbmlFree(g_strSysknr);
//			g_strSysknr = NULL;
//		}
//		if( g_strKnsg != NULL ) {
//			ZbmlFree(g_strKnsg);
//			g_strKnsg = NULL;
//		}
//		if( g_strRngchk != NULL ) {
//			ZbmlFree(g_strRngchk);
//			g_strRngchk = NULL;
//		}
//		if( g_strSkchk != NULL ) {
//			ZbmlFree(g_strSkchk);
//			strSkchk = NULL;
//		}
//		if( g_strKrkmk != NULL ) {
//			ZbmlFree(g_strKrkmk);
//			g_strKrkmk = NULL;
//		}
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"�������ڃ}�X�^(KMKMST) SQL ERROR(%d)",iRet);
		return 0;
	}
//	g_strKmk = strKmk;
//	g_iKmk = iKmk;

	//YOON 2007-02-07
    for(i=0,rec=0;i<iKmk;i++){
        if(memcmp(g_strSysknr->kjnsriymd,(strKmk+i)->kaiymd,10) >= 0 &&
            memcmp(g_strSysknr->kjnsriymd,(strKmk+i)->haiymd,10) <= 0)
        {
            g_strKmk =(Kmkmst *) realloc(g_strKmk,
                 sizeof(Kmkmst) *(rec+1));
            memset(g_strKmk+rec,0,sizeof(Kmkmst));
            memcpy(g_strKmk+rec,strKmk+i,sizeof(Kmkmst));
            rec++;
        }else{
            sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "�������ڃ}�X�^(KMKMST) �J�n��(%s)�p�~��(%s)�̊Ԃɏ�����(%s)���Ȃ��B"
				,(strKmk+i)->kaiymd
                ,(strKmk+i)->haiymd,g_strSysknr->kjnsriymd);
        }
    }
	g_iKmk = rec;
    ZbmlFree(strKmk);
    if(g_iKmk <= 0)
        return 0;
	//�����������ڃ}�X�^
	if( g_strJdkmk != NULL ) {
		ZbmlFree(g_strJdkmk);
		g_strJdkmk = NULL;
	}
	if( A105JdkmkSelAll(&strJdkmk, &iJdkmk) < 0 ) {
//		if( g_strSysknr != NULL ) {
//			ZbmlFree(g_strSysknr);
//			g_strSysknr = NULL;
//		}
//		if( g_strKnsg != NULL ) {
//			ZbmlFree(g_strKnsg);
//			g_strKnsg = NULL;
//		}
//		if( g_strRngchk != NULL ) {
//			ZbmlFree(g_strRngchk);
//			g_strRngchk = NULL;
//		}
//		if( g_strSkchk != NULL ) {
//			ZbmlFree(g_strSkchk);
//			strSkchk = NULL;
//		}
//		if( g_strKrkmk != NULL ) {
//			ZbmlFree(g_strKrkmk);
//			g_strKrkmk = NULL;
//		}
//		if(g_strKmk != NULL) {
//			ZbmlFree(g_strKmk);
//			g_strKmk = NULL;
//		}
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			"�����������ڃ}�X�^(JDKMK) SQL ERROR(%d)",iRet);
		return 0;
	}
//	g_strJdkmk = strJdkmk;
//	g_iJdkmk = iJdkmk;

	//YOON 2007-02-07
    for(i=0,rec=0;i<iJdkmk;i++){
        if(memcmp(g_strSysknr->kjnsriymd,(strJdkmk+i)->kaiymd,10) >= 0 &&
            memcmp(g_strSysknr->kjnsriymd,(strJdkmk+i)->haiymd,10) <= 0)
        {
            g_strJdkmk =(Jdkmkmst*) realloc(g_strJdkmk,
                 sizeof(Jdkmkmst) * (rec+1));
            memset(g_strJdkmk+rec,0,sizeof(Jdkmkmst));
            memcpy(g_strJdkmk+rec,strJdkmk+i,sizeof(Jdkmkmst));
            rec++;
        }else{
            sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "�����������ڃ}�X�^(JDKMK) �J�n��(%s)�p�~��(%s)�̊Ԃɏ�����(%s)���Ȃ��B"
				,(strJdkmk+i)->kaiymd
                ,(strJdkmk+i)->haiymd,g_strSysknr->kjnsriymd);

        }
    }
	g_iJdkmk = rec;
    ZbmlFree(strJdkmk);
    if(g_iJdkmk <= 0){
     	
		return 0;
	}

	if( g_strCalck != NULL ) {
		ZbmlFree(g_strCalck);
		g_strCalck = NULL;
	}
	//�v�Z���ڃ}�X�^
	if( ZdbCalckmkmstSelectAll(&strCalck, &iCalck) < 0 ) {
//		if( g_strSysknr != NULL ) {
//			ZbmlFree(g_strSysknr);
//			g_strSysknr = NULL;
//		}
//		if( g_strKnsg != NULL ) {
//			ZbmlFree(g_strKnsg);
//			g_strKnsg = NULL;
//		}
//		if( g_strRngchk != NULL ) {
//			ZbmlFree(g_strRngchk);
//			g_strRngchk = NULL;
//		}
//		if( g_strSkchk != NULL ) {
//			ZbmlFree(g_strSkchk);
//			strSkchk = NULL;
//		}
//		if( g_strKrkmk != NULL ) {
//			ZbmlFree(g_strKrkmk);
//			g_strKrkmk = NULL;
//		}
//		if(g_strKmk != NULL) {
//			ZbmlFree(g_strKmk);
//			g_strKmk = NULL;
//		}
//		if( g_strJdkmk != NULL ) {
//			ZbmlFree(g_strJdkmk);
//			g_strJdkmk = NULL;
//		}
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�v�Z���ڃ}�X�^(CALCKMKMST) SQL ERROR(%d)",iRet);
		return 0;
	}
//	g_strCalck = strCalck;
//	g_iCalck = iCalck;

	//YOON 2007-02-07
//  for(i=0,rec=0;i<g_iCalck;i++)[
    for(i=0,rec=0;i<iCalck;i++){
        if(memcmp(g_strSysknr->kjnsriymd,(strCalck+i)->kaiymd,10) >= 0 &&
            memcmp(g_strSysknr->kjnsriymd,(strCalck+i)->haiymd,10) <= 0)
        {
            g_strCalck =(Calckmkmst*) realloc(g_strCalck,
                 sizeof(Calckmkmst) * (rec+1));
            memset(g_strCalck+rec,0,sizeof(Calckmkmst));
            memcpy(g_strCalck+rec,strCalck+i,sizeof(Calckmkmst));
            rec++;
        }else{
            sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "�v�Z���ڃ}�X�^(CALCKMKMST)�J�n��(%s)�p�~��(%s)�̊Ԃɏ�����(%s)���Ȃ��B"
				,(strCalck+i)->kaiymd
                ,(strCalck+i)->haiymd,g_strSysknr->kjnsriymd);

        }
    }
	g_iCalck = rec;
    ZbmlFree(strCalck);
    if(g_iCalck <= 0){
		sFncPutLog ( TRCKIND_DEBUG, __FILE__, "ABunGetKnsgrp", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"g_iCalck��0�ł��B");
        return 0;
	}

	ZdbCommit();
	return 1;
}
/****************************************************************************/
/*  �� �� ���@�FgetCalkmk()													*/
/*  �@�\�T�v�@�F�A�b�Z�C�X�P�W���[���}�X�^���猟���J�n�����擾����			*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int getCalKmk( char *sKnsgrp, char *sKmkcd, char *sYmd )
{
	int i;

	for( i=0; i < g_iKmk ;++i ) {
		if( !memcmp(sKnsgrp, (g_strKmk+i)->knsgrp, 16) &&
			!memcmp(sKmkcd, (g_strKmk+i)->kmkcd, 7) &
			memcmp(sYmd, (g_strKmk+i)->kaiymd, 10) >= 0 &&
			memcmp(sYmd, (g_strKmk+i)->haiymd, 10) <= 0 ) {
			break;
		}
	}
	if( (g_strKmk+i)->kmksbt == '2' )
		return 1;
	else
		return 0;
}
//YOON 2007-02-07 �����܂��B
/****************************************************************************/
/*  �� �� ���@�FgetKnsKaisibi()												*/
/*  �@�\�T�v�@�F�A�b�Z�C�X�P�W���[���}�X�^���猟���J�n�����擾����			*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
//int getKnsKaisibi(char *sKnsgrp, char *sDateK, char *sDateH ) 
//{
//	char sBuf[128];
//	int	i;
//
//	memset(sBuf, 0, sizeof(sBuf));
//	for( i=0; i < g_iAsyscdl ;++i ) {
//		if( memcmp(sKnsgrp, (g_strAsyscdl+i)->knsgrp, sizeof((g_strAsyscdl+i)->knsgrp)-1) )
//			continue;
//		if( memcmp(sDateK, (g_strAsyscdl+i)->asystartymd, 10) > 0 )
//			continue;
//		if( strlen(sBuf) == 0 ) {
//			memcpy(sBuf, (g_strAsyscdl+i)->asystartymd, 10);
//			continue;
//		}
//		if( memcmp(sBuf, (g_strAsyscdl+i)->asystartymd, 10) < 0 )
//			continue;
//		memcpy(sBuf, (g_strAsyscdl+i)->asystartymd, 10);
//	}
//	if( strlen(sBuf) == 0 )
//		strcpy(sDateH, sDateK);
//	else
//		strcpy(sDateH, sBuf);
//	return 1;
//}
/****************************************************************************/
/*  �� �� ���@�FgetShoribi()												*/
/*  �@�\�T�v�@�F�V�X�e���Ǘ��}�X�^���珈�������擾����						*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int getShoribi( char *sLbcd, char *sSatecd, char *sSyri )
{
	int i;
	for( i=0 ; i < g_iSyaknr ;++i ) 
	{
		if( !memcmp(sLbcd, (g_strSysknr+i)->lbcd, 3) && 
			!memcmp(sSatecd, (g_strSysknr+i)->sateid, 3) ) 
		{
			memcpy(sSyri, (g_strSysknr+i)->kjnsriymd, 10);
			break;
		}
	}
}
/****************************************************************************/
/*  �� �� ���@�FchkBunchu()													*/
/*  �@�\�T�v�@�F�����{����													*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
// CHG E.Osada 2006-08-30
//int chkBunchu( struct bunchuEnv *pst_Env, int iOdrMkFlg, Bunchu *pBun )
//2.01 UPD int chkBunchu( struct bunchuEnv *pst_Env, int iOdrMkFlg, Bunchu *pBun, char *sKnsgrp )
//YOON 2007-02-15
int chkBunchu(struct bunchuEnv *pst_Env,int iOdrMkFlg,Bunchu *pBun,
	char *sKnsgrp,int iDBBunUpflg)
{
	Bunchu *pBunF = NULL;
	Ninsiki strNin;
	int	iCnt, i;
	long lRet;
	int	iHit;

	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "chkBunchu", __LINE__,
		EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
		"�������SELECT IRINO(%s) smpcd(%s) KMKCD(%s) SRIYMD(%s)", 
		pBun->irino, pBun->smpcd, pBun->kmkcd,pBun->sriymd );
	if( (lRet = ABunSelKey( pBun, &pBunF, &iCnt )) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"�������SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)", 
			pBun->irino, pBun->kntno, pBun->kmkcd, lRet);
		return( -1 );
	}
	if( iCnt == 0 ) 
		return 0;
	iHit = 2;
	//�ŐV�̕������R�[�h���擾���A�D�揇�ʂ��l�����A�f�[�^�C������B
	if( pBunF->bnckka == '0' ) {	//���ɕ����n�j�̏ꍇ�͑S�ĕ����{

		// Update 2007.04.05 �d�����������̗D�揇�ʏ�����ǉ� iHit = 2;
		int k;
		for (k = 0; k < g_iKnsg; k++) {
			if((memcmp((g_strKnsg+k)->knsgrp, sKnsgrp, 16) == 0) && 
			   (memcmp((g_strKnsg+k)->kaiymd, pBun->sriymd, 10) <= 0) &&
			   (memcmp((g_strKnsg+k)->haiymd, pBun->sriymd, 10) >= 0)) {
				break;
			}
		}

		if (k == g_iKnsg) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�����O���[�v���� ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) KNSGRP(%s) SQLCODE(%d)", 
				pBun->irino, pBun->kntno, pBun->kmkcd, sKnsgrp, lRet);
			return( -1 );
		}

		if( (g_strKnsg+k)->bgroup != '3') {
			iHit = 2;
		} else {
			// 2007-04-25 UPD id2 -> trid
/* DEL STA
DELL		if (memcmp(pBunF->id2, pBun->id2, 10) < 0) {
DELL			iHit = 2;
DELL		} else
DELL		if (memcmp(pBunF->id2, pBun->id2, 10) > 0) {
DELL			iHit = 1;
DELL		} else {
DELL			if (pBunF->id2pos <= pBun->id2pos) {
DELL				iHit = 2;
DELL			} else {
DELL				iHit = 1;
DELL			}
DELL		}
DEL END*/
			// ���񂪕���OK�̏ꍇ�ɂ̂ݓ����W�b�N��ʂ�
			if( pBun->bnckka == '0' ) {
				if (memcmp(pBunF->trid, pBun->trid, 10) < 0) {
					iHit = 2;
				} else {
					if (memcmp(pBunF->trid, pBun->trid, 10) > 0) {
						iHit = 1;
					} else {
						if (pBunF->trpos <= pBun->trpos) {
							iHit = 2;
						} else {
							iHit = 1;
						}
					}
				}
			}
		}
	} else {
		switch(pBun->bnckka) {
		case '0':		//����OK
			//�D�揇�ʕύX
			iHit = 1;
			break;
		case '1':		//�����{���
			iHit = 2;
			break;
		default:
			if( chkYusen(pst_Env,pBun, pBunF, sKnsgrp) == 0 ) {
				//�D�揇�ʕύX
				iHit = 1;
			}
		}
	}

	if( iHit == 1 ) {
		pBunF->bnckka = '1';
		pBunF->srtkey = AbunGetSort(pst_Env, pBunF->id2, pBunF->bnckka);
		//YOON 2007-02-15 
		if( iDBBunUpflg == 0 ){
			sFncPutLog ( TRCKIND_DEBUG, __FILE__, "chkBunchu", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"������� �I�[�_�쐬�ς̂��ߍX�V���Ȃ�"
				"IRINO(%s) KNTNO(%s) KMKCD(%s)", 
				pBun->irino, pBun->kntno, pBun->kmkcd );
		} else {
		// 2.01 ADD END
			if( (lRet = ABunUpdate( pBunF )) < 0 ) {
				sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"�������SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)", 
					pBun->irino, pBun->kntno, pBun->kmkcd, lRet);
				return( -1 );
			}
		}	// 2.01 ADD
	}
	//ADD E.Osada 2006-09-13
	// �����������̏ꍇ�͔F���� "W" �ݒ�����Ȃ�
	if( memcmp(pBun->id2, "        ", 8) ) {
		memset(&strNin, 0, sizeof(Ninsiki));
		strcpy(strNin.utkymd, pBunF->utkymd);
		strcpy(strNin.sriymd, pBunF->sriymd);
		strcpy(strNin.irino, pBunF->irino);
		strcpy(strNin.kntno, pBunF->kntno);
		strNin.zssdino = pBunF->zssdino;
		if( (lRet = ABunNinUp( &strNin )) < 0 ) {
			sFncPutLog ( TRCKIND_WARNING, __FILE__, "chkBunchu", __LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"�F�����SELECT ERROR IRINO(%s) KNTNO(%s) KMKCD(%s) SQLCODE(%d)", 
				pBun->irino, pBun->kntno, pBun->kmkcd, lRet);
			return( -1 );
		}
	}

	if( pBunF != NULL ) {
		ZbmlFree(pBunF);
		pBunF = NULL;
	}

	return( iHit );
}
/****************************************************************************/
/*  �� �� ���@�FinsWsseqknri()												*/
/*  �@�\�T�v�@�F����WS�̏����e�[�u���ɓo�^����							*/
/*  ���@�@�́@�F                                                            */
/*�@ ��P���� �F															*/
/*  �o�@�@�́@�F                                                            */
/*  ���A���@�F  0     : ����												*/
/* �@�@�@�@�@�@�@-1     : ���s												*/
/****************************************************************************/
int insWsseqknri( char *sSriymd, char *sKnsgrp, char *sTrid, int iKntno, int iMinSeq, int iMaxSeq )
{
	int num;
	Wsseqknri	strWsSeq, *pWsSeq = NULL;
	long lRet;
	char	buf[10];

	//���[�N�V�[�g�r�d�p�Ǘ����̌������擾����
	if( (lRet = A105wsAllSel( &pWsSeq, &num ) ) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "insWsseqknri", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"WSSEQKNRI SELECT(ALL) ERROR SQLCODE(%d)", lRet );
		return( -1 );
	}

	//�f�[�^�̃Z�b�g
	memset(&strWsSeq, 0, sizeof(strWsSeq));
	strWsSeq.wstbnknr = num+1;
	ZbmlChgDBDate(strWsSeq.knskisymd, sSriymd, sizeof(strWsSeq.knskisymd)-1);
	memcpy(strWsSeq.knsgrp, sKnsgrp, sizeof(strWsSeq.knsgrp)-1);
	memcpy(strWsSeq.wssbt, sTrid, 4);
	memset(buf, 0, sizeof(buf));
	memcpy(buf, &sTrid[4], 4);
	strWsSeq.wsno = atoi(buf);
	strWsSeq.knsseqst = iMinSeq;
	strWsSeq.knsseqed = iMaxSeq;
	strWsSeq.knsseqsu = iKntno;
	strcpy(strWsSeq.dtnrtts, "DEAMON");
	strWsSeq.ksktkbn = 'A';

	if( (lRet = A105wsInsert( &strWsSeq )) < 0 ) {
		sFncPutLog ( TRCKIND_WARNING, __FILE__, "insWsseqknri", __LINE__,
			EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			"WSSEQKNRI INSERT ERROR TRID(%d) SQLCODE(%d)", sTrid, lRet );
		return( -1 );
	}
	if(pWsSeq != NULL )
		ZbmlFree(pWsSeq);
	
	ZdbCommit();

	return( 0 );
}
 
///////////////////////////////////////////////////////////////////////////////
// ADD E.Osada 2006-08-30
// �������̗D��m�F(����˗��E���ꕪ�����ʂ̏ꍇ)
// �߂�l�F�O�@��P�����D��
//         �P�@��Q�����D��
///////////////////////////////////////////////////////////////////////////////
int chkYusen(struct bunchuEnv *pst_Env,Bunchu *chk0, Bunchu *chk1, char *sKnsgrp ) 
{
	int	ret, i, iEda0, iEda1;
	char	sStartDay[128], cSybt, sChk[3], wBuf0[10], wBuf1[10];
	char	sTrid0[11], sTrid1[11];

	//�����J�n���擾
	memset(sStartDay, 0, sizeof(sStartDay));
	//YOON 2007-02-01
	//getKnsKaisibi(sKnsgrp, chk0->sriymd, sStartDay);
	getShoribi(pst_Env->sLbcd, pst_Env->sSateid, sStartDay);

	ret = 0;
	//�����O���[�v�}�X�^�擾
	for( i=0; i < g_iKnsg ;++i ) {
		if( !(!memcmp((g_strKnsg+i)->knsgrp, sKnsgrp, 16) && 
			(memcmp((g_strKnsg+i)->kaiymd, sStartDay, 10) <= 0)) ) {
			continue;
		}
		cSybt = (g_strKnsg+i)->knssbt;
		break;
	}

	if( i == g_iKnsg ) {
		//�����O���[�v���Ȃ��@���I�H�@����Ȃ�
		return( ret );
	}

	memset(sChk , 0, sizeof(sChk));
	if( cSybt == 'O' ) {
		// ��ʂ��u���̑��v�̏ꍇ
		// �@����No�̎}�Ԃ�50�ȏ�
		memset(sChk , '0', sizeof(sChk)-1);
		if( memcmp(&chk0->kntno[9], "50", 2) >= 0 )
				sChk[0] = '1';
		if( memcmp(&chk1->kntno[9], "50", 2) >= 0 )
				sChk[1] = '1';
		if( !memcmp(sChk, "10", 2) ) {
			//��P�����D��
			return( 0 );
		}
		if( !memcmp(sChk, "01", 2) ) {
			//��Q�����D��
			return( 1 );
		}

	  // ADD E.Osada 2006-09-12
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//	  if( ((chk0->id2[0] == 'X') || (chk0->id2[0] == 'Y')) &&
	  if( ((chk0->id2[0] == 'V') || (chk0->id2[0] == 'X') || (chk0->id2[0] == 'Y')) &&
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
		  ((chk1->id2[0] == 'T') || (chk1->id2[0] == 'K')) ) {
			//������D��
			return( 0 );
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//	  } else if( ((chk1->id2[0] == 'X') || (chk1->id2[0] == 'Y')) &&
	  } else if( ((chk1->id2[0] == 'V') || (chk1->id2[0] == 'X') || (chk1->id2[0] == 'Y')) &&
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
			   ((chk0->id2[0] == 'T') || (chk0->id2[0] == 'K')) ) {
			//������D��
			return( 1 );
	  } else {
		// �A�Q�h�c�|�W�V����������
		if( (chk0->id2pos > 0) && (chk1->id2pos == 0) ) {
			//��P�����D��
			return( 0 );
		} else if( (chk1->id2pos > 0) && (chk0->id2pos == 0) ) {
			//��Q�����D��
			return( 1 );
		}
	  }
	} else {
		// ��ʂ��u���̑��v�ȊO�̏ꍇ
		// �@����No�̎}�Ԃ�50�ȉ�
		memset(sChk , '0', sizeof(sChk)-1);
		if( memcmp(&chk0->kntno[9], "50", 2) <= 0 )
				sChk[0] = '1';
		if( memcmp(&chk1->kntno[9], "50", 2) <= 0 )
				sChk[1] = '1';
		if( !memcmp(sChk, "10", 2) ) {
			//��P�����D��
			return( 0 );
		}
		if( !memcmp(sChk, "01", 2) ) {
			//��Q�����D��
			return( 1 );
		}

	  // ADD E.Osada 2006-09-12
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//	  if( ((chk0->id2[0] == 'X') || (chk0->id2[0] == 'Y')) &&
	  if( ((chk0->id2[0] == 'V') || (chk0->id2[0] == 'X') || (chk0->id2[0] == 'Y')) &&
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
		  ((chk1->id2[0] == 'T') || (chk1->id2[0] == 'K')) ) {
			//������D��
			return( 0 );
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//	  } else if( ((chk1->id2[0] == 'X') || (chk1->id2[0] == 'Y')) &&
	  } else if( ((chk1->id2[0] == 'V') || (chk1->id2[0] == 'X') || (chk1->id2[0] == 'Y')) &&
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
			   ((chk0->id2[0] == 'T') || (chk0->id2[0] == 'K')) ) {
			//������D��
			return( 1 );
	  } else {
		// �A�Q�h�c��'X'/'Y'�Ŏn�܂��Ă��Ȃ�
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//		if( (chk1->id2[0] == 'X') || (chk1->id2[0] == 'Y') ) {
//			if( (chk0->id2[0] != 'X') && (chk0->id2[0] != 'Y') ) {
		if( (chk1->id2[0] == 'V') || (chk1->id2[0] == 'X') || (chk1->id2[0] == 'Y') ) {
			if( (chk0->id2[0] != 'V') && (chk0->id2[0] != 'X') && (chk0->id2[0] != 'Y') ) {
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
				if( memcmp(sKnsgrp,"0047",4) == 0){
					//��܍��ڂ̏ꍇ�� V ��D��
					return( 1 );
				} else {
					//��P�����D��
					return( 0 );
				}
			}
// 2008-07-02 �V�t�����e�B�A�Ή� UPD START
//		} else if( (chk0->id2[0] == 'X') || (chk0->id2[0] == 'Y') ) {
//			if( (chk1->id2[0] != 'X') && (chk1->id2[0] != 'Y') ) {
		} else if( (chk0->id2[0] == 'V') || (chk0->id2[0] == 'X') || (chk0->id2[0] == 'Y') ) {
			if( (chk1->id2[0] != 'V') && (chk1->id2[0] != 'X') && (chk1->id2[0] != 'Y') ) {
// 2008-07-02 �V�t�����e�B�A�Ή� UPD END
				if( memcmp(sKnsgrp,"0047",4) == 0){
					//��܍��ڂ̏ꍇ�� V ��D��
					return( 0 );
				} else {
					//��Q�����D��
					return( 1 );
				}
			}
		}
	  }
	}

	if( (!memcmp(chk0->id2, "TTTT", 4) || !memcmp(chk0->id2, "KKKK", 4)) &&
		(!memcmp(chk1->id2, "TTTT", 4) || !memcmp(chk1->id2, "KKKK", 4)) && 
		((cSybt == 'Z') || (cSybt == 'G')) ) {
		memset(wBuf0, 0, sizeof(wBuf0));
		memset(wBuf1, 0, sizeof(wBuf1));
		memcpy(wBuf0, &chk0->kntno[9], 2);
		memcpy(wBuf1, &chk1->kntno[9], 2);
		iEda0 = atoi(wBuf0);
		iEda1 = atoi(wBuf1);
		if( cSybt == 'Z' ) {	//���͑O
			//���͑O�́A�@�O�@���D��
			if( (iEda0 == 0) && (iEda1 != 0) ) {
				//��P�����D��
				return( 0 );
			}
			if( (iEda0 != 0) && (iEda1 == 0) ) {
				//��Q�����D��
				return( 1 );
			}
			if( (iEda0 % 2) && !(iEda1 % 2) ) {
				//��P�����D��
				return( 0 );
			}
			if( !(iEda0 % 2) && (iEda1 % 2) ) {
				//��Q�����D��
				return( 1 );
			}
		} else if( cSybt == 'G' ) {		//���͌�
			//���͑O�́A�@�O�@������D��
			if( !(iEda0 % 2) && (iEda1 % 2) ) {
				//��P�����D��
				return( 0 );
			}
			if( (iEda0 % 2) && !(iEda1 % 2) ) {
				//��Q�����D��
				return( 1 );
			}
		}
	} else {
		// ADD 2007-04-26 ���(0047)��p�̗D�惋�[���ǉ��i�Q�h�c�̕��їD��j
		if( memcmp(sKnsgrp,"0047",4) == 0){
			trim(sTrid0,chk0->id2);
			trim(sTrid1,chk1->id2);
			
			// �B' ��܂̏ꍇ�͂Q�h�c�̎Ⴂ�����Ƃ�
            if (strcmp(sTrid0, sTrid1) < 0) {
				//��P�����D��
				return( 0 );
            } else {
                if (strcmp(sTrid0, sTrid1) > 0) {
					//��Q�����D��
					return( 1 );
                } else {
                    if (chk0->id2pos <= chk1->id2pos) {
						//��P�����D��
						return( 0 );
                    } else {
						//��Q�����D��
						return( 1 );
                    }
                }
            }

		}
		else{
			// �B���̂m���̎}�Ԃ��Ⴂ
			ret = memcmp(chk0->kntno, chk1->kntno, 13);
			if( ret < 0 ) {
				//��P�����D��
				return( 0 );
			}
			if( ret > 0 ) {
				//��Q�����D��
				return( 1 );
			}
		}
	}

	// �C��ɏ���������Q�����D��
	return( 1 );
	
}

// ADD Nagata 2007-04-26
// �w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[����
void trim(char *dst, char *src) {
    int dstCnt;
    int srcCnt;
    int Flg;

    for(dstCnt = 0, srcCnt = 0, Flg = 0;
        src[srcCnt] != '\0';
        srcCnt ++) {
        if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
            continue;
        }
        dst[dstCnt++] = src[srcCnt];
        if (src[srcCnt] != '\x20') {
            Flg = dstCnt;
        }
    }
    dst[Flg] = '\0';
}

/** End of File ***************************************************************/

