/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD105.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _LD105_h
#define _LD105_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD105"
#define	MYAPP_APP_NAME_JP		"LD105"
#define	MYAPP_LOGINIFILE		"LD105_LOG.ini"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON	"00000000"
#define	MYAPP_LOG_ERRCODE_APP	"010"
#define	MYAPP_LOG_ERRCODE_DB	"020"
#define	MYAPP_LOG_ERRCODE_ETC	"0Z0"

//	エラーコード詳細
#define MYAPP_SQL_DEADLOCK	-911
#define MYAPP_SQL_DUPLICATION	-803

//	パラメータ文字列
#define	MYAPP_PRM_SHM_KEY	"SHM_KEY"
#define	MYAPP_PRM_SLEEP_MIN	"SLEEP_MIN"
#define	MYAPP_PRM_DB_NAME	"DB_NAME"
#define	MYAPP_PRM_DB_USER	"DB_USER"
#define	MYAPP_PRM_DB_PASSWD	"DB_PASSWD"
#define MYAPP_PRM_DIR_INPUT	"INPUT_DIR"
#define MYAPP_PRM_DIR_OK	"END_DIR_OK"
#define MYAPP_PRM_DIR_NG	"END_DIR_NG"
#define MYAPP_PRM_FILE_PRX	"FILE_PRX"
#define MYAPP_PRM_LOCK_FILE	"LOCK_FILE"

//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE		(1024)

#define MYAPP_LEN_FNCNM		32
#define MYAPP_LEN_MSG		3072

#define RECORDSIZE		1024

#define	FILE_RECSIZE		1024

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE		sizeof ( int )

