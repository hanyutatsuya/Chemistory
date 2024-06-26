/******************************************************************************/
/*   alklü¯¸VXe                                                 */
/*                                                                            */
/*   VXe¼F¢ãVXe                                               */
/*   t@C¼FtagPNC.h                                                     */
/*   T      vFombóMt@C\¢Ìè`                                 */
/******************************************************************************/
/*  Ver.     út           ¼O           C³àe                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/******************************************************************************/
#ifndef _TAGPNC_H
#define _TAGPNC_H

#define	PNC_RECSIZE		1024
#define	IRAI_MAX	6
#define	ERR_MAX		10

/******************************************************************************/
/* \¢Ìè`                                                                 */
/******************************************************************************/
/*====== PNCóMÌ§²Ù ==========================================
	Úº°ÄÞ¯Êq	\¢Ì¼		àe
-----------------------------------------------------------------
		HD	Z00SJHD		Ì§²ÙÍ¯ÀÞ°
		TR	Z01SJTR		Ì§²ÙÄÚ°×°
		R1	Z02SJIR1	Ë®«
		R5	Z03SJIR5	ËÚ(PCL)
		R2	Z04SJIR2	¡±g£
		R1	Z05SJIR1	ÊËÚ
		RF  Z11SJIRF	ENDîñiËj
		R1  Z12SJR1		vJ[h
=================================================================*/

