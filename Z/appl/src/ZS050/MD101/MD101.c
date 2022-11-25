
/* 改訂履歴
 2020.05.26 #01 小島  測定依頼送信の際に、依頼ファイルに誤って同じ項目コードが
                      複数設定されていた場合に、同じチャネルの測定依頼を複数
                      設定しないように修正

*/

/******************************************************************************
* インクルード宣言                                                            *
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/shm.h>
#include <time.h>
#include <signal.h>
#include <stdarg.h>
#include <bml_base.h>
#include <bmlprm.h>
#include <bmllog.h>
#include <MD101.h>

/******************************************************************************
* マクロ宣言                                                                  *
******************************************************************************/
#define  GOKI_MAX                 (3)                 /* 分析機接続MAX数 */
#define  SOCFRAME_MAXSIZE         (512)               /* 最大フレーム長 */
#define  SOCBUF_MAXSIZE           (2048)              /* SOC送受信バッファのMAXサイズ */
#define  MSTCHANL_MAX             (800)               /* チャネルマスタの配列MAX数 */
#define  RETRY_MAX1               (10)                /* ソケット接続エラー時のリトライ回数 */
#define  RETRY_MAX2               (2)                 /* ソケット再接続時のリトライ回数 */
#define  MYAPP_LOG_ERRCODE_NON    "00000000"
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */

/******************************************************************************
* グローバル宣言                                                              *
******************************************************************************/
static char    LmName[25];                            /* プログラム名 */
struct stcLogMember  gstLogMem;                       /* ログ出力情報 */
struct appEnv  sAppEnv;
SVRINF         Svrinf[GOKI_MAX];                      /* 分析機接続情報 */
CHLMST         MstChanl[MSTCHANL_MAX];                /* チャネルマスタ格納構造体 */
FILE           *SOCrcv_fp[GOKI_MAX];                  /* 受信データ退避用ファイルポインタ */
FILE           *SOCsnd_fp[GOKI_MAX];                  /* 送信データ退避用ファイルポインタ */
int            SOCrcv_fd[GOKI_MAX];                   /* 受信データ退避用ディスクリプタ */
int            SOCsnd_fd[GOKI_MAX];                   /* 送信データ退避用ディスクリプタ */
static char    FrmBuf[GOKI_MAX][SOCBUF_MAXSIZE];      /* 送信フレームバッファ */
static char    SndBuf[SOCBUF_MAXSIZE];                /* 送信データバッファ */
static char    RcvBuf[SOCFRAME_MAXSIZE +1];           /* 受信フレームバッファ */
static char    RBuf_rslt[GOKI_MAX][SOCBUF_MAXSIZE];   /* 分割測定結果蓄積用受信データバッファ */
static int     Frbuf_len[GOKI_MAX];                   /* 送信フレームのデータ長 */
static int     Svrinf_cnt;                            /* 有効な分析機接続情報の数 */
static int     MstChanl_cnt;                          /* チャネルマスタのデータ数 */
static int     DbgFlg;                                /* デバッグ出力スイッチ */

