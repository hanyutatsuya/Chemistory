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
/*  1.05     2007/06/01     INTEC.INC      ���Җ��L�[�󔒎��J���e�m���ݒ�     */
/*  2.01     2007/06/01     INTEC.INC      ���l�̍��ڂ̑Ó����`�F�b�N�ǉ�     */
/*  2.02     2007/06/01     INTEC.INC      ���ґ������ڂ̐��l�`�F�b�N�ǉ�     */
/*  3.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD202.h"

/******************************************************************************/
/*  �� �� ��  �FEditKinqKanjya                                                */
/*  �@�\�T�v  �F�ً}���ґ����f�[�^�ҏW ���@�`�F�b�N                           */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  AS4IRAI    *inp;	: AS400�ً}�˗����               */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA		*zok;	: ���ҏ��                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		EditKinqKanjya( inp, zok )
struct		AS4IRAI		*inp;		/* AS400�ً}�˗����(S-JIS)	*/
struct		_KANJYA		*zok;		/* ���ҏ��\����		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* ��������	*/
	strcpy(func_nm, "EditKinqKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 �a�l�k��t�N����	<- yyyy-mm-dd �`��
	sprintf( zok->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 �˗����m��			<- ����No����ҏW 00xxxxxxx00 �`��(����No�}�Ԃ͐؂�̂�)
	sprintf( zok->irino,"00%-3.3s%-4.4s00",inp->c_kentai_no	,&inp->c_kentai_no[5] );
	
	// 3 �˗����m�������t���O
	zok->iriketflg[0] = ' ';

	// 4 ��������m��
	zok->zssdino	= stcPRM.myp_sedai;

	// ���O�o�͗p�L�[���ڐݒ�
	strcpy( G_utkymd,	zok->utkymd );
	strcpy( G_irino,	zok->irino );

	// 5 �{�݃R�[�h
	if( memcmp( inp->c_siset_cd, MYAPP_SPACE10, sizeof(inp->c_siset_cd))==0){
											/* �{�݃R�[�h����̃P�[�X */
		memcpy( zok->sstcd,	inp->c_siset_cd,sizeof( inp->c_siset_cd ));
											/* �ꉞ�A��M�f�[�^����R�s�[���邪��ł� */
		strcpy( G_msg, "�{�݃R�[�h���󔒂ł��B" );
											/* WARNING��LOG�ɏo�� */
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	} else {								/* �{�݃R�[�h���ݒ肳��Ă���P�[�X */
		memcpy( zok->sstcd,	inp->c_siset_cd,sizeof( inp->c_siset_cd ));
											/* 7����(�S��)���R�s�[ */
	}
	// 6 �T�u�{�݃R�[�h
	strcpy( zok->subsstcd,	"0000" );

	// 7 �J�[�h�敪1
	memcpy( zok->cdkbn1,	inp->c_card1_kbn,sizeof( inp->c_card1_kbn ));

	// 8 �J�[�h�敪2
	// 9 �˗����L�[
	// 10 �f�ÉȃR�[�h
	memcpy( zok->srkcd,	inp->c_ka_cd,sizeof( inp->c_ka_cd ));
											/* ���̂܂܃R�s�[ */

	// 11 �f�ÉȖ�
	w_num = atoi( zok->srkcd );
	strcpy( zok->srknm,		kanm[w_num].sname );

	// 12 �S����R�[�h	
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
		// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->knjnmk);w_num < sizeof(zok->knjnmk)-1;w_num+=2 ){
		memcpy( &zok->knjnmk[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 22 ���Җ��L�[
	memset( buf,	0x00,	sizeof( buf ));
	NameKeyMake( buf, inp->c_kanja_nm, sizeof( inp->c_kanja_nm ));
		// 1.05 ADD ���Җ��L�[���󔒂̏ꍇ�J���e�m�����Z�b�g
	if(strcmp(buf, " ") == 0)
    {
        memcpy(buf, inp->c_karte_no,sizeof(inp->c_karte_no));
    }
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
	// 24 �̏d
	// 25 �̏d�敪			<- 0:Kg
	zok->tjtni[0] = '0';

	// 26 ���ʋ敪
	memcpy( zok->sbtkbn,	inp->c_sex,	sizeof( inp->c_sex ));

	// 27 ���N����
	// 28 ���N�����敪

	// 29 �N��
	memcpy( zok->age,		inp->c_age,	sizeof( inp->c_age ));
	// 30 �N��敪
	zok->agekbn[0] = 'Y';
		// �N��X�y�[�X�̏ꍇ�́AZ�F�s��
	if( memcmp( inp->c_age, MYAPP_SPACE10, sizeof( inp->c_age )) == 0 ){
		zok->agekbn[0] = 'Z';
	}

	// 31 �a���R�[�h
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
	memcpy( zok->utkcmtcd1,	inp->c_ukecmt_cd,sizeof( inp->c_ukecmt_cd));
	// 34 ��t�R�����g2
	// 35 ��t�R�����g3
	// 36 ��t�R�����g�t���[1
	// 37 ��t�R�����g�t���[2
	// 38 ��t�R�����g�t���[�t���O	zok->utkcmtfrflg
	strcpy( zok->utkcmtfrflg, "0" );

	// 39 ���@�O���敪
	memcpy( zok->ngkbn,		inp->c_ng_kbn,	sizeof( inp->c_ng_kbn ));
		// ���@�O���敪���X�y�[�X�̏ꍇ�́A0�F�s��
	if( memcmp( inp->c_ng_kbn, MYAPP_SPACE10, sizeof( inp->c_ng_kbn )) == 0 ){
		zok->ngkbn[0] = '0';
	}

	// 40 �D�P�T��
	// 41 �ی��R�[�h
	memcpy( zok->hkncd,		inp->c_hoken_cd,sizeof( inp->c_hoken_cd ));
	// 42 ���̑��{��		zok->ktshsu
	// 43 �@���˗���
	strcpy( zok->iniriymd,	INIT_DATE );
	// 44 �����C���t���O
	zok->zssflg[0] = '0';
	// 45 �ً}�˗��t���O
	memcpy( zok->kkiriflg,	inp->c_kinkyu_flg,sizeof( inp->c_kinkyu_flg ));
	// 46 �񌟍��敪
	zok->hknskbn[0] = '0';
	// 47 ��t�敪
	zok->utkkbn[0] = '0';

	// 48 �m�d�敪
	memcpy( zok->nekbn,	inp->c_ne_kbn,sizeof( inp->c_ne_kbn));

	// 49 �@�������敪		zok->inknskbn
	// 50 ��t��ԋ敪 		zok->utkjkkbn

	// 51 �����t���O	
	zok->krflg[0] = '0';

	// 52 �e�c��񍐃t���O
	zok->fdhhkkflg[0] = '0';

	// 53 ��t����
	strcpy( zok->utkdh,	INIT_TIME );
	// 54 ���a�l�k��t��
	strcpy( zok->mutkymd,	INIT_DATE );
	// 55 ���˗����m��
	// 56 �������{���{�R�[�h  knsjslbcd1
	// 57 �������{���{�R�[�h  knsjslbcd2
	// 58 �������{���{�R�[�h  knsjslbcd3
	// 59 �������{���{�R�[�h  knsjslbcd4

	// 60 �������񍐃t���O	
	zok->ymhkkflg[0] = ' ';
	// 61 �񍐊�]����
	strcpy( zok->hkkkbdh,	INIT_TIME );

	// 62 �c�Ə��R�[�h		<- ��3��
	sprintf( zok->ecd,		"%-3.3s",inp->c_eigyo_cd );
	// 63 �W�z�R�[�h		<- ��2��
	sprintf( zok->ecd,		"%-2.2s",&inp->c_eigyo_cd[3] );

	// 64 �{�ݖ���������
		// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->sstssnmj);w_num < sizeof(zok->sstssnmj)-1;w_num+=2 ){
		memcpy( &zok->sstssnmj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 65 �{�ݖ��������́i�J�i�j
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstssnmn, memcpy(buf, inp->c_sisetr_knm, 
		sizeof( inp->c_sisetr_knm )), sizeof( zok->sstssnmn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�{�ݖ��������́i�J�i�j�z"
			"[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 64 �{�ݖ��������� �J�i��ݒ�
	strcpy( zok->sstssnmj,	zok->sstssnmn );

	// 66 �{�ݖ�����
		// �S�p�X�y�[�X�Ŗ��߂�
	for( w_num=strlen(zok->sstrsj);w_num < sizeof(zok->sstrsj)-1;w_num+=2 ){
		memcpy( &zok->sstrsj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 67 �{�ݖ����́i�J�i�j	<- �{�ݖ��������́i�J�i�j10byte
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstrsn, memcpy(buf, inp->c_sisetr_knm, 10 ),
					 sizeof( zok->sstrsn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC �R�[�h�ϊ��G���[�y�{�ݖ����́i�J�i�j�z"
			"[%s][%s]"
			,zok->sstcd , zok->sstrsn );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 66 �{�ݖ����� �J�i��ݒ�
	strcpy( zok->sstrsj,	zok->sstrsn );

	// 68 �{�ݎ��
	// 69 ����{�݃t���O
	// 70 ���R�R�[�h
	// 71 �˗����ڐ�	
	if( memcmp( inp->c_kmcnt, MYAPP_SPACE10, sizeof( inp->c_kmcnt )) == 0 ){
		zok->irikmksu = 0;
	} else {
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_kmcnt,	sizeof( inp->c_kmcnt ));
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

	// 2.01 ADD STA
		/* 8byte �̎�N���� 	<- ��t�N�����̔N��t������ */
    // �̎�N���� �̎掞�� �Ó����`�F�b�N
	if( memcmp( inp->c_saisyu_bi, MYAPP_SPACE10, sizeof(inp->c_saisyu_bi))!=0){
        memset( w_str, 0x00, sizeof( w_str ));
		sprintf( w_str,	"%.4s%.4s", zok->utkymd, inp->c_saisyu_bi );
        if( ValidDate( VALDATE_DATE, w_str ) == RTN_NG ){
                // ERROR --> CONV
            sprintf( G_msg, "�̎�N���� �Ó����G���[�̂��ߏ����l�u��[%s]"
                , w_str );
            EditCsvMsg( G_msg );
            LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
                // �����l���Z�b�g
            memcpy( inp->c_saisyu_bi, MYAPP_SPACE10, sizeof(inp->c_saisyu_bi));
        }
    }
	// 2.01 ADD END

	// 79 ���l�P
		/* 3byte �ޗ��R�[�h */
	if( memcmp( inp->c_zairyo_cd, MYAPP_SPACE10, sizeof(inp->c_zairyo_cd))==0){
											/* �ޗ��R�[�h����̃P�[�X */
		memset( w_str,	0x00, sizeof( w_str ));
		strncpy( w_str, MYAPP_SPACE10, 3 );	/* �X�y�[�X�Ŗ��߂�(3BYTE��) */
	} else {								/* �ޗ��R�[�h���ݒ肳��Ă���P�[�X */
		sprintf( w_str,	"%-3.3s",	 inp->c_zairyo_cd );
											/* ���e���R�s�[ */
	}
		/* 8byte �̎�N���� 	<- ��t�N�����̔N��t������ */
	memset( buf,	0x00, sizeof( buf ));
	if( memcmp( inp->c_saisyu_bi, MYAPP_SPACE10, sizeof(inp->c_saisyu_bi))==0){
		strncpy( buf,	MYAPP_SPACE10, 8 );
	} else {
		sprintf( buf,	"%.4s%.4s", zok->utkymd, inp->c_saisyu_bi );
	}
		/* 4byte �̎掞�� */

	sprintf( zok->bko1, "%s!%.8s!%.4s", w_str,	buf, MYAPP_SPACE10 );


	// 80 ���l�Q 
		/* 4byte �~�A����		<- �OZERO��t�����Č������킹�� */
	if( memcmp( inp->c_nyotime, MYAPP_SPACE10, sizeof(inp->c_nyotime))==0){
		strncpy( w_str,	MYAPP_SPACE10, 4 );
	} else {
		memset( w_str,	0x00,		sizeof( w_str ));
		sprintf( w_str, "00%.2s", 	inp->c_nyotime );
		for( w_num=2;w_num < strlen(w_str);w_num++ ){
			if( w_str[w_num] == ' ' ){
				w_str[w_num] = '0';
			} else {
				break;
			}
		}
	}
		/* 1byte �~�A���ԒP�� 	<- 0 */
		/* 5byte �~�A��			<- �OZERO��t�����Č������킹�� */
	if( memcmp( inp->c_nyoryo, MYAPP_SPACE10, sizeof(inp->c_nyoryo))==0){
		strncpy( buf,	MYAPP_SPACE10, 5 );
	} else {
		memset( buf,	0x00,		sizeof( buf ));
		sprintf( buf,	"0%.4s", 	inp->c_nyoryo );
		for( w_num=1;w_num < strlen(buf);w_num++ ){
			if( buf[w_num] == ' ' ){
				buf[w_num] = '0';
			} else {
				break;
			}
		}
	}
		/* 1byte �~�A�ʒP��		<- 0 */

	sprintf( zok->bko2, "%-4.4s!0!%-5.5s!0", w_str,	buf );
	
		
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
	 &&( memcmp( &stcPRM.myp_zairyo[1], inp->c_zairyo_cd, 3 ) == 0 )){
		// �~�A����	c_nyotime
		if( memcmp( inp->c_nyotime, MYAPP_SPACE10
					, sizeof( inp->c_nyotime )) == 0 ){
			// WARNING
			sprintf( G_msg, "�~�A �~�A���ԃG���[[%.2s]" ,inp->c_nyotime );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		// �~�A��	c_nyoryo
		if( memcmp( inp->c_nyoryo, MYAPP_SPACE10
				, sizeof( inp->c_nyoryo )) == 0 ){
			// WARNING
			sprintf( G_msg, "�~�A �~�A�ʃG���[[%.4s]" ,inp->c_nyoryo );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

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
	int		a,k;
	unsigned char	name[61];
	unsigned char	keyj[61];
	char	func_nm[MYAPP_LEN_FNCNM+1];

	strcpy( func_nm,	"NameKeyMake" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( keyj, 0x00, sizeof( keyj ));
	strncpy( name, kan_name, len );
	a = k = 0;
	j  =  0;
	for  (i=0;i<len;i++) {
		switch  ( name[i] )
			{
			case 0xa0:		/*      */
			case 0xa1:		/*  �B   */
			case 0xa2:		/*  �u   */
			case 0xa3:		/*  �v   */
			case 0xa4:		/*  �A   */
			case 0xa5:		/*  �E  */
			case 0xb0:		/*     */
			case 0xde:		/*  �   */
			case 0xdf:		/*  �   */
			case 0x20:		/*  " " */
				break;
			case 0xa7:		/*	�	*/
				keyj[j]  =  0xb1;
				j++;
				break;
			case 0xa8:		/*	�	*/
				keyj[j]  =  0xb2;
				j++;
				break;
			case 0xa9:		/*	�	*/
				keyj[j]  =  0xb3;
				j++;
				break;
			case 0xaa:		/*	�	*/
				keyj[j]  =  0xb4;
				j++;
				break;
			case 0xab:		/*	�	*/
				keyj[j]  =  0xb5;
				j++;
				break;
			case 0xac:		/*	�	*/
				keyj[j]  =  0xd4;
				j++;
				break;
			case 0xad:		/*	�	*/
				keyj[j]  =  0xd5;
				j++;
				break;
			case 0xae:		/*	�	*/
				keyj[j]  =  0xd6;
				j++;
				break;
			case 0xaf:		/*	�	*/
				keyj[j]  =  0xc2;
				j++;
				break;
			default:
				/* ���䕶��?  0x00-0x1F,0x7F */
				if( iscntrl( name[i] ) != 0 ){
					/* ���䕶���͏��O */
					j++;
					break;
				}
				/* ASCII��������ALPHABET�ȊO�͏��O���� */
				if( isprint( name[i] ) != 0 ){
					if( isalpha( name[i] ) == 0 ){
						/* �p�����ȊO�͏��O */
						break;
					}
					/* alphabet letter count */
					a++;
				}
				/* ���p�J�i or ALPHABET */
				keyj[j]  =  name[i];
				j++;
				break;
			}
	}
	/* �S��ALPHABET�̏ꍇ2�����ȉ��͋󔒂ɒu������	*/
	if( strlen( keyj ) == a ){
		if( a < 3 ){
			strcpy( keyj, " " );
		}
	}

	strcpy( name_key, keyj );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
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

	printf( "utkymd    [%s]\n",	in->utkymd );
	printf( "irino     [%s]\n",	in->irino );
	printf( "zssdino   [%d]\n",	in->zssdino );
	printf( "sstcd     [%s]\n",	in->sstcd );
	printf( "subsstcd  [%s]\n",	in->subsstcd );
	printf( "cdkbn1    [%s]\n",	in->cdkbn1 );
	printf( "cdkbn2    [%s]\n",	in->cdkbn2 );
	printf( "irimkey   [%s]\n",	in->irimkey );
	printf( "srkcd     [%s]\n",	in->srkcd );
	printf( "srknm     [%s]\n",	in->srknm );
	printf( "tticd     [%s]\n",	in->tticd );
	printf( "ttinm     [%s]\n",	in->ttinm );
	printf( "gpcd      [%s]\n",	in->gpcd );
	printf( "gpnm      [%s]\n",	in->gpnm );
	printf( "skicd     [%s]\n",	in->skicd );
	printf( "skinm     [%s]\n",	in->skinm );
	printf( "krtno     [%s]\n",	in->krtno );
	printf( "knjid     [%s]\n",	in->knjid );
	printf( "knjnmn    [%s]\n",	in->knjnmn );
	printf( "knjnmk    [%s]\n",	in->knjnmk );
	printf( "knjnmkey  [%s]\n",	in->knjnmkey );
	printf( "sc        [%s]\n",	in->sc );
	printf( "tj        [%s]\n",	in->tj );
	printf( "tjtni     [%s]\n",	in->tjtni );
	printf( "sbtkbn    [%s]\n",	in->sbtkbn );
	printf( "birthday  [%s]\n",	in->birthday );
	printf( "birthdaykbn[%s]\n",in->birthdaykbn );
	printf( "age       [%s]\n",	in->age );
	printf( "agekbn    [%s]\n",	in->agekbn );
	printf( "btcd      [%s]\n",	in->btcd );
	printf( "btnm      [%s]\n",	in->btnm );
	printf( "utkcmtcd1 [%s]\n",	in->utkcmtcd1 );
	printf( "utkcmtcd2 [%s]\n",	in->utkcmtcd2 );
	printf( "utkcmtcd3 [%s]\n",	in->utkcmtcd3 );
	printf( "utkcmtfr1 [%s]\n",	in->utkcmtfr1 );
	printf( "utkcmtfr2 [%s]\n",	in->utkcmtfr2 );
	printf( "utkcmtfrflg[%s]\n",in->utkcmtfrflg );
	printf( "ngkbn     [%s]\n",	in->ngkbn );
	printf( "nsssu     [%s]\n",	in->nsssu );
	printf( "hkncd     [%s]\n",	in->hkncd );
	printf( "ktshsu    [%s]\n",	in->ktshsu );
	printf( "iniriymd  [%s]\n",	in->iniriymd );
	printf( "zssflg    [%s]\n",	in->zssflg );
	printf( "kkiriflg  [%s]\n",	in->kkiriflg );
	printf( "hknskbn   [%s]\n",	in->hknskbn );
	printf( "utkkbn    [%s]\n",	in->utkkbn );
	printf( "nekbn     [%s]\n",	in->nekbn );
	printf( "inknskbn  [%s]\n",	in->inknskbn );
	printf( "utkjkkbn  [%s]\n",	in->utkjkkbn );
	printf( "krflg     [%s]\n",	in->krflg );
	printf( "fdhhkkflg [%s]\n",	in->fdhhkkflg );
	printf( "utkdh     [%s]\n",	in->utkdh );
	printf( "mutkymd   [%s]\n",	in->mutkymd );
	printf( "mirino    [%s]\n",	in->mirino );
	printf( "knsjslbcd1[%s]\n",	in->knsjslbcd1 );
	printf( "knsjslbcd2[%s]\n",	in->knsjslbcd2 );
	printf( "knsjslbcd3[%s]\n",	in->knsjslbcd3 );
	printf( "knsjslbcd4[%s]\n",	in->knsjslbcd4 );
	printf( "ymhkkflg  [%s]\n",	in->ymhkkflg );
	printf( "hkkkbdh   [%s]\n",	in->hkkkbdh );
	printf( "ecd       [%s]\n",	in->ecd );
	printf( "shcd      [%s]\n",	in->shcd );
	printf( "sstssnmj  [%s]\n",	in->sstssnmj );
	printf( "sstssnmn  [%s]\n",	in->sstssnmn );
	printf( "sstrsj    [%s]\n",	in->sstrsj );
	printf( "sstrsn    [%s]\n",	in->sstrsn );
	printf( "sstsbt    [%s]\n",	in->sstsbt );
	printf( "ttsstflg  [%s]\n",	in->ttsstflg );
	printf( "rucd      [%s]\n",	in->rucd );
	printf( "irikmksu  [%d]\n",	in->irikmksu );
	printf( "bmskn     [%s]\n",	in->bmskn );
	printf( "irinrsbt  [%s]\n",	in->irinrsbt );
	printf( "irihsmkbn [%s]\n",	in->irihsmkbn );
	printf( "caresstflg[%s]\n",	in->caresstflg );
	printf( "tktyflg   [%s]\n",	in->tktyflg );
	printf( "apkntino  [%s]\n",	in->apkntino );
	printf( "sdnm      [%s]\n",	in->sdnm );
	printf( "bko1      [%s]\n",	in->bko1 );
	printf( "bko2      [%s]\n",	in->bko2 );
	printf( "bko3      [%s]\n",	in->bko3 );
	printf( "zstrdh    [%s]\n",	in->zstrdh );
	printf( "zsssdh    [%s]\n",	in->zsssdh );
	printf( "stlzsssdh [%s]\n",	in->stlzsssdh );
	printf( "stlzsssip [%s]\n",	in->stlzsssip );
	printf( "stlzssssyaid[%s]\n",in->stlzssssyaid );
	printf( "ksndh     [%s]\n",	in->ksndh );
	printf( "oyasstcd  [%s]\n", in->oyasstcd   );
	printf( "trkdh     [%s]\n",	in->trkdh );

	printf( "}\n" );
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/** End of File ***************************************************************/
