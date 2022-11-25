/**********************************************************************
 *
 *     ケミストリー検査システム
 *
 *     システム名：履歴情報ファイルコンバート
 *     ファイル名：RirekiConv.c
 *     概要      ：他ラボの結果情報ファイルをケミストリーの履歴テーブルに
 *                 変換できる形式へコンバートする。
 *
 **********************************************************************/
/* ※１ 呼び出し元で出力結果をログに出力するため、printf で標準出力へ出力する */
/* ※２ 日次エラー時にエラーメッセージをメール送信するために、エラーファイルを作成する */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

/********************************************************************************
*       別名定義                                                                *
*********************************************************************************/
#define MY_COM_SIZE	sizeof  ( char )

#define DEF_STAMP "-00.00.00.000001"

#define RTN_OK 0
#define RTN_NG -1

#define FILE_KMKMST	"TMP_KMKMST.del"
#define FILE_CMTMST	"TMP_CMTMST.del"
#define FILE_ID		"A00"

/* ※２ */
#define LOG_DIR		"/apdata/aplog"
#define NAME_ERRLOG	"FATAL_"
/********************************************************************************
*       内部関数定義                                                            *
*********************************************************************************/
static int		mainFunction( char*, char*, char* ) ;
static int		SetKnsgrp( char *, char * ) ;
static int		ConvKekka( char *, char *, char, char *, char * ) ;
static int		ConvCmtKekka( char *, char * ) ;
static int		GetKmkFile( void ) ;
static int		GetCmtFile( void ) ;
static int		NameKeyMake( char *, char *, int ) ;
static char*	SetValue( char *, char *, int ) ;
static int		DateGetToday( char * ) ;
static void		StringTrim( char *, char * ) ;
static void		PutErrLog() ;

/********************************************************************************
*       グローバル変数定義                                                      *
*********************************************************************************/
static void		*FILE_KMKMST_DATA ;		/* 項目マスタファイルのメモリポインタ   */
static int		CNT_KMKMST ;			/* 項目マスタファイルの取得件数         */
static void		*FILE_CMTMST_DATA ;		/* コメントマスタのメモリポインタ       */
static int		CNT_CMTMST ;			/* コメントマスタの取得件数             */
static char		WORK_DIR_PATH[512] ;	/* 日次ディレクトリ                     */

/********************************************************************************
*       構造体定義                                                              *
*********************************************************************************/
/* 履歴テーブル定義 */
typedef struct _rireki_table {
	char utkymd[10+1];
	char irino[11+1];
	char iriketflg[1+1];
	char zssdino[1+1];
	char knsgrp[16+1];
	char kmkcd[7+1];
	char sstcd[7+1];
	char krtno[40+1];
	char knjnmkey[60+1];
	char sbtkbn[1+1];
	char age[3+1];
	char agekbn[1+1];
	char bskkbn[4+1];
	char bsklne[4+1];
	char bskgok[6+1];
	char rawdata[20+1];
	char hjkka[24+1];
	char kkacmt1[5+1];
	char kkacmt2[5+1];
	char ijkbnm[1+1];
	char ijkbnf[1+1];
	char ijkbnn[1+1];
	char tbijkbnm[1+1];
	char tbijkbnf[1+1];
	char tbijkbnn[1+1];
	char ksbr[15+1];
	char nbdo[2+1];
	char ykdo[2+1];
	char hkkdh[26+1];
	char ksndh[26+1];
	char oyasstcd[7+1];
} RIREKI_TABLE ;

/* 検査グループ取得用ファイル構造体 */
typedef struct _struct_kmkmst {
	char kmkcd[7+1];
	char knsgrp[16+1];
} STRUCT_KMKMST ;

/* 検査グループ取得用ファイル構造体 */
typedef struct _struct_cmtmst {
	char cmcd[5+1];
	char kekka[12+1];
} STRUCT_CMTMST ;