/******************************************************************************
* 関数宣言                                                                    *
******************************************************************************/
static int    initFunction(int, char **);
static int    mainFunction();
static void   endFunction();
static void   sFncPutLog(LOG_TRCKIND, char *, char *, int, char *, char *, char *, ...);
static int    sFncChMstLoad();
static int    sFncGetUdate();
static void   sFncGetMemSave();
static void   sFncPutMemSave();
static int    sFncConctSvr(short);
static int    sFncSocSend(SVRINF *, int);
static int    sFncIraiSend(SVRINF *, int);
static int    sFncSocRecv(SVRINF *, int);
static int    sFncRcvdatProc(SVRINF *, char *, int);
static int    sFncKekSave(SVRINF *, char *, char *, char *, char *, char *, char *, char *);
static void   sFncSocdatOut(char *, char *, int, short);
static void   sFncGetChecksum(char *, int, char *);
static int    sFncShmCrt(struct appEnv *);
static int    sFncShmGet(struct appEnv *, int *);
static int    sFncShmDel(struct appEnv *);
static void   sFncTrim(char *);


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
    char    buff[256], lc_prmBuf[256];
    char    fpth[101];
    int     ii, mecd, portno, i_tmp;
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
        if(DbgFlg)  printf("パラメータファイルのオープンに失敗しました[%s]\n", argv[1]);
        return(RTN_NG);
    }


    memset(&Svrinf[0],'\0', (sizeof(SVRINF)*GOKI_MAX));
    for(ii = 0 ; ii < GOKI_MAX ; ii++)
        Svrinf[ii].sfd = -1;
    Svrinf_cnt = 0;

    /* 処理対象のラインNo.取得 */
    if(ZbmlPrmGetVal(bp, "LINENO", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[LINENO]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[LINENO]\n");
        return(RTN_NG);
    }
    sAppEnv.lineno = atoi(lc_prmBuf);


    /* "GOKI_1"(分析機1) の情報取得 (見つからなくてもエラーにしない) */
    if(ZbmlPrmGetVal(bp, "GOKI_1", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[GOKI_1]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[GOKI_1]\n");
    }
    else {
        sscanf(lc_prmBuf,"%d %s %d", &mecd, buff, &portno);
        sprintf(Svrinf[Svrinf_cnt].svhost,"%s", buff);
        Svrinf[Svrinf_cnt].mecd = mecd;
        Svrinf[Svrinf_cnt].svport = portno;
        Svrinf_cnt++;
    }

    /* "GOKI_2"(分析機2) の情報取得 (見つからなくてもエラーにしない) */
    if(ZbmlPrmGetVal(bp, "GOKI_2", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[GOKI_2]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[GOKI_2]\n");
    }
    else {
        sscanf(lc_prmBuf,"%d %s %d", &mecd, buff, &portno);
        sprintf(Svrinf[Svrinf_cnt].svhost,"%s", buff);
        Svrinf[Svrinf_cnt].mecd = mecd;
        Svrinf[Svrinf_cnt].svport = portno;
        Svrinf_cnt++;
    }

    /* "GOKI_3"(分析機3) の情報取得 (見つからなくてもエラーにしない) */
    if(ZbmlPrmGetVal(bp, "GOKI_3", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[GOKI_3]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[GOKI_3]\n");
    }
    else {
        sscanf(lc_prmBuf,"%d %s %d", &mecd, buff, &portno);
        sprintf(Svrinf[Svrinf_cnt].svhost,"%s", buff);
        Svrinf[Svrinf_cnt].mecd = mecd;
        Svrinf[Svrinf_cnt].svport = portno;
        Svrinf_cnt++;
    }

    if(Svrinf_cnt > GOKI_MAX) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "分析機接続情報のMAX数を超えました。Svrinf_cnt[%d]", Svrinf_cnt);
        if(DbgFlg)  printf("分析機接続情報のMAX数を超えました。Svrinf_cnt[%d]", Svrinf_cnt);
        return(RTN_NG);
    }

    /* その他のパラメータ取得 */
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    if(ZbmlPrmGetVal(bp, "SHM_KEY", lc_prmBuf) != 0) {          /* 共有メモリキー */
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[SHM_KEY]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[SHM_KEY]\n");
        return(RTN_NG);
    }
    sAppEnv.shm_Key = atoi(lc_prmBuf);

    if(ZbmlPrmGetVal(bp, "TIMEOUT_SEC", lc_prmBuf) != 0) {      /* タイムアウト値(sec) */
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[TIMEOUT_SEC]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[TIMEOUT_SEC]\n");
        return(RTN_NG);
    }
    sAppEnv.timeout_Sec = atoi(lc_prmBuf);

    if(ZbmlPrmGetVal(bp, "TIMEOUT_USEC", lc_prmBuf) != 0) {     /* タイムアウト値(msec) */
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "パラメータが取得できませんでした[TIMEOUT_USEC]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[TIMEOUT_USEC]\n");
        return(RTN_NG);
    }
    sAppEnv.timeout_uSec = atoi(lc_prmBuf);

    /* 血清項目(乳び)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "NYUBI_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[NYUBI_KM]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[NYUBI_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.nyubi_km,"%s", buff);
    sAppEnv.nyubi_ch = i_tmp;
    if(DbgFlg)  printf("血清項目(乳び) KM[%s] CH[%d]\n", sAppEnv.nyubi_km, sAppEnv.nyubi_ch);

    /* 血清項目(溶血)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "YOUKETSU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[YOUKETSU_KM]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[YOUKETSU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.youkets_km,"%s", buff);
    sAppEnv.youkets_ch = i_tmp;
    if(DbgFlg)  printf("血清項目(溶血) KM[%s] CH[%d]\n", sAppEnv.youkets_km, sAppEnv.youkets_ch);

    /* 血清項目(黄疸)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "OUDAN_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[OUDAN_KM]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[OUDAN_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.oudan_km,"%s", buff);
    sAppEnv.oudan_ch = i_tmp;
    if(DbgFlg)  printf("血清項目(黄疸) KM[%s] CH[%d]\n", sAppEnv.oudan_km, sAppEnv.oudan_ch);

    /* 血清項目(生食)の項目コードとチャネルNo. */
    if(ZbmlPrmGetVal(bp, "SEISYOKU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[SEISYOKU_KM]");
        if(DbgFlg)  printf("パラメータが取得できませんでした[SEISYOKU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.seisyk_km,"%s", buff);
    sAppEnv.seisyk_ch = i_tmp;
    if(DbgFlg)  printf("血清項目(生食) KM[%s] CH[%d]\n", sAppEnv.seisyk_km, sAppEnv.seisyk_ch);


    /* パラメータファイルクローズ */
    ZbmlPrmClose(bp);


    /* 共有メモリの取得 */
    if(sFncShmCrt(&sAppEnv) != RTN_OK)  return(RTN_NG);


    /* チャネルマスタのメモリロード */
    if(sFncChMstLoad() != RTN_OK)  return(RTN_NG);

    /* 処理日取得 */
    if(sFncGetUdate() != RTN_OK)  return(RTN_NG);
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "処理日 [%s]", sAppEnv.udate);
    if(DbgFlg)  printf("処理日 [%s]\n", sAppEnv.udate);


    /* ソケットデータ退避ファイルオープン */
    for(ii = 0 ; ii < GOKI_MAX ; ii++) {              /* fd、ポインタの初期化 */
        SOCrcv_fd[ii] = -1;    SOCsnd_fd[ii] = -1;
        SOCrcv_fp[ii] = NULL;  SOCsnd_fp[ii] = NULL;
    }

    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {

        /* 受信Rawファイルのオープン */
        sprintf(fpth,"%s/ZS050_%02dRCV.raw", RCSDDATA_PATH, Svrinf[ii].mecd);
        SOCrcv_fd[ii] = open(fpth, (O_WRONLY|O_CREAT|O_APPEND), (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
        if(SOCrcv_fd[ii] == -1) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]\n", fpth, errno);
        }

        /* 受信データファイルのオープン */
        sprintf(fpth,"%s/ZS050_%02dRCV", RCSDDATA_PATH, Svrinf[ii].mecd);
        if(NULL == (SOCrcv_fp[ii] = fopen(fpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]\n", fpth, errno);
        }

        /* 送信Rawファイルのオープン */
        sprintf(fpth,"%s/ZS050_%02dSND.raw", RCSDDATA_PATH, Svrinf[ii].mecd);
        SOCsnd_fd[ii] = open(fpth, (O_WRONLY|O_CREAT|O_APPEND), (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
        if(SOCsnd_fd[ii] == -1) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]\n", fpth, errno);
        }

        /* 送信データファイルのオープン */
        sprintf(fpth,"%s/ZS050_%02dSND", RCSDDATA_PATH, Svrinf[ii].mecd);
        if(NULL == (SOCsnd_fp[ii] = fopen(fpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("データ退避ファイルのオープンに失敗。FILE[%s] ERR[%d]\n", fpth, errno);
        }
    }

    /* メモリ退避情報の読込み */
    sFncGetMemSave();

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
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
    char    fpth[101];
    int     ii, rtn, maxfd, li_stopFlg, ptr;
    short   f_snd;
    ssize_t blen;
    fd_set  rsds;
    struct  timeval  tv;
    struct  stat     st;

    /* 初期処理 */
    tv.tv_sec  = sAppEnv.timeout_Sec;
    tv.tv_usec = sAppEnv.timeout_uSec;

    /* 分析機とのソケット接続処理 */
    if(sFncConctSvr(1) != RTN_OK)
        return(RTN_NG);

    sprintf(fpth,"%s/%d_ME_RECONCT", ONLINE_PATH, sAppEnv.lineno);


    /* メインループ */
    for( ; ; ) {

        maxfd = -1;
        FD_ZERO(&rsds);
        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].sfd == -1)  continue;
            FD_SET(Svrinf[ii].sfd, &rsds);
            if(Svrinf[ii].sfd > maxfd)  maxfd = Svrinf[ii].sfd;
        }

        /* ソケット送信処理 */
        f_snd = 0;
        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].sfd == -1)  continue;

            rtn = sFncSocSend(&Svrinf[ii], ii);       /* Ack、依頼情報等の送信処理 */
            if(rtn > 0)  f_snd = 1;
        }

        /* 終了通知の状態確認 */
        li_stopFlg = 0;
        sFncShmGet(&sAppEnv, &li_stopFlg);
        if(li_stopFlg == 1)  break;

        /* 回線断先の再接続処理 */
        if(stat(fpth, &st) == 0) {
            rtn = sFncConctSvr(2);  unlink(fpth);
        }

        /* メモリ情報の退避(CtlNo.、MeSEQNo.) */
        sFncPutMemSave();

        if(f_snd > 0)  continue;


        /* ソケット受信処理 */
        tv.tv_sec  = sAppEnv.timeout_Sec;
        tv.tv_usec = sAppEnv.timeout_uSec;

        rtn = select(maxfd+1, &rsds, NULL, NULL, &tv);
        if(rtn < 0) {
            if(errno == EINTR)  continue;
            sFncPutLog(TRCKIND_ERROR, __FILE__, "select", __LINE__,
                       EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                       "SOCKET状態監視に割込みが発生しました。ERR[%d]", errno);
            if(DbgFlg)  printf("SOCKET状態監視に割込みが発生しました。ERR[%d]\n", errno);
            break;
        }
        else if(rtn == 0) {
            if(DbgFlg)  printf("SOCKETタイムアウト...\n");
            continue;
        }

        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].sfd == -1)  continue;

            if(FD_ISSET(Svrinf[ii].sfd, &rsds)) {
                rtn = sFncSocRecv(&Svrinf[ii], ii);   /* ソケットデータ受信 */
            }
        }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    }

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
    char    buff[11];
    int     ii, blen;

    /* シグナルハンドラの設定 */
    signal(SIGINT, endFunction);
    signal(SIGKILL, endFunction);

    if(DbgFlg)  printf("終了処理中.....");

    /* メモリ情報の退避(CtlNo.) */
    sFncPutMemSave();

    /* ソケットクローズ処理 */
    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
        if(Svrinf[ii].sfd == -1)  continue;
        shutdown(Svrinf[ii].sfd, 2);
        close(Svrinf[ii].sfd);
    }


    /* 送受信データ退避ファイルのクローズ */
    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
        if(SOCrcv_fd[ii] > 0)      close(SOCrcv_fd[ii]);
        if(SOCsnd_fd[ii] > 0)      close(SOCsnd_fd[ii]);

        if(SOCrcv_fp[ii] != NULL)  fclose(SOCrcv_fp[ii]);
        if(SOCsnd_fp[ii] != NULL)  fclose(SOCsnd_fp[ii]);
    }


    /* 共有メモリ削除 */
    sFncShmDel(&sAppEnv);

    /* 終了のログ出力 */
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "プログラム終了");
    if(DbgFlg)  printf("プログラム終了\n");

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
    char    fpth[256], fbuf[256];
    char    wk_mekbn[5], wk_chname[21], wk_chnum[8], wk_kmcode[8];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstChanl_cnt = 0;
    sprintf(fpth,"%s/mechmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "チャネルマスタファイルのオープンに失敗しました。File[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("チャネルマスタファイルのオープンに失敗しました。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

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

            if(c_dl == 1) {
                memcpy(wk_mekbn, (fbuf+c_st), (c_en-c_st));
                wk_mekbn[(c_en-c_st)] = '\0';
            }
            else if(c_dl == 2) {
                memcpy(wk_chnum, (fbuf+c_st), (c_en-c_st));
                wk_chnum[(c_en-c_st)] = '\0';
            }
            else if(c_dl == 3) {
                memcpy(wk_chname, (fbuf+c_st), (c_en-c_st));
                wk_chname[(c_en-c_st)] = '\0';
            }
            else if(c_dl == 4) {
                memcpy(wk_kmcode, (fbuf+c_st), (c_en-c_st));
                wk_kmcode[(c_en-c_st)] = '\0';
                break;
            }
        }
        sFncTrim(wk_mekbn);
        sFncTrim(wk_chnum);
        sFncTrim(wk_chname);
        sFncTrim(wk_kmcode);

        sprintf(MstChanl[mm].mekbn,"%s", wk_mekbn);
        MstChanl[mm].chnum = atoi(wk_chnum);
        sprintf(MstChanl[mm].chname,"%s", wk_chname);
        MstChanl[mm].kmcode = atoi(wk_kmcode);
        mm++;

        if(mm > MSTCHANL_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "チャネルマスタの配列MAX数を超えました。File[%s]", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstChanl_cnt = mm;

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
    int     c_st, c_en, c_dl;
    int     ii, jj, len;
    FILE    *fp;

    sprintf(fpth,"%s/sysknrmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetUdate", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "システム管理マスタファイルのオープンに失敗。File[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("システム管理マスタファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    fgets(fbuf, 512, fp);                             /* 1行取得 */
    len = strlen(fbuf);

    c_dl = jj = 0;
    for(ii = 0 ; ii < len ; ii++) {
        if(fbuf[ii] == ',') {
            if(c_dl == 2)  { buff[jj] = '\0';  break; }
            c_dl++;  continue;
        }
        if(c_dl == 2)  { buff[jj] = fbuf[ii];  jj++; }
    }
    fclose(fp);

    sprintf(sAppEnv.udate,"%4.4s/%2.2s/%2.2s", buff, (buff+4), (buff+6));
    return(RTN_OK);
}

/**/
static void sFncGetMemSave()
/******************************************************************************
*  関 数 名　：sFncGetMemSave()                                               *
*  機能概要　：メモリ退避情報の読込み/反映処理                                *
*  入　　力　：                                                               *
*  引    数                                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
******************************************************************************/
{
    char    fpth[101], fbuf[101], qctp[11];
    int     ii, mecd, ctlno, meseq;
    FILE    *fp;
    struct stat  st;

    sprintf(fpth,"%s/%d_MD101.sav", ONLINE_PATH, sAppEnv.lineno);
    if(stat(fpth, &st) != 0) {
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "メモリ退避ファイルが見つかりません。File[%s]", fpth);
        if(DbgFlg)  printf("メモリ退避ファイルが見つかりません。File[%s]\n", fpth);
        return;
    }

    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
        return;
    }

    for( ; ; ) {
        if(NULL == fgets(fbuf,101, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;

        sscanf(fbuf,"%d %d %d", &mecd, &ctlno, &meseq);
        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].mecd == (short)mecd) {
                Svrinf[ii].ctlno = ctlno;             /* 該当号機のCtlNo.設定 */
                Svrinf[ii].meseqno = meseq;           /* 該当号機のMeSEQNo.設定 */
                if(DbgFlg)  printf("CtlNo読込み完了   ME[%d] CtlNo[%d]   TP[%s]\n", mecd, ctlno, qctp);
                if(DbgFlg)  printf("MeSEQNo読込み完了 ME[%d] MeSEQNo[%d]\n", mecd, meseq);
                break;
            }
        }
    }
    fclose(fp);

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return;
}

