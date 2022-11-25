/**********************************************************************
 *
 *	   ＢＭＬ様向け検査システム
 *
 *	   システム名：検査結果DB登録
 *	   ファイル名：MD105.c
 *	   概要 	 ：分析機から受信した検査結果のCSVファイルをDBに登録する
 *
 **********************************************************************/

/**********************************************************************
 *	Ver.	 Date			Name		   History
 * --------------------------------------------------------------------
 **********************************************************************/

#include "MD105.h"

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <ctype.h>

/* グローバル変数 */
char	dbname[16];
char	dbuser[16];
char	dbpass[16];

char	GetFolder[256];
char	GetFolderErr[256];
char	GetFolderEnd[256];

char	iniName[256];

int 	SleepTime;

int 	EndFlg = 0;

int 	shm_Key = 0;
int 	shm_Id;

Kmkmst		sKmkmst;
Kmkmst		*pKmkmst;
int 		cntKmkmst;

char		gLogFile[256];
char		gMsgBuff[128];
void LogFileOut(char * msg);

static int chkRawdata( char *, char * );

/* 希釈倍率変換(マスタと整合性を取ること) */
char		KskbrB10HY[16+1] ;
char		KskbrB10CD[16+1] ;
char		KskbrB2HY[16+1] ;
char		KskbrB2CD[16+1] ;

/* 乳び・溶血チェック >> */
char		NyubiCD[8];
char		NyubiCM[6];
char		NyubiCHK[21];
char		NyubiKekka[21];
char		NyubiSTS[3];
char		YoketsuCD[8];
char		YoketsuCM[6];
char		YoketsuCHK[21];
char		YoketsuKekka[21];
char		YoketsuSTS[3];
char		OudanCD[8];
char		OudanCM[6];
char		OudanCHK[21];
char		OudanKekka[21];
char		OudanSTS[3];
int 		gfNyuYou;		/* 乳び・溶血フラグ */
static int	NyubiYoketuChk(Kekka *, int, int, int);
static int	NyubiYoketu( Kekka *, int );

int chkDenkai( Kekka *p );
int kesseiCHK(Kekka *pSrc, int iKcnt);

int sFncSel_REALCHK( char *,char *, char * , char * , short);
long ZdbSelectMihoKekka( char *,char *, char *, char *, char * );

long updKkaYsn( Kekka* pKey );
/* RIBINDシェルパス */
char		gcMyRebindShell[256];

/* 定性値基準値判定の為の換算テーブル */
char		KZN_Teisei[25][5];
char		KZN_Coment[25][5];
char		IJOU_KKACMT[100][5];

/* 計算式拡張対応
 * 相関式中の計算式にのみ適用、計算項目の計算は、 MD105 では行わない。
 */

#ifndef MAXBUF
#define MAXBUF                   (260)
#endif									/* !define MAXBUF					*/

/* 検査オーダーに含まれる属性に関する項目のバイト サイズ                    */
#define FLDSIZE_SC         ((size_t)5)  /* 身長 (cm)                        */
#define FLDSIZE_TJ         ((size_t)5)  /* 体重                             */
#define FLDSIZE_TJTNI      ((size_t)1)  /* 体重区分                         */
#define FLDSIZE_TNTME      ((size_t)4)  /* 蓄尿時間                         */
#define FLDSIZE_TNTNI      ((size_t)1)  /* 蓄尿時間区分                     */
#define FLDSIZE_TNRYO      ((size_t)5)  /* 蓄尿量                           */
#define FLDSIZE_TNRYOTNI   ((size_t)1)  /* 蓄尿量区分                       */

#define FLDSIZE_SBTKBN     ((size_t)1)  /* 性別区分                         */
#define FLDSIZE_AGE        ((size_t)3)  /* 年齢                             */
#define FLDSIZE_AGEKBN     ((size_t)1)  /* 年齢区分                         */

/* 単位等を示す項目に格納される識別子                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* 蓄尿時間: 時間単位               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* 蓄尿時間: 分単位                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* 蓄尿時間: 時間単位不明           */
#define _VALUE_TNRYO_LITER      ('0')   /* 蓄尿量: リットル単位             */
#define _VALUE_TNRYO_MILLILITER ('1')   /* 蓄尿量: ミリ リットル単位        */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* 蓄尿量: 量単位不明               */
#define _VALUE_TJTNI_GRAM       ('1')   /* 体重: グラム単位                 */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* 体重: キログラム単位             */
#define _VALUE_SBTKBN_MALE      ('0')   /* 性別: 男性                       */
#define _VALUE_SBTKBN_FEMALE    ('1')   /* 性別: 女性                       */
#define _VALUE_SBTKBN_UNKNOWN   ('9')   /* 性別: 性別不明                   */
#define _VALUE_AGEKBN_YEAR      ('Y')   /* 年齢: 年齢                       */

/* 計算式に含まれる属性情報の値に置換する指定                               */
#define KSNSK_TNTME     ('N')           /* 蓄尿時間 (時間単位)              */
#define KSNSK_TNRYO     ('R')           /* 蓄尿量 (ミリ リットル単位)       */
#define KSNSK_SC        ('T')           /* 身長                             */
#define KSNSK_TJ        ('W')           /* 体重 (グラム単位)                */
#define KSNSK_SBTKBN    ('S')           /* 性別区分                         */
#define KSNSK_AGE       ('A')           /* 年齢                             */

char gszTransfer[MAXBUF + 1];			/* 文字列→数値 変換バッファ
										   単一の値の置換のみなので、コレで
										   足りる                           */

/* 計算式中の IF ブロック展開                                               */
extern char *OperateKSNSK(const char *);

/* 数値文字列判定                                                           */
extern int _isnumeric(const char *);

/*----<< End add source Feb 27, 2008 H.Sato >>----*/

/* 照合チェックにて再検値についていた場合、用手再検へと落とす分析機エラーコード */
int		errsts_sai_cnt = 33;
char	errsts_sai[33][3] = {
			"1", "2", "4", "5", "6", "7", "8", "9", "10", "11", 
			"18", "19", "23", "24", "25", "26", "27",  
			"37", "38", "39", "40", "41", "42", "43", "44", "45", "46", 
			"56", "57", "58", "59", "60", "73"
		};

int		errsts_ng_cnt = 3;
char	errsts_ng[3][3] = {
			"3","47","72"
		};
/* レンジチェックマスタ 範囲区分定義 */
#define BML_PANIC	('2') 
#define KNS_PANIC	('3')
#define SYOGO_CHK	('4')