/******************************************************************************/
/*  関 数 名  ：main                                                          */
/*  機能概要  ：メイン                                                        */
/*   第１引数 ：作業ディレクトリ                                              */
/******************************************************************************/
int main ( argc, argv ) 
int		 argc ;
char	*argv[] ;
{
	DIR				*Dirp;					/* ディレクトリポインタ */
	struct dirent	*Direntp;				/* ディレクト構造体 */
	char            FileName[1024];			/* ファイル名 (作業用) */
	char			*FileDate;				/* ファイル名 日付（未使用）*/
	char			*FileLaboCode;			/* ファイル名 ラボコード */
	char			*FileExtention;			/* ファイル名 サテライトＩＤ＋拡張子 */
	char			*Empty;					/* ファイル名 末端確認用*/
	char            TargetFileName[1024];	/* 処理対象ファイル */

	int				rtc;
	char			InFilePath[512];
	char			OutFilePath[512];

	/* 引数チェック */
	if ( argc < 2 ) {
		printf("引数が間違っています。\n"); /* ※１ */
		PutErrLog() ;
		return( RTN_NG ) ;
	}

	/* 引数の取得 */
	sprintf( WORK_DIR_PATH, "%s", argv[1]);

	/* マスタファイルの内容取得 */
	rtc = GetKmkFile();
	if( rtc != RTN_OK ){
		PutErrLog() ;
		return( RTN_NG ) ;
	}
	rtc = GetCmtFile();
	if( rtc != RTN_OK ){
		PutErrLog() ;
		free( FILE_KMKMST_DATA ) ;
		return( RTN_NG ) ;
	}

	/* */
	Dirp = opendir( WORK_DIR_PATH ) ;
	while(( Direntp = readdir( Dirp )) != NULL ){
		sprintf( FileName, "%s", Direntp->d_name );
		sprintf( TargetFileName,"%s%s", FILE_ID, ".dat" );
		/* ファイル名が拡張子より短い場合はスキップ */
		if( strlen( FileName ) <= strlen( TargetFileName ) ) continue;
		/* ファイル名を分割 */
		FileDate = strtok( FileName, "_");
		if( FileDate == NULL ) continue; 
		FileLaboCode = strtok(NULL, "_");
		if( FileLaboCode == NULL ) continue; 
		FileExtention = strtok(NULL, "_");
		if( FileExtention == NULL ) continue; 
		Empty = strtok(NULL, "_");
		if( Empty != NULL ) continue;			/* 拡張子の後に何かファイル名が存在している場合はＮＧ */
		/* 拡張子が .dat のファイル、かつ、自サテライトＩＤのファイルのみ処理 */
		if( strncmp( FileExtention , TargetFileName, strlen( TargetFileName ) ) == 0 ){
			sprintf(InFilePath, "%s/%s", WORK_DIR_PATH, Direntp->d_name ) ;
			sprintf(OutFilePath,"%s/CNV_%s", WORK_DIR_PATH, Direntp->d_name ) ;
			printf("ファイルコンバート処理を開始します。 [%s] -> [%s]\n", InFilePath, OutFilePath ) ; /* ※１ */
			/* ファイルを Insert 形式にコンバートする */
			rtc = mainFunction( InFilePath, OutFilePath, FileLaboCode ) ;
			if( rtc != RTN_OK ){
				printf("ファイルコンバートに失敗しました。[%s] -> [%s]\n", InFilePath, OutFilePath ) ; /* ※１ */
				PutErrLog() ;
				free( FILE_KMKMST_DATA ) ;
				free( FILE_CMTMST_DATA ) ;
				closedir( Dirp ) ;
				return( RTN_NG ) ;
			}
			printf("ファイルコンバートに成功しました。[%s] -> [%s]\n", InFilePath, OutFilePath ) ; /* ※１ */
		}
	}

	free( FILE_KMKMST_DATA ) ;
	free( FILE_CMTMST_DATA ) ;
	closedir( Dirp );
	return( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：mainFunction                                                  */
/*  機能概要  ：メイン                                                        */
/*   第１引数 ：処理ファイル名（フルパス）                                    */
/*   第２引数 ：出力ファイル名（フルパス）                                    */
/*   第３引数 ：ラボコード                                                    */
/******************************************************************************/
int mainFunction( InFilePath, OutFilePath, LaboCode )
char *InFilePath;
char *OutFilePath;
char *LaboCode;
{
	char buf[1024];
	char field[1024];
	int  field_no; 
	char *p;
    FILE *in_fp = NULL;
    FILE *out_fp = NULL;

	char namekey[128];
	char knskka1[128];
	char knskka2[128];
	char kka2kbn[128]; 
	char kkahskcd[128];
	char hjkka[128];

	RIREKI_TABLE RirekiTable;

	/* 変換対象ファイル OPEN */
	if(( in_fp = fopen(InFilePath, "r")) == NULL ){ 
		printf("変換対象ファイルのオープンに失敗しました。[%s]\n", InFilePath) ; /* ※１ */
		return( RTN_NG );
	}
	/* 出力ファイル OPEN */
	if ((out_fp = fopen(OutFilePath, "w")) == NULL){
		printf("出力ファイルのオープンに失敗しました。[%s]\n", OutFilePath) ; /* ※１ */
		return( RTN_NG );
	}

	/* 変換対象ファイル 行数分ループ */
    while (fgets(buf, sizeof(buf), in_fp)) {
		field_no = 0; 
        // カラム毎に切り出して、構造体に入れる
        for (p = buf; *p; ) {
			p = SetValue(p, field, sizeof(field));
/*
			printf("SetValue OK [%s] [%d]\n", field, field_no); 
*/
			switch (field_no){
				case 0 :
					snprintf(RirekiTable.utkymd, 11, "%s", field);
					break ;
				case 1 :
					snprintf(RirekiTable.irino, 12, "%s", field);
					break ;
				case 2 :
					snprintf(RirekiTable.sstcd, 8, "%s", field);
					snprintf(RirekiTable.oyasstcd, 8, "%s", field);
					break ;
				case 3 :
					snprintf(RirekiTable.krtno, 41, "%s", field);
					break ;
				case 4 :
					NameKeyMake(namekey, field, strlen(field)); 
					snprintf(RirekiTable.knjnmkey, 61, "%s", namekey);
					break ;
				case 5 :
					snprintf(RirekiTable.sbtkbn, 2, "%s", field);
					break ;
				case 8 :
					snprintf(RirekiTable.age, 4, "%s", field);
					break ;
				case 9 :
					snprintf(RirekiTable.agekbn, 2, "%s", field);
					break ;
				case 11 :
					snprintf(RirekiTable.hkkdh, 11, "%s", field);
					break ;
				case 16 :
					snprintf(RirekiTable.kmkcd, 8, "%s", field);
					break ;
				case 17 :
					snprintf(knskka1, 13, "%s", field);
					break ;
				case 18 :
					snprintf(knskka2, 13, "%s", field);
					break ;
				case 19 :
					snprintf(kka2kbn, 2, "%s", field);
					break ;
				case 20 :
					snprintf(kkahskcd, 4, "%s", field);
					break ;
				case 21 :
					snprintf(RirekiTable.kkacmt1, 6, "%s", field);
					break ;
				case 22 :
					snprintf(RirekiTable.kkacmt2, 6, "%s", field);
					break ;
				case 23 :
					snprintf(RirekiTable.ijkbnm, 2, "%s", field);
					break ;
				case 24 :
					snprintf(RirekiTable.ijkbnf, 2, "%s", field);
					break ;
				case 25 :
					snprintf(RirekiTable.ijkbnn, 2, "%s", field);
					break ;
			}
			++field_no; 
        }
		/* 結果のコンパート */
		ConvKekka(knskka1, knskka2, kka2kbn[0], kkahskcd, hjkka);
		snprintf(RirekiTable.hjkka, 25, "%s", hjkka);
		/* デフォルト値の設定 */
		snprintf(RirekiTable.knsgrp, 17, "%s", "                 ");
		SetKnsgrp(RirekiTable.kmkcd, RirekiTable.knsgrp);
		snprintf(RirekiTable.rawdata, 21, "%s", "                    ");
		snprintf(RirekiTable.iriketflg, 2, "%s", " ");
		snprintf(RirekiTable.zssdino, 2, "%s", "0");
		snprintf(RirekiTable.bskkbn, 5, "%s", LaboCode);
		snprintf(RirekiTable.bsklne, 5, "%s", "    ");
		snprintf(RirekiTable.bskgok, 7, "%s", "      ");
		snprintf(RirekiTable.tbijkbnm, 2, "%s", " ");
		snprintf(RirekiTable.tbijkbnf, 2, "%s", " ");
		snprintf(RirekiTable.tbijkbnn, 2, "%s", " ");
		snprintf(RirekiTable.ksbr, 16, "               ");
		snprintf(RirekiTable.nbdo, 3, "  ");
		snprintf(RirekiTable.ykdo, 3, "  ");
		DateGetToday(RirekiTable.ksndh);
/*		
		printf("\"%-10s\",\"%-11s\",\"%-1s\",%-1s,\"%-16s\",\"%-7s\",\"%-7s\",\"%-40s\",\"%-60s\",\"%-1s\",\"%-3s\",\"%-1s\",\"%-4s\",\"%-4s\",\"%-6s\",\"%-20s\",\"%-24s\",\"%-5s\",\"%-5s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-15s\",\"%-2s\",\"%-2s\",\"%-10s%-16s\",\"%-26s\",\"%-7s\"\n",
						RirekiTable.utkymd, RirekiTable.irino, RirekiTable.iriketflg, RirekiTable.zssdino, RirekiTable.knsgrp,
						RirekiTable.kmkcd, RirekiTable.sstcd, RirekiTable.krtno, RirekiTable.knjnmkey, RirekiTable.sbtkbn,
						RirekiTable.age, RirekiTable.agekbn, RirekiTable.bskkbn, RirekiTable.bsklne, RirekiTable.bskgok,
						RirekiTable.rawdata, RirekiTable.hjkka, RirekiTable.kkacmt1, RirekiTable.kkacmt2, RirekiTable.ijkbnm,
						RirekiTable.ijkbnf, RirekiTable.ijkbnn, RirekiTable.tbijkbnm, RirekiTable.tbijkbnf, RirekiTable.tbijkbnn,
						RirekiTable.ksbr, RirekiTable.nbdo, RirekiTable.ykdo, RirekiTable.hkkdh, DEF_STAMP, RirekiTable.ksndh,
						RirekiTable.oyasstcd);
*/
		/* コンバート結果出力 */
		fprintf(out_fp, "\"%-10s\",\"%-11s\",\"%-1s\",%-1s,\"%-16s\",\"%-7s\",\"%-7s\",\"%-40s\",\"%-60s\",\"%-1s\",\"%-3s\",\"%-1s\",\"%-4s\",\"%-4s\",\"%-6s\",\"%-20s\",\"%-24s\",\"%-5s\",\"%-5s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-15s\",\"%-2s\",\"%-2s\",\"%-10s%-16s\",\"%-26s\",\"%-7s\"\n",
						RirekiTable.utkymd, RirekiTable.irino, RirekiTable.iriketflg, RirekiTable.zssdino, RirekiTable.knsgrp,
						RirekiTable.kmkcd, RirekiTable.sstcd, RirekiTable.krtno, RirekiTable.knjnmkey, RirekiTable.sbtkbn,
						RirekiTable.age, RirekiTable.agekbn, RirekiTable.bskkbn, RirekiTable.bsklne, RirekiTable.bskgok,
						RirekiTable.rawdata, RirekiTable.hjkka, RirekiTable.kkacmt1, RirekiTable.kkacmt2, RirekiTable.ijkbnm,
						RirekiTable.ijkbnf, RirekiTable.ijkbnn, RirekiTable.tbijkbnm, RirekiTable.tbijkbnf, RirekiTable.tbijkbnn,
						RirekiTable.ksbr, RirekiTable.nbdo, RirekiTable.ykdo, RirekiTable.hkkdh, DEF_STAMP, RirekiTable.ksndh,
						RirekiTable.oyasstcd);

    }
    fclose(in_fp);
    fclose(out_fp);

    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：SetKnsgrp                                                     */
/*  機能概要  ：検査グループを設定する                                        */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int SetKnsgrp(char *kmkcd, char *knsgrp)
{
	int				cnt ;
	STRUCT_KMKMST	*mp ;			/* メモリーポインター */
		
	mp = ( STRUCT_KMKMST * )FILE_KMKMST_DATA;
	for( cnt=0 ; cnt<CNT_KMKMST ; cnt++ ){
        if( strcmp( kmkcd, mp[cnt].kmkcd ) == 0 ){
            snprintf( knsgrp, 18, "%s", mp[cnt].knsgrp ) ;
            break ;
        }
	}

	return( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：ConvKekka                                                     */
/*  機能概要  ：表示結果の取得                                                */
/*  入    力  ：                                                              */
/*   第１引数 ：char    *knskka1;                                             */
/*   第２引数 ：char    *knskka2;                                             */
/*   第３引数 ：char    kka2kbn;                                              */
/*   第４引数 ：char    *kkahskcd;                                            */
/*   第５引数 ：char    *hjkka;                                               */
/*  出    力  ：                                                              */
/*   第５引数 ：char    *hjkka;                                               */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int ConvKekka(char *knskka1, char *knskka2, char kka2kbn, char *kkahskcd, char *hjkka)
{
	char    buf_kka[256] ;
	char    buf_hsk[256] ;
	int     num_cmt ;

	memset( buf_kka, 0x00, sizeof( buf_kka )) ;
	memset( buf_hsk, 0x00, sizeof( buf_hsk )) ;
    if( kka2kbn == '0' ){
		/* 結果２区分が０の場合、コメント結果 */
		StringTrim( buf_kka, knskka2 ) ;
		num_cmt = atoi( buf_kka ) ;
		snprintf( hjkka, 25, "*%d", num_cmt ) ;
		/* コメントマスタに結果値が設定されている場合はそれに置き換える */
		/* 設定されていない場合はそのまま                               */
		ConvCmtKekka( buf_kka, hjkka);
	} else {
		StringTrim( buf_kka, knskka1 ) ;
		snprintf( hjkka, 25, "%s", buf_kka ) ;
	}
    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：ConvCmtKekka                                                  */
/*  機能概要  ：コメントマスタに結果値が設定されている場合はそれに置き換える  */
/*              設定されていない場合はそのまま                                */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int ConvCmtKekka(char *cmcd, char *hjkka)
{
	int				cnt ;
	char			buf_kka[256] ;
	char 			buf_cmcd[256] ;
	STRUCT_CMTMST	*mp ;			/* メモリーポインター */
		
	mp = ( STRUCT_CMTMST * )FILE_CMTMST_DATA;
	for( cnt=0 ; cnt<CNT_CMTMST ; cnt++ ){
		StringTrim( buf_cmcd, mp[cnt].cmcd ) ;
        if( strcmp( cmcd, buf_cmcd ) == 0 ){
			StringTrim( buf_kka, mp[cnt].kekka ) ;
            snprintf( hjkka, 25, "%s", buf_kka ) ;
            break ;
        }
	}

	return( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：GetKmkFile                                                    */
/*  機能概要  ：検査グループ取得用ファイルの内容取得                          */
/*              マスタファイルは日次で出力してくれる                          */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int GetKmkFile()
{
	int				rtc;
	int				cnt;
	char			buf[1024];
	char			Path[1024];
	char			field[1024];
	int				field_no; 
	char			*p;
    FILE			*fp = NULL;
	STRUCT_KMKMST	*mp;        /* メモリーポインター */

	sprintf( Path, "%s/%s", WORK_DIR_PATH, FILE_KMKMST ) ;
	fp = fopen( Path, "r");
	if( fp == NULL ) {
		printf("検査グループ取得用ファイルのオープンに失敗しました。[%s]\n", Path) ; /* ※１ */
		return( RTN_NG );
	}

	CNT_KMKMST = 0;
	memset( buf,0,1024 );
	while( fgets( buf, 1024, fp ) != NULL ) {
		++CNT_KMKMST;
	}

	/* メモリ領域の確保 */
	FILE_KMKMST_DATA = ( STRUCT_KMKMST * )malloc(sizeof( STRUCT_KMKMST ) * CNT_KMKMST );
	if( FILE_KMKMST_DATA == NULL ){
		printf("メモリ領域の確保に失敗しました。[GetKmkFile]\n" ) ; /* ※１ */
		fclose ( fp ) ;
		return( RTN_NG );
	}
	rewind(fp);

	memset(( char * )FILE_KMKMST_DATA,0x00, ( sizeof( STRUCT_KMKMST ) * CNT_KMKMST ));

	/* メモリの先頭ポインター */
	mp = ( STRUCT_KMKMST * )FILE_KMKMST_DATA;
	cnt = 0 ;
	/* 変換対象ファイル 行数分ループ */
    while (fgets(buf, sizeof(buf), fp)) {
		field_no = 0; 
        /* カラム毎に切り出して、構造体に入れる */
        for (p = buf; *p; ) {
			p = SetValue(p, field, sizeof(field));
			switch (field_no){
				case 0 :
					snprintf(mp[cnt].kmkcd, 8, "%s", field) ;
					break ;
				case 1 :
					snprintf(mp[cnt].knsgrp, 17, "%s", field) ;
					break ;
			}
			field_no++;
		}
		cnt++;
	}
	fclose ( fp ) ;
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：GetCmtFile                                                    */
/*  機能概要  ：コメントマスタ取得用ファイルの内容取得                        */
/*              マスタファイルは日次で出力してくれる                          */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int GetCmtFile()
{
	int				rtc;
	int				cnt;
	char			buf[1024];
	char			Path[1024];
	char			field[1024];
	int				field_no; 
	char			*p;
    FILE			*fp = NULL;
	STRUCT_CMTMST	*mp;        /* メモリーポインター */

	sprintf( Path, "%s/%s", WORK_DIR_PATH, FILE_CMTMST ) ;
	fp = fopen( Path, "r") ;
	if( fp == NULL ) {
		printf("コメントマスタ取得用ファイルのオープンに失敗しました。[%s]\n", Path) ; /* ※１ */
		return ( RTN_NG ) ;
	}

	CNT_CMTMST = 0;
	memset( buf,0,1024 );
	while( fgets( buf, 1024, fp ) != NULL ) {
		++CNT_CMTMST;
	}

	/* メモリ領域の確保 */
	FILE_CMTMST_DATA = ( STRUCT_CMTMST * )malloc(sizeof( STRUCT_CMTMST ) * CNT_CMTMST );
	if( FILE_CMTMST_DATA == NULL ){
		printf("メモリ領域の確保に失敗しました。[GetCmtFile]\n" ) ; /* ※１ */
		fclose ( fp ) ;
		return( RTN_NG );
	}
	rewind(fp);

	memset(( char * )FILE_CMTMST_DATA,0x00, ( sizeof( STRUCT_CMTMST ) * CNT_CMTMST ));

	/* メモリの先頭ポインター */
	mp = ( STRUCT_CMTMST * )FILE_CMTMST_DATA;
	cnt = 0 ;
	/* 変換対象ファイル 行数分ループ */
    while (fgets(buf, sizeof(buf), fp)) {
		field_no = 0; 
        /* カラム毎に切り出して、構造体に入れる */
        for (p = buf; *p; ) {
			p = SetValue(p, field, sizeof(field));
			switch (field_no){
				case 0 :
					snprintf(mp[cnt].cmcd, 6, "%s", field) ;
					break ;
				case 1 :
					snprintf(mp[cnt].kekka, 13, "%s", field) ;
					break ;
			}
			field_no++;
		}
		cnt++;
	}
	fclose ( fp ) ;
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名  ：NameKeyMake                                                   */
/*  機能概要  ：患者名キー作成                                                */
/*  入    力  ：                                                              */
/*   第１引数 ：char    kan_name[]; : S-JIS 患者カナ氏名                      */
/*   第２引数 ：int     len;        : S-JIS 患者カナ氏名length                */
/*  出    力  ：                                                              */
/*   第１引数 ：char    name_key[]; : S-JIS 患者名キー                        */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
int		NameKeyMake( name_key, kan_name, len )
char	name_key[];		/* [O] 患者名キー */
char	kan_name[];		/* [I] 患者名 */
int		len;			/* [I] 患者名length */
{
	int				i,j;
	unsigned char	name[61];
	unsigned char	keyj[61];

	memset( keyj, 0x00, sizeof( keyj ));
	strncpy( name, kan_name, len );
	j = 0;
	for	(i=0;i<len;i++) {
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
/*  関 数 名  ：SetValue                                                      */
/*  機能概要  ：ＣＳＶの読込                                                  */
/*              一行の中のデータは ,(カンマ)で区切る。行の終りは改行。        */
/*              データがカンマやダブルクォートを含む場合は                    */
/*              "(ダブルクォート)で囲む。                                     */
/*              データの中のダブルクォートはそれを                            */
/*              ダブルクォート2個("")で置き換える。                           */
/******************************************************************************/
char *SetValue(char *p, char *field, int size) {
    if (*p == '"') {
        /* ここでのインクリメントは
         * 最後のインクリメントではポインタが＋２になる(評価された場合のみ)
         * *p != '"'が0になった場合のみ *(++p) == '"'が実行される
         * これはダブルクォート連続の時の対策
         */
        while (*(++p) && *p != '\n' && (*p != '"' || *(++p) == '"')) {
            if (--size > 0) {
                *(field++) = *p;
            }
        }
    }
    // ここの部分は""で囲まれていない部分が通るようになっている
    for ( ; *p && *p != ',' && *p != '\n'; p++) {
        if (--size > 0) {
            *(field++) = *p;
        }
    }
    *field = '\0';
    return *p ? (p + 1) : p;
}

/******************************************************************************/
/*      関数名          ：DateGetToday()                                      */
/*      機能概要        ：システム日付を取得する                              */
/*      入力                                                                  */
/*       第１引数       ：char* date DB2タイムスタンプ型の日付の文字列        */
/*      出力                                                                  */
/*       第１引数       ：char* date システム日付(DB2タイムスタンプ型)        */
/*       正常：TRUE                                                           */
/*       異常：FALSE                                                          */
/******************************************************************************/
int DateGetToday(char *date)
{
	time_t now = time(NULL);
    struct tm *tm;

	time(&now);
    tm = localtime(&now);
	sprintf( date, "%4.4d-%2.2d-%2.2d-%2.2d.%2.2d.%2.2d.000000", 
					tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec ) ;

    return( RTN_OK );
}

/******************************************************************************/
/*      関数名          ：StringTrim()                                        */
/*      機能概要        ：指定文字列の前後のスペースを取り除いて              */
/*                        文字列をコピーする                                  */
/*      入力                                                                  */
/*       第２引数       ：char* トリム前の文字列                              */
/*      出力                                                                  */
/*       第１引数       ：char* トリム後の文字列                              */
/******************************************************************************/
void StringTrim(char *dst, char *src) {
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

	return ;
}

/******************************************************************************/
/*  関 数 名  ：PutErrLog                                                     */
/*  機能概要  ：コメントマスタ取得用ファイルの内容取得                        */
/*  入    力  ：                                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：RTN_OK       正常終了                                         */
/*            ：RTN_NG       異常終了                                         */
/******************************************************************************/
void PutErrLog()
{
	int				rtc;
	char			Path[1024];
	char			*p;
    FILE			*fp = NULL;

	sprintf( Path, "%s/%sRirekiConv.log", LOG_DIR, NAME_ERRLOG ) ;
	fp = fopen( Path, "w") ;
	if( fp == NULL ) {
		printf("エラー送信用ログファイルのオープンに失敗しました。[%s]\n", Path) ; /* ※１ */
		return ;
	}

	fprintf( fp, "ERROR : 履歴ファイルのコンバート処理でエラーが発生しました。\n" ) ;

	fclose ( fp ) ;
	return ;
}
