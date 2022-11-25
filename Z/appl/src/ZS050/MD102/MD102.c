
/* 改訂履歴
 2020.05.26 #01 小島  結果一時ファイルに対して該当依頼ファイルが無い場合に、
                      同一時ファイルを"err"Dirに移動して処理を継続するよう
                      修正

*/

/******************************************************************************
* インクルード宣言                                                            *
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <math.h>
#include <stdarg.h>
#include <bml_base.h>
#include <bmlprm.h>
#include <bmllog.h>
#include <Kekka.h>
#include <MD102.h>

/******************************************************************************
* マクロ宣言                                                                  *
******************************************************************************/
#define  FLARRY_MAX               (2000)              /* 結果一時ファイルリスト格納MAX数 */
#define  MSTCHANL_MAX             (1000)              /* チャネルマスタの配列MAX数 */
#define  MSTKISYK_MAX             (10240)             /* 希釈倍率マスタの配列MAX数 */
#define  MSTRANGE_MAX             (20480)             /* 範囲チェックマスタの配列MAX数 */
#define  MSTMESTS_MAX             (200)               /* 分析機データフラグの配列MAX数 */
#define  MSTKNREN_MAX             (10240)             /* 関連項目マスタの配列MAX数 */
#define  MSTCALC_MAX              (10240)             /* 計算項目マスタの配列MAX数 */
#define  MSTKM_MAX                (10240)             /* 項目マスタの配列MAX数 */
#define  MSTCTL_MAX               (3000)              /* コントロールマスタの配列MAX数 */

#define  MYAPP_LOG_ERRCODE_NON    "00000000"
#define  DBL_EPSILON              (2.2204460492503130808473E-16)

#define  OPERATOR_LT              ('<')               /* 条件式: 未満                     */
#define  OPERATOR_GT              ('>')               /* 条件式: 越える                   */
#define  OPERATOR_EQ              ('=')               /* 条件式: 一致                     */
#define  STR_NE                   "<>"                /* 条件式: 不一致                   */
#define  MAXCNT_ITEM_IFBLOCK      (5)                 /* IF ブロック内の要素数            */
#define  _EOS                     ('\0')              /* End Of String (文字列終端記号)   */
#define  _MASK_TOUPPER            (0x00DF)            /* 半角英小文字→大文字変換のマスク */
#define  STR_BEGIN_IFBLOCK        ("IF(")             /* IF 文開始を示す文字列            */
#define  STR_BEGIN_POW            ("POW(")
#define  STR_BEGIN_LOG            ("LOG(")
#define  STR_BEGIN_LOG10          ("LOG10(")

/* 以下、 IF 文中で意味を持つ文字                                           */
#define  PARENT_BEGIN             ('(')
#define  PARENT_END               (')')
#define  SPLITTER_COMMA           (':')               /* 条件式と適用値の区切り           */

/******************************************************************************
* グローバル宣言                                                              *
******************************************************************************/
static char    LmName[25];                            /* プログラム名 */
struct stcLogMember  gstLogMem;                       /* ログ出力情報 */
struct appEnv  sAppEnv;                               /* iniファイルパラメータ格納構造体 */
static char    Temp_fpth[101];                        /* 結果一時ファイルリストを格納する一時ファイル */
KEKFL_STR      FLrec[FLARRY_MAX];                     /* 結果一時ファイルリスト格納構造体 */
static int     FLrec_cnt;                             /* 結果一時ファイルリスト格納構造体数 */
KEKFL_STR      KekFL[FLARRY_MAX];                     /* 結果作成済みのRackID,POS格納構造体 */
static int     KekFL_cnt;                             /* 結果作成済みのRackID,POS格納構造体数 */
KEKFL_STR      KekFL_tmp[FLARRY_MAX];                 /* 結果作成済みのRackID,POS格納構造体 */
static int     KekFLtmp_cnt;                          /* 結果作成済みのRackID,POS格納構造体数 */
CHLMST         MstChanl[MSTCHANL_MAX];                /* チャネルマスタ格納構造体 */
static int     MstChanl_cnt;                          /* チャネルマスタのデータ数 */
KISYKMST       MstKisyk[MSTKISYK_MAX];                /* 希釈倍率マスタ格納構造体 */
static int     MstKisyk_cnt;                          /* 希釈倍率マスタのデータ数 */
RNGMST         MstRange[MSTRANGE_MAX];                /* 範囲チェックマスタ格納構造体 */
static int     MstRange_cnt;                          /* 範囲チェックマスタのデータ数 */
MESTSMST       MstMests[MSTMESTS_MAX];                /* 分析機データフラグ格納構造体 */
static int     MstMeSts_cnt;                          /* 分析機データフラグのデータ数 */
KANRENMST      MstKnren[MSTKNREN_MAX];                /* 関連項目マスタ格納構造体 */
static int     MstKnren_cnt;                          /* 関連項目マスタのデータ数 */
CALCMST        MstCalc[MSTCALC_MAX];                  /* 計算項目マスタ格納構造体 */
static int     MstCalc_cnt;                           /* 計算項目マスタのデータ数 */
KMMST          MstKm[MSTKM_MAX];                      /* 項目マスタ格納構造体 */
static int     MstKm_cnt;                             /* 項目マスタのデータ数 */
CTLMST         MstCtl[MSTCTL_MAX];                    /* コントロールマスタ格納構造体 */
static int     MstCtl_cnt;                            /* コントロールマスタのデータ数 */
static char    gszTransfer[260 + 1];                  /* 文字列→数値 変換バッファ */
static int     DbgFlg;                                /* デバッグ出力スイッチ(0:File出力、1:標準出力) */
static char    Dbg_fpth[101];                         /* 結果一時ファイルリストを格納する一時ファイル */
FILE           *Dbg_fp;                               /* デバッグ情報出力用ファイルポインタ */


/******************************************************************************
* 関数宣言                                                                    *
******************************************************************************/
static int     initFunction(int, char **);
static int     mainFunction();
static void    endFunction();
static int     sFncChMstLoad();
static int     sFncKskMstLoad();
static int     sFncRngMstLoad();
static int     sFncMeStsMstLoad();
static int     sFncKrnMstLoad();
static int     sFncCalcMstLoad();
static int     sFncKmMstLoad();
static int     sFncCtlMstLoad();
static int     sFncGetUdate();
static void    sFncGetMemSave();
static void    sFncPutMemSave();
static void    sFncGetFilelst();
static void    sFncGetRackChPos(char *, char *, short *, short *);
static int     sFncMatchIrai(KEKFL_STR *);
static void    sFncSetFlstSts(KEKFL_STR *, int);
static void    sFncKekkaProc();
static int     sFncGetRsltTmp(KEKFL_STR *);
static void    sFncCalcKmProc(KEKFL_STR *, int);
static void    sFncMeErrorChk(KEKFL_STR *);
static void    sFncKisyakChk(KEKFL_STR *);
static void    sFncRngChkProc(KEKFL_STR *);
static void    sFncKanrenChk(KEKFL_STR *);
static void    sFncMKSatKekka();
static int     sFncWriteSatKekka(FILE *, FILE *, KEKFL_STR *);
static int     sFncWriteSaiIrai(FILE *, KEKFL_STR *);
static void    sFncCtlKekkaProc();
static void    sFncMkLineKekka();
static void    sFncRnmStray();
static void    sFncMkReSknKekka();
static void    sFncTrim(char *s);
static int     sFncShmCrt(struct appEnv *);
static int     sFncShmGet(struct appEnv *, int *);
static int     sFncShmDel(struct appEnv *);
static void    sFncPutLog(LOG_TRCKIND, char *, char *, int, char *, char *, char *, ...);

static int     chkInfoRead(int, char *,char *, char **, char *);
static int     KeisanChk(char *, KEKFL_STR *, int, char **, STKEISANCHK *);
static double  StringCal(char *);
double         StringCal_sub(char, double, double);
static char    *OperateKSNSK(char *);
static char    *_touppercase(char *);
static char    *_replace(char *, char *, char *);
static char    *GetIFBlock(char *);
static char    *_strrstr(char *, char *);
static char    *_strndup(char *, size_t);
static int     _isnumeric(char *);
struct _IFBLOCK *SplitIFBlockItems(char *);
static void    freeIFBLOCK(struct _IFBLOCK *);
static int     IsFormula(char *);

/**/
int main(int argc, char **argv)
/******************************************************************************
*  関 数 名　：main()                                                         *
*  機能概要　：メイン関数                                                     *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    int     ii, len, rtn;

    /* 実行モジュール名取得 */
    len = strlen(argv[0]);
    for(ii = (len-1) ; ii >= 0 ; ii--) {
        if(argv[0][ii] == '/')  break;
    }
    if(ii >= 0)  sprintf(LmName,"%s", &argv[0][ii+1]);
    else         sprintf(LmName,"%s", argv[0]);

    /* バックグラウンドで実行 */
    if(daemon(0, 1) < 0) {
        fprintf(stderr,"%s : Error (daemon Err[%d])\n", LmName, errno);
        exit(-1);
    }

    /* 初期処理 */
    if(initFunction(argc, argv) != 0) {
        fprintf(stderr,"%s : Error (initFunction)\n", LmName);
        goto END;
    }


    /* メイン処理 */
    rtn = mainFunction();


    /* 終了処理 */
  END:
    endFunction();

    exit(0);
}

/**/
static int initFunction(int argc, char **argv)
/******************************************************************************
*  関 数 名　：initFunction()                                                 *
*  機能概要　：初期処理                                                       *
*  入　　力　：                                                               *
*  引    数    int  argc;     (引数の数)                                      *
*              char  **argv;  (引数のポインタ)                                *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    lc_prmBuf[256], wk_buff[101];
    int     i_tmp;
    BMLPRM  *bp;

    /* 引数チェック */
    if(argc < 2) {
        fprintf(stderr,"%s : Invalid argument !!!\n", LmName);
        return(RTN_NG);
    }

    /* ログオープン */
    if(ZbmlOpenLog(argv[1]) != 0) {
        fprintf(stderr,"%s : Log open failed !!!\n", LmName);
        return(RTN_NG);
    }

    /* シグナルハンドラの設定 */
    signal(SIGINT,  endFunction);
    signal(SIGKILL, endFunction);

    /* ログ情報初期設定 */
    memset(&gstLogMem,'\0', sizeof(struct stcLogMember));
    sprintf(gstLogMem.pcLoginId,"%s", getenv("LOGNAME"));
    sprintf(gstLogMem.pcAppName,"%s", LmName);
    gstLogMem.lPid = getpid();

    /* Debug出力フラグ設定 */
    DbgFlg = 0;
    if(argc >= 3 && isdigit(argv[2][0]))  DbgFlg = atoi(argv[2]);

    /* 開始ログ出力 */
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム起動");

    /* パラメータファイルオープン */
    if(NULL == (bp = ZbmlPrmOpen(argv[1]))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータファイルのオープンに失敗しました[%s]",
                   argv[1]);
        return(RTN_NG);
    }

    /* 処理対象のラインNo.取得 */
    if(ZbmlPrmGetVal(bp, "LINENO", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[LINENO]");
        return(RTN_NG);
    }
    sAppEnv.lineno = atoi(lc_prmBuf);


    /* Debug出力先を設定 */
    Dbg_fp = stdout;
    if(DbgFlg == 0) {
        sprintf(Dbg_fpth,"%s/%d_MD102.dbg", DBGFILE_PATH, sAppEnv.lineno);
        if(NULL == (Dbg_fp = fopen(Dbg_fpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "initFunction", __LINE__, EXEFLG_NON,
                MYAPP_LOG_ERRCODE_NON, "デバッグファイルのオープンに失敗しました[%s]", Dbg_fpth);
            return(RTN_NG);
        }
    }


    /* 共有メモリキー */
    if(ZbmlPrmGetVal(bp, "SHM_KEY", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[SHM_KEY]");
        fprintf(Dbg_fp,"パラメータが取得できませんでした[SHM_KEY]\n");
        return(RTN_NG);
    }
    sAppEnv.shm_Key = atoi(lc_prmBuf);

    /* 血清項目(乳び)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "NYUBI_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[NYUBI_KM]");
        fprintf(Dbg_fp,"パラメータが取得できませんでした[NYUBI_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.nyubi_km,"%s", wk_buff);
    sAppEnv.nyubi_ch = i_tmp;
    fprintf(Dbg_fp,"血清項目(乳び) KM[%s] CH[%d]\n", sAppEnv.nyubi_km, sAppEnv.nyubi_ch);

    /* 血清項目(溶血)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "YOUKETSU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[YOUKETSU_KM]");
        fprintf(Dbg_fp,"パラメータが取得できませんでした[YOUKETSU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.youkets_km,"%s", wk_buff);
    sAppEnv.youkets_ch = i_tmp;
    fprintf(Dbg_fp,"血清項目(溶血) KM[%s] CH[%d]\n", sAppEnv.youkets_km, sAppEnv.youkets_ch);

    /* 血清項目(黄疸)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "OUDAN_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[OUDAN_KM]");
        fprintf(Dbg_fp,"パラメータが取得できませんでした[OUDAN_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.oudan_km,"%s", wk_buff);
    sAppEnv.oudan_ch = i_tmp;
    fprintf(Dbg_fp,"血清項目(黄疸) KM[%s] CH[%d]\n", sAppEnv.oudan_km, sAppEnv.oudan_ch);

    /* 血清項目(生食)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "SEISYOKU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[SEISYOKU_KM]");
        fprintf(Dbg_fp,"パラメータが取得できませんでした[SEISYOKU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.seisyk_km,"%s", wk_buff);
    sAppEnv.seisyk_ch = i_tmp;
    fprintf(Dbg_fp,"血清項目(生食) KM[%s] CH[%d]\n", sAppEnv.seisyk_km, sAppEnv.seisyk_ch);


    /* パラメータファイルクローズ */
    ZbmlPrmClose(bp);


    /* 共有メモリの作成 */
    if(sFncShmCrt(&sAppEnv) != RTN_OK)  return(RTN_NG);


    /* 各種マスタデータのロード */
    if(sFncChMstLoad() != RTN_OK)     return(RTN_NG);   /* チャネルマスタ */
    if(sFncKskMstLoad() != RTN_OK)    return(RTN_NG);   /* 希釈マスタ */
    if(sFncRngMstLoad() != RTN_OK)    return(RTN_NG);   /* 範囲マスタ */
    if(sFncMeStsMstLoad() != RTN_OK)  return(RTN_NG);   /* 分析機データフラグマスタ */
    if(sFncKrnMstLoad() != RTN_OK)    return(RTN_NG);   /* 関連項目マスタ */
    if(sFncCalcMstLoad() != RTN_OK)   return(RTN_NG);   /* 計算項目マスタ */
    if(sFncKmMstLoad() != RTN_OK)     return(RTN_NG);   /* 項目マスタ */
    if(sFncCtlMstLoad() != RTN_OK)    return(RTN_NG);   /* コントロールマスタ */


    /* 処理日取得 */
    if(sFncGetUdate() != RTN_OK)  return(RTN_NG);
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "処理日 [%s]", sAppEnv.udate);
    fprintf(Dbg_fp,"処理日 [%s]\n", sAppEnv.udate);


    KekFL_cnt = 0;
    memset(&KekFL[0],'\0', (sizeof(KEKFL_STR) * FLARRY_MAX));

    /* ライン結果出力待ち退避情報の読込み */
    sFncGetMemSave();

    return(RTN_OK);
}

/**/
static int mainFunction()
/******************************************************************************
*  関 数 名　：mainFunction()                                                 *
*  機能概要　：メイン処理                                                     *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    cmd[256];
    int     ii, kektmp_cnt, li_stopFlg;
    struct stat  st;

    /* 一時ファイルの生成 */
    sprintf(Temp_fpth,"/tmp/MD102_%d", getpid());
    kektmp_cnt = KekFL_cnt;

    /* メインループ */
    for( ; ; ) {

        /* 測定結果一時ファイルのファイルリスト取得 */
        sprintf(cmd,"/usr/bin/ls %s/%d* > %s 2>&1", KEKKATMP_PATH, sAppEnv.lineno, Temp_fpth);
        system(cmd);

        if(stat(Temp_fpth, &st) != 0 || st.st_size == 0) {
            fprintf(Dbg_fp,"測定結果一時ファイルリストが未作成...\n");
            goto RNM_STRY;
        }

        /* 測定項目(チャネル)が揃った結果情報を選出 */
        sFncGetFilelst();
        if(FLrec_cnt == 0)  goto RNM_STRY;            /* 測定結果一時ファイルが無いとき */


        /* 一般検体測定結果関連処理 */
        sFncKekkaProc();


        /* Ctl結果ファイル作成処理 */
        sFncCtlKekkaProc();


        /* サテライト向け検査結果ファイル作成 */
        /* (同時に再検用測定依頼ファイル作成) */
        sFncMKSatKekka();


RNM_STRY:
        /* 1ラック分揃った情報に対し、ライン側への検査結果ファイル作成 */
        sFncMkLineKekka();


        /* Line用収納トレー情報をサーチし、依頼情報と併せてリネーム処理 */
        sFncRnmStray();


        /* 再々検依頼の結果要求(Line側からの)ファイル検出処理 */
        /* (測定結果を待たずに再々検の投入ラックを回収するため) */
        sFncMkReSknKekka();


        /* 未処理の検体情報退避処理 */
        if(KekFL_cnt != kektmp_cnt) {
            sFncPutMemSave();
            kektmp_cnt = KekFL_cnt;
        }

        for(ii = 0 ; ii < KekFL_cnt ; ii++) {
            fprintf(Dbg_fp,"KekFL: CNT[%d] fnm[%s] Rack[%s] Pos[%d] CH[%d] KM[%07d] Ckens[%d] ken[%s] CAL[%d] STS[%d]\n",
                   KekFL_cnt,KekFL[ii].fname,KekFL[ii].rackid,KekFL[ii].pos,KekFL[ii].chnum,KekFL[ii].kmcode,
                   KekFL[ii].c_kensa,KekFL[ii].kenno,KekFL[ii].f_calc,KekFL[ii].sts);
        }

        /* 終了通知の状態確認 */
        li_stopFlg = 0;
        sFncShmGet(&sAppEnv, &li_stopFlg);
        if(li_stopFlg == 1)  break;

        sleep(2);
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static void endFunction()
/******************************************************************************
*  関 数 名　：endFunction()                                                  *
*  機能概要　：終了処理                                                       *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{

    /* シグナルハンドラの設定 */
    signal(SIGINT,  endFunction);
    signal(SIGKILL, endFunction);

    /* 未処理の検体情報退避処理 */
    sFncPutMemSave();


    /* 共有メモリ削除 */
    sFncShmDel(&sAppEnv);

    /* 終了のログ出力 */
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "プログラム終了");
    fprintf(Dbg_fp,"プログラム終了\n");
    if(Dbg_fp != stdout)  fclose(Dbg_fp);

    unlink(Temp_fpth);

    /* ログのクローズ */
    ZbmlCloseLog();

    exit(0);
}

/**/
static int sFncChMstLoad()
/******************************************************************************
*  関 数 名　：sFncChMstLoad()                                                *
*  機能概要　：チャネルマスタロード処理                                       *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstChanl_cnt = 0;
    sprintf(fpth,"%s/mechmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "チャネルマスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"チャネルマスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstChanl[0],'\0', (sizeof(CHLMST) * MSTCHANL_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strncmp(fbuf, ME_KUBUN, 4) != 0)  continue;     /* 分析機区分非該当のものは対象外 */

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 1)                             /* 分析機区分 */
                sprintf(MstChanl[mm].mekbn,"%s", buff);
            else if(c_dl == 2)                        /* チャネルNo. */
                MstChanl[mm].chnum = atoi(buff);
            else if(c_dl == 3)                        /* チャネル名 */
                sprintf(MstChanl[mm].chname,"%s", buff);
            else if(c_dl == 4) {                      /* チャネルNo. */
                MstChanl[mm].kmcode = atoi(buff);
                break;
            }
        }
        mm++;

        if(mm > MSTCHANL_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "チャネルマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"チャネルマスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstChanl_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "チャネルマスタ[%d]件ロードしました。", MstChanl_cnt);
    fprintf(Dbg_fp,"チャネルマスタ[%d]件ロードしました。\n", MstChanl_cnt);

    return(RTN_OK);
}

/**/
static int sFncKskMstLoad()
/******************************************************************************
*  関 数 名　：sFncKskMstLoad()                                               *
*  機能概要　：希釈倍率マスタロード処理                                       *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstKisyk_cnt = 0;
    sprintf(fpth,"%s/kskbrmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKskMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "希釈倍率マスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"希釈倍率マスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstKisyk[0],'\0', (sizeof(KISYKMST) * MSTKISYK_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strncmp(fbuf, ME_KUBUN, 4) != 0)  continue;     /* 分析機区分非該当のものは対象外 */

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 1)                             /* 分析機区分 */
                sprintf(MstKisyk[mm].mekbn,"%s", buff);
            else if(c_dl == 2)                        /* 検査グループ */
                sprintf(MstKisyk[mm].kengrp,"%s", buff);
            else if(c_dl == 3)                        /* 項目コード */
                MstKisyk[mm].kmcode = atoi(buff);
            else if(c_dl == 4)                        /* 希釈倍率 */
                sprintf(MstKisyk[mm].kisykbai,"%s", buff);
            else if(c_dl == 5) {                      /* 希釈下限値 */
                sprintf(MstKisyk[mm].kisyk_low,"%s", buff);
                MstKisyk[mm].dbksk_low = (double)atof(MstKisyk[mm].kisyk_low);
            }
            else if(c_dl == 6) {                      /* 希釈上限値 */
                sprintf(MstKisyk[mm].kisyk_hi,"%s", buff);
                MstKisyk[mm].dbksk_hi = (double)atof(MstKisyk[mm].kisyk_hi);
            }
            else if(c_dl == 9) {                      /* 希釈区分(依頼ファイルに反映) */
                sprintf(MstKisyk[mm].kisyk_kbn,"%s", buff);
                break;
            }
        }
        mm++;

        if(mm > MSTKISYK_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKskMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "希釈倍率マスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"希釈倍率マスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstKisyk_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "希釈倍率マスタ[%d]件ロードしました。", MstKisyk_cnt);
    fprintf(Dbg_fp,"希釈倍率マスタ[%d]件ロードしました。\n", MstKisyk_cnt);

    return(RTN_OK);
}