/******************************************************************************/
/*	関 数 名  ：main()							*/
/*	機能概要  ：プロセスメイン処理						*/
/*	入	  力  ：							*/
/*	 第１引数 ：argc	パラメタ数					*/
/*	 第２引数 ：argv	パラメタ配列					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int main(int argc, char **argv)
{
	long db_ret;
	BMLPRM * bp;
	char	wk[16];
	int 	daemonFlg = 0;
	int 	lcnt;
	int 	cnt;
	char	wk_key[30];
	strncpy(iniName, "MD105.ini", 32);
	/* パラメータチェック */
	if (argc > 1) {
		for (lcnt = 1; lcnt < argc; lcnt++) {
			if (argv[lcnt][0] == '-') {
				switch (argv[lcnt][1]) {
				case 'S': case 's':
					daemonFlg = 0;
					break;
				case 'N': case 'n':
					daemonFlg = 1;
					break;
				}
			}
			else {
				strncpy(iniName, argv[lcnt], 256);
			}
		}
	}
	else {
		printf("%s iniFileName [-n]\n", argv[0]);
		printf("Option -n : Non Daemon Exec\n");
		exit(0);
	}

	if (daemonFlg == 0) {
		/***
		 ***	バックグラウンド実行
		 ***/
		if ( daemon ( 0, 1 ) < 0 ) {
			exit ( 9 ) ;
		}
	}

	/* 初期化 */
	if (ZbmlOpenLog( iniName )	!= 0 ) {
		printf("ZbmlOpenLog Error\n");
	}

	sFncSyslog(TRCKIND_TRACE, "main", "Process Start");
	bp = ZbmlPrmOpen(iniName);
	ZbmlPrmGetVal(bp, "DBNAME", dbname);
	ZbmlPrmGetVal(bp, "USER", dbuser);
	ZbmlPrmGetVal(bp, "PASS", dbpass);

	ZbmlPrmGetVal(bp, "GetFolder", GetFolder);
	ZbmlPrmGetVal(bp, "GetFolderErr", GetFolderErr);
	ZbmlPrmGetVal(bp, "GetFolderEnd", GetFolderEnd);

	ZbmlPrmGetVal(bp, "SleepTime", wk);
	SleepTime = atoi(wk);

	if ( ZbmlPrmGetVal ( bp, "SHM_KEY", wk ) != 0 ) {
		/* 異常終了	LOG */
		return ( -1 ) ;
	}
	shm_Key = atoi ( wk ) ;

	ZbmlPrmGetVal(bp, "LogFileName", gLogFile);
	/* 希釈倍率変換(マスタと整合性を取ること) */
	ZbmlPrmGetVal(bp, "KSKBR_B10_HYOJI", KskbrB10HY);
	ZbmlPrmGetVal(bp, "KSKBR_B10_CODE", KskbrB10CD);
	ZbmlPrmGetVal(bp, "KSKBR_B2_HYOJI", KskbrB2HY);
	ZbmlPrmGetVal(bp, "KSKBR_B2_CODE", KskbrB2CD);

	/* 乳び・溶血の項目コード及び設定コメントCDの取得 */
	ZbmlPrmGetVal(bp, "NyubiCD", NyubiCD);
	ZbmlPrmGetVal(bp, "NyubiCM", NyubiCM);
	ZbmlPrmGetVal(bp, "NyubiCHK", NyubiCHK);
	ZbmlPrmGetVal(bp, "YoketsuCD", YoketsuCD);
	ZbmlPrmGetVal(bp, "YoketsuCM", YoketsuCM);
	ZbmlPrmGetVal(bp, "YoketsuCHK", YoketsuCHK);
	ZbmlPrmGetVal(bp, "OudanCD", OudanCD);
	ZbmlPrmGetVal(bp, "OudanCM", OudanCM);
	ZbmlPrmGetVal(bp, "OudanCHK", OudanCHK);

	/* 定性値基準値判定の為の換算テーブル >> */
	for (cnt = 1; cnt < 25 ; cnt++) {
		sprintf(wk_key,"KANZAN_TEISEI_%02d",cnt);
		/* iniファイルから換算元文字列を取得 */
		ZbmlPrmGetVal(bp, wk_key, KZN_Teisei[cnt]);
		if(memcmp(KZN_Teisei[cnt],"END",3) == 0){
			/* ENDなら抜ける */
			break;
		}
		/* iniファイルから換算元コメントコードを取得 */
		sprintf(wk_key,"KANZAN_COMENT_%02d",cnt);
		ZbmlPrmGetVal(bp, wk_key, KZN_Coment[cnt]);
		if(memcmp(KZN_Coment[cnt],"END",3) == 0){
			/* ENDなら抜ける */
			break;
		}
    }

	/* 異常値マーク代入コメント >> */
	for (cnt = 1; cnt < 100; cnt++) {
		sprintf(wk_key,"IJOU_KKACMT_%02d",cnt);
		/* iniファイルから換算元文字列を取得 */
		ZbmlPrmGetVal(bp, wk_key, IJOU_KKACMT[cnt]);
		if(memcmp(IJOU_KKACMT[cnt],"END",3) == 0){
			/* ENDなら抜ける */
			break;
		}
	}
	ZbmlPrmClose(bp);

	if ( sFncShmCrt ( shm_Key ) < 0 ) {
		return ( -1 ) ;
	}

	/* man 7 signal で確認 */
	if(SIG_ERR == signal(SIGINT,sigcatch)){
		exit(1);
	}

	/* DBの接続 */
	db_ret = ZdbConnect(dbname, dbuser, dbpass);
	if (db_ret != 0L) {
		sprintf(gMsgBuff,"DB Connect OK [%s]\n", dbname);
		sFncSyslog(TRCKIND_TRACE, "main", gMsgBuff);
	}
	/* マスタ読み込み */
	if(GetKrkmkmst() != 0){
		/* 2006-12-18 YOON */
		/* Nagata 関連項目マスタ取得失敗!! トレースを残して終了する */
		sFncSyslog(TRCKIND_TRACE, "GetKrkmkmst Can't get and Process End", gMsgBuff);
		ZdbDisConnect();
		ZbmlCloseLog();
		return 0;
	}

	/* メイン処理 */
	main_proc();

	/* DBの切断 */
	ZdbDisConnect();

	sFncSyslog(TRCKIND_TRACE, "main", "Process End");
	ZbmlCloseLog() ;
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：main_proc() 						*/
/*	機能概要  ：メイン実処理						*/
/*	入	  力  ：							*/
/*	 第１引数 ：								*/
/*	 第２引数 ：								*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
char	gFileMsgBuff[256];
int main_proc()
{
	struct dirent	**entp; 
	FILE *		fd;
	char		*fname;
	char		*fname2;
	char		*buff;
	int 		err_flg;
	int 		li_stopFlg ;
	int 		flgCtrl;
	int 		ret;
	struct stat 	fst;
	int 		iKkaCnt;
	Kekka		strKekka[100];
	int 		num_file, n;
	int		fname_len;

	fname = (char *)malloc(sizeof(char)*256);
	fname2 = (char *)malloc(sizeof(char)*256);
	buff = (char *)malloc(sizeof(char)*1024);

	/* 終了シグナルを受けるまでループ */
	for (;;) {
		/*** 停止コマンド確認 ***/
		if ( sFncShmGet ( shm_Key, &li_stopFlg ) < 0 ) {
			return ( -1 ) ;
		}
		if ( li_stopFlg == 1 ) {
			sFncShmDel ( shm_Key ) ;
			break ;
		}
		/* 終了シグナルをチェック */
		if ( EndFlg ) {
			break;
		}
		/* 受信ファイルがあるか確認 */
		num_file = scandir( GetFolder, &entp, 0 , alphasort );
		for( n = 0; n < num_file; n++ ) {
			/* .dat ファイル以外は除外する */
			fname_len = strlen( entp[n]->d_name );
			if ( memcmp ( &(entp[n]->d_name[fname_len-strlen(MYAPP_RECV_SFX)]),
					MYAPP_RECV_SFX,
					strlen ( MYAPP_RECV_SFX ) ) != 0 ) {
				free( entp[n] );
				continue;
			}
			/***
			 *** 停止コマンド確認
			 ***/
			if ( sFncShmGet ( shm_Key, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				sFncShmDel ( shm_Key ) ;
				break ;
			}

			/* 終了シグナルをチェック */
			if ( EndFlg ) {
				break;
			}
			/* ファイル名のフルパスを生成する。 */
			strncpy(fname, GetFolder, 256);
			strncat(fname, entp[n]->d_name, 256);

			if (stat(fname, &fst) != 0) {
				/* ファイル異常？ */
				continue;
			}

			if (!S_ISREG(fst.st_mode)) {
				/* 通常のファイルでない */
				continue;
			}

			strncpy(fname2, GetFolderEnd, 256);
			strncat(fname2, entp[n]->d_name, 256);

			/* Endフォルダのファイル確認 */
			ret = stat(fname2, &fst);
			if (ret == 0) {
				/* 既にファイルが存在する。無いファイル名を検索 */
				int cnt = 1;
				char buf[4];
				while (ret == 0) {
					sprintf(buf, ".%d", cnt);
					strncpy(fname2, GetFolderEnd, 256);
					strncat(fname2, entp[n]->d_name, 256);
					strncat(fname2, buf, 256);
					ret = stat(fname2, &fst);
					cnt ++;
				}
			}

			/* ファイルを End フォルダへ移動 */
			if (rename(fname, fname2) != 0) {
				continue;
			}

			/* ファイル名を出力 */
			LogFileOut(entp[n]->d_name);

			/* ファイル名の頭3文字がCT_の時はコントロール情報 */
			/*/						XM_の時はX_M情報 */
			if (strncmp(entp[n]->d_name, "CT_",3) == 0) {
				flgCtrl = 1;
			}
			else if (strncmp(entp[n]->d_name, "XM_",3) == 0) {
				flgCtrl = 2;
			}
			else {
				flgCtrl = 0;
			}

			fd = fopen(fname2, "r");
			if ( fd == NULL ) {
				/* error */
				continue;
			}

			err_flg = 0;
			for( iKkaCnt=0; iKkaCnt < 100 ;++iKkaCnt ) {
				memset(&strKekka[iKkaCnt], 0, sizeof(Kekka));
			}
			iKkaCnt = 0;
			while (fgets(buff, 1024, fd) != NULL) {
				/* 読み出したファイルをDBへ登録 */
				if (flgCtrl == 0) {
					/* 結果登録処理はファイル読込み後に行うようにする */
					if( getKekkaData(buff, &strKekka[iKkaCnt]) != 0 ) {
						err_flg = 1;
						break;
					} else {
						++iKkaCnt;
					}
				}
				else if (flgCtrl == 1) {
					if( (ret = insertDBCtrl(buff)) != 0)
					{
						/* コントロール結果のインサート失敗 */
						if( ret == RET_STOP ) {
							ZdbRollback();
							err_flg = 1;
							break;
						}
						else if(ret == RET_CONTINUITY){
							ZdbRollback();
						}
					}
				}
				else {
					if ((ret=insertDBX_M(buff)) != 0) {
						/* X_M結果のインサート失敗 */
						if( ret == RET_STOP ) {
							ZdbRollback();
							err_flg = 1;
							break;
						}
						else if(ret == RET_CONTINUITY){
							ZdbRollback();
						}
					}
				}
			}
			fclose(fd);
			/* 結果登録処理を最後に行う */
			if( (flgCtrl == 0) && (err_flg == 0) ) {
				ret = EntryKekka( strKekka, iKkaCnt);
				/* 検査結果のインサート */
				if( ret == RET_STOP ) {
					ZdbRollback();
					err_flg = 1;
				}
				else if(ret == RET_CONTINUITY){
					ZdbRollback();
				}
			}
			/* 血清情報対応処理追加 */
			if( (flgCtrl == 0) && (err_flg == 0) ) {
				if( (kesseiCHK( strKekka, iKkaCnt )) != 0 ) {
					/* 血清情報更新 */
					if( ret == RET_STOP ) {
						ZdbRollback();
						err_flg = 1;
					}
					else if(ret == RET_CONTINUITY){
						ZdbRollback();
					}
				}
			}

			if (err_flg == 1) {
				/* エラー発生 */
				char errmsg[128];
				sprintf(errmsg, "%s %s", fname2, "[[DB ERROR]] File Data DB Rollback.");
				sFncSyslog ( LOG_ERR, "main_proc()", errmsg ) ;

				return 0;	/* 終了*/
			} else {
				ZdbCommit();
			}

			free( entp[n] );
		}
		free( entp );
		/* 一定時間待機 */
		sleep(SleepTime);
	}

	free(fname);
	free(fname2);
	free(buff);

	return 0;
}
/******************************************************************************/
/*	関 数 名  ：()								*/
/*	機能概要  ：メイン実処理						*/
/*	入	  力  ：							*/
/*	 第１引数 ：								*/
/*	 第２引数 ：								*/
/*	出	  力  ：							*/
/*	復帰情報  ：int								*/
/*			 0			正常			 	*/
/*			RET_STOP(-1)		異常				*/
/*			RET_CONTINUITY(2) 異常。次の処理する。			*/
/******************************************************************************/
int EntryKekka(Kekka *pSrc, int iKcnt)
{
	int 		i;
	Kekka		* pKekka;
	Kenorder	wOrder;
	int 		ret;
	int 		ret1;
	int 		iKesseiflg;
	short		rKnssu;
	long		num_irai;
	char		errMsg[1024] = {0,};
	int			iFukusuflg = 0; 
	/* iKesseiflg ... 血清情報オーダ有無 */
	/*	  血清情報依頼なし	... 0 */
	/*	  血清情報依頼有り	... 1 */
	iKesseiflg = 0;
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			/* 血清情報の影響がある([検体No＋検査グループ]の条件で */
			/* リアルチェックを検索し、血清パラメータが"00"以外の物が */
			/* 一件でもあれば、血清情報ありとする。 */
			/* 2006-09-01 Nagata 検査開始日追加 */
			/* 2007-05-22 Nagata 条件追加（アッセイラックID,アッセイラックPOS）*/
			/* 検査開始日+検体No+検査グループ+アッセイラックID+アッセイラックPOSの条件で */
			/* リアルチェックを検索し、血清パラメータが"00"以外の物が */
			/* 一件でもあれば、血清情報ありとする。 */
			ret = sFncSel_REALCHK( pKekka->knskisymd, pKekka->kntno, pKekka->knsgrp,
									pKekka->asyrckid,pKekka->asyrckpos );

			if(ret<0)
			{
				sprintf(errMsg,"SQLCODE:%d Input knskirymd(%s) kntno(%s) knsgrp(%s)"
					,ret,pKekka->knskisymd, pKekka->kntno, pKekka->knsgrp);

				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK)
				{
					sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog (TRCKIND_ERROR, "EntryKekka()", errMsg);
				return(RET_STOP);
			}
			else if( ret > 0 ) {
				iKesseiflg = 1;
			}
		}
	}
	/* 各種処理チェックループ */
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			/* 検査フラグが保留が設定されている時以外 */

			if (pKekka->irikbn != 'Y') {	/* キャリブレーション以外のとき */
				if (pKekka->knssu == 1) {
					/* 初回検査時は、結果優先フラグを優先に設定 */
					pKekka->kkaysnflg = '1';
					pKekka->siyflg = '1';
				}
				/* 手入力検査結果があるかチェック	*/
				/* 手入力フラグ  ＝１（手入力結果）	*/
				/* 結果優先フラグ＝１（優先結果）	*/
				Kekka	ssKekka;
				memcpy(&ssKekka, pKekka, sizeof(ssKekka));
				ssKekka.knssu = 0;
				ssKekka.knssueda = 0;
				ret = ZdbKekkaSelectTnyrkCount(&ssKekka);
				if (ret < 0){
					sprintf(errMsg,"SQLCODE:%d ZdbKekkaSelectTnyrkCount",ret);
					/* 2006-12-13	YOON */
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog (TRCKIND_ERROR, "EntryKekka()", errMsg);
					return(RET_STOP);
				}
				else if(ret ==0)
					;
				else if(ret > 0){
					/* 手入力の結果が存在するときは、結果を未報告完了に設定 */
					pKekka->siyflg	  = '0';
					pKekka->kkajkcd   = '1';
					pKekka->kkaysnflg = ' ';
					pKekka->knsflg	  = 'M';
				}

				/* 2.03 同一依頼でかつ別検体の結果が存在している場合は未報告完了に設定する。 */
				ret = ZdbKekkaSelectFukusuCount(pKekka);
				if (ret < 0){
					sprintf(errMsg,"SQLCODE:%d ZdbKekkaSelectFukusuCount",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog (TRCKIND_ERROR, "EntryKekka()", errMsg);
					return(RET_STOP);
				}
				else if(ret ==0){
					;
				}
				else if(ret > 0){
					sprintf(errMsg,"別検体で測定済み sriymd(%s) kntno(%s) knsgrp(%s)"
							,pKekka->sriymd, pKekka->kntno, pKekka->knsgrp);
					sFncSyslog (TRCKIND_ERROR, "EntryKekka", errMsg);

					pKekka->siyflg    = '0';
					pKekka->kkajkcd   = '1';
					pKekka->kkaysnflg = ' ';
					pKekka->knsflg    = 'M';
					iFukusuflg        =  1 ;
				}

				if (pKekka->knsflg != 'M') {
					/* 項目マスター読み出し */
					memset(&sKmkmst, 0, sizeof(Kmkmst));
					strncpy(sKmkmst.knsgrp, pKekka->knsgrp, 16);
					strncpy(sKmkmst.kmkcd, pKekka->kmkcd, 7);
					ret = ZdbKmkmstSelectKey(&sKmkmst, &pKmkmst, &cntKmkmst);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND))
					{
						sprintf(errMsg,"SQLCODE:%d ZdbKmkmstSelectKey",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog(LOG_ERR,"EntryKekka()",errMsg);
						return(RET_STOP);

					}
					else if (ret == HRC_SQL_NOT_FOUND) {
						cntKmkmst = 0;
					}
					/* 登録チェック */
					if( (ret = TourokuChk(pKekka, &iKesseiflg)) != 0 ) {
						/* 登録チェックエラー */
						sFncSyslog ( LOG_ERR, "EntryKekka()", "Touroku Check Error.");
						return(ret);
					}
					ZbmlFree(pKmkmst);
				}
			}
		}
	}

	/* 照合・関連チェックループ */
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			if( pKekka->syougoflg == '2' ) {
				kanrenChk(pSrc, iKcnt, i);
			}
			if( pKekka->syougoflg == '1' ) {
				kanrenChkYsn(pKekka);
			}
		}
	}

	/* 結果データINSERT処理ループ */
	for( i=0; i < iKcnt ; ++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			/*	検査オーダに自ＫＥＹのオーダがあるかをチェックする */
			/*	存在する */
			/*		自検査工程区分 "K" ： 用手再検 */
			/*	存在しない */
			/*		自検査工程区分 "K" ： 自動再検 */
			memset(&wOrder, 0, sizeof(wOrder));
			if( (ret1 = getOdrLast( pKekka, &wOrder )) < -1 ) {
				/* ＤＢエラー(ログ) */
				return -1;
			}
			if( iKesseiflg ) {
				if( pKekka->knssu == 1 || pKekka->ksktkbn == 'S' ){
					/* 2.乳び溶血フラグが'2'で検査フラグ'X'だったら検査フラグを'H'に変更する */
					if( pKekka->knsflg == 'X' ) {
						pKekka->kesseiflg = '2';
						pKekka->knsflg = 'H';
					}
					/* 乳びフラグは検査フラグ"X","A","R"に対しても更新する */
					else if( pKekka->knsflg == 'A' || pKekka->knsflg == 'R' ) {
						pKekka->kesseiflg = '2';
					}
				}
			}
			/* DBにインサート */
			do {
				ret = ZdbKekkaInsert(pKekka);
				if ((ret != HRC_SQL_NORMAL) && (ret != SQL_ERR_DUPLICATION)) {
					/* インサートエラー */
					sprintf(errMsg, "Kekka Insert Errer(%d) : KNTNO[%s]:KNSGRP[%s]:KMKCD[%s]:KNSSU[%d]",
						ret, pKekka->kntno, pKekka->knsgrp, pKekka->kmkcd, pKekka->knssu);

					if(ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
					return(RET_STOP);
				}
				if (ret == SQL_ERR_DUPLICATION) {
					if( ((ret1 == 0) && (pKekka->ksktkbn == 'K')) || iFukusuflg == 1) {
						/* 自動再検 何もしない */
						/* 別検体NOの優先結果が存在している場合は何もしない */
					} else {
						/* 再測定指示有り＆WS出力なし */
						/* 存在する結果を検索して、すべてが未報告完了"M"でかつ、中間報告の状態だったら、 */
						/* 再流しの処理を行わない。自分が生きる */
						num_irai = ZdbSelectMihoKekka(pKekka->knskisymd,pKekka->sriymd,
							pKekka->kntno, pKekka->knsgrp, pKekka->kmkcd );

						if(num_irai < 0)
						{
							/* 未報告完了レコードの検索 */
							sprintf(errMsg, "SQL CODE:%ld ZdbSelectMihoKekka",num_irai);
							if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
								sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
								return(RET_CONTINUITY);
							}
							sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
							return(RET_STOP);

						}
						else if( num_irai == 0 ) {
							/* 再流し前の検査回数がすべて中間 */
							/* フラグ類を再チェックして2以上が存在しない場合 */
							/* （自チャネルに関しては異常がない）、検査フラグを'X'に変更する */
							/* ※ 再測定指示後の再流しで正常データが再検対象になった為の対応 */
							if (pKekka->renjicflg < '2' && pKekka->soukn1flg < '2' &&
									pKekka->kesseiflg < '2' && pKekka->rirekiflg < '2' &&
									pKekka->syougoflg < '2' && pKekka->keisanflg < '2' &&
									pKekka->per100flg < '2' && pKekka->tousekflg < '2' &&
									pKekka->kisyakflg < '2' && pKekka->kouseiflg < '2' &&
									pKekka->syoungflg < '2' && pKekka->soukn2flg < '2' &&
									pKekka->fukaptflg < '2' && pKekka->yobiflg01 < '2' &&
									pKekka->tobiflg02 < '2' && pKekka->yobiflg03 < '2' &&
									pKekka->yobiflg04 < '2' && pKekka->yobiflg05 < '2') {
								pKekka->knsflg = 'X';
							}

						}
						else if(num_irai > 0)
						{
						/*	重複エラーが発生した場合 */
						/*	【更新仕様】 */
						/*		結果状況コード＝１（中間） */
						/*		結果優先フラグ＝ブランク */
						/*		検査フラグ＝Ｍ（未報告完了） */
						/*	自データを無効にする */
						pKekka->kkajkcd    = '1' ;
						if( pKekka->kesseiflg == '2' )
							pKekka->kesseiflg = '1';
						pKekka->knsflg	   = 'M' ;
						pKekka->kkaysnflg  = ' ' ;
						}
					}
					/* 重複エラーが発生したときは、検査回数をインクリメントする。 */
					pKekka->knssu ++;
				}
			} while (ret == -803);
		}
	}

	/* 依頼処理ループ */
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		/* 別検体NOの優先結果が存在している場合は 依頼を更新しない */
		if (pKekka->knsflg != 'H' && iFukusuflg != 1) {
			if (pKekka->irikbn != 'Y') {	/* キャリブレーション以外のとき */
				/* 依頼の検査回数更新ルール */
				/* １．結果のインサートの際は、結果の検査回数に合わせて依頼の検査回数も増やす */
				/*	   検査回数は、結果と同一のものをＵＰＤＡＴＥする。 */
				/* ２．"R"（再検対象）の場合は、１の検査回数にさらに＋１する */
				/*	   （ワークシート作成準備のため） */
				/* 依頼情報の取得 */
				Irai	sIrai;
				Irai	*pIrai;
				int 	cIrai;

				memset(&sIrai, 0, sizeof(sIrai));
				strncpy(sIrai.utkymd, pKekka->utkymd, sizeof(sIrai.utkymd)-1);
				strncpy(sIrai.irino, pKekka->irino, sizeof(sIrai.irino)-1);
				sIrai.zssdino = pKekka->zssdino;
				strncpy(sIrai.knsgrp, pKekka->knsgrp, sizeof(sIrai.knsgrp)-1);
				strncpy(sIrai.kmkcd, pKekka->kmkcd, sizeof(sIrai.kmkcd)-1);
				ret = ZdbIraiSelectKey(&sIrai, &pIrai, &cIrai);
				if(ret<0)
				{
					/* 依頼SELECTエラー */
					sprintf(errMsg,"SQL CODE:%d ZdbIraiSelectKey",ret);
					if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
						sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
					return(RET_STOP);
				}
				else if (cIrai == 0){
					sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				}
				else if (cIrai > 0) { /* 取得成功 */
					/* 予定希釈倍率のセット */
					Kskbrmst	sKskbrmst;
					Kskbrmst	*pKskbrmst;
					int 		cKskbrmst;

					/* 分析機区分が"YOUS"で規定濃度範囲にヒットしたら、 */
					/* その希釈倍率を依頼の予定希釈倍率にセットする */
					memset(&sKskbrmst, 0, sizeof(sKskbrmst));
					strncpy(sKskbrmst.bskkbn, "YOUS", sizeof(sKskbrmst.bskkbn)-1);
					strncpy(sKskbrmst.knsgrp, pKekka->knsgrp, sizeof(sKskbrmst.knsgrp)-1);
					strncpy(sKskbrmst.kmkcd, pKekka->kmkcd, sizeof(sKskbrmst.kmkcd)-1);
					ret = ZdbKskbrmstSelectChk(&sKskbrmst, &pKskbrmst, &cKskbrmst);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
						sprintf(errMsg,"SQL CODE:%d ZdbKskbrmstSelectChk",ret);
						if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
							sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
						return(RET_STOP);


					}
					if (ret != HRC_SQL_NOT_FOUND) {
						strncpy(pIrai->ytiksbr, pKskbrmst->ksbr, 15);
						ZbmlFree(pKskbrmst);
					}


					if(pKekka->knsflg == 'M'){
						/* 再流しの場合は依頼の検査回数に＋１するのみ */
						pIrai->knssu++;
					}
					else{
						/* ODRSSLF(オーダ作成フラグ)が'1'場合は誰かがWS指示したのでここではなにもしない */
						if( pIrai->odrssflg == '1' )
						{
							/* 何もしない */
						} else {
							/* 依頼の検査回数を結果に合わせる */
							/* 依頼の検査回数と(結果の検査回数 + 1)が同一だった場合、更新を行わない。 検査フラグを"A"に更新する */
							/* 依頼の検査回数≧（結果の検査回数＋１）だった場合、再検を出さない */
							if(pKekka->knsflg=='R'&&pIrai->knssu>=(pKekka->knssu + 1) ){
								/* 再検指示が行えない。検査中に変える */
								/* 何もしない（依頼の検査回数を変えない） */
							}
							else{
								pIrai->knssu = pKekka->knssu;
							}
						}
					}
					if ((ret = ZdbIraiUpdate(pIrai)) != 0) {
						sprintf(errMsg,"SQL CODE:%d ZdbIraiUpdate",ret);
						/* 依頼アップデートエラー */
						if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
							sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
						return(RET_STOP);

					}
					ZbmlFree(pIrai);
				}

				/* 結果の検査フラグがRだったら、さらに１プラスする */
				if (pKekka->knsflg == 'R')
				{
					Irai sIrai;

					memset(&sIrai, 0, sizeof(sIrai));
					strncpy(sIrai.utkymd, pKekka->utkymd, 10);
					strncpy(sIrai.irino, pKekka->irino, 11);
					sIrai.zssdino = pKekka->zssdino;
					strncpy(sIrai.knsgrp, pKekka->knsgrp, 16);
					strncpy(sIrai.kmkcd, pKekka->kmkcd, 7);

					/* 希釈フラグ="2"　且つ（初回もしくは再測定）の場合 */
					/*	 検査回数←２ */
					if( pKekka->kisyakflg == '2' &&
						( pKekka->knssu == 1 || pKekka->ksktkbn == 'S' ) ) {
						rKnssu = 2;
					} else {
						rKnssu = 1;
					}
					if ((ret = ZdbIraiUpdateSaiken(sIrai,rKnssu)) != 0L) {
						if(ret > 0 || ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
							sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sprintf(errMsg,"DataBase Update Err SQL CODE:%d",ret);
						sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg) ;
						return(RET_STOP);

					}
				}
			}
		}
	}
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：insertDBCtrl()						*/
/*	機能概要  ：コントロール結果情報のインサート				*/
/*	入	  力  ：							*/
/*	 第１引数 ：buff	結果情報のCSV形式1レコード			*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int insertDBCtrl(char * buff)
{
	Ctrlkka 	* pKekka;
	char		** pFld;
	int 		cnt;
	int 		offset;
	int ret;
	struct tm		*ptm ;
	struct timeb	 timebuf ;
	char		errMsg[1024] = {0,};

	pKekka = malloc(sizeof(Ctrlkka));
	memset(pKekka, 0, sizeof(Ctrlkka));
	pFld = malloc(sizeof(char *)*200);
	/* カンマ区切りのレコードを分割し、DBレコードの構造体に設定する。 */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 31) {
		/* フィールド数が一致しない */
		sFncSyslog ( LOG_ERR, "insertDBCtrl()", "Ctrlkka CSV File Field Not Count." ) ;
		return -1;
	}

	/* 各フィールドを格納する。 */
	strncpy( pKekka->knskisymd , pFld[0] , sizeof( pKekka->knskisymd )-1);
	strncpy( pKekka->bskkbn , pFld[1] , sizeof( pKekka->bskkbn )-1);
	strncpy( pKekka->bsklne , pFld[2] , sizeof( pKekka->bsklne )-1);
	strncpy( pKekka->bskgok , pFld[3] , sizeof( pKekka->bskgok )-1);
	strncpy( pKekka->knsgrp , pFld[4] , sizeof( pKekka->knsgrp )-1);
	strncpy( pKekka->kmkcd , pFld[5] , sizeof( pKekka->kmkcd )-1);
	strncpy( pKekka->nbkmkcd , pFld[6] , sizeof( pKekka->nbkmkcd )-1);
	pKekka->ctrlno = atoi( pFld[7] );
	strncpy( pKekka->ctrlsbt , pFld[8] , sizeof( pKekka->ctrlsbt )-1);
	pKekka->ctrlsbteda = atoi( pFld[9] );
	strncpy( pKekka->ctrllbl , pFld[10] , sizeof( pKekka->ctrllbl )-1);
	pKekka->tstrflg = pFld[11][0];
	strncpy( pKekka->asyrckid , pFld[12] , sizeof( pKekka->asyrckid )-1);
	pKekka->asyrckpos = atoi( pFld[13] );
	pKekka->knsseq = atoi( pFld[14] );
	pKekka->bskseq = atoi( pFld[15] );
	pKekka->bthno = atoi( pFld[16] );
	pKekka->bthrckjbn = atoi( pFld[17] );
	strncpy( pKekka->syklotno , pFld[18] , sizeof( pKekka->syklotno )-1);
	strncpy( pKekka->sktti , pFld[19] , sizeof( pKekka->sktti )-1);
	strncpy( pKekka->knzti , pFld[20] , sizeof( pKekka->knzti )-1);
	pKekka->knztistflg = pFld[21][0];
	strncpy( pKekka->sktdh , pFld[22] , sizeof( pKekka->sktdh )-1);
	pKekka->ctrljti = atoi( pFld[23] );
	pKekka->chkzmflg = pFld[24][0];
	strncpy( pKekka->facter , pFld[25] , sizeof( pKekka->facter )-1);
	strncpy( pKekka->base , pFld[26] , sizeof( pKekka->base )-1);
	pKekka->kosijt = pFld[27][0];
	strncpy( pKekka->kositts , pFld[28] , sizeof( pKekka->kositts )-1);
	strncpy( pKekka->kosidh , pFld[29] , sizeof( pKekka->kosidh )-1);
	strncpy( pKekka->ksndh , pFld[30] , sizeof( pKekka->ksndh )-1);

	/* 換算値をコントロールマスタの小数点桁数に合わせる。 */
	Ctrlmst 	sCtrlmst;
	Ctrlmst 	*pCtrlmst;
	int 		cntCtrlmst;

	memset(&sCtrlmst, 0, sizeof(sCtrlmst));
	strncpy(sCtrlmst.bskkbn, pKekka->bskkbn, sizeof(sCtrlmst.bskkbn)-1);
	strncpy(sCtrlmst.nbkmkcd, pKekka->nbkmkcd, sizeof(sCtrlmst.nbkmkcd)-1);
	strncpy(sCtrlmst.ctrlsbt, pKekka->ctrlsbt, sizeof(sCtrlmst.ctrlsbt)-1);

	/* システム日付日時取得 */
	ftime ( &timebuf ) ;
	ptm  = ( struct tm * ) localtime ( &( timebuf.time ) ) ;
	sprintf(sCtrlmst.kaiymd, "%04d-%02d-%02d", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday);

	ret = ZdbCtrlmstSelectKey(&sCtrlmst, &pCtrlmst, &cntCtrlmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"Err SQL CODE:%d ZdbCtrlmstSelectKey",ret);

		if(ret > 0 || ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
			sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBCtrl",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "insertDBCtrl()", errMsg) ;
		return(RET_STOP);

	}
	else if (ret != HRC_SQL_NOT_FOUND) {
		double		rawData;

		rawData = atof(pKekka->knzti);
		sprintf(pKekka->knzti, "%.*f", pCtrlmst->sstnksu, (rawData + 0.00001));

		ZbmlFree(pCtrlmst);
	}

	/* DBにインサート */
	if ((ret = ZdbCtrlkkaInsert(pKekka)) != 0L) {
		/* インサートエラー */
		sprintf(errMsg,"SQL CODE:%d ZdbCtrlkkaInsert",ret);
		/* コントロール結果のインサート失敗 */
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBCtrl",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "insertDBCtrl()", errMsg) ;
		return(RET_STOP);
	}

	free(pKekka);
	free(pFld);

	return 0;
}

