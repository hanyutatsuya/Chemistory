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
/*  1.00     2019/12/08     BML.INC        CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include	<string.h>
#include	"LD103.h"

/******************************************************************************/
/*  �� �� ��  �FEditPncKanjya                                                 */
/*  �@�\�T�v  �F�o�m�b�����f�[�^�ҏW ���@�`�F�b�N                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  my_stFileKanjya	*inp;	: PNC�˗����                 */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  my_stDbKanjya	*zok;	: ���ҏ��                    */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int	EditPncKanjya( inp, zok )
my_stFileKanjya		*inp;		/* PNC�˗����(S-JIS)	*/
my_stDbKanjya		*zok;		/* ���ҏ��\����	*/
{
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int	w_num;

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

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
	zok->zssdino	= 0;

	//----------------------------------------------------	
	// �L�[���ڕҏW��
	//	-> �폜�t���O='1'�Ȃ�Ώ����𔲂���
	//----------------------------------------------------	
	if( inp->c_zokdel_flg[0] == '1' ){
		// WARNING
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�����폜�f�[�^����M���܂����i�f�[�^�ǂݔ�΂��j�B" );
		return( RTN_SKIP );
	}

	// 5 �{�݃R�[�h
	memcpy( zok->sstcd,	inp->c_siset_cd,sizeof( inp->c_siset_cd ));
	// 6 �T�u�{�݃R�[�h
	memcpy( zok->subsstcd,	inp->c_subsiset_cd,sizeof( inp->c_subsiset_cd ));
	// 7 �J�[�h�敪1
	memcpy( zok->cdkbn1,	inp->c_card1_kbn,sizeof( inp->c_card1_kbn ));
	// 8 �J�[�h�敪2
	memcpy( zok->cdkbn2,	inp->c_card2_kbn,sizeof( inp->c_card2_kbn ));
	// 9 �˗����L�[
	memcpy( zok->irimkey,	inp->c_iraimoto_key,sizeof( inp->c_iraimoto_key ));
	// 10 �f�ÉȃR�[�h	
	memcpy( zok->srkcd,	inp->c_ka_cd,sizeof( inp->c_ka_cd ));
	// 11 �f�ÉȖ�
	memcpy( zok->srknm,	inp->c_ka_nm,sizeof( inp->c_ka_nm ));
	// 12 �S����R�[�h	
	memcpy( zok->tticd,	inp->c_dr_cd,sizeof( inp->c_dr_cd ));
	// 13 �S���㖼
	memcpy( zok->ttinm,	inp->c_dr_nm, sizeof( inp->c_dr_nm ));

	// 14 �厡��R�[�h		zok->gpcd
	// 15 �厡�㖼			zok->gpnm
	// 16 �Љ��R�[�h		zok->skicd
	// 17 �Љ�㖼			zok->skinm

	// 18 �J���e�m��
	memcpy( zok->krtno,	inp->c_karte_no,sizeof( inp->c_karte_no ));
	// 19 ���҂h�c
	memcpy( zok->knjid,	inp->c_kanja_id,sizeof( inp->c_kanja_id ));
	// 20 ���Җ��i�J�i�j
	memcpy( zok->knjnmn,	inp->c_kanja_nm,sizeof( inp->c_kanja_nm ));
	// 21 ���Җ��i�����j
	memcpy( zok->knjnmk,	inp->c_kanja_knm,sizeof( inp->c_kanja_knm ));
	// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->knjnmk);w_num < sizeof(zok->knjnmk)-1;w_num+=2 ){
		memcpy( &zok->knjnmk[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 22 ���Җ��L�[
	memset( buf,	0x00,	sizeof( buf ));

	NameKeyMake( buf,	inp->c_kanja_nm,sizeof( inp->c_kanja_nm ));
	if(strcmp(buf, " ") == 0)
	{
		memcpy(buf,	inp->c_karte_no,sizeof(inp->c_karte_no));
	}

	memcpy( zok->knjnmkey,	buf,sizeof( zok->knjnmkey ));
	// 23 �g��	
	memcpy( zok->sc,		inp->c_tall,	sizeof( inp->c_tall ));
	// �g���A�̏d�̐��l�`�F�b�N���s���i�ޗ���킸�j
	if( memcmp( inp->c_tall, MYAPP_SPACE10, sizeof( inp->c_tall )) != 0 ){
		//�@�Ó����`�F�b�N
		if( isCorrectChar( zok->sc ) != RTN_OK ) {
			// ERROR
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�g���G���[�̂��߃X�y�[�X�ɒu��[%5.5s]" , inp->c_tall );
			// NULL��ݒ�
			memset( zok->sc, 0x00, sizeof( zok->sc ));
		}
	}

	// 24 �̏d
	memcpy( zok->tj,		inp->c_weight,	sizeof( inp->c_weight ));
	// �g���A�̏d�̐��l�`�F�b�N���s���i�ޗ���킸�j
	if( memcmp( inp->c_weight, MYAPP_SPACE10, sizeof( inp->c_weight )) != 0 ){
		//�@�Ó����`�F�b�N
		if( isCorrectChar( zok->tj ) != RTN_OK ) {
			// ERROR
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�̏d�G���[�̂��߃X�y�[�X�ɒu��[%5.5s]" , inp->c_weight );
			// NULL��ݒ�
			memset( zok->tj, 0x00, sizeof( zok->tj ));
		}
	}

	// 25 �̏d�敪
	memcpy( zok->tjtni,		inp->c_weight_kbn,	sizeof( inp->c_weight_kbn));
	// 26 ���ʋ敪
	memcpy( zok->sbtkbn,		inp->c_sex,		sizeof( inp->c_sex ));
	// 27 ���N����
	memcpy( zok->birthday,		inp->c_birth_ymd,	sizeof( inp->c_birth_ymd ));
	// 28 ���N�����敪
	memcpy( zok->birthdaykbn,	inp->c_birth_kbn,	sizeof( inp->c_birth_kbn ));
	// 29 �N��
	memcpy( zok->age,		inp->c_age,		sizeof( inp->c_age ));
	// 30 �N��敪
	memcpy( zok->agekbn,		inp->c_age_kbn,		sizeof( inp->c_age_kbn ));
	// 31 �a���R�[�h
	memcpy( zok->btcd,		inp->c_byoto_cd,	sizeof( inp->c_byoto_cd ));

	// 32 �a����
	memcpy( zok->btnm,	inp->c_byoto_nm,sizeof( inp->c_byoto_nm ));
	// 33 ��t�R�����g1	
	memcpy( zok->utkcmtcd1,	inp->c_ukecmt1_cd,sizeof( inp->c_ukecmt1_cd));
	// 34 ��t�R�����g2
	memcpy( zok->utkcmtcd2,	inp->c_ukecmt2_cd,sizeof( inp->c_ukecmt2_cd));
	// 35 ��t�R�����g3
	memcpy( zok->utkcmtcd3,	inp->c_ukecmt3_cd,sizeof( inp->c_ukecmt3_cd));
	// 36 ��t�R�����g�t���[1
	memcpy( zok->utkcmtfr1,	inp->c_ukecmt1_cmt,sizeof( inp->c_ukecmt1_cmt ));
	// 37 ��t�R�����g�t���[2
	memcpy( zok->utkcmtfr2,	inp->c_ukecmt2_cmt, sizeof( inp->c_ukecmt2_cmt ));
	// 38 ��t�R�����g�t���[�t���O	zok->utkcmtfrflg
	strcpy( zok->utkcmtfrflg, "0" );
	// 39 ���@�O���敪
	memcpy( zok->ngkbn,	inp->c_ng_kbn,	sizeof( inp->c_ng_kbn ));
	// 40 �D�P�T��
	memcpy( zok->nsssu,	inp->c_ninsin_cnt,sizeof( inp->c_ninsin_cnt ));
	// 41 �ی��R�[�h
	memcpy( zok->hkncd,	inp->c_hoken_cd,sizeof( inp->c_hoken_cd ));
	// 42 ���̑��{��	zok->ktshsu
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
	memcpy( zok->nekbn,	inp->c_ne_kbn,	sizeof( inp->c_ne_kbn ));
	// 49 �@�������敪	zok->inknskbn
	// 50 ��t��ԋ敪 	zok->utkjkkbn
	// 51 �����t���O	
	strcpy( zok->krflg,	"0" );
	// 52 �e�c��񍐃t���O
	memcpy( zok->fdhhkkflg,	inp->c_hifd_flg,sizeof( inp->c_hifd_flg ));

	// 53 ��t����
	if( strncmp( inp->c_uke_time, MYAPP_SPACE10, 4 ) == 0 ){
		strcpy( zok->utkdh,	INIT_TIME );
	} else {
		sprintf( zok->utkdh,	"%.2s:%.2s:00", inp->c_uke_time,&inp->c_uke_time[2] );
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
	// �󔒂Ƃ���

	// 61 �񍐊�]����
	strcpy( zok->hkkkbdh,	INIT_TIME );
	// 62 �c�Ə��R�[�h
	memcpy( zok->ecd,	inp->c_eigyo_cd,sizeof( inp->c_eigyo_cd ));
	// 63 �W�z�R�[�h
	memcpy( zok->shcd,	inp->c_syuhai_cd,sizeof( inp->c_syuhai_cd ));
	// 64 �{�ݖ���������
	memcpy( zok->sstssnmj,	inp->c_siset_knm,sizeof( inp->c_siset_knm ));
	// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->sstssnmj);w_num < sizeof(zok->sstssnmj)-1;w_num+=2 ){
		memcpy( &zok->sstssnmj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 65 �{�ݖ��������́i�J�i�j
	memcpy( zok->sstssnmn,	inp->c_siset_nm,sizeof( inp->c_siset_nm ));
	// 66 �{�ݖ�����
	memcpy( zok->sstrsj,	inp->c_sisetr_knm,sizeof( inp->c_sisetr_knm ));
	// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->sstrsj);w_num < sizeof(zok->sstrsj)-1;w_num+=2 ){
		memcpy( &zok->sstrsj[w_num], MYAPP_KJSPACE10, 2 );
	}
		// ALL �S�p�X�y�[�X�̏ꍇ�A�������̂��ҏW
	if( strcmp( zok->sstrsj, MYAPP_KJSPACE10 ) == 0 ){
		memcpy( zok->sstrsj, zok->sstssnmj, sizeof( zok->sstrsj ) - 1 );
	}

	// 67 �{�ݖ����́i�J�i�j
	memcpy( zok->sstrsn,	inp->c_sisetr_nm, sizeof( inp->c_sisetr_nm ));
	// 68 �{�ݎ��
	memcpy( zok->sstsbt,inp->c_siset_kbn,sizeof( inp->c_siset_kbn ));
	// 69 ����{�݃t���O
	memcpy( zok->ttsstflg,inp->c_tokutei_flg,sizeof( inp->c_tokutei_flg));

	// 70 ���R�R�[�h
	memset( buf,	0x00,	sizeof( buf ));
	memcpy( zok->rucd,	inp->c_riyu_cd,sizeof( inp->c_riyu_cd ));
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

	// �̎�N���� �̎掞�� �Ó����`�F�b�N
	if( memcmp( inp->c_saisyu_ymd, MYAPP_SPACE10, sizeof(inp->c_saisyu_ymd) ) != 0 ){
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_saisyu_ymd,	sizeof( inp->c_saisyu_ymd ));
		if( ValidDate( VALDATE_DATE, w_str ) == RTN_NG ){
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
			// �����l���Z�b�g
			memcpy( inp->c_saisyu_time, MYAPP_SPACE10, sizeof(inp->c_saisyu_time));
		}
	}

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
	// 88 �e�{�݃R�[�h
	strcpy( zok->oyasstcd,	zok->sstcd );
	// 89 �o�^����	CURRENT TIMESTAMP

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	return( RTN_OK );
}
/******************************************************************************/
/*  �� �� ��  �FEditCommonKanjya                                              */
/*  �@�\�T�v  �F���ґ����f�[�^���ʕҏW���`�F�b�N                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  my_DbKanjya		*zok;	: ���ҏ��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int	EditCommonKanjya( zok )
my_stDbKanjya	*zok;	// ���ґ����\����
{
	int	ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;

	/* ��������     */
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	//=========================================
	//	CHECK
	//=========================================
	// DATE �Ó����`�F�b�N
	// �a�l�k��t��
	if( ( strcmp( zok->utkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->utkymd )) == RTN_NG )){
		// ERROR
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�a�l�k��t�� �Ó����G���[[%s]" , zok->utkymd );
		return( RTN_NG );
	}

	// �@���˗���		���敪���������ߐ����O��Ƃ���
	if( ( strcmp( zok->iniriymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->iniriymd )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�@���˗��� �Ó����G���[�̂��ߏ����l�u��[%s]" , zok->iniriymd );
		// �����l���Z�b�g
		strcpy( zok->iniriymd, INIT_DATE );
	}

	// ���a�l�k��t��
	if( ( strcmp( zok->mutkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->mutkymd )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���a�l�k��t�� �Ó����G���[�̂��ߏ����l�u��[%s]" , zok->mutkymd );
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
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���N���� �Ó����G���[[%s]", zok->birthday );
		}
	}

	// TIME �Ó����`�F�b�N
	// ��t����
	if( ( strcmp( zok->utkdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->utkdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "��t���� �Ó����G���[�̂��ߏ����l�u��[%s]" , zok->utkdh );
		// �����l���Z�b�g
		strcpy( zok->utkdh, INIT_TIME );
	}
	// �񍐊�]����
	if( ( strcmp( zok->hkkkbdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->hkkkbdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�񍐊�]���� �Ó����G���[�̂��ߏ����l�u��[%s]" , zok->hkkkbdh );
		// �����l���Z�b�g
		strcpy( zok->hkkkbdh, INIT_TIME );
	}

	// TIMESTAMP �Ó����`�F�b�N
	// �����o�^����
	if( ( strcmp( zok->zstrdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zstrdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�����o�^���� �Ó����G���[�̂��ߏ����l�u��[%s]" , zok->zstrdh );
		// �����l���Z�b�g
		strcpy( zok->zstrdh, INIT_TIMESTAMP );
	}
	// �����C������
	if( ( strcmp( zok->zsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�����C������ �Ó����G���[�̂��ߏ����l�u��[%s]" , zok->zsssdh );
		// �����l���Z�b�g
		strcpy( zok->zsssdh, INIT_TIMESTAMP );
	}
	// �T�e���C�g�������C������
	if( ( strcmp( zok->stlzsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->stlzsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�T�e���C�g�������C������ �Ó����G���[�̂���" "�����l�u��[%s]" , zok->stlzsssdh );
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
				sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�N�� �Ó����G���[[%s]" , zok->age );
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
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�N��敪�G���[[%s]" , zok->agekbn );
			// �����l���Z�b�g
			strcpy( zok->agekbn, AGEKBN_UNKNOWN );
		}
	//	���ʋ敪
	if(   ( strcmp( zok->sbtkbn, SEX_MALE   ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_FEMALE ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_UNKNOWN ) != 0 )){
			// WARNING
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���ʋ敪�G���[[%s]", zok->sbtkbn );
			// �����l���Z�b�g
			strcpy( zok->sbtkbn, SEX_UNKNOWN );
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FNameKeyMake                                                   */
/*  �@�\�T�v  �F���Җ��L�[�쐬                                                */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	kan_name[];	: S-JIS ���҃J�i����                  */
/*   ��Q���� �Fint	len;		: S-JIS ���҃J�i����length            */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fchar	name_key[];	: S-JIS ���Җ��L�[                    */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		NameKeyMake( name_key, kan_name, len )
char		name_key[];		/*	[O]	���Җ��L�[	*/
char		kan_name[];		/*	[I]	���Җ�		*/
int			len;			/*	[I]	���Җ�length	*/
{
	int		i,j;
	char	name[61];
	char	keyj[61];

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

	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FisCorrectChar                                                 */
/*  �@�\�T�v  �F���ґ������l�G���A�`�F�b�N                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	In[];	    : �`�F�b�N������                          */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK		    : ����I��                                */
/*               �ȊO		    : ���s                                    */
/******************************************************************************/
int isCorrectChar(char *In)
{
	int	ret=RTN_OK;

	int i = 0;
	int nSuziFlg =0; //���߂��������Ƃ�������

	/* ��������     */
	int nMaxNum = strlen(In);
	char	buf[nMaxNum + 1];
	memset( buf,	'\0', sizeof( buf ));

	sFncTrim( buf, In );
	nMaxNum = strlen(buf);

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	for(i=0;i<nMaxNum;i++){
		if(buf[i] == ' '){
			if(nSuziFlg == 1){
				// DEBUG
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l ��������SPACE[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(buf[i] == '.'){
			if(i==0){
				// DEBUG
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l �擪.�s��[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
			if(nSuziFlg == 0){
				// DEBUG
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l �擪.�s��[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(buf[i] >= '0' && buf[i] <= '9'){
			nSuziFlg = 1;
        	}
		else{
			// DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "���l ��.�ȊO�s��[%s]" , In );
			// ERROR
			ret=RTN_NG;
			break;
		}
	}
 
	if(i==nMaxNum){
		ret=RTN_OK;
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FValidDate                                                     */
/*  �@�\�T�v  �F���t�A�����@�Ó����`�F�b�N                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F int    mode            : �ҏW����Ă�����t�֘A���ڂ̌^      */
/*   ��Q���� �F char   indate[]        : ���͓��t����                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK              : ����                                   */
/*               RTN_NG              : �G���[                                 */
/******************************************************************************/
int	ValidDate( mode, indate )
int		mode;
char		indate[];
{
	static	int t[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int	y, m, d, h, mi, s;
	int	i;
	char	w_yyyy[5];
	char	w_mm[3];
	char	w_dd[3];
	char	w_hh[3];
	char	w_mi[3];
	char	w_ss[3];

	/* �����ݒ�     */
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ValidDate", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	strcpy( w_yyyy, "0000" );       y = strlen( w_yyyy ) - 1;
	strcpy( w_mm,   "00" );         m = strlen( w_mm ) - 1;
	strcpy( w_dd,   "00" );         d = strlen( w_dd ) - 1;
	strcpy( w_hh,   "00" );         h = strlen( w_hh ) - 1;
	strcpy( w_mi,   "00" );         mi = strlen( w_mi ) - 1;
	strcpy( w_ss,   "00" );         s = strlen( w_ss ) - 1;

	// INPUT���t��N���������b�ɕ���
	for( i = strlen( indate ) - 1; i >=0 ; --i){
		if( indate[i] >= '0' && indate[i] <= '9' ){
			if(( mode == VALDATE_TIME )||( mode == VALDATE_TIMESTAMP )){
				// SS
				if( s >= 0 ){
					w_ss[s] = indate[i];
					--s;
					continue;
				}
				// MINUTE
				if( mi >= 0 ){
					w_mi[mi] = indate[i];
					--mi;
					continue;
				}
				// HOUR
				if( h >= 0 ){
					w_hh[h] = indate[i];
					--h;
					continue;
				}
			}
		        if(( mode == VALDATE_DATE )||( mode == VALDATE_TIMESTAMP )){
		        	// DAY
		        	if( d >= 0 ){
		        		w_dd[d] = indate[i];
		        		--d;
		        		continue;
		        	}
		        	// MONTH
		        	if( m >= 0 ){
		        		w_mm[m] = indate[i];
		        		--m;
		        		continue;
		        	}
		        	// YEAR
		        	if( y >= 0 ){
		        		w_yyyy[y] = indate[i];
		        		--y;
		        		continue;
		        	}
			}
		}
	}
	y = atoi( w_yyyy );
	m = atoi( w_mm );
	d = atoi( w_dd );
	h = atoi( w_hh );
	mi = atoi( w_mi );
	s = atoi( w_ss );

	// TIME
	if(( h >= 24 ) || ( mi >= 60 ) || ( s >= 60 )){
		// �����G���[
		return( RTN_NG );
	}
	if( mode == VALDATE_TIME ){
		return( RTN_OK );
	}

	if( ( y >= 1 ) && ( y <= 9999 ) && ( m >= 1 ) && ( m <= 12 )
	 && ( d >= 1   ) &&( d <= t[ m - 1 ] )) {
		// OK
		return( RTN_OK );
	} else {
		// �[�N�`�F�b�N
		// �P�j ������S�Ŋ���A����؂ꂽ�N�͉[�N�ł���
		// �Q�j �Ȃ��A�P�̏����𖞂����Ă��A�P�O�O�Ŋ���؂ꂽ�ꍇ�͉[�N������
		// �R�j �Ȃ��A�Q�̏����𖞂����Ă��A�S�O�O�Ŋ���؂ꂽ�ꍇ�͉[�N
		if(( m == 2 ) && ( y%4 == 0 )){                         // �[�N���
			if(( y%100 != 0 ) || ( y%400 == 0 )){   // �[�N����
				if( d == 29 ){
					// OK
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "ValidDate", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
					return( RTN_OK );
				}
			}
		}
	}
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ValidDate", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	// ���t�G���[
	return( RTN_NG );
}

/*****************************************************************
        ����  : �a��E����ϊ�

        �T�v  : �a��琼��ɕϊ�����
                ���ފǗ�Ͻ��Ɍ����̊Ǘ������Ă���
        ���Ӂ@: �����ƕҏW�O�̔N���������������Ƃ��O��

        �\��  : char    *Lwa_ymd( ymd10, gengou, ymd )
        ����  : (out)   char    ymd10[];        �ҏW��(YYYY/MM/DD)
                (in)    char    gengou[];
                        ����
                        ' ':����
                         M :���� "1868/09/08", "1912/07/29"
                         T :�吳 "1912/07/30", "1926/12/24", "T"
                         S :���a "1926/12/25", "1989/01/07", "S"
                         H :���� "1989/01/08", "9999/12/31", "H"
                (in)    char    ymd[];          �ҏW�O(YYYYMMDD)

        ��-ݒl: ymd10�̐擪���ڽ
                ymd10=NULL�̏ꍇ�͓����ر�̕�����擪���ڽ
*****************************************************************/
int             wa2ymd( ymd10, gengou, ymd )
char            ymd10[];                                        /* �ҏW��(YYYY/MM/DD)   */
char            gengou[];                                       /* ����                 */
char            ymd[];                                          /* �ҏW�O(YYYYMMDD)     */
{
	char    wk_ymd8[10];
	char    wk_yy[10];
	char    wk_mmdd[10];
	int     i,j,k;
	int     add_yy;

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "wa2ymd", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	/* ����Ȃ�Ώ����I�� */
	if( gengou[0] == ' ' ){
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "wa2ymd", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
		sprintf( ymd10, "%.4s-%.2s-%.2s", ymd, &ymd[4], &ymd[6] );
		return( RTN_OK );
	}

	/* ���t�̊l��   */
	strcpy( wk_yy,   "0000" );
	strcpy( wk_mmdd, "0000" );
	j = k = strlen( wk_mmdd ) - 1;
	for( i = strlen( ymd ) - 1; i >=0 ; --i){
		if( ymd[i] >= '0' && ymd[i] <= '9' ){
			if( j >= 0 ){
				wk_mmdd[j] = ymd[i];
				--j;
				continue;
			}
			if( k >= 0 ){
				wk_yy[k] = ymd[i];
				--k;
				continue;
			}
			break;
		}
	}
	/* �����̊J�n�N�������߂�B�{����DB���]�܂����B�Ƃ肠����ON */
	switch  ( gengou[0] ) {
		case 'M' :              /* ���� */
			add_yy = 1868;
			break;
		case 'T' :              /* �吳 */
			add_yy = 1912;
			break;
		case 'S' :              /* ���a */
			add_yy = 1926;
			break;
		case 'H' :              /* ���� */
			add_yy = 1989;
			break;
		case 'R' :              /* �ߘa */
			add_yy = 2019;
			break;
		default:
			break;
	}
	/* �J�n��������߂�     */
	if( add_yy != 0 ){
		--add_yy;
	}
	sprintf( wk_ymd8, "%04d%s", atoi( wk_yy ) + add_yy, wk_mmdd );
	memset( ymd10, '\0', strlen( ymd10 ));
	sprintf( ymd10, "%.4s-%.2s-%.2s", wk_ymd8, &wk_ymd8[4], &wk_ymd8[6] );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "wa2ymd", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	return( RTN_OK );
}

/********************************************************************************/
/*  �� �� ��  �FsFncTrim                                                        */
/*  �@�\�T�v  �F�w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[����        */
/*  ��    ��  �F                                                                */
/*   ��Q���� �Fchar * �ϊ���������                                             */
/*  �o    ��  �F                                                                */
/*   ��P���� �Fchar * �ϊ��㕶����                                             */
/********************************************************************************/
void sFncTrim(char * dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != '\0'; srcCnt ++) {
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
