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
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� */
/*  2.01     2006/10/03     INTEC.INC      ���l�̍��ڂ̑Ó����`�F�b�N�ǉ�     */
/*  2.02     2007/01/31     INTEC.INC      ���ґ������ڂ̐��l�`�F�b�N�ǉ�     */
/*  2.03     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή�*/
/*                                         ��������No�W�J�s��C��           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD103.h"

/******************************************************************************/
/*  �� �� ��  �FEditPncKanjya                                                 */
/*  �@�\�T�v  �F�o�m�b�����f�[�^�ҏW ���@�`�F�b�N                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  Z02SJIR1    *inp;	: PNC�˗����                     */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA		*zok;	: ���ҏ��                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditPncKanjya( inp, zok )
struct		Z02SJIR1	*inp;		/* PNC�˗����(S-JIS)	*/
struct		_KANJYA		*zok;		/* ���ҏ��\����		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* ��������	*/
	strcpy(func_nm, "EditPncKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 �a�l�k��t�N����
	sprintf( zok->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 �˗����m��
	sprintf( zok->irino,	"00%-3.3s%-6.6s"
		,inp->c_irai_no	,&inp->c_irai_no[5] );

	// 3 �˗����m�������t���O
	zok->iriketflg[0] = ' ';
	// 4 ��������m��
	zok->zssdino	= stcPRM.myp_sedai;

	// ���O�o�͗p�L�[���ڐݒ�
	strcpy( G_utkymd,	zok->utkymd );
	strcpy( G_irino,	zok->irino );
	G_zssdino=zok->zssdino;

	//----------------------------------------------------	
	// �L�[���ڕҏW��
	//	-> �폜�t���O='1'�Ȃ�Ώ����𔲂���
	//----------------------------------------------------	
	if( inp->c_zokdel_flg[0] == '1' ){
		// WARNING
		sprintf( G_msg, "�����폜�f�[�^����M���܂����i�f�[�^�ǂݔ�΂��j�B" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_SKIP );
	}

	//----------------------------------------------------	
	// �L�[���ڕҏW��
	//----------------------------------------------------	
/*  2.03     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� -->*/
	if( inp->c_zokupd_flg[0] == '1' ){						/* �C���t���O = '1'�Ȃ瑮���C�� */
		if(( ret = SelKanjyaZssdinoMax( zok )) == RTN_OK ){	/* ���ɓW�J�ς݂̑�����񂩂��`�F�b�N */
			;												/* �W�J�ς݂Ȃ牽�����Ȃ��B��������No��"0"�Œ� */
		}
		else{												/* �W�J���Ă��Ȃ��ꍇ */
															/* ���������z���̏C���m�� */
			zok->zssdino=100;								/* ��������No��"100"�Œ� */
			// WARNING
			sprintf( G_msg, 
				"�����C���Ώۃf�[�^�擾�G���[�̂��ߑ�������NO��[%d]��"
				"�u�����������܂��B", zok->zssdino );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
	}
//	-> �C���t���O='1'�Ȃ��MAX(��������m��)+1 �擾
// 	if( inp->c_zokupd_flg[0] == '1' ){
// 		if(( ret = SelKanjyaZssdinoMax( zok )) == RTN_OK ){
// 			// COUNT UP	
// 			zok->zssdino++;
// 		} else {
// 			// ��������NO�u��
// 			zok->zssdino=100;
// 
// 			// WARNING
// 			sprintf( G_msg, 
// 				"�����C���Ώۃf�[�^�擾�G���[�̂��ߑ�������NO��[%d]��"
// 				"�u�����������܂��B", zok->zssdino );
// 			EditCsvMsg( G_msg );
// 			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
// 		}
// 	}
/*  2.03     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� <--*/	
	// 5 �{�݃R�[�h
	memcpy( zok->sstcd,		inp->c_siset_cd,sizeof( inp->c_siset_cd ));
	// 6 �T�u�{�݃R�[�h
	memcpy( zok->subsstcd,	inp->c_subsiset_cd,sizeof( inp->c_subsiset_cd ));
	// 7 �J�[�h�敪1
	memcpy( zok->cdkbn1,	inp->c_card1_kbn,sizeof( inp->c_card1_kbn ));
	// 8 �J�[�h�敪2
	memcpy( zok->cdkbn2,	inp->c_card2_kbn,sizeof( inp->c_card2_kbn ));

	// 9 �˗����L�[
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->irimkey, memcpy(buf, inp->c_iraimoto_key, 
		sizeof( inp->c_iraimoto_key )), sizeof( zok->irimkey ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�˗����L�[�z[%s]"
			,zok->irimkey );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 10 �f�ÉȃR�[�h	
	memcpy( zok->srkcd,		inp->c_ka_cd,	sizeof( inp->c_ka_cd ));

	// 11 �f�ÉȖ�
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->srknm, memcpy(buf, inp->c_ka_nm, 
		sizeof( inp->c_ka_nm )), sizeof( zok->srknm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�f�ÉȖ��z[%s]"
			,zok->srknm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 12 �S����R�[�h	
	memcpy( zok->tticd,		inp->c_dr_cd,	sizeof( inp->c_dr_cd ));

	// 13 �S���㖼
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->ttinm, memcpy(buf, inp->c_dr_nm, 
		sizeof( inp->c_dr_nm )), sizeof( zok->ttinm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�S���㖼�z[%s]"
			,zok->ttinm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 14 �厡��R�[�h		zok->gpcd
	// 15 �厡�㖼			zok->gpnm
	// 16 �Љ��R�[�h		zok->skicd
	// 17 �Љ�㖼			zok->skinm

	// 18 �J���e�m��
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->krtno, memcpy(buf, inp->c_karte_no, 
		sizeof( inp->c_karte_no )), sizeof( zok->krtno ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�J���e�m���z[%s]"
			,zok->krtno );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 19 ���҂h�c
	memcpy( zok->knjid,		inp->c_kanja_id,sizeof( inp->c_kanja_id ));

	// 20 ���Җ��i�J�i�j
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->knjnmn, memcpy(buf, inp->c_kanja_nm, 
		sizeof( inp->c_kanja_nm )), sizeof( zok->knjnmn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���Җ��i�J�i�j�z[%s]"
			,zok->knjnmn );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 21 ���Җ��i�����j
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->knjnmk, memcpy(buf, inp->c_kanja_knm, 
		sizeof( inp->c_kanja_knm )), sizeof( zok->knjnmk ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���Җ��i�����j�z[%s]"
			,zok->knjnmk );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->knjnmk);w_num < sizeof(zok->knjnmk)-1;w_num+=2 ){
		memcpy( &zok->knjnmk[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 22 ���Җ��L�[
	memset( buf,	0x00,	sizeof( buf ));

	//2007.01.24 KRTNO Input
	//printf("[Kim Input] --- mae --- kanzyameiki- : %s\n", buf);

	NameKeyMake( buf, inp->c_kanja_nm, sizeof( inp->c_kanja_nm ));

	//==> 2007.01.24 KRTNo Input
	if(strcmp(buf, " ") == 0)
	{
		memcpy(buf, inp->c_karte_no,sizeof(inp->c_karte_no));
		//printf("[Kim Input] --- ato --- kanzyameiki- : %s\n", buf);
	}
	//<== 2007.01.24 KRTNO Input

	cret=sj2euc( zok->knjnmkey, buf, sizeof( zok->knjnmkey ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���Җ��L�[�z[%s]"
			,zok->knjnmkey );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// DEBUG
	sprintf( G_msg, "NameKeyMake [%s]->[%s]", zok->knjnmn, zok->knjnmkey);
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 23 �g��	
	memcpy( zok->sc,		inp->c_tall,	sizeof( inp->c_tall ));

		// 2.02 ADD STA	�g���A�̏d�̐��l�`�F�b�N���s���i�ޗ���킸�j
	if( memcmp( inp->c_tall, MYAPP_SPACE10, sizeof( inp->c_tall )) != 0 ){
		//�@�Ó����`�F�b�N
		if( isCorrectChar( zok->sc ) != RTN_OK ) {
			// ERROR
			sprintf( G_msg, "�g���G���[�̂��߃X�y�[�X�ɒu��[%5.5s]" , inp->c_tall );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// NULL��ݒ�
			memset( zok->sc, 0x00, sizeof( zok->sc ));
		}
	}
	// 2.02 ADD END

	// 24 �̏d
	memcpy( zok->tj,		inp->c_weight,	sizeof( inp->c_weight ));

		// 2.02 ADD STA	�g���A�̏d�̐��l�`�F�b�N���s���i�ޗ���킸�j
	if( memcmp( inp->c_weight, MYAPP_SPACE10, sizeof( inp->c_weight )) != 0 ){
		//�@�Ó����`�F�b�N
		if( isCorrectChar( zok->tj ) != RTN_OK ) {
			// ERROR
			sprintf( G_msg, "�̏d�G���[�̂��߃X�y�[�X�ɒu��[%5.5s]" , inp->c_weight );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// NULL��ݒ�
			memset( zok->tj, 0x00, sizeof( zok->tj ));
		}
	}
	// 2.02 ADD END

	// 25 �̏d�敪
	memcpy( zok->tjtni,		inp->c_weight_kbn,sizeof( inp->c_weight_kbn));
	// 26 ���ʋ敪
	memcpy( zok->sbtkbn,	inp->c_sex,	sizeof( inp->c_sex ));
	// 27 ���N����
	memcpy( zok->birthday,	inp->c_birth_ymd,	sizeof( inp->c_birth_ymd ));
	// 28 ���N�����敪
	memcpy( zok->birthdaykbn,inp->c_birth_kbn,sizeof( inp->c_birth_kbn ));
	// 29 �N��
	memcpy( zok->age,		inp->c_age,	sizeof( inp->c_age ));
	// 30 �N��敪
	memcpy( zok->agekbn,	inp->c_age_kbn,sizeof( inp->c_age_kbn ));
	// 31 �a���R�[�h
	memcpy( zok->btcd,		inp->c_byoto_cd,sizeof( inp->c_byoto_cd ));

	// 32 �a����
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->btnm, memcpy(buf, inp->c_byoto_nm, 
		sizeof( inp->c_byoto_nm )), sizeof( zok->btnm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�a�����z[%s]"
			,zok->btnm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 33 ��t�R�����g1	
	memcpy( zok->utkcmtcd1,	inp->c_ukecmt1_cd,sizeof( inp->c_ukecmt1_cd));
	// 34 ��t�R�����g2
	memcpy( zok->utkcmtcd2,	inp->c_ukecmt2_cd,sizeof( inp->c_ukecmt2_cd));
	// 35 ��t�R�����g3
	memcpy( zok->utkcmtcd3,	inp->c_ukecmt3_cd,sizeof( inp->c_ukecmt3_cd));

	// 36 ��t�R�����g�t���[1
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->utkcmtfr1, memcpy(buf, inp->c_ukecmt1_cmt, 
		sizeof( inp->c_ukecmt1_cmt )), sizeof( zok->utkcmtfr1 ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y��t�R�����g�t���[1�z[%s]"
			,zok->utkcmtfr1 );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 37 ��t�R�����g�t���[2
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->utkcmtfr2, memcpy(buf, inp->c_ukecmt2_cmt, 
		sizeof( inp->c_ukecmt2_cmt )), sizeof( zok->utkcmtfr2 ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y��t�R�����g�t���[2�z[%s]"
			,zok->utkcmtfr2 );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 38 ��t�R�����g�t���[�t���O	zok->utkcmtfrflg
	strcpy( zok->utkcmtfrflg, "0" );
	// 39 ���@�O���敪
	memcpy( zok->ngkbn,		inp->c_ng_kbn,	sizeof( inp->c_ng_kbn ));
	// 40 �D�P�T��
	memcpy( zok->nsssu,		inp->c_ninsin_cnt,sizeof( inp->c_ninsin_cnt ));
	// 41 �ی��R�[�h
	memcpy( zok->hkncd,		inp->c_hoken_cd,sizeof( inp->c_hoken_cd ));
	// 42 ���̑��{��		zok->ktshsu
	// 43 �@���˗���
	strcpy( zok->iniriymd,	INIT_DATE );
	// 44 �����C���t���O
	memcpy( zok->zssflg,	inp->c_zokupd_flg,sizeof( inp->c_zokupd_flg ));
	// 45 �ً}�˗��t���O
		// 	  ���R�R�[�h���画��
	memcpy( zok->kkiriflg,	inp->c_kinkyu_flg,sizeof( inp->c_kinkyu_flg ));
	// 46 �񌟍��敪
	memcpy( zok->hknskbn,	inp->c_hikensa_kbn,sizeof( inp->c_hikensa_kbn ));
	// 47 ��t�敪
	memcpy( zok->utkkbn,	inp->c_uketuke_kbn,sizeof( inp->c_uketuke_kbn ));
	// 48 �m�d�敪
	memcpy( zok->nekbn,		inp->c_ne_kbn,	sizeof( inp->c_ne_kbn ));
	// 49 �@�������敪		zok->inknskbn
	// 50 ��t��ԋ敪 		zok->utkjkkbn
	// 51 �����t���O	
	strcpy( zok->krflg,	"0" );
	// 52 �e�c��񍐃t���O
	memcpy( zok->fdhhkkflg,	inp->c_hifd_flg,sizeof( inp->c_hifd_flg ));

	// 53 ��t����
	if( strncmp( inp->c_uke_time, MYAPP_SPACE10, 4 ) == 0 ){
		strcpy( zok->utkdh,	INIT_TIME );
	} else {
		sprintf( zok->utkdh,	"%.2s:%.2s:00",
			inp->c_uke_time,	&inp->c_uke_time[2] );
	}

	// 54 ���a�l�k��t��
	if( strncmp( inp->c_obmluke_ymd, MYAPP_SPACE10, 8 ) == 0 ){
		strcpy( zok->mutkymd,	INIT_DATE );
	} else {
		sprintf( zok->mutkymd,	"%.4s-%.2s-%.2s", inp->c_obmluke_ymd,	
			&inp->c_obmluke_ymd[4],&inp->c_obmluke_ymd[6] );
	}

	// 55 ���˗����m��
	memcpy( zok->mirino,	inp->c_oirai_no,sizeof( inp->c_oirai_no ));
	// 56 �������{���{�R�[�h  knsjslbcd1
	// 57 �������{���{�R�[�h  knsjslbcd2
	// 58 �������{���{�R�[�h  knsjslbcd3
	// 59 �������{���{�R�[�h  knsjslbcd4

	// 60 �������񍐃t���O	
		// �c�Ə��}�X�^���ҏW -> PNC�ł͋󔒂Ƃ���
	//cret=GetEigmst( zok->ecd, zok->shcd,	stcPRM.myp_kjnymd, zok->ymhkkflg );

	// 61 �񍐊�]����
	strcpy( zok->hkkkbdh,	INIT_TIME );

	// 62 �c�Ə��R�[�h
	memcpy( zok->ecd,inp->c_eigyo_cd,	sizeof( inp->c_eigyo_cd ));
	// 63 �W�z�R�[�h
	memcpy( zok->shcd,inp->c_syuhai_cd,	sizeof( inp->c_syuhai_cd ));

	// 64 �{�ݖ���������
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstssnmj, memcpy(buf, inp->c_siset_knm, 
		sizeof( inp->c_siset_knm )), sizeof( zok->sstssnmj ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�{�ݖ��������́z[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->sstssnmj);w_num < sizeof(zok->sstssnmj)-1;w_num+=2 ){
		memcpy( &zok->sstssnmj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 65 �{�ݖ��������́i�J�i�j
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstssnmn, memcpy(buf, inp->c_siset_nm, 
		sizeof( inp->c_siset_nm )), sizeof( zok->sstssnmn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�{�ݖ��������́i�J�i�j�z"
			"[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 66 �{�ݖ�����
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstrsj, memcpy(buf, inp->c_sisetr_knm, 
		sizeof( inp->c_sisetr_knm )), sizeof( zok->sstrsj ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�{�ݖ����́z[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->sstrsj);w_num < sizeof(zok->sstrsj)-1;w_num+=2 ){
		memcpy( &zok->sstrsj[w_num], MYAPP_KJSPACE10, 2 );
	}
		// ALL �S�p�X�y�[�X�̏ꍇ�A�������̂��ҏW
	if( strcmp( zok->sstrsj, MYAPP_KJSPACE10 ) == 0 ){
		memcpy( zok->sstrsj, zok->sstssnmj, sizeof( zok->sstrsj ) - 1 );
	}

	// 67 �{�ݖ����́i�J�i�j
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstrsn, memcpy(buf, inp->c_sisetr_nm, 
		sizeof( inp->c_sisetr_nm )), sizeof( zok->sstrsn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y �{�ݖ����́i�J�i�j�z"
			"[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 68 �{�ݎ��
	memcpy( zok->sstsbt,inp->c_siset_kbn,	sizeof( inp->c_siset_kbn ));
	// 69 ����{�݃t���O
	memcpy( zok->ttsstflg,inp->c_tokutei_flg,sizeof( inp->c_tokutei_flg));

	// 70 ���R�R�[�h
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->rucd, memcpy(buf, inp->c_riyu_cd, 
		sizeof( inp->c_riyu_cd )), sizeof( zok->rucd ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y���R�R�[�h�z[%s]"
			,zok->rucd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
	// 45 �ً}�˗��t���O
	if( zok->rucd[0] == 'L' ){
		 zok->kkiriflg[0] = '1';
	}
	// 71 �˗����ڐ�	
	if( memcmp( inp->c_kmax, MYAPP_SPACE10, sizeof( inp->c_kmax )) == 0 ){
		zok->irikmksu = 0;
	} else {
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_kmax,	sizeof( inp->c_kmax ));
		zok->irikmksu = atoi( w_str );
	}

	// 72 �a���y�я���		zok->bmskn
	// 73 �˗����͎��		zok->irinrsbt
	// 74 �˗��������敪	0:��ʔ��� 1:�T�e���C�g����
	strcpy( zok->irihsmkbn,	"0" );
	// 75 ���ʒ��ӎ{�݃t���Ozok->caresstflg
	// 76 �����g���t���O	0:�f�t�H���g 1:��񂠂�
	strcpy( zok->tktyflg,	"0" );
	// 77 AUTO-P���̂m��	zok->apkntino
	// 78 �f�f�� 			zok->sdnm

/* 2.01 ADD STA */
	// �̎�N���� �̎掞�� �Ó����`�F�b�N
	if( memcmp( inp->c_saisyu_ymd, MYAPP_SPACE10, sizeof(inp->c_saisyu_ymd) ) != 0 ){
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_saisyu_ymd,	sizeof( inp->c_saisyu_ymd ));
		if( ValidDate( VALDATE_DATE, w_str ) == RTN_NG ){
				// ERROR --> CONV
			sprintf( G_msg, "�̎�N���� �Ó����G���[�̂��ߏ����l�u��[%s]"
				, w_str );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
				// �����l���Z�b�g
			memcpy( inp->c_saisyu_ymd, MYAPP_SPACE10, sizeof(inp->c_saisyu_ymd));
		}
	}
	// �̎掞��
	if( memcmp( inp->c_saisyu_time, MYAPP_SPACE10, sizeof(inp->c_saisyu_time) ) != 0 ){
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_saisyu_time,	sizeof( inp->c_saisyu_time ));
		strcat( w_str, "00" );
		if( ValidDate( VALDATE_TIME, w_str ) == RTN_NG ){
				// ERROR --> CONV
			sprintf( G_msg, "�̎掞�� �Ó����G���[�̂��ߏ����l�u��[%4.4s]", w_str );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// �����l���Z�b�g
			memcpy( inp->c_saisyu_time, MYAPP_SPACE10, sizeof(inp->c_saisyu_time));
		}
	}
/* 2.01 ADD END */

	// 79 ���l�P
		/* 3byte �ޗ��R�[�h */
		/* 8byte �̎�N���� */
		/* 4byte �̎掞�� */
	sprintf( zok->bko1, "%-3.3s!%-8.8s!%-4.4s", 
		inp->c_zairyo01_cd, inp->c_saisyu_ymd, inp->c_saisyu_time );

	// 80 ���l�Q 
		/* 4byte �~�A����	*/
		/* 1byte �~�A���ԒP�� */
		/* 5byte �~�A��		*/
		/* 1byte �~�A�ʒP��	*/
	sprintf( zok->bko2, "%-4.4s!%-1.1s!%-5.5s!%-1.1s", 
		inp->c_nyotime,	inp->c_nyotime_kbn,
		inp->c_nyoryo,		inp->c_nyoryo_kbn );
		
	// 81 ���l�R
	// 82 �����o�^����
	strcpy( zok->zstrdh,	INIT_TIMESTAMP );
	// 83 �����C������
	strcpy( zok->zsssdh,	INIT_TIMESTAMP );
	// 84 �T�e���C�g�������C������
	strcpy( zok->stlzsssdh,	INIT_TIMESTAMP );
	// 85 �T�e���C�g�������C���[��IP
	// 86 �T�e���C�g�������C�����͎�
	// 87 ���X�V����	CURRENT TIMESTAMP
	// 1.01 ADD	88 �e�{�݃R�[�h
	strcpy( zok->oyasstcd,	zok->sstcd );
	// 1.01 ADD	89 �o�^����	CURRENT TIMESTAMP

	//=========================================
	//	CHECK
	//=========================================
	// �ޗ����~�A�ʂ̏ꍇ�A�����������[�j���O�`�F�b�N����
	if(( strlen( stcPRM.myp_zairyo ) != 0 )
	 &&( memcmp( stcPRM.myp_zairyo, inp->c_zairyo01_cd, 3 ) == 0 )){
		// �g��	c_tall
		if( memcmp( inp->c_tall, MYAPP_SPACE10, sizeof( inp->c_tall )) == 0 ){
			// WARNING
			sprintf( G_msg, "�~�A �g���G���[[%.5s]" , inp->c_tall );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		} else {
			//�@�Ó����`�F�b�N
			memset( buf, 	0x00, sizeof( w_str ));
			memset( w_str,	0x00, sizeof( w_str ));
			memcpy( buf,	inp->c_tall, sizeof( inp->c_tall ));
			strncpy( w_str,	buf,	strcspn( buf, "." ));
			w_num = atoi( w_str );
			if(( w_num < 1 ) || ( w_num > 250 )){
				// WARNING
				sprintf( G_msg, "�~�A �g���G���[[%.5s]", inp->c_tall );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
											__FILE__, __LINE__);
			}
		}
		// �̏d c_weight
		if( memcmp( inp->c_weight, MYAPP_SPACE10
					, sizeof( inp->c_weight )) == 0 ){
			// WARNING
			sprintf( G_msg, "�~�A �̏d�G���[[%.5s]\n" , inp->c_weight );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		} else {
			//�@�Ó����`�F�b�N
			memset( buf, 	0x00, sizeof( w_str ));
			memset( w_str,	0x00, sizeof( w_str ));
			memcpy( buf,	inp->c_weight, sizeof( inp->c_weight ));
			strncpy( w_str,	buf,	strcspn( buf, "." ));
			w_num = atoi( w_str );
			if( w_num < 1 ){
				// WARNING
				sprintf( G_msg, "�~�A �̏d�G���[[%.5s]", inp->c_weight );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
												__FILE__, __LINE__);
			}
		}
		// �~�A����	c_nyotime
		if( memcmp( inp->c_nyotime, MYAPP_SPACE10
					, sizeof( inp->c_nyotime )) == 0 ){
			// WARNING
			sprintf( G_msg, "�~�A �~�A���ԃG���[[%.4s]" ,inp->c_nyotime );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		// �~�A��	c_nyoryo
		if( memcmp( inp->c_nyoryo, MYAPP_SPACE10
				, sizeof( inp->c_nyoryo )) == 0 ){
			// WARNING
			sprintf( G_msg, "�~�A �~�A�ʃG���[[%.5s]" ,inp->c_nyoryo );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  �� �� ��  �FEditNxtKanjya                                                 */
/*  �@�\�T�v  �F�����㊳�ґ����f�[�^�ҏW                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  Z02SJIR1    *inp;	: PNC�˗����                     */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA		*zok;	: ���ҏ��                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditNxtKanjya( zok )
struct	_KANJYA	*zok;	/* �����f�[�^	*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* ��������	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditNxtKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  �� �� ��  �FEditCommonKanjya                                              */
/*  �@�\�T�v  �F���ґ����f�[�^���ʕҏW���`�F�b�N                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA		*zok;	: ���ҏ��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditCommonKanjya( zok )
struct		_KANJYA		*zok;	// ���ґ����\����
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;

	strcpy( func_nm, "EditCommonKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	CHECK
	//=========================================
	// DATE �Ó����`�F�b�N
	// �a�l�k��t��
	if( ( strcmp( zok->utkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->utkymd )) == RTN_NG )){
			// ERROR
		sprintf( G_msg, "�a�l�k��t�� �Ó����G���[[%s]" , zok->utkymd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 
		return( RTN_NG );
	}

	// �@���˗���		���敪���������ߐ����O��Ƃ���
	if( ( strcmp( zok->iniriymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->iniriymd )) == RTN_NG )){
			// ERROR --> CONV
		sprintf( G_msg, "�@���˗��� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, zok->iniriymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// �����l���Z�b�g
		strcpy( zok->iniriymd, INIT_DATE );
	}

	// ���a�l�k��t��
	if( ( strcmp( zok->mutkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->mutkymd )) == RTN_NG )){
			// ERROR --> CONV
		sprintf( G_msg, "���a�l�k��t�� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, zok->mutkymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// �����l���Z�b�g
		strcpy( zok->mutkymd, INIT_DATE );
	}

	// ���N����		��CHAR�^�̂��ߏ����l�u���͍s��Ȃ�
	if( strncmp( zok->birthday, MYAPP_SPACE10, strlen(zok->birthday) ) != 0 ){
		// ����ϊ�
		memset( w_str,	'\0',	sizeof( w_str ));
		strcpy( buf, zok->birthday );
		wa2ymd( w_str, zok->birthdaykbn, buf );
	 	if(( ret = ValidDate( VALDATE_DATE, w_str )) == RTN_NG ){
				// WARNING
			sprintf( G_msg, "���N���� �Ó����G���[[%s]", zok->birthday );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// TIME �Ó����`�F�b�N
	// ��t����
	if( ( strcmp( zok->utkdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->utkdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "��t���� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, zok->utkdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( zok->utkdh, INIT_TIME );
	}
	// �񍐊�]����
	if( ( strcmp( zok->hkkkbdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->hkkkbdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "�񍐊�]���� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, zok->hkkkbdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( zok->hkkkbdh, INIT_TIME );
	}

	// TIMESTAMP �Ó����`�F�b�N
	// �����o�^����
	if( ( strcmp( zok->zstrdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zstrdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "�����o�^���� �Ó����G���[�̂��ߏ����l�u��[%s]"
			, zok->zstrdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( zok->zstrdh, INIT_TIMESTAMP );
	}
	// �����C������
	if( ( strcmp( zok->zsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "�����C������ �Ó����G���[�̂��ߏ����l�u��[%s]"
			, zok->zsssdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( zok->zsssdh, INIT_TIMESTAMP );
	}
	// �T�e���C�g�������C������
	if( ( strcmp( zok->stlzsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->stlzsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "�T�e���C�g�������C������ �Ó����G���[�̂���"
			"�����l�u��[%s]"
			, zok->stlzsssdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// �����l���Z�b�g
		strcpy( zok->stlzsssdh, INIT_TIMESTAMP );
	}

	// �Ó����`�F�b�N
		// �N��
	if( strncmp( zok->age, MYAPP_SPACE10, sizeof( zok->age )) != 0 ){
		if( zok->agekbn[0] == 'Y' ){
			w_num = atoi( zok->age );
			if( w_num > 150 ){
				// WARNING
				sprintf( G_msg, "�N�� �Ó����G���[[%s]" , zok->age );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__);
			}
		}
	}
	//	�N��敪
	if(   ( strcmp( zok->agekbn, AGEKBN_YEAR  ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_MONTH ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_WEEK  ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_DAY   ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_UNKNOWN ) != 0 )){
			// WARNING
			sprintf( G_msg, "�N��敪�G���[[%s]" , zok->agekbn );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// �����l���Z�b�g
			strcpy( zok->agekbn, AGEKBN_UNKNOWN );
		}
	//	���ʋ敪
	if(   ( strcmp( zok->sbtkbn, SEX_MALE   ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_FEMALE ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_UNKNOWN ) != 0 )){
			// WARNING
			sprintf( G_msg, "���ʋ敪�G���[[%s]", zok->sbtkbn );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// �����l���Z�b�g
			strcpy( zok->sbtkbn, SEX_UNKNOWN );
	}

	// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
	if( stcPRM.myp_debug == 1 ){
		zoku_pr( zok );
	};
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FNameKeyMake                                                   */
/*  �@�\�T�v  �F���Җ��L�[�쐬                                                */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	kan_name[];	: S-JIS ���҃J�i����                      */
/*   ��Q���� �Fint		len;		: S-JIS ���҃J�i����length                */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fchar	name_key[];	: S-JIS ���Җ��L�[                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		NameKeyMake( name_key, kan_name, len )
char		name_key[];		/*	[O]	���Җ��L�[	*/
char		kan_name[];		/*	[I]	���Җ�		*/
int			len;			/*	[I]	���Җ�length	*/
{
	int		i,j;
	unsigned char	name[61];
	unsigned char	keyj[61];
	char	func_nm[MYAPP_LEN_FNCNM+1];

	strcpy( func_nm,	"NameKeyMake" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( keyj, 0x00, sizeof( keyj ));
	strncpy( name, kan_name, len );
	j = 0;
	for  (i=0;i<len;i++) {
		if( isdigit( name[i] )){
			;
		} else {
			keyj[j]  =  name[i];
			j++;
		}
	}

	strcpy( name_key, keyj );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FGetEigmst                                                     */
/*  �@�\�T�v  �F�c�Ə��}�X�^���擾                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar   eigyo_cd[]; 		: �c�Ə��R�[�h                        */
/*   ��Q���� �Fchar   ymd[]; 			: �Ώۓ�(YYYY/MM/DD)                  */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fchar   kbn[]; 			: �����񍐋敪                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/*	���@����  �F���֐���R1��INSERT�O�ɌĂ΂�TRANSACTION�ɉe������������       */
/*			  �FCOMMIT������                                                */
/******************************************************************************/
int		GetEigmst( eigyo_cd, syuhai_cd, ymd, kbn )
char		eigyo_cd[];				/* �c�Ə�����	*/
char		syuhai_cd[];			/* �W�z����		*/
char		ymd[];					/* ���		*/
char		kbn[];					/* �����񍐋敪	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];			/* �֐�����	*/
	int		ret;
	int		pos;
static	int	init_flg = 0;			/* �Ƽ���׸�	*/
static	struct	_EIGMST sv_m02[MYAPP_MAX_EIGMST];/* �c�Ə�Ͻ�(�ۑ��p)	*/

	/* ��������	*/
	strcpy( func_nm, "EigmstGet" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �c�Ə�Ͻ��̊l��	*/
	if( init_flg == 0 ){
		/* �c�Ə�Ͻ������ر	*/
		memset( sv_m02, '\0', sizeof( sv_m02 ));
		init_flg = 1;
	}

	for( pos = 0; pos < MYAPP_MAX_EIGMST
		&& strlen(  sv_m02[pos].ecd ) != 0; ++pos ){
		if( strcmp( sv_m02[pos].ecd, eigyo_cd ) == 0 ){
			// �W�z�R�[�h�J�n���I�������f
			if(( strcmp( syuhai_cd, sv_m02[pos].shcdfr ) >= 0 )
			 &&( strcmp( syuhai_cd, sv_m02[pos].shcdto ) <= 0 )
			 &&( strcmp( ymd, sv_m02[pos].kaiymd ) >= 0 )
			 &&( strcmp( ymd, sv_m02[pos].haiymd ) <= 0 )){
				strcpy( kbn, sv_m02[pos].yjhkkbn );
				return( RTN_OK );
			}
		}
	}
	if( pos >= MYAPP_MAX_EIGMST ){
		pos = MYAPP_MAX_EIGMST - 1;
	}
	// DEBUG
	sprintf( G_msg, "ecd[%s]scd[%s]ymd[%s] -> eigmst access pos[%d]"
			,eigyo_cd,syuhai_cd,ymd,pos );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	/* �c�Ə�Ͻ��̊l��	*/
	memset( &sv_m02[pos], '\0',	sizeof( struct _EIGMST ));
	strcpy( sv_m02[pos].ecd,	eigyo_cd );
	strcpy( sv_m02[pos].shcdfr,	syuhai_cd );
	strcpy( sv_m02[pos].kaiymd,	ymd );
	
	ret = SelEigmst( &sv_m02[pos] );
	Ydbcommit();

	if( ret == RTN_OK ){
		strcpy( kbn, sv_m02[pos].yjhkkbn );
		return( ret );
	} else {
		if( ret == RTN_ZERO ){
			// NOT FOUND
		}
		memset( &sv_m02[pos], '\0', sizeof( struct _EIGMST ));
			// �����l�́H 1:�����񍐑ΏۊO
		strcpy( kbn, "1" );
		return( ret );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FEditPncChikenzok                                              */
/*  �@�\�T�v  �F�o�m�b�����f�[�^�ҏW ���@�`�F�b�N                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  Z04SJIR2    *inp;	: PNC�˗����                     */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _CHIKENZOK	*zok;	: �����g���\����                  */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditPncChikenzok( inp, zok )
struct		Z04SJIR2	*inp;		/* PNC�˗����(S-JIS)   */
struct		_CHIKENZOK	*zok;		/* �����g���\����		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* ��������	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditChikenkzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 �a�l�k��t�N����
	sprintf( zok->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 �˗����m��
	sprintf( zok->irino,	"00%03.3s%-6.6s"
		,inp->c_irai_no	,&inp->c_irai_no[5] );

	// 3 �˗����m�������t���O
	zok->iriketflg[0] = ' ';

	// 4 ��������m��
	zok->zssdino = stcPRM.myp_sedai;

	// ���O�o�͗p�L�[���ڐݒ�
	strcpy( G_utkymd,	zok->utkymd );
	strcpy( G_irino,	zok->irino );
	G_zssdino=zok->zssdino;

	// 5 �����E�v���g�R���m��
	memcpy( zok->prtclno,	inp->c_protcol_no,sizeof( inp->c_protcol_no ));
	// 6 �����E�q�{�݃R�[�h
	memcpy( zok->kosstcd,	inp->c_ko_siset_cd,sizeof( inp->c_ko_siset_cd ));
	// 7 �����E���^����
	memcpy( zok->tytme,		inp->c_toyotime,sizeof( inp->c_toyotime ));
	// 8 �����E���^��(��)
	memcpy( zok->tyryo,		inp->c_toyoryo,sizeof( inp->c_toyoryo ));
	// 9 �����E���^��(�P��)
	memcpy( zok->tyryotni,	inp->c_toyoryo_kbn,sizeof( inp->c_toyoryo_kbn ));
	// 10 �����E��ܕ��׎���
	memcpy( zok->yzfktme,	inp->c_drfuka_time,sizeof( inp->c_drfuka_time ));
	// 11 �����E�ꊇ�A�b�Z�C�t���O
	memcpy( zok->ikasflg,	inp->c_ikassay_flg,sizeof( inp->c_ikassay_flg ));
	// 12 �����E���̐�
	if( memcmp( inp->c_kentai_su, MYAPP_SPACE10
				, sizeof( inp->c_kentai_su )) == 0 ){
		zok->kntsu = 0;
	} else {
		memset( w_str,		0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_kentai_su,sizeof( inp->c_kentai_su ));
		zok->kntsu = atoi( w_str );
	}
	// 13 �����E���ڐ�
	if( memcmp( inp->c_komoku_su, MYAPP_SPACE10
				, sizeof( inp->c_komoku_su )) == 0 ){
		zok->kmksu = 0;
	} else {
		memset( w_str, 		0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_komoku_su,	sizeof( inp->c_komoku_su ));
		zok->kmksu = atoi( w_str );
	}
	// 14 �����E�̎�|�C���g	
	memcpy( zok->sspit,		inp->c_saisyu_po,sizeof( inp->c_saisyu_po ));
	// 15 �����E�ޗ��R�[�h�P
	memcpy( zok->zrcd01,	inp->c_zairyo01_cd,sizeof( inp->c_zairyo01_cd ));
	memcpy( zok->zrcd02,	inp->c_zairyo02_cd,sizeof( inp->c_zairyo02_cd ));
	memcpy( zok->zrcd03,	inp->c_zairyo03_cd,sizeof( inp->c_zairyo03_cd ));
	memcpy( zok->zrcd04,	inp->c_zairyo04_cd,sizeof( inp->c_zairyo04_cd ));
	memcpy( zok->zrcd05,	inp->c_zairyo05_cd,sizeof( inp->c_zairyo05_cd ));
	memcpy( zok->zrcd06,	inp->c_zairyo06_cd,sizeof( inp->c_zairyo06_cd ));
	// 21 �����E�ޗ��L���P
	memcpy( zok->zrkg01,	inp->c_zairyo01_kg,sizeof( inp->c_zairyo01_kg ));
	memcpy( zok->zrkg02,	inp->c_zairyo02_kg,sizeof( inp->c_zairyo02_kg ));
	memcpy( zok->zrkg03,	inp->c_zairyo03_kg,sizeof( inp->c_zairyo03_kg ));
	memcpy( zok->zrkg04,	inp->c_zairyo04_kg,sizeof( inp->c_zairyo04_kg ));
	memcpy( zok->zrkg05,	inp->c_zairyo05_kg,sizeof( inp->c_zairyo05_kg ));
	memcpy( zok->zrkg06,	inp->c_zairyo06_kg,sizeof( inp->c_zairyo06_kg ));
	// 27 �����E�ۗ��V�[�P���X
	memcpy( zok->hrseq,		inp->c_horyu_seq,sizeof( inp->c_horyu_seq ));
	// 28 �����E���̉���t���O
	memcpy( zok->kntksflg,	inp->c_kaisyu_flg,sizeof( inp->c_kaisyu_flg ));
	// 29 �����E�f�b�o�t���O
	memcpy( zok->gcpflg,	inp->c_gcp_flg,sizeof( inp->c_gcp_flg ));
	// 30 �����E�v���g�R������
	memset( buf, 			0x00, sizeof( buf ));
	cret=sj2euc( zok->prtclnm, memcpy(buf, inp->c_protocol_knm, 
		sizeof( inp->c_protocol_knm )), sizeof( zok->prtclnm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�����E�v���g�R�����́z[%s]"
			,zok->prtclnm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FEditNxtChikenzok                                              */
/*  �@�\�T�v  �F�����㊳�ґ����f�[�^�ҏW                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  Z02SJIR1    *inp;	: PNC�˗����                     */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA		*zok;	: ���ҏ��                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditNxtChikenzok( zok )
struct		_CHIKENZOK		*zok;	/* �����f�[�^	*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* ��������	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditNxtChikenzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  �� �� ��  �FEditCommonChikenzok                                           */
/*  �@�\�T�v  �F�����g���f�[�^���ʕҏW���`�F�b�N                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _CHIKENZOK	*zok;	: �����g��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditCommonChikenzok( zk )
struct	_CHIKENZOK	*zk;		/* �����f�[�^	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[20];

	strcpy( func_nm, "EditCommonChikenzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// ini�t�@�C���ł�DEBUG�w�莞�̂�print���������s
	if( stcPRM.myp_debug == 1 ){
		chiken_pr( zk );
	};

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FEditCsvKanjya                                                 */
/*  �@�\�T�v  �F���ҏ���CSV�`���ł̃e�L�X�g�o��                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �F struct	_KANJYA	kan;  : ���ҏ��\����                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK             : ����                                    */
/*               RTN_NG             : �G���[                                  */
/******************************************************************************/
int		EditCsvKanjya( kan )
struct		_KANJYA		*kan;
{
	char	func_nm[30];		/* �֐�����	*/
	char	w_str[30];
	char	delim[1+1];
	int		ret=RTN_OK;
	int		sz;

	strcpy( func_nm, "EditCsvKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( G_msg,	'\0', sizeof( G_msg ));
	strcpy( delim,	"!" );
	sz=sizeof( G_msg ) - 1;

to_csv( delim, sz, 	G_msg, kan->utkymd );
to_csv( delim, sz, 	G_msg, kan->irino );
to_csv( delim, sz, 	G_msg, kan->iriketflg );
// NUM
memset( w_str ,	'\0', sizeof( w_str ));
sprintf( w_str,	"%d", kan->zssdino );
to_csv( delim, sz, 	G_msg, w_str );
to_csv( delim, sz, 	G_msg, kan->sstcd );
to_csv( delim, sz, 	G_msg, kan->subsstcd );
to_csv( delim, sz, 	G_msg, kan->cdkbn1 );
to_csv( delim, sz, 	G_msg, kan->cdkbn2 );
to_csv( delim, sz, 	G_msg, kan->irimkey );
to_csv( delim, sz, 	G_msg, kan->srkcd );
to_csv( delim, sz, 	G_msg, kan->srknm );
to_csv( delim, sz, 	G_msg, kan->tticd );
to_csv( delim, sz, 	G_msg, kan->ttinm );
to_csv( delim, sz, 	G_msg, kan->gpcd );
to_csv( delim, sz, 	G_msg, kan->gpnm );
to_csv( delim, sz, 	G_msg, kan->skicd );
to_csv( delim, sz, 	G_msg, kan->skinm );
to_csv( delim, sz, 	G_msg, kan->krtno );
to_csv( delim, sz, 	G_msg, kan->knjid );
to_csv( delim, sz, 	G_msg, kan->knjnmn );
to_csv( delim, sz, 	G_msg, kan->knjnmk );
to_csv( delim, sz, 	G_msg, kan->knjnmkey );
to_csv( delim, sz, 	G_msg, kan->sc );
to_csv( delim, sz, 	G_msg, kan->tj );
to_csv( delim, sz, 	G_msg, kan->tjtni );
to_csv( delim, sz, 	G_msg, kan->sbtkbn );
to_csv( delim, sz, 	G_msg, kan->birthday );
to_csv( delim, sz, 	G_msg, kan->birthdaykbn );
to_csv( delim, sz, 	G_msg, kan->age );
to_csv( delim, sz, 	G_msg, kan->agekbn );
to_csv( delim, sz, 	G_msg, kan->btcd );
to_csv( delim, sz, 	G_msg, kan->btnm );
to_csv( delim, sz, 	G_msg, kan->utkcmtcd1 );
to_csv( delim, sz, 	G_msg, kan->utkcmtcd2 );
to_csv( delim, sz, 	G_msg, kan->utkcmtcd3 );
to_csv( delim, sz, 	G_msg, kan->utkcmtfr1 );
to_csv( delim, sz, 	G_msg, kan->utkcmtfr2 );
to_csv( delim, sz, 	G_msg, kan->utkcmtfrflg );
to_csv( delim, sz, 	G_msg, kan->ngkbn );
to_csv( delim, sz, 	G_msg, kan->nsssu );
to_csv( delim, sz, 	G_msg, kan->hkncd );
to_csv( delim, sz, 	G_msg, kan->ktshsu );
to_csv( delim, sz, 	G_msg, kan->iniriymd );
to_csv( delim, sz, 	G_msg, kan->zssflg );
to_csv( delim, sz, 	G_msg, kan->kkiriflg );
to_csv( delim, sz, 	G_msg, kan->hknskbn );
to_csv( delim, sz, 	G_msg, kan->utkkbn );
to_csv( delim, sz, 	G_msg, kan->nekbn );
to_csv( delim, sz, 	G_msg, kan->inknskbn );
to_csv( delim, sz, 	G_msg, kan->utkjkkbn );
to_csv( delim, sz, 	G_msg, kan->krflg );
to_csv( delim, sz, 	G_msg, kan->fdhhkkflg );
to_csv( delim, sz, 	G_msg, kan->utkdh );
to_csv( delim, sz, 	G_msg, kan->mutkymd );
to_csv( delim, sz, 	G_msg, kan->mirino );
to_csv( delim, sz, 	G_msg, kan->knsjslbcd1 );
to_csv( delim, sz, 	G_msg, kan->knsjslbcd2 );
to_csv( delim, sz, 	G_msg, kan->knsjslbcd3 );
to_csv( delim, sz, 	G_msg, kan->knsjslbcd4 );
to_csv( delim, sz, 	G_msg, kan->ymhkkflg );
to_csv( delim, sz, 	G_msg, kan->hkkkbdh );
to_csv( delim, sz, 	G_msg, kan->ecd );
to_csv( delim, sz, 	G_msg, kan->shcd );
to_csv( delim, sz, 	G_msg, kan->sstssnmj );
to_csv( delim, sz, 	G_msg, kan->sstssnmn );
to_csv( delim, sz, 	G_msg, kan->sstrsj );
to_csv( delim, sz, 	G_msg, kan->sstrsn );
to_csv( delim, sz, 	G_msg, kan->sstsbt );
to_csv( delim, sz, 	G_msg, kan->ttsstflg );
to_csv( delim, sz, 	G_msg, kan->rucd );
// NUM
memset( w_str,	'\0', sizeof( w_str ));
sprintf( w_str,	"%d", kan->irikmksu );
to_csv( delim, sz, 	G_msg, w_str );
to_csv( delim, sz, 	G_msg, kan->bmskn );
to_csv( delim, sz, 	G_msg, kan->irinrsbt );
to_csv( delim, sz, 	G_msg, kan->irihsmkbn );
to_csv( delim, sz, 	G_msg, kan->caresstflg );
to_csv( delim, sz, 	G_msg, kan->tktyflg );
to_csv( delim, sz, 	G_msg, kan->apkntino );
to_csv( delim, sz, 	G_msg, kan->sdnm );
to_csv( delim, sz, 	G_msg, kan->bko1 );
to_csv( delim, sz, 	G_msg, kan->bko2 );
to_csv( delim, sz, 	G_msg, kan->bko3 );
to_csv( delim, sz, 	G_msg, kan->zstrdh );
to_csv( delim, sz, 	G_msg, kan->zsssdh );
to_csv( delim, sz, 	G_msg, kan->stlzsssdh );
to_csv( delim, sz, 	G_msg, kan->stlzsssip );
to_csv( delim, sz, 	G_msg, kan->stlzssssyaid );
to_csv( NULL,  sz,	G_msg, kan->ksndh );

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
					"%s!%.1s!%s!%.1s!"
					"%s"
		// 1 ��ʁE2�t�@�C�����E3�sNo�E4�����N����
		// 5 BML��t���E6��������NO�E7�˗���NO�E8���ڃR�[�h
		// 9 �ڍ�
		, MYAPP_APPLNAME, G_fnm, w_str, stcPRM.myp_kjnymd
		, G_utkymd, MYAPP_SPACE10, G_irino, MYAPP_SPACE10
		, msg
	);
	strcpy( msg, buf );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �Fzoku_pr                                                       */
/*  �@�\�T�v  �F���ґ����\����printf                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA		*zok;	: ���ҏ��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		zoku_pr( in )
struct		_KANJYA		*in;		/* �����f�[�^	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	strcpy( func_nm, "zoku_pr" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	printf( "���ґ����f�[�^{\n" );

	printf( "utkymd\t[%s]\n",	in->utkymd );
	printf( "irino\t[%s]\n",	in->irino );
	printf( "zssdino\t[%d]\n",	in->zssdino );
	printf( "sstcd\t[%s]\n",	in->sstcd );
	printf( "subsstcd\t[%s]\n",	in->subsstcd );
	printf( "cdkbn1\t[%s]\n",	in->cdkbn1 );
	printf( "cdkbn2\t[%s]\n",	in->cdkbn2 );
	printf( "irimkey\t[%s]\n",	in->irimkey );
	printf( "srkcd\t[%s]\n",	in->srkcd );
	printf( "srknm\t[%s]\n",	in->srknm );
	printf( "tticd\t[%s]\n",	in->tticd );
	printf( "ttinm\t[%s]\n",	in->ttinm );
	printf( "gpcd\t[%s]\n",		in->gpcd );
	printf( "gpnm\t[%s]\n",		in->gpnm );
	printf( "skicd\t[%s]\n",	in->skicd );
	printf( "skinm\t[%s]\n",	in->skinm );
	printf( "krtno\t[%s]\n",	in->krtno );
	printf( "knjid\t[%s]\n",	in->knjid );
	printf( "knjnmn\t[%s]\n",	in->knjnmn );
	printf( "knjnmk\t[%s]\n",	in->knjnmk );
	printf( "knjnmkey\t[%s]\n",	in->knjnmkey );
	printf( "sc\t[%s]\n",		in->sc );
	printf( "tj\t[%s]\n",		in->tj );
	printf( "tjtni\t[%s]\n",	in->tjtni );
	printf( "sbtkbn\t[%s]\n",	in->sbtkbn );
	printf( "birthday\t[%s]\n",	in->birthday );
	printf( "birthdaykbn\t[%s]\n",	in->birthdaykbn );
	printf( "age\t[%s]\n",		in->age );
	printf( "agekbn\t[%s]\n",	in->agekbn );
	printf( "btcd\t[%s]\n",		in->btcd );
	printf( "btnm\t[%s]\n",		in->btnm );
	printf( "utkcmtcd1\t[%s]\n",	in->utkcmtcd1 );
	printf( "utkcmtcd2\t[%s]\n",	in->utkcmtcd2 );
	printf( "utkcmtcd3\t[%s]\n",	in->utkcmtcd3 );
	printf( "utkcmtfr1\t[%s]\n",	in->utkcmtfr1 );
	printf( "utkcmtfr2\t[%s]\n",	in->utkcmtfr2 );
	printf( "utkcmtfrflg\t[%s]\n",	in->utkcmtfrflg );
	printf( "ngkbn\t[%s]\n",	in->ngkbn );
	printf( "nsssu\t[%s]\n",	in->nsssu );
	printf( "hkncd\t[%s]\n",	in->hkncd );
	printf( "ktshsu\t[%s]\n",	in->ktshsu );
	printf( "iniriymd\t[%s]\n",	in->iniriymd );
	printf( "zssflg\t[%s]\n",	in->zssflg );
	printf( "kkiriflg\t[%s]\n",	in->kkiriflg );
	printf( "hknskbn\t[%s]\n",	in->hknskbn );
	printf( "utkkbn\t[%s]\n",	in->utkkbn );
	printf( "nekbn\t[%s]\n",	in->nekbn );
	printf( "inknskbn\t[%s]\n",	in->inknskbn );
	printf( "utkjkkbn\t[%s]\n",	in->utkjkkbn );
	printf( "krflg\t[%s]\n",	in->krflg );
	printf( "fdhhkkflg\t[%s]\n",	in->fdhhkkflg );
	printf( "utkdh\t[%s]\n",	in->utkdh );
	printf( "mutkymd\t[%s]\n",	in->mutkymd );
	printf( "mirino\t[%s]\n",	in->mirino );
	printf( "knsjslbcd1\t[%s]\n",	in->knsjslbcd1 );
	printf( "knsjslbcd2\t[%s]\n",	in->knsjslbcd2 );
	printf( "knsjslbcd3\t[%s]\n",	in->knsjslbcd3 );
	printf( "knsjslbcd4\t[%s]\n",	in->knsjslbcd4 );
	printf( "ymhkkflg\t[%s]\n",	in->ymhkkflg );
	printf( "hkkkbdh\t[%s]\n",	in->hkkkbdh );
	printf( "ecd\t[%s]\n",		in->ecd );
	printf( "shcd\t[%s]\n",		in->shcd );
	printf( "sstssnmj\t[%s]\n",	in->sstssnmj );
	printf( "sstssnmn\t[%s]\n",	in->sstssnmn );
	printf( "sstrsj\t[%s]\n",	in->sstrsj );
	printf( "sstrsn\t[%s]\n",	in->sstrsn );
	printf( "sstsbt\t[%s]\n",	in->sstsbt );
	printf( "ttsstflg\t[%s]\n",	in->ttsstflg );
	printf( "rucd\t[%s]\n",		in->rucd );
	printf( "irikmksu\t[%d]\n",	in->irikmksu );
	printf( "irihsmkbn\t[%s]\n",	in->irihsmkbn );
	printf( "caresstflg\t[%s]\n",	in->caresstflg );
	printf( "tktyflg\t[%s]\n",	in->tktyflg );
	printf( "apkntino\t[%s]\n",	in->apkntino );
	printf( "bmskn\t[%s]\n",	in->bmskn );
	printf( "irinrsbt\t[%s]\n",	in->irinrsbt );
	printf( "apkntino\t[%s]\n",	in->apkntino );
	printf( "sdnm\t[%s]\n",		in->sdnm );
	printf( "bko1\t[%s]\n",		in->bko1 );
	printf( "bko2\t[%s]\n",		in->bko2 );
	printf( "bko3\t[%s]\n",		in->bko3 );
	printf( "zstrdh\t[%s]\n",	in->zstrdh );
	printf( "zsssdh\t[%s]\n",	in->zsssdh );
	printf( "stlzsssdh\t[%s]\n",	in->stlzsssdh );
	printf( "stlzsssip\t[%s]\n",	in->stlzsssip );
	printf( "stlzssssyaid\t[%s]\n",	in->stlzssssyaid );
	printf( "ksndh\t[%s]\n",	in->ksndh );
	printf( "oyasstcd\t[%s]\n",	in->oyasstcd );
	printf( "trkdh\t[%s]\n",	in->trkdh );

	printf( "}\n" );
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �Fchiken_pr                                                     */
/*  �@�\�T�v  �F�����g���\����printf                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _CHIKENZOK	*in;	: �����g��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		chiken_pr( in )
struct		_CHIKENZOK		*in;		/* �����f�[�^	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		ret;

	strcpy( func_nm, "chiken_pr" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	printf( "�����g���f�[�^{\n" );

	printf( "utkymd\t[%s]\n",	in->utkymd );
	printf( "irino\t[%s]\n",	in->irino );
	printf( "iriketflg\t[%s]\n",	in->iriketflg );
	printf( "zssdino\t[%d]\n",	in->zssdino );
	printf( "prtclno\t[%s]\n",	in->prtclno );
	printf( "kosstcd\t[%s]\n",	in->kosstcd );
	printf( "tytme\t[%s]\n",	in->tytme );
	printf( "tyryo\t[%s]\n",	in->tyryo );
	printf( "tyryotni\t[%s]\n",	in->tyryotni );
	printf( "yzfktme\t[%s]\n",	in->yzfktme );
	printf( "ikasflg\t[%s]\n",	in->ikasflg );
	printf( "kntsu\t[%d]\n",	in->kntsu );
	printf( "kmksu\t[%d]\n",	in->kmksu );
	printf( "sspit\t[%s]\n",	in->sspit );
	printf( "zrcd01\t[%s]\n",	in->zrcd01 );
	printf( "zrcd02\t[%s]\n",	in->zrcd02 );
	printf( "zrcd03\t[%s]\n",	in->zrcd03 );
	printf( "zrcd04\t[%s]\n",	in->zrcd04 );
	printf( "zrcd05\t[%s]\n",	in->zrcd05 );
	printf( "zrcd06\t[%s]\n",	in->zrcd06 );
	printf( "zrkg01\t[%s]\n",	in->zrkg01 );
	printf( "zrkg02\t[%s]\n",	in->zrkg02 );
	printf( "zrkg03\t[%s]\n",	in->zrkg03 );
	printf( "zrkg04\t[%s]\n",	in->zrkg04 );
	printf( "zrkg05\t[%s]\n",	in->zrkg05 );
	printf( "zrkg06\t[%s]\n",	in->zrkg06 );
	printf( "hrseq\t[%s]\n",	in->hrseq );
	printf( "kntksflg\t[%s]\n",	in->kntksflg );
	printf( "gcpflg\t[%s]\n",	in->gcpflg );
	printf( "prtclnm\t[%s]\n",	in->ksndh );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FisCorrectChar                                                 */
/*  �@�\�T�v  �F���ґ������l�G���A�`�F�b�N                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	In[];	    : �`�F�b�N������                          */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK			    : ����I��                                */
/*               �ȊO				: ���s                                    */
/******************************************************************************/
int isCorrectChar(char *In)
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];            /* �֐�����     */
	int		ret=RTN_OK;
	char	buf[MYAPP_LEN_MSG+1];
	char	w_str[10+1];

    int i = 0;
    int nSuziFlg =0; //���߂��������Ƃ�������
    int nMaxNum = strlen(In);

 	/* ��������     */
 	strcpy( func_nm, "isCorrectChar" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( buf,	'\0', sizeof( buf ));
	memset( w_str,	'\0', sizeof( w_str ));

    for(i=0;i<nMaxNum;i++)
    {
        if(In[i] == ' '){
            if(nSuziFlg == 1){
				// DEBUG
				sprintf( G_msg, "���l ��������SPACE[%s]" , In );
				EditCsvMsg( G_msg );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__);
				// ERROR
				ret=RTN_NG;
                break;
            }
        }
        else if(In[i] == '.'){
            if(i==0){
				// DEBUG
				sprintf( G_msg, "���l �擪.�s��[%s]" , In );
				EditCsvMsg( G_msg );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__);
				// ERROR
				ret=RTN_NG;
                break;
            }
            if(nSuziFlg == 0){
				// DEBUG
				sprintf( G_msg, "���l �擪.�s��[%s]" , In );
				EditCsvMsg( G_msg );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__);
				// ERROR
				ret=RTN_NG;
                break;
            }
        }
        else if(In[i] >= '0' && In[i] <= '9'){
            nSuziFlg = 1;
        }
        else{
			// DEBUG
			sprintf( G_msg, "���l ��.�ȊO�s��[%s]" , In );
			EditCsvMsg( G_msg );
			LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__);
			// ERROR
			ret=RTN_NG;
            break;
        }
    }
 
    if(i==nMaxNum){
		ret=RTN_OK;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/** End of File ***************************************************************/