/**/
static void sFncPutMemSave()
/******************************************************************************
*  関 数 名　：sFncPutMemSave()                                               *
*  機能概要　：メモリ退避情報の書込み処理                                     *
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

    sprintf(fpth,"%s/%d_MD101.sav", ONLINE_PATH, sAppEnv.lineno);
    if(NULL == (fp = fopen(fpth,"w"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("メモリ退避ファイルのオープンに失敗。File[%s] ERR[%d]\n", fpth, errno);
        return;
    }

    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
        fprintf(fp,"%d %d %d\n",
                Svrinf[ii].mecd, Svrinf[ii].ctlno, Svrinf[ii].meseqno);
    }
    fclose(fp);

    return;
}

/**/
static int sFncConctSvr(short flg)
/******************************************************************************
*  関 数 名　：sFncConctSvr()                                                 *
*  機能概要　：ソケット接続処理                                               *
*  入　　力　：                                                               *
*  引    数    short  flg; (1; 全接続、2: 再接続)                             *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    int     ii, jj, ertmp, try_max;
    struct  hostent  *server;
    struct  sockaddr_in sv_addr[GOKI_MAX];

    /* ソケットfdの初期化 */
    if(flg == 1) {
        for(ii = 0 ; ii < GOKI_MAX ; ii++) {
            Svrinf[ii].sfd = -1;
        }
    }

    if(flg == 1)  try_max = RETRY_MAX1;
    else          try_max = RETRY_MAX2;

    /* 接続処理 */
    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {

        if(flg == 2 && Svrinf[ii].sfd > 0)  continue;

        server = (struct hostent *)gethostbyname(Svrinf[ii].svhost);
        if(server == NULL) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncConctSvr", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "サーバのIP情報取得に失敗しました。Server[%s]", Svrinf[ii].svhost);
            if(DbgFlg)  printf("サーバのIP情報取得に失敗しました。Server[%s]\n", Svrinf[ii].svhost);
            return(RTN_NG);
        }

        /* ソケット生成 */
        Svrinf[ii].sfd = socket(AF_INET, SOCK_STREAM, 0);
        if(Svrinf[ii].sfd < 0) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncConctSvr", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET生成に失敗しました。Server[%s] ME[%d] ERR[%d]", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
            if(DbgFlg)
                printf("SOCKET生成に失敗しました。Server[%s] ME[%d] ERR[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
            return(RTN_NG);
        }

        memset(&sv_addr[ii], '\0', sizeof(struct sockaddr_in));
        sv_addr[ii].sin_family = AF_INET;
        sv_addr[ii].sin_port   = (u_short)htons((u_short)Svrinf[ii].svport);
        memcpy(&sv_addr[ii].sin_addr, server->h_addr, server->h_length);


        /* ソケット接続 */
        for(jj = 0 ; jj < try_max ; jj++) {
            ertmp = 0;
            if((connect(Svrinf[ii].sfd, (struct sockaddr *)&sv_addr[ii], sizeof(struct  sockaddr_in))) < 0) {
                if(DbgFlg)  printf("SOCKET接続に失敗しました。Server[%s] ME[%d] ERR[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
                ertmp = errno;
                sleep(1);  continue;
            }
            else  break;
        }
        if(ertmp != 0) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncConctSvr", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "SOCKET接続に失敗しました。Server[%s] ME[%d] ERR[%d]", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
            if(DbgFlg)  printf("SOCKET接続に失敗しました。Server[%s] ME[%d] ERR[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);

            close(Svrinf[ii].sfd);
            Svrinf[ii].sfd = -1;
            continue;
        }

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET接続しました。Server[%s] ME[%d]", Svrinf[ii].svhost, Svrinf[ii].mecd);
        if(DbgFlg)  printf("SOCKET接続しました。Server[%s] ME[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd);
    }

    return(RTN_OK);
}

/**/
static int sFncSocSend(SVRINF *svif, int idx)
/******************************************************************************
*  関 数 名　：sFncSocSend()                                                  *
*  機能概要　：ソケットデータ送信制御処理                                     *
*  入　　力　：                                                               *
*  引    数    short  flg; (1; 全接続、2: 再接続)                             *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    buff[SOCFRAME_MAXSIZE +1];
    int     f_sd, blen, ptr;
    time_t  tlsec;

    f_sd = 0;

    if(svif->sts == 1 ||
       svif->sts == 3 || svif->sts == 11) {           /* Ack送信 */
        buff[0] = 0x06;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts++;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("Ack送信...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 5) {                         /* 依頼送信前のENQ送信 */
        buff[0] = 0x05;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts++;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("ENQ送信...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 7) {                         /* 依頼情報送信 */
        if(sFncIraiSend(svif, idx) != RTN_OK) {
            buff[0] = 0x15;                           /* エラー時はNAK送信 */
            blen = send(svif->sfd, buff, 1, 0);
            svif->sts = 20;
            time(&tlsec);  svif->rstime = tlsec;
            sFncSocdatOut("SND", buff, blen, idx);
        }
        f_sd = 1;
    }
    /* 分割された依頼データの送信処理 */
    else if(svif->sts == 9 && svif->iraifrm_max > 1) {
        if(svif->iraifrm_cnt < svif->iraifrm_max) {
            ptr = svif->iraifrm_cnt * SOCFRAME_MAXSIZE;
            time(&tlsec);  svif->rstime = tlsec;

            if((svif->iraifrm_cnt +1) >= svif->iraifrm_max) {
                blen = send(svif->sfd, (FrmBuf[idx]+ptr), (Frbuf_len[idx]-ptr), 0);
                sFncSocdatOut("SND", (FrmBuf[idx]+ptr), (Frbuf_len[idx]-ptr), idx);
                svif->sts = 14;
            }
            else {
                blen = send(svif->sfd, (FrmBuf[idx]+ptr), SOCFRAME_MAXSIZE, 0);
                sFncSocdatOut("SND", (FrmBuf[idx]+ptr), SOCFRAME_MAXSIZE, idx);
                svif->sts = 8;
            }

            (svif->iraifrm_cnt)++;
            f_sd = 1;
            sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "依頼データ(分割続き)送信: ME[%d]", svif->mecd);
            if(DbgFlg)  printf("依頼データ(分割)送信: ME[%d]\n", svif->mecd);
/* printf("ircnt[%d] irmax[%d]\n",svif->iraifrm_cnt,svif->iraifrm_max); */
        }
    }
    else if(svif->sts == 9 || svif->sts == 15) {      /* EOT送信 */
        buff[0] = 0x04;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts = 0;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("EOT送信...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 20) {                        /* NAK送信 */
        buff[0] = 0x15;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts++;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("NAK送信...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 30) {                        /* NAK受信後、直前の依頼データ再送 */
        blen = send(svif->sfd, FrmBuf[idx], Frbuf_len[idx], 0);
        svif->sts = 8;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", FrmBuf[idx], blen, idx);
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "依頼データ(再送分)送信: ME[%d]", svif->mecd);
        if(DbgFlg)  printf("依頼データ(再送分)送信: ME[%d]\n", svif->mecd);
    }

    return(f_sd);
}

