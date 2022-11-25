/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FtagPNC.h                                                     */
/*   �T      �v�F�o�m�b��M�t�@�C���\���̒�`                                 */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/******************************************************************************/
#ifndef _TAGPNC_H
#define _TAGPNC_H

#define	PNC_RECSIZE		1024
#define	IRAI_MAX	6
#define	ERR_MAX		10

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
/*====== PNC����M̧�� ==========================================
	ں��ގ��ʎq	�\���̖�		���e
-----------------------------------------------------------------
		HD	Z00SJHD		̧��ͯ�ް
		TR	Z01SJTR		̧���ڰװ
		R1	Z02SJIR1	�˗�����
		R5	Z03SJIR5	�˗�����(PCL)
		R2	Z04SJIR2	�����g��
		R1	Z05SJIR1	���ʈ˗�����
		RF  Z11SJIRF	END���i�˗��j
		R1  Z12SJR1		�v���J�[�h
=================================================================*/

/*===============================================================*/
/*		����													 */
/*===============================================================*/
/*--- S-JIS�p�\���� ---*/
struct	Z00SJHD		{	/* ��PNC����Mͯ�ް(S-JIS�j 1024byte*/
	char	c_sbt[2];		/* ں��ގ��ʎq([HD]�Œ�)*/
	char	c_sosinsaki[8];		/* ���M��		*/
	char	c_sosinmoto[8];		/* ���M��		*/
	char	c_opedate[8];		/* ���M�������N����	*/
	char	c_tuban[4];			/* �ʔ�			*/
	char	c_dflow[10];		/* �ް��۰ID		*/
	char	c_param1[128];		/* ���Ұ�1		*/
	char	c_param2[128];		/* ���Ұ�2		*/
	char	c_yobi[216];		/* �\��			*/
	char	c_filler[511];		/* FILLER 		*/
	char	c_kaigyo[1];		/* ���s����		*/ 
};
struct	Z01SJTR		{	/* ��PNC����M�ڰװ(S-JIS�j 1024byte*/
	char	c_sbt[2];		/* ں��ގ��ʎq([TR]�Œ�)*/
	char	c_sosinsaki[8];		/* ���M��		*/
	char	c_sosinmoto[8];		/* ���M��		*/
	char	c_opedate[8];		/* ���M�������N����	*/
	char	c_tuban[4];			/* �ʔ�			*/
	char	c_dflow[10];		/* �ް��۰ID		*/
	char	c_reccnt[8];		/* ����ں��ތ���	*/
	char	c_reccnt01[8];		/* �_��ں��ތ����P	*/
	char	c_reccnt02[8];		/* �_��ں��ތ����Q	*/
	char	c_reccnt03[8];		/* �_��ں��ތ����R	*/
	char	c_reccnt04[8];		/* �_��ں��ތ����S	*/
	char	c_reccnt05[8];		/* �_��ں��ތ����T	*/
	char	c_reccnt06[8];		/* �_��ں��ތ����U	*/
	char	c_reccnt07[8];		/* �_��ں��ތ����V	*/
	char	c_reccnt08[8];		/* �_��ں��ތ����W	*/
	char	c_reccnt09[8];		/* �_��ں��ތ����X	*/
	char	c_reccnt10[8];		/* �_��ں��ތ����P�O	*/
	char	c_reccnt11[8];		/* �_��ں��ތ����P�P	*/
	char	c_reccnt12[8];		/* �_��ں��ތ����P�Q	*/
	char	c_reccnt13[8];		/* �_��ں��ތ����P�R	*/
	char	c_reccnt14[8];		/* �_��ں��ތ����P�S  	*/
	char	c_reccnt15[8];		/* �_��ں��ތ����P�T	*/
	char	c_yobi[344];		/* �\��			*/
	char	c_filler[511];		/* FILLER 		*/
	char	c_kaigyo[1];		/* ���s����		*/ 
};