/******************************************************************************/
/*	関 数 名  ：insertDBX_M()						*/
/*	機能概要  ：X-M情報のインサート 					*/
/*	入	  力  ：							*/
/*	 第１引数 ：buff	結果情報のCSV形式1レコード			*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int insertDBX_M(char * buff)
{
	Xbarm		* pXbarm;
	char		** pFld;
	int 		cnt;
	int 		offset;
	int 		ret;
	int 		chkflg;
	char		errMsg[1024] = {0,};

	pXbarm = malloc(sizeof(Xbarm));
	memset(pXbarm, 0, sizeof(Xbarm));
	pFld = malloc(sizeof(char *)*200);
	/* カンマ区切りのレコードを分割し、DBレコードの構造体に設定する。 */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 19) {
		/* フィールド数が一致しない */
		sFncSyslog ( LOG_ERR, "insertDBX_M()", "Xbarm CSV File Field Not Count." ) ;
		return -1;
	}

	/* X-M結果を基準値マスタの sstn = 6 に固定にする(オンラインで小数点以下6桁で出力している為) */
	int         sstn = 6;
	/* 各フィールドを格納する。 */
	strncpy(pXbarm->knskisymd, pFld[0], 10);
	strncpy(pXbarm->bskkbn, pFld[1], 4);
	strncpy(pXbarm->bsklne, pFld[2], 4);
	strncpy(pXbarm->bskgok, pFld[3], 6);
	strncpy(pXbarm->knsgrp, pFld[4], 16);
	strncpy(pXbarm->kmkcd, pFld[5], 7);
	strncpy(pXbarm->nbkmkcd, pFld[6], 7);
	pXbarm->pltno = atoi(pFld[7]);
	pXbarm->knsseqst = atoi(pFld[8]);
	pXbarm->knsseqed = atoi(pFld[9]);
	pXbarm->bskseqst = atoi(pFld[10]);
	pXbarm->bskseqed = atoi(pFld[11]);
	pXbarm->pltseqst = atoi(pFld[12]);
	pXbarm->pltseqed = atoi(pFld[13]);
	pXbarm->pltsu = atoi(pFld[14]);
	char tmp[32];
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%.*f", sstn, atof(pFld[15]));
	strncpy(pXbarm->xbarmkka, tmp, 24);

	pXbarm->xbarmjtkbn = pFld[16][0];
	pXbarm->xbarmjkflg = pFld[17][0];
	strncpy(pXbarm->ksndh, pFld[18], 26);
	/* 個別設定 */
	pXbarm->xbarmjtkbn = 'S';

	/* X-M確定フラグは人が確定した場合のみ1とする */  
	pXbarm->xbarmjkflg = '0';

	/* 項目マスター読み出し */
	Kmkmst		sKmkmst;
	Kmkmst		*pKmkmst;
	int 		cntKmkmst;

	/* 項目マスタ取得 */
	chkflg = 0;
	memset(&sKmkmst, 0, sizeof(Kmkmst));
	strncpy(sKmkmst.knsgrp, pXbarm->knsgrp, 16);
	strncpy(sKmkmst.kmkcd, pXbarm->kmkcd, 7);
	ret = ZdbKmkmstSelectKey(&sKmkmst, &pKmkmst, &cntKmkmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectKey",ret);
		/* コントロール結果のインサート失敗 */
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBX_M",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "insertDBX_M()", errMsg) ;
		return(RET_STOP);
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		/* X-M集計フラグ('0':集計する、'1':集計しない) */
		if (pKmkmst->xmskflg == '1') {
			/* 集計を行わない */
			chkflg = 2;
		}
		/* X-Mチェックフラグ('0':異常判定を行う、'1':異常判定を行わない) */
		if (pKmkmst->xmchkflg == '1') {
			/* 異常判定を行わない */
			chkflg = 1;
		}
		ZbmlFree(pKmkmst);
	}

	/* X-M集計を行う＆X-Mチェックを行う場合 */
	if (chkflg == 0) {
		/* X_Mチェックマスタ読み取り */
		Xbarmmst	sXmmst;
		Xbarmmst	*pXmmst;
		int 		cntXmmst;

		memset(&sXmmst, 0, sizeof(sXmmst));
		strncpy(sXmmst.knsgrp, pXbarm->knsgrp, 16);
		strncpy(sXmmst.kmkcd, pXbarm->kmkcd, 7);
		strncpy(sXmmst.kaiymd, pXbarm->knskisymd, sizeof(pXbarm->knskisymd)-1);
		ret = ZdbXbarmmstSelectKey(&sXmmst, &pXmmst, &cntXmmst);
		if (ret == HRC_SQL_NORMAL) {
			if (atof(pXbarm->xbarmkka) > atof(pXmmst->maxval)) {
				pXbarm->xbarmjtkbn = 'K';
			}
			if (atof(pXbarm->xbarmkka) < atof(pXmmst->minval)) {
				pXbarm->xbarmjtkbn = 'T'; /* 'L' -> 'T'に変更 */
			}
			ZbmlFree(pXmmst);
		}
		else {
			;
		}
	}

	/* X-Mチェックを行う場合 */
	if (chkflg < 2) {
		/* DBにインサート */
		if ((ret = ZdbXbarmInsert(pXbarm)) != 0L) {
			/* インサートエラー */
			sprintf(errMsg,"SQL CODE:%d ZdbXbarmInsert",ret);
			/* X_M結果のインサート失敗 */
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBX_M",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "insertDBX_M()", errMsg ) ;
			return(RET_STOP);

		}
	}
	free(pXbarm);
	free(pFld);

	return 0;
}

void sigcatch(int sig)
{
  EndFlg = 1;
  /* シグナルハンドラをデフォルトに戻す */
  signal(sig,SIG_DFL);
}

/******************************************************************************/
/*	関 数 名　：sFncShmCrt()						*/
/*	機能概要　：共有メモリ生成						*/
/*	入　　力　：								*/
/*　 第１引数 ：struct appEnv * 	プログラム環境構造体			*/
/*	出　　力　：								*/
/*	復帰情報　：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncShmCrt ( shm_Key )
int 	shm_Key;
{
	int 	*shmData ;

	/* 取得 */
	shm_Id = shmget ( (key_t)shm_Key, sizeof( int ), 0666 | IPC_CREAT ) ;
	if ( shm_Id < 0 ) {
		/* 異常終了	LOG */
		sFncSyslog ( LOG_ERR, "shmget()", "Cannot assign shared memory." ) ;
		return ( -1 ) ;
	}

	/* アタッチ */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* 異常終了	LOG */
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* 値設定 */
	*shmData = 0 ;

	/* デタッチ */
	if ( shmdt ( shmData ) == -1 ) {
		/* 異常終了	LOG */
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*	関 数 名　：sFncShmGet()						*/
/*	機能概要　：共有メモリ取得						*/
/*	入　　力　：								*/
/*　 第１引数 ：struct appEnv * 	プログラム環境構造体			*/
/*　 第２引数 ：int *				値				*/
/*	出　　力　：								*/
/*	復帰情報　：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncShmGet ( shm_Key, pshmData )
int 			shm_Key ;
int 			*pshmData ;
{
	int 	*shmData ;

	/* アタッチ */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* 異常終了	LOG */
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* 値設定 */
	*pshmData = *shmData ;

	/* デタッチ */
	if ( shmdt ( shmData ) == -1 ) {
		/* 異常終了	LOG */
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*	関 数 名　：sFncShmDel()						*/
/*	機能概要　：共有メモリ削除						*/
/*	入　　力　：								*/
/*　 第１引数 ：struct appEnv * 	プログラム環境構造体			*/
/*	出　　力　：								*/
/*	復帰情報　：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
static int
sFncShmDel ( shm_Key )
int 		shm_Key ;
{

	/*	削除 */
	if ( shmctl ( shm_Id, IPC_RMID, NULL) < 0 ) {
		/* 異常終了	LOG */
		sFncSyslog ( LOG_ERR, "shmctl()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*	関 数 名　：_sFncSyslog()						*/
/*	機能概要　：システムログ出力						*/
/*	入　　力　：								*/
/*　 第１引数 ：int 		プライオリティー				*/
/*　 第２引数 ：char *		関数名						*/
/*　 第３引数 ：char *		メッセージ					*/
/*	出　　力　：								*/
/*	復帰情報　：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
static void
_sFncSyslog (int piPri, char * pcFncname,char * pcMsg ,char * pcErrCode, char * pcExeFlg, char * file, long lineno)
{
#if defined ( _SYSLOGOUT )
	if ( errno != 0 ) {
		syslog ( piPri, "Error: Function %s %s (errno=%d msg=%m)",
						pcFncname, pcMsg, errno ) ;
	} else {
		syslog ( piPri, "Error: Function %s %s (errno=%d)",
						pcFncname, pcMsg, errno ) ;
	}
#endif
	struct stcLogMember plm;

	memset(&plm, 0, sizeof(plm));
	plm.eTrcKind = TRCKIND_ERROR;
	plm.lPid = getpid() ;					/* プロセスID */
	strncpy(plm.pcAppName, "MD105", 32);
	strncpy(plm.pcSrcName, file, 32);
	strncpy(plm.pcFncName, pcFncname, 32);
	plm.lLineNo = lineno;
	strncpy(plm.pcExeFlg, pcExeFlg, 2);
	strncpy(plm.pcErrCode, pcErrCode, 8);
	strncpy(plm.pcMsg, pcMsg, 1024);

	_ZbmlPutLog(&plm, file, lineno);
}
/******************************************************************************/
/*	関 数 名　：sFncPutlog()						*/
/*	機能概要　：システムログ出力						*/
/*	入　　力　：								*/
/*　 第１引数 ：int 		プライオリティー				*/
/*　 第２引数 ：char *		関数名						*/
/*　 第３引数 ：char *		メッセージ					*/
/*	出　　力　：								*/
/*	復帰情報　：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
void
sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName, int plLineNo, char *
 pcExeFlg, char *pcErrCode, char *pcfmt, ... )
{
	va_list  ap ;
	struct stcLogMember plm;

	/***
	 ***	ログ初期値設定
	 ***/
	memset(&plm, 0, sizeof(plm));
	plm.eTrcKind = peTrcKind ;
	strcpy ( plm.pcFncName, pcFncName ) ;
	strcpy ( plm.pcExeFlg,	pcExeFlg ) ;
	strcpy ( plm.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( plm.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***
	 ***	ログ出力
	 ***/
	_ZbmlPutLog ( &plm, pcSrcName, plLineNo) ;
	return ;

}

/* 指定文字列の前後のスペースを取り除いて文字列をコピーする */
void trim(char * dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0;
		src[srcCnt] != '\0';
		srcCnt ++) {
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

/******************************************************************************/
/*	関 数 名  ：TourokuChk()						*/
/*	機能概要  ：結果情報登録チェック					*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
/* 結果情報登録チェック */
int TourokuChk(Kekka *pKekka, int *iKesseiflg)
{


	int 		ret = 0;
	Realchk 	*pReal;
	Kenorder	sKenorder;
	Kenorder	*pKenorder;
	int 		orderCnt;
	char		errMsg[1024] = {0,};

	/* 基準値マスタの取得 */
	Kjnmst		sKjnmst;
	Kjnmst		*pKjnmst;
	int 		cntKjnmst;

	memset(&sKjnmst, 0, sizeof(sKjnmst));
	strncpy(sKjnmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sKjnmst.kjno, pKekka->kjno, 9);

	/* 基準値マスタSELECT */
	ret = ZdbKjnmstSelectKey2(&sKjnmst, &pKjnmst, &cntKjnmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKjnmstSelectKey2",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "TourokuChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "TourokuChk()", errMsg ) ;
		return(RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		sFncPutLog (TRCKIND_DEBUG, __FILE__, "TourokuChk", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "ZdbKjnmstSelectKey2 Not Found ret:0") ;
		return 0;
	}

	/* 新しい追加コード filterChk2 */
	ret = filterChk2(pKekka, pKjnmst);
	if(RET_STOP == ret || ret == RET_CONTINUITY){
		ZbmlFree(pKjnmst);
		return ret;
	}

	/* 基準値チェック */
	if (kjnChk(pKekka, pKjnmst) != 0) {
		ZbmlFree(pKjnmst);
		return -3;
	}
	ZbmlFree(pKjnmst);

	/* オーダー&即時チェックSELECT */
	memset(&sKenorder, 0, sizeof(sKenorder));
	strncpy(sKenorder.knskisymd, pKekka->knskisymd, 10);
	strncpy(sKenorder.sriymd, pKekka->sriymd, 10);
	strncpy(sKenorder.kntno, pKekka->kntno, 13);
	strncpy(sKenorder.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKenorder.kmkcd, pKekka->kmkcd, 8);
	sKenorder.knssu = pKekka->knssu;
	sKenorder.knssueda = 0;

	ret = ZdbKenorderRealchkSelectKey(&sKenorder, &pKenorder, &pReal, &orderCnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKenorderRealchkSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "TourokuChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "TourokuChk()", errMsg ) ;
		return(RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		/* 再検時を考慮し、検査回数が１より大きいときは検査回数をデクリメントし */
		/* もう一度、検索する。 */
		if (sKenorder.knssu > 1) {
			sKenorder.knssu--;
			ret = ZdbKenorderRealchkSelectKey(&sKenorder, &pKenorder, &pReal, &orderCnt);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				sprintf(errMsg,"SQL CODE:%d ZdbKenorderRealchkSelectKey",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING , __FILE__, "TourokuChk", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "TourokuChk()", errMsg ) ;
				return(RET_STOP);
			}
			if (ret == HRC_SQL_NOT_FOUND) {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	/* １００％チェック */
	if (pReal[0].per100flg == '1') {
		/* 100％チェック */
		per100Chk(pKekka);
	}
	else {
		pKekka->per100flg = '0';				/* １００％チェック */
	}

	/* 照合チェック */
	/*	【条件】 */
	/*	オーダ情報が存在せず（オーダ情報・回数と結果情報の回数に差異）、 */
	/*	検査工程区分Ｋ（再検）の場合のみ行う */
	if ( sKenorder.knssu != pKekka->knssu && pKekka->ksktkbn == 'K' ) {
		ret = shougoChk(pKekka, pKenorder, iKesseiflg);
		if(ret == RET_STOP || ret == RET_CONTINUITY)
			return ret;
	} else if ( sKenorder.knssu == pKekka->knssu && pKekka->ksktkbn == 'K' ) {
		pKekka->kkajkcd 		= '1';				/* 結果状況コード */
		pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
		pKekka->siyflg			= ' ';				/* 採用フラグ */
		pKekka->knsflg			= 'A';				/* 検査フラグ */
	}

	/* 透析前後チェック */
	if (pReal[0].tousekflg == '1') {
		ret = tousekiChk(pKekka);
		if(ret == RET_STOP || ret == RET_CONTINUITY)
			return ret;
	}
	else {
		pKekka->tousekflg = '0';
	}

	/* 相関チェック(WS間) */
	if (pReal[0].soukn2flg == '1') {
		ret = soukanChk(pKekka, pKenorder);
		if(ret == RET_STOP || ret == RET_CONTINUITY)
			return ret;
	}
	else {
		pKekka->soukn2flg = '0';
	}


	/* ＢＭＬパニックチェック */
	ret = BmlPanicChk(pKekka, pKenorder);
	if(RET_STOP == ret || ret == RET_CONTINUITY)
		return ret;

    /* 検査室パニックチェック */
    ret = KnsPanicChk(pKekka, pKenorder);
    if(RET_STOP == ret || ret == RET_CONTINUITY)
        return ret;

	/* 分画そろいチェック(照合ＮＧのみ行う) */
	ret = bungaChk(pKekka, iKesseiflg);
	if(RET_STOP == ret || ret == RET_CONTINUITY)
		return ret;

	ZbmlFree(pReal);
	ZbmlFree(pKenorder);

	return 0;
}
/******************************************************************************/
/*	関 数 名  ：kjnchk()							*/
/*	機能概要  ：基準値チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int kjnChk(Kekka *pKekka, Kjnmst *pKjnmst)
{
	/* 基準値から異常区分をチェックし、特別異常区分を設定する */
	char		tmp1[16];
	char		tmp2[16];
	double		rawData;
	char		wk_knskka[25];
	int 		ikzn;
	int 		iwkkzn;

	/* 異常値区分の初期化 */
	pKekka->ijkbnm = pKekka->ijkbnf = pKekka->ijkbnn = ' ';
	ikzn = 0;

	trim(wk_knskka, pKekka->knskka2);

	/* 結果コメントの基準値判断を追加 */
	if( pKekka->knskka2kbn[0] == '0' && atoi(wk_knskka) < 500 ){ /* *500以下の結果コメントか？ */
		/* 結果コメントのチェック */
		if(CHK_Kkacmt(wk_knskka) == 0){
			/* 異常値マーク無し; */
			pKekka->ijkbnm = ' ';
			pKekka->ijkbnf = ' ';
			pKekka->ijkbnn = ' ';
		}
		else {
			/* 異常値マーク有り; */
			pKekka->ijkbnm = '*';
			pKekka->ijkbnf = '*';
			pKekka->ijkbnn = '*';
		}
		return 0;
	}

	/* 定性項目の場合、基準値判定の為定性値を換算値に変換する */
	if (pKekka->tstrflg == 'S') {
		/* 定性項目 */
		/* 結果データに数値以外があるかチェック */
		ikzn = CHG_Mojikjn(wk_knskka,pKekka->knskka2kbn[0]);
		if(ikzn == 0){
			/* 換算値が見つからなかった */
			/* 基準値マスタに基準値設定がある場合"*"、 */
			/* 基準値マスタに基準値設定がない場合" " */
			/* を設定する */

			/* 男性 */
			trim(tmp1, pKjnmst->kjnmlw);
			trim(tmp2, pKjnmst->kjnmhi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnm = ' ';
			}
			else {
				pKekka->ijkbnm = '*';
			}

			/* 女性 */
			trim(tmp1, pKjnmst->kjnflw);
			trim(tmp2, pKjnmst->kjnfhi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnf = ' ';
			}
			else {
				pKekka->ijkbnf = '*';
			}

			/* 不明 */
			trim(tmp1, pKjnmst->kjnelw);
			trim(tmp2, pKjnmst->kjnehi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnn = ' ';
			}
			else {
				pKekka->ijkbnn = '*';
			}
			/* 異常値区分が設定されたので抜ける */
			return 0;
		}

		/* 基準値 → 換算値変換（定性項目のみ） */
		/* 男低値１ */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm1,"%d",iwkkzn);
		}
		/* 男低値２ */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm2,"%d",iwkkzn);
		}
		/* 男基準値下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnmlw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmlw,"%d",iwkkzn);
		}
		/* 男基準値内下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm1,"%d",iwkkzn);
		}
		/* 男高値２ */
		iwkkzn =  CHG_Mojikjn(pKjnmst->him2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him2,"%d",iwkkzn);
		}
		/* 男高値１ */
		iwkkzn =  CHG_Mojikjn(pKjnmst->him1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him1,"%d",iwkkzn);
		}
		/* 男基準値上 */
		iwkkzn = CHG_Mojikjn(pKjnmst->kjnmhi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmhi,"%d",iwkkzn);
		}
		/* 男基準値内下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm2,"%d",iwkkzn);
		}
		/* 女低値１ */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf1,"%d",iwkkzn);
		}
		/* 女低値２ */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwf2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf2,"%d",iwkkzn);
		}
		/* 女基準値下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnflw,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnflw,"%d",iwkkzn);
		}
		/* 女基準値内下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnnaf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnnaf1,"%d",iwkkzn);
		}
		/* 女高値２ */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hif2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif2,"%d",iwkkzn);
		}
		/* 女高値１ */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hif1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif1,"%d",iwkkzn);
		}
		/* 女基準値上 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnfhi,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnfhi,"%d",iwkkzn);
		}
		/* 女基準値内下 */
		iwkkzn = CHG_Mojikjn(pKjnmst->kjnnaf2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnnaf2,"%d",iwkkzn);
		}
		/* 不明低値１ */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwe1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwe1,"%d",iwkkzn);
		}
		/* 不明低値２ */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwe2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwe2,"%d",iwkkzn);
		}
		/* 不明基準値下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnelw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnelw,"%d",iwkkzn);
		}
		/* 不明基準値内下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kje1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje1,"%d",iwkkzn);
		}
		/* 不明高値２ */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hie2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie2,"%d",iwkkzn);
		}
		/* 不明高値１ */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hie1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie1,"%d",iwkkzn);
		}
		/* 不明基準値上 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnehi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnehi,"%d",iwkkzn);
		}
		/* 不明基準値内下 */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kje2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje2,"%d",iwkkzn);
		}
	}