/**/
static int sFncRngMstLoad()
/******************************************************************************
*  関 数 名　：sFncRngMstLoad()                                               *
*  機能概要　：範囲チェックマスタロード処理                                   *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstRange_cnt = 0;
    sprintf(fpth,"%s/rngchkmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRngMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "範囲チェックマスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"範囲チェックマスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstRange[0],'\0', (sizeof(RNGMST) * MSTRANGE_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(fbuf[0] != '1')  continue;                 /* 読込み対象は再検レンジのみ */

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 2)                             /* 検査グループ */
                sprintf(MstRange[mm].kengrp,"%s", buff);
            else if(c_dl == 3)                        /* 項目コード */
                MstRange[mm].kmcode = atoi(buff);
            else if(c_dl == 4)                        /* 材料コード */
                sprintf(MstRange[mm].zaicode,"%s", buff);
            else if(c_dl == 5)                        /* 施設コード */
                sprintf(MstRange[mm].usercode,"%s", buff);
            else if(c_dl == 6)                        /* 性別 */
                sprintf(MstRange[mm].sex,"%s", buff);
            else if(c_dl == 7)                        /* 上下限区分 */
                MstRange[mm].uplow = (short)atoi(buff);
            else if(c_dl == 8)                        /* 許容(値)区分 */
                MstRange[mm].valkbn = (short)atoi(buff);
            else if(c_dl == 9) {                      /* レンジ上限 */
                sprintf(MstRange[mm].rng_hi,"%s", buff);
                MstRange[mm].dbrng_hi = (double)atof(MstRange[mm].rng_hi);
            }
            else if(c_dl == 10) {                     /* レンジ上限 */
                sprintf(MstRange[mm].rng_low,"%s", buff);
                MstRange[mm].dbrng_low = (double)atof(MstRange[mm].rng_low);
                break;
            }
        }
        mm++;

        if(mm > MSTRANGE_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRngMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "範囲チェックマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"範囲チェックマスタの配列MAX数を超えました。File[%s]", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstRange_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "範囲チェックマスタ[%d]件ロードしました。", MstRange_cnt);
    fprintf(Dbg_fp,"範囲チェックマスタ[%d]件ロードしました。\n", MstRange_cnt);

    return(RTN_OK);
}

/**/
static int sFncMeStsMstLoad()
/******************************************************************************
*  関 数 名　：sFncMeStsMstLoad()                                             *
*  機能概要　：分析機テータフラグマスタロード処理                             *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstMeSts_cnt = 0;
    sprintf(fpth,"%s/mestsmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMeStsMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "分析機フラグマスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"分析機フラグマスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstMests[0],'\0', (sizeof(MESTSMST) * MSTMESTS_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 1)                             /* ZS050データフラグ */
                sprintf(MstMests[mm].zscode,"%s", buff);
            else if(c_dl == 2)                        /* サテライト用変換コード */
                sprintf(MstMests[mm].trcode,"%s", buff);
            else if(c_dl == 3) {                      /* 処理コード */
                if(buff[0] != '\0')  MstMests[mm].procf = (short)atoi(buff);
            }
            else if(c_dl == 4) {                      /* 希釈条件コード */
                sprintf(MstMests[mm].skncond,"%s", buff);
                MstMests[mm].pri = atoi((fbuf+c_en+1));
                break;
            }
        }
        mm++;

        if(mm > MSTMESTS_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRngMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "分析機フラグマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"分析機フラグマスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstMeSts_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "分析機フラグマスタ[%d]件ロードしました。", MstMeSts_cnt);
    fprintf(Dbg_fp,"分析機フラグマスタ[%d]件ロードしました。\n", MstMeSts_cnt);

    return(RTN_OK);
}

/**/
static int sFncKrnMstLoad()
/******************************************************************************
*  関 数 名　：sFncKrnMstLoad()                                               *
*  機能概要　：関連項目マスタロード処理                                       *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstKnren_cnt = 0;
    sprintf(fpth,"%s/krkmkmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKrnMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "関連項目マスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"関連項目マスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstKnren[0],'\0', (sizeof(KANRENMST) * MSTKNREN_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 1)                             /* 項目コード */
                MstKnren[mm].kmcode = atoi(buff);
            else if(c_dl == 2) {                      /* 関連項目コード */
                MstKnren[mm].kanrenkm = atoi(buff);
                break;
            }
        }
        mm++;

        if(mm > MSTKNREN_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKrnMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "関連項目マスタマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"関連項目マスタマスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstKnren_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "関連項目マスタ[%d]件ロードしました。", MstKnren_cnt);
    fprintf(Dbg_fp,"関連項目マスタ[%d]件ロードしました。\n", MstKnren_cnt);

    return(RTN_OK);
}

/**/
static int sFncCalcMstLoad()
/******************************************************************************
*  関 数 名　：sFncCalcMstLoad()                                              *
*  機能概要　：計算項目マスタロード処理                                       *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstCalc_cnt = 0;
    sprintf(fpth,"%s/calckmkmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCalcMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "計算項目マスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"計算項目マスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstCalc[0],'\0', (sizeof(CALCMST) * MSTCALC_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 1)                             /* 検査グループ */
                sprintf(MstCalc[mm].kengrp,"%s", buff);
            else if(c_dl == 2)                        /* 項目コード */
                MstCalc[mm].kmcode = atoi(buff);
            else if(c_dl == 3)                        /* 施設コード */
                sprintf(MstCalc[mm].usercode,"%s", buff);
            else if(c_dl == 4)                        /* 材料コード */
                sprintf(MstCalc[mm].zaicode,"%s", buff);
            else if(c_dl == 5) {                      /* 計算式 */
                sprintf(MstCalc[mm].calc,"%s", buff);
                break;
            }
        }
        mm++;

        if(mm > MSTCALC_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCalcMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "計算項目マスタマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"計算項目マスタマスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstCalc_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "計算項目マスタ[%d]件ロードしました。", MstCalc_cnt);
    fprintf(Dbg_fp,"計算項目マスタ[%d]件ロードしました。\n", MstCalc_cnt);

    return(RTN_OK);
}

/**/
static int sFncCtlMstLoad()
/******************************************************************************
*  関 数 名　：sFncCtlMstLoad()                                               *
*  機能概要　：コントロールマスタロード処理                                   *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fbuf[512], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstCtl_cnt = 0;
    sprintf(fpth,"%s/ctrlmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCtlMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "コントロールマスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"Ctlマスタファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstCtl[0],'\0', (sizeof(CTLMST) * MSTCTL_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strncmp(fbuf, ME_KUBUN, 4) != 0)  continue;     /* 分析機区分非該当のものは対象外 */

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 2)                             /* チャネルNo. */
                MstCtl[mm].chnum = (short)atoi(buff);
            else if(c_dl == 3)                        /* Ctl種別 */
                sprintf(MstCtl[mm].ctlknd,"%s", buff);
            else if(c_dl == 6)                        /* ロットNo. */
                sprintf(MstCtl[mm].lotno,"%s", buff);
            else if(c_dl == 8)                        /* 平均値 */
                sprintf(MstCtl[mm].ctrlx,"%s", buff);
            else if(c_dl == 9) {                      /* SD値 */
                sprintf(MstCtl[mm].ctrlsd,"%s", buff);
                break;
            }
        }
        mm++;

        if(mm > MSTCTL_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCtlMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "コントロールマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"Ctlマスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstCtl_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "コントロールマスタ[%d]件ロードしました。", MstCtl_cnt);
    fprintf(Dbg_fp,"コントロールマスタ[%d]件ロードしました。\n", MstCtl_cnt);

    return(RTN_OK);
}

/**/
static int sFncKmMstLoad()
/******************************************************************************
*  関 数 名　：sFncKmMstLoad()                                                *
*  機能概要　：項目マスタロード処理                                           *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[601], fbuf[256], buff[51];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstKm_cnt = 0;
    sprintf(fpth,"%s/kmkmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKmMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "項目マスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"項目マスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstKm[0],'\0', (sizeof(KMMST) * MSTKNREN_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 601, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len--; }

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < len ; ii++) {
            if(fbuf[ii] == ',') {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 1)                             /* 検査グループ */
                sprintf(MstKm[mm].kengrp,"%s", buff);
            else if(c_dl == 2)                        /* 項目コード */
                MstKm[mm].kmcode = atoi(buff);
            else if(c_dl == 16) {                     /* 小数点桁数 */
                MstKm[mm].place = atoi(buff);
                break;
            }
        }
        mm++;

        if(mm > MSTKM_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKmMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "項目マスタマスタの配列MAX数を超えました。File[%s]", fpth);
            fprintf(Dbg_fp,"項目マスタマスタの配列MAX数を超えました。File[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstKm_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "項目マスタ[%d]件ロードしました。", MstKm_cnt);
    fprintf(Dbg_fp,"項目マスタ[%d]件ロードしました。\n", MstKm_cnt);

    return(RTN_OK);
}

/**/
static int sFncGetUdate()
/******************************************************************************
*  関 数 名　：sFncGetUdate()                                                 *
*  機能概要　：システム管理マスタからの処理日取得処理                         *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[101], fbuf[512], buff[21];
    int     ii, jj, len, c_st, c_en, c_dl;
    FILE    *fp;

    sprintf(fpth,"%s/sysknrmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetUdate", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "システム管理マスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"システム管理マスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    /* 1レコード取得 */
    if(NULL == fgets(fbuf, 512, fp)) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetUdate", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "システム管理マスタファイルの読込みに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"システム管理マスタファイルの読込みに失敗しました。File[%s] ERR[%d]\n", fpth, errno);

        fclose(fp);
        return(RTN_NG);
    }
    fclose(fp);

    len = strlen(fbuf);
    c_st = c_en = c_dl = 0;
    for(ii = 0 ; ii < len ; ii++) {
        if(fbuf[ii] == ',') {
            if(c_en > 0)  c_st = c_en+1;
            c_en = ii;  c_dl++;
        }
        else  continue;

        if(c_dl == 3) {
            memcpy(buff, (fbuf+c_st), (c_en-c_st));  buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);  break;
        }
    }

    len = strlen(buff);
    jj = 0;
    for(ii = 0 ; ii < len ; ii++) {
        if(buff[ii] == '/')  continue;
        sAppEnv.udate[jj] = buff[ii];
        jj++;
        if(buff[ii] == '\0')  break;
    }

    return(RTN_OK);
}

/**/
static void sFncGetMemSave()
/******************************************************************************
*  関 数 名　：sFncGetMemSave()                                               *
*  機能概要　：メモリのライン結果出力待ち退避情報の読込み/反映処理            *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
******************************************************************************/
{
    char    fpth[101];
    int     ii, mecd, ctlno;
    short   f_brk;
    FILE    *fp;
    struct stat  st;
    KEKFL_STR    keklst;

    sprintf(fpth,"%s/%d_MD102.sav", ONLINE_PATH, sAppEnv.lineno);
    if(stat(fpth, &st) != 0) {
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "メモリ退避ファイルが見つかりません。(初期状態) File[%s]", fpth);
        fprintf(Dbg_fp,"メモリ退避ファイルが見つかりません。File[%s]\n", fpth);
        return;
    }

    if(st.st_size < sizeof(KEKFL_STR))
        return;


    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
        return;
    }

    KekFL_cnt = f_brk = 0;
    for( ; ; ) {
        memset(&keklst,'\0', sizeof(KEKFL_STR));
printf("sizeof(KEKFL_STR) [%d]\n",sizeof(KEKFL_STR));
        if(fread((char *)&keklst, sizeof(KEKFL_STR), 1, fp) == 0) {
            if(feof(fp))  f_brk = 1;
            else {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "メモリ退避ファイルの読込みに失敗。File[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"メモリ退避ファイルの読込みに失敗。File[%s] ERR[%d]\n", fpth, errno);
            break;
            }
        }

        memcpy(&KekFL[KekFL_cnt], &keklst, sizeof(KEKFL_STR));
        fprintf(Dbg_fp,"KekFL: RackID[%s] POS[%d]\n", KekFL[KekFL_cnt].rackid, KekFL[KekFL_cnt].pos);
        KekFL_cnt++;
        if(f_brk == 1)  break;
    }
    fclose(fp);

    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "[%d]件のメモリ退避情報をロードしました。", KekFL_cnt);
    fprintf(Dbg_fp,"[%d]件のメモリ退避情報をロード...\n", KekFL_cnt);

    return;
}

/**/
static void sFncPutMemSave()
/******************************************************************************
*  関 数 名　：sFncPutMemSave()                                               *
*  機能概要　：メモリのライン結果出力待ち退避情報の書込み処理                 *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
******************************************************************************/
{
    char    fpth[101];
    int     ii;
    FILE    *fp;
    struct stat  st;

    sprintf(fpth,"%s/%d_MD102.sav", ONLINE_PATH, sAppEnv.lineno);
    if(NULL == (fp = fopen(fpth,"w"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncPutMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
        return;
    }

    for(ii = 0 ; ii < KekFL_cnt ; ii++) {
        fwrite(&KekFL[ii], sizeof(KEKFL_STR), 1, fp);
    }
    fclose(fp);

    return;
}

/**/
static void sFncGetFilelst()
/******************************************************************************
*  関 数 名　：sFncGetFilelst()                                               *
*  機能概要　：結果が揃ったファイル一覧のメモリロード処理                     *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[101], fnm[51], fbuf[101];
    char    wk_rack[30 +1];
    int     ii, jj, len;
    short   wk_pos, wk_ch;
    FILE    *fp;
    struct stat  st;

    /* ファイルリストのオープン */
    if(NULL == (fp = fopen(Temp_fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetFilelst", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "結果一時ファイルリストのオープンに失敗しました。File[%s] ERR[%d]", Temp_fpth, errno);
        fprintf(Dbg_fp,"結果一時ファイルリストのオープンに失敗しました。File[%s] ERR[%d]\n", Temp_fpth, errno);
        return;
    }

    memset(&FLrec[0],'\0', (sizeof(KEKFL_STR) * FLARRY_MAX));
    FLrec_cnt = 0;
    for(ii = 0 ; ii < FLARRY_MAX ; ii++) {
        strcpy(FLrec[ii].meerrsts,"  ");
        strcpy(FLrec[ii].kisyak_sts," ");
        strcpy(FLrec[ii].cksts,"  ");
    }

    ii = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 101, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '\0')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n') {
            fbuf[len-1] = '\0';  len = strlen(fbuf);
        }

        if(stat(fbuf, &st) != 0)     continue;
        if(st.st_size < (size_t)20)  continue;


        strcpy(fpth, fbuf);
        for(jj = (len-1) ; jj >= 0 ; jj--) {
            if(fbuf[jj] == '/')  break;
        }
        if(jj >= 0)  sprintf(fnm,"%s", (fbuf+jj+1));
        else         sprintf(fnm,"%s", fbuf);

        /* ファイル名よりラックID、ラックPOS、チャネルNo.を取得 */
        sFncGetRackChPos((fnm+2), wk_rack, &wk_pos, &wk_ch);
        sprintf(FLrec[ii].path,"%s", fpth);
        sprintf(FLrec[ii].fname,"%s", fnm);
        if(strncmp((fnm+2),"QCK", 3) == 0) {
            sprintf(FLrec[ii].kenid,"%s", wk_rack);
            FLrec[ii].chnum = wk_ch;
            FLrec[ii].qcflg = 1;
        }
        else  sprintf(FLrec[ii].rackid,"%s", wk_rack);

        FLrec[ii].pos = wk_pos;
        FLrec[ii].chnum = wk_ch;
        fprintf(Dbg_fp,"fnm[%s] Rack[%s] Pos[%d] CH[%d]\n", FLrec[ii].fname, FLrec[ii].rackid, FLrec[ii].pos, FLrec[ii].chnum);

        /* 血清項目かどうか判定 */
        if(FLrec[ii].chnum == sAppEnv.seisyk_ch)
            FLrec[ii].f_kessei = 2;
        else if(FLrec[ii].chnum == sAppEnv.nyubi_ch ||
                FLrec[ii].chnum == sAppEnv.youkets_ch ||
                FLrec[ii].chnum == sAppEnv.oudan_ch) {
            FLrec[ii].f_kessei = 1;
        }
        else  FLrec[ii].f_kessei = 0;


        ii++;
        if(ii >= FLARRY_MAX)  break;                  /* 配列MAX数に達したとき */
    }
    fclose(fp);

    fprintf(Dbg_fp,"[%d]件の結果一時ファイルを読込み...\n", ii);
    if(ii == 0)  return;                              /* 0件のときはここでリターン */

    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "[%d]件の結果一時ファイルを読込み...", ii);
    FLrec_cnt = ii;


    /* 個々の結果情報に対する依頼情報との照合処理 */
    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].qcflg == 1)  continue;           /* Ctl結果はチェックの対象外 */
        if(FLrec[ii].sts != 0)    continue;           /* 照合実行済みデータは対象外 */

        /* 依頼情報との照合 */
        if(sFncMatchIrai(&FLrec[ii]) != RTN_OK)
            sFncSetFlstSts(&FLrec[ii], -1);           /* NGの場合はstsを"-1"に設定 */
    }

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].sts > 0) {
            sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "測定項目揃い済み fnm[%s] Rack[%s] Pos[%d] CH[%d] KM[%07d] Ckens[%d] ken[%s] CAL[%d] STS[%d]",
                FLrec[ii].fname, FLrec[ii].rackid, FLrec[ii].pos, FLrec[ii].chnum,
                FLrec[ii].kmcode, FLrec[ii].c_kensa, FLrec[ii].kenno, FLrec[ii].f_calc, FLrec[ii].sts);
        }
        fprintf(Dbg_fp,"fnm[%s] Rack[%s] Pos[%d] CH[%d] KM[%07d] Ckens[%d] ken[%s] CAL[%d] STS[%d]\n",
                FLrec[ii].fname, FLrec[ii].rackid, FLrec[ii].pos, FLrec[ii].chnum,
                FLrec[ii].kmcode, FLrec[ii].c_kensa, FLrec[ii].kenno, FLrec[ii].f_calc, FLrec[ii].sts);
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
    return;
}

/**/
static void sFncGetRackChPos(char *fnm, char *rackid, short *pos, short *chno)
/******************************************************************************
*  関 数 名　：sFncGetRackChPos()                                             *
*  機能概要　：ファイル名からのラックID, POS, CH番号取得処理                  *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    buff[51];
    int     mm, c_st, c_en, c_dl;

    if(strncmp(fnm,"QCK", 3) == 0) {                  /* コントロール結果のとき */
        memcpy(rackid, (fnm+3), 10);  rackid[10] = '\0';
        *pos = -1;
        c_st = c_en = c_dl = 0;
        for(mm = 13 ; mm < strlen(fnm) ; mm++) {
            if(fnm[mm] == '_' || fnm[mm] == '.') {
                if(c_en > 0)  c_st = c_en + 1;
                c_dl++;  c_en = mm;
            }
            else  continue;

            if(c_dl == 2) {
                memcpy(buff, (fnm+c_st), (c_en-c_st));  buff[(c_en-c_st)] = '\0';
                *chno = (short)atoi(buff);
                break;
            }
        }
    }
    else {                                            /* 一般検体のとき */
        memcpy(rackid, (fnm+3), 5);  rackid[5] = '\0';
        c_st = c_en = c_dl = 0;
        for(mm = 8 ; mm < strlen(fnm) ; mm++) {
            if(fnm[mm] == '_' || fnm[mm] == '.') {
                if(c_en > 0)  c_st = c_en + 1;
                c_dl++;  c_en = mm;
            }
            else  continue;

            if(c_dl == 4) {
                memcpy(buff, (fnm+c_st), (c_en-c_st));  buff[(c_en-c_st)] = '\0';
                *pos = (short)atoi(buff);
            }
            else if(c_dl == 5) {
                memcpy(buff, (fnm+c_st), (c_en-c_st));  buff[(c_en-c_st)] = '\0';
                *chno = (short)atoi(buff);
                break;
            }
        }
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return;
}