/*===============================================================*/
/*		����													 */
/*===============================================================*/
/*--- S-JIS�p�\���� ---*/

struct	Z02SJIR1 {			/* PNC����M���� 	*/
	char	c_sbt[2];			/* ں��ގ��ʋ敪 	*/
	char	c_bml_ymd[8];		/* BML��t�N���� 	*/
	char	c_irai_no[11];		/* �˗���No 		*/
	char	c_siset_cd[7];		/* �{�ݺ��� 		*/
	char	c_subsiset_cd[4];	/* ��ގ{�ݺ��� 		*/
	char	c_card1_kbn[2];		/* ���ދ敪1 		*/
	char	c_card2_kbn[2];		/* ���ދ敪2 		*/
	char	c_iraimoto_key[20];	/* �˗����� 		*/
	char	c_ka_cd[3];			/* �f�ÉȺ��� 		*/
	char	c_ka_nm[15];		/* �f�ÉȖ� 		*/
	char	c_dr_cd[8];			/* �S���㺰�� 		*/
	char	c_dr_nm[15];		/* �S���㖼 		*/
	char	c_karte_no[15];		/* ���No 		*/
	char	c_kanja_id[15];		/* ����ID 		*/
	char	c_kanja_nm[20];		/* ���Җ� 		*/
	char	c_kanja_knm[20];	/* ���Җ��i�����j 	*/
	char	c_tall[5];			/* �g�� 		*/
	char	c_weight[5];		/* �̏d 		*/
	char	c_weight_kbn[1];	/* �̏d�P�� 		*/
	char	c_sex[1];			/* ���ʋ敪 		*/
	char	c_birth_ymd[8];		/* ���N���� 		*/
	char	c_birth_kbn[1];		/* ���N�����敪 	*/
	char	c_age[3];			/* �N�� 		*/
	char	c_age_kbn[1];		/* �N��敪 		*/
	char	c_byoto_cd[5];		/* �a������ 		*/
	char	c_byoto_nm[15];		/* �a���� 		*/
	char	c_ukecmt1_cd[2];	/* ��t���ĺ���1 	*/
	char	c_ukecmt2_cd[2];	/* ��t���ĺ���2 	*/
	char	c_ukecmt3_cd[2];	/* ��t���ĺ���3 	*/
	char	c_ukecmt1_cmt[20]; 	/* ��t�����ذ1 	*/
	char	c_ukecmt2_cmt[20]; 	/* ��t�����ذ2 	*/
	char	c_ng_kbn[1];		/* ���O�敪 		*/
	char	c_ninsin_cnt[2];	/* �D�P�T�� 		*/
	char	c_hoken_cd[1];		/* �ی����� 		*/
	char	c_zairyo01_cd[3];	/* �ޗ�����1 		*/
	char	c_zairyo02_cd[3];	/* �ޗ�����2 		*/
	char	c_zairyo03_cd[3];	/* �ޗ�����3 		*/
	char	c_zairyo04_cd[3];	/* �ޗ�����4 		*/
	char	c_zairyo05_cd[3];	/* �ޗ�����5 		*/
	char	c_zairyo06_cd[3];	/* �ޗ�����6 		*/
	char	c_zairyo07_cd[3];	/* �ޗ�����7 		*/
	char	c_zairyo08_cd[3];	/* �ޗ�����8 		*/
	char	c_zairyo09_cd[3];	/* �ޗ�����9 		*/
	char	c_zairyo10_cd[3];	/* �ޗ�����10 		*/
	char	c_yokisu01[2];		/* �{���i�e�퐔�j1 	*/
	char	c_yokisu02[2];		/* �{���i�e�퐔�j2 	*/
	char	c_yokisu03[2];		/* �{���i�e�퐔�j3 	*/
	char	c_yokisu04[2];		/* �{���i�e�퐔�j4 	*/
	char	c_yokisu05[2];		/* �{���i�e�퐔�j5 	*/
	char	c_yokisu06[2];		/* �{���i�e�퐔�j6 	*/
	char	c_yokisu07[2];		/* �{���i�e�퐔�j7 	*/
	char	c_yokisu08[2];		/* �{���i�e�퐔�j8 	*/
	char	c_yokisu09[2];		/* �{���i�e�퐔�j9 	*/
	char	c_yokisu10[2];		/* �{���i�e�퐔�j10 	*/
	char	c_saisyu_time[4];	/* �̎掞�� 		*/
	char	c_saisyu_ymd[8];	/* �̎�N���� 		*/
	char	c_nyotime[4];		/* �~�A���� 		*/
	char	c_nyotime_kbn[1];	/* �~�A���ԁi�P�ʁj 	*/
	char	c_nyoryo[5];		/* �~�A�� 		*/
	char	c_nyoryo_kbn[1];	/* �~�A�ʁi�P�ʁj 	*/
	char	c_tochak_ymd[8];	/* ���̓����\��� 	*/
	char	c_imoto_lab[3];		/* �˗���ID 		*/
	char	c_hsaki_lab1[3];	/* �񍐐�ID�P 		*/
	char	c_hsaki_lab2[3];	/* �񍐐�ID�Q 		*/
	char	c_hsaki_lab3[3];	/* �񍐐�ID�R 		*/
	char	c_gmoto_lab1[3];	/* �O����ID1 		*/
	char	c_gmoto_lab2[3];	/* �O����ID2 		*/
	char	c_gmoto_lab3[3];	/* �O����ID3 		*/
	char	c_gmoto_lab4[3];	/* �O����ID4 		*/
	char	c_gmoto_lab5[3];	/* �O����ID5 		*/
	char	c_gsaki_lab[3];		/* �O����ID 		*/
	char	c_verify_kbn[1];	/* ���̧��󋵋敪 	*/
	char	c_zokdel_flg[1];	/* �����폜�׸� 	*/
	char	c_zokupd_flg[1];	/* �����C���׸� 	*/
	char	c_kinkyu_flg[1];	/* �ً}�˗��׸� 	*/
	char	c_add_flg[1];		/* �ǉ��L���׸� 	*/
	char	c_hikensa_kbn[1];	/* �񌟍��敪 		*/
	char	c_uketuke_kbn[1];	/* ��t�敪 		*/
	char	c_ne_kbn[1];		/* NE�敪 		*/
	char	c_hifd_flg[1];		/* FD����׸� 	*/
	char	c_kakucho_flg[1];	/* �g������DB�����׸� 	*/
	char	c_uke_time[4];		/* ��t���� 		*/
	char	c_ope_ymd[8];		/* �����N���� 		*/
	char	c_obmluke_ymd[8];	/* ��BML��t�N���� 	*/
	char	c_oirai_no[11];		/* ���˗���NO 		*/
	char	c_eigyo_cd[3];		/* �c�Ə����� 		*/
	char	c_syuhai_cd[2];		/* �W�z���� 		*/
	char	c_siset_knm[40];	/* �{�ݖ��������́i�����j*/
	char	c_siset_nm[20];		/* �{�ݖ��������́i�Łj */
	char	c_sisetr_knm[20];	/* �{�ݖ����́i�����j 	*/
	char	c_sisetr_nm[10];	/* �{�ݖ����́i�Łj 	*/
	char	c_siset_kbn[2];		/* �{�ݎ�� 		*/
	char	c_tokutei_flg[1];	/* ����{���׸� 	*/
	char	c_riyu_cd[1];		/* ���R���� 		*/
	char	c_kmax[3];			/* �˗����ڐ� 		*/
	char	c_kjlab1_cd[3];		/* �������{��޺��ނP 	*/
	char	c_kjlab2_cd[3];		/* �������{��޺��ނQ 	*/
	char	c_kjlab3_cd[3];		/* �������{��޺��ނR 	*/
	char	c_hokoku_no[2];		/* ������NO 		*/
	char	c_yoyaku[12];		/* �\��̨���� 		*/
	char	c_filler[478];		/* FILLER 		*/
	char	c_kaigyo[1];		/* ���s����		*/ 
};