/**/
static int sFncIraiSend(SVRINF *svif, int idx)
/******************************************************************************
*  関 数 名　：sFncIraiSend()                                                 *
*  機能概要　：測定依頼ソケット送信処理                                       *
*  入　　力　：                                                               *
*  引    数    SVRINF *svif                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[101], fbuf[512], buff[256], b_tmp[101];
    char    wk_kenid[30 +1], wk_kmcode[7 +1], cksum[3], wk_kensphs[1 +1];
    char    wk_ino[11 +1], *frmb, ch_rireki[201];
    int     ii, jj, c_st, c_en, c_dl, dcnt, dcntmax, blen;
    int     reccnt, recmax, fptr, sptr;
    short   f_fend, frmnum, wk_kenkaisu, wk_chnum;
    time_t  tlsec;
    FILE    *fp;
    struct stat  st;


    /* rackid,rackposによる依頼ファイル特定 */
    for(ii = 0 ; ii < 2 ; ii++) {
        if(ii == 0)       strcpy(b_tmp, NEWFL_SUFFIX);
        else if(ii == 1)  strcpy(b_tmp, SKNIRAI_SUFFIX);

        sprintf(fpth,"%s/%s%s_____%03d.%s", IRAINEW_PATH, IRAI_PREFIX, svif->rackid, atoi(svif->pos), b_tmp);
        if(DbgFlg)  printf("依頼ファイルサーチ: [%s%s_____%03d.%s]...", IRAI_PREFIX, svif->rackid, atoi(svif->pos), b_tmp);

        if(stat(fpth, &st) == 0 && st.st_size > 0) {
            if(DbgFlg)  printf("存在確認!!!\n");
            break;
        }
        else { if(DbgFlg)  printf("無い!!!\n"); }
    }

    /* 依頼ファイルが見つからないとき */
    if(ii >= 2) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncIraiSend", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "依頼ファイルが見つかりません。\"依頼無し\"の依頼MSG送信 File[%s] ME[%d] ERR[%d]", fpth, svif->mecd, errno);
        if(DbgFlg)  printf("\"依頼無し\"の依頼MSG送信 File[%s] ME[%d] ERR[%d]\n", fpth, svif->mecd, errno);

        memset(SndBuf,'\0', SOCBUF_MAXSIZE);
        strcpy(SndBuf,"H|\\^&|LIS||||||||O|P|1");     /* ヘッダREC生成 */
        dcnt = 22;
        SndBuf[dcnt] = 0x0d;  dcnt++;

        strcpy((SndBuf+dcnt),"P|1");  dcnt = dcnt+3;  /* 患者REC生成 */
        SndBuf[dcnt] = 0x0d;  dcnt++;

        /* 「依頼無し」の測定依頼REC生成 */
        (svif->meseqno)++;                            /* 内部meseqnoをカウントアップ */
        sprintf((SndBuf+dcnt),"O|1|%s|||||||||P||^^^^7||S|||%06d^^|||||||O", svif->kenid, svif->meseqno);
        dcnt = dcnt + (strlen(svif->kenid) +43);
        SndBuf[dcnt] = 0x0d;  dcnt++;

        goto IRAISND;
    }


    /* 依頼ファイルオープン */
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncIraiSend", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "依頼ファイルのオープンに失敗しました。File[%s] ME[%d] ERR[%d]", fpth, svif->mecd, errno);
        if(DbgFlg)  printf("依頼ファイルのオープンに失敗しました。File[%s] ME[%d] ERR[%d]\n", fpth, svif->mecd, errno);
        return(RTN_NG);
    }

    /* 依頼ファイルの有効レコード数をカウント */
    reccnt = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strlen(fbuf) < 50)  continue;

        reccnt++;
    }
    recmax = reccnt;
    rewind(fp);


    /* 測定依頼MSGの生成 */
    svif->iraifrm_cnt = svif->iraifrm_max = 0;
    memset(SndBuf,'\0', SOCBUF_MAXSIZE);
    strcpy(SndBuf,"H|\\^&|LIS||||||||O|P|1");              /* ヘッダREC生成 */
    dcnt = 22;
    SndBuf[dcnt] = 0x0d;  dcnt++;

    strcpy((SndBuf+dcnt),"P|1");   dcnt = dcnt+3;          /* 患者REC生成 */
    SndBuf[dcnt] = 0x0d;  dcnt++;
    sprintf((SndBuf+dcnt),"O|1|%s||", svif->kenid);        /* 測定依頼REC生成 */
    dcnt = dcnt + (strlen(svif->kenid) +6);

    f_fend = reccnt = wk_kenkaisu = 0;
    wk_kenid[0] = wk_kmcode[0] = buff[0] = '\0';
    ch_rireki[0] = '\0';                                   /* #01 追加 */
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strlen(fbuf) < 50)  continue;

        reccnt++;
        if(reccnt >= recmax)  f_fend = 1;                  /* 現レコードが最終データ */

        /* 各フィールドの処理 */
        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < strlen(fbuf) ; ii++) {
            if(fbuf[ii] == ',')  {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            if(c_dl == 6) {                                /* 項目(CH)設定 */
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

                    for(jj = 0 ; jj < MstChanl_cnt ; jj++) {
                        if(MstChanl[jj].kmcode == atoi(wk_kmcode))
                            break;
                    }
                    if(jj >= MstChanl_cnt) {
                        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncIraiSend", __LINE__,
                            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "チャネル番号がマスタに見つかりません。(非測定項目) KM[%s] ME[%d]", wk_kmcode, svif->mecd);
                        if(DbgFlg)  printf("チャネル番号がマスタに見つかりません。(非測定項目) KM[%s] ME[%d]\n", wk_kmcode, svif->mecd);

                        if(f_fend == 0)  break;

                        blen = strlen(buff);
                        if(buff[blen-1] == '\\')  buff[blen-1] = '|';
                        break;
                    }
                    else  wk_chnum = MstChanl[jj].chnum;

                    /* #01 同一チャネルNoを複数検出した場合は、最初のものを対象とする */
                    sprintf(b_tmp,"%d", wk_chnum);
                    if(NULL != strstr(ch_rireki, b_tmp)) {      /* #01 既に検出済みの場合はBreak */
                        if(f_fend == 0)  break;

                        blen = strlen(buff);
                        if(buff[blen-1] == '\\')  buff[blen-1] = '|';
                        break;
                    }

                    if(ch_rireki[0] == '\0')  strcpy(ch_rireki, b_tmp);
                    else  { strcat(ch_rireki,",");  strcat(ch_rireki, b_tmp); }
                }

                /* 測定項目(チャネル)の組立て (希釈条件"M"付きで初検から送信) */
                if(f_fend == 0)  sprintf(b_tmp,"^^^%03d^M\\", wk_chnum);
                else             sprintf(b_tmp,"^^^%03d^M|",  wk_chnum);
                strcat(buff, b_tmp);
            }

            if(c_dl == 7) {                                /* 再検判断(検査回数取得) */
                memcpy(b_tmp, (fbuf+c_st), (c_en-c_st));
                b_tmp[(c_en-c_st)] = '\0';
                if(wk_kenkaisu < (short)atoi(b_tmp))  wk_kenkaisu = (short)atoi(b_tmp);
            }

            if(c_dl == 11) {                               /* 再検判断(検査工程区分)取得 */
                memcpy(wk_kensphs, (fbuf+c_st), (c_en-c_st));
                wk_kensphs[(c_en-c_st)] = '\0';
            }

            if(c_dl == 13) {                               /* 依頼書No.取得 */
                memcpy(wk_ino, (fbuf+c_st), (c_en-c_st));
                wk_ino[(c_en-c_st)] = '\0';
                sFncTrim(wk_ino);
            }

            if(c_dl == 37) {                               /* 希釈条件取得 */
                memcpy(b_tmp, (fbuf+c_st), (c_en-c_st));
                b_tmp[(c_en-c_st)] = '\0';
                sFncTrim(b_tmp);
                if(wk_kenkaisu > 1 && b_tmp[0] != '\0' && b_tmp[0] != '1') {
                    if(islower(b_tmp[0]))  b_tmp[0] = toupper(b_tmp[0]);

                    /* 再検(希釈)の場合は希釈条件を設定しなおす */
                    if(DbgFlg)  printf("再検の希釈条件を再設定 [%s]\n", b_tmp);
                    blen = strlen(buff);
                    buff[blen-2] = b_tmp[0];
                }
            }
        }

        if(f_fend == 1)  break;
    }
    fclose(fp);


    /* アクションコード、容器形状、検体材料("血清"("S")固定)、 */
    /* レポートタイプを固定で設定 */
    blen = strlen(buff);
    (svif->meseqno)++;                                /* 内部meseqnoをカウントアップ */
    sprintf((buff+blen),"||||||A||^^^^7||S|||%06d^%s^|||||||O", svif->meseqno, wk_ino);

 /* strcat(buff,"||||||A||^^^^7||S||||||||||O"); */
    blen = strlen(buff);
    strcpy((SndBuf+dcnt), buff);
    dcnt = dcnt + blen;
    SndBuf[dcnt] = 0x0d;  dcnt++;


  IRAISND:
    /* 終了MSG生成 */
    strcpy((SndBuf+dcnt),"L|1|N");   dcnt = dcnt+5;
    SndBuf[dcnt] = 0x0d;  dcnt++;
    SndBuf[dcnt] = '\0';

    /* 送信フレーム生成処理 */
    memset(FrmBuf[idx],'\0', SOCBUF_MAXSIZE);