/**/
static int sFncMatchIrai(KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncMatchIrai()                                                *
*  機能概要　：依頼ファイルとのチャネルNo.照合処理                            *
*  入　　力　：                                                               *
*  引    数      KEKFL_STR *flst                                              *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[101], fnm[51], fbuf[512], b_tmp[101];
    char    wk_kensacnt[1 +1], wk_kensaphs[1 +1], wk_ino[11 +1];
    char    wk_usercode[7 +1], wk_zaicode[4 +1], wk_sex[1 +1];
    char    wk_kenno[13 +1], wk_kmcode[7 +1], wk_kengrp[16 +1];
    char    rnmfpth[101];
    int     c_st, c_en, c_dl, c_rec;
    int     ii, jj, mm;
    short   f_infset, f_calc, f_mch, wk_chnum;
    FILE    *fp;
    struct stat  st;

    /* 依頼ファイルのサーチ */
    for(ii = 0 ; ii < 2 ; ii++) {
        if(ii == 0)       strcpy(b_tmp, NEWFL_SUFFIX);
        else if(ii == 1)  strcpy(b_tmp, SKNIRAI_SUFFIX);

        sprintf(fnm,"%s%s_____%03d.%s", IRAI_PREFIX, flst->rackid, flst->pos, b_tmp);
        sprintf(fpth,"%s/%s", IRAINEW_PATH, fnm);
        fprintf(Dbg_fp,"依頼ファイルサーチ: [%s]...", fnm);

        if(stat(fpth, &st) == 0 && st.st_size > 0) {
            fprintf(Dbg_fp,"存在確認!!!\n");
            break;
        }
        else { fprintf(Dbg_fp,"無い!!!\n"); }
    }

    /* 依頼ファイルが見つからないとき */
    if(ii >= 2) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "依頼ファイルが見つかりません。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"依頼ファイルが見つかりません。File[%s] ERR[%d]\n", fpth, errno);

        /* #01 エラー時は結果一時ファイルを"end"Dirにリネーム */
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, flst->rackid) != 0)  continue;
            if(FLrec[jj].pos != flst->pos)  continue;

            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "結果一時ファイルをerr Dirに移動します。File[%s]", FLrec[jj].fname);
            fprintf(Dbg_fp,"結果一時ファイルをerr Dirに移動します。File[%s]\n", FLrec[jj].fname);
            sprintf(rnmfpth,"%s/%s", KEKKAERR_PATH, FLrec[jj].fname);
            rename(FLrec[jj].path, rnmfpth);
        }

        return(RTN_NG);
    }

    /* 依頼ファイルオープン */
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);

        /* #01 エラー時は結果一時ファイルを"end"Dirにリネーム */
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, flst->rackid) != 0)  continue;
            if(FLrec[jj].pos != flst->pos)  continue;

            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "結果一時ファイルをerr Dirに移動します。File[%s]", FLrec[jj].fname);
            fprintf(Dbg_fp,"結果一時ファイルをerr Dirに移動します。File[%s]\n", FLrec[jj].fname);
            sprintf(rnmfpth,"%s/%s", KEKKAERR_PATH, FLrec[jj].fname);
            rename(FLrec[jj].path, rnmfpth);
        }

        return(RTN_NG);
    }


    f_infset = 0;
    c_rec = f_calc = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strlen(fbuf) < 50)  continue;

        /* 各フィールドの処理 */
        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < strlen(fbuf) ; ii++) {
            if(fbuf[ii] == ',')  {
                if(c_en > 0)  c_st = c_en +1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            if(c_dl == 3) {
                memcpy(wk_kenno, (fbuf+c_st), (c_en-c_st));  wk_kenno[(c_en-c_st)] = '\0';
                sFncTrim(wk_kenno);
            }
            else if(c_dl == 5) {                      /* 検査グループ */
                memcpy(wk_kengrp, (fbuf+c_st), (c_en-c_st));  wk_kengrp[(c_en-c_st)] = '\0';
                sFncTrim(wk_kengrp);
            }
            else if(c_dl == 6) {                      /* 項目(CH)設定 */
                memcpy(wk_kmcode, (fbuf+c_st), (c_en-c_st));
                wk_kmcode[(c_en-c_st)] = '\0';
                sFncTrim(wk_kmcode);

                /* チャネルNo.を取得 */
                jj = 0;

                /* 血清項目に対する処理 */
                if(strcmp(wk_kmcode, sAppEnv.nyubi_km) == 0)         wk_chnum = sAppEnv.nyubi_ch;
                else if(strcmp(wk_kmcode, sAppEnv.youkets_km) == 0)  wk_chnum = sAppEnv.youkets_ch;
                else if(strcmp(wk_kmcode, sAppEnv.oudan_km) == 0)    wk_chnum = sAppEnv.oudan_ch;
                else if(strcmp(wk_kmcode, sAppEnv.seisyk_km) == 0)   wk_chnum = sAppEnv.seisyk_ch;
                else {

                    /* その他の項目の処理 */
                    for(jj = 0 ; jj < MstChanl_cnt ; jj++) {
                        if(MstChanl[jj].kmcode == atoi(wk_kmcode))
                            break;
                    }
                    if(jj >= MstChanl_cnt) {
                        fprintf(Dbg_fp,"チャネル番号がマスタに見つかりません。(非測定項目) KM[%s]\n", wk_kmcode);

                        /* 計算項目の情報を生成 */
                        sprintf(FLrec[FLrec_cnt].rackid,"%s", flst->rackid);
                        FLrec[FLrec_cnt].pos = flst->pos;
                        sprintf(FLrec[FLrec_cnt].irfnm,"%s", fnm);
                        FLrec[FLrec_cnt].kmcode = atoi(wk_kmcode);
                        FLrec[FLrec_cnt].f_calc = 1;
                        FLrec[FLrec_cnt].sts = 1;
                        strcpy(FLrec[FLrec_cnt].cksts,"  ");
                        strcpy(FLrec[FLrec_cnt].kisyak_sts," ");
                        FLrec_cnt++;
                        f_mch = 1;
                    }
                    else  wk_chnum = MstChanl[jj].chnum;

                }
                if(jj < MstChanl_cnt) {

                    /* 結果一時ファイルと依頼ファイルの照合 */
                    f_mch = 0;
                    for(mm = 0 ; mm < FLrec_cnt ; mm++) {
                        if(strcmp(FLrec[mm].rackid, flst->rackid) != 0)  continue;
                        if(FLrec[mm].pos != flst->pos)  continue;

                        if(FLrec[mm].chnum == wk_chnum) {
                            f_mch = 1;
                            FLrec[mm].sts = 1;
                            sprintf(FLrec[mm].kenno,"%s", wk_kenno);
                            if(FLrec[mm].f_kessei == 0)  FLrec[mm].kmcode = atoi(wk_kmcode);
                            break;
                        }
                    }
                    if(f_mch == 0) {
                        fprintf(Dbg_fp,"CH不整合 CH[%d] fbuf[%s]\n", wk_chnum, fbuf);
                    }
                }
            }
            else if(c_dl == 7) {                      /* 検査回数 */
                memcpy(wk_kensacnt, (fbuf+c_st), (c_en-c_st));  wk_kensacnt[(c_en-c_st)] = '\0';
                sFncTrim(wk_kensacnt);
            }
            else if(c_dl == 11) {                     /* 検査工程区分 */
                memcpy(wk_kensaphs, (fbuf+c_st), (c_en-c_st));  wk_kensaphs[(c_en-c_st)] = '\0';
                sFncTrim(wk_kensaphs);
            }
            else if(c_dl == 13) {                     /* 依頼書No. */
                memcpy(wk_ino, (fbuf+c_st), (c_en-c_st));  wk_ino[(c_en-c_st)] = '\0';
                sFncTrim(wk_ino);
            }
            else if(c_dl == 16) {                     /* 施設コード */
                memcpy(wk_usercode, (fbuf+c_st), (c_en-c_st));  wk_usercode[(c_en-c_st)] = '\0';
                sFncTrim(wk_usercode);
            }
            else if(c_dl == 27) {                     /* 材料コード */
                memcpy(wk_zaicode, (fbuf+c_st), (c_en-c_st));  wk_zaicode[(c_en-c_st)] = '\0';
                sFncTrim(wk_zaicode);
            }
            else if(c_dl == 44) {                     /* 性別 */
                memcpy(wk_sex, (fbuf+c_st), (c_en-c_st));  wk_sex[(c_en-c_st)] = '\0';
                sFncTrim(wk_sex);
                break;
            }
        }

        /* 依頼情報のチャネルNoに該当したとき */
        if(f_mch == 1) {
            for(mm = 0 ; mm < FLrec_cnt ; mm++) {
                if(strcmp(FLrec[mm].rackid, flst->rackid) != 0)  continue;
                if(FLrec[mm].pos != flst->pos)  continue;

                sprintf(FLrec[mm].irfnm,"%s", fnm);
                if(wk_kengrp[0] != '\0')  sprintf(FLrec[mm].kengrp,"%s", wk_kengrp);
                FLrec[mm].c_kensa = (short)atoi(wk_kensacnt);
                sprintf(FLrec[mm].kensaphs,"%s", wk_kensaphs);
                sprintf(FLrec[mm].ino,"%s", wk_ino);
                sprintf(FLrec[mm].usercode,"%s", wk_usercode);
                sprintf(FLrec[mm].zaicode,"%s", wk_zaicode);
                sprintf(FLrec[mm].sex,"%s", wk_sex);
                strcpy(FLrec[mm].cksts,"  ");
                strcpy(FLrec[mm].kisyak_sts," ");
            }
            continue;
        }

        /* 依頼情報のチャネルNoに該当する結果一時ファイルが無いとき */
        sFncSetFlstSts(flst, -1);                     /* stsを"-1"に設定 */
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "測定項目(チャネル)の結果が揃っていません。Rack[%s] Pos[%d]", flst->rackid, flst->pos);
        fprintf(Dbg_fp,"測定項目(チャネル)の結果が揃っていません。Rack[%s] Pos[%d]\n", flst->rackid, flst->pos);
        break;
    }
    fclose(fp);

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
    return(RTN_OK);
}

/**/
static void sFncSetFlstSts(KEKFL_STR *flst, int val)
/******************************************************************************
*  関 数 名　：sFncSetFlstSts()                                               *
*  機能概要　：結果一時ファイルリストへのステータス設定処理                   *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    int     ii;

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(strcmp(FLrec[ii].rackid, flst->rackid) != 0)  continue;
        if(FLrec[ii].pos != flst->pos)  continue;

        FLrec[ii].sts = val;
    }

    return;
}

/**/
static void sFncKekkaProc()
/******************************************************************************
*  関 数 名　：sFncKekkaProc()                                                *
*  機能概要　：一般検体測定結果関連処理                                       *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    int     ii;

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {

        if(FLrec[ii].qcflg == 1)  continue;           /* Ctl結果は対象外 */
        if(FLrec[ii].sts != 1)    continue;           /* 測定項目結果が揃っていない場合も対象外 */

        /* 測定結果の読込み */
        if(FLrec[ii].f_calc != 1) {
            if(sFncGetRsltTmp(&FLrec[ii]) != RTN_OK) {
                sFncSetFlstSts(&FLrec[ii], -1);       /* NGの場合はstsを"-1"に設定 */
            }
        }

        /* 計算項目処理 */
        if(FLrec[ii].f_calc == 1) {
            sFncCalcKmProc(&FLrec[ii], ii);
        }
                                                      /* CHマスタ、計算KMマスタに存在しない場合 */
        if(FLrec[ii].f_calc == 2)  { FLrec[ii].sts = 3;  continue; }


        /* 分析機エラーチェック処理 */
        strcpy(FLrec[ii].kisyak_sts," ");
        if(strncmp(FLrec[ii].errcd2,"  ", 2) != 0 || FLrec[ii].errcd2[0] != '\0')
            sFncMeErrorChk(&FLrec[ii]);


        /* 血清項目は以下のチェックの対象外とする */
        if(FLrec[ii].f_kessei > 0)  { FLrec[ii].sts = 3;  continue; }


        /* 希釈チェック処理 */
        sFncKisyakChk(&FLrec[ii]);


        /* 範囲チェック処理 */
        sFncRngChkProc(&FLrec[ii]);

        fprintf(Dbg_fp,"最終STS MEerr[%s] MEPRC[%d] KISYAK[%s] CHK[%s]\n",
                FLrec[ii].meerrsts, FLrec[ii].meerrprc, FLrec[ii].kisyak_sts, FLrec[ii].cksts);
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
    return;
}

/**/
static int sFncGetRsltTmp(KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncGetRsltTmp()                                               *
*  機能概要　：測定結果一時ファイルの結果取得処理                             *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fbuf[101], buff[256];
    int     ii, len, c_st, c_en, c_dl, wk_place;
    double  wk_bias, dbl_kekka;
    FILE    *fp;

    if(NULL == (fp = fopen(flst->path,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetRsltTmp", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "結果一時ファイルのオープンに失敗しました。File[%s] ERR[%d]", flst->fname, errno);
        fprintf(Dbg_fp,"結果一時ファイルのオープンに失敗しました。File[%s] ERR[%d]\n", flst->fname, errno);

        return(RTN_NG);
    }

    if(NULL == fgets(fbuf, 101, fp)) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetRsltTmp", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "結果一時ファイルの読込みに失敗しました。File[%s] ERR[%d]", flst->fname, errno);
        fprintf(Dbg_fp,"結果一時ファイルの読込みに失敗しました。File[%s] ERR[%d]\n", flst->fname, errno);

        fclose(fp);
        return(RTN_NG);
    }
    fclose(fp);

    len = strlen(fbuf);
    if(fbuf[len-1] == '\n')  fbuf[len-1] = '\0';
    len = strlen(fbuf);

    /* 結果データ取得 */
    c_st = c_en = c_dl = 0;
    for(ii = 0 ; ii < len ; ii++) {
        if(fbuf[ii] == ',')  {
            if(c_en > 0)  c_st = c_en+1;
            c_en = ii;  c_dl++;
        }
        else  continue;

        if(c_en == c_st)  continue;
        memcpy(buff, (fbuf+c_st), (c_en-c_st));
        buff[(c_en-c_st)] = '\0';

        if(c_dl == 1)       sprintf(flst->rstime,"%s", buff);
        else if(c_dl == 2)  flst->mecd = (short)atoi(buff);
        else if(c_dl == 3)  flst->meseqno = atoi(buff);
        else if(c_dl == 4)  sprintf(flst->kenid,"%s", buff);
        else if(c_dl == 7) {
            sprintf(flst->raw,"%s", buff);
            sprintf(flst->kekka,"%s", buff);
        }
        else if(c_dl == 8)  flst->ctlno = atoi(buff);
        else if(c_dl == 9) {
            sprintf(flst->errcd1,"%s", buff);
            if(fbuf[c_en+1] != '\0')
                sprintf(flst->errcd2,"%.30s", (fbuf+c_en+1));
            break;
        }
    }

    /* 項目マスタより該当情報取得 */
    wk_place = 0;
    for(ii = 0 ; ii < MstKm_cnt ; ii++) {
        if(strcmp(MstKm[ii].kengrp, flst->kengrp) != 0)  continue;
        if(MstKm[ii].kmcode != flst->kmcode)             continue;

        wk_place = MstKm[ii].place;  break;
    }

    /* 血清項目とCtl結果は丸めない */
    if(flst->f_kessei > 0 || flst->qcflg == 1 || flst->raw[0] == '\0')
        return(RTN_OK);


    /* 項目マスタの小数点桁数による丸め処理 */
    dbl_kekka = (double)atof(flst->raw);
    if(wk_place == 0)      wk_bias = (double)0.5;
    else if(wk_place > 0)  wk_bias = (double)(0.5/(pow(10, wk_place)));

    if(dbl_kekka > 0 ||                               /* 結果値が0以上か判断 */
      (fabs(dbl_kekka -0) <= DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(0))))) {
        sprintf(buff,"%f", (dbl_kekka + wk_bias));
    }
    else  sprintf(buff,"%f", (dbl_kekka - wk_bias));

    len = strlen(buff);
    for(ii = 0 ; ii < len ; ii++) {
        if(buff[ii] == '.')  break;
    }
    sprintf(flst->kekka,"%.*s", ii, buff);
    if(wk_place > 0)
        sprintf((flst->kekka +ii),".%.*s", wk_place, (buff+ii+1));

    fprintf(Dbg_fp,"結果値丸め処理 FNM[%s] RAW[%s] PLC[%d] KEK[%s]\n",
            flst->fname, flst->raw, wk_place, flst->kekka);

    return(RTN_OK);
}

/**/
static void sFncCalcKmProc(KEKFL_STR *flst, int idx)
/******************************************************************************
*  関 数 名　：sFncCalcKmProc()                                               *
*  機能概要　：計算項目の算出処理                                             *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    buff[256], **pFldOD, *pBuffOD, wk_calc[128 +1];
    int     ii, jj, len, rtn, wk_place;
    short   mch_ucd, mch_zai, f_fnd;
    double  wk_bias;
    STKEISANCHK	kekkabuf[32];
    struct CALKEKKA {
        int     kmcode;
        char    kekka[8 +1];
    } calkek[2][2];

    pFldOD = malloc(sizeof(char *) * 200);
    memset(pFldOD, 0, (sizeof(char *) *200));
    pBuffOD = malloc(sizeof(char) * 512);
    memset(pBuffOD, 0, sizeof(char) * 512);

    /* 項目マスタより該当情報取得 */
    wk_place = 0;
    for(ii = 0 ; ii < MstKm_cnt ; ii++) {
        if(strcmp(MstKm[ii].kengrp, flst->kengrp) != 0)      continue;
        if(MstKm[ii].kmcode != flst->kmcode)                 continue;

        wk_place = MstKm[ii].place;  break;
    }
    fprintf(Dbg_fp,"小数点桁数[%d]\n",wk_place);


    /* 依頼情報の取得 */
    sprintf(buff,"%07d", flst->kmcode);
    rtn = chkInfoRead(1, buff, flst->irfnm, pFldOD, pBuffOD);


    /* 計算項目の計算式をマスタより取得 */
    f_fnd = 0;
    memset(&calkek[0][0],'\0', (sizeof(struct CALKEKKA) *4));
    for(ii = 0 ; ii < MstCalc_cnt ; ii++) {
        mch_ucd = mch_zai = 0;

        if(strcmp(MstCalc[ii].kengrp, flst->kengrp) != 0)      continue;
        if(MstCalc[ii].kmcode != flst->kmcode)                 continue;

        if(strncmp(MstCalc[ii].usercode,"0000000", 7) != 0 &&
           strcmp(MstCalc[ii].usercode, flst->usercode) != 0)  continue;

        if(strncmp(MstCalc[ii].zaicode,"000", 3) != 0 &&
           strcmp(MstCalc[ii].zaicode, flst->zaicode) != 0)    continue;


        if(strncmp(MstCalc[ii].usercode,"0000000", 7) != 0)  mch_ucd = 1;
        if(strncmp(MstCalc[ii].zaicode,"000", 3) != 0)       mch_zai = 1;

        f_fnd = 1;

        if(MstCalc[ii].calc[0] == '(') {
            strcpy(buff, MstCalc[ii].calc);
            len = strlen(buff);
            if(buff[len-1] == ')') {
                buff[len-1] = '\0';
                strcpy(wk_calc, (buff+1));
            }
        }
        else  strcpy(wk_calc, MstCalc[ii].calc);
fprintf(Dbg_fp,"Calc: Kekka[%s] RAW[%s]\n", flst->kekka, flst->raw);

        /* 計算処理実行関数の呼出し */
        rtn = KeisanChk(wk_calc, flst, idx, pFldOD, &kekkabuf[0]);
        calkek[mch_ucd][mch_zai].kmcode = flst->kmcode;


        /* 項目マスタの小数点桁数による丸め処理 */
        if(kekkabuf[0].flgRawNone != MY_FLG_ON) {     /* 結果が入っている場合のみ */
            if(wk_place == 0)      wk_bias = 0.5;
            else if(wk_place > 0)  wk_bias = (0.5/(pow(10, wk_place)));
            fprintf(Dbg_fp,"raw[%f]...bias[%f]\n",kekkabuf[0].raw,wk_bias);

            if(kekkabuf[0].raw > 0 ||                     /* 結果値が0以上か判断 */
              (fabs(kekkabuf[0].raw -0) <= (DBL_EPSILON * fmax(1, fmax(fabs(kekkabuf[0].raw), fabs(0)))))) {
                sprintf(buff,"%f", (kekkabuf[0].raw + wk_bias));
            }
            else  sprintf(buff,"%f", (kekkabuf[0].raw - wk_bias));

            len = strlen(buff);
            for(jj = 0 ; jj < len ; jj++) {
                if(buff[jj] == '.')  break;
            }
            sprintf(calkek[mch_ucd][mch_zai].kekka,"%.*s", jj, buff);
            if(wk_place > 0)
                sprintf((calkek[mch_ucd][mch_zai].kekka +jj),".%.*s", wk_place, (buff+jj+1));
        }

        /* 計算項目の号機設定 */
        if(flst->mecd == 0) {
            for(jj = 0 ; jj < FLrec_cnt ; jj++) {
                if(strcmp(FLrec[jj].rackid, flst->rackid) != 0)  continue;
                if(FLrec[jj].pos != flst->pos)                   continue;

                sprintf(buff,"%07d", FLrec[jj].kmcode);
                if(NULL == strstr(wk_calc, buff))                continue;

                if(FLrec[jj].mecd > 0) {
                    flst->mecd  = FLrec[jj].mecd;
                    flst->ctlno = FLrec[jj].ctlno;  break;
                }
            }
        }

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "計算項目結果(算出毎) UCD[%d] ZAI[%d] KEKKA[%s] FRML[%s]",
            mch_ucd, mch_zai, calkek[mch_ucd][mch_zai].kekka, MstCalc[ii].calc);
        fprintf(Dbg_fp,"計算項目結果(算出毎) UCD[%d] ZAI[%d] KEKKA[%s] FRML[%s]\n",
                mch_ucd, mch_zai, calkek[mch_ucd][mch_zai].kekka, MstCalc[ii].calc);
    }
    if(f_fnd == 0) {
        flst->f_calc = 2;  return;
    }

    if(calkek[1][1].kekka[0] != '\0')
          sprintf(flst->kekka,"%s", calkek[1][1].kekka);
    else if(calkek[0][1].kekka[0] != '\0')
          sprintf(flst->kekka,"%s", calkek[0][1].kekka);
    else if(calkek[1][0].kekka[0] != '\0')
          sprintf(flst->kekka,"%s", calkek[1][0].kekka);
    else  sprintf(flst->kekka,"%s", calkek[0][0].kekka);

    sprintf(flst->raw,"%s", flst->kekka);

    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "計算項目結果 KM[%d] UCD[%s] ZAI[%s] KEK[%s] ME[%d] CTL[%d]",
        flst->kmcode, flst->usercode, flst->zaicode, flst->kekka, flst->mecd, flst->ctlno);
    fprintf(Dbg_fp,"計算項目結果 KM[%d] UCD[%s] ZAI[%s] KEK[%s] ME[%d] CTL[%d]\n",
            flst->kmcode, flst->usercode, flst->zaicode, flst->kekka, flst->mecd, flst->ctlno);

    return;
}

