/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：tagPNC.h                                                     */
/*   概      要：ＰＮＣ受信ファイル構造体定義                                 */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/******************************************************************************/
#ifndef _TAGPNC_H
#define _TAGPNC_H

#define	PNC_RECSIZE		1024
#define	IRAI_MAX	6
#define	ERR_MAX		10

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
/*====== PNC送受信ﾌｧｲﾙ ==========================================
	ﾚｺｰﾄﾞ識別子	構造体名		内容
-----------------------------------------------------------------
		HD	Z00SJHD		ﾌｧｲﾙﾍｯﾀﾞｰ
		TR	Z01SJTR		ﾌｧｲﾙﾄﾚｰﾗｰ
		R1	Z02SJIR1	依頼属性
		R5	Z03SJIR5	依頼項目(PCL)
		R2	Z04SJIR2	治験拡張
		R1	Z05SJIR1	結果依頼項目
		RF  Z11SJIRF	END情報（依頼）
		R1  Z12SJR1		要求カード
=================================================================*/

/*===============================================================*/
/*		共通													 */
/*===============================================================*/
/*--- S-JIS用構造体 ---*/
struct	Z00SJHD		{	/* 対PNC送受信ﾍｯﾀﾞｰ(S-JIS） 1024byte*/
	char	c_sbt[2];		/* ﾚｺｰﾄﾞ識別子([HD]固定)*/
	char	c_sosinsaki[8];		/* 送信先		*/
	char	c_sosinmoto[8];		/* 送信元		*/
	char	c_opedate[8];		/* 送信元処理年月日	*/
	char	c_tuban[4];			/* 通番			*/
	char	c_dflow[10];		/* ﾃﾞｰﾀﾌﾛｰID		*/
	char	c_param1[128];		/* ﾊﾟﾗﾒｰﾀ1		*/
	char	c_param2[128];		/* ﾊﾟﾗﾒｰﾀ2		*/
	char	c_yobi[216];		/* 予備			*/
	char	c_filler[511];		/* FILLER 		*/
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};
struct	Z01SJTR		{	/* 対PNC送受信ﾄﾚｰﾗｰ(S-JIS） 1024byte*/
	char	c_sbt[2];		/* ﾚｺｰﾄﾞ識別子([TR]固定)*/
	char	c_sosinsaki[8];		/* 送信先		*/
	char	c_sosinmoto[8];		/* 送信元		*/
	char	c_opedate[8];		/* 送信元処理年月日	*/
	char	c_tuban[4];			/* 通番			*/
	char	c_dflow[10];		/* ﾃﾞｰﾀﾌﾛｰID		*/
	char	c_reccnt[8];		/* 物理ﾚｺｰﾄﾞ件数	*/
	char	c_reccnt01[8];		/* 論理ﾚｺｰﾄﾞ件数１	*/
	char	c_reccnt02[8];		/* 論理ﾚｺｰﾄﾞ件数２	*/
	char	c_reccnt03[8];		/* 論理ﾚｺｰﾄﾞ件数３	*/
	char	c_reccnt04[8];		/* 論理ﾚｺｰﾄﾞ件数４	*/
	char	c_reccnt05[8];		/* 論理ﾚｺｰﾄﾞ件数５	*/
	char	c_reccnt06[8];		/* 論理ﾚｺｰﾄﾞ件数６	*/
	char	c_reccnt07[8];		/* 論理ﾚｺｰﾄﾞ件数７	*/
	char	c_reccnt08[8];		/* 論理ﾚｺｰﾄﾞ件数８	*/
	char	c_reccnt09[8];		/* 論理ﾚｺｰﾄﾞ件数９	*/
	char	c_reccnt10[8];		/* 論理ﾚｺｰﾄﾞ件数１０	*/
	char	c_reccnt11[8];		/* 論理ﾚｺｰﾄﾞ件数１１	*/
	char	c_reccnt12[8];		/* 論理ﾚｺｰﾄﾞ件数１２	*/
	char	c_reccnt13[8];		/* 論理ﾚｺｰﾄﾞ件数１３	*/
	char	c_reccnt14[8];		/* 論理ﾚｺｰﾄﾞ件数１４  	*/
	char	c_reccnt15[8];		/* 論理ﾚｺｰﾄﾞ件数１５	*/
	char	c_yobi[344];		/* 予備			*/
	char	c_filler[511];		/* FILLER 		*/
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

/*===============================================================*/
/*		属性													 */
/*===============================================================*/
/*--- S-JIS用構造体 ---*/

struct	Z02SJIR1 {			/* PNC送受信属性 	*/
	char	c_sbt[2];			/* ﾚｺｰﾄﾞ識別区分 	*/
	char	c_bml_ymd[8];		/* BML受付年月日 	*/
	char	c_irai_no[11];		/* 依頼書No 		*/
	char	c_siset_cd[7];		/* 施設ｺｰﾄﾞ 		*/
	char	c_subsiset_cd[4];	/* ｻﾌﾞ施設ｺｰﾄﾞ 		*/
	char	c_card1_kbn[2];		/* ｶｰﾄﾞ区分1 		*/
	char	c_card2_kbn[2];		/* ｶｰﾄﾞ区分2 		*/
	char	c_iraimoto_key[20];	/* 依頼元ｷｰ 		*/
	char	c_ka_cd[3];			/* 診療科ｺｰﾄﾞ 		*/
	char	c_ka_nm[15];		/* 診療科名 		*/
	char	c_dr_cd[8];			/* 担当医ｺｰﾄﾞ 		*/
	char	c_dr_nm[15];		/* 担当医名 		*/
	char	c_karte_no[15];		/* ｶﾙﾃNo 		*/
	char	c_kanja_id[15];		/* 患者ID 		*/
	char	c_kanja_nm[20];		/* 患者名 		*/
	char	c_kanja_knm[20];	/* 患者名（漢字） 	*/
	char	c_tall[5];			/* 身長 		*/
	char	c_weight[5];		/* 体重 		*/
	char	c_weight_kbn[1];	/* 体重単位 		*/
	char	c_sex[1];			/* 性別区分 		*/
	char	c_birth_ymd[8];		/* 生年月日 		*/
	char	c_birth_kbn[1];		/* 生年月日区分 	*/
	char	c_age[3];			/* 年齢 		*/
	char	c_age_kbn[1];		/* 年齢区分 		*/
	char	c_byoto_cd[5];		/* 病棟ｺｰﾄﾞ 		*/
	char	c_byoto_nm[15];		/* 病棟名 		*/
	char	c_ukecmt1_cd[2];	/* 受付ｺﾒﾝﾄｺｰﾄﾞ1 	*/
	char	c_ukecmt2_cd[2];	/* 受付ｺﾒﾝﾄｺｰﾄﾞ2 	*/
	char	c_ukecmt3_cd[2];	/* 受付ｺﾒﾝﾄｺｰﾄﾞ3 	*/
	char	c_ukecmt1_cmt[20]; 	/* 受付ｺﾒﾝﾄﾌﾘｰ1 	*/
	char	c_ukecmt2_cmt[20]; 	/* 受付ｺﾒﾝﾄﾌﾘｰ2 	*/
	char	c_ng_kbn[1];		/* 入外区分 		*/
	char	c_ninsin_cnt[2];	/* 妊娠週数 		*/
	char	c_hoken_cd[1];		/* 保険ｺｰﾄﾞ 		*/
	char	c_zairyo01_cd[3];	/* 材料ｺｰﾄﾞ1 		*/
	char	c_zairyo02_cd[3];	/* 材料ｺｰﾄﾞ2 		*/
	char	c_zairyo03_cd[3];	/* 材料ｺｰﾄﾞ3 		*/
	char	c_zairyo04_cd[3];	/* 材料ｺｰﾄﾞ4 		*/
	char	c_zairyo05_cd[3];	/* 材料ｺｰﾄﾞ5 		*/
	char	c_zairyo06_cd[3];	/* 材料ｺｰﾄﾞ6 		*/
	char	c_zairyo07_cd[3];	/* 材料ｺｰﾄﾞ7 		*/
	char	c_zairyo08_cd[3];	/* 材料ｺｰﾄﾞ8 		*/
	char	c_zairyo09_cd[3];	/* 材料ｺｰﾄﾞ9 		*/
	char	c_zairyo10_cd[3];	/* 材料ｺｰﾄﾞ10 		*/
	char	c_yokisu01[2];		/* 本数（容器数）1 	*/
	char	c_yokisu02[2];		/* 本数（容器数）2 	*/
	char	c_yokisu03[2];		/* 本数（容器数）3 	*/
	char	c_yokisu04[2];		/* 本数（容器数）4 	*/
	char	c_yokisu05[2];		/* 本数（容器数）5 	*/
	char	c_yokisu06[2];		/* 本数（容器数）6 	*/
	char	c_yokisu07[2];		/* 本数（容器数）7 	*/
	char	c_yokisu08[2];		/* 本数（容器数）8 	*/
	char	c_yokisu09[2];		/* 本数（容器数）9 	*/
	char	c_yokisu10[2];		/* 本数（容器数）10 	*/
	char	c_saisyu_time[4];	/* 採取時間 		*/
	char	c_saisyu_ymd[8];	/* 採取年月日 		*/
	char	c_nyotime[4];		/* 蓄尿時間 		*/
	char	c_nyotime_kbn[1];	/* 蓄尿時間（単位） 	*/
	char	c_nyoryo[5];		/* 蓄尿量 		*/
	char	c_nyoryo_kbn[1];	/* 蓄尿量（単位） 	*/
	char	c_tochak_ymd[8];	/* 検体到着予定日 	*/
	char	c_imoto_lab[3];		/* 依頼元ID 		*/
	char	c_hsaki_lab1[3];	/* 報告先ID１ 		*/
	char	c_hsaki_lab2[3];	/* 報告先ID２ 		*/
	char	c_hsaki_lab3[3];	/* 報告先ID３ 		*/
	char	c_gmoto_lab1[3];	/* 外注元ID1 		*/
	char	c_gmoto_lab2[3];	/* 外注元ID2 		*/
	char	c_gmoto_lab3[3];	/* 外注元ID3 		*/
	char	c_gmoto_lab4[3];	/* 外注元ID4 		*/
	char	c_gmoto_lab5[3];	/* 外注元ID5 		*/
	char	c_gsaki_lab[3];		/* 外注先ID 		*/
	char	c_verify_kbn[1];	/* ﾍﾞﾘﾌｧｲ状況区分 	*/
	char	c_zokdel_flg[1];	/* 属性削除ﾌﾗｸﾞ 	*/
	char	c_zokupd_flg[1];	/* 属性修正ﾌﾗｸﾞ 	*/
	char	c_kinkyu_flg[1];	/* 緊急依頼ﾌﾗｸﾞ 	*/
	char	c_add_flg[1];		/* 追加有無ﾌﾗｸﾞ 	*/
	char	c_hikensa_kbn[1];	/* 非検査区分 		*/
	char	c_uketuke_kbn[1];	/* 受付区分 		*/
	char	c_ne_kbn[1];		/* NE区分 		*/
	char	c_hifd_flg[1];		/* FD非報告ﾌﾗｸﾞ 	*/
	char	c_kakucho_flg[1];	/* 拡張属性DB識別ﾌﾗｸﾞ 	*/
	char	c_uke_time[4];		/* 受付時刻 		*/
	char	c_ope_ymd[8];		/* 処理年月日 		*/
	char	c_obmluke_ymd[8];	/* 元BML受付年月日 	*/
	char	c_oirai_no[11];		/* 元依頼書NO 		*/
	char	c_eigyo_cd[3];		/* 営業所ｺｰﾄﾞ 		*/
	char	c_syuhai_cd[2];		/* 集配ｺｰﾄﾞ 		*/
	char	c_siset_knm[40];	/* 施設名正式名称（漢字）*/
	char	c_siset_nm[20];		/* 施設名正式名称（ｶﾅ） */
	char	c_sisetr_knm[20];	/* 施設名略称（漢字） 	*/
	char	c_sisetr_nm[10];	/* 施設名略称（ｶﾅ） 	*/
	char	c_siset_kbn[2];		/* 施設種別 		*/
	char	c_tokutei_flg[1];	/* 特定施設ﾌﾗｸﾞ 	*/
	char	c_riyu_cd[1];		/* 理由ｺｰﾄﾞ 		*/
	char	c_kmax[3];			/* 依頼項目数 		*/
	char	c_kjlab1_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ１ 	*/
	char	c_kjlab2_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ２ 	*/
	char	c_kjlab3_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ３ 	*/
	char	c_hokoku_no[2];		/* 当日報告NO 		*/
	char	c_yoyaku[12];		/* 予約ﾌｨｰﾙﾄﾞ 		*/
	char	c_filler[478];		/* FILLER 		*/
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

struct	Z03SJKOU {			/* PNC送受信項目 	*/
	char	c_bml_ymd[8];		/* BML受付年月日 	*/
	char	c_irai_no[11];		/* 依頼書No 		*/
	char	c_koumoku_cd[7];	/* 項目ｺｰﾄﾞ 		*/
	char	c_kentai_no[11];	/* 検体NO 		*/
	char	c_kentai_ch[2];		/* 検体ﾁｪｯｸ文字 	*/
	char	c_szairyo_cd[3];	/* 推定材料ｺｰﾄﾞ 	*/
	char	c_koumoku_rnm[8];	/* 項目名略称 		*/
	char	c_oya_cd[7];		/* 親項目ｺｰﾄﾞ 		*/
	char	c_set_cd[7];		/* ｾｯﾄ項目ｺｰﾄﾞ 		*/
	char	c_hisyokai_flg[1];	/* 非照会ﾌﾗｸﾞ 		*/
	char	c_hiseikyu_kbn[1];	/* 非請求区分 		*/
	char	c_hihokok_flg[1];	/* 非報告ﾌﾗｸﾞ 		*/
	char	c_naiyo_cd[1];		/* 処理内容ｺｰﾄﾞ 	*/
	char	c_section_cd[2];	/* ｾｸｼｮﾝｺｰﾄﾞ 		*/
	char	c_outchk_flg[1];	/* 出荷ﾁｪｯｸﾌﾗｸﾞ 	*/
	char	c_bunkaku_kbn[1];	/* 分画負荷区分 	*/
	char	c_yusen_lvl[2];		/* 優先ﾚﾍﾞﾙ 		*/
	char	c_add_flg[1];		/* 追加ﾌﾗｸﾞ 		*/
	char	c_del_flg[1];		/* 削除ﾌﾗｸﾞ 		*/
	char	c_jokenadd_flg[1];	/* 条件付追加ﾌﾗｸﾞ 	*/
	char	c_kakucho_flg[1];	/* 拡張結果DB識別ｺｰﾄﾞ 	*/
	char	c_fdkekka_flg[1];	/* FD拡張結果DB識別ｺｰﾄﾞ */
	char	c_kjlab_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ 	*/
	char	c_uketuke_kbn[1];	/* 受付区分 		*/
	char	c_kinkyu_gp[1];		/* 緊急ｸﾞﾙｰﾌﾟ 		*/
	char	c_base_no[3];		/* 基準値NO 		*/
	char	c_fuka_no[1];		/* 負荷報告NO表示	*/
	char	c_serial_no[5];		/* 出力順ｼﾘｱﾙNO 	*/
	char	c_hiteke_time[12];	/* 非定型負荷時間 	*/
	char	c_ope_ymd[8];		/* 処理年月日 		*/
	char	c_ws_cd[4];			/* W/Sｺｰﾄﾞ		*/
	char	c_lgtoket_flg[1];	/* ﾗﾎﾞ外注凍結振替ﾌﾗｸﾞ 	*/
	char	c_sateraito[3];		/* 検査ｻﾃﾗｲﾄID 		*/
	char	c_toseki_flg[1];	/* 透析ﾌﾗｸﾞ 		*/
	char	c_toketu_flg[1];	/* 凍結ﾌﾗｸﾞ 		*/
	char	c_buncyu_kbn[1];	/* 分注区分 		*/
	char	c_nbuncyu_kbn[1];	/* 尿分注区分 		*/
	char	c_kinkou_flg[1];	/* 緊急項目ﾌﾗｸﾞ 	*/
	char	c_toukou_flg[1];	/* 当日項目ﾌﾗｸﾞ 	*/
	char	c_yoyaku[31];		/* 予約ﾌｨｰﾙﾄﾞ 		*/
};

struct  Z03SJIR5        {       /* 依頼送受信ＰＮＣﾌｫｰﾏｯﾄ(細胞診用）*/
    char    c_sbt[2];       	/* ﾚｺｰﾄﾞ識別子([R5]固定)*/
    struct  Z03SJKOU        kou[IRAI_MAX];
    char	c_filler[61]; 		/* 1ﾃﾞｰﾀ中に複数項目がｾｯﾄされている*/
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

struct  Z04SJIR2        {       /* 依頼送受信ＰＮＣﾌｫｰﾏｯﾄ(治験拡張)*/
    char    c_sbt[2];       	/* ﾚｺｰﾄﾞ識別子([R2]固定)*/
	char    c_bml_ymd[8];       /* BML受付年月日    */
	char    c_irai_no[11];      /* 依頼書No         */
	char    c_protcol_no[11];   /* protcolNo         */
	char    c_ko_siset_cd[7];   /* 子施設コード      */
	char    c_toyotime[4];   	/* 投与時間     	 */
	char    c_toyoryo[5];   	/* 投与量     		 */
	char    c_toyoryo_kbn[3];  	/* 投与量単位  	    */
	char    c_drfuka_time[4];  	/* 薬剤負荷時間	    */
	char    c_ikassay_flg[1];  	/* 一括アッセイフラグ	    */
	char    c_kentai_su[2];  	/* 検体数	    */
	char    c_komoku_su[3];  	/* 項目数	    */
	char    c_saisyu_po[2];  	/* 採取ポイント	    */
	char    c_zairyo01_cd[5];  	/* 材料コード１	    */
	char    c_zairyo02_cd[5];  	/* 材料コード１	    */
	char    c_zairyo03_cd[5];  	/* 材料コード１	    */
	char    c_zairyo04_cd[5];  	/* 材料コード１	    */
	char    c_zairyo05_cd[5];  	/* 材料コード１	    */
	char    c_zairyo06_cd[5];  	/* 材料コード１	    */
	char    c_zairyo01_kg[1];  	/* 材料コード１記号 */
	char    c_zairyo02_kg[1];  	/* 材料コード１記号 */
	char    c_zairyo03_kg[1];  	/* 材料コード１記号 */
	char    c_zairyo04_kg[1];  	/* 材料コード１記号 */
	char    c_zairyo05_kg[1];  	/* 材料コード１記号 */
	char    c_zairyo06_kg[1];  	/* 材料コード１記号 */
	char    c_horyu_seq[4];  	/* 保留シーケンス */
	char    c_kaisyu_flg[1];  	/* 検体回収フラグ */
	char    c_gcp_flg[1];  		/* GCPフラグ */
	char    c_protocol_knm[40]; /* プロトコル漢字名 */
	char	c_yoyaku[53];		/* 予約ﾌｨｰﾙﾄﾞ       */
	char    c_filler[825];      /* FILLER       */
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

/*===============================================================*/
/*		結果依頼情報（生化学）									 */
/*===============================================================*/
/*--- S-JIS用構造体 ---*/

struct  Z05SJIR1        {       /* 依頼送受信ＰＮＣﾌｫｰﾏｯﾄ(細胞診用）*/
    char    c_sbt[2];       	/* ﾚｺｰﾄﾞ識別子([R1]固定)*/
	char	c_bml_ymd[8];		/* BML受付年月日 	*/
	char	c_irai_no[11];		/* 依頼書No 		*/
	char	c_koumoku_cd[7];	/* 項目ｺｰﾄﾞ 		*/
	char	c_kentai_no[11];	/* 検体NO 		*/
	char	c_kentai_ch[2];		/* 検体ﾁｪｯｸ文字 	*/
	char	c_szairyo_cd[3];	/* 推定材料ｺｰﾄﾞ 	*/
	char	c_koumoku_rnm[8];	/* 項目名略称 		*/
	char	c_oya_cd[7];		/* 親項目ｺｰﾄﾞ 		*/
	char	c_set_cd[7];		/* ｾｯﾄ項目ｺｰﾄﾞ 		*/
	char	c_hisyokai_flg[1];	/* 非照会ﾌﾗｸﾞ 		*/
	char	c_hiseikyu_kbn[1];	/* 非請求区分 		*/
	char	c_hihokok_flg[1];	/* 非報告ﾌﾗｸﾞ 		*/
	char	c_naiyo_cd[1];		/* 処理内容ｺｰﾄﾞ 	*/
	char	c_section_cd[2];	/* ｾｸｼｮﾝｺｰﾄﾞ 		*/
	char	c_outchk_flg[1];	/* 出荷ﾁｪｯｸﾌﾗｸﾞ 	*/
	char	c_bunkaku_kbn[1];	/* 分画負荷区分 	*/
	char	c_yusen_lvl[2];		/* 優先ﾚﾍﾞﾙ 		*/
	char	c_add_flg[1];		/* 追加ﾌﾗｸﾞ 		*/
	char	c_del_flg[1];		/* 削除ﾌﾗｸﾞ 		*/
	char	c_jokenadd_flg[1];	/* 条件付追加ﾌﾗｸﾞ 	*/
	char	c_kakucho_flg[1];	/* 拡張結果DB識別ｺｰﾄﾞ 	*/
	char	c_fdkekka_flg[1];	/* FD拡張結果DB識別ｺｰﾄﾞ */
	char	c_kjlab_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ 	*/
	char	c_uketuke_kbn[1];	/* 受付区分 		*/
	char	c_kinkyu_gp[1];		/* 緊急ｸﾞﾙｰﾌﾟ 		*/
	char	c_base_no[3];		/* 基準値NO 		*/
	char	c_fuka_no[1];		/* 負荷報告NO表示	*/
	char	c_serial_no[5];		/* 出力順ｼﾘｱﾙNO 	*/
	char	c_hiteke_time[12];	/* 非定型負荷時間 	*/
	char	c_ope_ymd[8];		/* 処理年月日 		*/
	char	c_ws_cd[4];			/* W/Sｺｰﾄﾞ		*/
	char	c_lgtoket_flg[1];	/* ﾗﾎﾞ外注凍結振替ﾌﾗｸﾞ 	*/
	char	c_sateraito[3];		/* 検査ｻﾃﾗｲﾄID 		*/
	char	c_toseki_flg[1];	/* 透析ﾌﾗｸﾞ 		*/
	char	c_toketu_flg[1];	/* 凍結ﾌﾗｸﾞ 		*/
	char	c_buncyu_kbn[1];	/* 分注区分 		*/
	char	c_nbuncyu_kbn[1];	/* 尿分注区分 		*/
	char	c_kinkou_flg[1];	/* 緊急項目ﾌﾗｸﾞ 	*/
	char	c_toukou_flg[1];	/* 当日項目ﾌﾗｸﾞ 	*/
	char	c_yoyaku[31];		/* 予約ﾌｨｰﾙﾄﾞ 		*/
	char	c_riyu_cd[1];       /* (依頼)理由ｺｰﾄﾞ   */
	char	c_ws_tan[1];		/* 	WS単独          */
	char    c_sex[1];			/* 性別区分         */
	char    c_age_kbn[1];		/* 年齢区分         */
	char    c_age[3];			/* 年齢         */
	char    c_nyotime[4];       /* 蓄尿時間         */
    char    c_nyotime_kbn[1];   /* 蓄尿時間（単位）     */
    char    c_nyoryo[5];        /* 蓄尿量       */
    char    c_nyoryo_kbn[1];    /* 蓄尿量（単位）   */
	char    c_siset_cd[7];      /* 施設ｺｰﾄﾞ         */
	char    c_eigyo_cd[3];      /* 営業所ｺｰﾄﾞ       */
    char	c_filler[835]; 
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

struct	Z11SJIRF {		/* END情報			*/
	char	c_sbt[2];			/* ﾚｺｰﾄﾞ識別区分	*/
	char	c_end[3];			/* 'END'固定		*/
	char	c_ope_ymd[8];		/* 処理年月日		*/
	char	c_filler[1010];		/* ﾌｨﾗｰ			*/
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

/*===============================================================*/
/*		要求カード           									 */
/*===============================================================*/
/*--- S-JIS用構造体 ---*/

struct  Z12SJR1        {       /* 要求カードＰＮＣﾌｫｰﾏｯﾄ */
    char    c_sbt[2];       	/* ﾚｺｰﾄﾞ識別子([R1]固定)*/
	char	c_opedate[8];		/* 送信元処理年月日	*/
	char	c_sateraito[3];		/* 検査ｻﾃﾗｲﾄID 		*/
	char	c_yokyu_kbn[1];		/* BML受付年月日 	*/
    char	c_filler[1009]; 
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ		*/ 
};

#endif