/*********
    if(svif->frmno >= 7)  frmnum = 0;
    else                  frmnum = svif->frmno +1;
*********/
    frmnum = 1;
    svif->frmno = 1;


    /* 送信バッファサイズを確認 */
    if((dcnt+7) > SOCFRAME_MAXSIZE) {                      /* 最大フレーム長を超える場合 */
        dcntmax = dcnt;
        fptr = sptr = dcnt = 0;
        frmb = FrmBuf[idx];

        /* フレーム長に合わせて送信バッファを分割 */
        for(ii = 1 ; (ii*(SOCFRAME_MAXSIZE -7)) <= dcntmax ; ii++) {
            sprintf((frmb+fptr),"%c%d", 0x02, frmnum);
            memcpy((frmb+fptr+2), (SndBuf+sptr), (SOCFRAME_MAXSIZE -7));
            dcnt = dcnt + 2 + (SOCFRAME_MAXSIZE -7);
            frmb[dcnt] = 0x17;  dcnt++;                    /* "ETB"を設定 */

            sFncGetChecksum((frmb+fptr), dcnt, cksum);     /* チェックサム算出 */
            sprintf((frmb+dcnt),"%s%c%c", cksum, 0x0d, 0x0a);
            dcnt = dcnt +4;

/* printf("ii[%d] dcnt[%d]\n",ii,dcnt); */
            fptr = ii * SOCFRAME_MAXSIZE;
            sptr = ii * (SOCFRAME_MAXSIZE -7);
            if(frmnum >= 7)  frmnum = 0;
            else             frmnum++;
        }

        /* 最終送信フレーム生成 */
        svif->iraifrm_max = ii;                            /* 送信フレーム数を設定 */
        sprintf((frmb+fptr),"%c%d", 0x02, frmnum);
        memcpy((frmb+fptr+2), (SndBuf+sptr), (dcntmax - ((ii-1)*(SOCFRAME_MAXSIZE -7))));
        dcnt = dcnt + 2 + (dcntmax - ((ii-1)*(SOCFRAME_MAXSIZE -7)));
        frmb[dcnt] = 0x03;  dcnt++;                        /* "ETX"を設定 */

        sFncGetChecksum((frmb+fptr), dcnt, cksum);         /* チェックサム算出 */
        sprintf((frmb+dcnt),"%s%c%c", cksum, 0x0d, 0x0a);
        dcnt = dcnt +4;
        Frbuf_len[idx] = dcnt;

        /* 分割フレームのソケット送信処理(1フレーム目) */
        blen = send(svif->sfd, FrmBuf[idx], SOCFRAME_MAXSIZE, 0);
        time(&tlsec);
        svif->rstime = tlsec;
        svif->sts = 8;
        svif->iraifrm_cnt = 1;
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "依頼データ(分割)送信: RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);
        if(DbgFlg)  printf("依頼データ(分割)送信: RackID[%s] Pos[%s] ME[%d]\n", svif->rackid, svif->pos, svif->mecd);

/* printf("irmax[%d] ircnt[%d]\n",svif->iraifrm_max,svif->iraifrm_cnt); */

        /* 送信データの退避 */
        sFncSocdatOut("SND", FrmBuf[idx], SOCFRAME_MAXSIZE, idx);

        return(RTN_OK);
    }

    /* 以下は最大フレーム長を超えない場合 */
    /* STX、フレームNo、ETXを付加 */
    sprintf(FrmBuf[idx],"%c%d%s%c", 0x02, frmnum, SndBuf, 0x03);
    dcnt = dcnt+3;
    svif->frmno = frmnum;

    /* チェックサム算出 */
    sFncGetChecksum(FrmBuf[idx], dcnt, cksum);
    sprintf((FrmBuf[idx]+dcnt),"%s%c%c", cksum, 0x0d, 0x0a);
    Frbuf_len[idx] = dcnt+4;

    /* ソケット送信処理 */
    blen = send(svif->sfd, FrmBuf[idx], Frbuf_len[idx], 0);
    time(&tlsec);
    svif->rstime = tlsec;
    svif->iraifrm_cnt = svif->iraifrm_max = 1;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "依頼データ送信: RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);
    if(DbgFlg)  printf("依頼データ送信: RackID[%s] Pos[%s] ME[%d]\n", svif->rackid, svif->pos, svif->mecd);

    /* 状態ステータス設定 */
    svif->sts = 8;

    /* 送信データの退避 */
    sFncSocdatOut("SND", FrmBuf[idx], Frbuf_len[idx], idx);