/**/
static void sFncMeErrorChk(KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncMeErrorChk()                                               *
*  機能概要　：分析機エラーチェック処理 (エラーステータス10件まで対応)        *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    *buf1, *tmptr, *errtkn;
    int     ii, jj, dcnt;
    int     dsppri[2], dspidx[2];
    struct ERSTS {
      char    erbuf[2 +1];
      char    trcode[1 +1];
      short   procf;
      char    skncond[1 +1];
      int     pri;
    } mests[10];

    /* エラーステータスを分割 */
    memset(&mests[0],'\0', (sizeof(struct ERSTS) *10));
    for(ii = 0 ; ii < 10 ; ii++) {
        if(ii == 0)  buf1 = flst->errcd2;
        else         buf1 = NULL;

        if(NULL == (errtkn = strtok_r(buf1, ",", &tmptr))) {
            dcnt = ii;  break;
        }
        sprintf(mests[ii].erbuf,"%s", errtkn);
    }
    if(ii == 0)  return;


    /* マスタとの照合 */
    for(ii = 0 ; ii < dcnt ; ii++) {
        for(jj = 0 ; jj < MstMeSts_cnt ; jj++) {
            if(strcmp(mests[ii].erbuf, MstMests[jj].zscode) != 0)
                continue;

            sprintf(mests[ii].trcode,"%s", MstMests[jj].trcode);
            mests[ii].procf = MstMests[jj].procf;
            sprintf(mests[ii].skncond,"%s", MstMests[jj].skncond);
            mests[ii].pri = MstMests[jj].pri;
            break;
        }
        if(jj >= MstMeSts_cnt) {                      /* エラーがマスタに無いときは無視する */
            strcpy(mests[ii].trcode,"?");
            mests[ii].procf = 3;
        }
        fprintf(Dbg_fp,"分析機Err(個別) FNM[%s] ER[%s] TR[%s] PRC[%d] SKN[%s] PRI[%d]\n",
                flst->fname, mests[ii].erbuf, mests[ii].trcode, mests[ii].procf, mests[ii].skncond, mests[ii].pri);
    }

    /* 優先度の高い2つのステータスを抽出 */
    dsppri[0] = dsppri[1] = 0;
    dspidx[0] = dspidx[1] = 0;
    for(ii = 0 ; ii < dcnt ; ii++) {
        if(mests[ii].procf > 2)  continue;
        if(dsppri[0] == 0)  { dsppri[0] = mests[ii].pri;  dspidx[0] = ii;  continue; }

        if(dsppri[0] > mests[ii].pri) {               /* より高い優先度があったとき */
            dsppri[1] = dsppri[0];      dspidx[1] = dspidx[0];
            dsppri[0] = mests[ii].pri;  dspidx[0] = ii;
            continue;
        }

        if(dsppri[1] == 0)                  { dsppri[1] = mests[ii].pri;  dspidx[1] = ii; }
        else if(dsppri[1] > mests[ii].pri)  { dsppri[1] = mests[ii].pri;  dsppri[1] = ii; }
    }

    if(dsppri[0] > 0) {
        ii = dspidx[0];
        flst->meerrsts[0] = mests[ii].trcode[0];
        flst->meerrprc = mests[ii].procf;
        if(mests[ii].skncond[0] != ' ' && mests[ii].skncond[0] != '\0')
            flst->kisyak_sts[0] = mests[ii].skncond[0];
        if(dsppri[1] > 0) {
            jj = dspidx[1];  flst->meerrsts[1] = mests[jj].trcode[0];
        }
    }

    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "分析機Err(決定) FNM[%s] ER[%s] PRC[%d] SKN[%s]",
        flst->fname, flst->meerrsts, flst->meerrprc, mests[ii].skncond);
    fprintf(Dbg_fp,"分析機Err(決定) FNM[%s] ER[%s] PRC[%d] SKN[%s]\n",
            flst->fname, flst->meerrsts, flst->meerrprc, mests[ii].skncond);

    return;
}

/**/
static void sFncKisyakChk(KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncKisyakChk()                                                *
*  機能概要　：希釈チェック処理                                               *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    int     ii;
    short   f_bound;
    double  dbl_kekka;

    if(flst->qcflg == 1)  return;                     /* Ctl結果は対象外 */
    if(flst->sts != 1)    return;                     /* 測定項目が揃っていない場合も対象外 */

    /* 結果値が無い場合はリターン */
    if(flst->kekka[0] == '\0') {
        flst->sts = 2;  return;
    }

    /* 再検、用手の場合はチェック自体が不要 */
    if(flst->c_kensa > 1 && flst->kensaphs[0] == 'K') {
        flst->sts = 2;  return;
    }

    dbl_kekka = (double)atof(flst->kekka);
    flst->kisyak_err = 0;

    /* 該当する希釈倍率マスタとの照合 */
    f_bound = 0;
    for(ii = 0 ; ii < MstKisyk_cnt ; ii++) {
        if(strcmp(MstKisyk[ii].kengrp, flst->kengrp) != 0)  continue;
        if(MstKisyk[ii].kmcode != flst->kmcode)             continue;

        f_bound = 0;

        /* 下限値の範囲内チェック */
        if(strncmp((MstKisyk[ii].kisyk_low +1),"999999999999",12) != 0) {
                                                      /* Double型の誤差を考慮した比較 */
            if(dbl_kekka > MstKisyk[ii].dbksk_low ||
              (fabs(dbl_kekka - MstKisyk[ii].dbksk_low) <=
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstKisyk[ii].dbksk_low)))))) {

                f_bound = 1;
            }
        }
        else  f_bound = 1;

        /* 高値チェック */
        if(strncmp((MstKisyk[ii].kisyk_hi +1),"999999999999",12) != 0) {
                                                      /* Double型の誤差を考慮した比較 */
            if(dbl_kekka < MstKisyk[ii].dbksk_hi ||
              (fabs(dbl_kekka - MstKisyk[ii].dbksk_hi) <=
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstKisyk[ii].dbksk_hi)))))) {

                f_bound++;
            }
        }
        else  f_bound++;

        if(f_bound == 2)  break;
    }

    if(f_bound == 2) {
        flst->kisyak_err = 1;
        if(flst->kisyak_sts[0] == ' ') {
            if(islower(MstKisyk[ii].kisyk_kbn[0]))
                  flst->kisyak_sts[0] = toupper(MstKisyk[ii].kisyk_kbn[0]);
            else  flst->kisyak_sts[0] = MstKisyk[ii].kisyk_kbn[0];
        }

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "希釈チェック(決定) FNM[%s] KM[%d] ER[%s]",
            flst->fname, flst->kmcode, flst->kisyak_sts);
        fprintf(Dbg_fp,"希釈チェック(決定) FNM[%s] KM[%d] ER[%s]\n",
                        flst->fname, flst->kmcode, flst->kisyak_sts);
    }

    flst->sts = 2;
    return;
}

/**/
static void sFncRngChkProc(KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncRngChkProc()                                               *
*  機能概要　：範囲チェック処理                                               *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    chksts[2][2][2][3];
    int     ii;
    short   mch_ucd, mch_sex, mch_zai, f_mch;
    double  dbl_kekka;

    if(flst->qcflg == 1)  return;                     /* Ctl結果は対象外 */
    if(flst->sts != 2)    return;                     /* 希釈CHKを経過していない場合も対象外 */

    /* 結果値が無い場合の処理 */
    if(flst->kekka[0] == '\0') {
        if(flst->meerrprc == 1 ||
          (flst->cksts[1] == ' ' && flst->meerrprc == 2)) {

            sFncKanrenChk(flst);                      /* 分析機ERR有りの場合は関連項目CHK呼出し */
        }
        flst->sts = 3;
        return;
    }


    dbl_kekka = (double)atof(flst->kekka);

    /* 該当する範囲チェックマスタの取得 */
    flst->cksts[0] = ' ';
    memset(chksts[0][0][0],'\0', 24);
    f_mch = 0;
    for(ii = 0 ; ii < MstRange_cnt ; ii++) {
        mch_ucd = mch_sex = mch_zai = 0;

        if(strcmp(MstRange[ii].kengrp, flst->kengrp) != 0)      continue;
        if(MstRange[ii].kmcode != flst->kmcode)                 continue;

        if(strncmp(MstRange[ii].usercode,"0000000", 7) != 0 &&
           strcmp(MstRange[ii].usercode, flst->usercode) != 0)  continue;

        if(MstRange[ii].sex[0] != '\0' &&
           MstRange[ii].sex[0] != flst->sex[0])                 continue;

        if(strncmp(MstRange[ii].zaicode,"000", 3) != 0 &&
           strcmp(MstRange[ii].zaicode, flst->zaicode) != 0)    continue;


        if(strncmp(MstRange[ii].usercode,"0000000", 7) != 0)  mch_ucd = 1;
        if(MstRange[ii].sex[0] != '\0')                       mch_sex = 1;
        if(strncmp(MstRange[ii].zaicode,"000", 3) != 0)       mch_zai = 1;


        /* 該当情報があれば範囲チェック実行 */
        f_mch = 1;
        if(MstRange[ii].uplow == 1) {                 /* 高値チェック */
            if(dbl_kekka > MstRange[ii].dbrng_hi &&
              (fabs(dbl_kekka - MstRange[ii].dbrng_hi) >
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstRange[ii].dbrng_hi)))))) {

                if(chksts[mch_ucd][mch_sex][mch_zai][0] == '\0') {
                    chksts[mch_ucd][mch_sex][mch_zai][0] = 'H'; /* チェックSTSを設定 */
                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "範囲CHKエラー(High) McUCD[%d] McSEX[%d] McZAI[%d]", mch_ucd, mch_sex, mch_zai);
                    fprintf(Dbg_fp,"範囲CHKエラー(High) McUCD[%d] McSEX[%d] McZAI[%d]\n", mch_ucd, mch_sex, mch_zai);
                }
            }
        }
        else if(MstRange[ii].uplow == 2) {            /* 低値チェック */
            if(dbl_kekka < MstRange[ii].dbrng_low &&
              (fabs(dbl_kekka - MstRange[ii].dbrng_low) >
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstRange[ii].dbrng_low)))))) {

                if(chksts[mch_ucd][mch_sex][mch_zai][0] == '\0') {
                    chksts[mch_ucd][mch_sex][mch_zai][0] = 'L'; /* チェックSTSを設定 */
                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "範囲CHKエラー(Low) McUCD[%d] McSEX[%d] McZAI[%d]", mch_ucd, mch_sex, mch_zai);
                    fprintf(Dbg_fp,"範囲CHKエラー(Low) McUCD[%d] McSEX[%d] McZAI[%d]\n", mch_ucd, mch_sex, mch_zai);
                }
            }
        }
    }

    if(f_mch == 0) {
        fprintf(Dbg_fp,"該当する範囲チェックマスタが見つかりません。(正常扱い)Rack[%s] KM[%d] USRCD[%s] SEX[%s]\n",
                flst->rackid, flst->kmcode, flst->usercode, flst->sex);
    }

    if(chksts[1][1][1][0] != '\0')       flst->cksts[0] = chksts[1][1][1][0];
    else if(chksts[1][0][1][0] != '\0')  flst->cksts[0] = chksts[1][0][1][0];
    else if(chksts[1][0][0][0] != '\0')  flst->cksts[0] = chksts[1][0][0][0];
    else if(chksts[0][0][1][0] != '\0')  flst->cksts[0] = chksts[0][0][1][0];
    else if(chksts[0][0][0][0] != '\0')  flst->cksts[0] = chksts[0][0][0][0];


    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "範囲チェック(決定) FNM[%s] KM[%d] ER[%s]", flst->fname, flst->kmcode, flst->cksts);
    fprintf(Dbg_fp,"範囲チェック(決定) FNM[%s] KM[%d] ER[%s]\n",
            flst->fname, flst->kmcode, flst->cksts);


    /* 関連項目チェック */
    if(flst->meerrprc == 1 ||
      (flst->cksts[1] == ' ' &&
      (flst->meerrprc == 2 || flst->kisyak_sts[0] != ' ' || flst->cksts[0] != ' '))) {

        sFncKanrenChk(flst);
    }

    flst->sts = 3;
    return;
}

/**/
static void sFncKanrenChk(KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncKanrenChk()                                                *
*  機能概要　：関連チェック処理                                               *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    wk_mests[2 +1];
    int     ii, jj, mm, nn, pp;
    int     idx[10];
    short   errtmp;

    for(ii = 0 ; ii < 10 ; ii++)
        idx[ii] = -1;

    wk_mests[0] = '\0';
    if(flst->meerrprc == 1)  strcpy(wk_mests, flst->meerrsts);

    errtmp = pp = 0;
    for(ii = 0 ; ii < MstKnren_cnt ; ii++) {
        if(MstKnren[ii].kmcode != flst->kmcode)  continue;

        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, flst->rackid) != 0)  continue;
            if(FLrec[jj].pos != flst->pos)                   continue;
            if(FLrec[jj].kmcode == flst->kmcode)             continue;

            if(MstKnren[ii].kanrenkm != FLrec[jj].kmcode)    continue;

            FLrec[jj].cksts[1] = 'K';  errtmp = 1;
            if(pp < 10)  { idx[pp] = jj;  pp++; }
            if(wk_mests[0] == '\0' && FLrec[jj].meerrprc == 1)
                strcpy(wk_mests, FLrec[jj].meerrsts);

            for(mm = 0 ; mm < MstKnren_cnt ; mm++) {
                if(MstKnren[mm].kmcode != FLrec[jj].kmcode)  continue;

                for(nn = 0 ; nn < FLrec_cnt ; nn++) {
                    if(strcmp(FLrec[nn].rackid, flst->rackid) != 0)  continue;
                    if(FLrec[nn].pos != flst->pos)                   continue;
                    if(FLrec[nn].kmcode == FLrec[jj].kmcode)         continue;

                    if(MstKnren[mm].kanrenkm != FLrec[nn].kmcode)    continue;

                    FLrec[nn].cksts[1] = 'K';
                    if(pp < 10)  { idx[pp] = nn;  pp++; }
                    if(wk_mests[0] == '\0' && FLrec[nn].meerrprc == 1)
                        strcpy(wk_mests, FLrec[nn].meerrsts);
                    break;
                }

                break;
            }
        }
    }

    if(errtmp == 1)  flst->cksts[1] = 'K';

    if(wk_mests[0] == '\0' || wk_mests[0] == ' ')  return;

    /* 関連ERRで分析機ERRが"照合のみ"の項目がある場合には、 */
    /* その分析機ERRのSTSを関連項目に設定する */
    for(ii = 0 ; ii < pp ; ii++) {
        jj = idx[ii];
        fprintf(Dbg_fp,"[%s]--[%d]...KM[%d] MESTS[%s] CALC[%d]\n",
                __FILE__,__LINE__,FLrec[jj].kmcode,wk_mests,FLrec[jj].f_calc);
        if(FLrec[jj].f_calc == 1)                     /* 計算項目に対して"照合のみ"ERRのSTSを設定 */
            strcpy(FLrec[jj].meerrsts, wk_mests);
        FLrec[jj].meerrprc = 1;
    }

    return;
}

/**/
static void sFncMKSatKekka()
/******************************************************************************
*  関 数 名　：sFncMKSatKekka()                                               *
*  機能概要　：一般検体分のサテライト向け検査結果ファイル作成処理             *
*              (同時に再検用測定依頼ファイル作成)                             *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
******************************************************************************/
{
    char    b_tmp[101], fpth[101], irfpth[101], kkfpth[101], rnmfpth[101];
    char    tmbuf[21], irfnm[51], kkfnm[51], cmd[256];
    int     ii, jj, mm, rtn, len;
    short   f_saiken;
    FILE    *fp_ir, *fp_kk, *fp_sk;
    time_t  tlsec;
    struct stat  st;
    struct tm  *tms;

    /* 現在日時を取得 */
    time(&tlsec);
    if(NULL != (tms = localtime(&tlsec))) {
        sprintf(tmbuf,"%d%02d%02d%02d%02d%02d", (tms->tm_year +1900),
            (tms->tm_mon +1), tms->tm_mday, tms->tm_hour, tms->tm_min, tms->tm_sec);
    }

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].qcflg == 1)  continue;           /* Ctl結果は対象外 */
        if(FLrec[ii].sts != 3)    continue;           /* 範囲チェックまで通っていない場合も対象外 */

        /* 依頼ファイルオープン */
        for(jj = 0 ; jj < 2 ; jj++) {
            if(jj == 0)       strcpy(b_tmp, SKNIRAI_SUFFIX);
            else if(jj == 1)  strcpy(b_tmp, NEWFL_SUFFIX);

            sprintf(irfnm,"%s%s_____%03d.%s", IRAI_PREFIX, FLrec[ii].rackid, FLrec[ii].pos, b_tmp);
            sprintf(irfpth,"%s/%s", IRAINEW_PATH, irfnm);
            if(stat(irfpth, &st) == 0 && st.st_size > 0)  break;
        }
        if(jj >= 2) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMKSatKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "依頼ファイルが見つかりません。File[%s] ERR[%d]", irfpth, errno);
            fprintf(Dbg_fp,"依頼ファイルが見つかりません。File[%s] ERR[%d]\n", irfpth, errno);
            sFncSetFlstSts(&FLrec[ii], -1);  continue;
        }

        if(NULL == (fp_ir = fopen(irfpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMKSatKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "依頼ファイルのファイルオープンに失敗しました。File[%s] ERR[%d]", irfpth, errno);
            fprintf(Dbg_fp,"依頼ファイルファイルオープンに失敗。File[%s] ERR[%d]\n", irfpth, errno);
            sFncSetFlstSts(&FLrec[ii], -1);  continue;
        }

        /* 検体単位のサテライト向け結果ファイルオープン */
        sprintf(kkfnm,"%s_____%03d_%s.tmp", FLrec[ii].rackid, FLrec[ii].pos, tmbuf);
        sprintf(kkfpth,"%s/%s", SATKEKKA_PATH, kkfnm);

        if(NULL == (fp_kk = fopen(kkfpth,"w"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMKSatKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "結果ファイルのオープンに失敗しました。File[%s] ERR[%d]", kkfpth, errno);
            fprintf(Dbg_fp,"結果ファイルのオープンに失敗。File[%s] ERR[%d]\n", kkfpth, errno);
            sFncSetFlstSts(&FLrec[ii], -1);  continue;

        }


        f_saiken = 0;
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, FLrec[ii].rackid) != 0)  continue; 
            if(FLrec[jj].pos != FLrec[ii].pos)                   continue;


            /* サテライト向け結果ファイル書込み */
            if(FLrec[jj].f_kessei != 2 && FLrec[jj].f_calc < 2) {
                rtn = sFncWriteSatKekka(fp_ir, fp_kk, &FLrec[jj]);
                if(rtn != RTN_OK)  { sFncSetFlstSts(&FLrec[jj], -1);  break; }
            }

            /* 分析機エラー、チェックエラー有りの場合は再検依頼を生成(用手の希釈以外) */
            if(FLrec[jj].kensaphs[0] != 'K' && FLrec[jj].f_kessei == 0) {  /* 初検で非血清項目のみ対象 */
                if(FLrec[jj].meerrprc != 1) {         /* 分析機Errが"照合のみ"以外のとき */
                    if(FLrec[jj].meerrprc == 2 ||
                      (FLrec[jj].kisyak_sts[0] != 'M' &&
                      (FLrec[jj].kisyak_sts[0] != ' ' || strcmp(FLrec[jj].cksts,"  ") != 0))) {

                        rtn = sFncWriteSaiIrai(fp_ir, &FLrec[jj]);   /* 再検依頼を生成 */
                        if(rtn != RTN_OK)  { sFncSetFlstSts(&FLrec[jj], -1);  break; }
                    }
                }
            }

            if(FLrec[jj].f_saiken == 1)  f_saiken = 1;
        }
        if(rtn != RTN_OK) {
            fclose(fp_ir);  fclose(fp_kk);
            continue;
        }

        fclose(fp_ir);
        fclose(fp_kk);

        /* 結果作成済み情報の構造体MAX数を超えたとき */
        if(KekFL_cnt >= FLARRY_MAX) {
            fclose(fp_kk);  unlink(kkfpth);           /* 結果ファイルの削除 */
            break;
        }

        /* Sat用結果ファイル等のリネーム処理 */
        len = strlen(kkfnm);
        if(strncmp((kkfnm+len-3),"tmp", 3) == 0)  strcpy((kkfnm+len-3),"dat");
        sprintf(rnmfpth,"%s/%s", SATKEKKA_PATH, kkfnm);
        rename(kkfpth, rnmfpth);                      /* Sat用結果ファイルをリネーム */

        /* 結果一時ファイルのリネーム処理(end下へ移動) */
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, FLrec[ii].rackid) != 0)  continue;
            if(FLrec[jj].pos != FLrec[ii].pos)                   continue;

            len = strlen(FLrec[jj].fname);
            if(strncmp((FLrec[jj].fname+len-3),"dat", 3) == 0)
                strcpy((FLrec[jj].fname+len-3),"end");
            sprintf(rnmfpth,"%s/%s", KEKKAEND_PATH, FLrec[jj].fname);

            mm = 0;
            if(stat(rnmfpth, &st) == 0) {             /* ファイルが既に存在するとき */
                strcat(FLrec[jj].fname,"_00");
                len = strlen(FLrec[jj].fname);

                for(mm = 1 ; mm <= 10 ; mm++) {
                    sprintf(b_tmp,"%02d", mm);
                    strcpy((FLrec[jj].fname+len-2), b_tmp);
                    sprintf(rnmfpth,"%s/%s", KEKKAEND_PATH, FLrec[jj].fname);
                    if(stat(rnmfpth, &st) != 0)  break;
                }
            }

            if(mm <= 10)  rename(FLrec[jj].path, rnmfpth);
            else {
                sprintf(cmd,"/usr/bin/cp -p %s %s", FLrec[jj].path, rnmfpth);
                system(cmd);
                unlink(FLrec[jj].path);
            }
        }

        sFncSetFlstSts(&FLrec[ii], 4);                /* ステータスを"4"に設定 */

        /* Line用検査結果出力の配列にコピー (ラックID,POS単位) */
        FLrec[ii].f_saiken = f_saiken;
        memcpy(&KekFL[KekFL_cnt], &FLrec[ii], sizeof(KEKFL_STR));
        KekFL_cnt++;
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
    return;
}