#define	MYAPP_MAX_CHAR		256
/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	int	 SleepMin ;
	char	 cInputDir[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirOK[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirNG[MYAPP_PATH_SIZE] ;
	char	 cFilePrx[MYAPP_PATH_SIZE] ;
	char	 cLockFile[MYAPP_PATH_SIZE] ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
} pAppEnv;

/*==============================================================*/
/* 相関結果情報ファイル						*/
/*==============================================================*/
typedef struct file_othkekka {
	char	recid[2];			/* レコード識別		 	*/
	char	utkymd[8];			/* ＢＭＬ受付年月日		*/
	char	irino[11];			/* 依頼書ＮＯ			*/
	char	kmkcd[7];			/* 項目コード			*/
	char	kntno[11];			/* 検体ＮＯ			*/
	char	chkmj[2];			/* チェック文字			*/
	char	stzrcd[3];			/* 推定材料コード		*/
	char	kmkrs[8];			/* 項目名略称			*/
	char	oyakmkcd[7];			/* 親項目コード			*/
	char	setkmkcd[7];			/* セット項目コード		*/
	char	hsykflg[1];			/* 非照会フラグ			*/
	char	hskflg[1];			/* 非請求区分			*/
	char	hhkkflg[1];			/* 非報告フラグ			*/
	char	srinycd[1];			/* 処理内容コード		*/
	char	seccd[2];			/* セクションコード		*/
	char	skchkflg[1];			/* 出荷チェックフラグ		*/
	char	bkfkkbn[1];			/* 分画負荷区分			*/
	char	ysnlvl[2];			/* 優先レベル			*/
	char	tikflg[1];			/* 追加フラグ			*/
	char	skjflg[1];			/* 削除フラグ			*/
	char	jkntikflg[1];			/* 条件付き追加フラグ		*/
	char	kkckkacd[1];			/* 拡張結果ＤＢ識別コード	*/
	char	fdkkckkacd[1];			/* ＦＤ拡張結果ＤＢ識別コード	*/
	char	knslabcd[3];			/* 検査実施ラボコード		*/
	char	uktkbn[1];			/* 受付区分			*/
	char	kkajkcd[1];			/* 結果状況コード		*/
	char	pncrgflg[1];			/* パニックレンジフラグ 	*/
	char	knkgrp[1];			/* 緊急グループ			*/
	char	kkaksflg[1];			/* 結果換算フラグ		*/
	char	kkassflg[1];			/* 結果修正フラグ		*/
	char	knskka1[8];			/* 結果１			*/
	char	knskka2[8];			/* 結果２			*/
	char	knskka2kbn[1];			/* 結果２区分			*/
	char	kkahskcd[3];			/* 結果補足コード		*/
	char	kkacmt1[4];			/* 結果コメント１		*/
	char	kkacmt2[4];			/* 結果コメント２		*/
	char	ijkbnm[1];			/* 異常値区分（男）		*/
	char	ijkbnf[1];			/* 異常値区分（女）		*/
	char	ijkbnn[1];			/* 異常値区分（不明）		*/
	char	sdi[3];				/* 指数 			*/
	char	hkkhjkka[8];			/* 報告書表記結果		*/
	char	hkkhjkkakj[16];			/* 報告書表記結果(漢字) 	*/
	char	kjntino[3];			/* 基準値ＮＯ			*/
	char	hkahkkkbn[1];			/* 負荷報告ＮＯ表示区分 	*/
	char	strno[5];			/* 出力順シリアルＮＯ		*/
	char	htkihka[12];			/* 非定型負荷時間		*/
	char	kkatimstamp[26];		/* 結果更新タイムスタンプ	*/
	char	knsendyti[8];			/* 検査完了予定日		*/
	char	sriymd[8];			/* 処理年月日			*/
	char	gcyuskcd[1];			/* 外注先コード			*/
	char	ltgtcd[1];			/* ＬＴＧＴ変換コード		*/
	char	kkaovr[1];			/* 結果６桁オーバーフラグ	*/
	char	tktfrk[1];			/* 凍結振替フラグ		*/
	char	kntinokkt[1];			/* 検体ＮＯ確定フラグ		*/
	char	labtyakuymd[8];			/* ラボ着日			*/
	char	wscd[4];			/* Ｗ／Ｓコード			*/
	char	seq[6];				/* ＳＥＱ			*/
	char	sryokktflg[1];			/* 材料確定フラグ		*/
	char	tikakmkhji[1];			/* 追加項目表示フラグ		*/
	char	kkaupdhji[1];			/* 結果修正項目表示フラグ	*/
	char	filler[61];			/* 予備 			*/
} my_stFileOTHERKKA;

/******************************************************************************/
/* データ構造体定義                                                           */
/******************************************************************************/
//      システム管理マスタ情報構造体
typedef struct  _stSYSKNR {
	char	kjnsriymd[10+1];	// 基準処理年月日
	char	iriendflg[1+1];		// 依頼ENDフラグ
	char	bchendflg[1+1];		// 分注ENDフラグ
	char	unyflg[1+1];		// 運用フラグ
} my_stSYSKNR ;


// <<   他サテライト結果情報テーブル      >>
typedef struct	db_otherkka {
	char	utkymd[10+1];
	char	irino[11+1];
	char	kmkcd[7+1];
	char	sriymd[10+1];
	char	kntno[13+1];
	char	chkmj[4+1];
	char	stzrcd[4+1];
	char	kmkrs[16+1];
	char	oyakmkcd[7+1];
	char	seccd[2+1];
	char	bkfkkbn[1+1];
	char	knsjslbcd[3+1];
	char	kkajkcd[1+1];
	char	pncrgflg[1+1];
	char	kkaksflg[1+1];
	char	kkassflg[1+1];
	char	knskka1[12+1];
	char	knskka2[24+1];
	char	knskka2kbn[2+1];
	char	kkahskcd[3+1];
	char	kkacmt1[5+1];
	char	kkacmt2[5+1];
	char	ijkbnm[1+1];
	char	ijkbnf[1+1];
	char	ijkbnn[1+1];
	char	sdi[3+1];
	char	hkkki[24+1];
	char	hkkkiknj[24+1];
	char	kjno[3+1];
	char	smpcd[7+1];
	short	knsseq;
	char	ksndh[26+1];
	char	trkdh[26+1];
} my_stDbOTHERKKA;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/