/*===============================================================*/
/*		¤Ê													 */
/*===============================================================*/
/*--- S-JISp\¢Ì ---*/
struct	Z00SJHD		{	/* ÎPNCóMÍ¯ÀÞ°(S-JISj 1024byte*/
	char	c_sbt[2];		/* Úº°ÄÞ¯Êq([HD]Åè)*/
	char	c_sosinsaki[8];		/* Mæ		*/
	char	c_sosinmoto[8];		/* M³		*/
	char	c_opedate[8];		/* M³Nú	*/
	char	c_tuban[4];			/* ÊÔ			*/
	char	c_dflow[10];		/* ÃÞ°ÀÌÛ°ID		*/
	char	c_param1[128];		/* Êß×Ò°À1		*/
	char	c_param2[128];		/* Êß×Ò°À2		*/
	char	c_yobi[216];		/* \õ			*/
	char	c_filler[511];		/* FILLER 		*/
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};
struct	Z01SJTR		{	/* ÎPNCóMÄÚ°×°(S-JISj 1024byte*/
	char	c_sbt[2];		/* Úº°ÄÞ¯Êq([TR]Åè)*/
	char	c_sosinsaki[8];		/* Mæ		*/
	char	c_sosinmoto[8];		/* M³		*/
	char	c_opedate[8];		/* M³Nú	*/
	char	c_tuban[4];			/* ÊÔ			*/
	char	c_dflow[10];		/* ÃÞ°ÀÌÛ°ID		*/
	char	c_reccnt[8];		/* ¨Úº°ÄÞ	*/
	char	c_reccnt01[8];		/* _Úº°ÄÞP	*/
	char	c_reccnt02[8];		/* _Úº°ÄÞQ	*/
	char	c_reccnt03[8];		/* _Úº°ÄÞR	*/
	char	c_reccnt04[8];		/* _Úº°ÄÞS	*/
	char	c_reccnt05[8];		/* _Úº°ÄÞT	*/
	char	c_reccnt06[8];		/* _Úº°ÄÞU	*/
	char	c_reccnt07[8];		/* _Úº°ÄÞV	*/
	char	c_reccnt08[8];		/* _Úº°ÄÞW	*/
	char	c_reccnt09[8];		/* _Úº°ÄÞX	*/
	char	c_reccnt10[8];		/* _Úº°ÄÞPO	*/
	char	c_reccnt11[8];		/* _Úº°ÄÞPP	*/
	char	c_reccnt12[8];		/* _Úº°ÄÞPQ	*/
	char	c_reccnt13[8];		/* _Úº°ÄÞPR	*/
	char	c_reccnt14[8];		/* _Úº°ÄÞPS  	*/
	char	c_reccnt15[8];		/* _Úº°ÄÞPT	*/
	char	c_yobi[344];		/* \õ			*/
	char	c_filler[511];		/* FILLER 		*/
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

/*===============================================================*/
/*		®«													 */
/*===============================================================*/
/*--- S-JISp\¢Ì ---*/

struct	Z02SJIR1 {			/* PNCóM®« 	*/
	char	c_sbt[2];			/* Úº°ÄÞ¯Êæª 	*/
	char	c_bml_ymd[8];		/* BMLótNú 	*/
	char	c_irai_no[11];		/* ËNo 		*/
	char	c_siset_cd[7];		/* {Ýº°ÄÞ 		*/
	char	c_subsiset_cd[4];	/* »ÌÞ{Ýº°ÄÞ 		*/
	char	c_card1_kbn[2];		/* ¶°ÄÞæª1 		*/
	char	c_card2_kbn[2];		/* ¶°ÄÞæª2 		*/
	char	c_iraimoto_key[20];	/* Ë³·° 		*/
	char	c_ka_cd[3];			/* fÃÈº°ÄÞ 		*/
	char	c_ka_nm[15];		/* fÃÈ¼ 		*/
	char	c_dr_cd[8];			/* Sãº°ÄÞ 		*/
	char	c_dr_nm[15];		/* Sã¼ 		*/
	char	c_karte_no[15];		/* ¶ÙÃNo 		*/
	char	c_kanja_id[15];		/* ³ÒID 		*/
	char	c_kanja_nm[20];		/* ³Ò¼ 		*/
	char	c_kanja_knm[20];	/* ³Ò¼i¿j 	*/
	char	c_tall[5];			/* g· 		*/
	char	c_weight[5];		/* Ìd 		*/
	char	c_weight_kbn[1];	/* ÌdPÊ 		*/
	char	c_sex[1];			/* «Êæª 		*/
	char	c_birth_ymd[8];		/* ¶Nú 		*/
	char	c_birth_kbn[1];		/* ¶Núæª 	*/
	char	c_age[3];			/* Nî 		*/
	char	c_age_kbn[1];		/* Nîæª 		*/
	char	c_byoto_cd[5];		/* aº°ÄÞ 		*/
	char	c_byoto_nm[15];		/* a¼ 		*/
	char	c_ukecmt1_cd[2];	/* ótºÒÝÄº°ÄÞ1 	*/
	char	c_ukecmt2_cd[2];	/* ótºÒÝÄº°ÄÞ2 	*/
	char	c_ukecmt3_cd[2];	/* ótºÒÝÄº°ÄÞ3 	*/
	char	c_ukecmt1_cmt[20]; 	/* ótºÒÝÄÌØ°1 	*/
	char	c_ukecmt2_cmt[20]; 	/* ótºÒÝÄÌØ°2 	*/
	char	c_ng_kbn[1];		/* üOæª 		*/
	char	c_ninsin_cnt[2];	/* DPT 		*/
	char	c_hoken_cd[1];		/* Û¯º°ÄÞ 		*/
	char	c_zairyo01_cd[3];	/* Þ¿º°ÄÞ1 		*/
	char	c_zairyo02_cd[3];	/* Þ¿º°ÄÞ2 		*/
	char	c_zairyo03_cd[3];	/* Þ¿º°ÄÞ3 		*/
	char	c_zairyo04_cd[3];	/* Þ¿º°ÄÞ4 		*/
	char	c_zairyo05_cd[3];	/* Þ¿º°ÄÞ5 		*/
	char	c_zairyo06_cd[3];	/* Þ¿º°ÄÞ6 		*/
	char	c_zairyo07_cd[3];	/* Þ¿º°ÄÞ7 		*/
	char	c_zairyo08_cd[3];	/* Þ¿º°ÄÞ8 		*/
	char	c_zairyo09_cd[3];	/* Þ¿º°ÄÞ9 		*/
	char	c_zairyo10_cd[3];	/* Þ¿º°ÄÞ10 		*/
	char	c_yokisu01[2];		/* {ieíj1 	*/
	char	c_yokisu02[2];		/* {ieíj2 	*/
	char	c_yokisu03[2];		/* {ieíj3 	*/
	char	c_yokisu04[2];		/* {ieíj4 	*/
	char	c_yokisu05[2];		/* {ieíj5 	*/
	char	c_yokisu06[2];		/* {ieíj6 	*/
	char	c_yokisu07[2];		/* {ieíj7 	*/
	char	c_yokisu08[2];		/* {ieíj8 	*/
	char	c_yokisu09[2];		/* {ieíj9 	*/
	char	c_yokisu10[2];		/* {ieíj10 	*/
	char	c_saisyu_time[4];	/* ÌæÔ 		*/
	char	c_saisyu_ymd[8];	/* ÌæNú 		*/
	char	c_nyotime[4];		/* ~AÔ 		*/
	char	c_nyotime_kbn[1];	/* ~AÔiPÊj 	*/
	char	c_nyoryo[5];		/* ~AÊ 		*/
	char	c_nyoryo_kbn[1];	/* ~AÊiPÊj 	*/
	char	c_tochak_ymd[8];	/* Ì\èú 	*/
	char	c_imoto_lab[3];		/* Ë³ID 		*/
	char	c_hsaki_lab1[3];	/* ñæIDP 		*/
	char	c_hsaki_lab2[3];	/* ñæIDQ 		*/
	char	c_hsaki_lab3[3];	/* ñæIDR 		*/
	char	c_gmoto_lab1[3];	/* O³ID1 		*/
	char	c_gmoto_lab2[3];	/* O³ID2 		*/
	char	c_gmoto_lab3[3];	/* O³ID3 		*/
	char	c_gmoto_lab4[3];	/* O³ID4 		*/
	char	c_gmoto_lab5[3];	/* O³ID5 		*/
	char	c_gsaki_lab[3];		/* OæID 		*/
	char	c_verify_kbn[1];	/* ÍÞØÌ§²óµæª 	*/
	char	c_zokdel_flg[1];	/* ®«íÌ×¸Þ 	*/
	char	c_zokupd_flg[1];	/* ®«C³Ì×¸Þ 	*/
	char	c_kinkyu_flg[1];	/* Ù}ËÌ×¸Þ 	*/
	char	c_add_flg[1];		/* ÇÁL³Ì×¸Þ 	*/
	char	c_hikensa_kbn[1];	/* ñ¸æª 		*/
	char	c_uketuke_kbn[1];	/* ótæª 		*/
	char	c_ne_kbn[1];		/* NEæª 		*/
	char	c_hifd_flg[1];		/* FDññÌ×¸Þ 	*/
	char	c_kakucho_flg[1];	/* g£®«DB¯ÊÌ×¸Þ 	*/
	char	c_uke_time[4];		/* ót 		*/
	char	c_ope_ymd[8];		/* Nú 		*/
	char	c_obmluke_ymd[8];	/* ³BMLótNú 	*/
	char	c_oirai_no[11];		/* ³ËNO 		*/
	char	c_eigyo_cd[3];		/* cÆº°ÄÞ 		*/
	char	c_syuhai_cd[2];		/* Wzº°ÄÞ 		*/
	char	c_siset_knm[40];	/* {Ý¼³®¼Ìi¿j*/
	char	c_siset_nm[20];		/* {Ý¼³®¼Ìi¶Åj */
	char	c_sisetr_knm[20];	/* {Ý¼ªÌi¿j 	*/
	char	c_sisetr_nm[10];	/* {Ý¼ªÌi¶Åj 	*/
	char	c_siset_kbn[2];		/* {ÝíÊ 		*/
	char	c_tokutei_flg[1];	/* Áè{ÝÌ×¸Þ 	*/
	char	c_riyu_cd[1];		/* Rº°ÄÞ 		*/
	char	c_kmax[3];			/* ËÚ 		*/
	char	c_kjlab1_cd[3];		/* ¸À{×ÎÞº°ÄÞP 	*/
	char	c_kjlab2_cd[3];		/* ¸À{×ÎÞº°ÄÞQ 	*/
	char	c_kjlab3_cd[3];		/* ¸À{×ÎÞº°ÄÞR 	*/
	char	c_hokoku_no[2];		/* úñNO 		*/
	char	c_yoyaku[12];		/* \ñÌ¨°ÙÄÞ 		*/
	char	c_filler[478];		/* FILLER 		*/
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

struct	Z03SJKOU {			/* PNCóMÚ 	*/
	char	c_bml_ymd[8];		/* BMLótNú 	*/
	char	c_irai_no[11];		/* ËNo 		*/
	char	c_koumoku_cd[7];	/* Úº°ÄÞ 		*/
	char	c_kentai_no[11];	/* ÌNO 		*/
	char	c_kentai_ch[2];		/* ÌÁª¯¸¶ 	*/
	char	c_szairyo_cd[3];	/* èÞ¿º°ÄÞ 	*/
	char	c_koumoku_rnm[8];	/* Ú¼ªÌ 		*/
	char	c_oya_cd[7];		/* eÚº°ÄÞ 		*/
	char	c_set_cd[7];		/* ¾¯ÄÚº°ÄÞ 		*/
	char	c_hisyokai_flg[1];	/* ñÆïÌ×¸Þ 		*/
	char	c_hiseikyu_kbn[1];	/* ñ¿æª 		*/
	char	c_hihokok_flg[1];	/* ññÌ×¸Þ 		*/
	char	c_naiyo_cd[1];		/* àeº°ÄÞ 	*/
	char	c_section_cd[2];	/* ¾¸¼®Ýº°ÄÞ 		*/
	char	c_outchk_flg[1];	/* o×Áª¯¸Ì×¸Þ 	*/
	char	c_bunkaku_kbn[1];	/* ªæ×æª 	*/
	char	c_yusen_lvl[2];		/* DæÚÍÞÙ 		*/
	char	c_add_flg[1];		/* ÇÁÌ×¸Þ 		*/
	char	c_del_flg[1];		/* íÌ×¸Þ 		*/
	char	c_jokenadd_flg[1];	/* ðtÇÁÌ×¸Þ 	*/
	char	c_kakucho_flg[1];	/* g£ÊDB¯Êº°ÄÞ 	*/
	char	c_fdkekka_flg[1];	/* FDg£ÊDB¯Êº°ÄÞ */
	char	c_kjlab_cd[3];		/* ¸À{×ÎÞº°ÄÞ 	*/
	char	c_uketuke_kbn[1];	/* ótæª 		*/
	char	c_kinkyu_gp[1];		/* Ù}¸ÞÙ°Ìß 		*/
	char	c_base_no[3];		/* îlNO 		*/
	char	c_fuka_no[1];		/* ×ñNO\¦	*/
	char	c_serial_no[5];		/* oÍ¼Ø±ÙNO 	*/
	char	c_hiteke_time[12];	/* ñè^×Ô 	*/
	char	c_ope_ymd[8];		/* Nú 		*/
	char	c_ws_cd[4];			/* W/Sº°ÄÞ		*/
	char	c_lgtoket_flg[1];	/* ×ÎÞOUÖÌ×¸Þ 	*/
	char	c_sateraito[3];		/* ¸»Ã×²ÄID 		*/
	char	c_toseki_flg[1];	/* §ÍÌ×¸Þ 		*/
	char	c_toketu_flg[1];	/* Ì×¸Þ 		*/
	char	c_buncyu_kbn[1];	/* ªæª 		*/
	char	c_nbuncyu_kbn[1];	/* Aªæª 		*/
	char	c_kinkou_flg[1];	/* Ù}ÚÌ×¸Þ 	*/
	char	c_toukou_flg[1];	/* úÚÌ×¸Þ 	*/
	char	c_yoyaku[31];		/* \ñÌ¨°ÙÄÞ 		*/
};

struct  Z03SJIR5        {       /* ËóMombÌ«°Ï¯Ä(×Efpj*/
    char    c_sbt[2];       	/* Úº°ÄÞ¯Êq([R5]Åè)*/
    struct  Z03SJKOU        kou[IRAI_MAX];
    char	c_filler[61]; 		/* 1ÃÞ°ÀÉ¡Úª¾¯Ä³êÄ¢é*/
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

struct  Z04SJIR2        {       /* ËóMombÌ«°Ï¯Ä(¡±g£)*/
    char    c_sbt[2];       	/* Úº°ÄÞ¯Êq([R2]Åè)*/
	char    c_bml_ymd[8];       /* BMLótNú    */
	char    c_irai_no[11];      /* ËNo         */
	char    c_protcol_no[11];   /* protcolNo         */
	char    c_ko_siset_cd[7];   /* q{ÝR[h      */
	char    c_toyotime[4];   	/* ^Ô     	 */
	char    c_toyoryo[5];   	/* ^Ê     		 */
	char    c_toyoryo_kbn[3];  	/* ^ÊPÊ  	    */
	char    c_drfuka_time[4];  	/* òÜ×Ô	    */
	char    c_ikassay_flg[1];  	/* êAbZCtO	    */
	char    c_kentai_su[2];  	/* Ì	    */
	char    c_komoku_su[3];  	/* Ú	    */
	char    c_saisyu_po[2];  	/* Ìæ|Cg	    */
	char    c_zairyo01_cd[5];  	/* Þ¿R[hP	    */
	char    c_zairyo02_cd[5];  	/* Þ¿R[hP	    */
	char    c_zairyo03_cd[5];  	/* Þ¿R[hP	    */
	char    c_zairyo04_cd[5];  	/* Þ¿R[hP	    */
	char    c_zairyo05_cd[5];  	/* Þ¿R[hP	    */
	char    c_zairyo06_cd[5];  	/* Þ¿R[hP	    */
	char    c_zairyo01_kg[1];  	/* Þ¿R[hPL */
	char    c_zairyo02_kg[1];  	/* Þ¿R[hPL */
	char    c_zairyo03_kg[1];  	/* Þ¿R[hPL */
	char    c_zairyo04_kg[1];  	/* Þ¿R[hPL */
	char    c_zairyo05_kg[1];  	/* Þ¿R[hPL */
	char    c_zairyo06_kg[1];  	/* Þ¿R[hPL */
	char    c_horyu_seq[4];  	/* Û¯V[PX */
	char    c_kaisyu_flg[1];  	/* ÌñûtO */
	char    c_gcp_flg[1];  		/* GCPtO */
	char    c_protocol_knm[40]; /* vgR¿¼ */
	char	c_yoyaku[53];		/* \ñÌ¨°ÙÄÞ       */
	char    c_filler[825];      /* FILLER       */
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

/*===============================================================*/
/*		ÊËîñi¶»wj									 */
/*===============================================================*/
/*--- S-JISp\¢Ì ---*/

struct  Z05SJIR1        {       /* ËóMombÌ«°Ï¯Ä(×Efpj*/
    char    c_sbt[2];       	/* Úº°ÄÞ¯Êq([R1]Åè)*/
	char	c_bml_ymd[8];		/* BMLótNú 	*/
	char	c_irai_no[11];		/* ËNo 		*/
	char	c_koumoku_cd[7];	/* Úº°ÄÞ 		*/
	char	c_kentai_no[11];	/* ÌNO 		*/
	char	c_kentai_ch[2];		/* ÌÁª¯¸¶ 	*/
	char	c_szairyo_cd[3];	/* èÞ¿º°ÄÞ 	*/
	char	c_koumoku_rnm[8];	/* Ú¼ªÌ 		*/
	char	c_oya_cd[7];		/* eÚº°ÄÞ 		*/
	char	c_set_cd[7];		/* ¾¯ÄÚº°ÄÞ 		*/
	char	c_hisyokai_flg[1];	/* ñÆïÌ×¸Þ 		*/
	char	c_hiseikyu_kbn[1];	/* ñ¿æª 		*/
	char	c_hihokok_flg[1];	/* ññÌ×¸Þ 		*/
	char	c_naiyo_cd[1];		/* àeº°ÄÞ 	*/
	char	c_section_cd[2];	/* ¾¸¼®Ýº°ÄÞ 		*/
	char	c_outchk_flg[1];	/* o×Áª¯¸Ì×¸Þ 	*/
	char	c_bunkaku_kbn[1];	/* ªæ×æª 	*/
	char	c_yusen_lvl[2];		/* DæÚÍÞÙ 		*/
	char	c_add_flg[1];		/* ÇÁÌ×¸Þ 		*/
	char	c_del_flg[1];		/* íÌ×¸Þ 		*/
	char	c_jokenadd_flg[1];	/* ðtÇÁÌ×¸Þ 	*/
	char	c_kakucho_flg[1];	/* g£ÊDB¯Êº°ÄÞ 	*/
	char	c_fdkekka_flg[1];	/* FDg£ÊDB¯Êº°ÄÞ */
	char	c_kjlab_cd[3];		/* ¸À{×ÎÞº°ÄÞ 	*/
	char	c_uketuke_kbn[1];	/* ótæª 		*/
	char	c_kinkyu_gp[1];		/* Ù}¸ÞÙ°Ìß 		*/
	char	c_base_no[3];		/* îlNO 		*/
	char	c_fuka_no[1];		/* ×ñNO\¦	*/
	char	c_serial_no[5];		/* oÍ¼Ø±ÙNO 	*/
	char	c_hiteke_time[12];	/* ñè^×Ô 	*/
	char	c_ope_ymd[8];		/* Nú 		*/
	char	c_ws_cd[4];			/* W/Sº°ÄÞ		*/
	char	c_lgtoket_flg[1];	/* ×ÎÞOUÖÌ×¸Þ 	*/
	char	c_sateraito[3];		/* ¸»Ã×²ÄID 		*/
	char	c_toseki_flg[1];	/* §ÍÌ×¸Þ 		*/
	char	c_toketu_flg[1];	/* Ì×¸Þ 		*/
	char	c_buncyu_kbn[1];	/* ªæª 		*/
	char	c_nbuncyu_kbn[1];	/* Aªæª 		*/
	char	c_kinkou_flg[1];	/* Ù}ÚÌ×¸Þ 	*/
	char	c_toukou_flg[1];	/* úÚÌ×¸Þ 	*/
	char	c_yoyaku[31];		/* \ñÌ¨°ÙÄÞ 		*/
	char	c_riyu_cd[1];       /* (Ë)Rº°ÄÞ   */
	char	c_ws_tan[1];		/* 	WSPÆ          */
	char    c_sex[1];			/* «Êæª         */
	char    c_age_kbn[1];		/* Nîæª         */
	char    c_age[3];			/* Nî         */
	char    c_nyotime[4];       /* ~AÔ         */
    char    c_nyotime_kbn[1];   /* ~AÔiPÊj     */
    char    c_nyoryo[5];        /* ~AÊ       */
    char    c_nyoryo_kbn[1];    /* ~AÊiPÊj   */
	char    c_siset_cd[7];      /* {Ýº°ÄÞ         */
	char    c_eigyo_cd[3];      /* cÆº°ÄÞ       */
    char	c_filler[835]; 
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

struct	Z11SJIRF {		/* ENDîñ			*/
	char	c_sbt[2];			/* Úº°ÄÞ¯Êæª	*/
	char	c_end[3];			/* 'END'Åè		*/
	char	c_ope_ymd[8];		/* Nú		*/
	char	c_filler[1010];		/* Ì¨×°			*/
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

/*===============================================================*/
/*		vJ[h           									 */
/*===============================================================*/
/*--- S-JISp\¢Ì ---*/

struct  Z12SJR1        {       /* vJ[hombÌ«°Ï¯Ä */
    char    c_sbt[2];       	/* Úº°ÄÞ¯Êq([R1]Åè)*/
	char	c_opedate[8];		/* M³Nú	*/
	char	c_sateraito[3];		/* ¸»Ã×²ÄID 		*/
	char	c_yokyu_kbn[1];		/* BMLótNú 	*/
    char	c_filler[1009]; 
	char	c_kaigyo[1];		/* üsº°ÄÞ		*/ 
};

#endif