struct	Z03SJKOU {			/* PNC����M���� 	*/
	char	c_bml_ymd[8];		/* BML��t�N���� 	*/
	char	c_irai_no[11];		/* �˗���No 		*/
	char	c_koumoku_cd[7];	/* ���ں��� 		*/
	char	c_kentai_no[11];	/* ����NO 		*/
	char	c_kentai_ch[2];		/* ������������ 	*/
	char	c_szairyo_cd[3];	/* ����ޗ����� 	*/
	char	c_koumoku_rnm[8];	/* ���ږ����� 		*/
	char	c_oya_cd[7];		/* �e���ں��� 		*/
	char	c_set_cd[7];		/* ��č��ں��� 		*/
	char	c_hisyokai_flg[1];	/* ��Ɖ��׸� 		*/
	char	c_hiseikyu_kbn[1];	/* �񐿋��敪 		*/
	char	c_hihokok_flg[1];	/* ����׸� 		*/
	char	c_naiyo_cd[1];		/* �������e���� 	*/
	char	c_section_cd[2];	/* ����ݺ��� 		*/
	char	c_outchk_flg[1];	/* �o�������׸� 	*/
	char	c_bunkaku_kbn[1];	/* ���敉�׋敪 	*/
	char	c_yusen_lvl[2];		/* �D������ 		*/
	char	c_add_flg[1];		/* �ǉ��׸� 		*/
	char	c_del_flg[1];		/* �폜�׸� 		*/
	char	c_jokenadd_flg[1];	/* �����t�ǉ��׸� 	*/
	char	c_kakucho_flg[1];	/* �g������DB���ʺ��� 	*/
	char	c_fdkekka_flg[1];	/* FD�g������DB���ʺ��� */
	char	c_kjlab_cd[3];		/* �������{��޺��� 	*/
	char	c_uketuke_kbn[1];	/* ��t�敪 		*/
	char	c_kinkyu_gp[1];		/* �ً}��ٰ�� 		*/
	char	c_base_no[3];		/* ��lNO 		*/
	char	c_fuka_no[1];		/* ���ו�NO�\��	*/
	char	c_serial_no[5];		/* �o�͏��ر�NO 	*/
	char	c_hiteke_time[12];	/* ���^���׎��� 	*/
	char	c_ope_ymd[8];		/* �����N���� 		*/
	char	c_ws_cd[4];			/* W/S����		*/
	char	c_lgtoket_flg[1];	/* ��ފO�������U���׸� 	*/
	char	c_sateraito[3];		/* ������ײ�ID 		*/
	char	c_toseki_flg[1];	/* �����׸� 		*/
	char	c_toketu_flg[1];	/* �����׸� 		*/
	char	c_buncyu_kbn[1];	/* �����敪 		*/
	char	c_nbuncyu_kbn[1];	/* �A�����敪 		*/
	char	c_kinkou_flg[1];	/* �ً}�����׸� 	*/
	char	c_toukou_flg[1];	/* ���������׸� 	*/
	char	c_yoyaku[31];		/* �\��̨���� 		*/
};

