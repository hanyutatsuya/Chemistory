/* 改訂履歴
 2020.05.26 #01 小島  下記の"KEKKAERR_PATH"の設定を追加

*/

#define  ONLINE_PATH         "/apdata/today/file/KEA00/kea00ap/ZS050"
#define  IRAINEW_PATH        "/apdata/today/file/KEA00/kea00ap/ZS050/irai_file"
#define  IRAIEND_PATH        "/apdata/today/file/KEA00/kea00ap/ZS050/irai_file/end"
#define  KEKKATMP_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/kekka_onl/new"
#define  KEKKAEND_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/kekka_onl/end"
#define  KEKKAERR_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/kekka_onl/err"
#define  SATKEKKA_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/kekka_file/new"
#define  MSTFILE_PATH        "/apdata/today/file/KEA00/kea00ap/ZS050/mst_file"

#define  LANEKEKKA_PATH      "/apdata/today/file/KEA00/kea00ap/ZS050/lane/result/new"
#define  LANEKEKEND_PATH     "/apdata/today/file/KEA00/kea00ap/ZS050/lane/result/end"
#define  LANEIRAI_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/lane/request/end"
#define  LANESTRYNEW_PATH    "/apdata/today/file/KEA00/kea00ap/ZS050/lane/stray/new"
#define  LANESTRYMV_PATH     "/apdata/today/file/KEA00/kea00ap/ZS050/lane/stray/new2"
#define  LANESTRYEND_PATH    "/apdata/today/file/KEA00/kea00ap/ZS050/lane/stray/end"
#define  LANERSREQNEW_PATH   "/apdata/today/file/KEA00/kea00ap/ZS050/lane/result_req/new"
#define  LANERSREQEND_PATH   "/apdata/today/file/KEA00/kea00ap/ZS050/lane/result_req/end"

#define  DBGFILE_PATH        "/apdata/aplog"

#define  IRAI_PREFIX         "OD_"
#define  SKNIRAI_SUFFIX      "dat_01"
#define  SKNIRAIEND_SUFFIX   "dat_001"
#define  CTLKEKTMP_PRFIX     "QCK_"
#define  DATKEKTMP_PRFIX     "KEK_"

#define  NEWFL_SUFFIX        "dat"
#define  ENDFL_SUFFIX        "end"
#define  ERRFL_SUFFIX        "err"

#define  ME_KUBUN            "Z050"


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

/* 検査オーダーのファイル (CSV 形式) に含まれる属性情報の位置               */
#define FLDIDX_SC                 (40)  /* 身長 (cm)                        */
#define FLDIDX_TJ                 (41)  /* 体重                             */
#define FLDIDX_TJTNI              (42)  /* 体重区分                         */
#define FLDIDX_TNTME              (50)  /* 蓄尿時間                         */
#define FLDIDX_TNTNI              (51)  /* 蓄尿時間区分                     */
#define FLDIDX_TNRYO              (52)  /* 蓄尿量                           */
#define FLDIDX_TNRYOTNI           (53)  /* 蓄尿量区分                       */
#define FLDIDX_SBTKBN             (43)  /* 性別区分                         */
#define FLDIDX_AGE                (46)  /* 年齢                             */
#define FLDIDX_AGEKBN             (47)  /* 年齢区分                         */

/* 単位等を示す項目に格納される識別子                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* 蓄尿時間: 時間単位               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* 蓄尿時間: 分単位                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* 蓄尿時間: 時間単位不明           */
#define _VALUE_TNRYO_MILLILITER ('0')   /* 蓄尿量: ミリ リットル単位        */
#define _VALUE_TNRYO_LITER      ('1')   /* 蓄尿量: リットル単位             */
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


/* システムパラメータ格納構造体 */
struct appEnv {
    int     shm_Id ;
    key_t   shm_Key ;
    char    udate[11];
    short   lineno;
    char    nyubi_km[7 +1];
    short   nyubi_ch;
    char    youkets_km[7 +1];
    short   youkets_ch;
    char    oudan_km[7 +1];
    short   oudan_ch;
    char    seisyk_km[7 +1];
    short   seisyk_ch;
};

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0 */