/**/
static int sFncWriteSatKekka(FILE *irfp, FILE *kkfp, KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncWriteSatKekka()                                            *
*  機能概要　：サテライト向け検査結果ファイル作成処理                         *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    fbuf[512], buff[101], wk_buff[101];
    int     ii, c_st, c_en, c_dl, c_bg, wk_kmcode;
    time_t  tlsec;
    struct tm  *tms;

    rewind(irfp);
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, irfp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strlen(fbuf) < 50)  continue;

        c_st = c_en = c_dl = c_bg = 0;
        for(ii = 0 ; ii < strlen(fbuf) ; ii++) {
            if(fbuf[ii] == ',')  {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            if(c_dl == 2)                             /* 検査開始日と処理日出力 */
                sprintf(wk_buff,"%.*s,", c_en, fbuf);

            else if(c_dl == 3)  c_bg = c_st;

            else if(c_dl == 6) {
                if(flst->f_kessei > 0) {              /* 血清項目に関する処理 */
                    if(flst->chnum == sAppEnv.nyubi_ch && strcmp(buff, sAppEnv.nyubi_km) != 0)
                        break;
                    else if(flst->chnum == sAppEnv.youkets_ch && strcmp(buff, sAppEnv.youkets_km) != 0)
                        break;
                    else if(flst->chnum == sAppEnv.oudan_ch && strcmp(buff, sAppEnv.oudan_km) != 0)
                        break;
                }
                else {
                    wk_kmcode = atoi(buff);
                    if(wk_kmcode != flst->kmcode)  break;
                }
                fprintf(kkfp,"%s", wk_buff);          /* 上で設定した検査開始日と処理日を出力 */
            }

            else if(c_dl == 24) {                     /* No.28の分析機SEQまで出力 */
                fprintf(kkfp,"%.*s,%s,%02d,%02d0000,%d,%s,", (c_en-c_bg), (fbuf+c_bg), ME_KUBUN,
                        flst->mecd, flst->mecd, flst->meseqno, flst->meerrsts);
                fprintf(kkfp,"%s,%03d,R,", flst->rstime, flst->chnum);
            }
            else if(c_dl == 27)  c_bg = c_st;
            else if(c_dl == 40) {                     /* No.27の材料コードからNo.40の緊急依頼ロットNo.まで出力 */
                fprintf(kkfp,"%.*s,", (c_en-c_bg), (fbuf+c_bg));
                fprintf(kkfp," , , ,%8s,,,,,%s,,,,3,0,0,0,0, , , , , , ,,,,,,,%d,",
                        flst->raw, flst->kekka, flst->ctlno);
            }
            else if(c_dl == 55)  c_bg = c_st;
            else if(c_dl == 56) {                     /* 結果のNo.77の検査SEQ～No.94検査フラグを出力 */
                if(flst->f_kessei > 0)               strcpy(wk_buff,"H"); /* 血清項目は"H"固定 */
                else if(flst->kisyak_sts[0] == 'M')  strcpy(wk_buff,"R"); /* 希釈再検(用手)の場合 */
                else if(flst->meerrprc == 1)         strcpy(wk_buff,"R"); /* "照合のみ"の分析機ERRの場合 */
                else if(flst->meerrprc == 2 ||
                        strcmp(flst->cksts,"  ") != 0 || flst->kisyak_sts[0] != ' ') {
                      strcpy(wk_buff,"A");            /* その他自動再検の場合 */
                }
                else  strcpy(wk_buff,"X");            /* 正常時 */

                fprintf(kkfp,"%.*s,,,,,,,,,,,,1,1,,1,%s,", (c_en-c_bg), (fbuf+c_bg), wk_buff);
                /* 分析機測定では補正フラグを"1"に設定 */
                /* 併せて採用フラグ、結果優先フラグも"1"固定に設定 */


                if(flst->cksts[0] == 'H')       strcpy(buff,"3,0,");
                else if(flst->cksts[0] == 'L')  strcpy(buff,"4,0,");
                else                            strcpy(buff,"1,0,");

                if(flst->cksts[1] != ' ')       strcat(buff,"2,0,0,0,0,0,0,0,");
                else                            strcat(buff,"1,0,0,0,0,0,0,0,");
                if(flst->kisyak_err == 1)       strcat(buff,"2,0,0,0,0,");
                else                            strcat(buff,"1,0,0,0,0,");
                if(flst->meerrsts[0] != ' ')    strcat(buff,"2,0,0,0,0,,,,");  /* 予備フラグ設定 */
                else                            strcat(buff,"1,0,0,0,0,,,,");

                time(&tlsec);
                if(NULL != (tms = localtime(&tlsec))) {
                    fprintf(kkfp,"%s%d-%02d-%02d %02d:%02d:%02d\n",
                        buff, (tms->tm_year +1900), (tms->tm_mon +1), tms->tm_mday,
                        tms->tm_hour, tms->tm_min, tms->tm_sec);
                }
                fflush(kkfp);

                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "サテライト向け結果ファイル出力 Rack[%s] POS[%d] CH[%d] KEK[%s]",
                    flst->rackid, flst->pos, flst->chnum, flst->kekka);
                fprintf(Dbg_fp,"Sat向け結果ファイル出力 Rack[%s] POS[%d] CH[%d] KEK[%s]\n",
                        flst->rackid, flst->pos, flst->chnum, flst->kekka);
                break;
            }
        }
    }

    return(RTN_OK);
}

/**/
static int sFncWriteSaiIrai(FILE *irfp, KEKFL_STR *flst)
/******************************************************************************
*  関 数 名　：sFncWriteSaiIrai()                                             *
*  機能概要　：再検用測定依頼ファイル作成処理                                 *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    fpth[101], fbuf[512], buff[256];
    char    b_tmp[101];
    int     ii, c_st, c_en, c_dl, wk_kmcode;
    short   wk_kenkaisu;
    FILE    *sknfp;

    sprintf(fpth,"%s/%s%s_____%03d.%s",
            IRAINEW_PATH, IRAI_PREFIX, flst->rackid, flst->pos, SKNIRAI_SUFFIX);

    if(NULL == (sknfp = fopen(fpth,"a"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "再検用依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"再検用依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    rewind(irfp);
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, irfp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strlen(fbuf) < 50)  continue;

        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < strlen(fbuf) ; ii++) {
            if(fbuf[ii] == ',')  {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            memcpy(buff, (fbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            sFncTrim(buff);

            /* 初検の依頼情報を取得して編集 */
            if(c_dl == 6) {
                wk_kmcode = atoi(buff);
                if(wk_kmcode != flst->kmcode)  break;
            }
            else if(c_dl == 7) {
                wk_kenkaisu = (short)atoi(buff) +1;
                sprintf(b_tmp,"%d", wk_kenkaisu);
                fbuf[c_st] = b_tmp[0];                /* 検査回数を設定 */
            }
            else if(c_dl == 11)  fbuf[c_st] = 'K';    /* 検査工程区分を設定 */
            else if(c_dl == 37) {
                if(flst->kisyak_sts[0] != ' ')
                    fbuf[c_st] = flst->kisyak_sts[0]; /* 希釈条件を設定 */
                break;
            }
        }
        if(wk_kmcode != flst->kmcode)  continue;


        /* 再検依頼情報のファイル出力 */
        fprintf(sknfp,"%s", fbuf);
        flst->f_saiken = 1;                           /* 再検実施フラグ設定 */


        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "再検依頼情報のファイル出力 Rack[%s] POS[%d] CH[%d] MEerr[%s] MEPRC[%d] KISYAK[%s] CHK[%s]",
            flst->rackid, flst->pos, flst->chnum, flst->meerrsts, flst->meerrprc, flst->kisyak_sts, flst->cksts);
        fprintf(Dbg_fp,"再検依頼情報のファイル出力 Rack[%s] POS[%d] CH[%d] MEerr[%s] MEPRC[%d] KISYAK[%s] CHK[%s]\n",
                flst->rackid, flst->pos, flst->chnum, flst->meerrsts, flst->meerrprc, flst->kisyak_sts, flst->cksts);

        break;
    }
    fclose(sknfp);

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static void sFncCtlKekkaProc()
/******************************************************************************
*  関 数 名　：sFncCtlKekkaProc()                                             *
*  機能概要　：サテライト向けコントロール結果ファイル作成処理                 *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    qkfpth[101], qkfnm[51], rnmfpth[101], tmbuf[21];
    char    cmd[256], buff[256], wk_lotno[20 +1], buf1[21];
    int     ii, jj, len;
    double  wk_valuex, wk_mstsd, wk_sd, wk_dbl;
    time_t  tlsec;
    FILE    *fp_qk;
    struct stat  st;
    struct tm  *tms;

    /* 現在日時を取得 */
    time(&tlsec);
    if(NULL != (tms = localtime(&tlsec))) {
        sprintf(tmbuf,"%d%02d%02d%02d%02d%02d", (tms->tm_year +1900),
            (tms->tm_mon +1), tms->tm_mday, tms->tm_hour, tms->tm_min, tms->tm_sec);
    }

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].qcflg != 1)  continue;           /* Ctl結果以外は対象外 */
        if(FLrec[ii].sts > 0)     continue;           /* 既に結果ファイル作成済みのものは対象外 */

        /* 測定結果の読込み */
        if(sFncGetRsltTmp(&FLrec[ii]) != RTN_OK)
            sFncSetFlstSts(&FLrec[ii], 10);       /* NGの場合はstsを"10"に設定 */

        /* サテライト向けCtl結果ファイルオープン */
        sprintf(qkfnm,"CT_%.10s_%s%d.tmp", (FLrec[ii].fname +5), tmbuf, FLrec[ii].chnum);
        sprintf(qkfpth,"%s/%s", SATKEKKA_PATH, qkfnm);

        if(NULL == (fp_qk = fopen(qkfpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCtlKekkaProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Ctl結果ファイルのオープンに失敗しました。File[%s] ERR[%d]", qkfpth, errno);
            fprintf(Dbg_fp,"Ctl結果ファイルのオープンに失敗。File[%s] ERR[%d]\n", qkfpth, errno);
            continue;

        }

        /* Ctlマスタの該当情報サーチ */
        for(jj = 0 ; jj < MstCtl_cnt ; jj++) {
            if(MstCtl[jj].chnum != FLrec[ii].chnum)  continue;
            if(strncmp(MstCtl[jj].ctlknd, (FLrec[ii].kenid +2), 3) != 0)
                continue;

            wk_valuex = (double)atof(MstCtl[jj].ctrlx);
            wk_mstsd  = (double)atof(MstCtl[jj].ctrlsd);
            sprintf(wk_lotno,"%s", MstCtl[jj].lotno);
            break;
        }
        if(jj >= MstCtl_cnt) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCtlKekkaProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Ctlマスタに設定されていません。FNM[%s] CH[%d] CTLKND[%.3s]", FLrec[ii].fname, FLrec[ii].chnum, (FLrec[ii].kenid +2));
            fprintf(Dbg_fp,"Ctlマスタに設定されていません。FNM[%s] CH[%d] CTLKND[%.3s]\n",
                               FLrec[ii].fname, FLrec[ii].chnum, (FLrec[ii].kenid +2));
            continue;
        }

        /* SD値の算出 */
        wk_sd = (double)atof(FLrec[ii].kekka);
fprintf(Dbg_fp,"QCkek[%f]...", wk_sd);
        wk_sd = (wk_sd - wk_valuex) / wk_mstsd;
        wk_dbl = wk_sd-(int)(wk_sd/1);
        sprintf(buf1,"%f", (wk_sd-(int)(wk_sd/1)));
fprintf(Dbg_fp,"SDdbl[%f] RST[%f]\n", wk_sd, wk_dbl);

        if(fabs(wk_dbl -(double)0) <=                 /* 小数点以下が0のとき */
           (DBL_EPSILON * fmax(1, fmax(fabs(wk_dbl), fabs((double)0))))) {
            sprintf(buff,"%d", (int)(wk_sd/1));
        }
        else if(strncmp(buf1,"0.000000", 8) == 0)     /* 小数点以下が0のとき(上の条件に該当しないとき) */
            sprintf(buff,"%d", (int)(wk_sd/1));
        else if((int)(wk_sd/1) >= 0) {
            if(buf1[0] == '-')
                  sprintf(buff,"%d", ((int)(wk_sd/1) -1));
            else  sprintf(buff,"%d", ((int)(wk_sd/1) +1));
        }
        else      sprintf(buff,"%d", ((int)(wk_sd/1) -1));
        fprintf(Dbg_fp,"buff[%s]\n",buff);

        if(atoi(buff) > 9)        strcpy(buff,"9");
        else if(atoi(buff) < -9)  strcpy(buff,"-9");


        /* チャネルNo.に該当する項目コード分のレコード出力 */
        for(jj = 0 ; jj < MstChanl_cnt ; jj++) {
            if(MstChanl[jj].chnum != FLrec[ii].chnum) /* チャネルマスタとのチャネルNo.照合 */
                continue;

            /* 結果レコード出力 */
            fprintf(fp_qk,"%.4s-%.2s-%.2s,%s,%02d,%02d0000,,%07d,%03d,%d,",
                sAppEnv.udate, (sAppEnv.udate +4), (sAppEnv.udate +6), ME_KUBUN,
                FLrec[ii].mecd, FLrec[ii].mecd, MstChanl[jj].kmcode, FLrec[ii].chnum, FLrec[ii].ctlno);

            fprintf(fp_qk,"%.3s,0,  , ,,0,0,0,0,0,%-20s,%8s,%8s, ,%s,%s,0,,,0,,,",
                (FLrec[ii].kenid +2), wk_lotno, FLrec[ii].kekka, FLrec[ii].kekka, FLrec[ii].rstime, buff);

            time(&tlsec);
            if(NULL != (tms = localtime(&tlsec))) {
                fprintf(fp_qk,"%d-%02d-%02d %02d:%02d:%02d\n",
                    (tms->tm_year +1900), (tms->tm_mon +1), tms->tm_mday,
                    tms->tm_hour, tms->tm_min, tms->tm_sec);
            }
        }

        FLrec[ii].sts = 4;
        fclose(fp_qk);


        /* Sat用結果ファイルのリネーム処理 */
        len = strlen(qkfnm);
        strcpy((qkfnm+len-4),".dat");
        sprintf(rnmfpth,"%s/%s", SATKEKKA_PATH, qkfnm);

        if(stat(rnmfpth, &st) == 0) {                 /* ファイルが現存するとき */
            sprintf(cmd,"/usr/bin/cp -p %s %s", qkfpth, rnmfpth);
            system(cmd);
            unlink(qkfpth);
        }
        else  rename(qkfpth, rnmfpth);

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "サテライト向けCtl結果ファイル出力 FNM[%s] CTLSBT[%.3s] CH[%d] CTLNO[%d] KEK[%s] SD[%s]",
            qkfnm, (FLrec[ii].kenid +2), FLrec[ii].chnum, FLrec[ii].ctlno, FLrec[ii].kekka, buff);
        fprintf(Dbg_fp,"Sat向けCtl結果ファイル出力 FNM[%s] CTLSBT[%.3s] CH[%d] CTLNO[%d] KEK[%s] SD[%s]\n",
                qkfnm, (FLrec[ii].kenid +2), FLrec[ii].chnum, FLrec[ii].ctlno, FLrec[ii].kekka, buff);


        /* Ctl結果一時ファイルのリネーム */
        len = strlen(FLrec[ii].fname);
        if(strncmp((FLrec[ii].fname+len-3),"dat", 3) == 0)
            strcpy((FLrec[ii].fname+len-3),"end");
        sprintf(rnmfpth,"%s/%s", KEKKAEND_PATH, FLrec[ii].fname);

        if(rename(FLrec[ii].path, rnmfpth) < 0) {
            sprintf(cmd,"/usr/bin/cp -p %s %s", FLrec[ii].path, rnmfpth);
            system(cmd);
            unlink(FLrec[ii].path);
        }
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return;
}

