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
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(親施設,登録日時)対応 */
/*  1.05     2007/06/01     INTEC.INC      患者名キー空白時カルテＮｏ設定     */
/*  2.01     2007/06/01     INTEC.INC      備考の項目の妥当性チェック追加     */
/*  2.02     2007/06/01     INTEC.INC      患者属性項目の数値チェック追加     */
/*  3.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD202.h"

/******************************************************************************/
/*  関 数 名  ：EditKinqKanjya                                                */
/*  機能概要  ：緊急患者属性データ編集 ＆　チェック                           */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  AS4IRAI    *inp;	: AS400緊急依頼情報               */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA		*zok;	: 患者情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditKinqKanjya( inp, zok )
struct		AS4IRAI		*inp;		/* AS400緊急依頼情報(S-JIS)	*/
struct		_KANJYA		*zok;		/* 患者情報構造体		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* 初期処理	*/
	strcpy(func_nm, "EditKinqKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 ＢＭＬ受付年月日	<- yyyy-mm-dd 形式
	sprintf( zok->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 依頼書Ｎｏ			<- 検体Noから編集 00xxxxxxx00 形式(検体No枝番は切り捨て)
	sprintf( zok->irino,"00%-3.3s%-4.4s00",inp->c_kentai_no	,&inp->c_kentai_no[5] );
	
	// 3 依頼書Ｎｏ桁数フラグ
	zok->iriketflg[0] = ' ';

	// 4 属性世代Ｎｏ
	zok->zssdino	= stcPRM.myp_sedai;

	// ログ出力用キー項目設定
	strcpy( G_utkymd,	zok->utkymd );
	strcpy( G_irino,	zok->irino );

	// 5 施設コード
	if( memcmp( inp->c_siset_cd, MYAPP_SPACE10, sizeof(inp->c_siset_cd))==0){
											/* 施設コードが空のケース */
		memcpy( zok->sstcd,	inp->c_siset_cd,sizeof( inp->c_siset_cd ));
											/* 一応、受信データからコピーするが空です */
		strcpy( G_msg, "施設コードが空白です。" );
											/* WARNINGをLOGに出力 */
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	} else {								/* 施設コードが設定されているケース */
		memcpy( zok->sstcd,	inp->c_siset_cd,sizeof( inp->c_siset_cd ));
											/* 7桁分(全部)をコピー */
	}
	// 6 サブ施設コード
	strcpy( zok->subsstcd,	"0000" );

	// 7 カード区分1
	memcpy( zok->cdkbn1,	inp->c_card1_kbn,sizeof( inp->c_card1_kbn ));

	// 8 カード区分2
	// 9 依頼元キー
	// 10 診療科コード
	memcpy( zok->srkcd,	inp->c_ka_cd,sizeof( inp->c_ka_cd ));
											/* そのままコピー */

	// 11 診療科名
	w_num = atoi( zok->srkcd );
	strcpy( zok->srknm,		kanm[w_num].sname );

	// 12 担当医コード	
	// 13 担当医名
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->ttinm, memcpy(buf, inp->c_dr_nm, 
		sizeof( inp->c_dr_nm )), sizeof( zok->ttinm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【担当医名】[%s]"
			,zok->ttinm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 14 主治医コード		zok->gpcd
	// 15 主治医名			zok->gpnm
	// 16 紹介医コード		zok->skicd
	// 17 紹介医名			zok->skinm

	// 18 カルテＮｏ
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->krtno, memcpy(buf, inp->c_karte_no, 
		sizeof( inp->c_karte_no )), sizeof( zok->krtno ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【カルテＮｏ】[%s]"
			,zok->krtno );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 19 患者ＩＤ

	// 20 患者名（カナ）
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->knjnmn, memcpy(buf, inp->c_kanja_nm, 
		sizeof( inp->c_kanja_nm )), sizeof( zok->knjnmn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【患者名（カナ）】[%s]"
			,zok->knjnmn );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 21 患者名（漢字）
		// 全角スペースで埋める
	for( w_num=strlen(zok->knjnmk);w_num < sizeof(zok->knjnmk)-1;w_num+=2 ){
		memcpy( &zok->knjnmk[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 22 患者名キー
	memset( buf,	0x00,	sizeof( buf ));
	NameKeyMake( buf, inp->c_kanja_nm, sizeof( inp->c_kanja_nm ));
		// 1.05 ADD 患者名キーが空白の場合カルテＮｏをセット
	if(strcmp(buf, " ") == 0)
    {
        memcpy(buf, inp->c_karte_no,sizeof(inp->c_karte_no));
    }
	cret=sj2euc( zok->knjnmkey, buf, sizeof( zok->knjnmkey ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【患者名キー】[%s]"
			,zok->knjnmkey );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// DEBUG
	sprintf( G_msg, "NameKeyMake [%s]->[%s]", zok->knjnmn, zok->knjnmkey);
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 23 身長	
	// 24 体重
	// 25 体重区分			<- 0:Kg
	zok->tjtni[0] = '0';

	// 26 性別区分
	memcpy( zok->sbtkbn,	inp->c_sex,	sizeof( inp->c_sex ));

	// 27 生年月日
	// 28 生年月日区分

	// 29 年齢
	memcpy( zok->age,		inp->c_age,	sizeof( inp->c_age ));
	// 30 年齢区分
	zok->agekbn[0] = 'Y';
		// 年齢がスペースの場合は、Z：不明
	if( memcmp( inp->c_age, MYAPP_SPACE10, sizeof( inp->c_age )) == 0 ){
		zok->agekbn[0] = 'Z';
	}

	// 31 病棟コード
	// 32 病棟名
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->btnm, memcpy(buf, inp->c_byoto_nm, 
		sizeof( inp->c_byoto_nm )), sizeof( zok->btnm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【病棟名】[%s]"
			,zok->btnm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 33 受付コメント1	
	memcpy( zok->utkcmtcd1,	inp->c_ukecmt_cd,sizeof( inp->c_ukecmt_cd));
	// 34 受付コメント2
	// 35 受付コメント3
	// 36 受付コメントフリー1
	// 37 受付コメントフリー2
	// 38 受付コメントフリーフラグ	zok->utkcmtfrflg
	strcpy( zok->utkcmtfrflg, "0" );

	// 39 入院外来区分
	memcpy( zok->ngkbn,		inp->c_ng_kbn,	sizeof( inp->c_ng_kbn ));
		// 入院外来区分がスペースの場合は、0：不明
	if( memcmp( inp->c_ng_kbn, MYAPP_SPACE10, sizeof( inp->c_ng_kbn )) == 0 ){
		zok->ngkbn[0] = '0';
	}

	// 40 妊娠週数
	// 41 保険コード
	memcpy( zok->hkncd,		inp->c_hoken_cd,sizeof( inp->c_hoken_cd ));
	// 42 検体総本数		zok->ktshsu
	// 43 院内依頼日
	strcpy( zok->iniriymd,	INIT_DATE );
	// 44 属性修正フラグ
	zok->zssflg[0] = '0';
	// 45 緊急依頼フラグ
	memcpy( zok->kkiriflg,	inp->c_kinkyu_flg,sizeof( inp->c_kinkyu_flg ));
	// 46 非検査区分
	zok->hknskbn[0] = '0';
	// 47 受付区分
	zok->utkkbn[0] = '0';

	// 48 ＮＥ区分
	memcpy( zok->nekbn,	inp->c_ne_kbn,sizeof( inp->c_ne_kbn));

	// 49 院内検査区分		zok->inknskbn
	// 50 受付状態区分 		zok->utkjkkbn

	// 51 完了フラグ	
	zok->krflg[0] = '0';

	// 52 ＦＤ非報告フラグ
	zok->fdhhkkflg[0] = '0';

	// 53 受付時刻
	strcpy( zok->utkdh,	INIT_TIME );
	// 54 元ＢＭＬ受付日
	strcpy( zok->mutkymd,	INIT_DATE );
	// 55 元依頼書Ｎｏ
	// 56 検査実施ラボコード  knsjslbcd1
	// 57 検査実施ラボコード  knsjslbcd2
	// 58 検査実施ラボコード  knsjslbcd3
	// 59 検査実施ラボコード  knsjslbcd4

	// 60 翌日未報告フラグ	
	zok->ymhkkflg[0] = ' ';
	// 61 報告希望時間
	strcpy( zok->hkkkbdh,	INIT_TIME );

	// 62 営業所コード		<- 頭3桁
	sprintf( zok->ecd,		"%-3.3s",inp->c_eigyo_cd );
	// 63 集配コード		<- 後2桁
	sprintf( zok->ecd,		"%-2.2s",&inp->c_eigyo_cd[3] );

	// 64 施設名正式名称
		// 全角スペースで埋める
	for( w_num=strlen(zok->sstssnmj);w_num < sizeof(zok->sstssnmj)-1;w_num+=2 ){
		memcpy( &zok->sstssnmj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 65 施設名正式名称（カナ）
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstssnmn, memcpy(buf, inp->c_sisetr_knm, 
		sizeof( inp->c_sisetr_knm )), sizeof( zok->sstssnmn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【施設名正式名称（カナ）】"
			"[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 64 施設名正式名称 カナを設定
	strcpy( zok->sstssnmj,	zok->sstssnmn );

	// 66 施設名略称
		// 全角スペースで埋める
	for( w_num=strlen(zok->sstrsj);w_num < sizeof(zok->sstrsj)-1;w_num+=2 ){
		memcpy( &zok->sstrsj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 67 施設名略称（カナ）	<- 施設名正式名称（カナ）10byte
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstrsn, memcpy(buf, inp->c_sisetr_knm, 10 ),
					 sizeof( zok->sstrsn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【施設名略称（カナ）】"
			"[%s][%s]"
			,zok->sstcd , zok->sstrsn );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 66 施設名略称 カナを設定
	strcpy( zok->sstrsj,	zok->sstrsn );

	// 68 施設種別
	// 69 特定施設フラグ
	// 70 理由コード
	// 71 依頼項目数	
	if( memcmp( inp->c_kmcnt, MYAPP_SPACE10, sizeof( inp->c_kmcnt )) == 0 ){
		zok->irikmksu = 0;
	} else {
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_kmcnt,	sizeof( inp->c_kmcnt ));
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

	// 2.01 ADD STA
		/* 8byte 採取年月日 	<- 受付年月日の年を付加する */
    // 採取年月日 採取時間 妥当性チェック
	if( memcmp( inp->c_saisyu_bi, MYAPP_SPACE10, sizeof(inp->c_saisyu_bi))!=0){
        memset( w_str, 0x00, sizeof( w_str ));
		sprintf( w_str,	"%.4s%.4s", zok->utkymd, inp->c_saisyu_bi );
        if( ValidDate( VALDATE_DATE, w_str ) == RTN_NG ){
                // ERROR --> CONV
            sprintf( G_msg, "採取年月日 妥当性エラーのため初期値置換[%s]"
                , w_str );
            EditCsvMsg( G_msg );
            LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
                // 初期値をセット
            memcpy( inp->c_saisyu_bi, MYAPP_SPACE10, sizeof(inp->c_saisyu_bi));
        }
    }
	// 2.01 ADD END

	// 79 備考１
		/* 3byte 材料コード */
	if( memcmp( inp->c_zairyo_cd, MYAPP_SPACE10, sizeof(inp->c_zairyo_cd))==0){
											/* 材料コードが空のケース */
		memset( w_str,	0x00, sizeof( w_str ));
		strncpy( w_str, MYAPP_SPACE10, 3 );	/* スペースで埋める(3BYTE分) */
	} else {								/* 材料コードが設定されているケース */
		sprintf( w_str,	"%-3.3s",	 inp->c_zairyo_cd );
											/* 内容をコピー */
	}
		/* 8byte 採取年月日 	<- 受付年月日の年を付加する */
	memset( buf,	0x00, sizeof( buf ));
	if( memcmp( inp->c_saisyu_bi, MYAPP_SPACE10, sizeof(inp->c_saisyu_bi))==0){
		strncpy( buf,	MYAPP_SPACE10, 8 );
	} else {
		sprintf( buf,	"%.4s%.4s", zok->utkymd, inp->c_saisyu_bi );
	}
		/* 4byte 採取時間 */

	sprintf( zok->bko1, "%s!%.8s!%.4s", w_str,	buf, MYAPP_SPACE10 );


	// 80 備考２ 
		/* 4byte 蓄尿時間		<- 前ZEROを付加して桁を合わせる */
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
		/* 1byte 蓄尿時間単位 	<- 0 */
		/* 5byte 蓄尿量			<- 前ZEROを付加して桁を合わせる */
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
		/* 1byte 蓄尿量単位		<- 0 */

	sprintf( zok->bko2, "%-4.4s!0!%-5.5s!0", w_str,	buf );
	
		
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
	// 1.01 ADD	88 親施設コード
	strcpy( zok->oyasstcd,	zok->sstcd );
	// 1.01 ADD	89 登録日時	CURRENT TIMESTAMP

	//=========================================
	//	CHECK
	//=========================================
	// 材料が蓄尿量の場合、属性情報をワーニングチェックする
	if(( strlen( stcPRM.myp_zairyo ) != 0 )
	 &&( memcmp( &stcPRM.myp_zairyo[1], inp->c_zairyo_cd, 3 ) == 0 )){
		// 蓄尿時間	c_nyotime
		if( memcmp( inp->c_nyotime, MYAPP_SPACE10
					, sizeof( inp->c_nyotime )) == 0 ){
			// WARNING
			sprintf( G_msg, "蓄尿 蓄尿時間エラー[%.2s]" ,inp->c_nyotime );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		// 蓄尿量	c_nyoryo
		if( memcmp( inp->c_nyoryo, MYAPP_SPACE10
				, sizeof( inp->c_nyoryo )) == 0 ){
			// WARNING
			sprintf( G_msg, "蓄尿 蓄尿量エラー[%.4s]" ,inp->c_nyoryo );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// DATE 妥当性チェック
	// ＢＭＬ受付日
	if( ( strcmp( zok->utkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->utkymd )) == RTN_NG )){
			// ERROR
		sprintf( G_msg, "ＢＭＬ受付日 妥当性エラー[%s]" , zok->utkymd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 
		return( RTN_NG );
	}

	// 院内依頼日		→区分が無いため西暦を前提とする
	if( ( strcmp( zok->iniriymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->iniriymd )) == RTN_NG )){
			// ERROR --> CONV
		sprintf( G_msg, "院内依頼日 妥当性エラーのため初期値置換[%s]"
			, zok->iniriymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 初期値をセット
		strcpy( zok->iniriymd, INIT_DATE );
	}

	// 元ＢＭＬ受付日
	if( ( strcmp( zok->mutkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, zok->mutkymd )) == RTN_NG )){
			// ERROR --> CONV
		sprintf( G_msg, "元ＢＭＬ受付日 妥当性エラーのため初期値置換[%s]"
			, zok->mutkymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
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
			sprintf( G_msg, "生年月日 妥当性エラー[%s]", zok->birthday );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// TIME 妥当性チェック
	// 受付時刻
	if( ( strcmp( zok->utkdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->utkdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "受付時刻 妥当性エラーのため初期値置換[%s]"
			, zok->utkdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// 初期値をセット
		strcpy( zok->utkdh, INIT_TIME );
	}
	// 報告希望時間
	if( ( strcmp( zok->hkkkbdh, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, zok->hkkkbdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "報告希望時間 妥当性エラーのため初期値置換[%s]"
			, zok->hkkkbdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// 初期値をセット
		strcpy( zok->hkkkbdh, INIT_TIME );
	}

	// TIMESTAMP 妥当性チェック
	// 属性登録日時
	if( ( strcmp( zok->zstrdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zstrdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "属性登録日時 妥当性エラーのため初期値置換[%s]"
			, zok->zstrdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// 初期値をセット
		strcpy( zok->zstrdh, INIT_TIMESTAMP );
	}
	// 属性修正日時
	if( ( strcmp( zok->zsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->zsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "属性修正日時 妥当性エラーのため初期値置換[%s]"
			, zok->zsssdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// 初期値をセット
		strcpy( zok->zsssdh, INIT_TIMESTAMP );
	}
	// サテライト内属性修正日時
	if( ( strcmp( zok->stlzsssdh, INIT_TIMESTAMP ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIMESTAMP, zok->stlzsssdh )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "サテライト内属性修正日時 妥当性エラーのため"
			"初期値置換[%s]"
			, zok->stlzsssdh );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
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
				sprintf( G_msg, "年齢 妥当性エラー[%s]" , zok->age );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__);
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
			sprintf( G_msg, "年齢区分エラー[%s]" , zok->agekbn );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 初期値をセット
			strcpy( zok->agekbn, AGEKBN_UNKNOWN );
		}
	//	性別区分
	if(   ( strcmp( zok->sbtkbn, SEX_MALE   ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_FEMALE ) != 0 )
		&&( strcmp( zok->sbtkbn, SEX_UNKNOWN ) != 0 )){
			// WARNING
			sprintf( G_msg, "性別区分エラー[%s]", zok->sbtkbn );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 初期値をセット
			strcpy( zok->sbtkbn, SEX_UNKNOWN );
	}

	// iniファイルでのDEBUG指定時のみprint処理を実行
	if( stcPRM.myp_debug == 1 ){
		zoku_pr( zok );
	};
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：NameKeyMake                                                   */
/*  機能概要  ：患者名キー作成                                                */
/*  入    力  ：                                                              */
/*   第１引数 ：char	kan_name[];	: S-JIS 患者カナ氏名                      */
/*   第２引数 ：int		len;		: S-JIS 患者カナ氏名length                */
/*  出    力  ：                                                              */
/*   第１引数 ：char	name_key[];	: S-JIS 患者名キー                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		NameKeyMake( name_key, kan_name, len )
char		name_key[];		/*	[O]	患者名キー	*/
char		kan_name[];		/*	[I]	患者名		*/
int			len;			/*	[I]	患者名length	*/
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
			case 0xa1:		/*  。   */
			case 0xa2:		/*  「   */
			case 0xa3:		/*  」   */
			case 0xa4:		/*  、   */
			case 0xa5:		/*  ・  */
			case 0xb0:		/*     */
			case 0xde:		/*  ﾞ   */
			case 0xdf:		/*  ﾟ   */
			case 0x20:		/*  " " */
				break;
			case 0xa7:		/*	ｧ	*/
				keyj[j]  =  0xb1;
				j++;
				break;
			case 0xa8:		/*	ｨ	*/
				keyj[j]  =  0xb2;
				j++;
				break;
			case 0xa9:		/*	ｩ	*/
				keyj[j]  =  0xb3;
				j++;
				break;
			case 0xaa:		/*	ｪ	*/
				keyj[j]  =  0xb4;
				j++;
				break;
			case 0xab:		/*	ｫ	*/
				keyj[j]  =  0xb5;
				j++;
				break;
			case 0xac:		/*	ｬ	*/
				keyj[j]  =  0xd4;
				j++;
				break;
			case 0xad:		/*	ｭ	*/
				keyj[j]  =  0xd5;
				j++;
				break;
			case 0xae:		/*	ｮ	*/
				keyj[j]  =  0xd6;
				j++;
				break;
			case 0xaf:		/*	ｯ	*/
				keyj[j]  =  0xc2;
				j++;
				break;
			default:
				/* 制御文字?  0x00-0x1F,0x7F */
				if( iscntrl( name[i] ) != 0 ){
					/* 制御文字は除外 */
					j++;
					break;
				}
				/* ASCII文字内でALPHABET以外は除外する */
				if( isprint( name[i] ) != 0 ){
					if( isalpha( name[i] ) == 0 ){
						/* 英文字以外は除外 */
						break;
					}
					/* alphabet letter count */
					a++;
				}
				/* 半角カナ or ALPHABET */
				keyj[j]  =  name[i];
				j++;
				break;
			}
	}
	/* 全てALPHABETの場合2文字以下は空白に置き換え	*/
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
/*  関 数 名  ：EditCsvMsg                                                    */
/*  機能概要  ：ログ出力メッセージCSV編集                                     */
/*  入    力  ：                                                              */
/*   第１引数 ： char	msg[];	    : メッセージ内容                          */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK			    : 正常終了                                */
/*               以外				: 失敗                                    */
/******************************************************************************/
int		EditCsvMsg( msg )
char		msg[];	
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];            /* 関数名称     */
	int		ret=RTN_OK;
	char	buf[MYAPP_LEN_MSG+1];
	char	w_str[10+1];

 	/* 初期処理     */
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
		// 1 種別・2ファイル名・3行No・4処理年月日
		// 5 BML受付日・6属性検体NO・7依頼書NO・8項目コード
		// 9 詳細
		, MYAPP_APPLNAME, G_fnm, w_str, stcPRM.myp_kjnymd
		, G_utkymd, MYAPP_SPACE10, G_irino, MYAPP_SPACE10
		, msg
	);
	strcpy( msg, buf );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：zoku_pr                                                       */
/*  機能概要  ：患者属性構造体printf                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA		*zok;	: 患者情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		zoku_pr( in )
struct		_KANJYA		*in;		/* 属性データ	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	strcpy( func_nm, "zoku_pr" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	printf( "患者属性データ{\n" );

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