typedef struct {
    char    path[101];                                /* 結果一時ファイルのフルパス */
    char    fname[51];                                /* 結果一時ファイルのファイル名 */
    char    rackid[13];                               /* 結果一時ファイル名から取得したラックID */
    short   pos;                                      /* 結果一時ファイル名から取得したラック内位置 */
    short   chnum;                                    /* 結果一時ファイル名から取得したチャネルNo. */
    char    irfnm[51];                                /* 該当する依頼ファイル名 */
    char    kengrp[16 +1];                            /* 特定した依頼情報からの検査グループ */
    int     kmcode;                                   /* 特定した依頼情報からの項目コード */
    char    kessei_km[7 +1];                          /* 特定した依頼情報からの血清項目コード */
    short   c_kensa;                                  /* 特定した依頼情報からの検査回数 */
    char    kensaphs[1 +1];                           /* 特定した依頼情報からの検査工程区分 */
    char    usercode[7 +1];                           /* 特定した依頼情報からの施設コード */
    char    ino[11 +1];                               /* 特定した依頼情報からの依頼書No. */
    char    kenno[13 +1];                             /* 特定した依頼情報からの検体No. */
    char    line_kenno[11 +1];                        /* Line用依頼情報内の検体No. */
    char    kenid[30 +1];                             /* 結果一時ファイルから取得した検体ID (RackID+POS) */
    char    zaicode[4 +1];                            /* 特定した依頼情報からの材料コード */
    char    sex[1 +1];                                /* 特定した依頼情報からの性別コード */
    char    rstime[21];                               /* 結果一時ファイルから取得した結果受信日時 */
    short   mecd;                                     /* 結果一時ファイルから取得した分析機No. */
    int     meseqno;                                  /* 結果一時ファイルから取得した分析機SEQNo. */
    char    kekka[12 +1];                             /* 結果一時ファイルから取得した測定結果(丸め後) */
    char    raw[12 +1];                               /* 結果一時ファイルから取得した測定結果 */
    char    errcd1[2 +1];
    char    errcd2[30 +1];
    int     ctlno;
    short   qcflg;
    short   sts;                                      /* 1:測定項目揃い済、2:希釈CHK済、3:RNG CHK済み */
    char    meerrsts[2 +1];
    short   meerrprc;
    char    kisyak_sts[1 +1];
    short   kisyak_err;
    char    cksts[3];
    short   f_saiken;                                 /* 再検実施フラグ */
    short   f_calc;
    short   f_kessei;                                 /* 血清項目フラグ (1:血清, 2:生食) */
    int     clcptr;
} KEKFL_STR;


/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
typedef struct {
    char    rackid[13];
    short   pos;
    int     kmcode;
    char    kenno[13 +1];
    char    kekka[12 +1];
} CALCKM_STR;


/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
/* チャネルマスタ格納構造体 */
typedef struct {
    char    mekbn[4 +1];
    short   chnum;
    char    chname[16 +1];
    int     kmcode;
} CHLMST;

/* 計算項目マスタ格納構造体 */
typedef struct {
    char    kengrp[16 +1];
    int     kmcode;
    char    usercode[7 +1];
    char    zaicode[4 +1];
    char    calc[128 +1];
} CALCMST;

/* 希釈倍率マスタ格納構造体 */
typedef struct {
    char    mekbn[4 +1];
    char    kengrp[16 +1];
    int     kmcode;
    char    kisykbai[15 +1];
    char    kisyk_low[20 +1];
    double  dbksk_low;
    char    kisyk_hi[20 +1];
    double  dbksk_hi;
    char    kisyk_kbn[8 +1];
} KISYKMST;

/* 範囲チェックマスタ格納構造体 */
typedef struct {
    char    kengrp[16 +1];
    int     kmcode;
    char    zaicode[4 +1];
    char    usercode[7 +1];
    char    sex[1 +1];
    short   uplow;
    short   valkbn;
    char    rng_hi[20 +1];
    double  dbrng_hi;
    char    rng_low[20 +1];
    double  dbrng_low;
} RNGMST;

/* 関連項目マスタ格納構造体 */
typedef struct {
    int     kmcode;
    int     kanrenkm;
} KANRENMST;

/* 分析機ステータス格納構造体 */
typedef struct {
    char    zscode[2 +1];
    char    trcode[1 +1];
    short   procf;
    char    skncond[1 +1];
    int     pri;
} MESTSMST;

/* 項目マスタ格納構造体 */
typedef struct {
    char    kengrp[16 +1];
    int     kmcode;
    int     place;                          /* 小数点桁数 */
} KMMST;

/* コントロールマスタ格納構造体 */
typedef struct {
    short   chnum;
    char    ctlknd[20 +1];
    char    lotno[20 +1];
    char    ctrlx[12 +1];
    char    ctrlsd[12 +1];
} CTLMST;

typedef enum myFlg {
    MY_FLG_ON,
    MY_FLG_OFF
} MY_FLG ;

typedef struct stKeisanChk_tag {
    char motoKMKCD[8];
    char KMKCD[8];
    double raw;
    MY_FLG flgRawNone ;
} STKEISANCHK;

/* IF ブロック内要素分解構造体 (char** としても参照可能)                    */
struct _IFBLOCK {
    char *pszConditionLeft;             /* 条件式 (比較演算子) 左辺         */
    char *pszOperator;                  /* 条件式の比較演算子               */
    char *pszConditionRight;            /* 条件式 (比較演算子) 右辺         */
    char *pszValueTrue;                 /* 条件式が真の場合に適用する値     */
    char *pszValueFalse;                /* 条件式が偽の場合に適用する値     */
    char *pszEndOfList;                 /* この構造体を char** として参照す
                                           る場合の End Of List             */
};

