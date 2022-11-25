/* 改訂履歴

*/

#define  ONLINE_PATH         "/apdata/today/file/KEA00/kea00ap/ZS050"
#define  RCSDDATA_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/socdata"
#define  IRAINEW_PATH        "/apdata/today/file/KEA00/kea00ap/ZS050/irai_file"
#define  IRAIERR_PATH        "/apdata/today/file/KEA00/kea00ap/ZS050/irai_file/err"
#define  KEKKATMP_PATH       "/apdata/today/file/KEA00/kea00ap/ZS050/kekka_onl/new"
#define  MSTFILE_PATH        "/apdata/today/file/KEA00/kea00ap/ZS050/mst_file"

#define  IRAI_PREFIX         "OD_"
#define  SKNIRAI_SUFFIX      "dat_01"
#define  CTLKEK_PREFIX       "QCK_"
#define  DATKEK_PREFIX       "KEK_"

#define  NEWFL_SUFFIX        "dat"
#define  ENDFL_SUFFIX        "end"
#define  ERRFL_SUFFIX        "err"

/* システムパラメータ格納構造体 */
struct appEnv {
    int     shm_Id ;
    key_t   shm_Key ;
    long    timeout_Sec ;
    long    timeout_uSec ;
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
/* 接続分析機情報格納構造体 */
typedef struct {
    short   mecd;
    char    svhost[51];
    int     svport;
    int     sfd;
    short   sts;
    time_t  rstime;
    char    rackid[8];
    char    pos[8];
    char    kenid[30 +1];
    short   frmno;
    short   iraifrm_cnt;
    short   iraifrm_max;
    short   rsltfrm_no;
    int     rsltlen;
    short   rsltsts;
    char    qctype[6];
    short   ctlflg;
    int     ctlno;
    int     meseqno;
    int     rmsg_meseq;
} SVRINF;

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
/* チャネルマスタ格納構造体 */
typedef struct {
    char    mekbn[4 +1];
    int     chnum;
    char    chname[16 +1];
    int     kmcode;
} CHLMST;

