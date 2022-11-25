/**********************************************************************
 *
 *	   ＢＭＬ検査システム
 *
 *	   システム名：検査結果DB登録
 *	   ファイル名：LD106.c
 *	   概要		：分析機から受信した検査結果のCSVファイルをDBに登録する
 *
 **********************************************************************/

/**********************************************************************
 *	Ver.	 Date		Name		History
 * --------------------------------------------------------------------
 *	1.00	 2006/01/12 	BML.inc		Create
 **********************************************************************/
#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

#include "sql.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_dbrc.h"
#include "bml_base.h"

#include "LD106.h"
#include "LD106_db.h"

/* グローバル変数 */
/* 定性値基準値判定の為の換算テーブル */
char		KZN_Teisei[25][5];
char		KZN_Coment[25][5];
char		IJOU_KKACMT[100][5];

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
#define _VALUE_TNRYO_MILLILITER ('0')   /* 蓄尿量: ミリ リットル単位        */
#define _VALUE_TNRYO_LITER      ('1')   /* 蓄尿量: リットル単位             */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* 蓄尿量: 量単位不明               */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* 体重: キログラム単位             */
#define _VALUE_TJTNI_GRAM       ('1')   /* 体重: グラム単位                 */
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

/* レンジチェックマスタ 範囲区分定義 */
#define RNG_CHK		('1') 
#define BML_PANIC	('2') 
#define KNS_PANIC	('3')
#define SYOGO_CHK	('4')


/* 計算式中の IF ブロック展開                                               */
char	*OperateKSNSK(const char *);
char	*GetIFBlock(const char *);
struct	_IFBLOCK *SplitIFBlockItems(char *);
int	IsFormula(const char *);
void	freeIFBLOCK(struct _IFBLOCK *);

/* common_str.c 中の汎用関数                                                */
extern char	*_replace(const char *, const char *, const char *);
extern char	*_strchain(const char *, const char *);
extern char	*_strndup(const char *, size_t);
extern char	*_touppercase(const char *);
extern char	*_strrstr(char *, const char *);

/* 数値文字列判定                                                           */
extern int	_isnumeric(const char *);

double	StringCal_sub(char enzan,double val1,double val2);
double	StringCal(char *CalStr) ;

char	gszTransfer[MAXBUF + 1];		/* 文字列→数値 変換バッファ 単一の値の置換のみなので、コレで足りる    */

/* 指定文字列の前後のスペースを取り除いて文字列をコピーする */
void trim(char *dst, char *src) {
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
/*	関 数 名  ：kjnchk()							*/
/*	機能概要  ：基準値チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int kjnChk(my_stKEKKA *pKekka, my_stKJNMST *pKjnmst)
{
	/* 基準値から異常区分をチェックし、特別異常区分を設定する */
	char		tmp1[16];
	char		tmp2[16];
	double		rawData = 0.0;
	char		wk_knskka[25];
	int 		ikzn;
	int 		iwkkzn;

	/* 異常値区分の初期化 */
	pKekka->ijkbnm = pKekka->ijkbnf = pKekka->ijkbnn = '0';
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
		ikzn = chk_Mojikjn(wk_knskka,pKekka->knskka2kbn[0]);
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

			sFncPutLog (TRCKIND_DEBUG , __FILE__, "kjnChk1", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				    "ijkbn %c %c %c", pKekka->ijkbnm, pKekka->ijkbnf, pKekka->ijkbnn );
			/* 異常値区分が設定されたので抜ける */
			return 0;
		}

		/* 基準値 → 換算値変換（定性項目のみ） */
		/* 男低値１ */
		iwkkzn = chk_Mojikjn(pKjnmst->lwm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm1,"%d",iwkkzn);
		}
		/* 男低値２ */
		iwkkzn = chk_Mojikjn(pKjnmst->lwm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm2,"%d",iwkkzn);
		}
		/* 男基準値下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnmlw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmlw,"%d",iwkkzn);
		}
		/* 男基準値内下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm1,"%d",iwkkzn);
		}
		/* 男高値２ */
		iwkkzn =  chk_Mojikjn(pKjnmst->him2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him2,"%d",iwkkzn);
		}
		/* 男高値１ */
		iwkkzn =  chk_Mojikjn(pKjnmst->him1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him1,"%d",iwkkzn);
		}
		/* 男基準値上 */
		iwkkzn = chk_Mojikjn(pKjnmst->kjnmhi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmhi,"%d",iwkkzn);
		}
		/* 男基準値内下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm2,"%d",iwkkzn);
		}
		/* 女低値１ */
		iwkkzn = chk_Mojikjn(pKjnmst->lwf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf1,"%d",iwkkzn);
		}
		/* 女低値２ */
		iwkkzn = chk_Mojikjn(pKjnmst->lwf2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf2,"%d",iwkkzn);
		}
		/* 女基準値下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnflw,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnflw,"%d",iwkkzn);
		}
		/* 女基準値内下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnnaf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnnaf1,"%d",iwkkzn);
		}
		/* 女高値２ */
		iwkkzn =  chk_Mojikjn(pKjnmst->hif2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif2,"%d",iwkkzn);
		}
		/* 女高値１ */
		iwkkzn =  chk_Mojikjn(pKjnmst->hif1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif1,"%d",iwkkzn);
		}
		/* 女基準値上 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnfhi,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnfhi,"%d",iwkkzn);
		}
		/* 女基準値内下 */
		iwkkzn = chk_Mojikjn(pKjnmst->kjnnaf2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnnaf2,"%d",iwkkzn);
		}
		/* 不明低値１ */
		iwkkzn = chk_Mojikjn(pKjnmst->lwe1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwe1,"%d",iwkkzn);
		}
		/* 不明低値２ */
		iwkkzn = chk_Mojikjn(pKjnmst->lwe2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwe2,"%d",iwkkzn);
		}
		/* 不明基準値下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnelw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnelw,"%d",iwkkzn);
		}
		/* 不明基準値内下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kje1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje1,"%d",iwkkzn);
		}
		/* 不明高値２ */
		iwkkzn =  chk_Mojikjn(pKjnmst->hie2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie2,"%d",iwkkzn);
		}
		/* 不明高値１ */
		iwkkzn =  chk_Mojikjn(pKjnmst->hie1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie1,"%d",iwkkzn);
		}
		/* 不明基準値上 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kjnehi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnehi,"%d",iwkkzn);
		}
		/* 不明基準値内下 */
		iwkkzn =  chk_Mojikjn(pKjnmst->kje2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje2,"%d",iwkkzn);
		}
	}