/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static int sFncSocRecv(SVRINF *svif, int idx)
/******************************************************************************
*  関 数 名　：sFncSocRecv()                                                  *
*  機能概要　：ソケットデータ受信制御処理                                     *
*  入　　力　：                                                               *
*  引    数    SVRINF *svif                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    buff[11];
    int     blen, rtn, ptr;
    short   frmnum;
    time_t  tlsec;

    /* ソケット受信 */
    memset(RcvBuf,'\0', (SOCFRAME_MAXSIZE +1));
    blen = recv(svif->sfd, RcvBuf, SOCFRAME_MAXSIZE, 0);
    time(&tlsec);
    svif->rstime = tlsec;
    if(blen > 0)
        sFncSocdatOut("RCV", RcvBuf, blen, idx);      /* ソケットデータ退避 */

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    if(blen == 1) {
        if((RcvBuf[0] & 0xff) == 0x06) {              /* ACK受信 */
            svif->sts++;
            if(DbgFlg)  printf("ACK recvd...Server PORT[%d]\n", svif->svport);
        }
        else if((RcvBuf[0] & 0xff) == 0x05) {         /* ENQ受信 */
            svif->sts = 1;
            if(DbgFlg)  printf("ENQ recvd...Server PORT[%d]\n", svif->svport);
        }
        else if((RcvBuf[0] & 0xff) == 0x04) {         /* EOT受信 */
            svif->sts++;
            if(DbgFlg)  printf("EOT recvd...Server PORT[%d]\n", svif->svport);
        }
        else if((RcvBuf[0] & 0xff) == 0x17) {         /* NAK受信 */
            if(svif->sts == 6)  svif->sts = 5;
            else                svif->sts = 30;
            if(DbgFlg)  printf("NAK recvd...Server PORT[%d]\n", svif->svport);
        }
    }
    else if(blen == 0) {
        if(DbgFlg)  printf("NULL Break....Connection down Port[%d]\n", svif->svport);
        sFncPutLog(TRCKIND_ERROR, __FILE__, "recv", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET接続がダウンしました。Port[%d] ERR[%d]", svif->svport, errno);
        close(svif->sfd);
        svif->sfd = -1;
        return(RTN_NG);
    }
    else if(blen < 0) {
        if(DbgFlg)  printf("Read error....Connection down Port[%d]\n", svif->svport);
        sFncPutLog(TRCKIND_ERROR, __FILE__, "recv", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET読込みエラーが発生しました。Port[%d] ERR[%d]", svif->svport, errno);
        close(svif->sfd);
        svif->sfd = -1;
        return(RTN_NG);
    }
    else if(blen < 7) {                              /* #01 その他不正MSG受信 */
        if(DbgFlg)  printf("Invalid msg received....ME[%d] Port[%d] Len[%d]\n", svif->mecd, svif->svport, blen);
        sFncPutLog(TRCKIND_ERROR, __FILE__, "recv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "不正なMSGを受信しました。ME[%d] Port[%d] Len[%d]", svif->mecd, svif->svport, blen);
        svif->sts = 20;                               /* NAK送信のためのsts設定 */
    }

    else {
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */

        /* "ETB"付きの分割MSG受信時の処理(測定結果MSGと判断) */
        if((RcvBuf[blen-5] & 0xff) == 0x17) {
            if(svif->rsltsts == 0) {
                memset(RBuf_rslt[idx],'\0', SOCBUF_MAXSIZE);
                memcpy(RBuf_rslt[idx], RcvBuf, (blen-5));
                svif->rsltlen = blen -5;
                svif->rsltsts = 1;
                buff[0] = RcvBuf[1];  buff[1] = '\0';
                svif->rsltfrm_no = (short)atoi(buff);
/* printf("LEN[%d]\n",blen); */
            }
            else {
                /* フレームNo.チェック(結果MSG受信時のみ) */
                buff[0] = RcvBuf[1];  buff[1] = '\0';
                frmnum = (short)atoi(buff);
                if((frmnum == 0 && svif->rsltfrm_no != 7) ||
                   (frmnum > 0  && frmnum != (svif->rsltfrm_no +1))) {
                    sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncSocRecv", __LINE__,
                        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "フレームNo.が不整合です。FRMNo[%d] PrevNo[%s]", frmnum, svif->rsltfrm_no);
                    if(DbgFlg)  printf("フレームNo.が不整合です。FRMNo[%d] PrevNo[%s]\n", frmnum, svif->rsltfrm_no);
                    svif->sts = 20;                   /* NAK送信のためのsts設定 */
                    return(RTN_NG);
                }

                ptr = svif->rsltlen;
                memcpy((RBuf_rslt[idx]+ptr), (RcvBuf+2), (blen-7));
                svif->rsltlen = svif->rsltlen + blen -7;
            }
            svif->sts = 11;                           /* 結果MSG受信時のSTSにしてACKを返す */
            return(RTN_OK);
        }
        else if((RcvBuf[blen-5] & 0xff) == 0x03 && svif->rsltsts > 0) {
            ptr = svif->rsltlen;
            memcpy((RBuf_rslt[idx]+ptr), (RcvBuf+2), (blen-2));
            blen = svif->rsltlen + blen -2;
            svif->sts = 11;

            rtn = sFncRcvdatProc(svif, RBuf_rslt[idx], blen);   /* 連結フレームデータ処理 */
            svif->rsltsts = 0;
            svif->rsltlen = 0;
        }

        /* 分割無しの受信フレームデータ処理 */
        else  rtn = sFncRcvdatProc(svif, RcvBuf, blen);

        if(rtn == RTN_NG)  svif->sts = 20;            /* NAK送信のためのsts設定 */
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static int sFncRcvdatProc(SVRINF *svif, char *rbuf, int blen)
/******************************************************************************
*  関 数 名　：sFncRcvdatProc()                                               *
*  機能概要　：ソケット受信フレームデータ解析処理                             *
*  入　　力　：                                                               *
*  引    数    SVRINF *svif                                                   *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    buff[512], cksum[3], buf2[51], buf3[31];
    char    wk_rackid[8], wk_pos[4], msgknd[5];
    char    wk_kenid[30 +1], wk_chnum[5], wk_kekka[12 +1], wk_unit[11 +1];
    char    wk_errcd1[2 +1], wk_errcd2[30 +1], wk_usrfield[101];
    char    *buf1, *tmptr, *errtkn;
    int     ii, jj, c_st, c_en, c_dl, c_st2, c_en2, c_dl2, c_res, ctlnum;
    int     mm, rseq, rtn, len;
    short   f_hdr, frmnum;
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */

    /* 受信バッファ内のSTXの位置をサーチ */
    if((rbuf[0] & 0xff) != 0x02) {                    /* 先頭がSTXかどうかを判断 */
        for(ii = 0 ; ii < blen ; ii++) {
            if((rbuf[ii] & 0xff) == 0x02) {           /* STXの位置をサーチ */
                rbuf = (rbuf +ii);  break;
            }
        }
    }
    buff[0] = rbuf[1];  buff[1] = '\0';
    svif->frmno = atoi(buff);

    /* CHKSUMチェック (連結フレーム以外の場合に実行) */
    if(blen <= SOCFRAME_MAXSIZE) {
        sFncGetChecksum(rbuf, blen, cksum);
        if(memcmp((rbuf+blen-4), cksum, 2) != 0) {
            memcpy(buff, (rbuf+blen-4), 2);  buff[2] = '\0';
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "チェックサムが不整合です。CKSUM[%s] Calc[%s]", buff, cksum);
            if(DbgFlg)  printf("チェックサムが不整合です。CKSUM[%s] Calc[%s]\n", buff, cksum);
            return(RTN_NG);
        }
    }


    /* ヘッダレコード解析 */
    msgknd[0] = '\0';
    f_hdr = c_st = 0;
    for(ii = 2 ; ii < blen ; ii++) {
        if(rbuf[ii] == '|')  { c_dl++;  continue; }   /* 各レコード内のデリミタをカウント */
        if(f_hdr == 0) {
            if(rbuf[ii] == 'H')  { f_hdr = 1;  c_dl = 0;  continue; }
        }
        else if(f_hdr == 1) {
            if(c_dl == 10 && msgknd[0] == '\0') {     /* MSG種別を取得 */
                msgknd[0] = rbuf[ii];  continue;
            }
            if((rbuf[ii] & 0xff) == 0x0d)  { c_st = ii+1;  break; }
        }
    }
if(DbgFlg)  printf("msgknd[%c]\n",msgknd[0]);


    /* 問合せMSGの処理 */
    if(msgknd[0] == 'Q') {
        if(rbuf[c_st] != 'Q') {                       /* MSG種別の不整合時 */
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "MSG種別が不整合です。Mknd[%c] Mtyp[%c]", msgknd[0], rbuf[c_st]);
            if(DbgFlg)  printf("MSG種別が不整合です。Mknd[%c] Mtyp[%c]\n", msgknd[0], rbuf[c_st]);
            return(RTN_NG);
        }

        /* rackid, rackpos取得 */
        c_en = c_dl = 0;
        c_st = c_st +4;
        for(ii = c_st ; ii < blen ; ii++) {
            if(rbuf[ii] == '^' || rbuf[ii] == '|') {
                c_en = ii;  c_dl++;
            }
            else  continue;

            if(c_dl == 1) {
            	if(c_en-c_st-2 <= 0) {
                    sprintf(wk_rackid, "     " );
                    sprintf(wk_pos, "  " );
		} else {
                    memcpy(wk_rackid, (rbuf+c_st), (c_en-c_st-2));
                    wk_rackid[(c_en-c_st-2)] = '\0';
                    memcpy(wk_pos, (rbuf+c_en-2), 2);
                    wk_pos[2] = '\0';
		}
            }
            else if(c_dl == 2) {
                memcpy(wk_kenid, (rbuf+c_st), (c_en-c_st));
                wk_kenid[(c_en-c_st)] = '\0';
                sprintf(svif->kenid,"%s", wk_kenid);
                break;
            }
        }

        sFncTrim(wk_rackid);
        sFncTrim(wk_pos);
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "問合せ受信: RackID[%s] Pos[%s] ME[%d]", wk_rackid, wk_pos, svif->mecd);
        if(DbgFlg)  printf("問合せ受信: RackID[%s] Pos[%s] ME[%d]\n", wk_rackid, wk_pos, svif->mecd);
        sprintf(svif->rackid,"%s", wk_rackid);
        sprintf(svif->pos,"%03d", atoi(wk_pos));
        svif->sts = 3;
    }


    /* 測定結果MSGの処理 */
    else if(msgknd[0] == 'R') {
        if(rbuf[c_st] == 'L') {                       /* 結果が空MSGのとき */
            sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "空の結果MSGを受信: RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);
            if(DbgFlg)  printf("空の結果MSGを受信 RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);

            svif->sts = 11;
            return(RTN_OK);
        }
        else if(rbuf[c_st+4] != 'O') {                /* MSG種別の不整合時 */
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "MSG種別が不整合です。Mknd[%c] Mtyp[%c]", msgknd[0], rbuf[c_st]);
            if(DbgFlg)  printf("MSG種別が不整合です。Mknd[%c] Mtyp[%c]\n", msgknd[0], rbuf[c_st+4]);

            return(RTN_NG);
        }

        /* 検体No.取得 (Oレコードより) */
        c_st = c_st+8;                                /* 検体IDの先頭にセット */
        c_en = c_dl = 0;
        for(ii = c_st ; ii < blen ; ii++) {
            if(rbuf[ii] == '^' || rbuf[ii] == '|') {
                c_en = ii;  c_dl++;
            }
            else  continue;

            if(c_dl == 1) {
            	if(c_en-c_st-2 <= 0) {
                    sprintf(wk_rackid, "00000" );
                    sprintf(wk_pos, "00" );
		} else {
                    memcpy(wk_rackid, (rbuf+c_st), (c_en-c_st-2));
                    wk_rackid[(c_en-c_st-2)] = '\0';
                    memcpy(wk_pos, (rbuf+c_en-2), 2);
                    wk_pos[2] = '\0';
                }
            }
            else if(c_dl == 2) {
                memcpy(wk_kenid, (rbuf+c_st), (c_en-c_st));
                wk_kenid[(c_en-c_st)] = '\0';
                break;
            }
        }

        sFncTrim(wk_rackid);
        sFncTrim(wk_pos);

        if(wk_rackid[0] == '\0' || wk_pos[0] == '\0') {
            memcpy(buff, (rbuf+c_st-4), (ii-c_st));
            buff[(ii-c_st)] = '\0';
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "検体No.(ラックID, POS)の取得に失敗しました。Orec[%s]", buff);
            if(DbgFlg)  printf("検体No.(ラックID, POS)の取得に失敗しました。Orec[%s]\n", buff);
            return(RTN_NG);
        }

        /* OレコードのユーザフィールドよりMeSEQNo.取得 */
        if(strncmp(wk_kenid,"QC", 2) != 0) {
            c_en = c_dl = 0;
            wk_usrfield[0] = buf2[0] = '\0';
            for(ii = c_st ; ii < blen ; ii++) {       /* 検体IDの先頭からスタート */
                if(rbuf[ii] == '|') {
                    if(c_en > 0)  c_st = c_en+1;
                    c_en = ii;  c_dl++;
                }
                else  continue;

                if(c_dl == 17) {                      /* ユーザフィールド */
                    memcpy(wk_usrfield, (rbuf+c_st), (c_en-c_st));
                    wk_usrfield[(c_en-c_st)] = '\0';
                    if(wk_usrfield[0] == '\0')  break;

                    c_dl2 = 0;
                    for(jj = 0 ; jj < strlen(wk_usrfield) ; jj++) {
                        if(wk_usrfield[jj] == '^' || wk_usrfield[jj] == '|') {
                            c_dl2++;
                        }
                        else  continue;

                        if(c_dl2 == 1) {
                            memcpy(buf2, wk_usrfield, jj);  buff[jj] = '\0';
                            break;
                        }
                    }

                    if(buf2[0] != '\0')  svif->rmsg_meseq = atoi(buf2);
                    break;
                }
            }

            if(wk_usrfield[0] == '\0' || buf2[0] == '\0') {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "結果MSGからの分析機SEQ取得に失敗。UserField[%s]", wk_usrfield);
                if(DbgFlg)  printf("結果MSGからの分析機SEQ取得に失敗。UserField[%s]\n", wk_usrfield);

                svif->sts = 11;
                return(RTN_SKIP);
            }
        }


        for(ii = c_st ; ii < blen ; ii++) {           /* Rレコードの頭出し */
            if((rbuf[ii] & 0xff) == 0x0d) {
                c_st = ii+1;  break;
            }
        }

        /* 測定結果の取得 (全てのRレコードより) */
        c_dl = c_en = rseq = 0;
        c_res = 1;
        for(ii = c_st ; ii < blen ; ii++) {
            if(rbuf[ii] == '|') {
                if(c_en > 0)  c_st = c_en+1;
                c_dl++;  c_en = ii;
            }
            else if((rbuf[ii] & 0xff) == 0x0d) {      /* 個々のRレコードの最後を検出 */
                if(rbuf[ii+1] == 'L')  break;
                c_res++;  c_dl = 0;  c_en = ii;  continue;
            }
            else  continue;

            if(c_dl == 2) {                           /* RレコードのSeqチェック */
                memcpy(buff, (rbuf+c_st), (c_en-c_st));
                buff[(c_en-c_st)] = '\0';  sFncTrim(buff);

                if(atoi(buff) != (rseq +1)) {
                    sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                           EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                           "RレコードのSEQNo.が不整合です。Kenid[%s] RSeq[%d] PrevNo[%d]", wk_kenid, atoi(buff), rseq);
                    if(DbgFlg)  printf("RレコードのSEQNo.が不整合です。Kenid[%s] RSeq[%d] PrevNo[%d]\n", wk_kenid, atoi(buff), rseq);
                }
                rseq = atoi(buff);
            }
            else if(c_dl == 3) {                      /* チャネルNo.取得 */
                mm = c_dl2 = 0;
                for(jj = c_st ; jj < c_en ; jj++) {
                    if(rbuf[jj] == '^') {
                        if(c_dl2 == 3)  { wk_chnum[mm] = '\0';  break; }
                        c_dl2++;  mm = 0;  continue;
                    }

                    if(c_dl2 == 3)  { wk_chnum[mm] = rbuf[jj];  mm++; }
                }
                sFncTrim(wk_chnum);
            }
            else if(c_dl == 4) {                      /* 結果値取得 */
                memcpy(wk_kekka, (rbuf+c_st), (c_en-c_st));
                wk_kekka[(c_en-c_st)] = '\0';   sFncTrim(wk_kekka);
            }
            else if(c_dl == 5) {                      /* 結果値単位取得 */
                memcpy(wk_unit, (rbuf+c_st), (c_en-c_st));
                wk_unit[(c_en-c_st)] = '\0';    sFncTrim(wk_unit);
            }
            else if(c_dl == 7) {                      /* 結果異常フラグ取得 */
                c_dl2 = c_en2 = 0;
                c_st2 = c_st;
                for(jj = c_st ; jj < c_en ; jj++) {
                    if(rbuf[jj] == '^') {
                        if(c_en2 > 0)  c_st2 = c_en2 +1;
                        c_en2 = jj;  c_dl2++;
                    }
                    else  continue;

                    if(c_dl2 == 1) {
                        memcpy(wk_errcd1, (rbuf+c_st2), (c_en2-c_st2));
                        wk_errcd1[(c_en2-c_st2)] = '\0';
                        if(rbuf[jj+1] == '^')  { wk_errcd2[0] = '\0';  break; }
                    }
                    else if(c_dl2 == 2) {
                        if((c_en2-c_st2) <= 30) {
                            memcpy(wk_errcd2, (rbuf+c_st2), (c_en2-c_st2));
                            wk_errcd2[(c_en2-c_st2)] = '\0';
                        }
                        else {
                            memcpy(wk_errcd2, (rbuf+c_st2), 30);
                            wk_errcd2[30] = '\0';
                        }
                        break;
                    }
                }
if(DbgFlg)  printf("err1[%s]\n",wk_errcd1);
if(DbgFlg)  printf("err2[%s]\n",wk_errcd2);

                /* 複数の分析機エラー受信の際の分割処理 */
                if(wk_errcd2[0] != '\0') {
                 /* sprintf(buf2,"\\%s^", wk_errcd1); */
                    for(jj = 0 ; jj < 10 ; jj++) {
                        if(jj == 0)  buf1 = wk_errcd2;
                        else         buf1 = NULL;

                        if(NULL == (errtkn = strtok_r(buf1," ", &tmptr)))
                            break;
                        if(jj == 0)  sprintf(buf3,"%s", errtkn);
                        else {
                            strcat(buf3,",");  len = strlen(buf3);  sprintf((buf3+len),"%s", errtkn);
                        }
                    }
                    strcpy(wk_errcd2, buf3);
                }


                /* コントロール検体の場合、コントロールフラグを設定 */
                if(strncmp(wk_kenid,"QC", 2) == 0) {
/******************
                    ctlnum = svif->ctlno;
                    if(svif->ctlflg == 0)  { svif->ctlflg = 1;  ctlnum++; }
******************/
                    (svif->ctlno)++;

                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                           EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                           "コントロール結果受信: KenID[%s] CH[%s] ME[%d] No[%d]", wk_kenid, wk_chnum, svif->mecd, svif->ctlno);
                    if(DbgFlg)  printf("Ctl結果受信: KenID[%s] CH[%s] ME[%d] No[%d]\n", wk_kenid, wk_chnum, svif->mecd, svif->ctlno);
                }
                else {
                    /* コントロールフラグが"1"のときはctlnoをカウントアップ */
/******************
                    if(svif->ctlflg == 1)  { svif->ctlflg = 0;  (svif->ctlno)++; }
******************/

                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                           EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                           "測定結果受信: KenID[%s] CH[%s] ME[%d]", wk_kenid, wk_chnum, svif->mecd);
                    if(DbgFlg)  printf("測定結果受信: KenID[%s] CH[%s] ME[%d]\n", wk_kenid, wk_chnum, svif->mecd);
                }