struct  Z03SJIR5        {       /* �˗�����M�o�m�b̫�ϯ�(�זE�f�p�j*/
    char    c_sbt[2];       	/* ں��ގ��ʎq([R5]�Œ�)*/
    struct  Z03SJKOU        kou[IRAI_MAX];
    char	c_filler[61]; 		/* 1�ް����ɕ������ڂ���Ă���Ă���*/
	char	c_kaigyo[1];		/* ���s����		*/ 
};

struct  Z04SJIR2        {       /* �˗�����M�o�m�b̫�ϯ�(�����g��)*/
    char    c_sbt[2];       	/* ں��ގ��ʎq([R2]�Œ�)*/
	char    c_bml_ymd[8];       /* BML��t�N����    */
	char    c_irai_no[11];      /* �˗���No         */
	char    c_protcol_no[11];   /* protcolNo         */
	char    c_ko_siset_cd[7];   /* �q�{�݃R�[�h      */
	char    c_toyotime[4];   	/* ���^����     	 */
	char    c_toyoryo[5];   	/* ���^��     		 */
	char    c_toyoryo_kbn[3];  	/* ���^�ʒP��  	    */
	char    c_drfuka_time[4];  	/* ��ܕ��׎���	    */
	char    c_ikassay_flg[1];  	/* �ꊇ�A�b�Z�C�t���O	    */
	char    c_kentai_su[2];  	/* ���̐�	    */
	char    c_komoku_su[3];  	/* ���ڐ�	    */
	char    c_saisyu_po[2];  	/* �̎�|�C���g	    */
	char    c_zairyo01_cd[5];  	/* �ޗ��R�[�h�P	    */
	char    c_zairyo02_cd[5];  	/* �ޗ��R�[�h�P	    */
	char    c_zairyo03_cd[5];  	/* �ޗ��R�[�h�P	    */
	char    c_zairyo04_cd[5];  	/* �ޗ��R�[�h�P	    */
	char    c_zairyo05_cd[5];  	/* �ޗ��R�[�h�P	    */
	char    c_zairyo06_cd[5];  	/* �ޗ��R�[�h�P	    */
	char    c_zairyo01_kg[1];  	/* �ޗ��R�[�h�P�L�� */
	char    c_zairyo02_kg[1];  	/* �ޗ��R�[�h�P�L�� */
	char    c_zairyo03_kg[1];  	/* �ޗ��R�[�h�P�L�� */
	char    c_zairyo04_kg[1];  	/* �ޗ��R�[�h�P�L�� */
	char    c_zairyo05_kg[1];  	/* �ޗ��R�[�h�P�L�� */
	char    c_zairyo06_kg[1];  	/* �ޗ��R�[�h�P�L�� */
	char    c_horyu_seq[4];  	/* �ۗ��V�[�P���X */
	char    c_kaisyu_flg[1];  	/* ���̉���t���O */
	char    c_gcp_flg[1];  		/* GCP�t���O */
	char    c_protocol_knm[40]; /* �v���g�R�������� */
	char	c_yoyaku[53];		/* �\��̨����       */
	char    c_filler[825];      /* FILLER       */
	char	c_kaigyo[1];		/* ���s����		*/ 
};

