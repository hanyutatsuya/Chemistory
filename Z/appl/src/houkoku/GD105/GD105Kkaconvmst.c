static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,119,65,70,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,56,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "GD105Kkaconvmst.sqc"
/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：GD105Kkaconvmst.sqc
 *     機能概要  ：結果変換マスタアクセス関数(報告処理)
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-11                    Create
 **********************************************************************/

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include <stdio.h>
#include "GD105Kkaconvmst.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"
#include "bmllog.h"

#define	RETRY			3		// リトライ回数
#define	ERR_LOCK		-911	// デッドロック時エラーコード
#define	LOCK_WAIT_SEC	5		// スリープ単位：秒

#define	ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 33 "GD105Kkaconvmst.sqc"


/*--------------------------------------
// DBラップ変数定義
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 38 "GD105Kkaconvmst.sqc"

	char		knsgrp[16+1];
	char		kmkcd[7+1];
	char		sstcd[7+1];
	sqlint32	no;
	char		sbtkbn;
	char		age[32+1];
	char		agekbn;
	char		sc[32+1];
	char		tj[32+1];
	char		tjtni;
	char		tntme[32+1];
	char		tntni;
	char		tnryo[32+1];
	char		tnryotni;
	char		knskka1[12+1];
	char		knskka2[24+1];
	char		knskka2kbn[2+1];
	char		kkahskcd[3+1];
	char		hjkka[24+1];
	char		kaiymd[10+1];
	char		haiymd[10+1];
	char		hnktntid[8+1];
	char		ksndh[26+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 62 "GD105Kkaconvmst.sqc"



/*--------------------------------------
// DMM定義
*/
#define DMM_STRUCT	Kkaconvmst

