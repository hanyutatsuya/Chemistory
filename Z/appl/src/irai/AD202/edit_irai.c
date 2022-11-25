/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����Fedit_irai.c                                                  */
/*   �T      �v�F�f�[�^�ҏW����                                               */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�o�^����)�Ή�        */
/*  1.04     2007/06/01     INTEC.INC      �����������ړo�^�{����G�ҏW�ǉ�    */
/*  2.01     2007/06/01     INTEC.INC      �W������404�̒ǉ�                  */
/*  3.01     2007/06/01     INTEC.INC      �ً}�^�p�ύX�ɔ����ǉ��C��         */
/*  4.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD202.h"

/******************************************************************************/
/*  �� �� ��  �FEditKinqIrai                                                  */
/*  �@�\�T�v  �FAS400�ً}�˗��f�[�^�ҏW ���@�`�F�b�N                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  AS4IRAI   	*inp;	: AS400�ً}�˗����               */
/*   ��Q���� �Fstruct  _KANJYA   	*kan;	: ���ґ������                    */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI		*iri;	: �˗����                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditKinqIrai( inp, kan, iri )
struct		AS4IRAI		*inp;		/* AS400�ً}�˗����(S-JIS)	*/
struct		_KANJYA		*kan;		/* ���ґ����\����		*/
struct		_IRAI		*iri;		/* �˗����\����		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	buf2[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;							// �R�[�h�ϊ��߂�l
	struct	stcKJNO		kj;					// ��lNO�擾�p�\����

	/* ��������	*/
	strcpy(func_nm, "EditKinqIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 �a�l�k��t�N����
	strcpy( iri->utkymd,	kan->utkymd );

	// 2 �˗����m��
	strcpy( iri->irino,	kan->irino );
	// 3 �˗����m�������t���O
	strcpy( iri->iriketflg,kan->iriketflg );

	// 4 �˗�����m��
	iri->zssdino	= stcPRM.myp_sedai;

	// 5 �����O���[�v
		// 1.04             -> ���ڃ}�X�^���ƈꏏ�ɕҏW
	strcpy( iri->knsgrp, 	" " );

	// 6 ���ڃR�[�h			<- ���ڃ}�X�^���ƈꏏ�ɕҏW

	// 7 �˗��������敪		0:��ʃV�X�e��
	iri->irihsmkbn[0] = '0';
	
	// 8 �˗��敪			K:�ً}
	iri->irikbn[0] = 'K';

	// 9 �����H���敪		A:�ʏ�
	iri->ksktkbn[0] = 'A';

	// 10 ������			�V�X�e���Ǘ��}�X�^�D�ً}��t��
	strcpy( iri->sriymd,	stcPRM.myp_kjnymd );

	// 11 ���̂m��
	strcpy( iri->kntno,		kan->irino );
	// 12 ���̂m�������t���O
	strcpy( iri->kntketflg,	" " );

	// 13 �`�F�b�N�����i����ς�K�v�j
	memset( buf, '\0', sizeof( buf ));
	if( memcmp( inp->c_kentai_ch, MYAPP_SPACE10, sizeof(inp->c_kentai_ch))==0){
		// 3.01 ADD	����No6������Z�o
		memcpy( buf,	inp->c_kentai_no	,sizeof( inp->c_kentai_no ));
		EditChkmj( buf,	iri->chkmj );
	} else {
		cret=sj2euc( iri->chkmj, memcpy(buf, inp->c_kentai_ch,
        	sizeof( inp->c_kentai_ch )), sizeof( iri->chkmj ));
			// WARNING
		if( cret != RTN_OK ){
			sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�`�F�b�N�����z[%s]"
				,iri->chkmj );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// 14 ����ޗ��R�[�h		<- INPUT 3byte CODE 3byte DB 4byte
	if( memcmp( inp->c_zairyo_cd, MYAPP_ZRCD_ASDEF, sizeof(inp->c_zairyo_cd))==0){
											/* �ޗ��R�[�h����̃P�[�X */
		strcpy( iri->stsrcd,	MYAPP_DEF_ZRCD );
											/* ����ޗ��R�[�h���f�t�H���g(�����F023)�ɐݒ肷�� */
		sprintf( G_msg, "�ޗ��R�[�h�ɏ����l��ݒ肵�܂�[%s]" ,iri->stsrcd );
		EditCsvMsg( G_msg );				/* DEBUG�o��(LOG)���Ă��� */
		LogOut( LT_DBG, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	} else {								/* �ޗ��R�[�h���ݒ肳��Ă���P�[�X */
		sprintf( iri->stsrcd, "%-3.3s",  inp->c_zairyo_cd );
											/* ���̂܂܃R�s�[���� */
	}

	// 15 ���ڗ���			<- ���ڃ}�X�^�ҏW��
	// 16 �e���ڃR�[�h		<- ���ڃ}�X�^�ҏW��
	// 17 �T���v�����O�R�[�h<- ���ڃ}�X�^�ҏW��

	// 18 �Z�b�g���ڃR�[�h
	strcpy( iri->setkmkcd,	"0000000" );
	// 19 �������e�R�[�h
	strcpy( iri->srinycd,	"0" );

	// 20 �Z�N�V�����R�[�h	<- ���ڃ}�X�^�ҏW��

	// 21 �o�׃`�F�b�N�t���O
	strcpy( iri->skchkflg,	"0" );

	// 22 ���敉�׋敪		<- ���ڃ}�X�^�ҏW��

	// 23 �D�惌�x��
	strcpy( iri->ysnlbl,	"00" );

	// 24 �W���t���O 		<- �J�[�h�敪='17'�Ȃ��'1'
	if( strcmp( kan->cdkbn1, "17" ) == 0 ){
		iri->skflg[0] = '1';
	} else {
		iri->skflg[0] = '0';
	}
    if(( memcmp( inp->c_kentai_no, "12", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "13", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "14", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "20", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "90", 2 ) == 0 )){
//     ( memcmp( inp->c_kentai_no, "403", 3 ) == 0 )||
//     ( memcmp( inp->c_kentai_no, "404", 3 ) == 0 )||    // 2.1 ADD
//     ( memcmp( inp->c_kentai_no, "405", 3 ) == 0 )||
//     ( memcmp( inp->c_kentai_no, "412", 3 ) == 0 )||
//     ( memcmp( inp->c_kentai_no, "490", 3 ) == 0 ))[
        iri->skflg[0] = '1';
    }

	
	// 25 �ǉ��t���O	
	strcpy( iri->tkflg,		"0" );
	// 26 �폜�t���O
	strcpy( iri->sjflg,		"0" );
	// 27 �����ǉ��t���O
	strcpy( iri->jktkflg,	"0" );

	// 28 ��l�m�n		<- ���ڃ}�X�^�ҏW��
	// 29 ���ו񍐂m�n�\���敪
	// 30 ���ʊ�l�m�n
	// 31 ���ʊ�l�t���O

	// 32 ���^���׎���
		 // �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(iri->htkfkhms);w_num < sizeof(iri->htkfkhms)-1;w_num+=2 ){
		memcpy( &iri->htkfkhms[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 33 ���̓t���O
	// 34 �����t���O

	// 35 �����敪		2(=�������ڃT�e���C�g�L��j
	iri->bnckbn[0] = '2';
	// 36 �A�����敪	0(=�񕪒����ځj
	iri->nbnckbn[0] = '0';

	// 37 �����J�n�\���
	strcpy( iri->knskisyymd,INIT_DATE );
	// 38 ���������\���
	strcpy( iri->knskryymd,	INIT_DATE );
	// 39 ���������\�莞��
	strcpy( iri->knskrytme,	INIT_TIME );

	// 40 �ً}�񍐃t���O
	iri->kkhkkflg[0] = '0';

	// 41 �ً}�˗��t���O
	memcpy( iri->kkiriflg,	inp->c_kinkyu_flg,sizeof( inp->c_kinkyu_flg ));

	// 42 �ً}�˗����b�g�m��
	memset( w_str,	'\0',	sizeof( w_str ));
	memcpy( w_str,	inp->c_lotno,sizeof( inp->c_lotno ));
	iri->kkirilotno = atoi( w_str );

	// 43 �ً}�Ή���t�h�c
	strcpy( iri->kktoutkid,	" " );
	// 44 ������
	iri->knssu = 1;

	// 45 �I�[�_�쐬�t���O	��:�����l
	iri->odrssflg[0] = ' ';

	// 46 �\���ߔ{��
	iri->ytiksbr[0] = '1';

	// 47 �񍐏󋵃t���O
	strcpy( iri->hhkjkflg,	" " );

	// 48 ���X�V����  CURRENT TIMESTAMP
    // 1.01 ADD 49 �o�^���� CURRENT TIMESTAMP

	// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
/*
//	if( stcPRM.myp_debug == 1 ){
//		irai_pr( iri );
//	};
*/
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FEditKinqIraiKomoku                                            */
/*  �@�\�T�v  �F�ً}�Ή����ڔ��f�����ڃ}�X�^���ҏW                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  KOMST   	*kom;	: ���ڏ��                        */
/*   ��Q���� �Fchar	zairyo[];			: �ޗ��R�[�h                      */
/*   ��R���� �Fchar	age[];				: �N��                            */
/*   ��S���� �Fchar	skflg[];			: �W���t���O                      */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
// 1.04 int		EditKinqIraiKomoku( kom, zairyo, age )
int		EditKinqIraiKomoku( kom, zairyo, age, skflg )
struct		KOMST		*kom;		/* �˗����ڏ��\����	*/
char		zairyo[];
char		age[];
char		skflg[];				// 1.04 ADD
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	buf2[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	struct	stcKJNO		kj;					// ��lNO�擾�p�\����

	/* ��������	*/
	strcpy(func_nm, "EditKinqIraiKomoku" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// �ً}�Ή����ڃ}�X�^�擾->���ڃ}�X�^�A�����O���[�v����
/* 1.04 DEL
DEL	if( SelKinqKomokmst( kom, skflg ) != RTN_OK ){
DEL		// �ΏۊO
DEL		return( RTN_SKIP );
DEL	}
*/
	// 1.04 ADD ����CD+�T���v�����O+����G.���->�R�[�h���Ⴂ�擪�P����
	if( SelKinqKomokmst( kom, skflg ) != RTN_OK ){
		// �W����z�肵�Ď擾���s�̏ꍇ�́A��ʂōēx�擾������
		if( skflg[0] == '1' ){
/* 3.01 	�ً}��1rec�ŕ������ڂ̂���DEL
DEL			strcpy( skflg,	"0" );
*/
			if( SelKinqKomokmst( kom, skflg ) != RTN_OK ){
				sprintf( G_msg,"��ʏW�����ɊY�����錟���O���[�v������܂���B"
					"����CD[%s]�W��F[%s]",
					kom->kmkcd, skflg );
				EditCsvMsg( G_msg );
				LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__);
				// SKIP
				ret=RTN_SKIP;
			}
		} else {
			sprintf( G_msg,"�Y�����錟���O���[�v������܂���B"
				"����CD[%s]�W��F[%s]",
				kom->kmkcd, skflg );
			EditCsvMsg( G_msg );
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// SKIP
			ret=RTN_SKIP;
		}
	}
	if( ret == RTN_SKIP ){
		sprintf( G_msg,
			"�Ώۃ��{�ł����}�X�^�ɊY�����鍀�ځA�O���[�v�����݂����ASKIP���܂��B"
			"����CD[%s]�W��F[%s]",
			kom->kmkcd, skflg );
		EditCsvMsg( G_msg );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		return( RTN_SKIP );
	}

	// DEBUG
	sprintf( G_msg,
		"���ڃ}�X�^GET�I" "����CD[%s]�W��F[%s]->SMPCD[%s]KNSGRP[%s]",
		kom->kmkcd, skflg, kom->smpcd, kom->knsgrp );
	EditCsvMsg( G_msg );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	// 15 ���ڗ���			<- ���ڃ}�X�^�ҏW��
	// 16 �e���ڃR�[�h		<- ���ڃ}�X�^�ҏW��
	// 17 �T���v�����O�R�[�h<- ���ڃ}�X�^�ҏW��
	// 20 �Z�N�V�����R�[�h	<- ���ڃ}�X�^�ҏW��
	// 22 ���敉�׋敪		<- ���ڃ}�X�^�ҏW��

	// 28 ��l�m�n		<- ���ڃ}�X�^�ҏW��
	memset( &kj,		'\0', sizeof( struct stcKJNO ));
	strcpy( kj.kmkcd,	kom->kmkcd );
	strcpy( kj.zrcd,	zairyo );
	strcpy( kj.age,		age );
	strcpy( kj.agekbn,	AGEKBN_YEAR );

	if( GetKjnmst( &kj ) == RTN_OK ){
		strcpy( kom->kjno,	kj.kjno );	
	} else {
		strcpy( kom->kjno,	"000" );	
		sprintf( G_msg,
			"�Y�������l�}�X�^�f�[�^������܂���B: ����CD[%s]�ޗ�CD[%-4s]",
			kom->kmkcd, zairyo );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FGetKjnmst                                                     */
/*  �@�\�T�v  �F��lNO�擾                                                  */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct	stcKJNO		*in;: ��lNO�擾�p�\����                */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fint   kjno; 			: ��lNO                            */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		GetKjnmst( in )
struct		stcKJNO		*in;	
{
	char	func_nm[MYAPP_LEN_FNCNM+1];			/* �֐�����	*/
static	int	init_flg = 0;
static  int  kj_max;
	int		ret;
	int 	i = 0;
	int		knichirei;
	char	keybuf[30];

	/* ��������	*/
	strcpy( func_nm, "GetKjnmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ��l�}�X�^�̊l��	*/
	if( init_flg == 0 ){
		// �Ώۊ�l�}�X�^�̌����擾
		kj_max=SelCountKjnmst( stcPRM.myp_kjnymd );
		// �̈�m��
		if(( pKjn = ((struct _KJNMST *)malloc( 
					sizeof(struct _KJNMST) * kj_max ))) == NULL ){
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, "��l�}�X�^�̗̈�m�ۂɎ��s���܂����B" );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
                return( RTN_NG );
		}
		/* ��l�}�X�^�ޔ�̈�̏�����	*/
		memset( pKjn, '\0', sizeof( struct _KJNMST ) * kj_max );

		// �Ώۊ�l�}�X�^�̎擾
		if( SelKjnmst( stcPRM.myp_kjnymd, kj_max ) !=  RTN_OK ){
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, "��l�}�X�^�̓ǂݍ��݂Ɏ��s���܂����B" );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );

				free( pKjn );
                return( RTN_NG );
		}
		//-----------------------------------------------------------------
		for ( i = 0; i < kj_max; i++ ){
			// �����L�[�̐ݒ�
			sprintf( pKjn[i].kkey, "%-7s%-4s000", pKjn[i].kmkcd, pKjn[i].zrcd );
			// ����𐔒l�ϊ�����
			pKjn[i].knlow=atoi( pKjn[i].nichilw );
			pKjn[i].knhigh=atoi( pKjn[i].nichihi );
		}
		sprintf( G_msg, "��l�}�X�^����[%d]", kj_max );
		LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		init_flg = 1;
		return( RTN_OK );
	}

	// ��������߂�
	if( strcmp( in->agekbn,	AGEKBN_UNKNOWN ) == 0 ){
		knichirei = 99999;
	} else if( strcmp( in->agekbn, AGEKBN_YEAR ) == 0 ){
		knichirei = atoi( in->age ) * 365;
	} else if( strcmp( in->agekbn, AGEKBN_MONTH ) == 0 ){
		knichirei = atoi( in->age ) * 30;
	} else if( strcmp( in->agekbn, AGEKBN_WEEK ) == 0 ){
		knichirei = atoi( in->age ) * 7;
	} else if( strcmp( in->agekbn, AGEKBN_DAY ) == 0 ){
		knichirei = atoi( in->age ) * 1;
	} else {
		knichirei = 0;
	}

	/* ��������̊�l�}�X�^�f�[�^���猟�� */
	strcpy( in->kjno,	"000" );
	memset( keybuf,		'\0',			sizeof( keybuf ));
	sprintf( keybuf,	"%-7s%-4s000",	in->kmkcd, in->zrcd );

	if( stcPRM.myp_debug != 0 ){
		sprintf( G_msg,"KJNO SERCH STA keybuf[%s] rei[%d]", keybuf,knichirei );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	// �ޗ��R�[�h���󔒂̏ꍇ�́A��l��000��ݒ�
	if( strncmp( in->zrcd, MYAPP_SPACE10, 4 ) == 0 ){
		strcpy( in->kjno, "000" );
	}

	// ��1����
	for( i = 0; i <= kj_max; ++i ){
		ret = memcmp( keybuf, pKjn[i].kkey, MYAPP_LEN_KJN );
		if( ret == 0 ){
			strcpy( in->kjno, pKjn[i].kjno );

			// DEBUG
			if( stcPRM.myp_debug != 0 ){
				sprintf( G_msg,"KJNO1 HAS FOUND !! kjno[%s] keybuf[%s]", 
						in->kjno, keybuf );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm,
						 __FILE__, __LINE__ );
			}
			ret=RTN_OK;
			break;
		} else if( ret < 0 ){
				// WARNING
			sprintf( G_msg,"KJNO NOT FOUND !!  keybuf[%s]", keybuf );
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, 
						__FILE__, __LINE__ );
			// �����𔲂���
			return( RTN_NG );
		}
	}
	// ��2����
	for( ; i <= kj_max; ++i ){
		ret = memcmp( keybuf, pKjn[i].kkey, MYAPP_LEN_KJN );
			// KEY���傫���Ȃ����甲����
		if( ret < 0 ){
			break;
		}
		if(( knichirei >= pKjn[i].knlow ) && ( knichirei <=  pKjn[i].knhigh )){
			strcpy( in->kjno, pKjn[i].kjno );

			// DEBUG
			if( stcPRM.myp_debug != 0 ){
				sprintf( G_msg,"KJNO2 HAS FOUND !! kj[%s]rei[%d] [%d]-[%d]", 
						pKjn[i].kjno,knichirei, pKjn[i].knlow, pKjn[i].knhigh );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm,
						 __FILE__, __LINE__ );
			}
			ret=RTN_OK;
			break;
		}
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

// 1.04 ADD STA ==============================================================
/******************************************************************************/
/*  �� �� ��  �FEditJidoIrai                                                  */
/*  �@�\�T�v  �F���������˗��ҏW                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  JIDOIRAI		*jdi;	: ���������˗����            */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditJidoIrai( jdi )
struct		JIDOIRAI		*jdi;	// ���������˗����
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	struct	stcKJNO		kj;					// ��lNO�擾�p�\����

	strcpy( func_nm, "EditJidoIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	���������˗���� EDIT
	//=========================================
	// 5 �����O���[�v
	strcpy( jdi->sIri.knsgrp,	jdi->sJdm.jknsgrp );
	// 6 ���ڃR�[�h
	strcpy( jdi->sIri.kmkcd,	jdi->sJdm.jkmkcd );
	// 7 �˗��������敪
	if( jdi->sJdm.hhkumflg[0] == '0' ){				// �񍐂��Ȃ�
		// �T�e���C�g�V�X�e���i�񍐖����j
		strcpy( jdi->sIri.irihsmkbn,	"2" );
	} else if( jdi->sJdm.hhkumflg[0] == '1' ){		// �񍐂���
		// �T�e���C�g�V�X�e���i�񍐗L��j
		strcpy( jdi->sIri.irihsmkbn,	"1" );
	}
	// 15 ���ڗ���
	strcpy( jdi->sIri.kmkrs,	jdi->sKmk.kmkrs );
	// 16 �e���ڃR�[�h
	strcpy( jdi->sIri.oyakmkcd,	jdi->sKmk.oyakmkcd );
	// 17 �T���v�����O�R�[�h
	strcpy( jdi->sIri.smpcd,	jdi->sKmk.smpcd );
	// 18 �Z�b�g���ڃR�[�h
	strcpy( jdi->sIri.setkmkcd,	"0000000" );
	// 19 �������e�R�[�h
	strcpy( jdi->sIri.srinycd,	"2" );
	// 22 ���敉�׋敪
	strcpy( jdi->sIri.bkfkkbn,	jdi->sKmk.fkbnkkb );
	// 28 ��l�m�n
	memset( &kj,		'\0', sizeof( struct stcKJNO ));
	strcpy( kj.kmkcd,	jdi->sIri.kmkcd );
	strcpy( kj.zrcd,	jdi->sIri.stsrcd );
	strcpy( kj.age,		jdi->age );
	strcpy( kj.agekbn,	jdi->agekbn );
	if( GetKjnmst( &kj ) != RTN_OK ){
		sprintf( G_msg,"�Y�������l�}�X�^�f�[�^������܂���B"
			"����CD[%s]�ޗ�CD[%-4s]",
			jdi->sIri.kmkcd, jdi->sIri.stsrcd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
	}
	strcpy( jdi->sIri.kjno,		kj.kjno );	

	// 45 �I�[�_�쐬�t���O
	strcpy( jdi->sIri.odrssflg,	" " );

	// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
	if( stcPRM.myp_debug == 1 ){
		irai_pr( &jdi->sIri );
	};
	
	// ���O�o�͗p�L�[���ڐݒ�
	strcpy( G_utkymd,	jdi->sIri.utkymd );
	strcpy( G_irino,	jdi->sIri.irino );
	G_zssdino=jdi->sIri.zssdino;
	strcpy( G_kmkcd,	jdi->sIri.kmkcd );
	strcpy( G_kntno,	jdi->sIri.kntno );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
// 1.04 ADD END =============================================================
/******************************************************************************/
/*  �� �� ��  �FEditChkmj                                                     */
/*  �@�\�T�v  �F���̃`�F�b�N�����ҏW                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar  ����No�iINPUT6��)	*jdi;	: ���������˗����            */
/*   ��Q���� �Fchar  ���̃`�F�b�N����  *chkmj;	: ���̃`�F�b�N����            */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
//*fc	CONVERT FROM SINGLE
//    ����No���`�F�b�N�������Z�o����
//*nm
//    ���R�@��
//*dt
//    1996.02.15
//*rt
//    ����I��..........  0
//    �Z�o�G���[........ -1
//*nt
//    �`�F�b�N�����i�[�̈�͂TByte �ȏ゠�鎖�B
//    ����No�� 11 Byte �� NULL ���Ȱ� ����Ă��邱��
//*db
//*ag
//    char* kenno   ����No                        [I]
//    char* chmoji  �`�F�b�N�����i�[�̈�|�C���^  [O]
/******************************************************************************/
int		EditChkmj( kenno,	chmoji )
char	kenno[];
char	chmoji[];
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	int		ret=RTN_OK;

    char   wk[16];
    int    i,len,ken, chk_flg;
    int    amr=0;

    chk_flg = 0;

static char *moji[] = { /* �`�F�b�N�����z�� */
"��","��","��","��","Ƹ","Ͳ","ն","��","��","��","��","´","��","ؽ","��",
"��","��","��","��","��","��","��","��","��","·","п","��","��","��","��",
"��","��","��","Ͻ","Ⱥ","��","��","��","��","��","��","շ","��","��","��",
"��","��","��","��","��","��","��","��","��","��","��","Ѽ","��","��","��",
"��","��","��","��","��","��","ʽ","��","��","Ƽ","��","��","��","��","��",
"��","̶","��","��","��","��","��","��","��","��","��","��","��","��","��",
"��","��","��","��","��","��","��","��","μ","��","��","Ž","��","��","��",
"��","��","��","��","̷","��","��","��","��","��","��","��","��","ʹ","��",
"��","��","��","��","��","Ƕ","��","��","��","��","��","��","ƽ","��","��",
"��","��","��","��","ʼ","��","��","��","Լ","��","��","��","ּ","��","��",
"��","��","��","��","ظ","��","��","̴","��","��","��","��","��","��","��",
"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��",
"��","��","��","��","��","��","��","��","ķ","��","��","��","��","��","��",
"��","��"
};

	strcpy( func_nm, "EditChkmj" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    len = strlen(kenno);

	sprintf( G_msg,"IN kntno[%s] len[%d] ", kenno, len );
	EditCsvMsg( G_msg );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

    //if(len != LEN_KENNO)[
    if(len != 6 ){
        chk_flg=1;
    }
    else{
        for(i=0; i<len; i++){
            if(isdigit(kenno[i]) == 0){ /* �����łȂ� */
                chk_flg=1;
                break;
            }
        }
    }    
    if(chk_flg == 1){
        strcpy(chmoji,"    ");
        return(-1);
    }

    //sprintf( wk, "%-6.6s", &kenno[1] ); /* #01 */
    sprintf( wk, "%-6.6s", &kenno[0] );
    /* #01 memcpy(wk,kenno,7); wk[7]=NULL;  */

    ken = atoi(wk);
    amr = ken % 197;
    strcpy(chmoji,moji[amr]);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �Firai_pr                                                       */
/*  �@�\�T�v  �F�˗����\����printf                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI		*irai;	: �˗����                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		irai_pr( in )
struct		_IRAI		*in;		/* �˗��f�[�^	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	strcpy( func_nm, "irai_pr" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	printf( "�˗��f�[�^{\n" );

	printf( "utkymd    [%s]\n",	in->utkymd );
	printf( "irino     [%s]\n",	in->irino );
	printf( "iriketflg [%s]\n",	in->iriketflg );
	printf( "zssdino   [%d]\n",	in->zssdino );
	printf( "knsgrp    [%s]\n",	in->knsgrp );
	printf( "kmkcd     [%s]\n",	in->kmkcd );
	printf( "irihsmkbn [%s]\n",	in->irihsmkbn );
	printf( "irikbn    [%s]\n",	in->irikbn );
	printf( "ksktkbn   [%s]\n",	in->ksktkbn );
	printf( "sriymd    [%s]\n",	in->sriymd );
	printf( "kntno     [%s]\n",	in->kntno );
	printf( "kntketflg [%s]\n",	in->kntketflg );
	printf( "chkmj     [%s]\n",	in->chkmj );
	printf( "stsrcd    [%s]\n",	in->stsrcd );
	printf( "kmkrs     [%s]\n",	in->kmkrs );
	printf( "oyakmkcd  [%s]\n",	in->oyakmkcd );
	printf( "smpcd     [%s]\n",	in->smpcd );
	printf( "setkmkcd  [%s]\n",	in->setkmkcd );
	printf( "srinycd   [%s]\n",	in->srinycd );
	printf( "seccd     [%s]\n",	in->seccd );
	printf( "skchkflg  [%s]\n",	in->skchkflg );
	printf( "bkfkkbn   [%s]\n",	in->bkfkkbn );
	printf( "ysnlbl    [%s]\n",	in->ysnlbl );
	printf( "skflg     [%s]\n",	in->skflg );
	printf( "tkflg     [%s]\n",	in->tkflg );
	printf( "sjflg     [%s]\n",	in->sjflg );
	printf( "jktkflg   [%s]\n",	in->jktkflg );
	printf( "kjno      [%s]\n",	in->kjno );
	printf( "fkhkknohjkbn[%s]\n",in->fkhkknohjkbn );
	printf( "tbkjno    [%s]\n",	in->tbkjno );
	printf( "tbkjflg   [%s]\n",	in->tbkjflg );
	printf( "htkfkhms  [%s]\n",	in->htkfkhms );
	printf( "tskflg    [%s]\n",	in->tskflg );
	printf( "tktflg    [%s]\n",	in->tktflg );
	printf( "bnckbn    [%s]\n",	in->bnckbn );
	printf( "nbnckbn   [%s]\n",	in->nbnckbn );
	printf( "knskisyymd[%s]\n",	in->knskisyymd );
	printf( "knskryymd [%s]\n",	in->knskryymd );
	printf( "knskrytme [%s]\n",	in->knskrytme );
	printf( "kkhkkflg  [%s]\n",	in->kkhkkflg );
	printf( "kkiriflg  [%s]\n",	in->kkiriflg );
	printf( "kkirilotno[%d]\n",	in->kkirilotno );
	printf( "kktoutkid [%s]\n",	in->kktoutkid );
	printf( "knssu     [%d]\n",	in->knssu );
	printf( "odrssflg  [%s]\n",	in->odrssflg );
	printf( "ytiksbr   [%s]\n",	in->ytiksbr );
	printf( "hhkjkflg  [%s]\n",	in->hhkjkflg );
	printf( "ksndh     [%s]\n",	in->ksndh );
	printf( "trkdh     [%s]\n",	in->trkdh );
	printf( "}\n" );
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/** End of File ***************************************************************/