/*===============================================================*/
/*		���ʈ˗����i�����w�j									 */
/*===============================================================*/
/*--- S-JIS�p�\���� ---*/

struct  Z05SJIR1        {       /* �˗�����M�o�m�b̫�ϯ�(�זE�f�p�j*/
    char    c_sbt[2];       	/* ں��ގ��ʎq([R1]�Œ�)*/
	char	c_bml_ymd[8];		/* BML��t�N���� 	*/
	char	c_irai_no[11];		/* �˗���No 		*/
	char	c_koumoku_cd[7];	/* ���ں��� 		*/
	char	c_kentai_no[11];	/* ����NO 		*/
	char	c_kentai_ch[2];		/* ������������ 	*/
	char	c_szairyo_cd[3];	/* ����ޗ����� 	*/
	char	c_koumoku_rnm[8];	/* ���ږ����� 		*/
	char	c_oya_cd[7];		/* �e���ں��� 		*/
	char	c_set_cd[7];		/* ��č��ں��� 		*/
	char	c_hisyokai_flg[1];	/* ��Ɖ��׸� 		*/
	char	c_hiseikyu_kbn[1];	/* �񐿋��敪 		*/
	char	c_hihokok_flg[1];	/* ����׸� 		*/
	char	c_naiyo_cd[1];		/* �������e���� 	*/
	char	c_section_cd[2];	/* ����ݺ��� 		*/
	char	c_outchk_flg[1];	/* �o�������׸� 	*/
	char	c_bunkaku_kbn[1];	/* ���敉�׋敪 	*/
	char	c_yusen_lvl[2];		/* �D������ 		*/
	char	c_add_flg[1];		/* �ǉ��׸� 		*/
	char	c_del_flg[1];		/* �폜�׸� 		*/
	char	c_jokenadd_flg[1];	/* �����t�ǉ��׸� 	*/
	char	c_kakucho_flg[1];	/* �g������DB���ʺ��� 	*/
	char	c_fdkekka_flg[1];	/* FD�g������DB���ʺ��� */
	char	c_kjlab_cd[3];		/* �������{��޺��� 	*/
	char	c_uketuke_kbn[1];	/* ��t�敪 		*/
	char	c_kinkyu_gp[1];		/* �ً}��ٰ�� 		*/
	char	c_base_no[3];		/* ��lNO 		*/
	char	c_fuka_no[1];		/* ���ו�NO�\��	*/
	char	c_serial_no[5];		/* �o�͏��ر�NO 	*/
	char	c_hiteke_time[12];	/* ���^���׎��� 	*/
	char	c_ope_ymd[8];		/* �����N���� 		*/
	char	c_ws_cd[4];			/* W/S����		*/
	char	c_lgtoket_flg[1];	/* ��ފO�������U���׸� 	*/
	char	c_sateraito[3];		/* ������ײ�ID 		*/
	char	c_toseki_flg[1];	/* �����׸� 		*/
	char	c_toketu_flg[1];	/* �����׸� 		*/
	char	c_buncyu_kbn[1];	/* �����敪 		*/
	char	c_nbuncyu_kbn[1];	/* �A�����敪 		*/
	char	c_kinkou_flg[1];	/* �ً}�����׸� 	*/
	char	c_toukou_flg[1];	/* ���������׸� 	*/
	char	c_yoyaku[31];		/* �\��̨���� 		*/
	char	c_riyu_cd[1];       /* (�˗�)���R����   */
	char	c_ws_tan[1];		/* 	WS�P��          */
	char    c_sex[1];			/* ���ʋ敪         */
	char    c_age_kbn[1];		/* �N��敪         */
	char    c_age[3];			/* �N��         */
	char    c_nyotime[4];       /* �~�A����         */
    char    c_nyotime_kbn[1];   /* �~�A���ԁi�P�ʁj     */
    char    c_nyoryo[5];        /* �~�A��       */
    char    c_nyoryo_kbn[1];    /* �~�A�ʁi�P�ʁj   */
	char    c_siset_cd[7];      /* �{�ݺ���         */
	char    c_eigyo_cd[3];      /* �c�Ə�����       */
    char	c_filler[835]; 
	char	c_kaigyo[1];		/* ���s����		*/ 
};

struct	Z11SJIRF {		/* END���			*/
	char	c_sbt[2];			/* ں��ގ��ʋ敪	*/
	char	c_end[3];			/* 'END'�Œ�		*/
	char	c_ope_ymd[8];		/* �����N����		*/
	char	c_filler[1010];		/* ̨װ			*/
	char	c_kaigyo[1];		/* ���s����		*/ 
};

/*===============================================================*/
/*		�v���J�[�h           									 */
/*===============================================================*/
/*--- S-JIS�p�\���� ---*/

struct  Z12SJR1        {       /* �v���J�[�h�o�m�b̫�ϯ� */
    char    c_sbt[2];       	/* ں��ގ��ʎq([R1]�Œ�)*/
	char	c_opedate[8];		/* ���M�������N����	*/
	char	c_sateraito[3];		/* ������ײ�ID 		*/
	char	c_yokyu_kbn[1];		/* BML��t�N���� 	*/
    char	c_filler[1009]; 
	char	c_kaigyo[1];		/* ���s����		*/ 
};

#endif