#define chknum1(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 < atof(p2)))
#define chknum2(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 > atof(p2)))

#define chknumi1(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 < atoi(p2)))
#define chknumi2(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 > atoi(p2)))

	if( ikzn == 0 ){
		//rawData = atof(pKekka->rawdata);
		//rawData = atof(pKekka->skkaka);
		rawData = atof(pKekka->knskka1);
		if (pKmkmst != NULL && pKmkmst->ltmmnflg == '1') {
			rawData = rawData - pow(10.0, pKjnmst->kjsstnksu);
		}

		/* 定量項目の比較(float float) */
		/* 男性のチェック */
		pKekka->ijkbnm = '5';
		if chknum1(rawData , pKjnmst->lwm1) {
			pKekka->ijkbnm = '1';
		}
		else if chknum1(rawData, pKjnmst->lwm2) {
			pKekka->ijkbnm = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnmlw) {
			pKekka->ijkbnm = '3';
		}
		else if chknum1(rawData, pKjnmst->kjm1) {
			pKekka->ijkbnm = '4';
		}
		else if chknum2(rawData, pKjnmst->him2) {
			pKekka->ijkbnm = '9';
		}
		else if chknum2(rawData, pKjnmst->him1) {
			pKekka->ijkbnm = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnmhi) {
			pKekka->ijkbnm = '7';
		}
		else if chknum2(rawData, pKjnmst->kjm2) {
			pKekka->ijkbnm = '6';
		}
		/* 女性のチェック */
		pKekka->ijkbnf = '5';
		if chknum1(rawData, pKjnmst->lwf1) {
			pKekka->ijkbnf = '1';
		}
		else if chknum1(rawData, pKjnmst->lwf2) {
			pKekka->ijkbnf = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnflw) {
			pKekka->ijkbnf = '3';
		}
		else if chknum1(rawData, pKjnmst->kjnnaf1) {
			pKekka->ijkbnf = '4';
		}
		else if chknum2(rawData, pKjnmst->hif2) {
			pKekka->ijkbnf = '9';
		}
		else if chknum2(rawData, pKjnmst->hif1) {
			pKekka->ijkbnf = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnfhi) {
			pKekka->ijkbnf = '7';
		}
		else if chknum2(rawData, pKjnmst->kjnnaf2) {
			pKekka->ijkbnf = '6';
		}
		/* 不明のチェック */
		pKekka->ijkbnn = '5';
		if chknum1(rawData, pKjnmst->lwe1) {
			pKekka->ijkbnn = '1';
		}
		else if chknum1(rawData, pKjnmst->lwe2) {
			pKekka->ijkbnn = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnelw) {
			pKekka->ijkbnn = '3';
		}
		else if chknum1(rawData, pKjnmst->kje1) {
			pKekka->ijkbnn = '4';
		}
		else if chknum2(rawData, pKjnmst->hie2) {
			pKekka->ijkbnn = '9';
		}
		else if chknum2(rawData, pKjnmst->hie1) {
			pKekka->ijkbnn = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnehi) {
			pKekka->ijkbnn = '7';
		}
		else if chknum2(rawData, pKjnmst->kje2) {
			pKekka->ijkbnn = '6';
		}
	}
	else{
		/* 定性値の換算が成功したので、 */
		/* 換算値をローデータとして扱う */

		/* 定性項目の比較 */
		/* 男性のチェック */
		pKekka->ijkbnm = '5';
		if chknumi1(ikzn , pKjnmst->lwm1) {
			pKekka->ijkbnm = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwm2) {
			pKekka->ijkbnm = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnmlw) {
			pKekka->ijkbnm = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kjm1) {
			pKekka->ijkbnm = '4';
		}
		else if chknumi2(ikzn, pKjnmst->him2) {
			pKekka->ijkbnm = '9';
		}
		else if chknumi2(ikzn, pKjnmst->him1) {
			pKekka->ijkbnm = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnmhi) {
			pKekka->ijkbnm = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kjm2) {
			pKekka->ijkbnm = '6';
		}
		/* 女性のチェック */
		pKekka->ijkbnf = '5';
		if chknumi1(ikzn, pKjnmst->lwf1) {
			pKekka->ijkbnf = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwf2) {
			pKekka->ijkbnf = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnflw) {
			pKekka->ijkbnf = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kjnnaf1) {
			pKekka->ijkbnf = '4';
		}
		else if chknumi2(ikzn, pKjnmst->hif2) {
			pKekka->ijkbnf = '9';
		}
		else if chknumi2(ikzn, pKjnmst->hif1) {
			pKekka->ijkbnf = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnfhi) {
			pKekka->ijkbnf = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kjnnaf2) {
			pKekka->ijkbnf = '6';
		}
		/* 不明のチェック */
		pKekka->ijkbnn = '5';
		if chknumi1(ikzn, pKjnmst->lwe1) {
			pKekka->ijkbnn = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwe2) {
			pKekka->ijkbnn = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnelw) {
			pKekka->ijkbnn = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kje1) {
			pKekka->ijkbnn = '4';
		}
		else if chknumi2(ikzn, pKjnmst->hie2) {
			pKekka->ijkbnn = '9';
		}
		else if chknumi2(ikzn, pKjnmst->hie1) {
			pKekka->ijkbnn = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnehi) {
			pKekka->ijkbnn = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kje2) {
			pKekka->ijkbnn = '6';
		}
	}
	return 0;
}


/******************************************************************************/
/*	関 数 名  ：filterChk2()						*/
/*	機能概要  ：フィルターチェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int filterChk2(Kekka *pKekka, Kjnmst *pKjnmst)
{
	Kkafltmst2	 *pKkafltmst2;
	Kkafltmst2	 sKkafltmst2;
	int 		ret;
	int 		Kkafltmstflg;
	int 		cnt;
	int 		lCnt;
	double		rawData;
	double		DataMax;
	double		DataMin;
	char		tmp[32];
	int 		mojiFlg = 0;
	char		errMsg[1024] = {0,};

	pKkafltmst2 = NULL;

	/* フィルターマスター読み出し */
	memset(&sKkafltmst2, 0, sizeof(sKkafltmst2));
	strncpy(sKkafltmst2.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKkafltmst2.kmkcd, pKekka->kmkcd, 7);
	strncpy(sKkafltmst2.sstcd, pKekka->sstcd, 7);
	cnt = 0;

	ret = ZdbKkafltmstSelectGRPKMKKey2(&sKkafltmst2, &pKkafltmst2, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKkafltmstSelectGRPKMKKey2",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "filterChk2", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "filterChk2()", errMsg ) ;
		return(RET_STOP);
	}

	/* 結果値の値文字列を数値化する */
	memset(tmp, 0, sizeof(tmp));
	trim(tmp, pKekka->rawdata);
	if ((tmp[0] >= '0'&&tmp[0]<='9') || tmp[0]=='+' || tmp[0]=='-' || tmp[0] == '.' ) {
		rawData = atof(tmp);
	}
	else {
		/* 文字のときはフィルター処理を行わない */
		cnt = 0;
		mojiFlg = 1;
		ZbmlFree(pKkafltmst2);
	}

	Kkafltmstflg = 0;
	if (cnt > 0) {
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			/* 上限・下限の値文字列を数値化する */
			memset(tmp, 0, sizeof(tmp));
			strncpy(tmp, pKkafltmst2[lCnt].minval, 12);
			DataMin = atof(tmp);

			memset(tmp, 0, sizeof(tmp));
			strncpy(tmp, pKkafltmst2[lCnt].maxval, 12);
			DataMax = atof(tmp);

			if ((DataMin <= rawData) && (rawData <= DataMax)) {
				strncpy(pKekka->knskka1, pKkafltmst2[lCnt].knskka1, 12);
				strncpy(pKekka->knskka2, pKkafltmst2[lCnt].knskka2, 24);
				strncpy(pKekka->knskka2kbn, pKkafltmst2[lCnt].knskka2kbn, 2);
				strncpy(pKekka->kkahskcd, pKkafltmst2[lCnt].kkahskcd, 3);
				strncpy(pKekka->skkka, pKkafltmst2[lCnt].hjkka, 24);	 /*  */
				if (pKjnmst->kjsstnksu == 9) {
					sprintf(tmp, "%.0f", (rawData + 0.00001));
				}
				else {
					sprintf(tmp, "%.*f", pKjnmst->kjsstnksu, (rawData + 0.00001));
				}
				strncpy(pKekka->hjkka, tmp, 24);
				Kkafltmstflg = 1;
				break;
			}
		}
		ZbmlFree(pKkafltmst2);
	}
	if ((cnt <= 0) || (Kkafltmstflg == 0)) {
		/* フィルターマスターに存在しないとき */
		/* フィルターマスターの情報でヒットしなかった。 */
		if (mojiFlg == 1) {
			strncpy(pKekka->knskka2, tmp, 24);
			strncpy(pKekka->knskka2kbn, "X", 2);
		}
		else if (pKjnmst->kjsstnksu == 9) {
			/* 小数点桁数が９の時は直値 */
			sprintf(tmp, "%.0f", (rawData + 0.00001));
			strncpy(pKekka->knskka2, tmp, 24);
			strncpy(pKekka->knskka2kbn, "X", 2);
		}
		else {
			sprintf(tmp, "%.*f", pKjnmst->kjsstnksu, (rawData + 0.00001));
			if (pKekka->tstrflg == 'S') {		/* 定性 */
				strncpy(pKekka->knskka2, tmp, 24);
				strncpy(pKekka->knskka2kbn, "X", 2);
			}
			else if (pKekka->tstrflg == 'R') {	/* 定量 */
				memset(pKekka->knskka1, ' ', 12);
				strcpy(&(pKekka->knskka1[12-strlen(tmp)]), tmp);
				strncpy(tmp, pKekka->knskka1, 32);
			}
			else {								/* 不明 */
				strncpy(pKekka->knskka2, tmp, 24);
				strncpy(pKekka->knskka2kbn, "X", 2);
			}
		}
		trim(pKekka->hjkka, tmp);			/* 左詰(定量時右詰になっているものを左詰に変換) */
		strncpy(pKekka->skkka, tmp, 24);	/* 定量時右詰・それ以外左詰 */
	}
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：per100Chk() 						*/
/*	機能概要  ：100%チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int per100Chk(Kekka *pKekka)
{

/* 未対応のため、実装しない */

	return 0;
}

/******************************************************************************/
/*	関 数 名  ：BmlPanicChk()						*/
/*	機能概要  ：ＢＭＬパニックチェック					*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int BmlPanicChk(Kekka *pKekka, Kenorder *pKenorder)
{
	Rngchkmst	sRngchkmst;
	Rngchkmst	*pRngchkmst;
	int 		cnt;
	int 		ret;
	double		rawData;
	char		cRawBuf[256];
	char		errMsg[1024] = {0,};

	/* 生データがない(スペースor/)の場合なにもしない */
	memset(cRawBuf, 0, sizeof(cRawBuf));
	trim(cRawBuf, pKekka->rawdata);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, 0, sizeof(Rngchkmst));
	/* 範囲区分を条件に追加 */
	sRngchkmst.hnikbn = BML_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pKenorder->zrcd, "001", 3) == 0)
		|| (strncmp(pKenorder->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pKenorder->sbtkbn;
	/* 施設コード、性別区分を指定して検索 */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg) ;
		return(RET_STOP);

	}
	/* 見つからなかった場合、施設コードを指定、性別区分をオール(' ')で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
        sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "BmlPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	/* さらに見つからなかった場合、性別区分を指定し、施設コードをオール(0000000)で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pKenorder->sbtkbn;
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg) ;
			return(RET_STOP);
		}
	}
	/* それでも見つからなかった場合、施設コード、性別区分共にオール指定で検索 */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->rawdata);
		pKekka->pncrgflg = '0';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ((atof(pRngchkmst[lCnt].hrng) >= rawData) &&
				(rawData >= atof(pRngchkmst[lCnt].lrng))) {
				pKekka->pncrgflg = '0';
			}
			else {
				pKekka->pncrgflg = '1';
				break;
			}
		}
	}
	ZbmlFree(pRngchkmst);
	return 0;
}