BmlDMMInfo	KkaconvmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( sstcd ),
	DMM_SLONG( no ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_SSTRING( sc ),
	DMM_SSTRING( tj ),
	DMM_SCHAR( tjtni ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( hjkka ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * mGD105_KKACONVMST_SelAll()
 *    KKACONVMST 全レコード取得
 * ■引数
 *    [O]    Kkaconvmst** arrayOut  取得レコード配列格納領域
 *    [O]    int* numOut            取得件数
 * ■戻り値
 *    (long) HRC_SQL_NORMAL(0)      正常終了（レコードあり）
 *           HRC_SQL_NOT_FOUND(100) レコードなし
 *           HRC_SQL_ERR(-2)        DBエラー
 ******************************************************************************/
long mGD105_KKACONVMST_SelAll( Kkaconvmst** arrayOut, int* numOut )
{
	Kkaconvmst*		array = NULL;
	int				num = 0;
	int				error = 0;

	// リトライ用ループ設定
	int i;
	for (i = 0; i <= RETRY; i++) {
		error = 0;

		
/*
EXEC SQL DECLARE cur_kkaconvmst CURSOR FOR
		SELECT
			KNSGRP,
			KMKCD,
			SSTCD,
			NO,
			SBTKBN,
			AGE,
			AGEKBN,
			SC,
			TJ,
			TJTNI,
			TNTME,
			TNTNI,
			TNRYO,
			TNRYOTNI,
			KNSKKA1,
			KNSKKA2,
			KNSKKA2KBN,
			KKAHSKCD,
			HJKKA,
			KAIYMD,
			HAIYMD,
			HNKTNTID,
			KSNDH
		FROM
			KKACONVMST
		ORDER BY
			KNSGRP,
			KMKCD,
			SSTCD,
			NO
		FOR READ ONLY;
*/

#line 151 "GD105Kkaconvmst.sqc"


	    
/*
EXEC SQL OPEN cur_kkaconvmst;
*/

{
#line 153 "GD105Kkaconvmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 153 "GD105Kkaconvmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 153 "GD105Kkaconvmst.sqc"
  sqlastop(0L);
}

#line 153 "GD105Kkaconvmst.sqc"


		while( 1 ) {
			Kkaconvmst* rec;

			
/*
EXEC SQL FETCH cur_kkaconvmst INTO
				:knsgrp,
				:kmkcd,
				:sstcd,
				:no,
				:sbtkbn,
				:age,
				:agekbn,
				:sc,
				:tj,
				:tjtni,
				:tntme,
				:tntni,
				:tnryo,
				:tnryotni,
				:knskka1,
				:knskka2,
				:knskka2kbn,
				:kkahskcd,
				:hjkka,
				:kaiymd,
				:haiymd,
				:hnktntid,
				:ksndh;
*/

{
#line 181 "GD105Kkaconvmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 181 "GD105Kkaconvmst.sqc"
  sqlaaloc(3,23,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[1].sqldata = (void*)kmkcd;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[2].sqldata = (void*)sstcd;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[3].sqldata = (void*)&no;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[4].sqldata = (void*)&sbtkbn;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 33;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[5].sqldata = (void*)age;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[6].sqldata = (void*)&agekbn;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 33;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[7].sqldata = (void*)sc;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 33;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[8].sqldata = (void*)tj;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[9].sqldata = (void*)&tjtni;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 33;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[10].sqldata = (void*)tntme;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[11].sqldata = (void*)&tntni;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 33;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[12].sqldata = (void*)tnryo;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[13].sqldata = (void*)&tnryotni;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 13;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[14].sqldata = (void*)knskka1;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[15].sqldata = (void*)knskka2;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 3;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[16].sqldata = (void*)knskka2kbn;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[17].sqldata = (void*)kkahskcd;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 25;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[18].sqldata = (void*)hjkka;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 11;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[19].sqldata = (void*)kaiymd;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 11;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[20].sqldata = (void*)haiymd;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[21].sqldata = (void*)hnktntid;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[22].sqldata = (void*)ksndh;
#line 181 "GD105Kkaconvmst.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 181 "GD105Kkaconvmst.sqc"
      sqlasetdata(3,0,23,sql_setdlist,0L,0L);
    }
#line 181 "GD105Kkaconvmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 181 "GD105Kkaconvmst.sqc"
  sqlastop(0L);
}

#line 181 "GD105Kkaconvmst.sqc"


			if( SQLCODE == HRC_SQL_NOT_FOUND ) {
				break;
			}

			// ロック時のリトライ対応
			if (sqlca.sqlcode < 0) {
				// エラー発生時は領域解放してブレイク
				if (array != NULL) {
					ZbmlFree(array);
					array = NULL;
					num   = 0;
				}
				error = sqlca.sqlcode;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "mGD105_KKACONVMST_Sel",
							 __LINE__,
							 EXEFLG_SEL, "020",
							 "DBエラー発生 [sqlcode : %d]", sqlca.sqlcode ) ;
				break;
			}

			if( num % ALLOC_UNIT == 0 ) {
				array = (Kkaconvmst*)ZbmlRealloc( array, sizeof( Kkaconvmst ) * ( num + ALLOC_UNIT ) );
				memset( array + num, 0, sizeof( Kkaconvmst ) * ALLOC_UNIT );
			}

			rec = array + num++;
			ZbmlMapHostToStruct( (char*)rec, KkaconvmstArray );
		}

		
/*
EXEC SQL CLOSE cur_kkaconvmst;
*/

{
#line 212 "GD105Kkaconvmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "GD105Kkaconvmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 212 "GD105Kkaconvmst.sqc"
  sqlastop(0L);
}

#line 212 "GD105Kkaconvmst.sqc"


		// ロック時のリトライ対応
		// ロックの場合はリトライ、ロック以外のエラーはデータ無しで終了
		// リトライは５秒待ってから
		if (error == ERR_LOCK) {
			sFncPutLog( TRCKIND_ERROR, __FILE__, "mGD105_KKACONVMST_Sel", __LINE__, EXEFLG_SEL, "020",
						"ロックによるリトライ[%d]回目", i ) ;
			sleep(LOCK_WAIT_SEC);
			continue;
		}

		*arrayOut = array;
		*numOut   = num;

		return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

	// リトライ用ループ終端
	}

	// リトライしてもエラーの場合、データ無しで終了
	*arrayOut = NULL;
	*numOut   = 0;
	return HRC_SQL_NOT_FOUND;

}

/** End of File *********************************************************/
