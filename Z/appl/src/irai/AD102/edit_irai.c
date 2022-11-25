/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����Fedit_proc.c                                                  */
/*   �T      �v�F�f�[�^�ҏW����                                               */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�o�^����)�Ή�        */
/*  1.04     2006/06/26     INTEC.INC      �����������ړo�^�{����G�ҏW�ǉ�    */
/*  2.01     2006/09/28     INTEC.INC      �W������404�̒ǉ�                  */
/*  2.02     2008/04/24     sekiya         �W������426�̒ǉ�                  */
/*  2.03     2011/09/29     sekiya         �W������790�̒ǉ�                  */
/*  2.04     2013/08/xx     sekiya         �W������590�̒ǉ�                  */
/*  2.05     2015/10/13     sekiya         �W������380,381�̒ǉ�              */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD102.h"

/******************************************************************************/
/*  �� �� ��  �FEditPncIrai                                                 */
/*  �@�\�T�v  �F�o�m�b�˗��f�[�^�ҏW ���@�`�F�b�N                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  Z02SJIR1    *inp;	: PNC�˗����                     */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI		*iri;	: �˗����                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditPncIrai( inp, iri )
struct		Z05SJIR1	*inp;		/* PNC�˗����(S-JIS)	*/
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
	strcpy(func_nm, "EditPncIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 �a�l�k��t�N����
	sprintf( iri->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 �˗����m��
	sprintf( iri->irino,	"00%-3.3s%-6.6s"
		,inp->c_irai_no	,&inp->c_irai_no[5] );
		// DEBUG
	sprintf( G_msg, "irino [%.11s]->[%s]", inp->c_irai_no, iri->irino );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 3 �˗����m�������t���O
	iri->iriketflg[0] = ' ';
	// 4 �˗�����m��
		iri->zssdino	= stcPRM.myp_sedai;

	// 5 �����O���[�v
		// 1.04 			-> EditCommonIrai
	// 6 ���ڃR�[�h
	memcpy( iri->kmkcd,		inp->c_koumoku_cd,sizeof( inp->c_koumoku_cd ));

	// 7 �˗��������敪		-> EditCommonIrai
	// 8 �˗��敪			-> EditCommonIrai
	// 9 �����H���敪		-> EditCommonIrai
	// 10 ������			-> EditCommonIrai

	// 11 ���̂m��
	sprintf( iri->kntno,"00%03.3s%-6.6s"
		,inp->c_kentai_no	,&inp->c_kentai_no[5] );
		// DEBUG
	sprintf( G_msg, "kntno [%.11s]->[%s]", inp->c_kentai_no, iri->kntno );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 12 ���̂m�������t���O
	iri->kntketflg[0] = ' ';

	// ���O�o�͗p�L�[���ڐݒ�
	strcpy( G_utkymd,	iri->utkymd );
	strcpy( G_irino,	iri->irino );
	G_zssdino=iri->zssdino;
	strcpy( G_kmkcd,	iri->kmkcd );
	strcpy( G_kntno,	iri->kntno );

	//----------------------------------------------------	
	// �L�[���ڕҏW��
	//	-> �폜�t���O='1'�Ȃ�Ώ����𔲂���
	//----------------------------------------------------	
	if( inp->c_del_flg[0] == '1' ){
		// WARNING
		sprintf( G_msg, "�˗��폜�f�[�^����M���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_SKIP );
	}

	// 13 �`�F�b�N�����i����ς�K�v�j
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->chkmj, memcpy(buf, inp->c_kentai_ch, 
		sizeof( inp->c_kentai_ch )), sizeof( iri->chkmj ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�`�F�b�N�����z[%s]"
			,iri->chkmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 14 ����ޗ��R�[�h
	memcpy( iri->stsrcd,	inp->c_szairyo_cd,sizeof( inp->c_szairyo_cd ));

	// 15 ���ڗ���
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->kmkrs, memcpy(buf, inp->c_koumoku_rnm, 
		sizeof( inp->c_koumoku_rnm )), sizeof( iri->kmkrs ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���ڗ��́z[%s]"
			,iri->kmkrs );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 16 �e���ڃR�[�h
	memcpy( iri->oyakmkcd,	inp->c_oya_cd,sizeof( inp->c_oya_cd ));
	// 17 �T���v�����O�R�[�h
	memcpy( iri->smpcd,		inp->c_ws_cd,sizeof( inp->c_ws_cd ));
	// 18 �Z�b�g���ڃR�[�h
	memcpy( iri->setkmkcd,	inp->c_set_cd,sizeof( inp->c_set_cd ));
	// 19 �������e�R�[�h
	memcpy( iri->srinycd,	inp->c_naiyo_cd,sizeof( inp->c_naiyo_cd ));
	// 20 �Z�N�V�����R�[�h
	memcpy( iri->seccd,	inp->c_section_cd,sizeof( inp->c_section_cd ));
	// 21 �o�׃`�F�b�N�t���O
	memcpy( iri->skchkflg,	inp->c_outchk_flg,sizeof( inp->c_outchk_flg ));
	// 22 ���敉�׋敪
	memcpy( iri->bkfkkbn,	inp->c_bunkaku_kbn,sizeof( inp->c_bunkaku_kbn ));
	// 23 �D�惌�x��
	memcpy( iri->ysnlbl,	inp->c_yusen_lvl,sizeof( inp->c_yusen_lvl ));
	// 24 �W���t���O  �˗���NO�̖��䂩�画�f
	iri->skflg[0] = '0';
	if(( memcmp( inp->c_irai_no, "012", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "013", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "014", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "020", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "090", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "231", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "232", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "233", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "234", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "235", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "236", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "237", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "238", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "239", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "240", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "241", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "380", 3 ) == 0 )||	// 2.05 ADD
	   ( memcmp( inp->c_irai_no, "381", 3 ) == 0 )||	// 2.05 ADD
	   ( memcmp( inp->c_irai_no, "403", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "404", 3 ) == 0 )||	// 2.01 ADD
	   ( memcmp( inp->c_irai_no, "405", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "412", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "426", 3 ) == 0 )||	// 2.02 ADD
	   ( memcmp( inp->c_irai_no, "434", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "490", 3 ) == 0 )||
	   ( memcmp( inp->c_irai_no, "528", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "590", 3 ) == 0 )||	// 2.04 ADD
	   ( memcmp( inp->c_irai_no, "784", 3 ) == 0 )||	// 2.07 ADD
	   ( memcmp( inp->c_irai_no, "786", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "787", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "788", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "789", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "790", 3 ) == 0 )||	// 2.03 ADD
	   ( memcmp( inp->c_irai_no, "793", 3 ) == 0 )||	// 2.07 ADD
	   ( memcmp( inp->c_irai_no, "795", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "796", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "797", 3 ) == 0 )||	// 2.06 ADD
	   ( memcmp( inp->c_irai_no, "798", 3 ) == 0 )){	// 2.06 ADD
		iri->skflg[0] = '1';
		if( stcPRM.myp_debug == 1 ){
			sprintf( G_msg, "�W���t���O[%3.3s]!!", func_nm, inp->c_irai_no  );
			LogOut( LT_DBG, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
		};
	}

	// 25 �ǉ��t���O	
	memcpy( iri->tkflg,	inp->c_add_flg,sizeof( inp->c_add_flg ));
	// 26 �폜�t���O
	memcpy( iri->sjflg,	inp->c_del_flg,sizeof( inp->c_del_flg ));
	// 27 �����ǉ��t���O
	memcpy( iri->jktkflg,	inp->c_jokenadd_flg,sizeof( inp->c_jokenadd_flg ));

	// 28 ��l�m�n
	memcpy( iri->kjno,	inp->c_base_no,sizeof( inp->c_base_no ));
	if( strncmp( iri->kjno, MYAPP_SPACE10, sizeof( inp->c_base_no )) == 0 ){
		/* ��lNO�����ݒ�̏ꍇ�A�}�X�^����Z�o	*/
		memset( &kj,		'\0', sizeof( struct stcKJNO ));
		strcpy( kj.kmkcd,	iri->kmkcd );
		strcpy( kj.zrcd,	iri->stsrcd );
		memcpy( kj.age,		inp->c_age,		sizeof( inp->c_age ));
		memcpy( kj.agekbn,	inp->c_age_kbn,	sizeof( inp->c_age_kbn ));
		if( GetKjnmst( &kj ) != RTN_OK ){
			sprintf( G_msg,"�Y�������l�}�X�^�f�[�^������܂���B"
				"����CD[%s]�ޗ�CD[%-4s]",
				iri->kmkcd, iri->stsrcd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		strcpy( iri->kjno,	kj.kjno );	
	}

	// 29 ���ו񍐂m�n�\���敪
	memcpy( iri->fkhkknohjkbn,	inp->c_fuka_no,sizeof( inp->c_fuka_no ));

	// 30 ���ʊ�l�m�n
	// 31 ���ʊ�l�t���O

	// 32 ���^���׎���
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->htkfkhms, memcpy(buf, inp->c_hiteke_time, 
		sizeof( inp->c_hiteke_time )), sizeof( iri->htkfkhms ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���^���׎��ԁz[%s]"
			,iri->htkfkhms );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		 // �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(iri->htkfkhms);w_num < sizeof(iri->htkfkhms)-1;w_num+=2 ){
		memcpy( &iri->htkfkhms[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 33 ���̓t���O
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->tskflg, memcpy(buf, inp->c_toseki_flg, 
		sizeof( inp->c_toseki_flg )), sizeof( iri->tskflg ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���̓t���O�z[%s]"
			,iri->tskflg );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 34 �����t���O
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->tktflg, memcpy(buf, inp->c_toketu_flg, 
		sizeof( inp->c_toketu_flg )), sizeof( iri->tktflg ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�����t���O�z[%s]"
			,iri->tktflg );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 33 ���̓t���O
	// 34 �����t���O
	//	  ���R�R�[�h�̓��e�ɂ��㏑������
	memset( buf, '\0', sizeof( buf ));
	memset( buf2, '\0', sizeof( buf2 ));
	cret=sj2euc( buf2, memcpy(buf, inp->c_riyu_cd,
		sizeof( inp->c_riyu_cd)), sizeof( buf2 ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���R�R�[�h�z[%s]"
			,buf2 );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

		// ���̓t���O
	if( strcmp( buf2, "�" ) == 0 || strcmp( buf2, "�" ) == 0 ){
		strcpy( iri->tskflg, buf2 );
	}
		// �����t���O
	if(strcmp(buf2,"�")== 0||strcmp(buf2,"�")==0||strcmp(buf2,"�")==0){
		strcpy( iri->tktflg, buf2 );
	}

	// 35 �����敪
	memcpy( iri->bnckbn,	inp->c_buncyu_kbn,sizeof( inp->c_buncyu_kbn ));
	// 36 �A�����敪
	memcpy( iri->nbnckbn,	inp->c_nbuncyu_kbn,sizeof( inp->c_nbuncyu_kbn ));
	// 37 �����J�n�\���
	strcpy( iri->knskisyymd,INIT_DATE );
	// 38 ���������\���
	strcpy( iri->knskryymd,	INIT_DATE );
	// 39 ���������\�莞��
	strcpy( iri->knskrytme,	INIT_TIME );
	// 40 �ً}�񍐃t���O
	iri->kkhkkflg[0] = '0';
	// 41 �ً}�˗��t���O
	iri->kkiriflg[0] = '0';
	// 42 �ً}�˗����b�g�m��
	iri->kkirilotno = 0;
	// 43 �ً}�Ή���t�h�c
	strcpy( iri->kktoutkid,	" " );
	// 44 ������
	iri->knssu = 0;

	// 45 �I�[�_�쐬�t���O
	// 46 �\���ߔ{��

	// 47 �񍐏󋵃t���O
	strcpy( iri->hhkjkflg,	" " );

	// 48 ���X�V����	CURRENT TIMESTAMP
	// 1.01 ADD	49 �o�^����	CURRENT TIMESTAMP

	//=========================================
	//	CHECK
	//=========================================

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  �� �� ��  �FEditNxtIrai                                                 */
/*  �@�\�T�v  �F�����㊳�҈˗��f�[�^�ҏW                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  Z02SJIR1    *inp;	: PNC�˗����                     */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI		*zok;	: �˗����                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditNxtIrai( iri )
struct	_IRAI	*iri;	/* �˗��f�[�^	*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* ��������	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditNxtIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  �� �� ��  �FEditCommonIrai                                              */
/*  �@�\�T�v  �F���҈˗��f�[�^���ʕҏW���`�F�b�N                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _IRAI		*zok;	: �˗����                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditCommonIrai( iri )
struct		_IRAI		*iri;	// ���҈˗��\����
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	struct	_KMKMST		km;					// 1.04 ADD

	strcpy( func_nm, "EditCommonIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	COMMON EDIT
	//=========================================
	// 5 �����O���[�v
	strcpy( iri->knsgrp, 	" " );
	// 1.04 ADD ����CD+�T���v�����O+����G.���->�R�[�h���Ⴂ�擪�P����
	memset( &km,		'\0', sizeof( struct _KMKMST ));
	strcpy( km.kmkcd,	iri->kmkcd );
	strcpy( km.smpcd,	iri->smpcd );
	strcpy( km.skflg,	iri->skflg );
	if( SelKnsgrp( &km, stcPRM.myp_kjnymd ) == RTN_OK ){
		strcpy( iri->knsgrp,	km.knsgrp );
			// DEBUG
		sprintf( G_msg, "kmkcd[%s]smpcd[%s]skflg[%s] -> knsgrp[%s]"
				, iri->kmkcd, iri->smpcd, iri->skflg, iri->knsgrp );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	} else {
		// �W����z�肵�Ď擾���s�̏ꍇ�́A��ʂōēx�擾������
		if( km.skflg[0] == '1' ){
			strcpy( km.skflg,	"0" );
			if( SelKnsgrp( &km, stcPRM.myp_kjnymd ) == RTN_OK ){
				strcpy( iri->knsgrp,	km.knsgrp );
					// DEBUG
				sprintf( G_msg
					, "����G�Ď擾OK!kmkcd[%s]smpcd[%s]skflg[%s] -> knsgrp[%s]"
					, iri->kmkcd, iri->smpcd, iri->skflg, iri->knsgrp );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__ );
			} else {
				sprintf( G_msg,"��ʏW�����ɊY�����錟���O���[�v������܂���B"
					"����CD[%s]SMPCD[%s]�W��F[%s]",
					iri->kmkcd, iri->smpcd, iri->skflg );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__);
			}
		} else {
			sprintf( G_msg,"�Y�����錟���O���[�v������܂���B"
				"����CD[%s]SMPCD[%s]�W��F[%s]",
				iri->kmkcd, iri->smpcd, iri->skflg );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// 7 �˗��������敪		0:��ʃV�X�e��
	iri->irihsmkbn[0] = '0';
	
	// 8 �˗��敪			A:�ʏ�
	iri->irikbn[0] = 'A';

	// 9 �����H���敪		A:�ʏ�
	iri->ksktkbn[0] = 'A';

	// 10 ������			�V�X�e���Ǘ��}�X�^�D�������
	strcpy( iri->sriymd,	stcPRM.myp_kjnymd );

	// 30 ���ʊ�l�m�n
	// 31 ���ʊ�l�t���O
	strcpy( iri->tbkjno,		" " );
	strcpy( iri->tbkjflg,		" " );

	// 44 ������
	iri->knssu = 1;
	// 45 �I�[�_�쐬�t���O	��:�����l
	iri->odrssflg[0] = ' ';
	// 46 �\���ߔ{��
	iri->ytiksbr[0] = '1';

	//=========================================
	//	CHECK
	//=========================================
	// �Ó����`�F�b�N
	// �T���v�����O�R�[�h�����ݒ�̏ꍇ�̓G���[
	if( strncmp( iri->smpcd, MYAPP_SPACE10, sizeof( iri->smpcd ) - 1 ) == 0 ){
			// ERROR 
		sprintf( G_msg, "�T���v�����O�R�[�h�����ݒ�ł��B[%s]", iri->smpcd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 
		return( RTN_NG );
	}

	// DATE �Ó����`�F�b�N
	// �a�l�k��t��
	if( ( strcmp( iri->utkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, iri->utkymd )) == RTN_NG )){
			// ERROR
		sprintf( G_msg, "�a�l�k��t�� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, iri->utkymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 
		return( RTN_NG );
	}

	// �����J�n�\���
	if( ( strcmp( iri->knskisyymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, iri->knskisyymd )) == RTN_NG )){
			// ERROR --> CONV
		sprintf( G_msg, "�����J�n�\\��� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, iri->knskisyymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// �����l���Z�b�g
		strcpy( iri->knskisyymd, INIT_DATE );
	}

	// ���������\���
	if( ( strcmp( iri->knskryymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, iri->knskryymd )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "���������\\��� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, iri->knskryymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( iri->knskryymd, INIT_DATE );
	}

	// TIME �Ó����`�F�b�N
	// ���������\�莞��
	if( ( strcmp( iri->knskrytme, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, iri->knskrytme )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "���������\\�莞�� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, iri->knskrytme );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( iri->knskrytme, INIT_TIME );
	}

	// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
	if( stcPRM.myp_debug == 1 ){
		irai_pr( iri );
	};
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
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
		sprintf( G_msg,"KJNO SERCH STA keybuf[%s]", keybuf );
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

/******************************************************************************/
/*  �� �� ��  �FEditCsvKanjya                                                 */
/*  �@�\�T�v  �F���ҏ���CSV�`���ł̃e�L�X�g�o��                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �F struct _KANJYA kan;  : ���ҏ��\����                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK             : ����                                    */
/*               RTN_NG             : �G���[                                  */
/******************************************************************************/
int     EditCsvIrai( iri )
struct      _IRAI     *iri;
{
    char    func_nm[30];        /* �֐����� */
    char    w_str[30];
    char    delim[1+1];
    int     ret=RTN_OK;
    int     sz;

    strcpy( func_nm, "EditCsvIrai" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    memset( G_msg,  '\0', sizeof( G_msg ));
    strcpy( delim,  "!" );
    sz=sizeof( G_msg ) - 1;

to_csv( delim, sz,  G_msg, iri->utkymd );
to_csv( delim, sz,  G_msg, iri->irino );
to_csv( delim, sz,  G_msg, iri->iriketflg );
// NUM
memset( w_str , '\0', sizeof( w_str ));
sprintf( w_str, "%d", iri->zssdino );
to_csv( delim, sz,  G_msg, w_str );

to_csv( delim, sz,  G_msg, iri->knsgrp );
to_csv( delim, sz,  G_msg, iri->kmkcd );
to_csv( delim, sz,  G_msg, iri->irihsmkbn );
to_csv( delim, sz,  G_msg, iri->irikbn );
to_csv( delim, sz,  G_msg, iri->ksktkbn );
to_csv( delim, sz,  G_msg, iri->sriymd );
to_csv( delim, sz,  G_msg, iri->kntno );
to_csv( delim, sz,  G_msg, iri->kntketflg );
to_csv( delim, sz,  G_msg, iri->chkmj );
to_csv( delim, sz,  G_msg, iri->stsrcd );
to_csv( delim, sz,  G_msg, iri->kmkrs );
to_csv( delim, sz,  G_msg, iri->oyakmkcd );
to_csv( delim, sz,  G_msg, iri->smpcd );
to_csv( delim, sz,  G_msg, iri->setkmkcd );
to_csv( delim, sz,  G_msg, iri->srinycd );
to_csv( delim, sz,  G_msg, iri->seccd );
to_csv( delim, sz,  G_msg, iri->skchkflg );
to_csv( delim, sz,  G_msg, iri->bkfkkbn );
to_csv( delim, sz,  G_msg, iri->ysnlbl );
to_csv( delim, sz,  G_msg, iri->skflg );
to_csv( delim, sz,  G_msg, iri->tkflg );
to_csv( delim, sz,  G_msg, iri->sjflg );
to_csv( delim, sz,  G_msg, iri->jktkflg );
to_csv( delim, sz,  G_msg, iri->kjno );
to_csv( delim, sz,  G_msg, iri->fkhkknohjkbn );
to_csv( delim, sz,  G_msg, iri->tbkjno );
to_csv( delim, sz,  G_msg, iri->tbkjflg );
to_csv( delim, sz,  G_msg, iri->htkfkhms );
to_csv( delim, sz,  G_msg, iri->tskflg );
to_csv( delim, sz,  G_msg, iri->tktflg );
to_csv( delim, sz,  G_msg, iri->bnckbn );
to_csv( delim, sz,  G_msg, iri->nbnckbn );
to_csv( delim, sz,  G_msg, iri->knskisyymd );
to_csv( delim, sz,  G_msg, iri->knskryymd );
to_csv( delim, sz,  G_msg, iri->knskrytme );
to_csv( delim, sz,  G_msg, iri->kkhkkflg );
to_csv( delim, sz,  G_msg, iri->kkiriflg );
// NUM
memset( w_str , '\0', sizeof( w_str ));
sprintf( w_str, "%d", iri->kkirilotno );
to_csv( delim, sz,  G_msg, w_str );

to_csv( delim, sz,  G_msg, iri->kktoutkid );
// NUM
memset( w_str , '\0', sizeof( w_str ));
sprintf( w_str, "%d", iri->knssu );
to_csv( delim, sz,  G_msg, w_str );

to_csv( delim, sz,  G_msg, iri->odrssflg );
to_csv( delim, sz,  G_msg, iri->ytiksbr );
to_csv( delim, sz,  G_msg, iri->hhkjkflg );
to_csv( delim, sz,  G_msg, iri->ksndh );
to_csv( delim, sz,  G_msg, iri->trkdh );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}
/******************************************************************************/
/*  �� �� ��  �FEditCsvMsg                                                    */
/*  �@�\�T�v  �F���O�o�̓��b�Z�[�WCSV�ҏW                                     */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	msg[];	    : ���b�Z�[�W���e                          */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK			    : ����I��                                */
/*               �ȊO				: ���s                                    */
/******************************************************************************/
int		EditCsvMsg( msg )
char		msg[];	
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];            /* �֐�����     */
	int		ret=RTN_OK;
	char	buf[MYAPP_LEN_MSG+1];
	char	w_str[10+1];

 	/* ��������     */
 	strcpy( func_nm, "EditCsvMsg" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( buf,	'\0', sizeof( buf ));
	memset( w_str,	'\0', sizeof( w_str ));
	if( G_line == 0 ){
		memcpy( w_str,	MYAPP_SPACE10,	5 );
	} else {
		sprintf( w_str, "%5d", G_line );
	}
	sprintf( buf,	"%s!%s!%s!%s!"
					"%s!%s!%s!%s!"
					"%s"
		// 1 ��ʁE2�t�@�C�����E3�sNo�E4�����N����
		// 5 BML��t���E6�˗�����NO)�E7�˗���NO�E8���ڃR�[�h
		// 9 �ڍ�
		, MYAPP_APPLNAME, G_fnm, w_str, stcPRM.myp_kjnymd
		, G_utkymd, G_kntno, G_irino, G_kmkcd
		, msg
	);
	strcpy( msg, buf );

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
	printf( "iriketflg [%s]\n",in->iriketflg );
	printf( "zssdino   [%d]\n",	in->zssdino );
	printf( "knsgrp    [%s]\n",	in->knsgrp );
	printf( "kmkcd     [%s]\n",	in->kmkcd );
	printf( "irihsmkbn [%s]\n",in->irihsmkbn );
	printf( "irikbn    [%s]\n",	in->irikbn );
	printf( "ksktkbn   [%s]\n",	in->ksktkbn );
	printf( "sriymd    [%s]\n",	in->sriymd );
	printf( "kntno     [%s]\n",	in->kntno );
	printf( "kntketflg [%s]\n",in->kntketflg );
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
	printf( "kjno      [%s]\n",		in->kjno );
	printf( "fkhkknohjkbn[%s]\n",	in->fkhkknohjkbn );
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
