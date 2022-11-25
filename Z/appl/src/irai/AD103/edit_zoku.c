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
/*  2.01     2006/10/03     INTEC.INC      備考の項目の妥当性チェック追加     */
/*  2.02     2007/01/31     INTEC.INC      患者属性項目の数値チェック追加     */
/*  2.03     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応*/
/*                                         属性世代No展開不具合修正           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD103.h"

/******************************************************************************/
/*  関 数 名  ：EditPncKanjya                                                 */
/*  機能概要  ：ＰＮＣ属性データ編集 ＆　チェック                             */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  Z02SJIR1    *inp;	: PNC依頼情報                     */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA		*zok;	: 患者情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditPncKanjya( inp, zok )
struct		Z02SJIR1	*inp;		/* PNC依頼情報(S-JIS)	*/
struct		_KANJYA		*zok;		/* 患者情報構造体		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* 初期処理	*/
	strcpy(func_nm, "EditPncKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

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
	zok->zssdino	= stcPRM.myp_sedai;

	// ログ出力用キー項目設定
	strcpy( G_utkymd,	zok->utkymd );
	strcpy( G_irino,	zok->irino );
	G_zssdino=zok->zssdino;

	//----------------------------------------------------	
	// キー項目編集済
	//	-> 削除フラグ='1'ならば処理を抜ける
	//----------------------------------------------------	
	if( inp->c_zokdel_flg[0] == '1' ){
		// WARNING
		sprintf( G_msg, "属性削除データを受信しました（データ読み飛ばし）。" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_SKIP );
	}

	//----------------------------------------------------	
	// キー項目編集済
	//----------------------------------------------------	
/*  2.03     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 -->*/
	if( inp->c_zokupd_flg[0] == '1' ){						/* 修正フラグ = '1'なら属性修正 */
		if(( ret = SelKanjyaZssdinoMax( zok )) == RTN_OK ){	/* 既に展開済みの属性情報かをチェック */
			;												/* 展開済みなら何もしない。属性世代Noは"0"固定 */
		}
		else{												/* 展開していない場合 */
															/* 翌日持ち越しの修正確定 */
			zok->zssdino=100;								/* 属性世代Noは"100"固定 */
			// WARNING
			sprintf( G_msg, 
				"属性修正対象データ取得エラーのため属性世代NOを[%d]に"
				"置換し処理します。", zok->zssdino );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
	}
//	-> 修正フラグ='1'ならばMAX(属性世代Ｎｏ)+1 取得
// 	if( inp->c_zokupd_flg[0] == '1' ){
// 		if(( ret = SelKanjyaZssdinoMax( zok )) == RTN_OK ){
// 			// COUNT UP	
// 			zok->zssdino++;
// 		} else {
// 			// 属性世代NO置換
// 			zok->zssdino=100;
// 
// 			// WARNING
// 			sprintf( G_msg, 
// 				"属性修正対象データ取得エラーのため属性世代NOを[%d]に"
// 				"置換し処理します。", zok->zssdino );
// 			EditCsvMsg( G_msg );
// 			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__);
// 		}
// 	}
/*  2.03     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 <--*/	
	// 5 施設コード
	memcpy( zok->sstcd,		inp->c_siset_cd,sizeof( inp->c_siset_cd ));
	// 6 サブ施設コード
	memcpy( zok->subsstcd,	inp->c_subsiset_cd,sizeof( inp->c_subsiset_cd ));
	// 7 カード区分1
	memcpy( zok->cdkbn1,	inp->c_card1_kbn,sizeof( inp->c_card1_kbn ));
	// 8 カード区分2
	memcpy( zok->cdkbn2,	inp->c_card2_kbn,sizeof( inp->c_card2_kbn ));

	// 9 依頼元キー
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->irimkey, memcpy(buf, inp->c_iraimoto_key, 
		sizeof( inp->c_iraimoto_key )), sizeof( zok->irimkey ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【依頼元キー】[%s]"
			,zok->irimkey );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 10 診療科コード	
	memcpy( zok->srkcd,		inp->c_ka_cd,	sizeof( inp->c_ka_cd ));

	// 11 診療科名
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->srknm, memcpy(buf, inp->c_ka_nm, 
		sizeof( inp->c_ka_nm )), sizeof( zok->srknm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【診療科名】[%s]"
			,zok->srknm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 12 担当医コード	
	memcpy( zok->tticd,		inp->c_dr_cd,	sizeof( inp->c_dr_cd ));

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
	memcpy( zok->knjid,		inp->c_kanja_id,sizeof( inp->c_kanja_id ));

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
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->knjnmk, memcpy(buf, inp->c_kanja_knm, 
		sizeof( inp->c_kanja_knm )), sizeof( zok->knjnmk ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【患者名（漢字）】[%s]"
			,zok->knjnmk );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 全角スペースで埋める
	for( w_num=strlen(zok->knjnmk);w_num < sizeof(zok->knjnmk)-1;w_num+=2 ){
		memcpy( &zok->knjnmk[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 22 患者名キー
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
		sprintf( G_msg, "SJIS->EUC コード変換エラー【患者名キー】[%s]"
			,zok->knjnmkey );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// DEBUG
	sprintf( G_msg, "NameKeyMake [%s]->[%s]", zok->knjnmn, zok->knjnmkey);
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 23 身長	
	memcpy( zok->sc,		inp->c_tall,	sizeof( inp->c_tall ));

		// 2.02 ADD STA	身長、体重の数値チェックを行う（材料問わず）
	if( memcmp( inp->c_tall, MYAPP_SPACE10, sizeof( inp->c_tall )) != 0 ){
		//　妥当性チェック
		if( isCorrectChar( zok->sc ) != RTN_OK ) {
			// ERROR
			sprintf( G_msg, "身長エラーのためスペースに置換[%5.5s]" , inp->c_tall );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// NULLを設定
			memset( zok->sc, 0x00, sizeof( zok->sc ));
		}
	}
	// 2.02 ADD END

	// 24 体重
	memcpy( zok->tj,		inp->c_weight,	sizeof( inp->c_weight ));

		// 2.02 ADD STA	身長、体重の数値チェックを行う（材料問わず）
	if( memcmp( inp->c_weight, MYAPP_SPACE10, sizeof( inp->c_weight )) != 0 ){
		//　妥当性チェック
		if( isCorrectChar( zok->tj ) != RTN_OK ) {
			// ERROR
			sprintf( G_msg, "体重エラーのためスペースに置換[%5.5s]" , inp->c_weight );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// NULLを設定
			memset( zok->tj, 0x00, sizeof( zok->tj ));
		}
	}
	// 2.02 ADD END

	// 25 体重区分
	memcpy( zok->tjtni,		inp->c_weight_kbn,sizeof( inp->c_weight_kbn));
	// 26 性別区分
	memcpy( zok->sbtkbn,	inp->c_sex,	sizeof( inp->c_sex ));
	// 27 生年月日
	memcpy( zok->birthday,	inp->c_birth_ymd,	sizeof( inp->c_birth_ymd ));
	// 28 生年月日区分
	memcpy( zok->birthdaykbn,inp->c_birth_kbn,sizeof( inp->c_birth_kbn ));
	// 29 年齢
	memcpy( zok->age,		inp->c_age,	sizeof( inp->c_age ));
	// 30 年齢区分
	memcpy( zok->agekbn,	inp->c_age_kbn,sizeof( inp->c_age_kbn ));
	// 31 病棟コード
	memcpy( zok->btcd,		inp->c_byoto_cd,sizeof( inp->c_byoto_cd ));

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
	memcpy( zok->utkcmtcd1,	inp->c_ukecmt1_cd,sizeof( inp->c_ukecmt1_cd));
	// 34 受付コメント2
	memcpy( zok->utkcmtcd2,	inp->c_ukecmt2_cd,sizeof( inp->c_ukecmt2_cd));
	// 35 受付コメント3
	memcpy( zok->utkcmtcd3,	inp->c_ukecmt3_cd,sizeof( inp->c_ukecmt3_cd));

	// 36 受付コメントフリー1
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->utkcmtfr1, memcpy(buf, inp->c_ukecmt1_cmt, 
		sizeof( inp->c_ukecmt1_cmt )), sizeof( zok->utkcmtfr1 ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【受付コメントフリー1】[%s]"
			,zok->utkcmtfr1 );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 37 受付コメントフリー2
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->utkcmtfr2, memcpy(buf, inp->c_ukecmt2_cmt, 
		sizeof( inp->c_ukecmt2_cmt )), sizeof( zok->utkcmtfr2 ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【受付コメントフリー2】[%s]"
			,zok->utkcmtfr2 );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 38 受付コメントフリーフラグ	zok->utkcmtfrflg
	strcpy( zok->utkcmtfrflg, "0" );
	// 39 入院外来区分
	memcpy( zok->ngkbn,		inp->c_ng_kbn,	sizeof( inp->c_ng_kbn ));
	// 40 妊娠週数
	memcpy( zok->nsssu,		inp->c_ninsin_cnt,sizeof( inp->c_ninsin_cnt ));
	// 41 保険コード
	memcpy( zok->hkncd,		inp->c_hoken_cd,sizeof( inp->c_hoken_cd ));
	// 42 検体総本数		zok->ktshsu
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
	memcpy( zok->nekbn,		inp->c_ne_kbn,	sizeof( inp->c_ne_kbn ));
	// 49 院内検査区分		zok->inknskbn
	// 50 受付状態区分 		zok->utkjkkbn
	// 51 完了フラグ	
	strcpy( zok->krflg,	"0" );
	// 52 ＦＤ非報告フラグ
	memcpy( zok->fdhhkkflg,	inp->c_hifd_flg,sizeof( inp->c_hifd_flg ));

	// 53 受付時刻
	if( strncmp( inp->c_uke_time, MYAPP_SPACE10, 4 ) == 0 ){
		strcpy( zok->utkdh,	INIT_TIME );
	} else {
		sprintf( zok->utkdh,	"%.2s:%.2s:00",
			inp->c_uke_time,	&inp->c_uke_time[2] );
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
		// 営業所マスタより編集 -> PNCでは空白とする
	//cret=GetEigmst( zok->ecd, zok->shcd,	stcPRM.myp_kjnymd, zok->ymhkkflg );

	// 61 報告希望時間
	strcpy( zok->hkkkbdh,	INIT_TIME );

	// 62 営業所コード
	memcpy( zok->ecd,inp->c_eigyo_cd,	sizeof( inp->c_eigyo_cd ));
	// 63 集配コード
	memcpy( zok->shcd,inp->c_syuhai_cd,	sizeof( inp->c_syuhai_cd ));

	// 64 施設名正式名称
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstssnmj, memcpy(buf, inp->c_siset_knm, 
		sizeof( inp->c_siset_knm )), sizeof( zok->sstssnmj ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【施設名正式名称】[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 全角スペースで埋める
	for( w_num=strlen(zok->sstssnmj);w_num < sizeof(zok->sstssnmj)-1;w_num+=2 ){
		memcpy( &zok->sstssnmj[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 65 施設名正式名称（カナ）
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstssnmn, memcpy(buf, inp->c_siset_nm, 
		sizeof( inp->c_siset_nm )), sizeof( zok->sstssnmn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【施設名正式名称（カナ）】"
			"[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 66 施設名略称
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstrsj, memcpy(buf, inp->c_sisetr_knm, 
		sizeof( inp->c_sisetr_knm )), sizeof( zok->sstrsj ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【施設名略称】[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		// 全角スペースで埋める
	for( w_num=strlen(zok->sstrsj);w_num < sizeof(zok->sstrsj)-1;w_num+=2 ){
		memcpy( &zok->sstrsj[w_num], MYAPP_KJSPACE10, 2 );
	}
		// ALL 全角スペースの場合、正式名称より編集
	if( strcmp( zok->sstrsj, MYAPP_KJSPACE10 ) == 0 ){
		memcpy( zok->sstrsj, zok->sstssnmj, sizeof( zok->sstrsj ) - 1 );
	}

	// 67 施設名略称（カナ）
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->sstrsn, memcpy(buf, inp->c_sisetr_nm, 
		sizeof( inp->c_sisetr_nm )), sizeof( zok->sstrsn ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【 施設名略称（カナ）】"
			"[%s][%s]"
			,zok->sstcd ,zok->sstssnmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 68 施設種別
	memcpy( zok->sstsbt,inp->c_siset_kbn,	sizeof( inp->c_siset_kbn ));
	// 69 特定施設フラグ
	memcpy( zok->ttsstflg,inp->c_tokutei_flg,sizeof( inp->c_tokutei_flg));

	// 70 理由コード
	memset( buf,	0x00,	sizeof( buf ));
	cret=sj2euc( zok->rucd, memcpy(buf, inp->c_riyu_cd, 
		sizeof( inp->c_riyu_cd )), sizeof( zok->rucd ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【理由コード】[%s]"
			,zok->rucd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
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

/* 2.01 ADD STA */
	// 採取年月日 採取時間 妥当性チェック
	if( memcmp( inp->c_saisyu_ymd, MYAPP_SPACE10, sizeof(inp->c_saisyu_ymd) ) != 0 ){
		memset( w_str, 0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_saisyu_ymd,	sizeof( inp->c_saisyu_ymd ));
		if( ValidDate( VALDATE_DATE, w_str ) == RTN_NG ){
				// ERROR --> CONV
			sprintf( G_msg, "採取年月日 妥当性エラーのため初期値置換[%s]"
				, w_str );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
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
				// ERROR --> CONV
			sprintf( G_msg, "採取時間 妥当性エラーのため初期値置換[%4.4s]", w_str );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 初期値をセット
			memcpy( inp->c_saisyu_time, MYAPP_SPACE10, sizeof(inp->c_saisyu_time));
		}
	}
/* 2.01 ADD END */

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
	// 1.01 ADD	88 親施設コード
	strcpy( zok->oyasstcd,	zok->sstcd );
	// 1.01 ADD	89 登録日時	CURRENT TIMESTAMP

	//=========================================
	//	CHECK
	//=========================================
	// 材料が蓄尿量の場合、属性情報をワーニングチェックする
	if(( strlen( stcPRM.myp_zairyo ) != 0 )
	 &&( memcmp( stcPRM.myp_zairyo, inp->c_zairyo01_cd, 3 ) == 0 )){
		// 身長	c_tall
		if( memcmp( inp->c_tall, MYAPP_SPACE10, sizeof( inp->c_tall )) == 0 ){
			// WARNING
			sprintf( G_msg, "蓄尿 身長エラー[%.5s]" , inp->c_tall );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		} else {
			//　妥当性チェック
			memset( buf, 	0x00, sizeof( w_str ));
			memset( w_str,	0x00, sizeof( w_str ));
			memcpy( buf,	inp->c_tall, sizeof( inp->c_tall ));
			strncpy( w_str,	buf,	strcspn( buf, "." ));
			w_num = atoi( w_str );
			if(( w_num < 1 ) || ( w_num > 250 )){
				// WARNING
				sprintf( G_msg, "蓄尿 身長エラー[%.5s]", inp->c_tall );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
											__FILE__, __LINE__);
			}
		}
		// 体重 c_weight
		if( memcmp( inp->c_weight, MYAPP_SPACE10
					, sizeof( inp->c_weight )) == 0 ){
			// WARNING
			sprintf( G_msg, "蓄尿 体重エラー[%.5s]\n" , inp->c_weight );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		} else {
			//　妥当性チェック
			memset( buf, 	0x00, sizeof( w_str ));
			memset( w_str,	0x00, sizeof( w_str ));
			memcpy( buf,	inp->c_weight, sizeof( inp->c_weight ));
			strncpy( w_str,	buf,	strcspn( buf, "." ));
			w_num = atoi( w_str );
			if( w_num < 1 ){
				// WARNING
				sprintf( G_msg, "蓄尿 体重エラー[%.5s]", inp->c_weight );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, 
												__FILE__, __LINE__);
			}
		}
		// 蓄尿時間	c_nyotime
		if( memcmp( inp->c_nyotime, MYAPP_SPACE10
					, sizeof( inp->c_nyotime )) == 0 ){
			// WARNING
			sprintf( G_msg, "蓄尿 蓄尿時間エラー[%.4s]" ,inp->c_nyotime );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		// 蓄尿量	c_nyoryo
		if( memcmp( inp->c_nyoryo, MYAPP_SPACE10
				, sizeof( inp->c_nyoryo )) == 0 ){
			// WARNING
			sprintf( G_msg, "蓄尿 蓄尿量エラー[%.5s]" ,inp->c_nyoryo );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  関 数 名  ：EditNxtKanjya                                                 */
/*  機能概要  ：次世代患者属性データ編集                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  Z02SJIR1    *inp;	: PNC依頼情報                     */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA		*zok;	: 患者情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditNxtKanjya( zok )
struct	_KANJYA	*zok;	/* 属性データ	*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* 初期処理	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditNxtKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  関 数 名  ：EditCommonKanjya                                              */
/*  機能概要  ：患者属性データ共通編集＆チェック                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA		*zok;	: 患者情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditCommonKanjya( zok )
struct		_KANJYA		*zok;	// 患者属性構造体
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int		ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;

	strcpy( func_nm, "EditCommonKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	CHECK
	//=========================================
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
/*  関 数 名  ：GetEigmst                                                     */
/*  機能概要  ：営業所マスタ情報取得                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：char   eigyo_cd[]; 		: 営業所コード                        */
/*   第２引数 ：char   ymd[]; 			: 対象日(YYYY/MM/DD)                  */
/*  出    力  ：                                                              */
/*   第１引数 ：char   kbn[]; 			: 翌日報告区分                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/*	特機事項  ：当関数はR1のINSERT前に呼ばれTRANSACTIONに影響が無いため       */
/*			  ：COMMITを入れる                                                */
/******************************************************************************/
int		GetEigmst( eigyo_cd, syuhai_cd, ymd, kbn )
char		eigyo_cd[];				/* 営業所ｺｰﾄﾞ	*/
char		syuhai_cd[];			/* 集配ｺｰﾄﾞ		*/
char		ymd[];					/* 基準日		*/
char		kbn[];					/* 翌日報告区分	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];			/* 関数名称	*/
	int		ret;
	int		pos;
static	int	init_flg = 0;			/* ｲﾆｼｬﾙﾌﾗｸﾞ	*/
static	struct	_EIGMST sv_m02[MYAPP_MAX_EIGMST];/* 営業所ﾏｽﾀ(保存用)	*/

	/* 初期処理	*/
	strcpy( func_nm, "EigmstGet" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* 営業所ﾏｽﾀの獲得	*/
	if( init_flg == 0 ){
		/* 営業所ﾏｽﾀ初期ｸﾘｱ	*/
		memset( sv_m02, '\0', sizeof( sv_m02 ));
		init_flg = 1;
	}

	for( pos = 0; pos < MYAPP_MAX_EIGMST
		&& strlen(  sv_m02[pos].ecd ) != 0; ++pos ){
		if( strcmp( sv_m02[pos].ecd, eigyo_cd ) == 0 ){
			// 集配コード開始日終了日判断
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

	/* 営業所ﾏｽﾀの獲得	*/
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
			// 初期値は？ 1:翌日報告対象外
		strcpy( kbn, "1" );
		return( ret );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：EditPncChikenzok                                              */
/*  機能概要  ：ＰＮＣ治験データ編集 ＆　チェック                             */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  Z04SJIR2    *inp;	: PNC依頼情報                     */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _CHIKENZOK	*zok;	: 治験拡張構造体                  */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditPncChikenzok( inp, zok )
struct		Z04SJIR2	*inp;		/* PNC依頼情報(S-JIS)   */
struct		_CHIKENZOK	*zok;		/* 治験拡張構造体		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* 初期処理	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditChikenkzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 ＢＭＬ受付年月日
	sprintf( zok->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 依頼書Ｎｏ
	sprintf( zok->irino,	"00%03.3s%-6.6s"
		,inp->c_irai_no	,&inp->c_irai_no[5] );

	// 3 依頼書Ｎｏ桁数フラグ
	zok->iriketflg[0] = ' ';

	// 4 属性世代Ｎｏ
	zok->zssdino = stcPRM.myp_sedai;

	// ログ出力用キー項目設定
	strcpy( G_utkymd,	zok->utkymd );
	strcpy( G_irino,	zok->irino );
	G_zssdino=zok->zssdino;

	// 5 治験・プロトコルＮｏ
	memcpy( zok->prtclno,	inp->c_protcol_no,sizeof( inp->c_protcol_no ));
	// 6 治験・子施設コード
	memcpy( zok->kosstcd,	inp->c_ko_siset_cd,sizeof( inp->c_ko_siset_cd ));
	// 7 治験・投与時間
	memcpy( zok->tytme,		inp->c_toyotime,sizeof( inp->c_toyotime ));
	// 8 治験・投与量(量)
	memcpy( zok->tyryo,		inp->c_toyoryo,sizeof( inp->c_toyoryo ));
	// 9 治験・投与量(単位)
	memcpy( zok->tyryotni,	inp->c_toyoryo_kbn,sizeof( inp->c_toyoryo_kbn ));
	// 10 治験・薬剤負荷時間
	memcpy( zok->yzfktme,	inp->c_drfuka_time,sizeof( inp->c_drfuka_time ));
	// 11 治験・一括アッセイフラグ
	memcpy( zok->ikasflg,	inp->c_ikassay_flg,sizeof( inp->c_ikassay_flg ));
	// 12 治験・検体数
	if( memcmp( inp->c_kentai_su, MYAPP_SPACE10
				, sizeof( inp->c_kentai_su )) == 0 ){
		zok->kntsu = 0;
	} else {
		memset( w_str,		0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_kentai_su,sizeof( inp->c_kentai_su ));
		zok->kntsu = atoi( w_str );
	}
	// 13 治験・項目数
	if( memcmp( inp->c_komoku_su, MYAPP_SPACE10
				, sizeof( inp->c_komoku_su )) == 0 ){
		zok->kmksu = 0;
	} else {
		memset( w_str, 		0x00, sizeof( w_str ));
		memcpy( w_str,		inp->c_komoku_su,	sizeof( inp->c_komoku_su ));
		zok->kmksu = atoi( w_str );
	}
	// 14 治験・採取ポイント	
	memcpy( zok->sspit,		inp->c_saisyu_po,sizeof( inp->c_saisyu_po ));
	// 15 治験・材料コード１
	memcpy( zok->zrcd01,	inp->c_zairyo01_cd,sizeof( inp->c_zairyo01_cd ));
	memcpy( zok->zrcd02,	inp->c_zairyo02_cd,sizeof( inp->c_zairyo02_cd ));
	memcpy( zok->zrcd03,	inp->c_zairyo03_cd,sizeof( inp->c_zairyo03_cd ));
	memcpy( zok->zrcd04,	inp->c_zairyo04_cd,sizeof( inp->c_zairyo04_cd ));
	memcpy( zok->zrcd05,	inp->c_zairyo05_cd,sizeof( inp->c_zairyo05_cd ));
	memcpy( zok->zrcd06,	inp->c_zairyo06_cd,sizeof( inp->c_zairyo06_cd ));
	// 21 治験・材料記号１
	memcpy( zok->zrkg01,	inp->c_zairyo01_kg,sizeof( inp->c_zairyo01_kg ));
	memcpy( zok->zrkg02,	inp->c_zairyo02_kg,sizeof( inp->c_zairyo02_kg ));
	memcpy( zok->zrkg03,	inp->c_zairyo03_kg,sizeof( inp->c_zairyo03_kg ));
	memcpy( zok->zrkg04,	inp->c_zairyo04_kg,sizeof( inp->c_zairyo04_kg ));
	memcpy( zok->zrkg05,	inp->c_zairyo05_kg,sizeof( inp->c_zairyo05_kg ));
	memcpy( zok->zrkg06,	inp->c_zairyo06_kg,sizeof( inp->c_zairyo06_kg ));
	// 27 治験・保留シーケンス
	memcpy( zok->hrseq,		inp->c_horyu_seq,sizeof( inp->c_horyu_seq ));
	// 28 治験・検体回収フラグ
	memcpy( zok->kntksflg,	inp->c_kaisyu_flg,sizeof( inp->c_kaisyu_flg ));
	// 29 治験・ＧＣＰフラグ
	memcpy( zok->gcpflg,	inp->c_gcp_flg,sizeof( inp->c_gcp_flg ));
	// 30 治験・プロトコル名称
	memset( buf, 			0x00, sizeof( buf ));
	cret=sj2euc( zok->prtclnm, memcpy(buf, inp->c_protocol_knm, 
		sizeof( inp->c_protocol_knm )), sizeof( zok->prtclnm ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【治験・プロトコル名称】[%s]"
			,zok->prtclnm );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：EditNxtChikenzok                                              */
/*  機能概要  ：次世代患者属性データ編集                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  Z02SJIR1    *inp;	: PNC依頼情報                     */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _KANJYA		*zok;	: 患者情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditNxtChikenzok( zok )
struct		_CHIKENZOK		*zok;	/* 属性データ	*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* 初期処理	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditNxtChikenzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  関 数 名  ：EditCommonChikenzok                                           */
/*  機能概要  ：治験拡張データ共通編集＆チェック                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _CHIKENZOK	*zok;	: 治験拡張                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditCommonChikenzok( zk )
struct	_CHIKENZOK	*zk;		/* 属性データ	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[20];

	strcpy( func_nm, "EditCommonChikenzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// iniファイルでのDEBUG指定時のみprint処理を実行
	if( stcPRM.myp_debug == 1 ){
		chiken_pr( zk );
	};

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：EditCsvKanjya                                                 */
/*  機能概要  ：患者情報のCSV形式でのテキスト出力                             */
/*  入    力  ：                                                              */
/*   第１引数 ： struct	_KANJYA	kan;  : 患者情報構造体                        */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK             : 正常                                    */
/*               RTN_NG             : エラー                                  */
/******************************************************************************/
int		EditCsvKanjya( kan )
struct		_KANJYA		*kan;
{
	char	func_nm[30];		/* 関数名称	*/
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
/*  関 数 名  ：chiken_pr                                                     */
/*  機能概要  ：治験拡張構造体printf                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _CHIKENZOK	*in;	: 治験拡張                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		chiken_pr( in )
struct		_CHIKENZOK		*in;		/* 属性データ	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int		ret;

	strcpy( func_nm, "chiken_pr" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	printf( "治験拡張データ{\n" );

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
/*  関 数 名  ：isCorrectChar                                                 */
/*  機能概要  ：患者属性数値エリアチェック                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： char	In[];	    : チェック文字列                          */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK			    : 正常終了                                */
/*               以外				: 失敗                                    */
/******************************************************************************/
int isCorrectChar(char *In)
{
 	char    func_nm[MYAPP_LEN_FNCNM+1];            /* 関数名称     */
	int		ret=RTN_OK;
	char	buf[MYAPP_LEN_MSG+1];
	char	w_str[10+1];

    int i = 0;
    int nSuziFlg =0; //初めが数字かとうか検索
    int nMaxNum = strlen(In);

 	/* 初期処理     */
 	strcpy( func_nm, "isCorrectChar" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	memset( buf,	'\0', sizeof( buf ));
	memset( w_str,	'\0', sizeof( w_str ));

    for(i=0;i<nMaxNum;i++)
    {
        if(In[i] == ' '){
            if(nSuziFlg == 1){
				// DEBUG
				sprintf( G_msg, "数値 数字中にSPACE[%s]" , In );
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
				sprintf( G_msg, "数値 先頭.不可[%s]" , In );
				EditCsvMsg( G_msg );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
						, __FILE__, __LINE__);
				// ERROR
				ret=RTN_NG;
                break;
            }
            if(nSuziFlg == 0){
				// DEBUG
				sprintf( G_msg, "数値 先頭.不可[%s]" , In );
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
			sprintf( G_msg, "数値 空白.以外不可[%s]" , In );
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
