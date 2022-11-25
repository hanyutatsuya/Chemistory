/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：edit_irai.c                                                  */
/*   概      要：データ編集処理                                               */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,項目追加(登録日時)対応        */
/*  1.04     2007/06/01     INTEC.INC      自動発生項目登録＋検査G編集追加    */
/*  2.01     2007/06/01     INTEC.INC      集検万台404の追加                  */
/*  3.01     2007/06/01     INTEC.INC      緊急運用変更に伴う追加修正         */
/*  4.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include	<stdio.h>
#include	<ctype.h>
#include    <string.h>
#include    "AD202.h"

/******************************************************************************/
/*  関 数 名  ：EditKinqIrai                                                  */
/*  機能概要  ：AS400緊急依頼データ編集 ＆　チェック                          */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  AS4IRAI   	*inp;	: AS400緊急依頼情報               */
/*   第２引数 ：struct  _KANJYA   	*kan;	: 患者属性情報                    */
/*  出    力  ：                                                              */
/*   第１引数 ：struct  _IRAI		*iri;	: 依頼情報                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		EditKinqIrai( inp, kan, iri )
struct		AS4IRAI		*inp;		/* AS400緊急依頼情報(S-JIS)	*/
struct		_KANJYA		*kan;		/* 患者属性構造体		*/
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
	strcpy(func_nm, "EditKinqIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//=========================================
	//	EDIT
	//=========================================
	// 1 ＢＭＬ受付年月日
	strcpy( iri->utkymd,	kan->utkymd );

	// 2 依頼書Ｎｏ
	strcpy( iri->irino,	kan->irino );
	// 3 依頼書Ｎｏ桁数フラグ
	strcpy( iri->iriketflg,kan->iriketflg );

	// 4 依頼世代Ｎｏ
	iri->zssdino	= stcPRM.myp_sedai;

	// 5 検査グループ
		// 1.04             -> 項目マスタ情報と一緒に編集
	strcpy( iri->knsgrp, 	" " );

	// 6 項目コード			<- 項目マスタ情報と一緒に編集

	// 7 依頼発生元区分		0:上位システム
	iri->irihsmkbn[0] = '0';
	
	// 8 依頼区分			K:緊急
	iri->irikbn[0] = 'K';

	// 9 検査工程区分		A:通常
	iri->ksktkbn[0] = 'A';

	// 10 処理日			システム管理マスタ．緊急受付日
	strcpy( iri->sriymd,	stcPRM.myp_kjnymd );

	// 11 検体Ｎｏ
	strcpy( iri->kntno,		kan->irino );
	// 12 検体Ｎｏ桁数フラグ
	strcpy( iri->kntketflg,	" " );

	// 13 チェック文字（やっぱり必要）
	memset( buf, '\0', sizeof( buf ));
	if( memcmp( inp->c_kentai_ch, MYAPP_SPACE10, sizeof(inp->c_kentai_ch))==0){
		// 3.01 ADD	検体No6桁から算出
		memcpy( buf,	inp->c_kentai_no	,sizeof( inp->c_kentai_no ));
		EditChkmj( buf,	iri->chkmj );
	} else {
		cret=sj2euc( iri->chkmj, memcpy(buf, inp->c_kentai_ch,
        	sizeof( inp->c_kentai_ch )), sizeof( iri->chkmj ));
			// WARNING
		if( cret != RTN_OK ){
			sprintf( G_msg, "SJIS->EUC コード変換エラー【チェック文字】[%s]"
				,iri->chkmj );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
		}
	}

	// 14 推定材料コード		<- INPUT 3byte CODE 3byte DB 4byte
	if( memcmp( inp->c_zairyo_cd, MYAPP_ZRCD_ASDEF, sizeof(inp->c_zairyo_cd))==0){
											/* 材料コードが空のケース */
		strcpy( iri->stsrcd,	MYAPP_DEF_ZRCD );
											/* 推定材料コードをデフォルト(血清：023)に設定する */
		sprintf( G_msg, "材料コードに初期値を設定します[%s]" ,iri->stsrcd );
		EditCsvMsg( G_msg );				/* DEBUG出力(LOG)しておく */
		LogOut( LT_DBG, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__);
	} else {								/* 材料コードが設定されているケース */
		sprintf( iri->stsrcd, "%-3.3s",  inp->c_zairyo_cd );
											/* そのままコピーする */
	}

	// 15 項目略称			<- 項目マスタ編集時
	// 16 親項目コード		<- 項目マスタ編集時
	// 17 サンプリングコード<- 項目マスタ編集時

	// 18 セット項目コード
	strcpy( iri->setkmkcd,	"0000000" );
	// 19 処理内容コード
	strcpy( iri->srinycd,	"0" );

	// 20 セクションコード	<- 項目マスタ編集時

	// 21 出荷チェックフラグ
	strcpy( iri->skchkflg,	"0" );

	// 22 分画負荷区分		<- 項目マスタ編集時

	// 23 優先レベル
	strcpy( iri->ysnlbl,	"00" );

	// 24 集検フラグ 		<- カード区分='17'ならば'1'
	if( strcmp( kan->cdkbn1, "17" ) == 0 ){
		iri->skflg[0] = '1';
	} else {
		iri->skflg[0] = '0';
	}
    if(( memcmp( inp->c_kentai_no, "12", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "13", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "14", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "20", 2 ) == 0 )||
       ( memcmp( inp->c_kentai_no, "90", 2 ) == 0 )){
//     ( memcmp( inp->c_kentai_no, "403", 3 ) == 0 )||
//     ( memcmp( inp->c_kentai_no, "404", 3 ) == 0 )||    // 2.1 ADD
//     ( memcmp( inp->c_kentai_no, "405", 3 ) == 0 )||
//     ( memcmp( inp->c_kentai_no, "412", 3 ) == 0 )||
//     ( memcmp( inp->c_kentai_no, "490", 3 ) == 0 ))[
        iri->skflg[0] = '1';
    }

	
	// 25 追加フラグ	
	strcpy( iri->tkflg,		"0" );
	// 26 削除フラグ
	strcpy( iri->sjflg,		"0" );
	// 27 条件追加フラグ
	strcpy( iri->jktkflg,	"0" );

	// 28 基準値ＮＯ		<- 項目マスタ編集時
	// 29 負荷報告ＮＯ表示区分
	// 30 特別基準値ＮＯ
	// 31 特別基準値フラグ

	// 32 非定型負荷時間
		 // 全角スペースで埋める
	for( w_num=strlen(iri->htkfkhms);w_num < sizeof(iri->htkfkhms)-1;w_num+=2 ){
		memcpy( &iri->htkfkhms[w_num], MYAPP_KJSPACE10, 2 );
	}

	// 33 透析フラグ
	// 34 凍結フラグ

	// 35 分注区分		2(=分注項目サテライト有り）
	iri->bnckbn[0] = '2';
	// 36 尿分注区分	0(=非分注項目）
	iri->nbnckbn[0] = '0';

	// 37 検査開始予定日
	strcpy( iri->knskisyymd,INIT_DATE );
	// 38 検査完了予定日
	strcpy( iri->knskryymd,	INIT_DATE );
	// 39 検査完了予定時間
	strcpy( iri->knskrytme,	INIT_TIME );

	// 40 緊急報告フラグ
	iri->kkhkkflg[0] = '0';

	// 41 緊急依頼フラグ
	memcpy( iri->kkiriflg,	inp->c_kinkyu_flg,sizeof( inp->c_kinkyu_flg ));

	// 42 緊急依頼ロットＮｏ
	memset( w_str,	'\0',	sizeof( w_str ));
	memcpy( w_str,	inp->c_lotno,sizeof( inp->c_lotno ));
	iri->kkirilotno = atoi( w_str );

	// 43 緊急対応受付ＩＤ
	strcpy( iri->kktoutkid,	" " );
	// 44 検査回数
	iri->knssu = 1;

	// 45 オーダ作成フラグ	空白:初期値
	iri->odrssflg[0] = ' ';

	// 46 予定希釈倍率
	iri->ytiksbr[0] = '1';

	// 47 報告状況フラグ
	strcpy( iri->hhkjkflg,	" " );

	// 48 情報更新日時  CURRENT TIMESTAMP
    // 1.01 ADD 49 登録日時 CURRENT TIMESTAMP

	// iniファイルでのDEBUG指定時のみprint処理を実行
/*
//	if( stcPRM.myp_debug == 1 ){
//		irai_pr( iri );
//	};
*/
	
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/******************************************************************************/
/*  関 数 名  ：EditKinqIraiKomoku                                            */
/*  機能概要  ：緊急対応項目判断＆項目マスタ情報編集                          */
/*  入    力  ：                                                              */
/*   第１引数 ：struct  KOMST   	*kom;	: 項目情報                        */
/*   第２引数 ：char	zairyo[];			: 材料コード                      */
/*   第３引数 ：char	age[];				: 年齢                            */
/*   第４引数 ：char	skflg[];			: 集検フラグ                      */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
// 1.04 int		EditKinqIraiKomoku( kom, zairyo, age )
int		EditKinqIraiKomoku( kom, zairyo, age, skflg )
struct		KOMST		*kom;		/* 依頼項目情報構造体	*/
char		zairyo[];
char		age[];
char		skflg[];				// 1.04 ADD
{
	int		ret=RTN_OK;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	char	buf2[MYAPP_MAX_CHAR+1];
	char	w_str[20];	
	int		w_num;
	struct	stcKJNO		kj;					// 基準値NO取得用構造体

	/* 初期処理	*/
	strcpy(func_nm, "EditKinqIraiKomoku" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// 緊急対応項目マスタ取得->項目マスタ、検査グループ決定
/* 1.04 DEL
DEL	if( SelKinqKomokmst( kom, skflg ) != RTN_OK ){
DEL		// 対象外
DEL		return( RTN_SKIP );
DEL	}
*/
	// 1.04 ADD 検査CD+サンプリング+検査G.種別->コードが若い先頭１件目
	if( SelKinqKomokmst( kom, skflg ) != RTN_OK ){
		// 集検を想定して取得失敗の場合は、一般で再度取得し直す
		if( skflg[0] == '1' ){
/* 3.01 	緊急は1recで複数項目のためDEL
DEL			strcpy( skflg,	"0" );
*/
			if( SelKinqKomokmst( kom, skflg ) != RTN_OK ){
				sprintf( G_msg,"一般集検共に該当する検査グループがありません。"
					"項目CD[%s]集検F[%s]",
					kom->kmkcd, skflg );
				EditCsvMsg( G_msg );
				LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm
					, __FILE__, __LINE__);
				// SKIP
				ret=RTN_SKIP;
			}
		} else {
			sprintf( G_msg,"該当する検査グループがありません。"
				"項目CD[%s]集検F[%s]",
				kom->kmkcd, skflg );
			EditCsvMsg( G_msg );
			LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
			// SKIP
			ret=RTN_SKIP;
		}
	}
	if( ret == RTN_SKIP ){
		sprintf( G_msg,
			"対象ラボですがマスタに該当する項目、グループが存在せず、SKIPします。"
			"項目CD[%s]集検F[%s]",
			kom->kmkcd, skflg );
		EditCsvMsg( G_msg );
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

		return( RTN_SKIP );
	}

	// DEBUG
	sprintf( G_msg,
		"項目マスタGET！" "項目CD[%s]集検F[%s]->SMPCD[%s]KNSGRP[%s]",
		kom->kmkcd, skflg, kom->smpcd, kom->knsgrp );
	EditCsvMsg( G_msg );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

	// 15 項目略称			<- 項目マスタ編集時
	// 16 親項目コード		<- 項目マスタ編集時
	// 17 サンプリングコード<- 項目マスタ編集時
	// 20 セクションコード	<- 項目マスタ編集時
	// 22 分画負荷区分		<- 項目マスタ編集時

	// 28 基準値ＮＯ		<- 項目マスタ編集時
	memset( &kj,		'\0', sizeof( struct stcKJNO ));
	strcpy( kj.kmkcd,	kom->kmkcd );
	strcpy( kj.zrcd,	zairyo );
	strcpy( kj.age,		age );
	strcpy( kj.agekbn,	AGEKBN_YEAR );

	if( GetKjnmst( &kj ) == RTN_OK ){
		strcpy( kom->kjno,	kj.kjno );	
	} else {
		strcpy( kom->kjno,	"000" );	
		sprintf( G_msg,
			"該当する基準値マスタデータがありません。: 項目CD[%s]材料CD[%-4s]",
			kom->kmkcd, zairyo );
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

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
		sprintf( G_msg,"KJNO SERCH STA keybuf[%s] rei[%d]", keybuf,knichirei );
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
/*  関 数 名  ：EditChkmj                                                     */
/*  機能概要  ：検体チェック文字編集                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：char  検体No（INPUT6桁)	*jdi;	: 自動発生依頼情報            */
/*   第２引数 ：char  検体チェック文字  *chkmj;	: 検体チェック文字            */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
//*fc	CONVERT FROM SINGLE
//    検体Noよりチェック文字を算出する
//*nm
//    小山　隆
//*dt
//    1996.02.15
//*rt
//    正常終了..........  0
//    算出エラー........ -1
//*nt
//    チェック文字格納領域は５Byte 以上ある事。
//    検体Noは 11 Byte で NULL ﾀｰﾐﾈｰﾄ されていること
//*db
//*ag
//    char* kenno   検体No                        [I]
//    char* chmoji  チェック文字格納領域ポインタ  [O]
/******************************************************************************/
int		EditChkmj( kenno,	chmoji )
char	kenno[];
char	chmoji[];
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	char	buf[MYAPP_MAX_CHAR+1];
	int		ret=RTN_OK;

    char   wk[16];
    int    i,len,ken, chk_flg;
    int    amr=0;

    chk_flg = 0;

static char *moji[] = { /* チェック文字配列 */
"ｱｲ","ｵｶ","ｹｻ","ﾀｲ","ﾆｸ","ﾍｲ","ﾕｶ","ｳﾘ","ｸｲ","ｽﾐ","ﾄﾗ","ﾂｴ","ﾏﾕ","ﾘｽ","ﾎﾔ",
"ﾆﾚ","ｱｼ","ｺﾏ","ﾀﾙ","ﾗﾝ","ｷﾈ","ｳﾀ","ｲｶ","ｻﾒ","ﾂｷ","ﾐｿ","ﾓﾔ","ﾌﾀ","ﾅﾂ","ｶｻ",
"ﾃﾗ","ﾊﾄ","ﾐﾐ","ﾏｽ","ﾈｺ","ｵﾆ","ｱﾘ","ﾊﾀ","ﾑﾗ","ﾕﾒ","ｵﾉ","ﾕｷ","ﾊﾈ","ｶﾜ","ｲﾄ",
"ﾁﾘ","ﾀﾈ","ﾆﾗ","ﾏﾂ","ﾖﾙ","ｱﾐ","ｲﾜ","ｸﾂ","ｽｽ","ｶｵ","ﾋﾙ","ﾑｼ","ﾀﾗ","ｺﾄ","ｵﾘ",
"ｱｷ","ﾀｹ","ｷﾘ","ｳﾏ","ｻﾜ","ｸﾗ","ﾊｽ","ﾔﾈ","ﾕﾐ","ﾆｼ","ｺｲ","ｵｹ","ｱﾒ","ﾂﾘ","ｳﾒ",
"ｽﾅ","ﾌｶ","ﾔﾘ","ｿﾗ","ｾﾐ","ｻｶ","ｶﾆ","ﾂﾉ","ﾏﾘ","ｶﾒ","ｼｵ","ｲﾓ","ﾊﾙ","ﾓﾁ","ﾌﾅ",
"ﾕﾘ","ｶﾐ","ｲｼ","ｳﾆ","ｵﾔ","ｸﾘ","ｱﾕ","ﾀﾆ","ﾎｼ","ﾓﾓ","ﾌﾛ","ﾅｽ","ｸﾏ","ｽｼ","ﾃﾂ",
"ｶﾏ","ｳｼ","ﾔﾏ","ﾅﾗ","ﾌｷ","ｳﾁ","ﾐﾂ","ﾜﾗ","ｵﾄ","ｲﾇ","ｸﾆ","ｼｶ","ﾂﾒ","ﾊｹ","ﾏﾄ",
"ﾀｺ","ｱｻ","ｲﾀ","ｺｹ","ﾀﾏ","ﾇｶ","ﾓﾘ","ｳｽ","ｴｷ","ｸﾁ","ｼｼ","ﾊﾅ","ﾆｽ","ﾀｶ","ﾉﾘ",
"ｻｹ","ｶﾈ","ｻﾗ","ｲﾈ","ﾊｼ","ｻｻ","ﾊﾑ","ｻｲ","ﾔｼ","ﾌﾈ","ｱﾜ","ﾀﾅ","ﾖｼ","ｿﾘ","ｸﾜ",
"ｳﾐ","ｲｹ","ﾈﾂ","ﾎﾘ","ﾘｸ","ﾋﾓ","ﾅﾀ","ﾌｴ","ﾄﾘ","ｷｸ","ｲｴ","ﾀｷ","ﾍﾗ","ﾊﾘ","ｾｷ",
"ｴﾗ","ｷﾇ","ｶﾓ","ｻﾙ","ｺﾅ","ﾂﾕ","ﾊﾁ","ﾏﾙ","ﾋﾚ","ｾﾘ","ﾅﾜ","ｵﾕ","ｸｼ","ﾂﾙ","ｸｻ",
"ﾌﾕ","ﾇﾏ","ｶｷ","ｼﾏ","ﾋﾅ","ﾐﾁ","ｶｲ","ﾓﾐ","ﾄｷ","ｻｵ","ﾆﾜ","ﾉﾐ","ｽｷ","ｶﾝ","ﾏﾁ",
"ｶｻ","ﾂﾀ"
};

	strcpy( func_nm, "EditChkmj" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    len = strlen(kenno);

	sprintf( G_msg,"IN kntno[%s] len[%d] ", kenno, len );
	EditCsvMsg( G_msg );
	LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__);

    //if(len != LEN_KENNO)[
    if(len != 6 ){
        chk_flg=1;
    }
    else{
        for(i=0; i<len; i++){
            if(isdigit(kenno[i]) == 0){ /* 数字でない */
                chk_flg=1;
                break;
            }
        }
    }    
    if(chk_flg == 1){
        strcpy(chmoji,"    ");
        return(-1);
    }

    //sprintf( wk, "%-6.6s", &kenno[1] ); /* #01 */
    sprintf( wk, "%-6.6s", &kenno[0] );
    /* #01 memcpy(wk,kenno,7); wk[7]=NULL;  */

    ken = atoi(wk);
    amr = ken % 197;
    strcpy(chmoji,moji[amr]);

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
	printf( "iriketflg [%s]\n",	in->iriketflg );
	printf( "zssdino   [%d]\n",	in->zssdino );
	printf( "knsgrp    [%s]\n",	in->knsgrp );
	printf( "kmkcd     [%s]\n",	in->kmkcd );
	printf( "irihsmkbn [%s]\n",	in->irihsmkbn );
	printf( "irikbn    [%s]\n",	in->irikbn );
	printf( "ksktkbn   [%s]\n",	in->ksktkbn );
	printf( "sriymd    [%s]\n",	in->sriymd );
	printf( "kntno     [%s]\n",	in->kntno );
	printf( "kntketflg [%s]\n",	in->kntketflg );
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
	printf( "kjno      [%s]\n",	in->kjno );
	printf( "fkhkknohjkbn[%s]\n",in->fkhkknohjkbn );
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
