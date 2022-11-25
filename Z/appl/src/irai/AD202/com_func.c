/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：com_func.c                                                   */
/*   概      要：患者情報展開                                                 */
/*	 OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      OS EUC->SJIS対応                   */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include "AD202.h"

/*:KH-------------------------------------------------------------------------*/
/*:K  関数名   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  機能概要 : ＄環境変数を展開する                                         */
/*----------------------------------------------------------------------------*/
/*:I  入力     : char    *src_cp  : 展開前文字列                              */
/*:O  出力     : 無し             : 無し                                      */
/*:R  戻り値   : char *           : 展開後文字列                              */
/*:C  特記事項 :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char		*src_cp;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];	// 関数名称
static char	value[256];     			/* 展開後文字列 */
    char	*dst_cp;        			/* 展開後文字列 */
    char	buf[256];       			/* ＄環境変数 */
    char	*env_cp;        			/* ＄環境変数 */

	strcpy( func_nm, "EnvRef" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0 
                && *src_cp != ' ' && *src_cp != '\t' 
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( value );
}
/*:KH-------------------------------------------------------------------------*/
/*:K  関数名   : GetIniFile                                                     */
/*----------------------------------------------------------------------------*/
/*:A  機能概要 : 設定ファイルから値を取得する                                 */
/*----------------------------------------------------------------------------*/
/*:I  入力     : char    *section : セクション名                              */
/*             : char    *key     : キー名                                    */
/*             : char    *profile : 設定ファイル名                            */
/*:O  出力     : 無し             : 無し                                      */
/*:R  戻り値   : char *           : キー値（文字列）                          */
/*:C  特記事項 :                                                              */
/*----------------------------------------------------------------------------*/
char	*GetIniFile( section, key, profile )
char		*section;
char		*key;
char		*profile;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		// 関数名称
static char	value[256];						/* 環境変数値 */
    FILE	*fp;            				/* FILEポインタ */
    char	buf[256];       				/* 読込みバッファ */
    int		sec_len;        				/* セクション名長 */
    int		key_len;        				/* キー名長 */
    int		value_len;      				/* キー値長 */
    int		i;              				/* 添え字 */

	strcpy( func_nm, "GetIniFile" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*==========================*/
    /*  設定ファイルのオープン  */
    /*==========================*/
    if(( fp = fopen( EnvRef( profile ), "rt" )) == NULL ) {
        printf( "FOPEN ERROR:%s\n", profile );
        return( NULL );
    }

    /*==================*/
    /*  セクション検索  */
    /*==================*/
    sec_len = strlen( section );
    key_len = 0;
    buf[sizeof( buf ) - 1] = 0;
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) {
            for( i++; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( strncmp( &buf[i], section, sec_len ) == 0 ) {
                for( i += sec_len; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                if( buf[i] == ']' ) {
                    /*================*/
                    /* 見つかった場合 */
                    /*================*/
                    key_len = strlen( key );
                    break;
                }
            }
        }
    }
    /*======================*/
    /* 見つからなかった場合 */
    /*======================*/
    if( key_len <= 0 ) {
        fclose( fp );
        return( NULL );
    }

    /*============*/
    /*  キー検索  */
    /*============*/
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) break;
        if( strncmp( &buf[i], key, key_len ) == 0 ) {
            for( i += key_len; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( buf[i] == '=' ) {
                /*================*/
                /* 見つかった場合 */
                /*================*/
                for( i++; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                strcpy( value, &buf[i] );
                value_len = strlen( value );
                if( value[value_len - 1] == '\n' ) {
                    value[value_len - 1] = 0;
                }
                fclose( fp );
                return( EnvRef( value ) );
            }
        }
    }
    /*======================*/
    /* 見つからなかった場合 */
    /*======================*/
    fclose( fp );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( NULL );
}