/**/
static void sFncMkLineKekka()
/******************************************************************************
*  関 数 名　：sFncMkLineKekka()                                              *
*  機能概要　：Line側への検査結果情報作成処理                                 *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    fpth[101], rnmfpth[101], fbuf[256], buff[101];
    char    cmd[256], wk_pos[4];
    char    rcvudate[8 +1];
    int     ii, jj, mm, len;
    short   f_mch, saiken_flg, f_sknirai;
    FILE    *fp_ir, *fp_kk, *fp;
    struct stat st;

    for(ii = 0 ; ii < KekFL_cnt ; ii++) {
        if(KekFL[ii].sts != 4)  continue;             /* 既にステータス変化したものは対象外 */

        /* 再検用の依頼ファイル参照かどうかの判定 */
        f_sknirai = 0;
        len = strlen(KekFL[ii].irfnm);
        if(strncmp((KekFL[ii].irfnm+len-6),"dat_01",6) == 0)
            f_sknirai = 1;


        /* 自動再検結果の場合はラック内の再検分が揃っているか確認 */
        /* (再々検の場合は対象外) */
        if(KekFL[ii].c_kensa > 1 && KekFL[ii].kensaphs[0] == 'K' && f_sknirai == 1) {

            sprintf(cmd,"/usr/bin/ls -t %s/%s*end* > %s 2>&1", LANEKEKEND_PATH, KekFL[ii].rackid, Temp_fpth);
            system(cmd);

            if(NULL == (fp = fopen(Temp_fpth,"r"))) {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "Line用検査結果ファイルリストのオープンに失敗しました。File[%s] ERR[%d]", Temp_fpth, errno);
                fprintf(Dbg_fp,"Line用検査結果ファイルオープンに失敗。File[%s] ERR[%d]\n", Temp_fpth, errno);
                continue;
            }

            if(NULL == fgets(fbuf, 256, fp)) {        /* 先頭の最新ファイルを取得 */
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetRsltTmp", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "Line用検査結果ファイルリストの読込みに失敗しました。File[%s] ERR[%d]", Temp_fpth, errno);
                fprintf(Dbg_fp,"Line用検査結果ファイルの読込みに失敗しました。File[%s] ERR[%d]\n", Temp_fpth, errno);

                fclose(fp);
                continue;
            }
            fclose(fp);

            len = strlen(fbuf);
            if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len = strlen(fbuf); }
            if(NULL != strstr(fbuf,"/usr/bin/ls"))  continue;

            if(NULL == (fp = fopen(fbuf,"r"))) {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "Line用検査結果ファイルのオープンに失敗しました。File[%s] ERR[%d]", fbuf, errno);
                fprintf(Dbg_fp,"Line用検査結果ファイルオープンに失敗。File[%s] ERR[%d]\n", fbuf, errno);
                continue;
            }

            for( ; ; ) {
                if(NULL == fgets(buff, 101, fp))  break;
                if(buff[0] == '\n' || buff[0] == ' ' || buff[0] == '\0')
                    continue;
                if(buff[14] != '1')  continue;        /* 再検分以外は対象外 */

                sprintf(wk_pos,"%.3s", buff);
                f_mch = 0;
                for(jj = 0 ; jj < KekFL_cnt ; jj++) {
                    if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;

                    KekFL[jj].sts = 6;
                    if(KekFL[jj].pos == atoi(wk_pos)) {
                        f_mch = 1;  break;
                    }
                }
                if(f_mch == 0)  break;                /* 再検POSの結果が未受信のとき */
            }
            fclose(fp);
            if(f_mch == 0) {
                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "ラックの検体結果が揃っていません。RackID[%s] POS[%.3s]", KekFL[ii].rackid, wk_pos);
                fprintf(Dbg_fp,"ラックの検体結果が揃っていません。RackID[%s] POS[%.3s]\n", KekFL[ii].rackid, wk_pos);
                for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                    if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                    KekFL[mm].sts = 10;               /* ラック分が揃っていない場合は"10"を設定 */
                }
                continue;
            }

            /* 再検結果が1ラック分揃ったとき */
            for(jj = 0 ; jj < KekFL_cnt ; jj++) {
                if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;
                KekFL[jj].sts = 7;
            }

            continue;                                 /* 自動再検分はここで戻る */
        }


        /* 以降は初検、再々検等の場合の処理 */
        sprintf(fpth,"%s/%s.end", LANEIRAI_PATH, KekFL[ii].rackid);
        if(NULL == (fp_ir = fopen(fpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line用依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line用依頼ファイルオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
            continue;
        }

        saiken_flg = 0;
        for(jj = 0 ; ; jj++) {
            if(NULL == fgets(fbuf, 256, fp_ir))  break;
            if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
                continue;
            len = strlen(fbuf);
            if(len < 10)  continue;

            /* ヘッダ情報のラインNo.チェック */
            if(jj == 0) {
                sprintf(rcvudate,"%.8s", fbuf);       /* Line依頼の受付日付取得 */

                sprintf(buff,"%d", sAppEnv.lineno);
                if(isdigit(fbuf[len-3]) && fbuf[len-3] != buff[0]) {
                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "Line用依頼ファイル内のLineNo.不一致 RackID[%s]", KekFL[ii].rackid);
                    fprintf(Dbg_fp,"Line用依頼ファイル内のLineNo.不一致 RackID[%s]\n", KekFL[ii].rackid);
                    break;                            /* 不一致の場合はbreak */
                }
                continue;
            }

            f_mch = 0;
            for(mm = 0 ; mm < KekFL_cnt ; mm++) {     /* RackPosが一致するかどうかチェック */
                if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;

                if(KekFL[mm].f_saiken == 1)  saiken_flg = 1;
                sprintf(buff,"%03d", KekFL[mm].pos);
                if(strncmp(fbuf, buff, 3) == 0) {
                    sprintf(KekFL[mm].line_kenno,"%.11s", (fbuf+3));
                    sFncTrim(KekFL[mm].line_kenno);
                    f_mch = 1;
                }

                KekFL[mm].sts = 5;
                if(f_mch == 1)  break;
            }
            if(f_mch == 0) {
                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "ラックの検体結果が揃っていません。RackID[%s] POS[%.3s]", KekFL[ii].rackid, buff);
                fprintf(Dbg_fp,"ラックの検体結果が揃っていません。RackID[%s] POS[%.3s]\n", KekFL[ii].rackid, buff);
                for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                    if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                    KekFL[mm].sts = 10;               /* ラック分が揃っていない場合は"10"を設定 */
                }
                break;
            }
        }
        fclose(fp_ir);

        if(f_mch == 0)  continue;


        /* 再々検、用手再検の場合、Line向け検査結果は作成済みとして扱う */
        /* ("sFncMkReSknKekka()"の関数にて別途作成する) */
        if(KekFL[ii].kensaphs[0] == 'K' && f_sknirai == 0) {
            for(jj = 0 ; jj < KekFL_cnt ; jj++) {
                if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;
                KekFL[jj].sts = 5;
            }
            continue;
        }


        /* Line側からの結果要求ファイル有無確認 */
        fprintf(Dbg_fp,"Line側からの結果要求ファイルサーチ...Rack[%s]...", KekFL[ii].rackid);
        sprintf(fpth,"%s/%s.dat", LANERSREQNEW_PATH, KekFL[ii].rackid);
        if(stat(fpth, &st) != 0) {
            for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;

                KekFL[mm].sts = 10;
            }
            fprintf(Dbg_fp,"無し\n");
            continue;                                 /* ファイルが無い場合はループ先頭に戻る */
        }

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "Line側からの結果要求ファイル検出 FNM[%s.dat]", KekFL[ii].rackid);
        fprintf(Dbg_fp,"存在確認\n");
        sprintf(rnmfpth,"%s/%s.end", LANERSREQEND_PATH, KekFL[ii].rackid);
        rename(fpth, rnmfpth);
        

        /* Line向け検査結果ファイル作成 */
        sprintf(fpth,"%s/%s_%d.tmp", LANEKEKKA_PATH, KekFL[ii].rackid, saiken_flg);
        if(NULL == (fp_kk = fopen(fpth,"w"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line用検査結果ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line用検査結果ファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);

            for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                KekFL[mm].sts = 10;                   /* この場合も"10"を設定 */
            }
            continue;
        }

        /* ヘッダ出力 */
        fprintf(fp_kk,"%s%s%d%c%c", rcvudate, KekFL[ii].rackid, sAppEnv.lineno, 0x0d, 0x0a);

        /* データ部出力 */
        for(jj = 1 ; jj <= 5 ; jj++) {
            for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                if(jj != (int)KekFL[mm].pos)                         continue;

                fprintf(fp_kk,"%03d%11.11s%d%c%c", KekFL[mm].pos,
                        KekFL[mm].line_kenno, KekFL[mm].f_saiken, 0x0d, 0x0a);
                break;
            }
        }
        fclose(fp_kk);


        /* Line用検査結果ファイル名のリネーム (.tmp -> .dat) */
        sprintf(rnmfpth,"%s/%s_%d.dat", LANEKEKKA_PATH, KekFL[ii].rackid, saiken_flg);
        rename(fpth, rnmfpth);

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "Line用検査結果ファイルの出力 FNM[%s_%d.dat]", KekFL[ii].rackid, saiken_flg);
        fprintf(Dbg_fp,"Line用検査結果ファイルの出力 FNM[%s_%d.dat]\n", KekFL[ii].rackid, saiken_flg);

        /* 再検無し、再々検、用手再検の場合はここでループ先頭に戻る */
        if(saiken_flg == 0 ||
          (KekFL[ii].c_kensa > 1 && KekFL[ii].kensaphs[0] == 'K')) {
            continue;
        }


        /* 再検有りの場合は依頼ファイルをリネーム */
        /* (再検の問合せ時に再検以外の検体の測定依頼が飛ばないようにする) */
        for(mm = 0 ; mm < KekFL_cnt ; mm++) {
            if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;

            sprintf(fpth,"%s/%s", IRAINEW_PATH, KekFL[mm].irfnm);
            len = strlen(KekFL[mm].irfnm);
            if(strncmp((KekFL[mm].irfnm+len-3),"dat", 3) != 0)  continue;

            strcpy((KekFL[mm].irfnm+len-3),"tmp");
            sprintf(rnmfpth,"%s/%s", IRAINEW_PATH, KekFL[mm].irfnm);
            rename(fpth, rnmfpth);
        }
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "再検準備のため初検依頼をリネーム Rack[%s]", KekFL[ii].rackid);
        fprintf(Dbg_fp,"再検準備のため初検依頼をリネーム Rack[%s]\n", KekFL[ii].rackid);
    }


    /* 完了した情報を構造体から削除 */
    KekFLtmp_cnt = 0;
    memset(&KekFL_tmp[0],'\0', (sizeof(KEKFL_STR) * FLARRY_MAX));
    for(ii = 0 ; ii < KekFL_cnt ; ii++) {
        if(KekFL[ii].sts < 4)    continue;
        if(KekFL[ii].sts == 5)   continue;
        if(KekFL[ii].sts == 10)  KekFL[ii].sts = 4;

        memcpy(&KekFL_tmp[KekFLtmp_cnt], &KekFL[ii], sizeof(KEKFL_STR));
        KekFLtmp_cnt++;
    }

    memcpy(&KekFL[0], &KekFL_tmp[0], (sizeof(KEKFL_STR) * FLARRY_MAX));
    KekFL_cnt = KekFLtmp_cnt;

    return;
}

/**/
static void sFncRnmStray()
/******************************************************************************
*  関 数 名　：sFncRnmStray()                                                 *
*  機能概要　：Line用収納トレー情報リネーム及び依頼情報リネーム処理           *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{

    char    fbuf[101], buff[101], fpth[101], rnmfpth[101];
    char    fnm[51], cmd[256], tmpth[101], tmbuf[21], iribuf[256];
    int     ii, jj, mm, nn, len;
    time_t  tlsec;
    FILE    *fp, *irifp;
    DIR     *dp;
    struct stat  st;
    struct tm  *tms;
    struct dirent  *dent;

    sprintf(cmd,"/usr/bin/ls %s/*dat* > %s 2>&1", LANESTRYNEW_PATH, Temp_fpth);
    system(cmd);

    /* 現在日時を取得 */
    time(&tlsec);
    if(NULL != (tms = localtime(&tlsec))) {
        sprintf(tmbuf,"%d%02d%02d%02d%02d%02d", (tms->tm_year +1900),
            (tms->tm_mon +1), tms->tm_mday, tms->tm_hour, tms->tm_min, tms->tm_sec);
    }

    /* 一時ファイル名の生成 */
    sprintf(tmpth,"/tmp/MD102_%d_%s", getpid(), tmbuf);


    /* ファイルリストのオープン */
    if(NULL == (fp = fopen(Temp_fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "Line側収納トレーファイルリストのオープンに失敗しました。File[%s] ERR[%d]", Temp_fpth, errno);
        fprintf(Dbg_fp,"Line側収納トレーファイルリストのオープンに失敗しました。File[%s] ERR[%d]\n", Temp_fpth, errno);
        return;
    }

    nn = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 101, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '\0')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n') {
            fbuf[len-1] = '\0';  len = strlen(fbuf);
        }
        if(NULL != strstr(fbuf,"/usr/bin/ls"))  break;
        if(stat(fbuf, &st) != 0)     continue;
        if(st.st_size < (size_t)20)  continue;


        /* Line側収納トレーファイルのリネーム処理 */
        len = strlen(fbuf);
        for(jj = (len-1) ; jj >= 0 ; jj--) {
            if(fbuf[jj] == '/')  break;
        }
        if(jj >= 0)  sprintf(fnm,"%s", (fbuf+jj+1));
        else         sprintf(fnm,"%s", fbuf);

        sprintf(rnmfpth,"%s/%s", LANESTRYMV_PATH, fnm);
        rename(fbuf, rnmfpth);
        nn++;
    }
    fclose(fp);

    if(nn > 0) {
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
              "[%d]件のLine側収納トレーファイルをリネームしました。", nn);
        fprintf(Dbg_fp,"[%d]件のLine側収納トレーファイルをリネーム\n", nn);
    }

    if(KekFL_cnt <= 0)  return;


    /* 以降は再検ラックに対する処理 */
    for(ii = 0 ; ii < KekFL_cnt ; ii++) {
        if(KekFL[ii].sts != 7)  continue;             /* 再検結果受信済み以外は対象外 */

/************************
        if(NULL == (dp = opendir(LANESTRYEND_PATH))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "収納トレイ情報格納Dirのオープンに失敗しました。Dir[%s] ERR[%d]", LANESTRYEND_PATH, errno);
            if(DbgFlg)  printf("収納トレイ情報格納Dirのオープンに失敗しました。Dir[%s] ERR[%d]\n", LANESTRYEND_PATH, errno);
            break;
        }

        nn = 0;
        for( ; ; ) {
            if(NULL == (dent = readdir(dp)))  break;
            if(dent->d_name[0] == '.')  continue;

            nn++;
        }
        closedir(dp);
printf("DIR nn[%d]\n",nn);
        if(nn == 0)  break;


        sprintf(cmd,"/usr/bin/grep %s `/usr/bin/ls -t %s/*` > %s 2>&1",
                KekFL[ii].rackid, LANESTRYEND_PATH, Temp_fpth);
        system(cmd);

        if(stat(Temp_fpth, &st) != 0)  continue;
        if(st.st_size < (size_t)15)    continue;
************************/


        /* 該当ラックがあった場合の依頼情報リネーム処理 */
        for(jj = 0 ; jj < 2 ; jj++) {
            if(jj == 0)
                  sprintf(cmd,"/usr/bin/ls %s/*%s*tmp > %s 2>&1", IRAINEW_PATH, KekFL[ii].rackid, tmpth);
            else  sprintf(cmd,"/usr/bin/ls %s/*%s*dat_01 > %s 2>&1", IRAINEW_PATH, KekFL[ii].rackid, tmpth);
            system(cmd);

            /* ファイルリストのオープン */
            if(NULL == (irifp = fopen(tmpth,"r"))) {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                       "再検対象依頼ファイルリストのオープンに失敗しました。File[%s] ERR[%d]", tmpth, errno);
                fprintf(Dbg_fp,"再検対象依頼ファイルリストのオープンに失敗しました。File[%s] ERR[%d]\n", tmpth, errno);
                continue;
            }

            for(nn = 0 ; ; ) {
                if(NULL == fgets(iribuf, 256, irifp))  break;
                if(iribuf[0] == '\n' || iribuf[0] == ' ' || iribuf[0] == '\0')
                    continue;
                if(NULL != strstr(iribuf,"/usr/bin/ls"))  break;

                len = strlen(iribuf);
                if(iribuf[len-1] == '\n') {
                    iribuf[len-1] = '\0';  len = strlen(iribuf);
                }

                strcpy(fpth, iribuf);
                if(jj == 0)  { strcpy((iribuf+len-3),"dat");  strcpy(rnmfpth, iribuf); }
                else {
                    for(mm = (len-1) ; mm >= 0 ; mm--) {
                        if(iribuf[mm] == '/') {
                            sprintf(fnm,"%s", (iribuf+mm+1));
                            break;
                        }
                    }
                    len = strlen(fnm);
                    strcpy((fnm+len-6),"end_01");  sprintf(rnmfpth,"%s/%s", IRAIEND_PATH, fnm);
                }

                /* 依頼ファイルのリネーム処理 */
                if(rename(fpth, rnmfpth) < 0) {
                    if(jj == 0) {
                        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "再検依頼ファイルのリネームに失敗しました。File[%s] ERR[%d]", fpth, errno);
                        fprintf(Dbg_fp,"再検依頼ファイルのリネームに失敗。File[%s] ERR[%d]\n", fpth, errno);

                        for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                            if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                            KekFL[mm].sts = 10;       /* この場合も"10"を設定 */
                        }
                        continue;
                    }

                    strcat(fnm,"_00");
                    len = strlen(fnm);

                    for(mm = 1 ; mm <= 10 ; mm++) {
                        sprintf(buff,"%02d", mm);
                        strcpy((fnm+len-2), buff);
                        sprintf(rnmfpth,"%s/%s", IRAIEND_PATH, fnm);
                        if(stat(rnmfpth, &st) != 0)  break;
                    }

                    if(mm <= 10)  rename(fpth, rnmfpth);
                    else {
                        sprintf(cmd,"/usr/bin/cp -p %s %s", fpth, rnmfpth);
                        system(cmd);
                        unlink(fpth);
                    }
                }
                nn++;
            }
            fclose(irifp);
            if(nn == 0)  continue;

            KekFL[ii].sts = 8;
            if(jj == 0) {
                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                      "再検対象の依頼ファイル(初検分)をリネームしました。RackID[%s]", KekFL[ii].rackid);
                fprintf(Dbg_fp,"再検対象の依頼ファイル(初検分)をリネーム。RackID[%s]\n", KekFL[ii].rackid);
            }
            else {
                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                      "再検依頼ファイルをend側にリネームしました。。RackID[%s]", KekFL[ii].rackid);
                fprintf(Dbg_fp,"再検依頼ファイルをend側にリネーム。RackID[%s]\n", KekFL[ii].rackid);
            }
        }

        for(jj = 0 ; jj < KekFL_cnt ; jj++) {
            if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;
            KekFL[jj].sts = 8;
        }
    }


    /* 完了した情報を構造体から削除 */
    KekFLtmp_cnt = 0;
    memset(&KekFL_tmp[0],'\0', (sizeof(KEKFL_STR) * FLARRY_MAX));
    for(ii = 0 ; ii < KekFL_cnt ; ii++) {
        if(KekFL[ii].sts < 4)    continue;
        if(KekFL[ii].sts == 8)  continue;

        memcpy(&KekFL_tmp[KekFLtmp_cnt], &KekFL[ii], sizeof(KEKFL_STR));
        KekFLtmp_cnt++;
    }

    memcpy(&KekFL[0], &KekFL_tmp[0], (sizeof(KEKFL_STR) * FLARRY_MAX));
    KekFL_cnt = KekFLtmp_cnt;

    return;
}