if(DbgFlg)  printf("KEN[%s] CH[%s]\n",wk_kenid,wk_chnum);


                /* 結果データを一時ファイルに出力 */
                rtn = sFncKekSave(svif, wk_rackid, wk_pos, wk_kenid, wk_chnum, wk_kekka, wk_errcd1, wk_errcd2);
            }
        }
        svif->sts = 11;
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static int sFncKekSave(SVRINF *svif, char *wk_rack, char *wk_pos, char *wk_ken, char *wk_ch, char *wk_kek, char *err1, char *err2)
/******************************************************************************
*  関 数 名　：sFncKekSave()                                                  *
*  機能概要　：測定結果の受信データのファイル出力処理                         *
*  入　　力　：                                                               *
*  引    数    SVRINF *svif                                                   *
*              char   *wk_ken;                                                *
*              char   *wk_ch;                                                 *
*              char   *wk_kek;                                                *
*              char   *err1;                                                  *
*              char   *err2;                                                  *
*  出　　力　：                                                               *
*  復帰情報　：  0     : 成功                                                 *
* 　　　　　　　-1     : 失敗                                                 *
******************************************************************************/
{
    char    fpth[256], fnm[101], buff[31];
    int     ii, ctlnum;
    FILE    *fp;
    struct stat st;
    struct tm  *tms;

    /* 退避ファイル名の決定 */
    if(strncmp(wk_ken,"QC", 2) == 0) {                /* コントロール結果 */
     /* ctlnum = svif->ctlno +1; */
        sprintf(fnm,"%d_QCK%.10s_%s_%d.dat", sAppEnv.lineno, wk_ken, wk_ch, svif->ctlno);
        sprintf(fpth,"%s/%s", KEKKATMP_PATH, fnm);
    }
    else {                                            /* 一般検体の場合 */
        sprintf(fnm,"%d_KEK%s___%s_%s.dat", sAppEnv.lineno, wk_rack, wk_pos, wk_ch);
        sprintf(fpth,"%s/%s", KEKKATMP_PATH, fnm);
    }
if(DbgFlg)  printf("fpth[%s]\n",fpth);

    /* 出力ファイルが重複して存在する場合 */
    if(stat(fpth, &st) == 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKekSave", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "結果出力一時ファイルが既に存在しています。FILE[%s]", fnm);
        if(DbgFlg)  printf("結果出力一時ファイルが既に存在しています。FILE[%s]\n", fnm);
        return(RTN_NG);
    }

    if(NULL == (fp = fopen(fpth,"w"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKekSave", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "結果出力一時ファイルのオープンに失敗。FILE[%s] ERR[%d]", fnm, errno);
        if(DbgFlg)  printf("結果出力一時ファイルのオープンに失敗。PATH[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    /* チャネルNo.から項目コードを特定 */
    for(ii = 0 ; ii < MstChanl_cnt ; ii++) {
        if(MstChanl[ii].chnum == atoi(wk_ch))
            break;
    }

    if(NULL != (tms = localtime(&(svif->rstime)))) {
        sprintf(buff,"%d-%02d-%02d %02d:%02d:%02d",
                (tms->tm_year +1900), (tms->tm_mon +1), tms->tm_mday,
                tms->tm_hour, tms->tm_min, tms->tm_sec);
    }


    /* 測定結果を一時ファイルに出力 */
    ctlnum = svif->ctlno;
    if(strncmp(wk_ken,"QC", 2) == 0) {
     /* ctlnum++; */                                  /* Ctl結果ではカウントアップしないため、ここで算出 */
        svif->rmsg_meseq = 0;                         /* Ctl結果では分析機No.は"0" */
    }
    fprintf(fp,"%s,%d,%d,%s,%s,%07d,%s,%d,%s,%s",
            buff, svif->mecd, svif->rmsg_meseq, wk_ken, wk_ch, MstChanl[ii].kmcode,
            wk_kek, ctlnum, err1, err2);

    fclose(fp);

    return(RTN_OK);
}

/**/
static void sFncSocdatOut(char *flg, char *svbuf, int blen, short idx)
/******************************************************************************
*  関 数 名　：sFncSocdatOut()                                                *
*  機能概要　：ソケット送受信データ退避処理                                   *
*  入　　力　：                                                               *
*  引    数    char   *svbuf;                                                 *
*              int    blen;                                                   *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
******************************************************************************/
{
    char    buff[SOCFRAME_MAXSIZE +25];
    char    tmbuf[31];
    int     fd, len, ii, c_st, c_en;
    FILE    *fp;
    struct tm  *tms;

    if(strcmp(flg,"RCV") == 0)
          { fd = SOCrcv_fd[idx];  fp = SOCrcv_fp[idx]; }
    else  { fd = SOCsnd_fd[idx];  fp = SOCsnd_fp[idx]; }

    if(NULL != (tms = localtime(&(Svrinf[idx].rstime)))) {
        sprintf(buff,"[%d/%02d/%02d %02d:%02d:%02d] ",
            (tms->tm_year +1900), (tms->tm_mon +1), tms->tm_mday,
            tms->tm_hour, tms->tm_min, tms->tm_sec);
        len = 22;
    }
    else  { strcpy(buff,"[] ");  len = 3; }

    strcpy(tmbuf, buff);

    /* Rawデータの退避 */
    memcpy((buff+len), svbuf, blen);
    buff[(blen+len)] = '\0';
    write(fd, buff, (blen+len));
    if(blen == 1)  write(fd,"\n", 1);

    /* 編集データの出力 */
    if(blen == 1) {
        if((svbuf[0] & 0xff) == 0x04)       fprintf(fp,"%-60s%s\n", "(EOT)", tmbuf);
        else if((svbuf[0] & 0xff) == 0x05)  fprintf(fp,"%-60s%s\n", "(ENQ)", tmbuf);
        else if((svbuf[0] & 0xff) == 0x06)  fprintf(fp,"%-60s%s\n", "(ACK)", tmbuf);
        else if((svbuf[0] & 0xff) == 0x15)  fprintf(fp,"%-60s%s\n", "(NAK)", tmbuf);
    }
    else {
        c_st = 1;
        c_en = 0;
        for(ii = 1 ; ii < blen ; ii++) {
            if((svbuf[ii] & 0xff) == 0x0d) {
                if(c_en > 0)  c_st = c_en +1;
                c_en = ii;
            }
            else if((svbuf[ii] & 0xff) == 0x17 || (svbuf[ii] & 0xff) == 0x03) {
                if(blen == SOCFRAME_MAXSIZE) {
                    if(c_en > 0)  c_st = c_en +1;
                    c_en = ii;
                    memcpy(buff, (svbuf+c_st), (c_en-c_st));
                    buff[(c_en-c_st)] = '\0';
                    fprintf(fp,"%s\n", buff);
                    break;
                }
            }
            else  continue;

            memcpy(buff, (svbuf+c_st), (c_en-c_st));
            buff[(c_en-c_st)] = '\0';
            if(strncmp((buff+1),"H|", 2) == 0)
                  fprintf(fp,"%-60s%s\n", buff, tmbuf);
            else  fprintf(fp,"%s\n", buff);
            if(strncmp(buff,"L|1|N", 5) == 0)  break;
        }
    }
    fflush(fp);

    return;
}

/**/
static void sFncGetChecksum(char *sbuf, int imax, char *cksum)
/******************************************************************************
*  関 数 名　：sFncGetChecksum()                                              *
*  機能概要　：チェックサム生成処理                                           *
*  入　　力　：                                                               *
*  引    数    char   *socbuf;                                                *
*              char   *cksum;                                                 *
*  出　　力　：                                                               *
*  復帰情報　：                                                               *
******************************************************************************/
{
    int     calc, ii;

    calc = -1;
    for(ii = 0 ; ii < imax ; ii++) {
        if(sbuf[ii] == 0x02)  continue;               /* STXは除外 */

        if(calc == -1) {
              calc = (int)sbuf[ii] + (int)sbuf[ii+1];  ii++;
        }
        else  calc = calc + (int)sbuf[ii];

        calc = calc % 256;

        if(sbuf[ii] == 0x03 || sbuf[ii] == 0x17)      /* ETB or ETXまで処理したらbreak */
            break;
    }

    sprintf(cksum,"%02x", (calc & 0xff));
    if(islower(cksum[0]))  cksum[0] = toupper(cksum[0]);
    if(islower(cksum[1]))  cksum[1] = toupper(cksum[1]);

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
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリの作成に失敗しました ERR[%d]", errno ) ;
        if(DbgFlg)  printf("共有メモリの作成に失敗しました ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  アタッチ
    shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのアタッチに失敗しました ERR[%d]", errno ) ;
        if(DbgFlg)  printf("共有メモリのアタッチに失敗しました ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  値設定
    *shmData = 0 ;

    //  デタッチ
    if ( shmdt ( shmData ) == -1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのデタッチに失敗しました ERR[%d]", errno ) ;
        if(DbgFlg)  printf("共有メモリのデタッチに失敗しました ERR[%d]\n", errno);
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
        if(DbgFlg)  printf("共有メモリの取得に失敗しました ERR[%d]\n", errno);
        return(RTN_NG);
    }

    //  アタッチ
    shmData = ( int * )shmat(pAppEnv->shm_Id, 0 , 0);
    if ( shmData == ( int * )-1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのアタッチに失敗しました ERR[%d]", errno ) ;
        if(DbgFlg)  printf("共有メモリのアタッチに失敗しました ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  値設定
    *pshmData = *shmData ;

/****************
    if(DbgFlg) {
        printf("共有メモリ[GET] shmKey[%d] ID[%d] Data[%d] Add[%x]\n",
               pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData);
    }
****************/

    //  デタッチ
    if ( shmdt ( shmData ) == -1 ) {
        //  異常終了    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "共有メモリのデタッチに失敗しました ERR[%d]", errno ) ;
        if(DbgFlg)  printf("共有メモリのデタッチに失敗しました ERR[%d]\n", errno);
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

    if(DbgFlg)  printf("共有メモリ[DEL] shmKey[%d] ID[%d]\n", pAppEnv->shm_Key, pAppEnv->shm_Id);

    //  削除
    if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static void sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName, int plLineNo, char *pcExeFlg, char *pcErrCode, char *pcfmt, ... )
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
