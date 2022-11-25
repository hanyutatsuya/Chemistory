/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：edit_proc.c                                                  */
/*   概      要：データ編集処理                                               */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2019/12/08     BML.INC        CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include	<string.h>
#include	"LD103.h"

/******************************************************************************/
/*  関 数 名  ：EditPncKanjya                                                 */
/*  機能概要  ：ＰＮＣ属性データ編集 ＆　チェック                             */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  my_stFileKanjya	*inp;	: PNC依頼情報                 */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  my_stDbKanjya	*zok;	: 患者情報                    */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int	EditPncKanjya( inp, zok )
my_stFileKanjya		*inp;		/* PNC依頼情報(S-JIS)	*/
my_stDbKanjya		*zok;		/* 患者情報構造体	*/
{
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int	w_num;

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	//=========================================
	//	EDIT
	//=========================================
	// 1 ＢＭＬ受付年月日
	sprintf( zok->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 依頼書Ｎｏ
	sprintf( zok->irino,	"00%-3.3s%-6.6s"
		,inp->c_irai_no	,&inp->c_irai_no[5] );

	// 3 依頼書Ｎｏ桁数フラグ
	zok->iriketflg[0] = ' ';
	// 4 属性世代Ｎｏ
	zok->zssdino	= 0;

	//----------------------------------------------------	
	// キー項目編集済
	//	-> 削除フラグ='1'ならば処理を抜ける
	//----------------------------------------------------	
	if( inp->c_zokdel_flg[0] == '1' ){
		// WARNING
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "属性削除データを受信しました（データ読み飛ばし）。" );
		return( RTN_SKIP );
	}

	// 5 施設コード
	memcpy( zok->sstcd,	inp->c_siset_cd,sizeof( inp->c_siset_cd ));
	// 6 サブ施設コード
	memcpy( zok->subsstcd,	inp->c_subsiset_cd,sizeof( inp->c_subsiset_cd ));
	// 7 カード区分1
	memcpy( zok->cdkbn1,	inp->c_card1_kbn,sizeof( inp->c_card1_kbn ));
	// 8 カード区分2
	memcpy( zok->cdkbn2,	inp->c_card2_kbn,sizeof( inp->c_card2_kbn ));
	// 9 依頼元キー
	memcpy( zok->irimkey,	inp->c_iraimoto_key,sizeof( inp->c_iraimoto_key ));
	// 10 診療科コード	
	memcpy( zok->srkcd,	inp->c_ka_cd,sizeof( inp->c_ka_cd ));
	// 11 診療科名
	memcpy( zok->srknm,	inp->c_ka_nm,sizeof( inp->c_ka_nm ));
	// 12 担当医コード	
	memcpy( zok->tticd,	inp->c_dr_cd,sizeof( inp->c_dr_cd ));
	// 13 担当医名
	memcpy( zok->ttinm,	inp->c_dr_nm, sizeof( inp->c_dr_nm ));

	// 14 主治医コード		zok->gpcd
	// 15 主治医名			zok->gpnm
	// 16 紹介医コード		zok->skicd
	// 17 紹介医名			zok->skinm

	// 18 カルテＮｏ
	memcpy( zok->krtno,	inp->c_karte_no,sizeof( inp->c_karte_no ));
	// 19 患者ＩＤ
	memcpy( zok->knjid,	inp->c_kanja_id,sizeof( inp->c_kanja_id ));
	// 20 患者名（カナ）
	memcpy( zok->knjnmn,	inp->c_kanja_nm,sizeof( inp->c_kanja_nm ));
	// 21 患者名（漢字）
	memcpy( zok->knjnmk,	inp->c_kanja_knm,sizeof( inp->c_kanja_knm ));
	// 全角スペースで埋める
	for( w_num=strlen(zok->knjnmk);w_num < sizeof(zok->knjnmk)-1;w_num+=2 ){
		memcpy( &zok->knjnmk[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 22 患者名キー
	memset( buf,	0x00,	sizeof( buf ));

	NameKeyMake( buf,	inp->c_kanja_nm,sizeof( inp->c_kanja_nm ));
	if(strcmp(buf, " ") == 0)
	{
		memcpy(buf,	inp->c_karte_no,sizeof(inp->c_karte_no));
	}

	memcpy( zok->knjnmkey,	buf,sizeof( zok->knjnmkey ));
	// 23 身長	
	memcpy( zok->sc,		inp->c_tall,	sizeof( inp->c_tall ));
	// 身長、体重の数値チェックを行う（材料問わず）
	if( memcmp( inp->c_tall, MYAPP_SPACE10, sizeof( inp->c_tall )) != 0 ){
		//　妥当性チェック
		if( isCorrectChar( zok->sc ) != RTN_OK ) {
			// ERROR
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "身長エラーのためスペースに置換[%5.5s]" , inp->c_tall );
			// NULLを設定
			memset( zok->sc, 0x00, sizeof( zok->sc ));
		}
	}

	// 24 体重
	memcpy( zok->tj,		inp->c_weight,	sizeof( inp->c_weight ));
	// 身長、体重の数値チェックを行う（材料問わず）
	if( memcmp( inp->c_weight, MYAPP_SPACE10, sizeof( inp->c_weight )) != 0 ){
		//　妥当性チェック
		if( isCorrectChar( zok->tj ) != RTN_OK ) {
			// ERROR
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "体重エラーのためスペースに置換[%5.5s]" , inp->c_weight );
			// NULLを設定
			memset( zok->tj, 0x00, sizeof( zok->tj ));
		}
	}

	// 25 体重区分
	memcpy( zok->tjtni,		inp->c_weight_kbn,	sizeof( inp->c_weight_kbn));
	// 26 性別区分
	memcpy( zok->sbtkbn,		inp->c_sex,		sizeof( inp->c_sex ));
	// 27 生年月日
	memcpy( zok->birthday,		inp->c_birth_ymd,	sizeof( inp->c_birth_ymd ));
	// 28 生年月日区分
	memcpy( zok->birthdaykbn,	inp->c_birth_kbn,	sizeof( inp->c_birth_kbn ));
	// 29 年齢
	memcpy( zok->age,		inp->c_age,		sizeof( inp->c_age ));
	// 30 年齢区分
	memcpy( zok->agekbn,		inp->c_age_kbn,		sizeof( inp->c_age_kbn ));
	// 31 病棟コード
	memcpy( zok->btcd,		inp->c_byoto_cd,	sizeof( inp->c_byoto_cd ));

	// 32 病棟名
	memcpy( zok->btnm,	inp->c_byoto_nm,sizeof( inp->c_byoto_nm ));
	// 33 受付コメント1	
	memcpy( zok->utkcmtcd1,	inp->c_ukecmt1_cd,sizeof( inp->c_ukecmt1_cd));
	// 34 受付コメント2
	memcpy( zok->utkcmtcd2,	inp->c_ukecmt2_cd,sizeof( inp->c_ukecmt2_cd));
	// 35 受付コメント3
	memcpy( zok->utkcmtcd3,	inp->c_ukecmt3_cd,sizeof( inp->c_ukecmt3_cd));
	// 36 受付コメントフリー1
	memcpy( zok->utkcmtfr1,	inp->c_ukecmt1_cmt,sizeof( inp->c_ukecmt1_cmt ));
	// 37 受付コメントフリー2
	memcpy( zok->utkcmtfr2,	inp->c_ukecmt2_cmt, sizeof( inp->c_ukecmt2_cmt ));
	// 38 受付コメントフリーフラグ	zok->utkcmtfrflg
	strcpy( zok->utkcmtfrflg, "0" );
	// 39 入院外来区分
	memcpy( zok->ngkbn,	inp->c_ng_kbn,	sizeof( inp->c_ng_kbn ));
	// 40 妊娠週数
	memcpy( zok->nsssu,	inp->c_ninsin_cnt,sizeof( inp->c_ninsin_cnt ));
	// 41 保険コード
	memcpy( zok->hkncd,	inp->c_hoken_cd,sizeof( inp->c_hoken_cd ));
	// 42 検体総本数	zok->ktshsu
	// 43 院内依頼日
	strcpy( zok->iniriymd,	INIT_DATE );
	// 44 属性修正フラグ
	memcpy( zok->zssflg,	inp->c_zokupd_flg,sizeof( inp->c_zokupd_flg ));
	// 45 緊急依頼フラグ
	// 	  理由コードから判定
	memcpy( zok->kkiriflg,	inp->c_kinkyu_flg,sizeof( inp->c_kinkyu_flg ));
	// 46 非検査区分
	memcpy( zok->hknskbn,	inp->c_hikensa_kbn,sizeof( inp->c_hikensa_kbn ));
	// 47 受付区分
	memcpy( zok->utkkbn,	inp->c_uketuke_kbn,sizeof( inp->c_uketuke_kbn ));
	// 48 ＮＥ区分
	memcpy( zok->nekbn,	inp->c_ne_kbn,	sizeof( inp->c_ne_kbn ));
	// 49 院内検査区分	zok->inknskbn
	// 50 受付状態区分 	zok->utkjkkbn
	// 51 完了フラグ	
	strcpy( zok->krflg,	"0" );
	// 52 ＦＤ非報告フラグ
	memcpy( zok->fdhhkkflg,	inp->c_hifd_flg,sizeof( inp->c_hifd_flg ));

	// 53 受付時刻
	if( strncmp( inp->c_uke_time, MYAPP_SPACE10, 4 ) == 0 ){
		strcpy( zok->utkdh,	INIT_TIME );
	} else {
		sprintf( zok->utkdh,	"%.2s:%.2s:00", inp->c_uke_time,&inp->c_uke_time[2] );
	}

	// 54 元ＢＭＬ受付日
	if( strncmp( inp->c_obmluke_ymd, MYAPP_SPACE10, 8 ) == 0 ){
		strcpy( zok->mutkymd,	INIT_DATE );
	} else {
		sprintf( zok->mutkymd,	"%.4s-%.2s-%.2s", inp->c_obmluke_ymd,	
			&inp->c_obmluke_ymd[4],&inp->c_obmluke_ymd[6] );
	}

	// 55 元依頼書Ｎｏ
	memcpy( zok->mirino,	inp->c_oirai_no,sizeof( inp->c_oirai_no ));
	// 56 検査実施ラボコード  knsjslbcd1
	// 57 検査実施ラボコード  knsjslbcd2
	// 58 検査実施ラボコード  knsjslbcd3
	// 59 検査実施ラボコード  knsjslbcd4

	// 60 翌日未報告フラグ	
	// 空白とする

	// 61 報告希望時間
	strcpy( zok->hkkkbdh,	INIT_TIME );
	// 62 営業所コード
	memcpy( zok->ecd,	inp->c_eigyo_cd,sizeof( inp->c_eigyo_cd ));
	// 63 集配コード
	memcpy( zok->shcd,	inp->c_syuhai_cd,sizeof( inp->c_syuhai_cd ));
	// 64 施設名正式名称
	memcpy( zok->sstssnmj,	inp->c_siset_knm,sizeof( inp->c_siset_knm ));
	// 全角スペースで埋める
	for( w_num=strlen(zok->sstssnmj);w_num < sizeof(zok->sstssnmj)-1;w_num+=2 ){
		memcpy( &zok->sstssnmj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 65 施設名正式名称（カナ）
	memcpy( zok->sstssnmn,	inp->c_siset_nm,sizeof( inp->c_siset_nm ));
	// 66 施設名略称
	memcpy( zok->sstrsj,	inp->c_sisetr_knm,sizeof( inp->c_sisetr_knm ));
	// 全角スペースで埋める
	for( w_num=strlen(zok->sstrsj);w_num < sizeof(zok->sstrsj)-1;w_num+=2 ){
		memcpy( &zok->sstrsj[w_num], MYAPP_KJSPACE10, 2 );
	}
		// ALL 全角スペースの場合、正式名称より編集
	if( strcmp( zok->sstrsj, MYAPP_KJSPACE10 ) == 0 ){
		memcpy( zok->sstrsj, zok->sstssnmj, sizeof( zok->sstrsj ) - 1 );
	}

	// 67 施設名略称（カナ）
	memcpy( zok->sstrsn,	inp->c_sisetr_nm, sizeof( inp->c_sisetr_nm ));
	// 68 施設種別
	memcpy( zok->sstsbt,inp->c_siset_kbn,sizeof( inp->c_siset_kbn ));
	// 69 特定施設フラグ
	memcpy( zok->ttsstflg,inp->c_tokutei_flg,sizeof( inp->c_tokutei_flg));

	// 70 理由コード
	memset( buf,	0x00,	sizeof( buf ));
	memcpy( zok->rucd,	inp->c_riyu_cd,sizeof( inp->c_riyu_cd ));
	// 45 緊急依頼フラグ
	if( zok->rucd[0] == 'L' ){
		 zok->kkiriflg[0] = '1';
	}
	// 71 依頼項目数	
	if( memcmp( inp->c_kmax, MYAPP_SPACE10, sizeof( inp->c_kmax )) == 0 ){
		zok->irikmksu = 0;
	} else {
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_kmax,	sizeof( inp->c_kmax ));
		zok->irikmksu = atoi( w_str );
	}

	// 72 病名及び所見		zok->bmskn
	// 73 依頼入力種別		zok->irinrsbt
	// 74 依頼発生元区分	0:上位発生 1:サテライト発生
	strcpy( zok->irihsmkbn,	"0" );
	// 75 特別注意施設フラグzok->caresstflg
	// 76 治験拡張フラグ	0:デフォルト 1:情報あり
	strcpy( zok->tktyflg,	"0" );
	// 77 AUTO-P検体Ｎｏ	zok->apkntino
	// 78 診断名 			zok->sdnm

	// 採取年月日 採取時間 妥当性チェック
	if( memcmp( inp->c_saisyu_ymd, MYAPP_SPACE10, sizeof(inp->c_saisyu_ymd) ) != 0 ){
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_saisyu_ymd,	sizeof( inp->c_saisyu_ymd ));
		if( ValidDate( VALDATE_DATE, w_str ) == RTN_NG ){
			// 初期値をセット
			memcpy( inp->c_saisyu_ymd, MYAPP_SPACE10, sizeof(inp->c_saisyu_ymd));
		}
	}
	// 採取時間
	if( memcmp( inp->c_saisyu_time, MYAPP_SPACE10, sizeof(inp->c_saisyu_time) ) != 0 ){
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_saisyu_time,	sizeof( inp->c_saisyu_time ));
		strcat( w_str, "00" );
		if( ValidDate( VALDATE_TIME, w_str ) == RTN_NG ){
			// 初期値をセット
			memcpy( inp->c_saisyu_time, MYAPP_SPACE10, sizeof(inp->c_saisyu_time));
		}
	}

	// 79 備考１
	/* 3byte 材料コード */
	/* 8byte 採取年月日 */
	/* 4byte 採取時間 */
	sprintf( zok->bko1, "%-3.3s!%-8.8s!%-4.4s", 
		inp->c_zairyo01_cd, inp->c_saisyu_ymd, inp->c_saisyu_time );

	// 80 備考２ 
	/* 4byte 蓄尿時間	*/
	/* 1byte 蓄尿時間単位 */
	/* 5byte 蓄尿量		*/
	/* 1byte 蓄尿量単位	*/
	sprintf( zok->bko2, "%-4.4s!%-1.1s!%-5.5s!%-1.1s", 
		inp->c_nyotime,	inp->c_nyotime_kbn,
		inp->c_nyoryo,		inp->c_nyoryo_kbn );
		
	// 81 備考３
	// 82 属性登録日時
	strcpy( zok->zstrdh,	INIT_TIMESTAMP );
	// 83 属性修正日時
	strcpy( zok->zsssdh,	INIT_TIMESTAMP );
	// 84 サテライト内属性修正日時
	strcpy( zok->stlzsssdh,	INIT_TIMESTAMP );
	// 85 サテライト内属性修正端末IP
	// 86 サテライト内属性修正入力者
	// 87 情報更新日時	CURRENT TIMESTAMP
	// 88 親施設コード
	strcpy( zok->oyasstcd,	zok->sstcd );
	// 89 登録日時	CURRENT TIMESTAMP

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditPncKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	return( RTN_OK );
}
/******************************************************************************/
/*  関 数 名  ：EditCommonKanjya                                              */
/*  機能概要  ：患者属性データ共通編集＆チェック                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  my_DbKanjya		*zok;	: 患者情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int	EditCommonKanjya( zok )
my_stDbKanjya	*zok;	// 患者属性構造体
{
	int	ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;

	/* 初期処理     */
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	//=========================================
	//	CHECK
	//=========================================
	// DATE 妥当性チェック
	// ＢＭＬ受付日
	if( ( strcmp( zok->utkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->utkymd )) == RTN_NG )){
		// ERROR
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "ＢＭＬ受付日 妥当性エラー[%s]" , zok->utkymd );
		return( RTN_NG );
	}

	// 院内依頼日		→区分が無いため西暦を前提とする
	if( ( strcmp( zok->iniriymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->iniriymd )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "院内依頼日 妥当性エラーのため初期値置換[%s]" , zok->iniriymd );
		// 初期値をセット
		strcpy( zok->iniriymd, INIT_DATE );
	}

	// 元ＢＭＬ受付日
	if( ( strcmp( zok->mutkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->mutkymd )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "元ＢＭＬ受付日 妥当性エラーのため初期値置換[%s]" , zok->mutkymd );
		// 初期値をセット
		strcpy( zok->mutkymd, INIT_DATE );
	}

	// 生年月日		→CHAR型のため初期値置換は行わない
	if( strncmp( zok->birthday, MYAPP_SPACE10, strlen(zok->birthday) ) != 0 ){
		// 西暦変換
		memset( w_str,	'\0',	sizeof( w_str ));
		strcpy( buf, zok->birthday );
		wa2ymd( w_str, zok->birthdaykbn, buf );
	 	if(( ret = ValidDate( VALDATE_DATE, w_str )) == RTN_NG ){
			// WARNING
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "生年月日 妥当性エラー[%s]", zok->birthday );
		}
	}

	// TIME 妥当性チェック
	// 受付時刻
	if( ( strcmp( zok->utkdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->utkdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "受付時刻 妥当性エラーのため初期値置換[%s]" , zok->utkdh );
		// 初期値をセット
		strcpy( zok->utkdh, INIT_TIME );
	}
	// 報告希望時間
	if( ( strcmp( zok->hkkkbdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->hkkkbdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "報告希望時間 妥当性エラーのため初期値置換[%s]" , zok->hkkkbdh );
		// 初期値をセット
		strcpy( zok->hkkkbdh, INIT_TIME );
	}

	// TIMESTAMP 妥当性チェック
	// 属性登録日時
	if( ( strcmp( zok->zstrdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zstrdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "属性登録日時 妥当性エラーのため初期値置換[%s]" , zok->zstrdh );
		// 初期値をセット
		strcpy( zok->zstrdh, INIT_TIMESTAMP );
	}
	// 属性修正日時
	if( ( strcmp( zok->zsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "属性修正日時 妥当性エラーのため初期値置換[%s]" , zok->zsssdh );
		// 初期値をセット
		strcpy( zok->zsssdh, INIT_TIMESTAMP );
	}
	// サテライト内属性修正日時
	if( ( strcmp( zok->stlzsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->stlzsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "サテライト内属性修正日時 妥当性エラーのため" "初期値置換[%s]" , zok->stlzsssdh );
		// 初期値をセット
		strcpy( zok->stlzsssdh, INIT_TIMESTAMP );
	}

	// 妥当性チェック
		// 年齢
	if( strncmp( zok->age, MYAPP_SPACE10, sizeof( zok->age )) != 0 ){
		if( zok->agekbn[0] == 'Y' ){
			w_num = atoi( zok->age );
			if( w_num > 150 ){
				// WARNING
				sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "年齢 妥当性エラー[%s]" , zok->age );
			}
		}
	}
	//	年齢区分
	if(   ( strcmp( zok->agekbn, AGEKBN_YEAR  ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_MONTH ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_WEEK  ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_DAY   ) != 0 )
		&&( strcmp( zok->agekbn, AGEKBN_UNKNOWN ) != 0 )){
			// WARNING
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "年齢区分エラー[%s]" , zok->agekbn );
			// 初期値をセット
			strcpy( zok->agekbn, AGEKBN_UNKNOWN );
		}
	//	性別区分
	if(   ( strcmp( zok->sbtkbn, SEX_MALE   ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_FEMALE ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_UNKNOWN ) != 0 )){
			// WARNING
			sFncPutLog( TRCKIND_ERROR, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "性別区分エラー[%s]", zok->sbtkbn );
			// 初期値をセット
			strcpy( zok->sbtkbn, SEX_UNKNOWN );
	}

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "EditCommonKanjya", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：NameKeyMake                                                   */
/*  機能概要  ：患者名キー作成                                                */
/*  入    力  ：                                                              */
/*   第１引数 ：char	kan_name[];	: S-JIS 患者カナ氏名                  */
/*   第２引数 ：int	len;		: S-JIS 患者カナ氏名length            */
/*  出    力  ：                                                              */
/*   第１引数 ：char	name_key[];	: S-JIS 患者名キー                    */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		NameKeyMake( name_key, kan_name, len )
char		name_key[];		/*	[O]	患者名キー	*/
char		kan_name[];		/*	[I]	患者名		*/
int			len;			/*	[I]	患者名length	*/
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
/*  関 数 名  ：isCorrectChar                                                 */
/*  機能概要  ：患者属性数値エリアチェック                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： char	In[];	    : チェック文字列                          */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK		    : 正常終了                                */
/*               以外		    : 失敗                                    */
/******************************************************************************/
int isCorrectChar(char *In)
{
	int	ret=RTN_OK;

	int i = 0;
	int nSuziFlg =0; //初めが数字かとうか検索

	/* 初期処理     */
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
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 数字中にSPACE[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
		}
		else if(buf[i] == '.'){
			if(i==0){
				// DEBUG
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 先頭.不可[%s]" , In );
				// ERROR
				ret=RTN_NG;
				break;
			}
			if(nSuziFlg == 0){
				// DEBUG
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 先頭.不可[%s]" , In );
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
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "isCorrectChar", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "数値 空白.以外不可[%s]" , In );
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
/*  関 数 名  ：ValidDate                                                     */
/*  機能概要  ：日付、時刻　妥当性チェック                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： int    mode            : 編集されている日付関連項目の型      */
/*   第２引数 ： char   indate[]        : 入力日付時刻                        */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK              : 正常                                   */
/*               RTN_NG              : エラー                                 */
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

	/* 初期設定     */
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ValidDate", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	strcpy( w_yyyy, "0000" );       y = strlen( w_yyyy ) - 1;
	strcpy( w_mm,   "00" );         m = strlen( w_mm ) - 1;
	strcpy( w_dd,   "00" );         d = strlen( w_dd ) - 1;
	strcpy( w_hh,   "00" );         h = strlen( w_hh ) - 1;
	strcpy( w_mi,   "00" );         mi = strlen( w_mi ) - 1;
	strcpy( w_ss,   "00" );         s = strlen( w_ss ) - 1;

	// INPUT日付を年月日時分秒に分解
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
		// 時刻エラー
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
		// 閏年チェック
		// １） 西暦を４で割り、割り切れた年は閏年である
		// ２） なお、１の条件を満たしても、１００で割り切れた場合は閏年を解除
		// ３） なお、２の条件を満たしても、４００で割り切れた場合は閏年
		if(( m == 2 ) && ( y%4 == 0 )){                         // 閏年候補
			if(( y%100 != 0 ) || ( y%400 == 0 )){   // 閏年決定
				if( d == 29 ){
					// OK
					sFncPutLog( TRCKIND_DEBUG, __FILE__, "ValidDate", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
					return( RTN_OK );
				}
			}
		}
	}
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "ValidDate", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
	// 日付エラー
	return( RTN_NG );
}

/*****************************************************************
        名称  : 和暦・西暦変換

        概要  : 和暦から西暦に変換する
                ｺｰﾄﾞ管理ﾏｽﾀに元号の管理をしている
        注意　: 元号と編集前の年月日が正しいことが前提

        構文  : char    *Lwa_ymd( ymd10, gengou, ymd )
        引数  : (out)   char    ymd10[];        編集後(YYYY/MM/DD)
                (in)    char    gengou[];
                        元号
                        ' ':西暦
                         M :明治 "1868/09/08", "1912/07/29"
                         T :大正 "1912/07/30", "1926/12/24", "T"
                         S :昭和 "1926/12/25", "1989/01/07", "S"
                         H :平成 "1989/01/08", "9999/12/31", "H"
                (in)    char    ymd[];          編集前(YYYYMMDD)

        ﾘﾀ-ﾝ値: ymd10の先頭ｱﾄﾞﾚｽ
                ymd10=NULLの場合は内部ｴﾘｱの文字列先頭ｱﾄﾞﾚｽ
*****************************************************************/
int             wa2ymd( ymd10, gengou, ymd )
char            ymd10[];                                        /* 編集後(YYYY/MM/DD)   */
char            gengou[];                                       /* 元号                 */
char            ymd[];                                          /* 編集前(YYYYMMDD)     */
{
	char    wk_ymd8[10];
	char    wk_yy[10];
	char    wk_mmdd[10];
	int     i,j,k;
	int     add_yy;

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "wa2ymd", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "START" );

	/* 西暦ならば処理終了 */
	if( gengou[0] == ' ' ){
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "wa2ymd", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "END" );
		sprintf( ymd10, "%.4s-%.2s-%.2s", ymd, &ymd[4], &ymd[6] );
		return( RTN_OK );
	}

	/* 日付の獲得   */
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
	/* 元号の開始年月を求める。本来はDBが望ましい。とりあえずON */
	switch  ( gengou[0] ) {
		case 'M' :              /* 明治 */
			add_yy = 1868;
			break;
		case 'T' :              /* 大正 */
			add_yy = 1912;
			break;
		case 'S' :              /* 昭和 */
			add_yy = 1926;
			break;
		case 'H' :              /* 平成 */
			add_yy = 1989;
			break;
		case 'R' :              /* 令和 */
			add_yy = 2019;
			break;
		default:
			break;
	}
	/* 開始西暦を求める     */
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
/*  関 数 名  ：sFncTrim                                                        */
/*  機能概要  ：指定文字列の前後のスペースを取り除いて文字列をコピーする        */
/*  入    力  ：                                                                */
/*   第２引数 ：char * 変換元文字列                                             */
/*  出    力  ：                                                                */
/*   第１引数 ：char * 変換後文字列                                             */
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