/******************************************************************************/
/*  関 数 名  ：KnsPanicChk()                                                 */
/*  機能概要  ：検査室パニックチェック                                        */
/*  入    力  ：                                                              */
/*   第１引数 ：pKekka  結果情報                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：int                                                           */
/*                   0  正常                                                  */
/*                  -1  異常                                                  */
/******************************************************************************/
int KnsPanicChk(Kekka *pKekka, Kenorder *pKenorder)
{
	Rngchkmst   sRngchkmst;
	Rngchkmst   *pRngchkmst;
	int         cnt;
	int         ret;
	double      rawData;
	char        cRawBuf[256];
	char        errMsg[1024] = {0,};

	/* 生データがない(スペースor/)の場合なにもしない */
	memset(cRawBuf, 0, sizeof(cRawBuf));
	trim(cRawBuf, pKekka->rawdata);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, 0, sizeof(Rngchkmst));
	/* 範囲区分を条件に追加(検査室パニックのみ取得) */
	sRngchkmst.hnikbn = KNS_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pKenorder->zrcd, "001", 3) == 0)
		|| (strncmp(pKenorder->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pKenorder->sbtkbn;
	/* 施設コード、性別区分を指定して検索 */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg) ;
		return(RET_STOP);

	}
	/* 見つからなかった場合、施設コードを指定、性別区分をオール(' ')で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
        sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "KnsPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	/* さらに見つからなかった場合、性別区分を指定し、施設コードをオール(0000000)で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pKenorder->sbtkbn;
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg) ;
			return(RET_STOP);
		}
	}
	/* それでも見つからなかった場合、施設コード、性別区分共にオール指定で検索 */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->rawdata);
		pKekka->knspncrgflg = '0';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ((atof(pRngchkmst[lCnt].hrng) >= rawData) &&
				(rawData >= atof(pRngchkmst[lCnt].lrng))) {
				pKekka->knspncrgflg = '0';
			}
			else {
				pKekka->knspncrgflg = '1';
				break;
			}
		}
	}
	ZbmlFree(pRngchkmst);
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：tousekiChk()						*/
/*	機能概要  ：透析前後チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int tousekiChk(Kekka *pKekka)
{
	Tschkmst	sTschkmst;
	Tschkmst	*pTschkmst;
	int 		cntTschkmst;
	int 		ret;
	Kekka		sKekka;
	Kekka		*spKekka;
	int 		cntKekka;
	int 		flg;
	double		rawData;
	int 		updateflg;
	char		errMsg[1024] = {0,};

	if ((strncmp(pKekka->tskflg, "ｾ", 2) != 0) &&
		(strncmp(pKekka->tskflg, "ｺ", 2) != 0)) {
		/* 透析項目でない。 */
		pKekka->tousekflg = '1';
		return 0;
	}

	/* 透析の相方項目を調べる（透析前後チェックマスタ） */
	memset(&sTschkmst, 0, sizeof(Tschkmst));
	if (strncmp(pKekka->tskflg, "ｾ", 2) == 0) {
		strncpy(sTschkmst.kmkcdzen, pKekka->kmkcd, 7);
		strncpy(sTschkmst.kmkcdgo, "       ", 7);
		flg = 0;
	}
	else {
		strncpy(sTschkmst.kmkcdzen, "       ", 7);
		strncpy(sTschkmst.kmkcdgo, pKekka->kmkcd, 7);
		flg = 1;
	}
	pTschkmst->tskchktyp = '2'; 	/* シングル・マルチ系のためチェックタイプA固定 */
	ret = ZdbTschkmstSelectKey2(&sTschkmst, &pTschkmst, &cntTschkmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		pKekka->tousekflg = '2';
		pKekka->knsflg = 'A';

		sprintf(errMsg,"SQL CODE:%d ZdbTschkmstSelectKey2",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "tousekiChk", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "tousekiChk()", errMsg ) ;
		return(RET_STOP);

		//return -1;
	}

	if (ret != HRC_SQL_NOT_FOUND) {
		/* 対になる検査結果を検索 */
		memcpy(&sKekka, pKekka, sizeof(Kekka) );
		if (flg == 0) {
			strncpy(sKekka.kmkcd, pTschkmst->kmkcdgo, 8);
		}
		else {
			strncpy(sKekka.kmkcd, pTschkmst->kmkcdzen, 8);
		}
		ret = ZdbKekkaSelectIrai(&sKekka, &spKekka, &cntKekka);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sFncSyslog ( LOG_ERR, "tousekiChk()", "DataBase Tschkmst Select Error." ) ;
			pKekka->tousekflg = '2';
			pKekka->knsflg = 'A';

			sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectIrai",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "tousekiChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "tousekiChk()", errMsg) ;
			return(RET_STOP);

		}
		if (ret != HRC_SQL_NOT_FOUND) {
			/* チェックタイプにより、差を求めるか、比を求めてチェックする。 */
			pKekka->tousekflg = '1';
			updateflg = 0;
			if (pTschkmst->tskchktyp == '2') {
				/* タイプA */
				if (flg == 0) {
					if ((atof(spKekka->rawdata) - atof(pKekka->rawdata)) >= 0) {
						pKekka->tousekflg = '2';
						spKekka->tousekflg = '2';
						pKekka->knsflg = 'A';
						spKekka->knsflg = 'A';
						updateflg = 1;
					}
				}
				else {
					if ((atof(pKekka->rawdata) - atof(spKekka->rawdata)) >= 0) {
						pKekka->tousekflg = '2';
						spKekka->tousekflg = '2';
						pKekka->knsflg = 'A';
						spKekka->knsflg = 'A';
						updateflg = 1;
					}
				}
			}
			else {
				/* タイプB */
				if (flg == 0) {
					rawData = atof(spKekka->rawdata) / atof(pKekka->rawdata) *100;
				}
				else {
					rawData = atof(pKekka->rawdata) / atof(spKekka->rawdata) * 100;
				}
				if ((atof(pTschkmst->maxval) != 0) && (atof(pTschkmst->maxval) < rawData)) {
					pKekka->tousekflg = '2';
					spKekka->tousekflg = '2';
					pKekka->knsflg = 'A';
					spKekka->knsflg = 'A';
					updateflg = 1;
				}
				if ((atof(pTschkmst->minval) != 0) && (atof(pTschkmst->minval) > rawData)) {
					pKekka->tousekflg = '2';
					spKekka->tousekflg = '2';
					pKekka->knsflg = 'A';
					spKekka->knsflg = 'A';
					updateflg = 1;
				}
			}

			if (updateflg == 1) {
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING , __FILE__, "tousekiChk", __LINE__,
							 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog (LOG_ERR,"tousekiChk()",errMsg);
					return(RET_STOP);

				}
			}
		}
		else {
			/* 相手の結果がない */
			pKekka->knsflg = 'A';
		}
	}
	ZbmlFree(spKekka);
	ZbmlFree(pTschkmst);
	return 0;
}
/******************************************************************************/
/*	関 数 名  ：bungaChk()							*/
/*	機能概要  ：分画そろいチェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int bungaChk(Kekka *pKekka, int *iKesseiflg)
{
	/* 項目マスタを見て、そろっているか確認する */
	Kmkmst		sKmkmst;
	Kmkmst		*pKmkmst;
	int 		cntKmkmst;
	int 		ret;
	Kekka		sKekka;
	Kekka		*spKekka;
	int 		cntKekka;
	int 		cnt;
	int 		lcnt;
	int 		flg;
	char		errMsg[1024] = {0,};

	/* 親項目コード取得 */
	memset(&sKmkmst, 0, sizeof(Kmkmst));
	strncpy(sKmkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKmkmst.kmkcd, pKekka->kmkcd, 7);
	ret = ZdbKmkmstSelectKey(&sKmkmst, &pKmkmst, &cntKmkmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
		return(RET_STOP);

	}
	if (ret != HRC_SQL_NOT_FOUND) {
		memcpy(&sKmkmst, pKmkmst, sizeof(Kmkmst));
		ZbmlFree(pKmkmst);
		if (sKmkmst.fkbnkkb != '2') {
			/* 分画子でないときはチェックしない */
			return 0;
		}
		/* 同じ親項目コードの項目を探し出す。 */
		ret = ZdbKmkmstSelectKey4(&sKmkmst, &pKmkmst, &cntKmkmst);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

			sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectKey4",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
			return(RET_STOP);
		}
		if (ret != HRC_SQL_NOT_FOUND){
			flg = 1;
			for (cnt = 0; cnt < cntKmkmst; cnt++) {
				if (strncmp(pKekka->kmkcd, pKmkmst[cnt].kmkcd, 7) == 0) {
					continue;
				}
				if (pKmkmst[cnt].fkbnkkb == '1') {
					/* 分画の親はチェック対象外 */
					continue;
				}
				memcpy(&sKekka, pKekka, sizeof(Kekka) );
				strncpy(sKekka.kmkcd, pKmkmst[cnt].kmkcd, 8);
				ret = ZdbKekkaSelectKey2(&sKekka, &spKekka, &cntKekka);
				if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND))
				{

					sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKey2",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
							 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}

					sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
					ZbmlFree(pKmkmst);
					return(RET_STOP);
				}
				if (ret == HRC_SQL_NOT_FOUND ||
						spKekka->syougoflg == '2' ) {
					flg = 0;
				}
				ZbmlFree(spKekka);
			}
			if (flg == 1) {
				/* すべての結果がそろっている。 */
				/* 報告可能にフラグを設定 */
				for (cnt = 0; cnt < cntKmkmst; cnt++) {
					if (strncmp(pKekka->kmkcd, pKmkmst[cnt].kmkcd, 7) == 0) {
						continue;
					}
					memcpy(&sKekka, pKekka, sizeof(Kekka) );
					strncpy(sKekka.kmkcd, pKmkmst[cnt].kmkcd, 8);
					ret = ZdbKekkaSelectKey2(&sKekka, &spKekka, &cntKekka);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

						sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKey2",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}

						sFncSyslog(LOG_ERR,"bungaChk()",errMsg);
						ZbmlFree(pKmkmst);
						return(RET_STOP);
					}
					if (ret == HRC_SQL_NOT_FOUND) {
						for (lcnt = 0; lcnt < cntKekka; lcnt++) {
							ret = ZdbKekkaUpdate(&spKekka[lcnt]);
							if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
								sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
								if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
									sFncPutLog (TRCKIND_WARNING , __FILE__,
										"bungaChk", __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
									return(RET_CONTINUITY);
								}
								sFncSyslog ( LOG_ERR, "bungaChk()",errMsg ) ;
								ZbmlFree(pKmkmst);
								return(RET_STOP);



							}
						}
					}
					ZbmlFree(spKekka);
				}
				/* 分画親の結果レコードを作成する。 */
				/* 項目コード '0006485'の分画親レコードはインサートしない */
				/* 項目コード '0006485'は分画親の特別処理を一切行わない */
				if(memcmp(pKekka->oyakmkcd,"0006485",7) != 0) {
					memcpy(&sKekka, pKekka, sizeof(Kekka) );
					strncpy(sKekka.kmkcd, sKmkmst.oyakmkcd, 8);
					sKekka.knssu = 1;
					sKekka.knssueda = 0;
					/* ひとまずインサートし、重複エラーは無視する。 */
					ret = ZdbKekkaInsert2(&sKekka);
					if ((ret != HRC_SQL_NORMAL) && (ret != -803)) {

						sprintf(errMsg,"SQL CODE:%d ZdbKekkaInsert2",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}

						sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
						ZbmlFree(pKmkmst);
						return(RET_STOP);
					}

					/* 登録されているレコードを読み出す。 */
					ret = ZdbKekkaSelectKey(&sKekka, &spKekka, &cntKekka);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
						sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKey",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR,"bungaChk()",errMsg);
						ZbmlFree(pKmkmst);
						return(RET_STOP);
					}
					if (ret != HRC_SQL_NOT_FOUND) {
						spKekka->knsflg 		= 'X';				/* 検査フラグ */
						spKekka->kkajkcd		= '3';				/* 結果状況コード */
						spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
						spKekka->siyflg 		= '1';				/* 採用フラグ */

						/* 分析機区分等を設定する。 */
						strncpy(spKekka->bskkbn, pKekka->bskkbn, sizeof(spKekka->bskkbn)-1);			/* 分析機区分 */
						strncpy(spKekka->bsklne, pKekka->bsklne, sizeof(spKekka->bsklne)-1);			/* 分析機ライン */
						strncpy(spKekka->bskgok, pKekka->bskgok, sizeof(spKekka->bskgok)-1);			/* 分析機号機 */
						spKekka->bskseq = pKekka->bskseq;												/* 分析機ＳＥＱ */
						strncpy(spKekka->sktdh, pKekka->sktdh, sizeof(spKekka->sktdh)-1);				/* 測定日時 */

						/* 新規に作成した結果の登録チェックを行う。 */
						TourokuChk(spKekka, iKesseiflg);

						spKekka->ctrlno = pKekka->ctrlno;												/* CTRL No */
						strncpy(spKekka->knskka2, "0400", 24);
						strncpy(spKekka->knskka2kbn, "0", 2);
						strncpy(spKekka->hjkka, "*400", 24);
						/* upd 2007-01-16 Nagata 照会結果を"*400" → スペースに変更 */
						strncpy(spKekka->skkka, " ", 24);

						spKekka->ijkbnm = ' ';
						spKekka->ijkbnf = ' ';
						spKekka->ijkbnn = ' ';

						ret = ZdbKekkaUpdate(spKekka);
						if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
							sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
							if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
								sFncPutLog (TRCKIND_WARNING, __FILE__, "bungaChk",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
								return(RET_CONTINUITY);
							}
							sFncSyslog ( LOG_ERR, "bungaChk()", errMsg) ;
							ZbmlFree(pKmkmst);
							ZbmlFree(spKekka);
							return(RET_STOP);
						}
						ZbmlFree(spKekka);
					}

				}
			}
			else {
				pKekka->knsflg = 'R';
				pKekka->bunkkuflg = '2';
			}
		}
		ZbmlFree(pKmkmst);
	}

	return 0;
}
/******************************************************************************/
/*	関 数 名  ：shougoChk() 						*/
/*	機能概要  ：照合チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int shougoChk(Kekka *pKekka, Kenorder *pKenorder, int *iKesseiflg)
{
	Rngchkmst	sRngchkmst;
	Rngchkmst	*pRngchkmst;
	Kekka		sKekka;
	Kekka		*spKekka;
	int 		cnt;
	int 		ret;
	double		rawData;
	double		rawDataZen;
	double		chk;
	int 		flg;
	double		hi_hrng;
	double		hi_lrng;
	char		Hzen_kyoyou;
	double		lo_hrng;
	double		lo_lrng;
	char		Lzen_kyoyou;
	double		et_hrng;
	double		et_lrng;
	char		Ezen_kyoyou;
	double		db_hrng;
	double		db_lrng;
	int 		h_hit;
	int 		l_hit;
	int 		e_hit;
	char		zen_kyoyou;
	char		sKisya[128];
	int 		iKisya;
	char		errMsg[1024] = {0,};

	int		errflg_cnt;

	if (pKekka->knssu == 1) {
		/* 再検でない */
		return 0;
	}

	if (cntKmkmst == 0) {
		flg = 0;	/* マスタが無いので、初回優先に設定 */
	}
	else {
		if (pKmkmst->sgchkflg == '2') {
			flg = 1;
		}
		else {
			flg = 0;
		}
	}

	memcpy(&sKekka, pKekka, sizeof(Kekka) );
	/***
	 ***	照合チェックは結果優先フラグが1:優先結果のデータと比較する
	 ***/
	/* 検査回数をデクリメント */
	sKekka.knssu -= 1;
	ret = ZdbKekkaSelectKKAYSN(&sKekka, &spKekka, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKKAYSN",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* 検査フラグ */
		return(RET_STOP);

	}
	if (ret == HRC_SQL_NOT_FOUND || spKekka->knsflg == 'H') {
		/* 優先結果が保留だった場合、照合を掛けてはいけない。 */
		/* 照合を行わず、取り込む結果を検査中('A')とする */
		pKekka->kkajkcd 		= '1';				/* 結果状況コード */
		pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
		pKekka->siyflg			= ' ';				/* 採用フラグ */
		pKekka->knsflg			= 'A';				/* 検査フラグ */
		/* この状態が未報告まで気づかれないと言うトラブルを避けるため、 */
		/* 予備フラグ１に"2"をセットする。 */
		/* →　検査中かつ、予備フラグ１に"2"は照合ＮＧ画面行き条件 */
		pKekka->yobiflg01		= '2';				/* 予備フラグ１ */
		return 0;
	}
	/* 優先結果が既に報告済みだった場合、検査フラグを"M"にする */
	if(spKekka->knsflg == 'E'){
		pKekka->kkajkcd 		= '1';				/* 結果状況コード */
		pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
		pKekka->siyflg			= ' ';				/* 採用フラグ */
		pKekka->knsflg			= 'M';				/* 検査フラグ */
		return 0;
	}

	/* 前回結果のtobiflg02が'1'の場合＆前回、今回のrawdata両方に値が入っている場合 */
	if (spKekka->tobiflg02 == '1' && chkRawdata(spKekka->rawdata, pKekka->rawdata)) {
		ret = ZdbXbarmJkflgUpdateZenkai(spKekka, '1'); /* 前回プロットNOのXBARM確定フラグを'1':確定済へ更新 */
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
            sprintf(errMsg,"SQL CODE:%d ZdbXbarmJkflgUpdateZenkai",ret);
            if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
                return(RET_CONTINUITY);
            }
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
            return(RET_STOP);
        			
		}
		ZbmlFree(spKekka);
		return 0;
	}

	iKisya = 0;
	memset(sKisya, 0, sizeof(sKisya));
	trim(sKisya, pKekka->jisksbr);
	if( sKisya[0] == '\0' ) {
		iKisya = 1;
	} else {
		if( (pKekka->jisksbr[0] == 'L') || (pKekka->jisksbr[0] == 'B') ) {
			memcpy(sKisya, &pKekka->jisksbr[1], 14);
			iKisya = atoi(sKisya);
		}
	}
	char	sChk[10], sChk1[10];
	memset(sChk, 0, sizeof(sChk));
	memset(sChk1, 0, sizeof(sChk1));
	trim(sChk, spKekka->nbdolbl);
	trim(sChk1, spKekka->ykdolbl);
	if( (sChk[0] != '\0') && (sChk1[0] != '\0') ) {
		*iKesseiflg = 0;
	}
	/* 初回、再検結果のどちらかにブランクデータが存在したらＮＧとする */
	if( (iKisya != 1) || (pKenorder->ksktkbn == 'K') || (pKenorder->ksktkbn == 'T')
	  || !chkRawdata( spKekka->rawdata, pKekka->rawdata ) ) {
		/* 再検オーダー・追加再検オーダーのときは照合NGにする。 */
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* 検査フラグ */
		spKekka->syougoflg = '2';
		spKekka->knsflg = 'A';				/* 検査フラグ */
		/* ADD E.Osada 照合NGの場合は予備フラグ０１を'2'にする */
		pKekka->yobiflg01 = '2';
		spKekka->yobiflg01 = '2';
		if (flg == 1) { 					/* 再検優先 */
			pKekka->kkajkcd 		= '3';				/* 結果状況コード */
			pKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
			pKekka->siyflg			= '1';				/* 採用フラグ */
			spKekka->kkajkcd		= '1';				/* 結果状況コード */
			spKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
			spKekka->siyflg 		= ' ';				/* 採用フラグ */
		}
		else {								/* 初回優先 */
			pKekka->kkajkcd 		= '1';				/* 結果状況コード */
			pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
			pKekka->siyflg			= ' ';				/* 採用フラグ */
			spKekka->kkajkcd		= '3';				/* 結果状況コード */
			spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
			spKekka->siyflg 		= '1';				/* 採用フラグ */
		}
		ret = ZdbKekkaUpdate(spKekka);
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			return(RET_STOP);

		}
		ZbmlFree(spKekka);
		return 0;
	}

	/* 前回結果の再検フラグで相関・分画・１００％のいずれかがＮＧだったら照合ＮＧとする */
	if ( (spKekka->soukn1flg == '2') || (spKekka->bunkkuflg == '2') ||
		 (spKekka->per100flg == '2') || (spKekka->soukn2flg == '2') ) {
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* 検査フラグ */
		spKekka->syougoflg = '2';
		spKekka->knsflg = 'A';				/* 検査フラグ */
		pKekka->yobiflg01 = '2';
		spKekka->yobiflg01 = '2';
		if (flg == 1) { 					/* 再検優先 */
			pKekka->kkajkcd 		= '3';				/* 結果状況コード */
			pKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
			pKekka->siyflg			= '1';				/* 採用フラグ */
			spKekka->kkajkcd		= '1';				/* 結果状況コード */
			spKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
			spKekka->siyflg 		= ' ';				/* 採用フラグ */
		}
		else {								/* 初回優先 */
			pKekka->kkajkcd 		= '1';				/* 結果状況コード */
			pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
			pKekka->siyflg			= ' ';				/* 採用フラグ */
			spKekka->kkajkcd		= '3';				/* 結果状況コード */
			spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
			spKekka->siyflg 		= '1';				/* 採用フラグ */
		}
		ret = ZdbKekkaUpdate(spKekka);
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			return(RET_STOP);
		}
		ZbmlFree(spKekka);
		return 0;
	}

	/* 再検結果に分析機エラーが存在した場合の処理を追加 */
	if( (strcmp(pKekka->bskerrsts, " ") != 0) && (strcmp(pKekka->bskerrsts, "0") != 0) ){
		/* エラーコード 3,47,72 の場合は照合ＮＧとする。再検には回さず、画面で用手でチェック */
		for(errflg_cnt=0; errflg_cnt < errsts_ng_cnt ;errflg_cnt++){
			if(strcmp(pKekka->bskerrsts, errsts_ng[errflg_cnt]) == 0){
				pKekka->syougoflg = '2';
				pKekka->knsflg  = 'A';              /* 検査フラグ */
				spKekka->syougoflg = '2';
				spKekka->knsflg = 'A';              /* 検査フラグ */
				pKekka->yobiflg01 = '2';
				spKekka->yobiflg01 = '2';

				if (flg == 1) {                     /* 再検優先 */
					pKekka->kkajkcd         = '3';              /* 結果状況コード */
					pKekka->kkaysnflg       = '1';              /* 結果優先フラグ */
					pKekka->siyflg          = '1';              /* 採用フラグ */
					spKekka->kkajkcd        = '1';              /* 結果状況コード */
					spKekka->kkaysnflg      = ' ';              /* 結果優先フラグ */
					spKekka->siyflg         = ' ';              /* 採用フラグ */
				}
				else {                              /* 初回優先 */
					pKekka->kkajkcd         = '1';              /* 結果状況コード */
					pKekka->kkaysnflg       = ' ';              /* 結果優先フラグ */
					pKekka->siyflg          = ' ';              /* 採用フラグ */
					spKekka->kkajkcd        = '3';              /* 結果状況コード */
					spKekka->kkaysnflg      = '1';              /* 結果優先フラグ */
					spKekka->siyflg         = '1';              /* 採用フラグ */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);
				}
				ZbmlFree(spKekka);
				return 0;
			}
		}
		
		/* 上記以外で指定されたエラーコードに関しては、照合エラーにして、用手再検に回す */
		for(errflg_cnt=0; errflg_cnt < errsts_sai_cnt ;errflg_cnt++){
			if(strcmp(pKekka->bskerrsts, errsts_sai[errflg_cnt]) == 0) {
				pKekka->syougoflg = '2';
				pKekka->knsflg  = 'R';              /* 検査フラグ */
				spKekka->syougoflg = '2';
				spKekka->knsflg = 'R';              /* 検査フラグ */

				if (flg == 1) {                     /* 再検優先 */
					pKekka->kkajkcd         = '3';              /* 結果状況コード */
					pKekka->kkaysnflg       = '1';              /* 結果優先フラグ */
					pKekka->siyflg          = '1';              /* 採用フラグ */
					spKekka->kkajkcd        = '1';              /* 結果状況コード */
					spKekka->kkaysnflg      = ' ';              /* 結果優先フラグ */
					spKekka->siyflg         = ' ';              /* 採用フラグ */
				}
				else {                              /* 初回優先 */
					pKekka->kkajkcd         = '1';              /* 結果状況コード */
					pKekka->kkaysnflg       = ' ';              /* 結果優先フラグ */
					pKekka->siyflg          = ' ';              /* 採用フラグ */
					spKekka->kkajkcd        = '3';              /* 結果状況コード */
					spKekka->kkaysnflg      = '1';              /* 結果優先フラグ */
					spKekka->siyflg         = '1';              /* 採用フラグ */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);
				}
				ZbmlFree(spKekka);
				return 0;
			}
		}
    }

	/* 前回値の検査値を取得する。 */
	rawDataZen = atof(spKekka->rawdata);

	memset(&sRngchkmst, 0, sizeof(Rngchkmst));
	sRngchkmst.hnikbn = SYOGO_CHK;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pKenorder->zrcd, "001", 3) == 0) || (strncmp(pKenorder->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pKenorder->sbtkbn;
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
		ZbmlFree(spKekka);
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* 検査フラグ */
		return(RET_STOP);

	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}

			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			pKekka->syougoflg = '2';
			pKekka->knsflg	= 'A';				/* 検査フラグ */
			return(RET_STOP);
		}
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pKenorder->sbtkbn;
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			pKekka->syougoflg = '2';
			pKekka->knsflg	= 'A';				/* 検査フラグ */
			return(RET_STOP);

		}
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			pKekka->syougoflg = '2';
			pKekka->knsflg  = 'A';              /* 検査フラグ */
			return(RET_STOP);

		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		int 	cFlg = 0;
		h_hit = l_hit = e_hit = 0;
		rawData = atof(pKekka->rawdata);
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			switch(pRngchkmst[lCnt].ssa) {
				case '1':
					hi_hrng = atof(pRngchkmst[lCnt].hrng);
					hi_lrng = atof(pRngchkmst[lCnt].lrng);
					Hzen_kyoyou = pRngchkmst[lCnt].zen_kyoyou;
					h_hit =1;
					break;
				case '2':
					lo_hrng = atof(pRngchkmst[lCnt].hrng);
					lo_lrng = atof(pRngchkmst[lCnt].lrng);
					Lzen_kyoyou = pRngchkmst[lCnt].zen_kyoyou;
					l_hit = 1;
					break;
				case '3':
					et_hrng = atof(pRngchkmst[lCnt].hrng);
					et_lrng = atof(pRngchkmst[lCnt].lrng);
					Ezen_kyoyou = pRngchkmst[lCnt].zen_kyoyou;
					e_hit = 1;
					break;
			}
		}
		cFlg = 1;
		if( spKekka->renjicflg == '3' && h_hit ) {
			db_hrng = hi_hrng;
			db_lrng = hi_lrng;
			zen_kyoyou = Hzen_kyoyou;
		} else if( spKekka->renjicflg == '4' && l_hit ) {
			db_hrng = lo_hrng;
			db_lrng = lo_lrng;
			zen_kyoyou = Lzen_kyoyou;
		} else if( spKekka->renjicflg != '3' && spKekka->renjicflg != '4'  &&
					e_hit ) {
			db_hrng = et_hrng;
			db_lrng = et_lrng;
			zen_kyoyou = Ezen_kyoyou;
		} else if( l_hit ) {
			db_hrng = lo_hrng;
			db_lrng = lo_lrng;
			zen_kyoyou = Lzen_kyoyou;
		} else {
			cFlg = 0;
		}
		if( cFlg ) {
			if (zen_kyoyou == '1') { /* % */
				chk = rawData / rawDataZen * 100;
			}
			else if (zen_kyoyou == '2') { /* 差 */
				chk = fabs(rawDataZen - rawData);
			}
			else {
				chk = rawData;
			}
			if( ((rawData >= 0) || (rawDataZen >= 0)) && (db_hrng >= chk) &&
				(chk >= db_lrng) ) {
				pKekka->syougoflg = '1';
				spKekka->syougoflg = '1';
				/* kkacmt1にが既に入っている場合はcmnt2に移行し、"0101"をCMNT1に入れる */
				if( pKekka->renjicflg > '1' ) {
					if( (pKekka->kkacmt1[0] == '\0') || (pKekka->kkacmt1[0] == ' ') ) {
						strncpy(pKekka->kkacmt1, "0101", 4);
					} else {
						if( memcmp(pKekka->kkacmt1, "0101", 4) ) {
							if( (pKekka->kkacmt2[0] == '\0') || (pKekka->kkacmt2[0] == ' ') ) {
								strncpy(pKekka->kkacmt2, "0101", 4);
							}
						}
					}
				}

				if( spKekka->renjicflg > '1' ) {
					if( (spKekka->kkacmt1[0] == '\0') || (spKekka->kkacmt1[0] == ' ') ) {
						strncpy(spKekka->kkacmt1, "0101", 4);
					} else {
						if( memcmp(spKekka->kkacmt1, "0101", 4) ) {
							if( (spKekka->kkacmt2[0] == '\0') || (spKekka->kkacmt2[0] == ' ') ) {
								strncpy(spKekka->kkacmt2, "0101", 4);
							}
						}
					}
				}
				/* 比色がきていない(電解質のみ)場合は 'H' */
				if( *iKesseiflg ) {
					pKekka->knsflg			= 'X';				/* 検査フラグ */
					spKekka->knsflg 		= 'H';				/* 検査フラグ */
				} else {
					pKekka->knsflg			= 'X';				/* 検査フラグ */
					spKekka->knsflg 		= 'X';				/* 検査フラグ */
				}
				if (flg == 1) {								/* 再検優先 */
					pKekka->kkajkcd 		= '3';				/* 結果状況コード */
					pKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
					pKekka->siyflg			= '1';				/* 採用フラグ */
					spKekka->kkajkcd		= '1';				/* 結果状況コード */
					spKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
					spKekka->siyflg 		= ' ';				/* 採用フラグ */
				}
				else {									/* 初回優先 */
					pKekka->kkajkcd 		= '1';				/* 結果状況コード */
					pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
					pKekka->siyflg			= ' ';				/* 採用フラグ */
					spKekka->kkajkcd		= '3';				/* 結果状況コード */
					spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
					spKekka->siyflg 		= '1';				/* 採用フラグ */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);

				}
			}
			else {
				/* 照合NGは再検対象とする */
				pKekka->syougoflg = '2';
				pKekka->knsflg	= 'R';				// 検査フラグ
				spKekka->syougoflg = '2';
				spKekka->knsflg = 'R';				// 検査フラグ
				if (flg == 1) { 					/* 再検優先 */
					pKekka->kkajkcd 		= '3';				/* 結果状況コード */
					pKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
					pKekka->siyflg			= '1';				/* 採用フラグ */
					spKekka->kkajkcd		= '1';				/* 結果状況コード */
					spKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
					spKekka->siyflg 		= ' ';				/* 採用フラグ */
				}
				else {								/* 初回優先 */
					pKekka->kkajkcd 		= '1';				/* 結果状況コード */
					pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
					pKekka->siyflg			= ' ';				/* 採用フラグ */
					spKekka->kkajkcd		= '3';				/* 結果状況コード */
					spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
					spKekka->siyflg 		= '1';				/* 採用フラグ */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);
				}
			}
		}
		if (cFlg == 0) {
			/* レンジなどフラグが設定されていないため、チェックできない。 */
			/* そのため、照合エラーとする。 */
			if (flg == 1) { 					/* 再検優先 */
				pKekka->kkajkcd 		= '3';				/* 結果状況コード */
				pKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
				pKekka->siyflg			= '1';				/* 採用フラグ */
				spKekka->kkajkcd		= '1';				/* 結果状況コード */
				spKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
				spKekka->siyflg 		= ' ';				/* 採用フラグ */
			}
			else {								/* 初回優先 */
				pKekka->kkajkcd 		= '1';				/* 結果状況コード */
				pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
				pKekka->siyflg			= ' ';				/* 採用フラグ */
				spKekka->kkajkcd		= '3';				/* 結果状況コード */
				spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
				spKekka->siyflg 		= '1';				/* 採用フラグ */
			}
			/* CHG E.Osada マスタにない場合はチェック必要ない　正常にする */
			pKekka->syougoflg		= '1';
			spKekka->syougoflg		= '1';
			if( *iKesseiflg ) {
				pKekka->knsflg			= 'X';				/* 検査フラグ */
				spKekka->knsflg 		= 'H';				/* 検査フラグ */
			} else {
				pKekka->knsflg			= 'X';				/* 検査フラグ */
				spKekka->knsflg 		= 'X';				/* 検査フラグ */
			}
			if( pKekka->renjicflg > '1' ) {
				if( (pKekka->kkacmt1[0] == '\0') || (pKekka->kkacmt1[0] == ' ') ) {
					strncpy(pKekka->kkacmt1, "0101", 4);
				} else {
					if( memcmp(pKekka->kkacmt1, "0101", 4) ) {
						if( (pKekka->kkacmt2[0] == '\0') || (pKekka->kkacmt2[0] == ' ') ) {
							strncpy(pKekka->kkacmt2, "0101", 4);
						}
					}
				}
			}
			if( spKekka->renjicflg > '1' ) {
				if( (spKekka->kkacmt1[0] == '\0') || (spKekka->kkacmt1[0] == ' ') ) {
					strncpy(spKekka->kkacmt1, "0101", 4);
				} else {
					if( memcmp(spKekka->kkacmt1, "0101", 4) ) {
						if( (spKekka->kkacmt2[0] == '\0') || (spKekka->kkacmt2[0] == ' ') ) {
							strncpy(spKekka->kkacmt2, "0101", 4);
						}
					}
				}
			}
			ret = ZdbKekkaUpdate(spKekka);
			if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
				sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
				return(RET_STOP);
			}
		}
	} else {
		/* レンジチェックにレコード自体存在しない場合の対応 */
		if (flg == 1) { 					/* 再検優先 */
			pKekka->kkajkcd 		= '3';				/* 結果状況コード */
			pKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
			pKekka->siyflg			= '1';				/* 採用フラグ */
			spKekka->kkajkcd		= '1';				/* 結果状況コード */
			spKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
			spKekka->siyflg 		= ' ';				/* 採用フラグ */
		}
		else {								/* 初回優先 */
			pKekka->kkajkcd 		= '1';				/* 結果状況コード */
			pKekka->kkaysnflg		= ' ';				/* 結果優先フラグ */
			pKekka->siyflg			= ' ';				/* 採用フラグ */
			spKekka->kkajkcd		= '3';				/* 結果状況コード */
			spKekka->kkaysnflg		= '1';				/* 結果優先フラグ */
			spKekka->siyflg 		= '1';				/* 採用フラグ */
		}
		/* マスタにない場合はチェック必要ない　正常にする */
		pKekka->syougoflg		= '1';
		spKekka->syougoflg		= '1';
		if( *iKesseiflg ) {
			pKekka->knsflg			= 'X';				/* 検査フラグ */
			spKekka->knsflg 		= 'H';				/* 検査フラグ */
		} else {
			pKekka->knsflg			= 'X';				/* 検査フラグ */
			spKekka->knsflg 		= 'X';				/* 検査フラグ */
		}
		if( pKekka->renjicflg > '1' ) {
			if( (pKekka->kkacmt1[0] == '\0') || (pKekka->kkacmt1[0] == ' ') ) {
				strncpy(pKekka->kkacmt1, "0101", 4);
			} else {
				if( memcmp(pKekka->kkacmt1, "0101", 4) ) {
					if( (pKekka->kkacmt2[0] == '\0') || (pKekka->kkacmt2[0] == ' ') ) {
						strncpy(pKekka->kkacmt2, "0101", 4);
					}
				}
			}
		}
		if( spKekka->renjicflg > '1' ) {
			if( (spKekka->kkacmt1[0] == '\0') || (spKekka->kkacmt1[0] == ' ') ) {
				strncpy(spKekka->kkacmt1, "0101", 4);
			} else {
				if( memcmp(spKekka->kkacmt1, "0101", 4) ) {
					if( (spKekka->kkacmt2[0] == '\0') || (spKekka->kkacmt2[0] == ' ') ) {
						strncpy(spKekka->kkacmt2, "0101", 4);
					}
				}
			}
		}
		ret = ZdbKekkaUpdate(spKekka);
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			return(RET_STOP);

		}
	}

	ZbmlFree(spKekka);
	ZbmlFree(pRngchkmst);
	return 0;
}
/******************************************************************************/
/*	関 数 名  ：soukanChk() 						*/
/*	機能概要  ：相関チェック(WS間)						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*			 0	正常						*/
/*			-1	異常						*/
/******************************************************************************/
int soukanChk(Kekka *pKekka, Kenorder *pKenorder)
{
	char		calBuff[256];
	Skchkmst	sSkchkmst;
	Skchkmst	*pSkchkmst;
	int 		cnt;
	int 		ret;
	double		rawData;
	Kmkmst		lKmkmst;
	Kmkmst		*plKmkmst;
	int 		iCnt;	/* ループカウンタ */
	int 		setCnt;
	int 		tmpCnt;
	char		tmp[32];
	double		calNum;
	char		errMsg[1024] = {0,};

	char *pszExpandKSNSK = (char *) NULL; /* IF 文展開後の計算式              */
	double dTransferLimit;

	memset(&sSkchkmst, 0, sizeof(sSkchkmst));
	strncpy(sSkchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sSkchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sSkchkmst.sstcd, pKekka->sstcd, 7);
	if((strncmp(pKenorder->zrcd,"001",3)==0)||(strncmp(pKenorder->zrcd,"002",3) == 0)) {
		strncpy(sSkchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sSkchkmst.zaicd, "000 ", 4);
	}
	ret = ZdbSkchkmstSelectKey(&sSkchkmst, &pSkchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbSkchkmstSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
		return (RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sSkchkmst.sstcd, "0000000", 7);
		ret = ZdbSkchkmstSelectKey(&sSkchkmst, &pSkchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbSkchkmstSelectKey",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
			return (RET_STOP);
		}

		if(ret == HRC_SQL_NOT_FOUND){
			pKekka->soukn2flg = '1';
			if( pKekka->soukn1flg == '0' ) {
				pKekka->soukn1flg = '1';
			}
			return(RET_CONTINUITY);
		}
	}


	/* 式中の項目コードを数値に置き換える。 */
	memset(calBuff, 0, sizeof(calBuff));
	for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
		/* 項目コードの始まり'['を検索する。 */
		if (pSkchkmst->soukan[iCnt] = '[') {
			/* 項目値を検索 */
			memset(tmp, 0, sizeof(tmp));
			tmpCnt = 0;
			iCnt++;
			/* 項目コードを転送（終了位置の]かNullまで） */
			while (pSkchkmst->soukan[iCnt] != ']' && pSkchkmst->soukan[iCnt] != '\0') {
				tmp[tmpCnt++] = pSkchkmst->soukan[iCnt++];
			}
			/* 結果情報から指定の項目コードを検索し、置き換える。 */
			memset(&lKmkmst, 0, sizeof(lKmkmst));
			strncpy(lKmkmst.kmkcd, tmp, 7);
			ret = ZdbKmkmstSelectCD(&lKmkmst, &plKmkmst, &cnt);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectCD",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}

				sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
				return (RET_STOP);
			}
			if (ret != HRC_SQL_NOT_FOUND) {
				if (plKmkmst->kmksbt == '3') {
					Soukan		sSoukan;
					Soukan		*pSoukan;
					int 		cntSoukan;

					memset(&sSoukan, 0, sizeof(sSoukan));
					strncpy(sSoukan.utkymd, pKekka->utkymd, 11);
					strncpy(sSoukan.irino, pKekka->irino, 11);
					sSoukan.zssdino = pKekka->zssdino;
					strncpy(sSoukan.knsgrp, pKekka->knsgrp, 16);
					strncpy(sSoukan.kmkcd, pKekka->kmkcd, 7);
					ret = ZdbSoukanSelectKey(&sSoukan, &pSoukan, &cntSoukan);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
						sprintf(errMsg,"SQL CODE:%d ZdbSoukanSelectKey",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
						ZbmlFree(plKmkmst);
						return (RET_STOP);
					}
					if (ret == HRC_SQL_NOT_FOUND) {
						pKekka->soukn2flg = '1';
						if( pKekka->soukn1flg == '0' ) {
							pKekka->soukn1flg = '1';
						}
						ZbmlFree(plKmkmst);
						return 0;
					}
					strncat(calBuff, pSoukan->rawdata, 21);
					setCnt = strlen(calBuff);
					ZbmlFree(pSoukan);
				}
				else {
					/* WS間の相関情報で無いので処理しない */
					pKekka->soukn2flg = '1';
					if( pKekka->soukn1flg == '0' ) {
						pKekka->soukn1flg = '1';
					}
					ZbmlFree(plKmkmst);
					return 0;
				}
				ZbmlFree(plKmkmst);
			}
			else {
				pKekka->soukn2flg = '1';
				if( pKekka->soukn1flg == '0' ) {
					pKekka->soukn1flg = '1';
				}
				return 0;
			}
		}
		else if (KSNSK_SC == (int) pSkchkmst->soukan[iCnt]) {
			/* 身長 */
			/* 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする */
			memcpy((void *) gszTransfer, pKenorder->sc, FLDSIZE_SC);
			gszTransfer[FLDSIZE_SC] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_TJ == (int) pSkchkmst->soukan[iCnt]) {
			/* POWと区別するため、前の文字がOで無いかチェックする。 */
			if (pSkchkmst->soukan[iCnt-1] != 'o' || pSkchkmst->soukan[iCnt-1] != 'O') {
				/* 体重 */
				/* 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする */
				strncpy(gszTransfer, pKenorder->tj, FLDSIZE_TJ);
				gszTransfer[FLDSIZE_TJ] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) pKenorder->tjtni) {
					case _VALUE_TJTNI_KILLOGRAM:
						dTransferLimit = 
								atof(gszTransfer) * (double) 1000.0;
						if ((double) 0.0 < dTransferLimit &&
								(double) 100000.0 > dTransferLimit) {
							sprintf(gszTransfer, "%-lf", dTransferLimit);
							gszTransfer[FLDSIZE_TJ] = (char) '\0';
						}
						else {
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}

					case _VALUE_TJTNI_GRAM:
						break;		/* NOP */
					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (KSNSK_TNTME == (int) pSkchkmst->soukan[iCnt]) {
			/* 蓄尿時間 */
			/* 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする */
			memcpy((void *) gszTransfer, pKenorder->sstme, FLDSIZE_TNTME);
			gszTransfer[FLDSIZE_TNTME] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);

		}
		else if (KSNSK_TNRYO == (int) pSkchkmst->soukan[iCnt]) {
			/* 蓄尿量 */
			/* 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする */
			memcpy((void *) gszTransfer, pKenorder->tnryo, FLDSIZE_TNRYO);
			gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
			}
			else {
				switch ((int) pKenorder->tnryotni) {
				case _VALUE_TNRYO_LITER:
					dTransferLimit = atof(gszTransfer) * (double) 1000.0;
					if ((double) 0.0 < dTransferLimit &&
							(double) 100000.0 > dTransferLimit) {
						sprintf(gszTransfer, "%-lf", dTransferLimit);
						gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
					}
					else {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}

				case _VALUE_TNRYO_MILLILITER:
					break;

				default:
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);

		}

		/* 計算式拡張対応 */
		else if (KSNSK_SBTKBN == (int) pSkchkmst->soukan[iCnt]) {
			/* 性別区分 */
			if (_VALUE_SBTKBN_MALE == (int) pKenorder->sbtkbn ||
					_VALUE_SBTKBN_FEMALE == (int) pKenorder->sbtkbn) {
				strncat(calBuff, &(pKenorder->sbtkbn), sizeof(pKenorder->sbtkbn));
				setCnt = strlen(calBuff);
			}
			else {
				calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
				calBuff[setCnt] = (char) '\0';
				/* 展開不可 */
			}
		}
		else if (KSNSK_AGE == (int) pSkchkmst->soukan[iCnt]) {
			/* 年齢 */
			if (_VALUE_AGEKBN_YEAR != (int) pKenorder->agekbn) {
				calBuff[setCnt++] = (char) '0';
				calBuff[setCnt] = (char) '\0';
				/* 展開不可 */
			}
			else {
				memcpy((void *) gszTransfer, pKenorder->age, FLDSIZE_AGE);
				gszTransfer[FLDSIZE_AGE] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (pSkchkmst->soukan[iCnt] = '\0') {
			break;
		}
		else {
			calBuff[setCnt++] = pSkchkmst->soukan[iCnt];
		}
	}

	/* 計算式に含まれる IF 文の展開 */

	if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
		if ('\0' != (int) *pszExpandKSNSK) {
			strcpy(calBuff, pszExpandKSNSK);
		}
		free((void *) pszExpandKSNSK);
		pszExpandKSNSK = (char *) NULL;
	}


	/* 文字列の計算式を計算する。 */
	calNum = StringCal(calBuff);

	/* 不等号の設定に従い、値を判定する。 */
	rawData = atof(pKekka->knskka1);
	switch (pSkchkmst->krknsgrp[0]) {
	case 0: /* = */
		if (rawData == calNum) {
			ret = 1;
		}
		break;
	case 1: /* != */
		if (rawData != calNum) {
			ret = 1;
		}
		break;
	case 2: /* >= */
		if (rawData >= calNum) {
			ret = 1;
		}
		break;
	case 3: /* <= */
		if (rawData <= calNum) {
			ret = 1;
		}
		break;
	case 4: /* > */
		if (rawData > calNum) {
			ret = 1;
		}
		break;
	case 5: /* < */
		if (rawData < calNum) {
			ret = 1;
		}
		break;
	}

	if (ret != 0) {
		pKekka->soukn2flg = '2';
		if( pKekka->soukn1flg == '0' ) {
			pKekka->soukn1flg = '2';
		}
	}
	else {
		pKekka->soukn2flg = '1';
		if( pKekka->soukn1flg == '0' ) {
			pKekka->soukn1flg = '1';
		}
	}

	ZbmlFree(pSkchkmst);
	return 0;
}
/******************************************************************************/
/*	関 数 名  ：StringCal_sub() 						*/
/*	機能概要  ：指定された演算子と値で四則演算行う				*/
/*	入	  力  ：							*/
/*	 第１引数 ：enzan	:	演算子					*/
/*	 第２引数 ：val1	:	値１					*/
/*	 第３引数 ：val2	:	値２					*/
/*	出	  力  ：							*/
/*	復帰情報  ：double	計算結果					*/
/******************************************************************************/
double StringCal_sub(char enzan,double val1,double val2)
{
	switch ( enzan ) {
	case '+':
		return (val1 + val2);
		break;
	case '-':
		return (val1 - val2);
		break;
	case '/':
		if (val2 == 0.0) {
			return 0;
		}
		return (val1 / val2);
		break;
	case '*':
		return (val1 * val2);
		break;
	}
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：StringCal() 						*/
/*	機能概要  ：渡された文字列の計算式を行う				*/
/*	入	  力  ：							*/
/*	 第１引数 ：CalStr	:	計算文字列				*/
/*	出	  力  ：							*/
/*	復帰情報  ：double	計算結果					*/
/*										*/
/*	注意：	対応する演算子は「+ - / *」が可能である。			*/
/*		それ以外にLOG、LOG10、POWの3つの計算を行う。			*/
/*		計算の優先順位は、四則演算の優先順位に従い*と/が優先される。	*/
/******************************************************************************/
double StringCal(char *CalStr)
{
	char		StacEn;
	double		StacNum;
	int 		flg;
	int 		loopCnt, strCnt;
	double		ret;
	char		cStacNum[32];
	char		cStacNum2[32];
	char		cChk[16];
	int 		i, c;
	double		StacRet[10];
	char		StacEnc[10];
	char		StacFlg[10];
	int 		StacCnt;

	ret = 0.0;
	StacEn = '+';
	flg = FALSE;
	strCnt = 0;
	StacCnt = 0;
	for(loopCnt = 0; loopCnt < strlen(CalStr); loopCnt ++) {
		switch (CalStr[loopCnt]) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			/* 数値の時 */
			break;
		case '+': case '-': case '/': case '*':
			/* 演算子の時 */
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			if ((StacEn == '+' || StacEn == '-') && (CalStr[loopCnt] == '*' || CalStr[loopCnt] == '/')) {
				StacFlg[StacCnt] = StacEn;
				StacRet[StacCnt] = ret;
				StacEnc[StacCnt] = StacEn;
				StacCnt += 1;

				flg = FALSE;
				ret = StacNum;
				StacEn = CalStr[loopCnt];
				strCnt = loopCnt + 1;
			}
			else if ((StacEn == '*' || StacEn == '/') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else if ((StacCnt > 0) && (StacEnc[StacCnt-1] == '+' || StacEnc[StacCnt-1] == '-') &&
					 (StacFlg[StacCnt-1] != '(') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEnc[StacCnt-1], StacRet[StacCnt-1], ret);
				StacCnt -= 1;
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}

			strCnt = loopCnt + 1;
			break;
		case 'L': case 'l':
			/* LOG及びLOG10の時 */
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk , "LOG10") == 0) {
				for (c = 0, i = loopCnt + 6; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = log10(atof(cStacNum));
				flg = TRUE;
				loopCnt += i;
			}
			else if (strcmp(cChk , "LOG") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = atof(cStacNum);
				StacNum = log(StacNum);
				flg = TRUE;
				loopCnt += i;
			}
			break;
		case 'P': case 'p':
			/* POWの時 */
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk, "POW") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				for (c = 0, i += 1; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum2[c] = CalStr[i];
				}
				cStacNum2[c] = '\0';
				StacNum = pow(atof(cStacNum), atof(cStacNum2));
				flg = TRUE;
				loopCnt = i;
			}
			break;
		case '(':
			StacFlg[StacCnt] = '(';
			StacRet[StacCnt] = ret;
			StacEnc[StacCnt] = StacEn;
			StacCnt++;
			ret = 0.0;
			StacEn = '+';
			strCnt = loopCnt + 1;
			break;
		case ')':
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			StacNum = StringCal_sub(StacEn, ret, StacNum);
			flg = TRUE;

			StacCnt--;
			StacEn = StacEnc[StacCnt];
			ret = StacRet[StacCnt];
			strCnt = loopCnt + 1;
			break;
		}
	}
	if (flg == FALSE) {
		for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
			cStacNum[c] = CalStr[i];
		}
		cStacNum[c] = '\0';
		StacNum = atof(cStacNum);
	}
	ret = StringCal_sub(StacEn, ret, StacNum);
	if (StacCnt > 0) {
		while (StacCnt > 0) {
			StacCnt -= 1;
			StacEn = StacEnc[StacCnt];
			StacNum = StacRet[StacCnt];
			ret = StringCal_sub(StacEn, StacNum, ret);
		}
	}
	return ret;
}