#define chknum1(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 < atof(p2)))
#define chknum2(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 > atof(p2)))

#define chknumi1(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 < atoi(p2)))
#define chknumi2(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 > atoi(p2)))

	if( ikzn == 0 ){
		rawData = atof(pKekka->knskka1);

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
		sFncPutLog (TRCKIND_DEBUG , __FILE__, "kjnChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "ijkbn %f %c %c %c", rawData, pKekka->ijkbnm, pKekka->ijkbnf, pKekka->ijkbnn );
	return 0;
}


/******************************************************************************/
/*	関 数 名  ：filterChk()							*/
/*	機能概要  ：フィルターチェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int filterChk(my_stKEKKA *pKekka, my_stKJNMST *pKjnmst)
{
	my_stKKAFLTMST	 *pKkafltmst;
	my_stKKAFLTMST	 sKkafltmst;
	int 		ret = 0;
	int 		Kkafltmstflg;
	int 		cnt = 0;
	int 		lCnt = 0;
	double		rawData;
	double		DataMax;
	double		DataMin;
	char		tmp[32];
	int 		mojiFlg = 0;
	char		errMsg[1024] = {0,};

	pKkafltmst = NULL;

	/* フィルターマスター読み出し */
	memset(&sKkafltmst, '\0', sizeof(sKkafltmst));
	strncpy(sKkafltmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKkafltmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sKkafltmst.sstcd, pKekka->sstcd, 7);
	cnt = 0;

	ret = ZdbKkafltmstSelectGRPKMKKey(pKekka->knskisymd, &sKkafltmst, &pKkafltmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKkafltmstSelectGRPKMKKey",ret);
		sFncPutLog (TRCKIND_ERROR , __FILE__, "filterChk", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			return(RET_CONTINUITY);
		}
		return(RET_STOP);
	}

	/* 結果値の値文字列を数値化する */
	memset(tmp, '\0', sizeof(tmp));
	trim(tmp, pKekka->knskka1);
	if ((tmp[0] >= '0'&&tmp[0]<='9') || tmp[0]=='+' || tmp[0]=='-' || tmp[0] == '.' ) {
		rawData = atof(tmp);
	}
	else {
		/* 文字のときはフィルター処理を行わない */
		cnt = 0;
		mojiFlg = 1;
	}

	Kkafltmstflg = 0;
	if (cnt > 0) {
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			/* 上限・下限の値文字列を数値化する */
			memset(tmp, '\0', sizeof(tmp));
			strncpy(tmp, pKkafltmst[lCnt].minval, 12);
			DataMin = atof(tmp);

			memset(tmp, '\0', sizeof(tmp));
			strncpy(tmp, pKkafltmst[lCnt].maxval, 12);
			DataMax = atof(tmp);

			if ((DataMin <= rawData) && (rawData <= DataMax)) {
				strncpy(pKekka->knskka1, pKkafltmst[lCnt].knskka1, 12);
				strncpy(pKekka->knskka2, pKkafltmst[lCnt].knskka2, 24);
				strncpy(pKekka->knskka2kbn, pKkafltmst[lCnt].knskka2kbn, 2);
				strncpy(pKekka->kkahskcd, pKkafltmst[lCnt].kkahskcd, 3);
				strncpy(pKekka->skkka, pKkafltmst[lCnt].hjkka, 24);	 /*  */
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
	if (pKkafltmst != NULL ) {
		free( pKkafltmst );
	}
	sFncPutLog (TRCKIND_DEBUG , __FILE__, "filterChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		    "[%s][%s][%s][%s][%s]", pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka );
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：rngChk()							*/
/*	機能概要  ：再検レンジチェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pCalc	チェック元情報					*/
/*	出	  力  ：							*/
/*	 第２引数 ：pKekka	結果情報					*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int rngChk(my_stCALC *pCalc, my_stKEKKA *pKekka)
{
	my_stRNGCHKMST	sRngchkmst;
	my_stRNGCHKMST	*pRngchkmst;
	int 		cnt = 0;
	int 		ret = 0;
	double		rawData = 0.0;
	char		cRawBuf[256];
	char		errMsg[1024] = {0,};

	pRngchkmst = NULL;

	/* 生データがない(スペースor/)の場合なにもしない */
	memset(cRawBuf, '\0', sizeof(cRawBuf));
	trim(cRawBuf, pKekka->knskka1);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, '\0', sizeof(my_stRNGCHKMST));
	/* 範囲区分を条件に追加 */
	sRngchkmst.hnikbn = RNG_CHK;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pCalc->zrcd, "001", 3) == 0)
		|| (strncmp(pCalc->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pCalc->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pCalc->sbtkbn[0];
	/* 施設コード、性別区分を指定して検索 */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
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
			sFncPutLog (TRCKIND_ERROR, __FILE__, "BmlPanicChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* さらに見つからなかった場合、性別区分を指定し、施設コードをオール(0000000)で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pCalc->sbtkbn[0];
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
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
				sFncPutLog (TRCKIND_WARNING , __FILE__, "rngChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "rngChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->knskka1);
		pKekka->renjicflg = '1';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ( pRngchkmst[lCnt].ssa == '1'){
				if (atof(pRngchkmst[lCnt].hrng) < rawData) {
					pKekka->renjicflg = '3';
					pKekka->knsflg = 'A';
					break;
				}
			}
			else if ( pRngchkmst[lCnt].ssa == '2'){
				if (atof(pRngchkmst[lCnt].lrng) > rawData) {
					pKekka->renjicflg = '4';
					pKekka->knsflg = 'A';
					break;
				}
			}
		}
	}
	if ( pRngchkmst != NULL ){
		free( pRngchkmst );
	};

	sFncPutLog (TRCKIND_DEBUG , __FILE__, "rngChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[%s][%s][%s][%s][%s][%c]", 
		pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka, pKekka->renjicflg );
	return( 0 );
}

/******************************************************************************/
/*	関 数 名  ：BmlPanicChk()						*/
/*	機能概要  ：ＢＭＬパニックチェック					*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int BmlPanicChk(my_stCALC *pCalc, my_stKEKKA *pKekka)
{
	my_stRNGCHKMST	sRngchkmst;
	my_stRNGCHKMST	*pRngchkmst;
	int 		cnt = 0;
	int 		ret = 0;
	double		rawData = 0.0;
	char		cRawBuf[256];
	char		errMsg[1024] = {0,};

	pRngchkmst = NULL;

	/* 生データがない(スペースor/)の場合なにもしない */
	memset(cRawBuf, '\0', sizeof(cRawBuf));
	trim(cRawBuf, pKekka->knskka1);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, '\0', sizeof(my_stRNGCHKMST));
	/* 範囲区分を条件に追加 */
	sRngchkmst.hnikbn = BML_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pCalc->zrcd, "001", 3) == 0)
		|| (strncmp(pCalc->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pCalc->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pCalc->sbtkbn[0];
	/* 施設コード、性別区分を指定して検索 */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
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
			sFncPutLog (TRCKIND_ERROR, __FILE__, "BmlPanicChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* さらに見つからなかった場合、性別区分を指定し、施設コードをオール(0000000)で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pCalc->sbtkbn[0];
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
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
			sFncPutLog (TRCKIND_ERROR , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->knskka1);
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
	if ( pRngchkmst != NULL ){
		free( pRngchkmst );
	};

	sFncPutLog (TRCKIND_DEBUG , __FILE__, "BmlPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[%s][%s][%s][%s][%s][%c]", 
			pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka, pKekka->pncrgflg );
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
int KnsPanicChk(my_stCALC *pCalc, my_stKEKKA *pKekka)
{
	my_stRNGCHKMST   sRngchkmst;
	my_stRNGCHKMST   *pRngchkmst;
	int         cnt = 0;
	int         ret = 0;
	double      rawData = 0.0;
	char        cRawBuf[256];
	char        errMsg[1024] = {0,};

	pRngchkmst = NULL;

	/* 生データがない(スペースor/)の場合なにもしない */
	memset(cRawBuf, '\0', sizeof(cRawBuf));
	trim(cRawBuf, pKekka->knskka1);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, '\0', sizeof(my_stRNGCHKMST));
	/* 範囲区分を条件に追加(検査室パニックのみ取得) */
	sRngchkmst.hnikbn = KNS_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pCalc->zrcd, "001", 3) == 0) || (strncmp(pCalc->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pCalc->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pCalc->sbtkbn[0];
	/* 施設コード、性別区分を指定して検索 */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncPutLog (TRCKIND_ERROR , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
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
			sFncPutLog (TRCKIND_ERROR, __FILE__, "KnsPanicChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	/* さらに見つからなかった場合、性別区分を指定し、施設コードをオール(0000000)で指定して検索*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pCalc->sbtkbn[0];
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncPutLog (TRCKIND_ERROR , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
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
			sFncPutLog (TRCKIND_ERROR , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->knskka1);
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
	if ( pRngchkmst != NULL ){
		free( pRngchkmst );
	};

	sFncPutLog (TRCKIND_DEBUG , __FILE__, "KnsPanicChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "[%s][%s][%s][%s][%s][%c]", 
			pKekka->knskka1, pKekka->knskka2, pKekka->knskka2kbn, pKekka->hjkka, pKekka->skkka, pKekka->knspncrgflg );
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：KeisanChk() 						*/
/*	機能概要  ：計算チェック						*/
/*	入	  力  ：							*/
/*	 第１引数 ：pKekka	結果情報					*/
/*	出	  力  ：							*/
/*	復帰情報  ：int 							*/
/*					 0	正常				*/
/*					-1	異常				*/
/******************************************************************************/
int KeisanChk(my_stCALC *pCalc, char *sKSNSK, my_stKEKKA *pCalcKka, char *sKnsflg, int kjsstnksu, int KekkaOtherFlg )
{
	char		calBuff[1024];
	int 		ret;
	char		rawData[64];
	char		knskka2kbn[2+1];
	char		kkahskcd[3+1];
	char		knsflg[1+1];
	int 		iCnt;	/* ループカウンタ */
	int 		setCnt;
	int 		tmpCnt;
	char		getKmkcd[32];
	double		calNum = 0.0;

	char *pszExpandKSNSK = (char *) NULL; /* IF 文展開後の計算式              */
	sKnsflg[0] = '\0';

	/* 式中の項目コードを数値に置き換える。 */
	memset(calBuff, '\0', sizeof(calBuff));
	for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
		/* 項目コードの始まり'['を検索する。 */
		if (sKSNSK[iCnt] == '[') {
			/* 項目値を検索 */
			memset(getKmkcd, '\0', sizeof(getKmkcd));
			tmpCnt = 0;
			iCnt++;
			/* 項目コードを転送（終了位置の]かNullまで） */
			while (sKSNSK[iCnt] != ']' && sKSNSK[iCnt] != '\0') {
				getKmkcd[tmpCnt++] = sKSNSK[iCnt++];
			}
			/* 結果情報、もしくは他サテライト結果情報から指定の項目コードを検索し、置き換える。 */
			memset(knsflg,'\0', sizeof(knsflg));
			ret = ZdbSelCalcSource(pCalc->utkymd, pCalc->irino, pCalc->kmkcd, getKmkcd, rawData, kkahskcd, knskka2kbn, knsflg, KekkaOtherFlg);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					return(RET_CONTINUITY);
				}
				return (RET_STOP);
			}
			if (ret == HRC_SQL_NOT_FOUND) {
				return(RET_CONTINUITY);
			}
			/* 計算元にコメント結果、もしくは結果補足コードが入っていた場合、計算元エラーとする。 */
			if (knskka2kbn[0] == '0' || strcmp(kkahskcd , "   ") != 0) {
				ret = ZdbInsNotCalc( pCalc );
				if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						return(RET_CONTINUITY);
					}
					return (RET_STOP);
				}
				return(RET_CONTINUITY);
			}
			/* 計算元項目に検査フラグＡの項目があった場合、報告できないように検査フラグを設定する。 */
			if (knsflg[0] == 'A') {
				sKnsflg[0] = 'A';
				sKnsflg[1] = '\0';
			}
			strncat(calBuff, rawData, 21);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_SC == (int) sKSNSK[iCnt]) {
			/* 身長 */
			/* 利用可能な値以外が指定されていた場合、計算しない */
			if (strncmp(pCalc->sc ,"     ", 5) == 0 ){
				return(RET_CONTINUITY);
			}
			memcpy((void *) gszTransfer, pCalc->sc, FLDSIZE_SC);
			gszTransfer[FLDSIZE_SC] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
				return(RET_CONTINUITY);
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_TJ == (int) sKSNSK[iCnt]) {
			/* POWと区別するため、前の文字がOで無いかチェックする。 */
			if (sKSNSK[iCnt-1] != 'o' || sKSNSK[iCnt-1] != 'O') {
				if (strncmp(pCalc->tj ,"     ", 5) == 0 ){
					return(RET_CONTINUITY);
				}
				/* 体重 */
				strncpy(gszTransfer, pCalc->tj, FLDSIZE_TJ);
				/* 利用可能な値以外が指定されていた場合、計算しない */
				gszTransfer[FLDSIZE_TJ] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
				else {
					/* 体重は kg 以外はＮＧ */
					if( ((int)pCalc->tjtni[0]) !=  _VALUE_TJTNI_KILLOGRAM) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
						return(RET_CONTINUITY);
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (KSNSK_TNTME == (int) sKSNSK[iCnt]) {
			/* 蓄尿時間 */
			/* 利用可能な値以外が指定されていた場合、計算しない */
			memcpy((void *) gszTransfer, pCalc->tntme, FLDSIZE_TNTME);
			gszTransfer[FLDSIZE_TNTME] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
				return(RET_CONTINUITY);
			}
			else {
				/* 蓄尿時間は 時間(h) 以外はＮＧ */
				if( ((int) pCalc->tntni[0]) != _VALUE_TNTNI_HOUR ) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_TNRYO == (int) sKSNSK[iCnt]) {
			/* 蓄尿量 */
			/* 利用可能な値以外が指定されていた場合、計算しない */
			memcpy((void *) gszTransfer, pCalc->tnryo, FLDSIZE_TNRYO);
			gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
				return(RET_CONTINUITY);
			}
			else {
				/* 蓄尿量は ml 以外はＮＧ */
				if( ((int) pCalc->tnryotni[0]) != _VALUE_TNRYO_MILLILITER ) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_SBTKBN == (int) sKSNSK[iCnt]) {
			/* 性別区分 */
			if (_VALUE_SBTKBN_MALE == (int) pCalc->sbtkbn[0] ||
					_VALUE_SBTKBN_FEMALE == (int) pCalc->sbtkbn[0]) {
				strncat(calBuff, &(pCalc->sbtkbn[0]), sizeof(pCalc->sbtkbn[0]));
				setCnt = strlen(calBuff);
			}
			else {
				calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
				calBuff[setCnt] = (char) '\0';
				/* 性別不明だった場合、計算しない */
				return(RET_CONTINUITY);
			}
		}
		else if (KSNSK_AGE == (int) sKSNSK[iCnt]) {
			if (strncmp(pCalc->age ,"   ", 3) == 0 ){
				return(RET_CONTINUITY);
			}
			/* 年齢	*/
			if (_VALUE_AGEKBN_YEAR != (int) pCalc->agekbn[0]) {
				calBuff[setCnt++] = (char) '0';
				calBuff[setCnt] = (char) '\0';
				/* 年齢区分が 歳 以外だった場合、計算しない */
				return(RET_CONTINUITY);
			}
			else {
				memcpy((void *) gszTransfer, pCalc->age, FLDSIZE_AGE);
				gszTransfer[FLDSIZE_AGE] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					/* 利用可能な値以外が指定されていた場合、計算しない */
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
					return(RET_CONTINUITY);
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (sKSNSK[iCnt] == '\0') {
			break;
		}
		else {
			calBuff[setCnt++] = sKSNSK[iCnt];
		}
	}

	/* 計算式に含まれる IF 文の展開                                         */
	if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
		if ('\0' != (int) *pszExpandKSNSK) {
			sFncPutLog (TRCKIND_TRACE, __FILE__, "KeisanChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "計算式[%s]", pszExpandKSNSK ) ;
			strcpy(calBuff, pszExpandKSNSK);
		}
		free((void *) pszExpandKSNSK);
		pszExpandKSNSK = (char *) NULL;
	}


	/* 文字列の計算式を計算する。 */
	calNum = StringCal(calBuff);
	if( isfinite(calNum) == 0 ){
		/* ０除算や負の値のlog等、正常に計算できない式となった場合 */
		sFncPutLog (TRCKIND_ERROR , __FILE__, "KeisanChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					  "計算結果が実数ではありません。 utkymd: %s irino: %s kmkcd:%s", pCalc->utkymd, pCalc->irino, pCalc->kmkcd) ;

		sprintf( pCalcKka->rawdata, "                    ");
		sprintf( pCalcKka->knskka1, "            ");
		sprintf( pCalcKka->knskka2, "                        " );
		sprintf( pCalcKka->knskka2kbn, "  " );
		sprintf( pCalcKka->kkahskcd, "   " );
		/* 報告できないように検査フラグを設定する。 */
		sKnsflg[0] = 'A';
		sKnsflg[1] = '\0';
	}
	else {
		snprintf( pCalcKka->rawdata, 21, "%-20f", calNum);
		if( kjsstnksu == 9 ) {
			snprintf( pCalcKka->knskka1, 13, "%-12f", calNum);
		}
		else {
			/* 丸め */
			calNum = calNum * pow( 10, kjsstnksu );
			calNum = round( calNum );
			calNum /= pow(10, kjsstnksu );
			snprintf( pCalcKka->knskka1, 13, "%12.*f", kjsstnksu, calNum );
		}
		sprintf( pCalcKka->knskka2, "                        " );
		sprintf( pCalcKka->knskka2kbn, "  " );
		sprintf( pCalcKka->kkahskcd, "   " );

		sFncPutLog (TRCKIND_DEBUG, __FILE__, "KeisanChk",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			    "(%f)(%s)(%s)", calNum, pCalcKka->rawdata, pCalcKka->knskka1) ;
	}

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
	sFncPutLog (TRCKIND_DEBUG, __FILE__, "StringCal_sub",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
		    "enzan(%c) val1(%f) val2(%f)", enzan, val1, val2) ;
	switch ( enzan ) {
	case '+':
		return (val1 + val2);
		break;
	case '-':
		return (val1 - val2);
		break;
	case '/':
		return (val1 / val2);
		break;
	case '*':
		return (val1 * val2);
		break;
	}
	return(0);
}

/****************************************************************************************/
/*	関 数 名  ：StringCal() 							*/
/*	機能概要  ：渡された文字列の計算式を行う					*/
/*	入	  力  ：								*/
/*	 第１引数 ：CalStr	:	計算文字列					*/
/*	出	  力  ：								*/
/*	復帰情報  ：double	計算結果						*/
/*											*/
/*	注意：	対応する演算子は「+ - * /」が可能である。				*/
/*			それ以外にLOG、LOG10、POWの3つの計算を行う。			*/
/*			計算の優先順位は、四則演算の優先順位に従い*と/が優先される。	*/
/****************************************************************************************/
double StringCal(char *CalStr)
{
	char		StacEn;
	double		StacNum;
	int 		flg;
	int 		loopCnt, strCnt;
	double		ret;
	char		cStacNum[1024];
	char		cStacNum2[1024];
	double		tmpStacNum;
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
			/* LOG及びLOG10内が計算式になっている場合については対応していない */
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
				for (c = 0, i = loopCnt + 4; CalStr[i] != ':' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				/* POWの底が計算式になっている場合があるので、再帰呼び出しで計算する。 */
				/* 食塩摂取量対応。ここだけの特別処理。他のプログラムの計算ロジックでは対応していない */
				tmpStacNum = 0.0 ;
				tmpStacNum = StringCal(cStacNum);
				for (c = 0, i += 1; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum2[c] = CalStr[i];
				}
				cStacNum2[c] = '\0';
				/* 指数が計算式になっている場合については対応していない */
				StacNum = pow(tmpStacNum, atof(cStacNum2));
				sFncPutLog (TRCKIND_DEBUG, __FILE__, "StringCal pow",__LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
							"StacNum[%f] tmpStacNum[%f] cStacNum2[%s] cStacNum[%s]",
							 StacNum, tmpStacNum, cStacNum2, cStacNum ) ;
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

/**/
int chk_Mojikjn(input,kbn)
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
        0          ... 異常値マークなし
        1          ... 異常値マークあり
        その他 ... エラー
*nt
*ag
*****************************************************************************/
char *input;
{
	int	cnt;
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

/****************************************************************************
 * KSNSK_if.c : 計算式文字列 IF ブロック展開
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

/*--------------------------------------------------------------------------*
 * OperateKSNSK
 *
 * 計算式文字列中に含まれる IF ブロックの展開
 *
 * Paramter(s):
 *  pszKSNSK            NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、 IF ブロックを含む計算式の文
 *                      字列です。
 *
 * Return value:
 *  関数が正常終了した場合、IF ブロック文字列展開後の文字列が格納している領
 *  域の先頭ポインタインタを返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で free() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
char *OperateKSNSK(const char *pszKSNSK)
{
	static char	 szBlank[] = " ";
	static char	 szNE[] = STR_NE;

	char		*pszFormular;				/* 戻り値 (処理対象の計算式)        */
	char		*pszReplace;				/* IF ブロック展開結果              */
	char		*pszIFBlock = (char *) NULL;		/* IF ブロック文字列                */
	struct _IFBLOCK *pstItems = (struct _IFBLOCK *) NULL;	/* IF ブロックを項目要素毎に分解    */
	double		dblLeft;				/* 条件式左辺値                     */
	double		dblRight;				/* 条件式右辺値                     */
	BOOL		nCompared = FALSE;			/* 条件式判定結果                   */
	BOOL		nErrorOccured = FALSE;			/* エラー発生フラグ                 */
	static char	 szConvert[32];

	if (NULL != (void *) (pszFormular = _touppercase(_replace(pszKSNSK, szBlank, (char *) NULL)))) {
		if (!nErrorOccured && NULL != (void *) pszFormular) {
			if (!IsFormula(pszFormular)) {
				nErrorOccured = TRUE;   /* 計算式として異常                 */
				free((void *) pszFormular);
				pszFormular = (char *) NULL;
			}
		}

		while (!nErrorOccured && NULL != (void *) (pszIFBlock = GetIFBlock(pszFormular))) {
			if (NULL == (void *) (pstItems = SplitIFBlockItems(pszIFBlock))) {
				nErrorOccured = TRUE;   /* IF ブロック内の要素分解失敗      */
				free((void *) pszFormular);
				pszFormular = (char *) NULL;
			}
			else if (NULL == (void *) pstItems->pszConditionLeft ||
			         NULL == (void *) pstItems->pszOperator ||
			         NULL == (void *) pstItems->pszConditionRight ||
			         NULL == (void *) pstItems->pszValueTrue ||
			         NULL == (void *) pstItems->pszValueFalse) {
				nErrorOccured = TRUE;   /* IF ブロック内の要素分解失敗      */
				free((void *) pszFormular);
				pszFormular = (char *) NULL;
			}
			else {
				/* 分解した内容を元に IF ブロック内判定 (ここが IF ブロックの展開エンジン) */
				dblLeft = StringCal(pstItems->pszConditionLeft);
				dblRight = StringCal(pstItems->pszConditionRight);
				/* 一度文字列に変換しないとうまく比較できない               */
				sprintf(szConvert, "%f", dblLeft);
				dblLeft = strtod(szConvert, (char **) NULL);
				sprintf(szConvert, "%f", dblRight);
				dblRight = strtod(szConvert, (char **) NULL);

				switch ((int) *(pstItems->pszOperator)) {
				case OPERATOR_EQ:       /* 条件式: 一致                     */
					nCompared = ((dblLeft == dblRight) ? TRUE : FALSE);
					break;
				case OPERATOR_LT:       /* 条件式: 未満 or 不一致           */
					if (strcmp(pstItems->pszOperator, szNE)) {
						nCompared = ((dblLeft < dblRight) ? TRUE : FALSE);
					} else {
						nCompared = ((dblLeft != dblRight) ? TRUE : FALSE);
					}
					break;
				case OPERATOR_GT:       /* 条件式: 越える                   */
					nCompared = ((dblLeft > dblRight) ? TRUE : FALSE);
					break;
				default:                /* 異常な比較演算子                 */
					nErrorOccured = TRUE;
					free((void *) pszFormular);
					pszFormular = (char *) NULL;
					break;
				}
			}
			if (!nErrorOccured) {
				if (nCompared) {
					pszReplace = _replace(pszFormular, pszIFBlock, pstItems->pszValueTrue);
				}
				else {
					pszReplace = _replace(pszFormular, pszIFBlock, pstItems->pszValueFalse);
				}
				if (NULL == (void *) pszReplace) {
					nErrorOccured = TRUE;
					/* IF ブロック → 適用値変換失敗    */
					free((void *) pszFormular);
					pszFormular = (char *) NULL;
				}
				else {
					free((void *) pszFormular);
					pszFormular = pszReplace;
				}
			}
			if (NULL != (void *) pszIFBlock) {
				free((void *) pszIFBlock);
			}
			freeIFBLOCK(pstItems);
		}
	}

	if (!nErrorOccured && NULL != (void *) pszFormular) {
		if (!IsFormula(pszFormular)) {
			nErrorOccured = TRUE;       /* 計算式として異常                 */
		}
	}

	if (nErrorOccured && NULL != pszFormular) {
		free((void *) pszFormular);
		pszFormular = (char *) NULL;
	}
	return (pszFormular);
}

/*--------------------------------------------------------------------------*
 * GetIFBlock
 *
 * 計算式に含まれる IF ブロック文字列を抽出します。
 *
 * Paramter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、 IF ブロックを含む計算式の文
 *                      字列です。
 *
 * Return value:
 *  関数が正常終了した場合、抽出した IF ブロック文字列を格納する領域の先頭ポ
 *  インタを返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で free() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
char *GetIFBlock(const char *pszOriginal)
{
	static char	szIFBlock[] = STR_BEGIN_IFBLOCK;

	char	*pszResult = NULL;	/* 戻り値                           */
	char	*pszIFBlock;	 	/* IF ブロック開始位置              */
	size_t	ulOriginal; 	 	/* 元の文字列の長さ                 */
	char	*pszFind;	 	/* IF ブロック終端検索              */
	int	nParenthesis = 0; 	/* 括弧の階層震度                   */
	int	nComma;			/* カンマの数                       */
	BOOL	nTarminate;		/* IF ブロック終端検出              */

	if (NULL != (void *) pszOriginal) {
		if ((size_t) 0 <= (ulOriginal = strlen(pszOriginal))) {
			if (NULL != (void *) (pszIFBlock = _strrstr((char *) pszOriginal, (const char *) szIFBlock))) {
				for (pszFind = (pszIFBlock + strlen(szIFBlock)), nTarminate = FALSE, nParenthesis = 0, nComma = 0; !nTarminate; pszFind++) {
					switch	((int) *pszFind) {
					case	PARENT_BEGIN:  /* カッコ (開始)                    */
						nParenthesis++;
						break;
					case	_EOS:
					case	PARENT_END:    /* カッコ (終了)                    */
						nParenthesis--;
						if (0 > nParenthesis) {
							nTarminate = TRUE;
							if (1 < nComma) {
								pszResult = _strndup(pszIFBlock, (size_t) (pszFind - pszIFBlock + 1));
							}
						}
						break;
					case SPLITTER_COMMA: /* 要素の区切りを示すカンマ         */
						nComma++;
						break;
					default:
					    break;
					}
				}
			}
		}
	}
	return (pszResult);
}

/*--------------------------------------------------------------------------*
 * IsFormula
 *
 * 計算式の書式チェック
 *
 * Paramter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、計算式の文字列です。
 *
 * Return value:
 *  指定された文字列が、計算式として成立している場合、 0 以外の値を返しま
 *  す。
 *  計算式以外の場合、またはエラーが発生した場合、値 0 を返します。
 *--------------------------------------------------------------------------*/
int IsFormula(const char *pszKSNSK)
{
	BOOL	bResult = FALSE;
	char	*pszFormular;
	char	*pszReplace;
	int	nIndex;
	int	nParenthesis = 0;               /* 括弧の階層震度                   */

	if (NULL != (void *) (pszFormular = _touppercase(_replace(pszKSNSK, " ", (char *) NULL)))) {
		/* 算術関数の除去                                                   */
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_IFBLOCK, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;

			if (NULL != (void *) (pszReplace = _replace(pszFormular, ":", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			if (NULL != (void *) (pszReplace = _replace(pszFormular, ",", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			/* 条件式中の比較演算子除去                                     */
			if (NULL != (void *) (pszReplace = _replace(pszFormular, "<", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			if (NULL != (void *) (pszReplace = _replace(pszFormular, ">", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
			if (NULL != (void *) (pszReplace = _replace(pszFormular, "=", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
		}
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_LOG10, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;
		}
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_LOG, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;
		}
		if (NULL != (void *) (pszReplace = _replace(pszFormular, STR_BEGIN_POW, (char *) NULL))) {
			free((void *) pszFormular);
			pszFormular = pszReplace;
			if (NULL != (void *) (pszReplace = _replace(pszFormular, ",", (char *) NULL))) {
				free((void *) pszFormular);
				pszFormular = pszReplace;
			}
		}
		/* 数文字 (小数点を含む) 、演算記号判定                             */
		for (nIndex = 0, bResult = TRUE; bResult && '\0' != (int) *(pszFormular + nIndex); nIndex++) {
			if (0 == isdigit((int) *(pszFormular + nIndex))) {
				if ('.' != (int) *(pszFormular + nIndex) &&
				    PARENT_BEGIN != (int) *(pszFormular + nIndex) &&
				    PARENT_END != (int) *(pszFormular + nIndex) &&
				    '+' != (int) *(pszFormular + nIndex) &&
				    '*' != (int) *(pszFormular + nIndex) &&
				    '-' != (int) *(pszFormular + nIndex) &&
				    '/' != (int) *(pszFormular + nIndex)) {
					bResult = FALSE;
				}
			}
		}
		free((void *) pszFormular);
		/* 括弧対応チェック                                                 */
		if (bResult) {
			for (nParenthesis = 0, nIndex = 0; bResult && '\0' != (int) *(pszKSNSK + nIndex); nIndex++) {
				switch ((int) *(pszKSNSK + nIndex)) {
				case PARENT_BEGIN:
					nParenthesis++;
					break;
				case PARENT_END:
					nParenthesis--;
				default:
					break;
				}
			}
			if (nParenthesis) {
				bResult = FALSE;
			}
		}
	}
	return (bResult ? !0:0);
}

/*--------------------------------------------------------------------------*
 * SplitIFBlockItems
 *
 * IF ブロック文字列を項目単位に分解します。
 *
 * Paramater(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、要素ごとに分解する計算式の 
 *                      IF ブロック文字列です。
 *
 * Return value:
 *  関数が正常終了した場合、分解後の項目文字列を格納する _IFBLOCK 構造体の先
 *  頭ポインタを返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で freeIFBLOCK() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
struct _IFBLOCK *SplitIFBlockItems(char *pszOrigin)
{
	static char szNE[] = STR_NE;

	struct	_IFBLOCK *pstResult = (struct _IFBLOCK *) NULL; /* 戻り値   */
	BOOL	nErrorOccured = FALSE;	/* エラー検出フラグ                 */
	BOOL	nTerminate = FALSE;	/* 分解終了フラグ                   */
	char	*pszTarget;		/* 判定文字                         */
	char	*pszBegin;		/* 分解対象の項目の先頭             */
	int	nParenthesis;		/* カッコの入れ子深度               */
	int	nIndex;			/* 分解項目の項目インデックス       */

	if (NULL == (void *) pszOrigin) {
		pstResult = (struct _IFBLOCK *) NULL;
	}
	else if (NULL != (void *) (pstResult = (struct _IFBLOCK *) malloc(sizeof(struct _IFBLOCK)))) {
		for (nIndex = 0; MAXCNT_ITEM_IFBLOCK >= nIndex; nIndex++) {
			*((void **) pstResult + nIndex) = NULL;
		}
		for (nErrorOccured = FALSE, nTerminate = FALSE, nIndex = 0, nParenthesis = 0, pszBegin = pszTarget = (strchr(pszOrigin, '(') + 1);
			!nErrorOccured && !nTerminate && NULL != (void *) pszTarget && _EOS != (int) *pszTarget;
			pszTarget++) {

			switch	((int) *pszTarget) {
			case	PARENT_BEGIN:          /* カッコ (開始)                    */
				nParenthesis++;
				break;

			case PARENT_END:            /* カッコ (終了)                    */
				nParenthesis--;
				if (0 > nParenthesis) {
					if (NULL == (void *) pstResult->pszValueTrue ||
					    NULL == (void *) pstResult->pszConditionRight) {
						nErrorOccured = TRUE;
						 /* IF ブロックの終了を示す ')' を検
						    出したが、必須項目が不足している */
					}
					else if (NULL == (void *) (pstResult->pszValueFalse = 
								_strndup(pszBegin, (size_t) (pszTarget - pszBegin)))) {
						nErrorOccured = TRUE;
					}
					else {
						nTerminate = TRUE;
					}
				}
				break;
			case OPERATOR_LT:           /* 条件式演算子                     */
			case OPERATOR_GT:
			case OPERATOR_EQ:
				if (nParenthesis &&
					NULL != (void *) pstResult->pszConditionLeft) {
					nErrorOccured = TRUE;
				}
				else if (NULL == (void *) (pstResult->pszConditionLeft = 
				                           _strndup(pszBegin,
				                                    (size_t) (pszTarget - pszBegin)))) {
					nErrorOccured = TRUE;
				}
				else if (OPERATOR_LT == (int) *pszTarget &&
					 OPERATOR_GT == (int) *(pszTarget + 1)) {
					if (NULL == (void *) (pstResult->pszOperator = strdup(szNE))) {
						nErrorOccured = TRUE;
					}
					else {
						pszTarget++;
						pszBegin = pszTarget;
						pszBegin++;
					}
				}
				else if (NULL == (void *) (pstResult->pszOperator = _strndup(pszTarget, 1))) {
					nErrorOccured = TRUE;
				}
				else {
					pszBegin = pszTarget;
					pszBegin++;
				}
				break;
			case SPLITTER_COMMA:    /* 要素の区切りを示すカンマ             */
				if (nParenthesis) {
					break;
				}
				else if (NULL == (void *) pstResult->pszConditionRight) {
					/* 条件式右辺 - 条件式が真の場合に適用する値            */
					if (NULL == (void *) (pstResult->pszConditionRight =
						 	_strndup(pszBegin, (size_t) (pszTarget - pszBegin)))) {
						nErrorOccured = TRUE;
					}
					else {
						pszBegin = pszTarget;
						pszBegin++;
					}
				}
				else if (NULL == (void *) pstResult->pszValueTrue) {
					/* 条件式が真の場合に適用する値 - 
					   偽の場合に適用する値                                 */
					if (NULL == (void *) (pstResult->pszValueTrue = 
								_strndup(pszBegin, (size_t) (pszTarget - pszBegin)))) {
						 nErrorOccured = TRUE;
					}
					else {
						pszBegin = pszTarget;
						pszBegin++;
					}
				}
				else {
					nErrorOccured = TRUE;
				}
				break;
			default:                    /* ここでの処理の対象外             */
				break;
			}
		}
	}

	/* エラー発生時は、 (途中まで) 確保した内容をクリア                     */
	if (nErrorOccured && NULL != (void *) pstResult) {
	    freeIFBLOCK(pstResult);
	    pstResult = (struct _IFBLOCK *) NULL;
	}
	return (pstResult);
}

/*--------------------------------------------------------------------------*
 * freeIFBLOCK
 *
 * IF ブロック内要素分解構造体の要素を全て開放
 *
 * Parameter(s):
 *  pstTarget           IF ブロック内要素分解構造体の先頭ポインタを指定しま
 *                      す。
 *
 * Return value:
 *  Nothing
 *--------------------------------------------------------------------------*/
void freeIFBLOCK(struct _IFBLOCK *pstTarget)
{
	int nIndex;                         /* 項目インデックス                 */

	if (NULL != (void *) pstTarget) {
		for (nIndex = 0; MAXCNT_ITEM_IFBLOCK > nIndex; nIndex++) {
			if (NULL != *((void **) pstTarget + nIndex)) {
				free((void *) *((void **) pstTarget + nIndex));
			}
		}
		free((void *) pstTarget);
	}
	return;
}
