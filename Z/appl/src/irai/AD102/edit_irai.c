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
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(登録日時)対応        */
/*  1.04     2006/06/26     INTEC.INC      自動発生項目登録＋検査G編集追加    */
/*  2.01     2006/09/28     INTEC.INC      集検万台404の追加                  */
/*  2.02     2008/04/24     sekiya         集検万台426の追加                  */
/*  2.03     2011/09/29     sekiya         集検万台790の追加                  */
/*  2.04     2013/08/xx     sekiya         集検万台590の追加                  */
/*  2.05     2015/10/13     sekiya         集検万台380,381の追加              */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD102.h"

/******************************************************************************/
/*  関 数 名  ：EditPncIrai                                                 */
/*  機能概要  ：ＰＮＣ依頼データ編集 ＆　チェック                             */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  Z02SJIR1    *inp;	: PNC依頼情報                     */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _IRAI		*iri;	: 依頼情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditPncIrai( inp, iri )
struct		Z05SJIR1	*inp;		/* PNC依頼情報(S-JIS)	*/
struct		_IRAI		*iri;		/* 依頼情報構造体		*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	buf2[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;							// コード変換戻り値
	struct	stcKJNO		kj;					// 基準値NO取得用構造体

	/* 初期処理	*/
	strcpy(func_nm, "EditPncIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 ＢＭＬ受付年月日
	sprintf( iri->utkymd,	"%.4s-%.2s-%.2s"
		,inp->c_bml_ymd	,&inp->c_bml_ymd[4]	,&inp->c_bml_ymd[6] );

	// 2 依頼書Ｎｏ
	sprintf( iri->irino,	"00%-3.3s%-6.6s"
		,inp->c_irai_no	,&inp->c_irai_no[5] );
		// DEBUG
	sprintf( G_msg, "irino [%.11s]->[%s]", inp->c_irai_no, iri->irino );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 3 依頼書Ｎｏ桁数フラグ
	iri->iriketflg[0] = ' ';
	// 4 依頼世代Ｎｏ
		iri->zssdino	= stcPRM.myp_sedai;

	// 5 検査グループ
		// 1.04 			-> EditCommonIrai
	// 6 項目コード
	memcpy( iri->kmkcd,		inp->c_koumoku_cd,sizeof( inp->c_koumoku_cd ));

	// 7 依頼発生元区分		-> EditCommonIrai
	// 8 依頼区分			-> EditCommonIrai
	// 9 検査工程区分		-> EditCommonIrai
	// 10 処理日			-> EditCommonIrai

	// 11 検体Ｎｏ
	sprintf( iri->kntno,"00%03.3s%-6.6s"
		,inp->c_kentai_no	,&inp->c_kentai_no[5] );
		// DEBUG
	sprintf( G_msg, "kntno [%.11s]->[%s]", inp->c_kentai_no, iri->kntno );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	// 12 検体Ｎｏ桁数フラグ
	iri->kntketflg[0] = ' ';

	// ログ出力用キー項目設定
	strcpy( G_utkymd,	iri->utkymd );
	strcpy( G_irino,	iri->irino );
	G_zssdino=iri->zssdino;
	strcpy( G_kmkcd,	iri->kmkcd );
	strcpy( G_kntno,	iri->kntno );

	//----------------------------------------------------	
	// キー項目編集済
	//	-> 削除フラグ='1'ならば処理を抜ける
	//----------------------------------------------------	
	if( inp->c_del_flg[0] == '1' ){
		// WARNING
		sprintf( G_msg, "依頼削除データを受信しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_SKIP );
	}

	// 13 チェック文字（やっぱり必要）
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->chkmj, memcpy(buf, inp->c_kentai_ch, 
		sizeof( inp->c_kentai_ch )), sizeof( iri->chkmj ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【チェック文字】[%s]"
			,iri->chkmj );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 14 推定材料コード
	memcpy( iri->stsrcd,	inp->c_szairyo_cd,sizeof( inp->c_szairyo_cd ));

	// 15 項目略称
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->kmkrs, memcpy(buf, inp->c_koumoku_rnm, 
		sizeof( inp->c_koumoku_rnm )), sizeof( iri->kmkrs ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【項目略称】[%s]"
			,iri->kmkrs );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 16 親項目コード
	memcpy( iri->oyakmkcd,	inp->c_oya_cd,sizeof( inp->c_oya_cd ));
	// 17 サンプリングコード
	memcpy( iri->smpcd,		inp->c_ws_cd,sizeof( inp->c_ws_cd ));
	// 18 セット項目コード
	memcpy( iri->setkmkcd,	inp->c_set_cd,sizeof( inp->c_set_cd ));
	// 19 処理内容コード
	memcpy( iri->srinycd,	inp->c_naiyo_cd,sizeof( inp->c_naiyo_cd ));
	// 20 セクションコード
	memcpy( iri->seccd,	inp->c_section_cd,sizeof( inp->c_section_cd ));
	// 21 出荷チェックフラグ
	memcpy( iri->skchkflg,	inp->c_outchk_flg,sizeof( inp->c_outchk_flg ));
	// 22 分画負荷区分
	memcpy( iri->bkfkkbn,	inp->c_bunkaku_kbn,sizeof( inp->c_bunkaku_kbn ));
	// 23 優先レベル
	memcpy( iri->ysnlbl,	inp->c_yusen_lvl,sizeof( inp->c_yusen_lvl ));
	// 24 集検フラグ  依頼書NOの万台から判断
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
			sprintf( G_msg, "集検フラグ[%3.3s]!!", func_nm, inp->c_irai_no  );
			LogOut( LT_DBG, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
		};
	}

	// 25 追加フラグ	
	memcpy( iri->tkflg,	inp->c_add_flg,sizeof( inp->c_add_flg ));
	// 26 削除フラグ
	memcpy( iri->sjflg,	inp->c_del_flg,sizeof( inp->c_del_flg ));
	// 27 条件追加フラグ
	memcpy( iri->jktkflg,	inp->c_jokenadd_flg,sizeof( inp->c_jokenadd_flg ));

	// 28 基準値ＮＯ
	memcpy( iri->kjno,	inp->c_base_no,sizeof( inp->c_base_no ));
	if( strncmp( iri->kjno, MYAPP_SPACE10, sizeof( inp->c_base_no )) == 0 ){
		/* 基準値NOが未設定の場合、マスタから算出	*/
		memset( &kj,		'\0', sizeof( struct stcKJNO ));
		strcpy( kj.kmkcd,	iri->kmkcd );
		strcpy( kj.zrcd,	iri->stsrcd );
		memcpy( kj.age,		inp->c_age,		sizeof( inp->c_age ));
		memcpy( kj.agekbn,	inp->c_age_kbn,	sizeof( inp->c_age_kbn ));
		if( GetKjnmst( &kj ) != RTN_OK ){
			sprintf( G_msg,"該当する基準値マスタデータがありません。"
				"項目CD[%s]材料CD[%-4s]",
				iri->kmkcd, iri->stsrcd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
		strcpy( iri->kjno,	kj.kjno );	
	}

	// 29 負荷報告ＮＯ表示区分
	memcpy( iri->fkhkknohjkbn,	inp->c_fuka_no,sizeof( inp->c_fuka_no ));

	// 30 特別基準値ＮＯ
	// 31 特別基準値フラグ

	// 32 非定型負荷時間
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->htkfkhms, memcpy(buf, inp->c_hiteke_time, 
		sizeof( inp->c_hiteke_time )), sizeof( iri->htkfkhms ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【非定型負荷時間】[%s]"
			,iri->htkfkhms );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}
		 // 全角スペースで埋める
	for( w_num=strlen(iri->htkfkhms);w_num < sizeof(iri->htkfkhms)-1;w_num+=2 ){
		memcpy( &iri->htkfkhms[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 33 透析フラグ
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->tskflg, memcpy(buf, inp->c_toseki_flg, 
		sizeof( inp->c_toseki_flg )), sizeof( iri->tskflg ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【透析フラグ】[%s]"
			,iri->tskflg );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 34 凍結フラグ
	memset( buf, '\0', sizeof( buf ));
	cret=sj2euc( iri->tktflg, memcpy(buf, inp->c_toketu_flg, 
		sizeof( inp->c_toketu_flg )), sizeof( iri->tktflg ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【凍結フラグ】[%s]"
			,iri->tktflg );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

	// 33 透析フラグ
	// 34 凍結フラグ
	//	  理由コードの内容により上書きする
	memset( buf, '\0', sizeof( buf ));
	memset( buf2, '\0', sizeof( buf2 ));
	cret=sj2euc( buf2, memcpy(buf, inp->c_riyu_cd,
		sizeof( inp->c_riyu_cd)), sizeof( buf2 ));
		// WARNING
	if( cret != RTN_OK ){
		sprintf( G_msg, "SJIS->EUC コード変換エラー【理由コード】[%s]"
			,buf2 );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	}

		// 透析フラグ
	if( strcmp( buf2, "ｾ" ) == 0 || strcmp( buf2, "ｺ" ) == 0 ){
		strcpy( iri->tskflg, buf2 );
	}
		// 凍結フラグ
	if(strcmp(buf2,"ｳ")== 0||strcmp(buf2,"ﾄ")==0||strcmp(buf2,"ｶ")==0){
		strcpy( iri->tktflg, buf2 );
	}

	// 35 分注区分
	memcpy( iri->bnckbn,	inp->c_buncyu_kbn,sizeof( inp->c_buncyu_kbn ));
	// 36 尿分注区分
	memcpy( iri->nbnckbn,	inp->c_nbuncyu_kbn,sizeof( inp->c_nbuncyu_kbn ));
	// 37 検査開始予定日
	strcpy( iri->knskisyymd,INIT_DATE );
	// 38 検査完了予定日
	strcpy( iri->knskryymd,	INIT_DATE );
	// 39 検査完了予定時間
	strcpy( iri->knskrytme,	INIT_TIME );
	// 40 緊急報告フラグ
	iri->kkhkkflg[0] = '0';
	// 41 緊急依頼フラグ
	iri->kkiriflg[0] = '0';
	// 42 緊急依頼ロットＮｏ
	iri->kkirilotno = 0;
	// 43 緊急対応受付ＩＤ
	strcpy( iri->kktoutkid,	" " );
	// 44 検査回数
	iri->knssu = 0;

	// 45 オーダ作成フラグ
	// 46 予定希釈倍率

	// 47 報告状況フラグ
	strcpy( iri->hhkjkflg,	" " );

	// 48 情報更新日時	CURRENT TIMESTAMP
	// 1.01 ADD	49 登録日時	CURRENT TIMESTAMP

	//=========================================
	//	CHECK
	//=========================================

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  関 数 名  ：EditNxtIrai                                                 */
/*  機能概要  ：次世代患者依頼データ編集                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  Z02SJIR1    *inp;	: PNC依頼情報                     */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _IRAI		*zok;	: 依頼情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditNxtIrai( iri )
struct	_IRAI	*iri;	/* 依頼データ	*/
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	size_t	cret;

	/* 初期処理	*/
	ret = RTN_OK;
	strcpy(func_nm, "EditNxtIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
/******************************************************************************/
/*  関 数 名  ：EditCommonIrai                                              */
/*  機能概要  ：患者依頼データ共通編集＆チェック                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _IRAI		*zok;	: 依頼情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditCommonIrai( iri )
struct		_IRAI		*iri;	// 患者依頼構造体
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
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
	// 5 検査グループ
	strcpy( iri->knsgrp, 	" " );
	// 1.04 ADD 検査CD+サンプリング+検査G.種別->コードが若い先頭１件目
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
		// 集検を想定して取得失敗の場合は、一般で再度取得し直す
		if( km.skflg[0] == '1' ){
			strcpy( km.skflg,	"0" );
			if( SelKnsgrp( &km, stcPRM.myp_kjnymd ) == RTN_OK ){
				strcpy( iri->knsgrp,	km.knsgrp );
					// DEBUG
				sprintf( G_msg
					, "検査G再取得OK!kmkcd[%s]smpcd[%s]skflg[%s] -> knsgrp[%s]"
					, iri->kmkcd, iri->smpcd, iri->skflg, iri->knsgrp );
				LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__ );
			} else {
				sprintf( G_msg,"一般集検共に該当する検査グループがありません。"
					"項目CD[%s]SMPCD[%s]集検F[%s]",
					iri->kmkcd, iri->smpcd, iri->skflg );
				EditCsvMsg( G_msg );
				LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__);
			}
		} else {
			sprintf( G_msg,"該当する検査グループがありません。"
				"項目CD[%s]SMPCD[%s]集検F[%s]",
				iri->kmkcd, iri->smpcd, iri->skflg );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// 7 依頼発生元区分		0:上位システム
	iri->irihsmkbn[0] = '0';
	
	// 8 依頼区分			A:通常
	iri->irikbn[0] = 'A';

	// 9 検査工程区分		A:通常
	iri->ksktkbn[0] = 'A';

	// 10 処理日			システム管理マスタ．基準処理日
	strcpy( iri->sriymd,	stcPRM.myp_kjnymd );

	// 30 特別基準値ＮＯ
	// 31 特別基準値フラグ
	strcpy( iri->tbkjno,		" " );
	strcpy( iri->tbkjflg,		" " );

	// 44 検査回数
	iri->knssu = 1;
	// 45 オーダ作成フラグ	空白:初期値
	iri->odrssflg[0] = ' ';
	// 46 予定希釈倍率
	iri->ytiksbr[0] = '1';

	//=========================================
	//	CHECK
	//=========================================
	// 妥当性チェック
	// サンプリングコードが未設定の場合はエラー
	if( strncmp( iri->smpcd, MYAPP_SPACE10, sizeof( iri->smpcd ) - 1 ) == 0 ){
			// ERROR 
		sprintf( G_msg, "サンプリングコードが未設定です。[%s]", iri->smpcd );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 
		return( RTN_NG );
	}

	// DATE 妥当性チェック
	// ＢＭＬ受付日
	if( ( strcmp( iri->utkymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, iri->utkymd )) == RTN_NG )){
			// ERROR
		sprintf( G_msg, "ＢＭＬ受付日 妥当性エラーのため初期値置換[%s]"
			, iri->utkymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 
		return( RTN_NG );
	}

	// 検査開始予定日
	if( ( strcmp( iri->knskisyymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, iri->knskisyymd )) == RTN_NG )){
			// ERROR --> CONV
		sprintf( G_msg, "検査開始予\定日 妥当性エラーのため初期値置換[%s]"
			, iri->knskisyymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// 初期値をセット
		strcpy( iri->knskisyymd, INIT_DATE );
	}

	// 検査完了予定日
	if( ( strcmp( iri->knskryymd, INIT_DATE ) != 0 )
	 &&(( ret = ValidDate( VALDATE_DATE, iri->knskryymd )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "検査完了予\定日 妥当性エラーのため初期値置換[%s]"
			, iri->knskryymd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// 初期値をセット
		strcpy( iri->knskryymd, INIT_DATE );
	}

	// TIME 妥当性チェック
	// 検査完了予定時間
	if( ( strcmp( iri->knskrytme, INIT_TIME ) != 0 )
	 &&(( ret = ValidDate( VALDATE_TIME, iri->knskrytme )) == RTN_NG )){
		// ERROR --> CONV
		sprintf( G_msg, "検査完了予\定時間 妥当性エラーのため初期値置換[%s]"
			, iri->knskrytme );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
		// 初期値をセット
		strcpy( iri->knskrytme, INIT_TIME );
	}

	// iniファイルでのDEBUG指定時のみprint処理を実行
	if( stcPRM.myp_debug == 1 ){
		irai_pr( iri );
	};
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}
// 1.04 ADD STA ==============================================================
/******************************************************************************/
/*  関 数 名  ：EditJidoIrai                                                  */
/*  機能概要  ：自動発生依頼編集                                              */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  JIDOIRAI		*jdi;	: 自動発生依頼情報            */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditJidoIrai( jdi )
struct		JIDOIRAI		*jdi;	// 自動発生依頼情報
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int		ret=RTN_OK;

	char	buf[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	struct	stcKJNO		kj;					// 基準値NO取得用構造体

	strcpy( func_nm, "EditJidoIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	自動発生依頼情報 EDIT
	//=========================================
	// 5 検査グループ
	strcpy( jdi->sIri.knsgrp,	jdi->sJdm.jknsgrp );
	// 6 項目コード
	strcpy( jdi->sIri.kmkcd,	jdi->sJdm.jkmkcd );
	// 7 依頼発生元区分
	if( jdi->sJdm.hhkumflg[0] == '0' ){				// 報告しない
		// サテライトシステム（報告無し）
		strcpy( jdi->sIri.irihsmkbn,	"2" );
	} else if( jdi->sJdm.hhkumflg[0] == '1' ){		// 報告する
		// サテライトシステム（報告有り）
		strcpy( jdi->sIri.irihsmkbn,	"1" );
	}
	// 15 項目略称
	strcpy( jdi->sIri.kmkrs,	jdi->sKmk.kmkrs );
	// 16 親項目コード
	strcpy( jdi->sIri.oyakmkcd,	jdi->sKmk.oyakmkcd );
	// 17 サンプリングコード
	strcpy( jdi->sIri.smpcd,	jdi->sKmk.smpcd );
	// 18 セット項目コード
	strcpy( jdi->sIri.setkmkcd,	"0000000" );
	// 19 処理内容コード
	strcpy( jdi->sIri.srinycd,	"2" );
	// 22 分画負荷区分
	strcpy( jdi->sIri.bkfkkbn,	jdi->sKmk.fkbnkkb );
	// 28 基準値ＮＯ
	memset( &kj,		'\0', sizeof( struct stcKJNO ));
	strcpy( kj.kmkcd,	jdi->sIri.kmkcd );
	strcpy( kj.zrcd,	jdi->sIri.stsrcd );
	strcpy( kj.age,		jdi->age );
	strcpy( kj.agekbn,	jdi->agekbn );
	if( GetKjnmst( &kj ) != RTN_OK ){
		sprintf( G_msg,"該当する基準値マスタデータがありません。"
			"項目CD[%s]材料CD[%-4s]",
			jdi->sIri.kmkcd, jdi->sIri.stsrcd );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
	}
	strcpy( jdi->sIri.kjno,		kj.kjno );	

	// 45 オーダ作成フラグ
	strcpy( jdi->sIri.odrssflg,	" " );

	// iniファイルでのDEBUG指定時のみprint処理を実行
	if( stcPRM.myp_debug == 1 ){
		irai_pr( &jdi->sIri );
	};
	
	// ログ出力用キー項目設定
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
/*  関 数 名  ：GetKjnmst                                                     */
/*  機能概要  ：基準値NO取得                                                  */
/*  入    力  ：                                                              */
/*   第１引数 ：struct	stcKJNO		*in;: 基準値NO取得用構造体                */
/*  出    力  ：                                                              */
/*   第１引数 ：int   kjno; 			: 基準値NO                            */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		GetKjnmst( in )
struct		stcKJNO		*in;	
{
	char	func_nm[MYAPP_LEN_FNCNM+1];			/* 関数名称	*/
static	int	init_flg = 0;
static  int  kj_max;
	int		ret;
	int 	i = 0;
	int		knichirei;
	char	keybuf[30];

	/* 初期処理	*/
	strcpy( func_nm, "GetKjnmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* 基準値マスタの獲得	*/
	if( init_flg == 0 ){
		// 対象基準値マスタの件数取得
		kj_max=SelCountKjnmst( stcPRM.myp_kjnymd );
		// 領域確保
		if(( pKjn = ((struct _KJNMST *)malloc( 
					sizeof(struct _KJNMST) * kj_max ))) == NULL ){
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, "基準値マスタの領域確保に失敗しました。" );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );
                return( RTN_NG );
		}
		/* 基準値マスタ退避領域の初期化	*/
		memset( pKjn, '\0', sizeof( struct _KJNMST ) * kj_max );

		// 対象基準値マスタの取得
		if( SelKjnmst( stcPRM.myp_kjnymd, kj_max ) !=  RTN_OK ){
				sprintf( G_err, "%d", errno );
				sprintf( G_msg, "基準値マスタの読み込みに失敗しました。" );
				LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, 
							__FILE__, __LINE__ );

				free( pKjn );
                return( RTN_NG );
		}
		//-----------------------------------------------------------------
		for ( i = 0; i < kj_max; i++ ){
			// 検索キーの設定
			sprintf( pKjn[i].kkey, "%-7s%-4s000", pKjn[i].kmkcd, pKjn[i].zrcd );
			// 日齢を数値変換する
			pKjn[i].knlow=atoi( pKjn[i].nichilw );
			pKjn[i].knhigh=atoi( pKjn[i].nichihi );
		}
		sprintf( G_msg, "基準値マスタ件数[%d]", kj_max );
		LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		init_flg = 1;
		return( RTN_OK );
	}

	// 日齢を求める
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

	/* メモリ上の基準値マスタデータから検索 */
	strcpy( in->kjno,	"000" );
	memset( keybuf,		'\0',			sizeof( keybuf ));
	sprintf( keybuf,	"%-7s%-4s000",	in->kmkcd, in->zrcd );

	if( stcPRM.myp_debug != 0 ){
		sprintf( G_msg,"KJNO SERCH STA keybuf[%s]", keybuf );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	// 材料コードが空白の場合は、基準値に000を設定
	if( strncmp( in->zrcd, MYAPP_SPACE10, 4 ) == 0 ){
		strcpy( in->kjno, "000" );
	}

	// 第1検索
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
			// 処理を抜ける
			return( RTN_NG );
		}
	}
	// 第2検索
	for( ; i <= kj_max; ++i ){
		ret = memcmp( keybuf, pKjn[i].kkey, MYAPP_LEN_KJN );
			// KEYが大きくなったら抜ける
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
/*  関 数 名  ：EditCsvKanjya                                                 */
/*  機能概要  ：患者情報のCSV形式でのテキスト出力                             */
/*  入    力  ：                                                              */
/*   第１引数 ： struct _KANJYA kan;  : 患者情報構造体                        */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK             : 正常                                    */
/*               RTN_NG             : エラー                                  */
/******************************************************************************/
int     EditCsvIrai( iri )
struct      _IRAI     *iri;
{
    char    func_nm[30];        /* 関数名称 */
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
					"%s!%s!%s!%s!"
					"%s"
		// 1 種別・2ファイル名・3行No・4処理年月日
		// 5 BML受付日・6依頼検体NO)・7依頼書NO・8項目コード
		// 9 詳細
		, MYAPP_APPLNAME, G_fnm, w_str, stcPRM.myp_kjnymd
		, G_utkymd, G_kntno, G_irino, G_kmkcd
		, msg
	);
	strcpy( msg, buf );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：irai_pr                                                       */
/*  機能概要  ：依頼情報構造体printf                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  _IRAI		*irai;	: 依頼情報                        */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		irai_pr( in )
struct		_IRAI		*in;		/* 依頼データ	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	strcpy( func_nm, "irai_pr" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	printf( "依頼データ{\n" );

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