void LogFileOut(char * msg)
{
	FILE *fp;

	struct tm* tm;
	struct timeval tv;
	char cWrk[16];
	gettimeofday( &tv, NULL );
	sprintf( cWrk, "%06ld", tv.tv_usec );
	tm = localtime(&tv.tv_sec);
	sprintf(gFileMsgBuff, "%04d/%02d/%02d %02d:%02d:%02d.%c%c%c %s",
					tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
					tm->tm_hour, tm->tm_min, tm->tm_sec,
					cWrk[0], cWrk[1], cWrk[2],
					msg);

	if (gLogFile[0] == 0) return;

	fp = fopen(gLogFile,"a");
	if( fp == NULL ) {
		return;
	}
	fprintf(fp,"%s\n", gFileMsgBuff);
	fclose(fp);
}
int kanrenChk(Kekka *pKekka, int iTcnt, int iCrcnt)
{
	int i, iCnt, iKcnt, iKhit;
	Kekka *pKkaYkrn = NULL;
	Kekka wKekka;
	char		errMsg[1024] = {0,};
	int ret;

	for( iCnt=0; iCnt < gKrkCnt ;++iCnt ) {
		iKhit = 0;
		/* 1.自分の関連項目コードを取得 */
		if( memcmp((gKrkmkmst+iCnt)->kmkcd, pKekka[iCrcnt].kmkcd, 7) )
			continue;

		/* 2.関連先項目を検索 */
		for( i=0; i < iTcnt ;++i ) {
			if( i == iCrcnt ) {
				/* 自分をヒット 読み飛ばし */
				continue;
			}
			if( !memcmp(pKekka[i].kmkcd, (gKrkmkmst+iCnt)->krkmkcd, 7) ) {
				/* 関連項目発見 */
				/* 相手＆自分の関連フラグを'2' */
				pKekka[i].kanrenflg = pKekka[iCrcnt].kanrenflg = '2';
				/* 自分の検査フラグが'R'だったら相手も'R'にする */
				if( pKekka[iCrcnt].knsflg == 'R' ) {
					pKekka[i].knsflg = 'R';
				}
				/* 自分が'A'で相手が'R'でなければ相手を'A'にする */
				if( pKekka[iCrcnt].knsflg == 'A' ) {
					if( pKekka[i].knsflg != 'R' ) {
						pKekka[i].knsflg = 'A';
					}
				}
				iKhit = 1;
			}
			/* 2.関連項目UPDATE */
			if( iKhit ) {
				/* 関連先の優先結果の検査フラグも変更する */
				/* 1. SELECT */
				if( pKkaYkrn != NULL ) {
					ZbmlFree(pKkaYkrn);
					pKkaYkrn = NULL;
				}
				iKcnt = 0;
				/* 検査回数デクリメント */
				memset(&wKekka, 0, sizeof(Kekka));
				memcpy(&wKekka, &pKekka[i], sizeof(Kekka));
				wKekka.knssu -= 1;
				if( (ret=ZdbKekkaSelectKKAYSN(&wKekka, &pKkaYkrn, &iKcnt)) < 0 ) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKKAYSN",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "kanrenChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						ZbmlFree(pKkaYkrn);
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "kanrenChk()", errMsg ) ;
					ZbmlFree(pKkaYkrn);
					return (RET_STOP);
				}
				if( iKcnt )
				{
					/* 2.検査ＦＬＧセット */
					pKkaYkrn->knsflg = pKekka[i].knsflg;
					/* CHG 2006/08/05 Nagata */
					/* 	関連エラーの引継ぎを、優先の回数に対して行わない。*/
					/* 	（照合で行った関連を前の回数に反映させない） */
					/* 	ただし、検査フラグの反映は行う。 */

					/* 3.Update */
					if( ZdbKekkaUpdate(pKkaYkrn) < 0 ) {
						sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING, __FILE__, "kanrenChkYsn",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							ZbmlFree(pKkaYkrn);
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "kanrenChk()", errMsg ) ;
						ZbmlFree(pKkaYkrn);
						return (RET_STOP);
					}
				}
			}
		}
	}
	return( 0 );
}
/*----------------------------------------------------------------------------*/
/* 照合ＯＫ時に関連項目の優先結果の検査フラグを更新する                       */
/* 条件：                                                                     */
/*		1)計算項目                                                            */
/*		2)検査フラグが 'A'                                                    */
/*		3)エラーフラグ '連' のみ(kanrenflg が '2'で、そのほかのフラグ'2'以外) */
/*----------------------------------------------------------------------------*/
int kanrenChkYsn(Kekka *pKekka)
{
	int iCnt;
	Kekka *pKkaYkrn = NULL;
	Kekka wKekka;
	int 		ret;
	char		errMsg[1024] = {0,};

	for( iCnt=0; iCnt < gKrkCnt ;++iCnt ) {
		/* 1.自分の関連項目コードを取得 */
		if( memcmp((gKrkmkmst+iCnt)->kmkcd, pKekka->kmkcd, 7) ) continue;

		/* 2.関連先の優先結果更新 */
		memset(&wKekka, 0, sizeof(Kekka));
		memcpy(&wKekka, pKekka, sizeof(Kekka));
		wKekka.knssu -= 1;
		memcpy(wKekka.kmkcd, (gKrkmkmst+iCnt)->krkmkcd, 7);
		/* Update */
		ret = updKkaYsn( &wKekka );
		if( ret < 0 ) {
			sprintf(errMsg,"SQL CODE:%d updKkaYsn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "kanrenChkYsn",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				ZbmlFree(pKkaYkrn);
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "kanrenChkYsn()", errMsg) ;
			ZbmlFree(pKkaYkrn);
			return (RET_STOP);

		}
	}
	return( 0 );
}