/**/
static void sFncMkReSknKekka()
/******************************************************************************
*  関 数 名　：sFncMkReSknKekka()                                             *
*  機能概要　：再々検依頼の結果要求(Line側からの)ファイル検出、               *
*              Line向け検査結果ファイル作成処理                               *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
* 　　　　　　　                                                              *
******************************************************************************/
{
    char    fbuf[101], iribuf[512], fpth[101], rnmfpth[101], buff[101];
    char    fnm[51], cmd[256], wk_rack[11];
    int     ii, len, c_st, c_en, c_dl;
    short   f_saisai;
    FILE    *fp, *irifp, *kekfp;
    struct stat  st;

    sprintf(cmd,"/usr/bin/ls %s/*dat > %s 2>&1", LANERSREQNEW_PATH, Temp_fpth);
    system(cmd);


    /* ファイルリストのオープン */
    if(NULL == (fp = fopen(Temp_fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "Line側結果要求ファイルリストのオープンに失敗しました。File[%s] ERR[%d]", Temp_fpth, errno);
        fprintf(Dbg_fp,"Line側結果要求ファイルリストのオープンに失敗しました。File[%s] ERR[%d]\n", Temp_fpth, errno);
        return;
    }

    for( ; ; ) {
        if(NULL == fgets(fbuf, 101, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '\0')
            continue;

        len = strlen(fbuf);
        if(fbuf[len-1] == '\n') {
            fbuf[len-1] = '\0';  len = strlen(fbuf);
        }
        if(NULL != strstr(fbuf,"/usr/bin/ls"))  break;
        if(stat(fbuf, &st) != 0)     continue;

        for(ii = (len-1) ; ii >= 0 ; ii--) {
            if(fbuf[ii] == '/') {
                sprintf(fnm,"%s", (fbuf+ii+1));  break;
            }
        }
        if(ii < 0)  continue;

        /* 該当ラックの依頼ファイル存在確認 */
        sprintf(wk_rack,"%.5s", fnm);
        for(ii = 1 ; ii <= 5 ; ii++) {
            sprintf(fnm,"%s%s_____%03d.dat", IRAI_PREFIX, wk_rack, ii);   /* 初検のファイル名でサーチ */
            sprintf(fpth,"%s/%s", IRAINEW_PATH, fnm);
            if(stat(fpth, &st) != 0)  continue;

            break;
        }
        if(ii > 5)  continue;


        /* 依頼ファイルのオープン */
        if(NULL == (irifp = fopen(fpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
            continue;
        }

        f_saisai = 0;
        for( ; ; ) {
            if(NULL == fgets(iribuf, 512, irifp))  break;
            if(iribuf[0] == '\n' || iribuf[0] == ' ' || iribuf[0] == '#')
                continue;
            if(strlen(iribuf) < 50)  continue;

            /* 各フィールドの処理 */
            c_st = c_en = c_dl = 0;
            for(ii = 0 ; ii < strlen(iribuf) ; ii++) {
                if(iribuf[ii] == ',')  {
                    if(c_en > 0)  c_st = c_en +1;
                    c_en = ii;  c_dl++;
                }
                else  continue;

                memcpy(buff, (iribuf+c_st), (c_en-c_st));  buff[(c_en-c_st)] = '\0';
                sFncTrim(buff);

                if(c_dl == 11) {                      /* 検査工程区分 */
                    if(buff[0] == 'K')  f_saisai = 1;
                    break;
                }
            }
            break;                                    /* 1レコードのみで判定 */
        }
        fclose(irifp);
        if(f_saisai == 0)  continue;                  /* 再々検、用手再検以外の場合は対象外 */


        /* 再々検、用手再検の結果要求ファイル検出 */
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "再々検、用手再検の結果要求ファイル検出 Rack[%s]", wk_rack);
        fprintf(Dbg_fp,"再々検、用手再検の結果要求ファイル検出 Rack[%s]\n", wk_rack);

        /* 以降は再々検、用手再検時のLine向け検査結果ファイル作成処理 */
        sprintf(fpth,"%s/%s.end", LANEIRAI_PATH, wk_rack);
        if(NULL == (irifp = fopen(fpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line用依頼ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line用依頼ファイルオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
            continue;
        }

        /* Line向け検査結果ファイルオープン */
        sprintf(fpth,"%s/%s_0.tmp", LANEKEKKA_PATH, wk_rack);
        if(NULL == (kekfp = fopen(fpth,"w"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line用検査結果ファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line用検査結果ファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
            fclose(irifp);
            continue;
        }

        for(ii = 0 ; ; ii++) {
            if(NULL == fgets(iribuf, 512, irifp))  break;
            if(iribuf[0] == '\n' || iribuf[0] == ' ' || iribuf[0] == '#')
                continue;
            len = strlen(iribuf);
            if(len < 10)  continue;

            /* ヘッダ情報のラインNo.チェック */
            if(ii == 0) {
                sprintf(buff,"%d", sAppEnv.lineno);
                if(isdigit(iribuf[len-3]) && iribuf[len-3] != buff[0]) {
                    fprintf(Dbg_fp,"Line用依頼ファイル内のLineNo.不一致 RackID[%s]\n", wk_rack);
                    break;                            /* 不一致の場合はbreak */
                }
                fprintf(kekfp,"%s", iribuf);          /* CR,LFコードも一緒に出力 */
                continue;
            }

            /* データ部出力 */
            iribuf[len-2] = '\0';
            fprintf(kekfp,"%s0%c%c", iribuf, 0x0d, 0x0a);
        }
        fclose(irifp);
        fclose(kekfp);
        if(ii == 0)  { unlink(fpth);  continue; }

        /* Line用検査結果ファイル名のリネーム (.tmp -> .dat) */
        sprintf(rnmfpth,"%s/%s_0.dat", LANEKEKKA_PATH, wk_rack);
        rename(fpth, rnmfpth);

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "Line用検査結果ファイル(再々検、用手再検時)の出力 FNM[%s_0.dat]", wk_rack);
        fprintf(Dbg_fp,"Line用検査結果ファイル(再々検、用手再検時)の出力 FNM[%s_0.dat]\n", wk_rack);


        /* Line側結果要求ファイルのリネーム */
        sprintf(rnmfpth,"%s/%s.end", LANERSREQEND_PATH, wk_rack);
        rename(fbuf, rnmfpth);
    }
    fclose(fp);

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return;
}

/**/
static void sFncTrim(char *s)
/******************************************************************************/
/*  関 数 名　：sFncTrim()                                                    */
/*  機能概要　：文字列前後のスペースを削除する                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *      編集文字列                                        */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/******************************************************************************/
{
    int     i ;

    i = strlen ( s ) ;

    while ( --i >= 0 && isspace ( (unsigned char)s[i] ) ) ;
    s[i+1] = '\0';
    for (i = 0; isspace((unsigned char)s[i]); i++) ;
    if ( i != 0 ) {
        strcpy ( s, s + i ) ;
    }

    return;
}

/**/
static int sFncShmCrt(struct appEnv *pAppEnv)
/******************************************************************************/
/*  関 数 名　：sFncShmCrt()                                                  */
/*  機能概要　：共有メモリ生成                                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *     プログラム環境構造体                      */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK     : 成功                                            */
/* 　　　　　　　RTN_NG     : 失敗                                            */
/******************************************************************************/
{
    int     *shmData ;

    //  取得
    pAppEnv->shm_Id = shmget(pAppEnv->shm_Key, sizeof(int), (0666 | IPC_CREAT));
    if ( pAppEnv->shm_Id < 0 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリの操作に失敗しました[shmget]" ) ;
        fprintf(Dbg_fp,"共有メモリの操作に失敗しました[shmget]\n");
        return ( RTN_NG ) ;
    }

    //  アタッチ
    shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのアタッチに失敗しました" ) ;
        fprintf(Dbg_fp,"共有メモリのアタッチに失敗しました\n");
        return ( RTN_NG ) ;
    }

    //  値設定
    *shmData = 0 ;

    //  デタッチ
    if ( shmdt ( shmData ) == -1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのデタッチに失敗しました" ) ;
        fprintf(Dbg_fp,"共有メモリのデタッチに失敗しました\n");
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static int sFncShmGet(struct appEnv *pAppEnv, int *pshmData)
/*****************************************************************************
*  関 数 名　：sFncShmGet()                                                  *
*  機能概要　：共有メモリ取得                                                *
*  入　　力　：                                                              *
*　 第１引数 ：                                                              *
*  復帰情報　： RTN_OK     : 成功                                            *
* 　　　　　　　RTN_NG     : 失敗                                            *
******************************************************************************/
{
    int     *shmData ;

    pAppEnv->shm_Id = shmget(pAppEnv->shm_Key, sizeof(int), 0666);
    if(pAppEnv->shm_Id == -1) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "shmget", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリの取得に失敗しました ERR[%d]", errno);
        fprintf(Dbg_fp,"共有メモリの取得に失敗しました ERR[%d]\n", errno);
        return(RTN_NG);
    }

    //  アタッチ
    shmData = ( int * )shmat(pAppEnv->shm_Id, 0 , 0);
    if ( shmData == ( int * )-1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリの操作に失敗しました ERR[%d]", errno ) ;
        fprintf(Dbg_fp,"共有メモリの操作に失敗しました ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  値設定
    *pshmData = *shmData ;

/*************
    fprintf(Dbg_fp,"共有メモリ[GET] shmKey[%d] ID[%d] Data[%d] Add[%x]\n",
            pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData);
*************/

    //  デタッチ
    if ( shmdt ( shmData ) == -1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのデタッチに失敗しました ERR[%d]", errno ) ;
        fprintf(Dbg_fp,"共有メモリのデタッチに失敗しました ERR[%d]", errno);
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static int sFncShmDel(struct appEnv *pAppEnv)
/******************************************************************************/
/*  関 数 名　：sFncShmDel()                                                  */
/*  機能概要　：共有メモリ削除                                                */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct appEnv *     プログラム環境構造体。                    */
/*  出　　力　：                                                              */
/*  復帰情報　： RTN_OK     : 成功                                            */
/* 　　　　　　　RTN_NG     : 失敗                                            */
/******************************************************************************/
{
    int     *shmData ;

    fprintf(Dbg_fp,"共有メモリ[DEL] shmKey[%d]-ID[%d]\n", pAppEnv->shm_Key, pAppEnv->shm_Id);

    //  削除
    if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static void sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName,
            int plLineNo, char *pcExeFlg, char *pcErrCode, char *pcfmt, ... )
/******************************************************************************/
/*  関 数 名　：sFncPutLog()                                                  */
/*  機能概要　：アプリケーションログ出力                                      */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *      編集文字列                                        */
/*  出　　力　：                                                              */
/*  復帰情報　：無し                                                          */
/******************************************************************************/
{
    va_list  ap ;
    char     cMsg[1024] ;

    /***
     ***    ログ初期値設定
     ***/
    gstLogMem.eTrcKind = peTrcKind ;
    //strcpy ( gstLogMem.pcSrcName, pcSrcName ) ;
    strcpy ( gstLogMem.pcFncName, pcFncName ) ;
    //gstLogMem.lLineNo = plLineNo ;
    strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
    strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
    va_start ( ap, pcfmt ) ;
    vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
    va_end ( ap ) ;

    /***
     ***    ログ出力
     ***/
    _ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;

    return ;
}

/**/
/******************************************************************************/
/*  関 数 名  ：KeisanChk()                                                   */
/*  機能概要  ：計算チェック(WS内)                                            */
/*  入    力  ：                                                              */
/*   第１引数 ：chkPara :   チェック用パラメータ                              */
/*   第２引数 ：pKekka  :   結果情報構造体配列                                */
/*   第３引数 ：KekkaCnt:   結果情報構造体数                                  */
/*   第３引数 ：lCnt    :   処理中位置                                        */
/*   第３引数 ：ODFld   :   オーダー情報                                      */
/*  出    力  ：                                                              */
/*  復帰情報  ：int                                                           */
/*                  0:再検無し                                                */
/*                  1:再検あり                                                */
/******************************************************************************/
int KeisanChk(char *chkPara, KEKFL_STR *pKekka, int lCnt, char **ODFld, STKEISANCHK *calbuf)
{
    int         ret = 0;
    int         ret2;
    char        calBuff[256];
    char        buff[51];
    struct stKEISANCHK {
        char    KMKCD[7+1];    // 項目コード
        char    KSNSK[128];    // 計算式
    } sKEISANCHK;
    int         iCnt;   // ループカウンタ
    int         paraCnt;
    int         i;
    int         setCnt;
    int         tmpCnt;
    char        tmp[32];
    double      calNum;
    char        *pBuffOD;
    char        **pFldOD;
    char        *pBuffRealchk ;
    char        **pFldRealchk;
    int         li_Keta ;
    char        lc_RawBuf[256] ;
    char        *lcp_RawBuf ;
    MY_FLG       myFlg_RawNone ;

    char *pszExpandKSNSK = (char *) NULL;
                                        /* IF 文展開後の計算式              */
    double dTransferLimit = (double) 0.0;

    pFldOD = malloc(sizeof(char *)*200);
    pBuffOD = malloc(sizeof(char) * 512);

fprintf(Dbg_fp,"chkPara[%s]\n",chkPara);
    paraCnt = 0;
    while (paraCnt < strlen(chkPara)) {
        memset(&sKEISANCHK, 0, sizeof(sKEISANCHK));
        memcpy(sKEISANCHK.KMKCD, &chkPara[paraCnt], 7);
     /* paraCnt += 7; */
        for (i = paraCnt + 1; i < strlen(chkPara) ; i++ ) if (chkPara[i] == '!') break;
     /* memcpy(sKEISANCHK.KSNSK, &chkPara[paraCnt+1], i-paraCnt-1); */
        memcpy(sKEISANCHK.KSNSK, chkPara, i);
        paraCnt += (i-paraCnt+1);
fprintf(Dbg_fp,"sKEISANCHK.KMKCD[%s]\n",sKEISANCHK.KMKCD);
fprintf(Dbg_fp,"sKEISANCHK.KSNSK[%s]\n",sKEISANCHK.KSNSK);
/*********
        ret2 = chkInfoRead(1, sKEISANCHK.KMKCD, pKekka->irfnm, pFldOD, pBuffOD);
        if ( ret2 != 0 ) {
            // オーダーに計算項目無し
            continue;
        }
*********/

        //--------------------------------------------------------
        // 結果値の値文字列を数値化する
        //  結果値がブランクの場合、計算は行わず、計算項目には
        //  ブランクを設定する
        //--------------------------------------------------------
        memset(tmp, 0, sizeof(tmp));
        strncpy(tmp, pKekka->kekka, 12);

        myFlg_RawNone = MY_FLG_OFF ;

        // 式中の項目コードを数値に置き換える。
        memset(calBuff, 0, sizeof(calBuff));
        for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
            // 項目コードの始まり'['を検索する。
            if (sKEISANCHK.KSNSK[iCnt] == '[') {
                // 項目値を検索
                memset(tmp, 0, sizeof(tmp));
                tmpCnt = 0;
                iCnt++;
                // 項目コードを転送（終了位置の]かNullまで）
                while (sKEISANCHK.KSNSK[iCnt] != ']' && sKEISANCHK.KSNSK[iCnt] != '\0') {
                    tmp[tmpCnt++] = sKEISANCHK.KSNSK[iCnt++];
                }
                // 結果情報から指定の項目コードを検索し、置き換える。
fprintf(Dbg_fp,"計算KM[%s]\n",tmp);
                for (tmpCnt = 0; tmpCnt < FLrec_cnt; tmpCnt++) {
                    if(strcmp(FLrec[tmpCnt].rackid, pKekka->rackid) != 0)  continue;
                    if(FLrec[tmpCnt].pos != pKekka->pos)                   continue;

                    sprintf(buff,"%07d", FLrec[tmpCnt].kmcode);
                    if (strncmp(buff, tmp, strlen(tmp)) == 0) {
                        strcpy ( lc_RawBuf, FLrec[tmpCnt].kekka ) ;
                        lcp_RawBuf = strtok ( lc_RawBuf, " " ) ;
                        if ( lcp_RawBuf == NULL || lcp_RawBuf[0] == '/' ||
                             lcp_RawBuf[0] == '\0' || lcp_RawBuf[0] == '?' ) {
                            //  値がブランク場合
                            myFlg_RawNone = MY_FLG_ON ;
                        }
                        else {
                            //  値が設定されている場合
                            strncat(calBuff, FLrec[tmpCnt].kekka, 12);
                            setCnt = strlen(calBuff);

                        }
                        break;
                    }
                }
                if (tmpCnt == FLrec_cnt) {
                    // 関連項目が見つからない。
                    break;
                }
            }
            else if (KSNSK_SC == (int) sKEISANCHK.KSNSK[iCnt]) {
                // 身長
                memcpy(gszTransfer, ODFld[FLDIDX_SC], FLDSIZE_SC);
                gszTransfer[FLDSIZE_SC] = (char) '\0';
                if (0 == _isnumeric(gszTransfer)) {
                    gszTransfer[0] = (char) '0';
                    gszTransfer[1] = (char) '\0';
                }
                strcat(calBuff, gszTransfer);
                setCnt = strlen(calBuff);
            }
            else if (KSNSK_TJ == (int) sKEISANCHK.KSNSK[iCnt]) {
                // POWと区別するため、前の文字がOで無いかチェックする。
                if (0 < iCnt &&
                    (sKEISANCHK.KSNSK[iCnt - 1] == 'o' ||
                     sKEISANCHK.KSNSK[iCnt - 1] == 'O')) {
                    break;
                }
                else {
                    // 体重
                    strncpy(gszTransfer, ODFld[FLDIDX_TJ], FLDSIZE_TJ);
                    gszTransfer[FLDSIZE_TJ] = (char) '\0';
                    if (0 == _isnumeric(gszTransfer)) {
                        gszTransfer[0] = (char) '0';
                        gszTransfer[1] = (char) '\0';
                    }
                    else {
                        switch ((int) ODFld[FLDIDX_TJTNI][0]) {
                        case _VALUE_TJTNI_KILLOGRAM:
                            dTransferLimit =
                                    atof(gszTransfer) * (double) 1000.0;
                            if ((double) 0.0 < dTransferLimit) {
                                sprintf(gszTransfer, "%f", dTransferLimit);
                            }
                            else {
                                gszTransfer[0] = (char) '0';
                                gszTransfer[1] = (char) '\0';
                            }

                        case _VALUE_TJTNI_GRAM:
                            break;      /* NOP                              */

                        default:
                            gszTransfer[0] = (char) '0';
                            gszTransfer[1] = (char) '\0';
                        }
                    }
                    strcat(calBuff, gszTransfer);
                    setCnt = strlen(calBuff);
                }
            }
            else if (KSNSK_TNTME == (int) sKEISANCHK.KSNSK[iCnt]) {
                // 蓄尿時間
                memcpy(gszTransfer, ODFld[FLDIDX_TNTME], FLDSIZE_TNTME);
                gszTransfer[FLDSIZE_TNTME] = (char) '\0';
                if (0 == _isnumeric(gszTransfer)) {
                    gszTransfer[0] = (char) '0';
                    gszTransfer[1] = (char) '\0';
                }
                else {
                    switch ((int) ODFld[FLDIDX_TNTNI][0]) {
                    case _VALUE_TNTNI_HOUR:
                        break;          /* NOP                             */

                    default:
                        gszTransfer[0] = (char) '0';
                        gszTransfer[1] = (char) '\0';
                    }
                }
                strcat(calBuff, gszTransfer);
                setCnt = strlen(calBuff);
            }
            else if (KSNSK_TNRYO == (int) sKEISANCHK.KSNSK[iCnt]) {
                // 蓄尿量
                // 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする
                memcpy(gszTransfer, ODFld[FLDIDX_TNRYO], FLDSIZE_TNRYO);
                gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
                if (0 == _isnumeric(gszTransfer)) {
                    gszTransfer[0] = (char) '0';
                    gszTransfer[1] = (char) '\0';
                }
                else {
                    switch ((int) ODFld[FLDIDX_TNRYOTNI][0]) {
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
            else if (KSNSK_SBTKBN == (int) sKEISANCHK.KSNSK[iCnt]) {
                /* 性別区分                                                 */
                if (_VALUE_SBTKBN_MALE == (int) ODFld[FLDIDX_SBTKBN][0] ||
                        _VALUE_SBTKBN_FEMALE == (int) ODFld[FLDIDX_SBTKBN][0]) {
                    calBuff[setCnt++] = ODFld[FLDIDX_SBTKBN][0];
                    calBuff[setCnt] = (char) '\0';
                }
                else {
                    calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
                    calBuff[setCnt] = (char) '\0';
                                        /* 展開不可                         */
                }
            }
            else if (KSNSK_AGE == (int) sKEISANCHK.KSNSK[iCnt]) {
                /* 年齢                                                     */
                if (_VALUE_AGEKBN_YEAR != (int) ODFld[FLDIDX_AGEKBN][0]) {
                    calBuff[setCnt++] = (char) '0';
                    calBuff[setCnt] = (char) '\0';
                                        /* 展開不可                         */
                }
                else {
                    memcpy(gszTransfer, ODFld[FLDIDX_AGE], FLDSIZE_AGE);
                    gszTransfer[FLDSIZE_AGE] = (char) '\0';
                    if (0 == _isnumeric(gszTransfer)) {
                        gszTransfer[0] = (char) '0';
                        gszTransfer[1] = (char) '\0';
                    }
                    strcat(calBuff, gszTransfer);
                    setCnt = strlen(calBuff);
                }
            }
            else if (sKEISANCHK.KSNSK[iCnt] == '\0') {
                break;
            }
            else {
                calBuff[setCnt++] = sKEISANCHK.KSNSK[iCnt];
            }
        }

        //--------------------------------------------------------
        // 計算項目を配列に退避する
        //  計算元の項目のいずれかがブランクの場合は
        //  結果値フラグを設定し、上位で結果値にブランクを設定する
        //--------------------------------------------------------
        if (iCnt == 128 || iCnt == strlen ( sKEISANCHK.KSNSK ) ) {
            //  桁数取得
            li_Keta = 8;

            //  項目コード設定
            sprintf(buff,"%07d", pKekka->kmcode);
            memcpy(calbuf[ret].motoKMKCD, buff, 8);
            memcpy(calbuf[ret].KMKCD, sKEISANCHK.KMKCD, 8);

            /* 計算式に含まれる IF 文の展開                                     */
            if (NULL != (pszExpandKSNSK = OperateKSNSK(calBuff))) {
                if ('\0' != (int) *pszExpandKSNSK) {
                    strcpy(calBuff, pszExpandKSNSK);
                }
                free(pszExpandKSNSK);
                pszExpandKSNSK = (char *) NULL;
            }

            // 文字列の計算式を計算する。
            calNum = StringCal(calBuff);
fprintf(Dbg_fp,"[%s]--[%d]...calBuff[%s] NUM[%f]\n",__FILE__,__LINE__,calBuff, calNum);
            if (li_Keta != 9) {
                sprintf(tmp, "%f", calNum);
                calNum = atof(tmp);
            }
            calbuf[ret].raw = calNum;
            calbuf[ret].flgRawNone = myFlg_RawNone ;
            ret ++;
        }
    }

    free(pFldOD);
    free(pBuffOD);

    return ret;
}

/**/
/******************************************************************************/
/*  関 数 名  ：StringCal_sub()                                               */
/*  機能概要  ：指定された演算子と値で四則演算行う                            */
/*  入    力  ：                                                              */
/*   第１引数 ：enzan   :   演算子                                            */
/*   第２引数 ：val1    :   値１                                              */
/*   第３引数 ：val2    :   値２                                              */
/*  出    力  ：                                                              */
/*  復帰情報  ：double  計算結果                                              */
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

/**/
/********************************************************************************/
/*  関 数 名  ：StringCal()                                                     */
/*  機能概要  ：渡された文字列の計算式を行う                                    */
/*  入    力  ：                                                                */
/*   第１引数 ：CalStr  :   計算文字列                                          */
/*  出    力  ：                                                                */
/*  復帰情報  ：double  計算結果                                                */
/*                                                                              */
/*  注意：  対応する演算子は「+ - / *」が可能である。                           */
/*          それ以外にLOG、LOG10、POWの3つの計算を行う。                        */
/*          計算の優先順位は、四則演算の優先順位に従い*と/が優先される。        */
/********************************************************************************/
double StringCal(char *CalStr)
{
    char        StacEn;
    double      StacNum;
    int         flg;
    int         loopCnt, strCnt;
    double      ret, ret1;
    char        cStacNum[32];
    char        cStacNum2[32];
    char        cChk[16];
    int         i, c;
    double      StacRet[10];
    char        StacEnc[10];
    char        StacFlg[10];
    int         StacCnt;

    ret = 0.0;
    StacEn = '+';
    flg = FALSE;
    strCnt = 0;
    StacCnt = 0;
    for(loopCnt = 0; loopCnt < strlen(CalStr); loopCnt ++) {
        switch (CalStr[loopCnt]) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
            // 数値の時
            break;

        case '+': case '-': case '/': case '*':
            // 演算子の時
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
/********
                StacRet[StacCnt] = StacNum;
                StacEnc[StacCnt] = CalStr[loopCnt];
********/
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

//          ret = StringCal_sub(StacEn, ret, StacNum);
//          flg = FALSE;
//          StacEn = CalStr[loopCnt];
            strCnt = loopCnt + 1;
            break;

        case 'L': case 'l':
            // LOG及びLOG10の時
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
            // POWの時
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

fprintf(Dbg_fp,"[%s]--[%d]...EN[%c] V1[%f] V2[%f]\n",__FILE__,__LINE__,StacEn,ret,StacNum);

            StacNum = StringCal_sub(StacEn, ret, StacNum);

/**********
            ret1 = StringCal_sub(StacEn, ret, StacNum);
            if(ret == (double)atof("0.000000") || StacNum == (double)atof("0.000000"))
                StacNum = ret1;
**********/

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

/*********
    for(i = (StacCnt-1) ; i >= 0 ; i--) {
        if(StacRet[i] == (double)atof("0.000000"))  continue;

        ret = StacRet[i];  StacEn = StacEnc[i];  break;
    }
*********/

fprintf(Dbg_fp,"[%s]--[%d]...EN[%c] V1[%f] V2[%f]\n",__FILE__,__LINE__,StacEn,ret,StacNum);
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
/******************************************************************************/
/*  関 数 名  ：chkInfoRead()                                                 */
/*  機能概要  ：ファイル情報読み出し                                          */
/*  入    力  ：                                                              */
/*   第１引数 ：モード  : 0:即時チェックファイル/ 1:オーダーファイル          */
/*   第２引数 ：kmkcd   :   項目コード                                        */
/*   第３引数 ：fName   :   ファイル名                                        */
/*  出    力  ：Data    :   情報（指定項目コード）                            */
/*            ：buff    :   出力用バッファ                                    */
/*  復帰情報  ：int                                                           */
/*                  0:正常                                                    */
/*                  1:異常(項目コード無し)                                    */
/*                  2:異常（その他）                                          */
/******************************************************************************/
static int chkInfoRead(int mode, char *kmkcd,char *fName, char **Data, char *buff)
{
    FILE * fp;

    char        ** pFld;
    int         cnt;
    int         offset;
    int         ret = 1;
    int         hitFlg = 0;
    char        fPath[101];

    sprintf(fPath,"%s/%s", IRAINEW_PATH, fName);

    fp = fopen(fPath, "r");
    if (fp == NULL) {
        return 2;
    }

    pFld = malloc(sizeof(char *)*200);
    while (fgets(buff, 512, fp)) {
        // カンマ区切りのレコードを分割し、
        hitFlg = 0;
        cnt = 0;
        offset = 0;;
        pFld[cnt] = &buff[cnt];
        cnt++;
        while (buff[offset] != '\0') {
            if (buff[offset] == ',') {
                pFld[cnt] = &buff[offset+1];
                buff[offset] = '\0';
                if (cnt == 5) {
                    if (strncmp(kmkcd, pFld[5], 7) == 0) {
                        hitFlg = 1;
                    }
                    else {
                        break;
                    }
                }
                cnt++;
            }
            offset++;
        }
        if (hitFlg == 0) {
            continue;
        }
        if (mode == 0) {
            if (cnt != 59) {
                // CSVフィールド数不正（読み飛ばす）
                continue;
            }
            if (strncmp(kmkcd, pFld[5], 7) == 0) {
                // 指定項目コードを見つけた
                memcpy(Data, pFld, sizeof(char *) * 118);
                ret = 0;
                break;
            }
        }
        else {
            if (cnt != 58) {
                // CSVフィールド数不正（読み飛ばす）
                continue;
            }
fprintf(Dbg_fp,"del cnt[%d] ret[%d]\n",cnt,ret);
            if (strncmp(kmkcd, pFld[5], 7) == 0) {
fprintf(Dbg_fp,"[%s]--[%d]...\n",__FILE__,__LINE__);
                // 指定項目コードを見つけた
                memcpy(Data, pFld, sizeof(char *) * 118);
                ret = 0;
fprintf(Dbg_fp,"del cnt[%d] ret[%d]\n",cnt,ret);
                break;
            }
        }
    }

    free(pFld);
    fclose(fp);

    return (ret);
}

/**/
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
static char *OperateKSNSK(char *pszKSNSK)
{
    static char szBlank[] = " ";
    static char szNE[] = STR_NE;

    char *pszFormular;                  /* 戻り値 (処理対象の計算式)        */
    char *pszReplace;                   /* IF ブロック展開結果              */
    char *pszIFBlock = (char *) NULL;   /* IF ブロック文字列                */
    struct _IFBLOCK *pstItems = (struct _IFBLOCK *) NULL;
                                        /* IF ブロックを項目要素毎に分解    */
    double dblLeft;                     /* 条件式左辺値                     */
    double dblRight;                    /* 条件式右辺値                     */
    BOOL nCompared = FALSE;             /* 条件式判定結果                   */
    BOOL nErrorOccured = FALSE;         /* エラー発生フラグ                 */
    static char szConvert[32];

    if (NULL != (pszFormular = _touppercase(_replace(pszKSNSK, szBlank, NULL)))) {

fprintf(Dbg_fp,"KSNSK: [%s]\n", pszFormular);

        if (!nErrorOccured && NULL != pszFormular) {
            if (!IsFormula(pszFormular)) {
                fprintf(Dbg_fp,"Invalid formular - \"%s\"\n", pszFormular);
                nErrorOccured = TRUE;   /* 計算式として異常                 */
                free(pszFormular);
                pszFormular = (char *) NULL;
            }
        }

        while (!nErrorOccured &&
               NULL !=  (pszIFBlock = GetIFBlock(pszFormular))) {

            if (NULL == (pstItems = SplitIFBlockItems(pszIFBlock))) {
                fprintf(Dbg_fp,"Invalid IF block items - \"%s\"\n", pszFormular);
                nErrorOccured = TRUE;   /* IF ブロック内の要素分解失敗      */
                free(pszFormular);
                pszFormular = (char *) NULL;
            }
            else if (NULL == pstItems->pszConditionLeft ||
                     NULL == pstItems->pszOperator ||
                     NULL == pstItems->pszConditionRight ||
                     NULL == pstItems->pszValueTrue ||
                     NULL == pstItems->pszValueFalse) {
                fprintf(Dbg_fp,"Analize error - \"%s\"\n", pszFormular);
                nErrorOccured = TRUE;   /* IF ブロック内の要素分解失敗      */
                free(pszFormular);
                pszFormular = (char *) NULL;
            }
            else {
                /* 分解した内容を元に IF ブロック内判定
                    (ここが IF ブロックの展開エンジン)                      */
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
                    fprintf(Dbg_fp,"Invalid operator in KSNSK.\n");
                    nErrorOccured = TRUE;
                    free(pszFormular);
                    pszFormular = (char *) NULL;
                    break;
                }
            }

            if (!nErrorOccured) {
                if (nCompared) {
                    pszReplace = _replace(pszFormular,
                                          pszIFBlock,
                                          pstItems->pszValueTrue);
                }
                else {
                    pszReplace = _replace(pszFormular,
                                          pszIFBlock,
                                          pstItems->pszValueFalse);
                }

                if (NULL == pszReplace) {
                    nErrorOccured = TRUE;
                                         /* IF ブロック → 適用値変換失敗    */
                    free(pszFormular);
                    pszFormular = (char *) NULL;
                }
                else {
                    free(pszFormular);
                    pszFormular = pszReplace;
                }
            }
            if (NULL != pszIFBlock) {
                free(pszIFBlock);
            }
            freeIFBLOCK(pstItems);
        }
    }

if (NULL != pszFormular) fprintf(Dbg_fp,"\tExpand:\t%s\n", pszFormular);

   return (pszFormular);
}

/**/
/*--------------------------------------------------------------------------*
 * _touppercase
 *
 * 文字列中の半角英小文字を半角英大文字に変換した文字列の生成
 *
 * Parameter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、変換元の文字列です。
 *
 * Return value:
 *  関数が正常終了した場合、変換後の文字列を格納している領域の先頭ポインタを
 *  返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で free() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
static char *_touppercase(char *pszOrigin)
{
    char *pszResult = (char *) NULL;    /* 戻り値                           */
    size_t ulIndex;                     /* 文字位置                         */

    if (NULL != pszOrigin) {
        if (NULL != (pszResult = strdup(pszOrigin))) {
            for (ulIndex = (size_t) 0;
                 _EOS != (int) *(pszResult + ulIndex);
                 ulIndex++) {
                if (islower((int) *(pszResult + ulIndex))) {
                    *(pszResult + ulIndex) &= (char) _MASK_TOUPPER;
                }
            }
        }
    }
    return (pszResult);
}

/*--------------------------------------------------------------------------*
 * _replace
 *
 * 文字列の置換
 *
 * Parameter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、置換対象となる文字列です。
 *  pszTarget           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、置換によって置き換えられる文
 *                      字列です。
 *  pszReplace          NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      NULL が指定された場合、空文字列が指定されたものとし
 *                      て扱います。
 *                      ここで指定する文字列は、置換によって置き換える文字
 *                      列です。
 *
 * Return value:
 *  関数が正常終了した場合、置換後の文字列を格納している領域の先頭ポインタを
 *  返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で free() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
static char *_replace(char *pszOrigin, char *pszTarget, char *pszReplace)
{
    char *pszResult = (char *) NULL;    /* 戻り値                           */
    char *pszFind;                      /* 置換対象検索                     */
    int nFindCount;                     /* 置換対象件数                     */
    size_t ulOrigin;                    /* 元の文字列のバイト サイズ        */
    size_t ulTarget;                    /* 元の文字列のバイト サイズ        */
    size_t ulSource;                    /* 置換対象のバイト サイズ          */
    size_t ulReplace;                   /* 置き換える文字列のバイト サイズ  */
    size_t ulDestination;               /* 置換後文字位置                   */

    if (NULL != pszOrigin && NULL != pszTarget) {
        if ((size_t) 0 < (ulTarget = strlen(pszTarget))) {
            if ((size_t) 1 > (ulOrigin = strlen(pszOrigin))) {
                pszResult = strdup(pszOrigin);
                                        /* 置換対象なし                     */
            }
            else {
                for (nFindCount = 0, pszFind = (char *) pszOrigin;
                     NULL != (pszFind = strstr(pszFind, pszTarget));
                     nFindCount++, pszFind++);
                if (0 == nFindCount) {
                    pszResult = strdup(pszOrigin);
                                        /* 置換対象なし                     */
                }
                else {
                    ulReplace = (NULL == pszReplace) ?
                                (size_t) 0 : strlen(pszReplace);
                    if (NULL != (pszResult =
                                          (char *) malloc(ulOrigin + 
                                                          ((size_t) nFindCount * (ulReplace - ulTarget)) + 
                                                          (size_t) 1))) {
                        ulDestination = (size_t) 0;
                        ulSource = (size_t) 0;
                        while (_EOS != (int) *(pszOrigin + ulSource) && 
                               ulOrigin > ulSource) {
                            if (strncmp(pszOrigin + ulSource,
                                        pszTarget,
                                        ulTarget)) {
                                *(pszResult + ulDestination) = 
                                    *(pszOrigin + ulSource);
                                ulDestination++;
                                ulSource++;
                            }
                            else {
                                if (ulReplace) {
                                    memcpy((pszResult + ulDestination),
                                           pszReplace,
                                           ulReplace);
                                    ulDestination += ulReplace;
                                }
                                ulSource += ulTarget;
                            }
                        }
                        *(pszResult + ulDestination) = (char) _EOS;
                    }
                }
            }
        }
    }
    return (pszResult);
}

/*--------------------------------------------------------------------------*
 * GetIFBlock
 *
 * 計算式に含まれる IF ブロック文字列を抽出します。
 *
 * Paramter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。

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
static char *GetIFBlock(char *pszOriginal)
{
    static char szIFBlock[] = STR_BEGIN_IFBLOCK;

    char *pszResult = NULL;             /* 戻り値                           */
    char *pszIFBlock;                   /* IF ブロック開始位置              */
    size_t ulOriginal;                  /* 元の文字列の長さ                 */
    char *pszFind;                      /* IF ブロック終端検索              */
    int nParenthesis = 0;               /* 括弧の階層震度                   */
    int nComma;                         /* カンマの数                       */
    BOOL nTarminate;                    /* IF ブロック終端検出              */

    if (NULL != pszOriginal) {
        if ((size_t) 0 <= (ulOriginal = strlen(pszOriginal))) {
            if (NULL != (pszIFBlock = _strrstr(pszOriginal, szIFBlock))) {
                for (pszFind = (pszIFBlock + strlen(szIFBlock)),
                         nTarminate = FALSE, nParenthesis = 0, nComma = 0;
                     !nTarminate; pszFind++) {

                    switch ((int) *pszFind) {
                    case PARENT_BEGIN:  /* カッコ (開始)                    */
                        nParenthesis++;
                        break;

                    case _EOS:
                    case PARENT_END:    /* カッコ (終了)                    */
                        nParenthesis--;
                        if (0 > nParenthesis) {
                            nTarminate = TRUE;
                            if (1 < nComma) {
                                pszResult = _strndup(pszIFBlock,
                                                     (size_t) (pszFind - pszIFBlock + 1));
                            }
                        }
                        break;

                    case SPLITTER_COMMA:
                                        /* 要素の区切りを示すカンマ         */
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

    struct _IFBLOCK *pstResult = (struct _IFBLOCK *) NULL;
                                        /* 戻り値                           */
    BOOL nErrorOccured = FALSE;         /* エラー検出フラグ                 */
    BOOL nTerminate = FALSE;            /* 分解終了フラグ                   */
    char *pszTarget;                    /* 判定文字                         */
    char *pszBegin;                     /* 分解対象の項目の先頭             */
    int nParenthesis;                   /* カッコの入れ子深度               */
    int nIndex;                         /* 分解項目の項目インデックス       */

    if (NULL == pszOrigin) {
        pstResult = (struct _IFBLOCK *) NULL;
    }
    else if (NULL != (pstResult = 
                               (struct _IFBLOCK *) malloc(sizeof(struct _IFBLOCK)))) {
        for (nIndex = 0; MAXCNT_ITEM_IFBLOCK >= nIndex; nIndex++) {
            *((void **) pstResult + nIndex) = NULL;
        }
        for (nErrorOccured = FALSE, nTerminate = FALSE, 
                 nIndex = 0, nParenthesis = 0,
                 pszBegin = pszTarget = (strchr(pszOrigin, '(') + 1);
             !nErrorOccured && !nTerminate && 
                 NULL != pszTarget && _EOS != (int) *pszTarget;
             pszTarget++) {

            switch ((int) *pszTarget) {
            case PARENT_BEGIN:          /* カッコ (開始)                    */
                nParenthesis++;
                break;

            case PARENT_END:            /* カッコ (終了)                    */
                nParenthesis--;
                if (0 > nParenthesis) {
                    if (NULL == pstResult->pszValueTrue ||
                        NULL == pstResult->pszConditionRight) {
                        nErrorOccured = TRUE;
                                        /* IF ブロックの終了を示す ')' を検
                                           出したが、必須項目が不足している */
                    }
                    else if (NULL == (pstResult->pszValueFalse = 
                                               _strndup(pszBegin, 
                                                        (size_t) (pszTarget - pszBegin)))) {
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
                    NULL != pstResult->pszConditionLeft) {
                    nErrorOccured = TRUE;
                }
                else if (NULL == (pstResult->pszConditionLeft = 
                                           _strndup(pszBegin,
                                                    (size_t) (pszTarget - pszBegin)))) {
                    nErrorOccured = TRUE;
                }
                else if (OPERATOR_LT == (int) *pszTarget &&
                         OPERATOR_GT == (int) *(pszTarget + 1)) {
                    if (NULL == (pstResult->pszOperator = strdup(szNE))) {
                        nErrorOccured = TRUE;
                    }
                    else {
                        pszTarget++;
                        pszBegin = pszTarget;
                        pszBegin++;
                    }
                }
                else if (NULL == (pstResult->pszOperator =
                                           _strndup(pszTarget, 1))) {
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
                else if (NULL == pstResult->pszConditionRight) {
                    /* 条件式右辺 - 条件式が真の場合に適用する値            */
                    if (NULL == (pstResult->pszConditionRight = 
                                          _strndup(pszBegin,
                                                   (size_t) (pszTarget - pszBegin)))) {
                        nErrorOccured = TRUE;
                    }
                    else {
                        pszBegin = pszTarget;
                        pszBegin++;
                    }
                }
                else if (NULL == pstResult->pszValueTrue) {
                    /* 条件式が真の場合に適用する値 - 
                       偽の場合に適用する値                                 */
                    if (NULL == (pstResult->pszValueTrue = 
                                          _strndup(pszBegin,
                                                   (size_t) (pszTarget - pszBegin)))) {
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
    if (nErrorOccured && NULL != pstResult) {
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
static void freeIFBLOCK(struct _IFBLOCK *pstTarget)
{
    int nIndex;                         /* 項目インデックス                 */

    if (NULL != pstTarget) {
        for (nIndex = 0; MAXCNT_ITEM_IFBLOCK > nIndex; nIndex++) {
            if (NULL != *((void **) pstTarget + nIndex)) {
                free(*((void **) pstTarget + nIndex));
            }
        }
        free(pstTarget);
    }
    return;
}

/*--------------------------------------------------------------------------*
 * _strrstr
 *
 * 文字列の検索 (末尾方向から)
 *
 * Parameter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、検索される文字列です。
 *  pszTarget           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、検索する文字列です。
 *
 * Return value:
 *  関数が正常終了した場合、検出した文字列を格納している領域の先頭ポインタを
 *  返します。
 *  エラーが発生した場合、指定した文字列が検出できなかった場合、 NULL を返し
 *  ます。
 *--------------------------------------------------------------------------*/
static char *_strrstr(char *pszOrigin, char *pszTarget)
{
    char *pszResult = (char *) NULL;
    char *pszFind;

    if (NULL != pszOrigin && NULL != pszTarget) {
        for (pszFind = pszOrigin;
             NULL != (pszFind = strstr(pszFind, pszTarget));
             pszFind++) {
            pszResult = pszFind;
        }
    }
    return (pszResult);
}

/*--------------------------------------------------------------------------*
 * _strndup
 *
 * 指定サイズ分のみ文字列を複製
 *
 * Parameter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、複製元となる文字列です。
 *  ulSize              複製する文字列のサイズを指定します。
 *                      このサイズに上記パラメータで指定した文字列の長さより
 *                      大きいサイズを指定した場合、単に文字列が複写されるだ
 *                      けです。
 *
 * Return value:
 *  関数が正常終了した場合、複製した文字列を格納している領域の先頭ポインタを
 *  返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で free() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
static char *_strndup(char *pszOrigin, size_t ulSize)
{
    char *pszResult = (char *) NULL;    /* 戻り値                           */
    size_t ulOrigin;                    /* 元の文字列のバイト サイズ        */
    size_t ulTruth;                     /* 抽出する文字列のバイト サイズ    */

    if (NULL != pszOrigin && (size_t) 0 < ulSize) {
        ulTruth = (ulSize < (ulOrigin = strlen(pszOrigin))) ? ulSize : ulOrigin;
        if (NULL != (pszResult =
                              (char *) malloc(ulTruth + (size_t) 1))) {
            memcpy(pszResult, pszOrigin, ulTruth);
            *(pszResult + ulTruth) = (char) _EOS;
        }
    }
    return (pszResult);
}

/*--------------------------------------------------------------------------*
 * _isnumeric
 *
 * 10 進法表記の数値文字列チェック
 *
 * Parameter(s):
 *  pszTarget           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、チェック対象の数値文字列で
 *                      す。
 *
 * Return value:
 *  指定した文字列が、 10 進法表記の数値文字列 (整数、小数、負の値を含む) の
 *  場合、 0 以外の値を返します。
 *  10 進法表記の数値文字列以外、またはエラーが発生した場合、値 0 を返しま
 *  す。
 *
 * Comment:
 *  10 進法表記の数値文字列
 *
 *          \s*(-\s*)?\d+(\.\d*)?\s*
 *
 *--------------------------------------------------------------------------*/
static int _isnumeric(char *pszTarget)
{
    int nResult = 0;
    int nIndex;

    if (NULL != (void *) pszTarget) {
        for (nIndex = 0; isspace(*(pszTarget + nIndex)); nIndex++);
                                        /* Trim start                       */
        if (_EOS != (int) *(pszTarget + nIndex)) {
            if ('-' == (int) *(pszTarget + nIndex)) {
                for (++nIndex; isspace(*(pszTarget + nIndex)); nIndex++);
            }
            for ( ; isdigit(*(pszTarget + nIndex)); nIndex++);
                                        /* Integer part                     */
            if ('.' == (int) *(pszTarget + nIndex)) {
                for (++nIndex; isspace(*(pszTarget + nIndex)); nIndex++);
                                        /* uner decimal point               */
            }
            for ( ; isspace(*(pszTarget + nIndex)); nIndex++);
                                        /* Trim end                         */
            if (_EOS == (int) *(pszTarget + nIndex)) {
                nResult = -1;
            }
        }
    }
    return (nResult);
}

/**/
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
static int IsFormula(char *pszKSNSK)
{
    BOOL bResult = FALSE;
    char *pszFormular;
    char *pszReplace;
    int nIndex;
    int nParenthesis = 0;               /* 括弧の階層震度                   */

    if (NULL != (pszFormular = 
                          _touppercase(_replace(pszKSNSK,
                                                " ",
                                                (char *) NULL)))) {

        /* 算術関去                                                   */
        if (NULL != (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_IFBLOCK,
                                                    (char *) NULL))) {
            free(pszFormular);
            pszFormular = pszReplace;

            if (NULL != (pszReplace = _replace(pszFormular,
													    ":",
                                                        (char *) NULL))) {
                free(pszFormular);
                pszFormular = pszReplace;
            }

            if (NULL != (pszReplace = _replace(pszFormular,
                                                        ",",
                                                        (char *) NULL))) {
                free(pszFormular);
                pszFormular = pszReplace;
            }

            /* 条件式中の比較演算子除去                                     */
            if (NULL != (pszReplace = _replace(pszFormular,
                                                        "<",
                                                        (char *) NULL))) {
                free(pszFormular);
                pszFormular = pszReplace;
            }
            if (NULL != (pszReplace = _replace(pszFormular,
                                                        ">",
                                                        (char *) NULL))) {
                free(pszFormular);
                pszFormular = pszReplace;
            }
            if (NULL != (pszReplace = _replace(pszFormular,
                                                        "=",
                                                        (char *) NULL))) {
                free(pszFormular);
                pszFormular = pszReplace;
            }
        }
        if (NULL != (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_LOG10,
                                                    (char *) NULL))) {
            free(pszFormular);
            pszFormular = pszReplace;
        }
        if (NULL != (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_LOG,
                                                    (char *) NULL))) {
            free(pszFormular);
            pszFormular = pszReplace;
        }
        if (NULL != (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_POW,
                                                    (char *) NULL))) {
            free(pszFormular);
            pszFormular = pszReplace;
            if (NULL != (pszReplace = _replace(pszFormular,
                                                        ",",
                                                        (char *) NULL))) {
                free(pszFormular);
                pszFormular = pszReplace;
            }
        }

        /* 数文字 (小数点を含む) 、演算記号判定                             */
        for (nIndex = 0, bResult = TRUE;
             bResult && '\0' != (int) *(pszFormular + nIndex);
             nIndex++) {
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
        free(pszFormular);

        /* 括弧対応チェック                                                 */
        if (bResult) {
            for (nParenthesis = 0, nIndex = 0;
                 bResult && '\0' != (int) *(pszKSNSK + nIndex);
                 nIndex++) {
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