/******************************************************************************/
/*  関 数 名  ：DaemonCheckProc                                               */
/*  機能概要  ：デーモン重複起動チェック                                      */
/*  入    力  ：                                                              */
/*   第１引数 ：int		argc	: パラメタ数                                  */
/*   第２引数 ：char	*argv[]	: パラメタリスト                              */
/*  出    力  ：なし                                                          */
/*  復帰情報  ： INT                                                          */
/*               RTN_OK     : 成功                                            */
/*               RTN_NG     : 失敗                                            */
/******************************************************************************/
int		DaemonCheckProc( argc, argv )
int			argc;
char		*argv[];
{
	int		ret = RTN_OK;			/* 復帰値 */
	int		cnt;					/* カウント */
	char	func_nm[MYAPP_LEN_FNCNM+1];			/* 関数名称	 */
	char	buf[128];				/* 読込みバッファ */
	char	cmd[128];				/* コマンド */
	char	tmp[80];				/* 作業ファイル */
	FILE	*tfp;					/* FILEポインタ */

	strcpy( func_nm, "DaemonCheckProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* コマンド実行 */
	sprintf( tmp, "/tmp/%s.%d.tmp", stcPRM.myp_exefile, getpid() );
	sprintf( cmd, "ps -e | grep %s | grep -v grep | wc > ", stcPRM.myp_exefile);
	strcat( cmd, tmp );
	system( cmd );

	// TRACE
	sprintf( G_msg, "重複起動チェックでコマンド[%s]を実行", cmd );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	/* 起動数の読込み */
	if( (tfp = fopen( tmp, "r" )) == NULL ) {
		// ERROR
		sprintf( G_msg, 
			"重複起動チェックコマンド結果ファイル オープンエラー", tmp );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		return	RTN_NG;
	}
	if( fgets( buf, sizeof( buf ), tfp ) == NULL ) {
		strcpy( buf, "0");
		// ERROR
		sprintf( G_msg, 
			"重複起動チェックで実行したコマンド結果を取得できない" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	fclose( tfp );
	unlink( tmp );

	/* 起動数チェック */
	cnt = 0;
	sscanf( buf, "%d", &cnt );

	// TRACE
	sprintf( G_msg, "重複起動チェックで%s"
		, (cnt>1)?"重複している" :"重複していない" );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	if( cnt > 1 ) {
		return( RTN_NG );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return RTN_OK;
}

/******************************************************************************/
/*  関 数 名  ：sj2euc                                                        */
/*  機能概要  ：S-JIS => EUC 変換                                             */
/*  入    力  ：                                                              */
/*   第１引数 ： char	bufin[]		: 入力文字列 (SJIS)                       */
/*   第２引数 ： int	len			: 出力文字列長                            */
/*  出    力  ：                                                              */
/*   第１引数 ： char	bufot[]		: 出力文字列 (EUC)                        */
/*  復帰情報  ： RTN_OK				: 正常終了(読込サイズ)                    */
/*               RTN_NG				: 失敗                                    */
/******************************************************************************/
int     sj2euc( bufot, bufin, len )
char		bufot[];	
char		bufin[];	
int			len;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int	ret;
	size_t  w_szi;
	size_t  szi;
	size_t  szo;
	char	str_in[MYAPP_MAX_CHAR+1];
	char	str_ot[MYAPP_MAX_CHAR+1];
	char	*pstr_in = str_in;
	char	*pstr_ot = str_ot;
	
	strcpy( func_nm, "sj2euc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// 1.01 SJIS 環境で実行するためコード変換は行わない
    memcpy( bufot, bufin, len - 1 );
    return( RTN_OK );

	szi = w_szi = strlen( bufin );
	szo = sizeof( str_ot ) - 1;
	memset( str_in, 0x00, sizeof( str_in ) );
	memset( str_ot, 0x00, sizeof( str_ot ) );
	memcpy( str_in, bufin, szi );
	ret = iconv( G_ic, &pstr_in, &szi, &pstr_ot, &szo );

	// ERROR
	if( ret == -1 ){
		sprintf( G_err, "%d", errno );
		sprintf( G_msg, "[%d]byte文字列の[%d]byte目コード変換中に"
				"エラーが発生しました。"
				,w_szi, w_szi - szi );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	memcpy( bufot, str_ot, len - 1 );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：to_csv                                                        */
/*  機能概要  ：CSV形式のデリミッタ付加                                       */
/*            ：colをrtrim後、'col'| と編集して buf に繋げて戻す              */
/*  入    力  ：                                                              */
/*   第１引数 ： char   delim[];  : デリミッタ                                */
/*   第２引数 ： char   buf[];    : 付加先項目                                */
/*   第３引数 ： char   col[];    : デリミッタをつけて付加する項目            */
/*   第４引数 ： int    len;      : 付加先項目最大サイズ                      */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK             : 正常                                    */
/*               RTN_NG             : エラー                                  */
/******************************************************************************/
int		to_csv( delim, len, msg, col )
char		*delim;
int			len;
char		*msg;
char		*col;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int		wc, bwc;
	int		ret=RTN_OK;

	strcpy( func_nm, "to_csv" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// rtrim( col )
	for( wc=strlen( col ); wc > 1; --wc ){
		if( col[wc - 1] != ' ' ){
			break;
		}
	}

	// ログのMSG領域より大きい場合は処理を抜ける
	bwc=strlen(msg);
	if( wc + bwc >= len -3 ){
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, "csv編集にて領域を超えました。"
				, func_nm, __FILE__, __LINE__ );
		return( RTN_NG );
	}

	// EDIT
	msg[bwc]='\'';
	memcpy(&msg[bwc+1],col,wc);
	msg[bwc+wc+1]='\'';

	if( &delim[0] != 0x00 ){
		msg[bwc+wc+2]=delim[0];
		msg[bwc+wc+3]='\0';
	} else {
		msg[bwc+wc+2]='\0';
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/*****************************************************************
	名称  :	和暦・西暦変換

	概要  :	和暦から西暦に変換する
		ｺｰﾄﾞ管理ﾏｽﾀに元号の管理をしている
	注意　: 元号と編集前の年月日が正しいことが前提

	構文  :	char	*Lwa_ymd( ymd10, gengou, ymd )
	引数  :	(out)	char	ymd10[];	編集後(YYYY/MM/DD)
		(in)	char	gengou[];	
			元号
			' ':西暦
			 M :明治 "1868/09/08", "1912/07/29"
			 T :大正 "1912/07/30", "1926/12/24", "T"
			 S :昭和 "1926/12/25", "1989/01/07", "S"
	                 H :平成 "1989/01/08", "9999/12/31", "H"
		(in)	char	ymd[];		編集前(YYYYMMDD)

	ﾘﾀ-ﾝ値:	ymd10の先頭ｱﾄﾞﾚｽ
		ymd10=NULLの場合は内部ｴﾘｱの文字列先頭ｱﾄﾞﾚｽ
*****************************************************************/
int		wa2ymd( ymd10, gengou, ymd )
char		ymd10[];					/* 編集後(YYYY/MM/DD)	*/
char		gengou[];					/* 元号			*/
char		ymd[];						/* 編集前(YYYYMMDD)	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/
	int		ret;

	char	wk_ymd8[10];
	char	wk_yy[10];
	char	wk_mmdd[10];
	int	i,j,k;
	int	add_yy;

	/* 初期設定	*/
	strcpy( func_nm, "wa2ymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* 西暦ならば処理終了 */
	if( gengou[0] == ' ' ){
		sprintf( ymd10,	"%.4s-%.2s-%.2s",
			ymd, &ymd[4], &ymd[6] );
		return( RTN_OK );
	}

	/* 日付の獲得	*/
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
	/* 元号の開始年月を求める	*/
		/* 本来はDBが望ましい。とりあえずON */
		switch  ( gengou[0] ) {
			case 'M' :		/* 明治 */
				add_yy = 1868;
				break;
			case 'T' :		/* 大正 */
				add_yy = 1912;
				break;
			case 'S' :		/* 昭和 */
				add_yy = 1926;
				break;
			case 'H' :		/* 平成 */
				add_yy = 1989;
				break;
			default:
				break;
		}
		/* 開始西暦を求める	*/
		if( add_yy != 0 ){
			--add_yy;
		}
	sprintf( wk_ymd8, "%04d%s", atoi( wk_yy ) + add_yy, wk_mmdd );
	memset( ymd10, '\0', sizeof( ymd10 ));
	sprintf( ymd10,	"%.4s-%.2s-%.2s",
		wk_ymd8, &wk_ymd8[4], &wk_ymd8[6] );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  関 数 名  ：ValidDate                                                     */
/*  機能概要  ：日付、時刻　妥当性チェック                                    */
/*  入    力  ：                                                              */
/*   第１引数 ： int	mode		: 編集されている日付関連項目の型          */
/*   第２引数 ： char	indate[]	: 入力日付時刻                            */
/*  出    力  ：                                                              */
/*  復帰情報  ： RTN_OK				: 正常                                    */
/*               RTN_NG				: エラー                                  */
/******************************************************************************/
int     ValidDate( mode, indate )
int			mode;
char		indate[];	
{
    static	int t[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int		y, m, d, h, mi, s;
    int		i;
	char	w_yyyy[5];
	char	w_mm[3];
	char	w_dd[3];
	char	w_hh[3];
	char	w_mi[3];
	char	w_ss[3];

	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	/* 初期設定	*/
	strcpy( func_nm, "ValidDate" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( w_yyyy, "0000" );	y = strlen( w_yyyy ) - 1;
	strcpy( w_mm, 	"00" );		m = strlen( w_mm ) - 1;
	strcpy( w_dd, 	"00" );		d = strlen( w_dd ) - 1;
	strcpy( w_hh, 	"00" );		h = strlen( w_hh ) - 1;
	strcpy( w_mi, 	"00" );		mi = strlen( w_mi ) - 1;
	strcpy( w_ss, 	"00" );		s = strlen( w_ss ) - 1;

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
	if(( h > 24 ) || ( mi > 60 ) || ( s > 60 )){
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
		if(( m == 2 ) && ( y%4 == 0 )){ 			// 閏年候補
			if(( y%100 != 0 ) || ( y%400 == 0 )){	// 閏年決定
				if( d == 29 ){
					// OK
					return( RTN_OK );
				}
			}
		}
	}
	// 日付エラー 

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_NG );
}

/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *   	共有メモリ構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int		sFncShmCrt ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	/* 初期設定	*/
	strcpy( func_nm, "sFncShmCrt" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//	取得
	stcShm->shm_Id = shmget ( (key_t)stcShm->shm_Key, 
					MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
	if ( stcShm->shm_Id < 0 ) {
		//	異常終了	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "共有メモリの操作(shmget)に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "共有メモリの操作(shmat)に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "共有メモリの操作(shmdt)に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()				 								  */
/*  機能概要　：共有メモリ取得								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *   	共有メモリ構造体                          */
/*　 第２引数 ：int *   				値							 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int		sFncShmGet ( stcShm, pshmData )
struct		SHM		*stcShm;
int			*pshmData ;
{
	int		*shmData ;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	/* 初期設定	*/
	strcpy( func_nm, "sFncShmGet" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//	アタッチ	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "共有メモリの操作(shmat)に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "共有メモリの操作(shmdt)に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()				 								  */
/*  機能概要　：共有メモリ削除								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *   	共有メモリ構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int		sFncShmDel ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* 関数名称	*/

	/* 初期設定	*/
	strcpy( func_nm, "sFncShmDel" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//	削除	
	if ( shmctl ( stcShm->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "共有メモリの操作(shmctl)に失敗しました。" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( RTN_OK ) ;
}
/** End of File ***************************************************************/