int GetKrkmkmst()
{
	char		errMsg[1024] = {0,};
	int 		ret;

	gKrkCnt = 0;
	ret=ZdbKrkmkmstSelectAll(&gKrkmkmst, &gKrkCnt);
	if(ret<0) {
		sprintf(errMsg,"SQL CODE:%d ZdbKrkmkmstSelectAll",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "GetKrkmkmst",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "GetKrkmkmst()", errMsg ) ;
		return(RET_STOP);
	}
	if(ret == HRC_SQL_NOT_FOUND){
		sFncSyslog ( LOG_ERR, "GetKrkmkmst()", errMsg ) ;
		return(RET_STOP);
	}

	return 0;
}

int getOdrLast(Kekka *pKekka, Kenorder *p_Order)
{
	long		lRet;
	Kenorder	sKenorder;
	Kenorder	*pKenorder = NULL;
	int 		orderCnt;
	char		errMsg[1024] = {0,};

	/* 現ＫＥＹのオーダー情報を取得 */
	memset(&sKenorder, 0, sizeof(sKenorder));
	memcpy(sKenorder.knskisymd, pKekka->knskisymd, sizeof(pKekka->knskisymd));
	memcpy(sKenorder.sriymd, pKekka->sriymd, sizeof(pKekka->sriymd));
	memcpy(sKenorder.kntno, pKekka->kntno, sizeof(pKekka->kntno));
	memcpy(sKenorder.knsgrp, pKekka->knsgrp, sizeof(pKekka->knsgrp));
	memcpy(sKenorder.kmkcd, pKekka->kmkcd, sizeof(pKekka->kmkcd));
	sKenorder.knssu = pKekka->knssu;
	sKenorder.knssueda = pKekka->knssueda;

	lRet = ZdbKenorderSelectKey(&sKenorder, &pKenorder, &orderCnt);
	if ((lRet != HRC_SQL_NORMAL) && (lRet != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%ld ZdbKenorderSelectKey",lRet);
		if(lRet == SQL_ERR_DUPLICATION || lRet == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "getOdrLast",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "getOdrLast()", errMsg ) ;
		return(RET_STOP);
	}
	if (orderCnt == 0) {
		/* 存在しない */
		return 0;
	} else {
		/* 存在する */
		if( pKenorder != NULL ) {
			memcpy(p_Order, pKenorder, sizeof(Kenorder));
			ZbmlFree(pKenorder);
		}
		return 1;
	}
}

/* 照合チェック(rawdataがブランクの場合NG) */
/*	 引数1 aRawdata1 検査回数1回目データ */
/*		 2 aRawdata2 検査回数2回目データ */
/*	 戻値  TRUE   OK */
/*		   FALSE  NG */
/* 初回、再検、どちらかのrawデータが、マイナスだったら照合NGとする */
static int chkRawdata( char * aRawdata1, char * aRawdata2 )
{
	char	cRawBuf[256] ;

	/* 初回データ */
	/* rawデータがブランク */
	trim( cRawBuf, aRawdata1 );
	if	( cRawBuf[0] == '\0' || cRawBuf[0] == '/' ) {
		return FALSE;
	}
	/* rawデータがマイナス */
	if( atof(cRawBuf) < 0.0 ){
		return FALSE;
	}

	/* 再検データ */
	/* rawデータがブランク */
	trim( cRawBuf, aRawdata2 );
	if	( cRawBuf[0] == '\0' || cRawBuf[0] == '/' ) {
		return FALSE;
	}

	/* rawデータがマイナス */
	if( atof(cRawBuf) < 0.0 ){
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************/
/*	関 数 名  ：getKekkaData()						*/
/*	機能概要  ：結果ファイル分割、設定					*/
/*	入	  力  ：							*/
/*	 第１引数 ：buff	:	ファイルレコード(CSV)			*/
/*	 第２引数 ：pKekka	:	結果情報構造体配列			*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/******************************************************************************/
int getKekkaData(char * buff, Kekka *pKekka)
{
	char		** pFld;
	int 		cnt;
	int 		offset;
	
	char		cJisksbr[16];
	char		cRawdata[21];

	pFld = malloc(sizeof(char *)*200);
	/* カンマ区切りのレコードを分割し、DBレコードの構造体に設定する。 */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 118) {
		/* フィールド数が一致しない */
		sFncSyslog ( LOG_ERR, "getKekkaData()", "Kekka CSV File Field Not Count." ) ;
		return -1;
	}

	/* 各フィールドを格納する。 */
	strncpy( pKekka->knskisymd, pFld[0], sizeof( pKekka->knskisymd )-1);	/* 検査開始日 */
	strncpy( pKekka->sriymd, pFld[1], sizeof( pKekka->sriymd )-1);
	strncpy( pKekka->kntno, pFld[2], sizeof( pKekka->kntno )-1);
	pKekka->kntketflg = pFld[3][0];
	strncpy( pKekka->knsgrp, pFld[4], sizeof( pKekka->knsgrp )-1);
	strncpy( pKekka->kmkcd, pFld[5], sizeof( pKekka->kmkcd )-1);		/* 項目コード */
	pKekka->knssu = atoi(pFld[6]);						/* 検査数 */
	pKekka->knssueda = atoi(pFld[7]);					/* 検査数枝 */
	pKekka->irihsmkbn = pFld[8][0];
	pKekka->irikbn = pFld[9][0];
	pKekka->ksktkbn = pFld[10][0];
	strncpy( pKekka->utkymd, pFld[11], sizeof( pKekka->utkymd )-1);
	strncpy( pKekka->irino, pFld[12], sizeof( pKekka->irino )-1);
	pKekka->iriketflg = pFld[13][0];
	pKekka->zssdino = atoi(pFld[14]);
	strncpy( pKekka->sstcd, pFld[15], sizeof( pKekka->sstcd )-1);
	strncpy( pKekka->trid, pFld[16], sizeof( pKekka->trid )-1);
	pKekka->trpos = atoi(pFld[17]);
	strncpy( pKekka->asyrckid, pFld[18], sizeof( pKekka->asyrckid )-1); 	/* ラックID */
	pKekka->asyrckpos = atoi(pFld[19]); 					/* ポジション */
	strncpy( pKekka->oyakmkcd, pFld[20], sizeof( pKekka->oyakmkcd )-1);
	strncpy( pKekka->seccd, pFld[21], sizeof( pKekka->seccd )-1);
	pKekka->bkfkkbn = pFld[22][0];
	strncpy( pKekka->smpcd, pFld[23], sizeof( pKekka->smpcd )-1);
	strncpy( pKekka->bskkbn, pFld[24], sizeof( pKekka->bskkbn )-1);
	strncpy( pKekka->bsklne, pFld[25], sizeof( pKekka->bsklne )-1);
	strncpy( pKekka->bskgok, pFld[26], sizeof( pKekka->bskgok )-1);
	pKekka->bskseq = atoi(pFld[27]);
	strncpy( pKekka->bskerrsts, pFld[28], sizeof( pKekka->bskerrsts )-1);
	strncpy( pKekka->sktdh, pFld[29], sizeof( pKekka->sktdh )-1);
	strncpy( pKekka->nbkmkcd, pFld[30], sizeof( pKekka->nbkmkcd )-1);
	pKekka->tstrflg = pFld[31][0];
	strncpy( pKekka->zrcd, pFld[32], sizeof( pKekka->zrcd )-1);
	strncpy( pKekka->ysnlbl, pFld[33], sizeof( pKekka->ysnlbl )-1);
	strncpy( pKekka->kjno, pFld[34], sizeof( pKekka->kjno )-1);
	pKekka->fkhkknohjkbn = pFld[35][0];
	strncpy( pKekka->tbkjno, pFld[36], sizeof( pKekka->tbkjno )-1);
	pKekka->tbkjflg = pFld[37][0];
	strncpy( pKekka->htkfkhms, pFld[38], sizeof( pKekka->htkfkhms )-1);
	pKekka->skflg = pFld[39][0];
	strncpy( pKekka->tskflg, pFld[40], sizeof( pKekka->tskflg )-1);
	strncpy( pKekka->tktflg, pFld[41], sizeof( pKekka->tktflg )-1);
	/* セットする希釈倍率をＤＢ登録・表示向けに変換する */
	memset( cJisksbr, '\0', sizeof ( cJisksbr ) );
	trim ( cJisksbr, pFld[42] );
	if( strcmp( cJisksbr, KskbrB10CD ) == 0 ){
		memset( cJisksbr, ' ', sizeof ( cJisksbr ) - 1 );
		strncpy( cJisksbr, KskbrB10HY , strlen( KskbrB10HY ) );
	} else if ( strcmp( cJisksbr, KskbrB2CD ) == 0 ) {
		memset( cJisksbr, ' ', sizeof ( cJisksbr ) - 1 );
		strncpy( cJisksbr, KskbrB2HY , strlen( KskbrB2HY ) );
	} else {
		memset( cJisksbr, ' ', sizeof ( cJisksbr ) - 1 );
	}
	strncpy( pKekka->jisksbr, cJisksbr, sizeof( pKekka->jisksbr )-1);
	pKekka->kkflg = pFld[43][0];
	pKekka->kkiriflg = pFld[44][0];
	pKekka->kkirilotno = atoi(pFld[45]);
	pKekka->hsykflg = pFld[46][0];
	pKekka->hskflg = pFld[47][0];
	pKekka->hhkkflg = pFld[48][0];
	/* 結果値が ? の場合は / に置き換えて、BM8060 の時と同じ動作をさせる。*/
	memset( cRawdata, '\0', sizeof ( cRawdata ) );
	trim ( cRawdata, pFld[49] );
	if( cRawdata[0] == '?' ){
		strncpy( pKekka->rawdata, "////////", sizeof( pKekka->rawdata )-1);
	} else {
		/* RAWDATA を左詰めで登録する */
		strncpy( pKekka->rawdata, pFld[49], sizeof( pKekka->rawdata )-1);
	}
	strncpy( pKekka->knskka1, pFld[50], sizeof( pKekka->knskka1 )-1);
	strncpy( pKekka->knskka2, pFld[51], sizeof( pKekka->knskka2 )-1);
	strncpy( pKekka->knskka2kbn, pFld[52], sizeof( pKekka->knskka2kbn )-1);
	strncpy( pKekka->kkahskcd, pFld[53], sizeof( pKekka->kkahskcd )-1);
	strncpy( pKekka->hjkka, pFld[54], sizeof( pKekka->hjkka )-1);
	strncpy( pKekka->sdi, pFld[55], sizeof( pKekka->sdi )-1);
	strncpy( pKekka->kkacmt1, pFld[56], sizeof( pKekka->kkacmt1 )-1);
	strncpy( pKekka->kkacmt2, pFld[57], sizeof( pKekka->kkacmt2 )-1);
	pKekka->kkajkcd = pFld[58][0];
	pKekka->pncrgflg = pFld[59][0];
	pKekka->knspncrgflg = pFld[60][0];
	pKekka->kkaksflg = pFld[61][0];
	pKekka->kkassflg = pFld[62][0];
	pKekka->ijkbnm = pFld[63][0];
	pKekka->ijkbnf = pFld[64][0];
	pKekka->ijkbnn = pFld[65][0];
	pKekka->tbijkbnm = pFld[66][0];
	pKekka->tbijkbnf = pFld[67][0];
	pKekka->tbijkbnn = pFld[68][0];
	strncpy( pKekka->nbdolbl, pFld[69], sizeof( pKekka->nbdolbl )-1);	/*乳び */
	strncpy( pKekka->nbdoerr, pFld[70], sizeof( pKekka->nbdoerr )-1);
	strncpy( pKekka->ykdolbl, pFld[71], sizeof( pKekka->ykdolbl )-1);	/*溶血 */
	strncpy( pKekka->ykdoerr, pFld[72], sizeof( pKekka->ykdoerr )-1);
	strncpy( pKekka->etclbl, pFld[73], sizeof( pKekka->etclbl )-1); 	/* 黄疸 */
	strncpy( pKekka->etcerr, pFld[74], sizeof( pKekka->etcerr )-1);
	pKekka->ctrlno = atoi(pFld[75]);
	pKekka->knsseq = atoi(pFld[76]);
	pKekka->bthno = atoi(pFld[77]);
	pKekka->pltno = atoi(pFld[78]);
	pKekka->pltseq = atoi(pFld[79]);
	strncpy( pKekka->dtnrtts, pFld[80], sizeof( pKekka->dtnrtts )-1);

	strncpy( pKekka->dtnrdh, pFld[81], sizeof( pKekka->dtnrdh )-1);
	strncpy( pKekka->knskrdh, pFld[82], sizeof( pKekka->knskrdh )-1);
	strncpy( pKekka->hkkdh, pFld[83], sizeof( pKekka->hkkdh )-1);
	strncpy( pKekka->hkkkbdh, pFld[84], sizeof( pKekka->hkkkbdh )-1);
	strncpy( pKekka->zkhkkyymd, pFld[85], sizeof( pKekka->zkhkkyymd )-1);

	strncpy( pKekka->zkhkkytme, pFld[86], sizeof( pKekka->zkhkkytme )-1);
	pKekka->frkkaflg = pFld[87][0];
	pKekka->gzbsflg = pFld[88][0];
	pKekka->hsiflg = pFld[89][0];
	pKekka->kkaysnflg = pFld[90][0];
	pKekka->tnyrkflg = pFld[91][0];
	pKekka->siyflg = pFld[92][0];
	pKekka->knsflg = pFld[93][0];
	pKekka->renjicflg = pFld[94][0];
	pKekka->soukn1flg = pFld[95][0];
	pKekka->kanrenflg = pFld[96][0];
	pKekka->bunkkuflg = pFld[97][0];
	pKekka->kesseiflg = pFld[98][0];
	pKekka->rirekiflg = pFld[99][0];
	pKekka->syougoflg = pFld[100][0];
	pKekka->keisanflg = pFld[101][0];
	pKekka->per100flg = pFld[102][0];
	pKekka->tousekflg = pFld[103][0];
	pKekka->kisyakflg = pFld[104][0];
	pKekka->kouseiflg = pFld[105][0];
	pKekka->syoungflg = pFld[106][0];
	pKekka->soukn2flg = pFld[107][0];
	pKekka->fukaptflg = pFld[108][0];
	pKekka->yobiflg01 = pFld[109][0];
	pKekka->tobiflg02 = pFld[110][0];
	pKekka->yobiflg03 = pFld[111][0];
	pKekka->yobiflg04 = pFld[112][0];
	pKekka->yobiflg05 = pFld[113][0];
	strncpy( pKekka->skrycda, pFld[114], sizeof( pKekka->skrycda )-1);
	strncpy( pKekka->skrycdb, pFld[115], sizeof( pKekka->skrycdb )-1);
	strncpy( pKekka->skrycdc, pFld[116], sizeof( pKekka->skrycdc )-1);
	strncpy( pKekka->ksndh, pFld[117], sizeof( pKekka->ksndh )-1);
	strncpy( pKekka->trkdh, "1000-01-01 00:00:01", sizeof( pKekka->trkdh )-1);
	strncpy( pKekka->skkka, pFld[54], sizeof( pKekka->skkka )-1);

	/* メモリ開放 */
	ZbmlFree( pFld );

	return( 0 );
}
/******************************************************************************/
/*	関 数 名  ：NyubiYoketuChk()						*/
/*	機能概要  ：乳び・溶血チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：chkPara :	チェック用パラメータ				*/
/*	 第２引数 ：pKekka	:	結果情報構造体配列			*/
/*	 第３引数 ：KekkaCnt:	結果情報構造体数				*/
/*	 第４引数 ：lCnt	:	処理中位置				*/
/*	 第５引数 ：fNyuYou :	乳び・溶血フラグ				*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					0:再検無し				*/
/*					1:再検あり				*/
/******************************************************************************/
static int	NyubiYoketuChk(Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou)
{
	int 		ret = 0;
	Realchk 	sReal;
	Realchk 	*pReal = NULL;
	int 		Realcnt;
	int 		iKnssu;

	/* 即時チェック情報の取得 */
	memset(&sReal, 0, sizeof(sReal));
	strncpy(sReal.knskisymd, pKekka->knskisymd, 10);
	strncpy(sReal.sriymd, pKekka->sriymd, 10);
	strncpy(sReal.kntno, pKekka->kntno, 13);
	strncpy(sReal.knsgrp, pKekka->knsgrp, 16);
	strncpy(sReal.kmkcd, pKekka->kmkcd, 8);
	sReal.knssu = pKekka->knssu;
	sReal.knssueda = 0;
	char		errMsg[1024] = {0,};

	ret = ZdbRealchkSelectKey(&sReal, &pReal, &Realcnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRealchkSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "NyubiYoketuChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "NyubiYoketuChk()", errMsg ) ;
		return(RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		/* 再検時を考慮し、検査回数が１より大きいときは検査回数をデクリメントし */
		/* もう一度、検索する。 */

		/* 再流しの際にリアルチェックが取得出来ない場合があるため、 */
		/* 見つけるまでデクリメントし続ける（ただし検査回数が１になったら終了） */
		iKnssu = 0;
		for (iKnssu = sReal.knssu - 1 ; iKnssu > 0 ; iKnssu-- ) {
			sReal.knssu = iKnssu;
			ret = ZdbRealchkSelectKey(&sReal, &pReal, &Realcnt);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				sprintf(errMsg,"SQL CODE:%d ZdbRealchkSelectKey",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "NyubiYoketuChk",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "NyubiYoketuChk()", errMsg ) ;
				return(RET_STOP);
			}
			if (ret != HRC_SQL_NOT_FOUND) {
				/* 見つかった */
				break;
			}
		}
		if(ret == HRC_SQL_NOT_FOUND) {
			/* 結局、最後までみつからなかった */
			return 0;
		}
	}
	if (fNyuYou == 0) {
		/* 乳び・溶血でないときは処理しない */
		return 0;
	}

	if (pReal->kesseipara[1] == '1') {
		switch (pReal->kesseipara[0]) {
		case '0':
			break;
		case '1':	/* 乳びのみ */
			if (fNyuYou & 1) {
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					/* 結果コメント１に何もセットされていなかったら0105を入れる */
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
					/* もし、結果コメントに乳びコメントが入っていたらなにもしない */
				}
				else {
					/* 結果コメント１にコメントがセットされていたら、１の内容を２に移し、*/
					/* １に0105を入れる */
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				ret = 1;
			}
			break;
		case '2':	/* 溶血のみ */
			if (fNyuYou & 2) {
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
					/* もし、結果コメントに溶血コメントが入っていたらなにもしない */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				ret = 1;
			}
			break;
		case '3':	/* 乳び優先 */
			if (fNyuYou & 2) {		/* 溶血 */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
					/* もし、結果コメントに溶血コメントが入っていたらなにもしない */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				ret = 1;
			}
			if (fNyuYou & 1) {		/* 乳び */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
					/* もし、結果コメントに乳びコメントが入っていたらなにもしない */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				ret = 1;
			}
			break;
		case '4':	/*  溶血優先 */
			if (fNyuYou & 1) {		/* 乳び */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
					/* もし、結果コメントに乳びコメントが入っていたらなにもしない */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				ret = 1;
			}
			if (fNyuYou & 2) {			/* 溶血 */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
					/* もし、結果コメントに溶血コメントが入っていたらなにもしない */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				ret = 1;
			}
			break;
		}
	}
	ret = 0;
	pKekka[lCnt].kesseiflg = '1';

	if( pReal != NULL ) {
		ZbmlFree(pReal);
		pReal = NULL;
	}

	return ret;
}
static int	NyubiYoketu( Kekka * pKekka, int KekkaCnt)
{
	int 		ret = 0;
	double		rawData;
	char		tmp[22];
	int 		lCnt;

	ret = 0;
	for (lCnt = 0; lCnt < KekkaCnt; lCnt++ ) {
		/* 結果値の値文字列を数値化する */
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
		rawData = atof(tmp);

		/* 乳びチェック */
		if (strncmp( pKekka[lCnt].kmkcd , NyubiCD, 7) == 0 ) {
			ret |= 0x10;
			memset( NyubiKekka, 0, sizeof(NyubiKekka)); 	/* Level */
			trim( NyubiKekka, pKekka[lCnt].rawdata );
			memset( NyubiSTS, 0, sizeof(NyubiSTS)); 		/* Status */
			strncpy( NyubiSTS, pKekka[lCnt].bskerrsts, 2);
			pKekka[lCnt].knsflg = 'H';
			if ( rawData > atof(NyubiCHK) ) {
				ret |= 0x01;
			}
		}
		/* 溶血チェック */
		else if (strncmp( pKekka[lCnt].kmkcd , YoketsuCD, 7) == 0 ) {
			ret |= 0x20;
			memset( YoketsuKekka, 0, sizeof(YoketsuKekka));
			trim( YoketsuKekka, pKekka[lCnt].rawdata );
			memset( YoketsuSTS, 0, sizeof(YoketsuSTS));
			strncpy( YoketsuSTS, pKekka[lCnt].bskerrsts, 2);
			pKekka[lCnt].knsflg = 'H';
			if ( rawData > atof(YoketsuCHK) ) {
				ret |= 0x02;
			}
		}
		/* 黄疸チェック */
		else if (strncmp( pKekka[lCnt].kmkcd , OudanCD, 7) == 0 ) {
			ret |= 0x40;
			memset( OudanKekka, 0, sizeof(OudanKekka));
			trim( OudanKekka, pKekka[lCnt].rawdata );
			memset( OudanSTS, 0, sizeof(OudanSTS));
			strncpy( OudanSTS, pKekka[lCnt].bskerrsts, 2);
			pKekka[lCnt].knsflg = 'H';
		}
	}
	return ret;
}

/* 血清情報処理追加 */
int kesseiCHK(Kekka *pSrc, int iKcnt)
{
	int 		i, KesFlg;
	Kekka		* pKekka, *spKekka = NULL;
	Kekka		KesKekka;
	int 		ret;
	int 		num_spKekka;
	char		sBuff[10];
	char		errMsg[1024] = {0,};

	KesFlg = 0;
	memset(&KesKekka, 0, sizeof(Kekka));
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if( i == 0 )
			memcpy(&KesKekka, pKekka, sizeof(Kekka));

		if( strncmp( pKekka->kmkcd, NyubiCD,   7 ) == 0 ) {
			if( KesFlg == 0 ) {
				KesFlg = 1;
			}
			/* 乳びエラーステータスの取得位置を分析機エラーに変更 */
			memcpy(KesKekka.nbdoerr, pKekka->bskerrsts, 2);
			/* CHG E.Osada 2006-09-16 */
			memset(sBuff, 0, sizeof(sBuff));
			trim(sBuff, pKekka->rawdata);
			if( strlen(sBuff) > 2 ) {
				memcpy(KesKekka.nbdolbl, "99", 2);
			} else {
				memcpy(KesKekka.nbdolbl, sBuff, 2);
			}
		}
		if( strncmp( pKekka->kmkcd, YoketsuCD, 7 ) == 0 ) {
			if( KesFlg == 0 ) {
				KesFlg = 1;
			}
			/* エラーステータスの取得位置を分析機エラーに変更 */
			memcpy(KesKekka.ykdoerr, pKekka->bskerrsts, 2);
			memset(sBuff, 0, sizeof(sBuff));
			trim(sBuff, pKekka->rawdata);
			if( strlen(sBuff) > 2 ) {
				memcpy(KesKekka.ykdolbl, "99", 2);
			} else {
				memcpy(KesKekka.ykdolbl, sBuff, 2);
			}
		}
		if( strncmp( pKekka->kmkcd, OudanCD, 7 ) == 0 ) {
			if( KesFlg == 0 ) {
				KesFlg = 1;
			}
			/* UPD 2006-09-05 Nagata */
			/* 乳びエラーステータスの取得位置を分析機エラーに変更 */
			memcpy(KesKekka.etcerr, pKekka->bskerrsts, 2);
			/* CHG E.Osada 2006-09-16 */
			memset(sBuff, 0, sizeof(sBuff));
			trim(sBuff, pKekka->rawdata);
			if( strlen(sBuff) > 2 ) {
				memcpy(KesKekka.etclbl, "99", 2);
			} else {
				memcpy(KesKekka.etclbl, sBuff, 2);
			}
		}
	}
	if( KesFlg )
	{
		/* 項目コードが「乳び」もしくは「溶血」の場合、関連項目Update */
		/* 乳び、溶血度更新 */
		ret = ZdbKekkaUpdateNbYk( &KesKekka );
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {

			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdateNbYk",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
			return(RET_STOP);

		}
		if( spKekka != NULL ) {
			ZbmlFree( spKekka );
			spKekka = NULL;
		}
		/*  関連項目のデータSelect */
		ret = ZdbKekkaSelectRckPos( &KesKekka, &spKekka, &num_spKekka );
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectRckPos",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
			return(RET_STOP);
		}
		else if(ret == HRC_SQL_NOT_FOUND){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		/* 乳び、溶血チェック */
		gfNyuYou = NyubiYoketu( pSrc, iKcnt );
		/* 関連項目データ分ループ */
		for( i = 0; i < num_spKekka; i++ ) {
			ret = NyubiYoketuChk(spKekka+i, 1, 0, gfNyuYou);
			if (ret != 0) {
				/* 登録チェックエラー */
				sFncSyslog ( LOG_ERR, "kesseiCHK()", "kessei Check Error." ) ;
				return ret;
			}
			/* 結果コメント1,2更新 */
			/*  ADD E.Osada 2006-08-17 */
			(spKekka+i)->kesseiflg = '1';

			ret = ZdbKekkaUpdateCmt12( spKekka+i );
			if ( ret != HRC_SQL_NORMAL&& ret != HRC_SQL_NOT_FOUND ) {
			   sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdateCmt12",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
					/* メモリ開放 */
				if( spKekka != NULL ) {
						ZbmlFree( spKekka );
				}
				return(RET_STOP);

			}
			if( (spKekka+i)->knsflg == 'H' ) {
				/* エラーがない場合は検査フラグに'X' */
				(spKekka+i)->knsflg = 'X';
			}
			/* ADD 2006-08-31 Nagata 検査フラグを更新する */
			ret = ZdbKekkaUpdateKnsFlg( spKekka+i );
			if(ret < 0){
				sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdateKnsFlg",ret);
				if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
				return(RET_STOP);
			}

		}
	}
	/* メモリ開放 */
	if( spKekka != NULL ) {
		ZbmlFree( spKekka );
	}
	return 0;
}

/**/
int CHG_Mojikjn(input,kbn)
/*****************************************************************************
*fc
	基準値(文字列データ)の換算値取得
	（１０ー　～　１０＋　の数値変換）
*rt
	換算値	 ... 基準値(文字列データ)の換算値
	BAD_DATA ... 基準値(文字列データ)に該当する換算値がない
*nt
*ag
*****************************************************************************/
char *input;
char kbn;
{
	int 	ret;
	int 	cnt;
	char	wk_input[20];

	ret = 0;

	trim(wk_input, input);

	if(wk_input[0] == '\0'){
		/* スペースなら終了 */
		return 0;
	}

	if( kbn == 'X' ){
		for(cnt = 1; KZN_Teisei[cnt] != NULL ; cnt++){
			if(memcmp(KZN_Teisei[cnt],"END",3) == 0){
				/* ENDなら抜ける */
				break;
			}
			if(memcmp(KZN_Teisei[cnt],wk_input,strlen(wk_input)) == 0){
				ret = cnt;
				break;
			}
		}
	}

	if( kbn == '0' ){
		for(cnt = 1; KZN_Coment[cnt] != NULL ; cnt++){
			if(memcmp(KZN_Coment[cnt],"END",3) == 0){
				/* ENDなら抜ける */
				break;
			}
			if(memcmp(KZN_Coment[cnt],wk_input,strlen(wk_input)) == 0){
				ret = cnt;
				break;
			}
		}
	}

	return ret;
}

/**/
int CHK_Kkacmt(input)
/*****************************************************************************
*fc
	異常値マーク代入結果コメントのチェック
*rt
	0	   ... 異常値マークなし
	1	   ... 異常値マークあり
	その他 ... エラー
*nt
*ag
*****************************************************************************/
char *input;
{
	int 	cnt;
	char	wk_input[20];

	trim(wk_input, input);

	if(wk_input[0] == '\0'){
		/* スペースなら終了 */
		return -1;
	}

	for(cnt = 1; IJOU_KKACMT[cnt] != NULL ; cnt++){
		if(memcmp(IJOU_KKACMT[cnt],"END",3) == 0){
			/* ENDなら抜ける */
			break;
		}
		if(memcmp(IJOU_KKACMT[cnt],wk_input,strlen(wk_input)) == 0){
			/* 異常値マークコメントに該当！！ */
			return 1;
		}
	}
	/* 該当なし */
	return 0;
}

