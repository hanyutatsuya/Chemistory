
/* ��������
 2020.05.26 #01 ����  ���ʈꎞ�t�@�C���ɑ΂��ĊY���˗��t�@�C���������ꍇ�ɁA
                      ���ꎞ�t�@�C����"err"Dir�Ɉړ����ď������p������悤
                      �C��

*/

/******************************************************************************
* �C���N���[�h�錾                                                            *
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
* �}�N���錾                                                                  *
******************************************************************************/
#define  FLARRY_MAX               (2000)              /* ���ʈꎞ�t�@�C�����X�g�i�[MAX�� */
#define  MSTCHANL_MAX             (1000)              /* �`���l���}�X�^�̔z��MAX�� */
#define  MSTKISYK_MAX             (10240)             /* ��ߔ{���}�X�^�̔z��MAX�� */
#define  MSTRANGE_MAX             (20480)             /* �͈̓`�F�b�N�}�X�^�̔z��MAX�� */
#define  MSTMESTS_MAX             (200)               /* ���͋@�f�[�^�t���O�̔z��MAX�� */
#define  MSTKNREN_MAX             (10240)             /* �֘A���ڃ}�X�^�̔z��MAX�� */
#define  MSTCALC_MAX              (10240)             /* �v�Z���ڃ}�X�^�̔z��MAX�� */
#define  MSTKM_MAX                (10240)             /* ���ڃ}�X�^�̔z��MAX�� */
#define  MSTCTL_MAX               (3000)              /* �R���g���[���}�X�^�̔z��MAX�� */

#define  MYAPP_LOG_ERRCODE_NON    "00000000"
#define  DBL_EPSILON              (2.2204460492503130808473E-16)

#define  OPERATOR_LT              ('<')               /* ������: ����                     */
#define  OPERATOR_GT              ('>')               /* ������: �z����                   */
#define  OPERATOR_EQ              ('=')               /* ������: ��v                     */
#define  STR_NE                   "<>"                /* ������: �s��v                   */
#define  MAXCNT_ITEM_IFBLOCK      (5)                 /* IF �u���b�N���̗v�f��            */
#define  _EOS                     ('\0')              /* End Of String (������I�[�L��)   */
#define  _MASK_TOUPPER            (0x00DF)            /* ���p�p���������啶���ϊ��̃}�X�N */
#define  STR_BEGIN_IFBLOCK        ("IF(")             /* IF ���J�n������������            */
#define  STR_BEGIN_POW            ("POW(")
#define  STR_BEGIN_LOG            ("LOG(")
#define  STR_BEGIN_LOG10          ("LOG10(")

/* �ȉ��A IF �����ňӖ���������                                           */
#define  PARENT_BEGIN             ('(')
#define  PARENT_END               (')')
#define  SPLITTER_COMMA           (':')               /* �������ƓK�p�l�̋�؂�           */

/******************************************************************************
* �O���[�o���錾                                                              *
******************************************************************************/
static char    LmName[25];                            /* �v���O������ */
struct stcLogMember  gstLogMem;                       /* ���O�o�͏�� */
struct appEnv  sAppEnv;                               /* ini�t�@�C���p�����[�^�i�[�\���� */
static char    Temp_fpth[101];                        /* ���ʈꎞ�t�@�C�����X�g���i�[����ꎞ�t�@�C�� */
KEKFL_STR      FLrec[FLARRY_MAX];                     /* ���ʈꎞ�t�@�C�����X�g�i�[�\���� */
static int     FLrec_cnt;                             /* ���ʈꎞ�t�@�C�����X�g�i�[�\���̐� */
KEKFL_STR      KekFL[FLARRY_MAX];                     /* ���ʍ쐬�ς݂�RackID,POS�i�[�\���� */
static int     KekFL_cnt;                             /* ���ʍ쐬�ς݂�RackID,POS�i�[�\���̐� */
KEKFL_STR      KekFL_tmp[FLARRY_MAX];                 /* ���ʍ쐬�ς݂�RackID,POS�i�[�\���� */
static int     KekFLtmp_cnt;                          /* ���ʍ쐬�ς݂�RackID,POS�i�[�\���̐� */
CHLMST         MstChanl[MSTCHANL_MAX];                /* �`���l���}�X�^�i�[�\���� */
static int     MstChanl_cnt;                          /* �`���l���}�X�^�̃f�[�^�� */
KISYKMST       MstKisyk[MSTKISYK_MAX];                /* ��ߔ{���}�X�^�i�[�\���� */
static int     MstKisyk_cnt;                          /* ��ߔ{���}�X�^�̃f�[�^�� */
RNGMST         MstRange[MSTRANGE_MAX];                /* �͈̓`�F�b�N�}�X�^�i�[�\���� */
static int     MstRange_cnt;                          /* �͈̓`�F�b�N�}�X�^�̃f�[�^�� */
MESTSMST       MstMests[MSTMESTS_MAX];                /* ���͋@�f�[�^�t���O�i�[�\���� */
static int     MstMeSts_cnt;                          /* ���͋@�f�[�^�t���O�̃f�[�^�� */
KANRENMST      MstKnren[MSTKNREN_MAX];                /* �֘A���ڃ}�X�^�i�[�\���� */
static int     MstKnren_cnt;                          /* �֘A���ڃ}�X�^�̃f�[�^�� */
CALCMST        MstCalc[MSTCALC_MAX];                  /* �v�Z���ڃ}�X�^�i�[�\���� */
static int     MstCalc_cnt;                           /* �v�Z���ڃ}�X�^�̃f�[�^�� */
KMMST          MstKm[MSTKM_MAX];                      /* ���ڃ}�X�^�i�[�\���� */
static int     MstKm_cnt;                             /* ���ڃ}�X�^�̃f�[�^�� */
CTLMST         MstCtl[MSTCTL_MAX];                    /* �R���g���[���}�X�^�i�[�\���� */
static int     MstCtl_cnt;                            /* �R���g���[���}�X�^�̃f�[�^�� */
static char    gszTransfer[260 + 1];                  /* �����񁨐��l �ϊ��o�b�t�@ */
static int     DbgFlg;                                /* �f�o�b�O�o�̓X�C�b�`(0:File�o�́A1:�W���o��) */
static char    Dbg_fpth[101];                         /* ���ʈꎞ�t�@�C�����X�g���i�[����ꎞ�t�@�C�� */
FILE           *Dbg_fp;                               /* �f�o�b�O���o�͗p�t�@�C���|�C���^ */


/******************************************************************************
* �֐��錾                                                                    *
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
*  �� �� ���@�Fmain()                                                         *
*  �@�\�T�v�@�F���C���֐�                                                     *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    int     ii, len, rtn;

    /* ���s���W���[�����擾 */
    len = strlen(argv[0]);
    for(ii = (len-1) ; ii >= 0 ; ii--) {
        if(argv[0][ii] == '/')  break;
    }
    if(ii >= 0)  sprintf(LmName,"%s", &argv[0][ii+1]);
    else         sprintf(LmName,"%s", argv[0]);

    /* �o�b�N�O���E���h�Ŏ��s */
    if(daemon(0, 1) < 0) {
        fprintf(stderr,"%s : Error (daemon Err[%d])\n", LmName, errno);
        exit(-1);
    }

    /* �������� */
    if(initFunction(argc, argv) != 0) {
        fprintf(stderr,"%s : Error (initFunction)\n", LmName);
        goto END;
    }


    /* ���C������ */
    rtn = mainFunction();


    /* �I������ */
  END:
    endFunction();

    exit(0);
}

/**/
static int initFunction(int argc, char **argv)
/******************************************************************************
*  �� �� ���@�FinitFunction()                                                 *
*  �@�\�T�v�@�F��������                                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��    int  argc;     (�����̐�)                                      *
*              char  **argv;  (�����̃|�C���^)                                *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    lc_prmBuf[256], wk_buff[101];
    int     i_tmp;
    BMLPRM  *bp;

    /* �����`�F�b�N */
    if(argc < 2) {
        fprintf(stderr,"%s : Invalid argument !!!\n", LmName);
        return(RTN_NG);
    }

    /* ���O�I�[�v�� */
    if(ZbmlOpenLog(argv[1]) != 0) {
        fprintf(stderr,"%s : Log open failed !!!\n", LmName);
        return(RTN_NG);
    }

    /* �V�O�i���n���h���̐ݒ� */
    signal(SIGINT,  endFunction);
    signal(SIGKILL, endFunction);

    /* ���O��񏉊��ݒ� */
    memset(&gstLogMem,'\0', sizeof(struct stcLogMember));
    sprintf(gstLogMem.pcLoginId,"%s", getenv("LOGNAME"));
    sprintf(gstLogMem.pcAppName,"%s", LmName);
    gstLogMem.lPid = getpid();

    /* Debug�o�̓t���O�ݒ� */
    DbgFlg = 0;
    if(argc >= 3 && isdigit(argv[2][0]))  DbgFlg = atoi(argv[2]);

    /* �J�n���O�o�� */
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "�v���O�����N��");

    /* �p�����[�^�t�@�C���I�[�v�� */
    if(NULL == (bp = ZbmlPrmOpen(argv[1]))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]",
                   argv[1]);
        return(RTN_NG);
    }

    /* �����Ώۂ̃��C��No.�擾 */
    if(ZbmlPrmGetVal(bp, "LINENO", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[LINENO]");
        return(RTN_NG);
    }
    sAppEnv.lineno = atoi(lc_prmBuf);


    /* Debug�o�͐��ݒ� */
    Dbg_fp = stdout;
    if(DbgFlg == 0) {
        sprintf(Dbg_fpth,"%s/%d_MD102.dbg", DBGFILE_PATH, sAppEnv.lineno);
        if(NULL == (Dbg_fp = fopen(Dbg_fpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "initFunction", __LINE__, EXEFLG_NON,
                MYAPP_LOG_ERRCODE_NON, "�f�o�b�O�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]", Dbg_fpth);
            return(RTN_NG);
        }
    }


    /* ���L�������L�[ */
    if(ZbmlPrmGetVal(bp, "SHM_KEY", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[SHM_KEY]");
        fprintf(Dbg_fp,"�p�����[�^���擾�ł��܂���ł���[SHM_KEY]\n");
        return(RTN_NG);
    }
    sAppEnv.shm_Key = atoi(lc_prmBuf);

    /* ��������(����)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "NYUBI_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[NYUBI_KM]");
        fprintf(Dbg_fp,"�p�����[�^���擾�ł��܂���ł���[NYUBI_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.nyubi_km,"%s", wk_buff);
    sAppEnv.nyubi_ch = i_tmp;
    fprintf(Dbg_fp,"��������(����) KM[%s] CH[%d]\n", sAppEnv.nyubi_km, sAppEnv.nyubi_ch);

    /* ��������(�n��)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "YOUKETSU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[YOUKETSU_KM]");
        fprintf(Dbg_fp,"�p�����[�^���擾�ł��܂���ł���[YOUKETSU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.youkets_km,"%s", wk_buff);
    sAppEnv.youkets_ch = i_tmp;
    fprintf(Dbg_fp,"��������(�n��) KM[%s] CH[%d]\n", sAppEnv.youkets_km, sAppEnv.youkets_ch);

    /* ��������(���t)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "OUDAN_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[OUDAN_KM]");
        fprintf(Dbg_fp,"�p�����[�^���擾�ł��܂���ł���[OUDAN_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.oudan_km,"%s", wk_buff);
    sAppEnv.oudan_ch = i_tmp;
    fprintf(Dbg_fp,"��������(���t) KM[%s] CH[%d]\n", sAppEnv.oudan_km, sAppEnv.oudan_ch);

    /* ��������(���H)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "SEISYOKU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[SEISYOKU_KM]");
        fprintf(Dbg_fp,"�p�����[�^���擾�ł��܂���ł���[SEISYOKU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", wk_buff, &i_tmp);
    sprintf(sAppEnv.seisyk_km,"%s", wk_buff);
    sAppEnv.seisyk_ch = i_tmp;
    fprintf(Dbg_fp,"��������(���H) KM[%s] CH[%d]\n", sAppEnv.seisyk_km, sAppEnv.seisyk_ch);


    /* �p�����[�^�t�@�C���N���[�Y */
    ZbmlPrmClose(bp);


    /* ���L�������̍쐬 */
    if(sFncShmCrt(&sAppEnv) != RTN_OK)  return(RTN_NG);


    /* �e��}�X�^�f�[�^�̃��[�h */
    if(sFncChMstLoad() != RTN_OK)     return(RTN_NG);   /* �`���l���}�X�^ */
    if(sFncKskMstLoad() != RTN_OK)    return(RTN_NG);   /* ��߃}�X�^ */
    if(sFncRngMstLoad() != RTN_OK)    return(RTN_NG);   /* �͈̓}�X�^ */
    if(sFncMeStsMstLoad() != RTN_OK)  return(RTN_NG);   /* ���͋@�f�[�^�t���O�}�X�^ */
    if(sFncKrnMstLoad() != RTN_OK)    return(RTN_NG);   /* �֘A���ڃ}�X�^ */
    if(sFncCalcMstLoad() != RTN_OK)   return(RTN_NG);   /* �v�Z���ڃ}�X�^ */
    if(sFncKmMstLoad() != RTN_OK)     return(RTN_NG);   /* ���ڃ}�X�^ */
    if(sFncCtlMstLoad() != RTN_OK)    return(RTN_NG);   /* �R���g���[���}�X�^ */


    /* �������擾 */
    if(sFncGetUdate() != RTN_OK)  return(RTN_NG);
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "������ [%s]", sAppEnv.udate);
    fprintf(Dbg_fp,"������ [%s]\n", sAppEnv.udate);


    KekFL_cnt = 0;
    memset(&KekFL[0],'\0', (sizeof(KEKFL_STR) * FLARRY_MAX));

    /* ���C�����ʏo�͑҂��ޔ����̓Ǎ��� */
    sFncGetMemSave();

    return(RTN_OK);
}

/**/
static int mainFunction()
/******************************************************************************
*  �� �� ���@�FmainFunction()                                                 *
*  �@�\�T�v�@�F���C������                                                     *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    cmd[256];
    int     ii, kektmp_cnt, li_stopFlg;
    struct stat  st;

    /* �ꎞ�t�@�C���̐��� */
    sprintf(Temp_fpth,"/tmp/MD102_%d", getpid());
    kektmp_cnt = KekFL_cnt;

    /* ���C�����[�v */
    for( ; ; ) {

        /* ���茋�ʈꎞ�t�@�C���̃t�@�C�����X�g�擾 */
        sprintf(cmd,"/usr/bin/ls %s/%d* > %s 2>&1", KEKKATMP_PATH, sAppEnv.lineno, Temp_fpth);
        system(cmd);

        if(stat(Temp_fpth, &st) != 0 || st.st_size == 0) {
            fprintf(Dbg_fp,"���茋�ʈꎞ�t�@�C�����X�g�����쐬...\n");
            goto RNM_STRY;
        }

        /* ���荀��(�`���l��)�����������ʏ���I�o */
        sFncGetFilelst();
        if(FLrec_cnt == 0)  goto RNM_STRY;            /* ���茋�ʈꎞ�t�@�C���������Ƃ� */


        /* ��ʌ��̑��茋�ʊ֘A���� */
        sFncKekkaProc();


        /* Ctl���ʃt�@�C���쐬���� */
        sFncCtlKekkaProc();


        /* �T�e���C�g�����������ʃt�@�C���쐬 */
        /* (�����ɍČ��p����˗��t�@�C���쐬) */
        sFncMKSatKekka();


RNM_STRY:
        /* 1���b�N�����������ɑ΂��A���C�����ւ̌������ʃt�@�C���쐬 */
        sFncMkLineKekka();


        /* Line�p���[�g���[�����T�[�`���A�˗����ƕ����ă��l�[������ */
        sFncRnmStray();


        /* �āX���˗��̌��ʗv��(Line�������)�t�@�C�����o���� */
        /* (���茋�ʂ�҂����ɍāX���̓������b�N��������邽��) */
        sFncMkReSknKekka();


        /* �������̌��̏��ޔ����� */
        if(KekFL_cnt != kektmp_cnt) {
            sFncPutMemSave();
            kektmp_cnt = KekFL_cnt;
        }

        for(ii = 0 ; ii < KekFL_cnt ; ii++) {
            fprintf(Dbg_fp,"KekFL: CNT[%d] fnm[%s] Rack[%s] Pos[%d] CH[%d] KM[%07d] Ckens[%d] ken[%s] CAL[%d] STS[%d]\n",
                   KekFL_cnt,KekFL[ii].fname,KekFL[ii].rackid,KekFL[ii].pos,KekFL[ii].chnum,KekFL[ii].kmcode,
                   KekFL[ii].c_kensa,KekFL[ii].kenno,KekFL[ii].f_calc,KekFL[ii].sts);
        }

        /* �I���ʒm�̏�Ԋm�F */
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
*  �� �� ���@�FendFunction()                                                  *
*  �@�\�T�v�@�F�I������                                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{

    /* �V�O�i���n���h���̐ݒ� */
    signal(SIGINT,  endFunction);
    signal(SIGKILL, endFunction);

    /* �������̌��̏��ޔ����� */
    sFncPutMemSave();


    /* ���L�������폜 */
    sFncShmDel(&sAppEnv);

    /* �I���̃��O�o�� */
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "�v���O�����I��");
    fprintf(Dbg_fp,"�v���O�����I��\n");
    if(Dbg_fp != stdout)  fclose(Dbg_fp);

    unlink(Temp_fpth);

    /* ���O�̃N���[�Y */
    ZbmlCloseLog();

    exit(0);
}

/**/
static int sFncChMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncChMstLoad()                                                *
*  �@�\�T�v�@�F�`���l���}�X�^���[�h����                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "�`���l���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�`���l���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstChanl[0],'\0', (sizeof(CHLMST) * MSTCHANL_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strncmp(fbuf, ME_KUBUN, 4) != 0)  continue;     /* ���͋@�敪��Y���̂��̂͑ΏۊO */

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

            if(c_dl == 1)                             /* ���͋@�敪 */
                sprintf(MstChanl[mm].mekbn,"%s", buff);
            else if(c_dl == 2)                        /* �`���l��No. */
                MstChanl[mm].chnum = atoi(buff);
            else if(c_dl == 3)                        /* �`���l���� */
                sprintf(MstChanl[mm].chname,"%s", buff);
            else if(c_dl == 4) {                      /* �`���l��No. */
                MstChanl[mm].kmcode = atoi(buff);
                break;
            }
        }
        mm++;

        if(mm > MSTCHANL_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�`���l���}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"�`���l���}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstChanl_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "�`���l���}�X�^[%d]�����[�h���܂����B", MstChanl_cnt);
    fprintf(Dbg_fp,"�`���l���}�X�^[%d]�����[�h���܂����B\n", MstChanl_cnt);

    return(RTN_OK);
}

/**/
static int sFncKskMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncKskMstLoad()                                               *
*  �@�\�T�v�@�F��ߔ{���}�X�^���[�h����                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "��ߔ{���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"��ߔ{���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstKisyk[0],'\0', (sizeof(KISYKMST) * MSTKISYK_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strncmp(fbuf, ME_KUBUN, 4) != 0)  continue;     /* ���͋@�敪��Y���̂��̂͑ΏۊO */

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

            if(c_dl == 1)                             /* ���͋@�敪 */
                sprintf(MstKisyk[mm].mekbn,"%s", buff);
            else if(c_dl == 2)                        /* �����O���[�v */
                sprintf(MstKisyk[mm].kengrp,"%s", buff);
            else if(c_dl == 3)                        /* ���ڃR�[�h */
                MstKisyk[mm].kmcode = atoi(buff);
            else if(c_dl == 4)                        /* ��ߔ{�� */
                sprintf(MstKisyk[mm].kisykbai,"%s", buff);
            else if(c_dl == 5) {                      /* ��߉����l */
                sprintf(MstKisyk[mm].kisyk_low,"%s", buff);
                MstKisyk[mm].dbksk_low = (double)atof(MstKisyk[mm].kisyk_low);
            }
            else if(c_dl == 6) {                      /* ��ߏ���l */
                sprintf(MstKisyk[mm].kisyk_hi,"%s", buff);
                MstKisyk[mm].dbksk_hi = (double)atof(MstKisyk[mm].kisyk_hi);
            }
            else if(c_dl == 9) {                      /* ��ߋ敪(�˗��t�@�C���ɔ��f) */
                sprintf(MstKisyk[mm].kisyk_kbn,"%s", buff);
                break;
            }
        }
        mm++;

        if(mm > MSTKISYK_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKskMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "��ߔ{���}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"��ߔ{���}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstKisyk_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "��ߔ{���}�X�^[%d]�����[�h���܂����B", MstKisyk_cnt);
    fprintf(Dbg_fp,"��ߔ{���}�X�^[%d]�����[�h���܂����B\n", MstKisyk_cnt);

    return(RTN_OK);
}

/**/
static int sFncRngMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncRngMstLoad()                                               *
*  �@�\�T�v�@�F�͈̓`�F�b�N�}�X�^���[�h����                                   *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "�͈̓`�F�b�N�}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�͈̓`�F�b�N�}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstRange[0],'\0', (sizeof(RNGMST) * MSTRANGE_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 256, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(fbuf[0] != '1')  continue;                 /* �Ǎ��ݑΏۂ͍Č������W�̂� */

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

            if(c_dl == 2)                             /* �����O���[�v */
                sprintf(MstRange[mm].kengrp,"%s", buff);
            else if(c_dl == 3)                        /* ���ڃR�[�h */
                MstRange[mm].kmcode = atoi(buff);
            else if(c_dl == 4)                        /* �ޗ��R�[�h */
                sprintf(MstRange[mm].zaicode,"%s", buff);
            else if(c_dl == 5)                        /* �{�݃R�[�h */
                sprintf(MstRange[mm].usercode,"%s", buff);
            else if(c_dl == 6)                        /* ���� */
                sprintf(MstRange[mm].sex,"%s", buff);
            else if(c_dl == 7)                        /* �㉺���敪 */
                MstRange[mm].uplow = (short)atoi(buff);
            else if(c_dl == 8)                        /* ���e(�l)�敪 */
                MstRange[mm].valkbn = (short)atoi(buff);
            else if(c_dl == 9) {                      /* �����W��� */
                sprintf(MstRange[mm].rng_hi,"%s", buff);
                MstRange[mm].dbrng_hi = (double)atof(MstRange[mm].rng_hi);
            }
            else if(c_dl == 10) {                     /* �����W��� */
                sprintf(MstRange[mm].rng_low,"%s", buff);
                MstRange[mm].dbrng_low = (double)atof(MstRange[mm].rng_low);
                break;
            }
        }
        mm++;

        if(mm > MSTRANGE_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRngMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�͈̓`�F�b�N�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"�͈̓`�F�b�N�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstRange_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "�͈̓`�F�b�N�}�X�^[%d]�����[�h���܂����B", MstRange_cnt);
    fprintf(Dbg_fp,"�͈̓`�F�b�N�}�X�^[%d]�����[�h���܂����B\n", MstRange_cnt);

    return(RTN_OK);
}

/**/
static int sFncMeStsMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncMeStsMstLoad()                                             *
*  �@�\�T�v�@�F���͋@�e�[�^�t���O�}�X�^���[�h����                             *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "���͋@�t���O�}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"���͋@�t���O�}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
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

            if(c_dl == 1)                             /* ZS050�f�[�^�t���O */
                sprintf(MstMests[mm].zscode,"%s", buff);
            else if(c_dl == 2)                        /* �T�e���C�g�p�ϊ��R�[�h */
                sprintf(MstMests[mm].trcode,"%s", buff);
            else if(c_dl == 3) {                      /* �����R�[�h */
                if(buff[0] != '\0')  MstMests[mm].procf = (short)atoi(buff);
            }
            else if(c_dl == 4) {                      /* ��ߏ����R�[�h */
                sprintf(MstMests[mm].skncond,"%s", buff);
                MstMests[mm].pri = atoi((fbuf+c_en+1));
                break;
            }
        }
        mm++;

        if(mm > MSTMESTS_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRngMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "���͋@�t���O�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"���͋@�t���O�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstMeSts_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "���͋@�t���O�}�X�^[%d]�����[�h���܂����B", MstMeSts_cnt);
    fprintf(Dbg_fp,"���͋@�t���O�}�X�^[%d]�����[�h���܂����B\n", MstMeSts_cnt);

    return(RTN_OK);
}

/**/
static int sFncKrnMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncKrnMstLoad()                                               *
*  �@�\�T�v�@�F�֘A���ڃ}�X�^���[�h����                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "�֘A���ڃ}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�֘A���ڃ}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
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

            if(c_dl == 1)                             /* ���ڃR�[�h */
                MstKnren[mm].kmcode = atoi(buff);
            else if(c_dl == 2) {                      /* �֘A���ڃR�[�h */
                MstKnren[mm].kanrenkm = atoi(buff);
                break;
            }
        }
        mm++;

        if(mm > MSTKNREN_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKrnMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�֘A���ڃ}�X�^�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"�֘A���ڃ}�X�^�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstKnren_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "�֘A���ڃ}�X�^[%d]�����[�h���܂����B", MstKnren_cnt);
    fprintf(Dbg_fp,"�֘A���ڃ}�X�^[%d]�����[�h���܂����B\n", MstKnren_cnt);

    return(RTN_OK);
}

/**/
static int sFncCalcMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncCalcMstLoad()                                              *
*  �@�\�T�v�@�F�v�Z���ڃ}�X�^���[�h����                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "�v�Z���ڃ}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�v�Z���ڃ}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
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

            if(c_dl == 1)                             /* �����O���[�v */
                sprintf(MstCalc[mm].kengrp,"%s", buff);
            else if(c_dl == 2)                        /* ���ڃR�[�h */
                MstCalc[mm].kmcode = atoi(buff);
            else if(c_dl == 3)                        /* �{�݃R�[�h */
                sprintf(MstCalc[mm].usercode,"%s", buff);
            else if(c_dl == 4)                        /* �ޗ��R�[�h */
                sprintf(MstCalc[mm].zaicode,"%s", buff);
            else if(c_dl == 5) {                      /* �v�Z�� */
                sprintf(MstCalc[mm].calc,"%s", buff);
                break;
            }
        }
        mm++;

        if(mm > MSTCALC_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCalcMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�v�Z���ڃ}�X�^�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"�v�Z���ڃ}�X�^�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstCalc_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "�v�Z���ڃ}�X�^[%d]�����[�h���܂����B", MstCalc_cnt);
    fprintf(Dbg_fp,"�v�Z���ڃ}�X�^[%d]�����[�h���܂����B\n", MstCalc_cnt);

    return(RTN_OK);
}

/**/
static int sFncCtlMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncCtlMstLoad()                                               *
*  �@�\�T�v�@�F�R���g���[���}�X�^���[�h����                                   *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "�R���g���[���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"Ctl�}�X�^�t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    memset(&MstCtl[0],'\0', (sizeof(CTLMST) * MSTCTL_MAX));
    mm = 0;
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strncmp(fbuf, ME_KUBUN, 4) != 0)  continue;     /* ���͋@�敪��Y���̂��̂͑ΏۊO */

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

            if(c_dl == 2)                             /* �`���l��No. */
                MstCtl[mm].chnum = (short)atoi(buff);
            else if(c_dl == 3)                        /* Ctl��� */
                sprintf(MstCtl[mm].ctlknd,"%s", buff);
            else if(c_dl == 6)                        /* ���b�gNo. */
                sprintf(MstCtl[mm].lotno,"%s", buff);
            else if(c_dl == 8)                        /* ���ϒl */
                sprintf(MstCtl[mm].ctrlx,"%s", buff);
            else if(c_dl == 9) {                      /* SD�l */
                sprintf(MstCtl[mm].ctrlsd,"%s", buff);
                break;
            }
        }
        mm++;

        if(mm > MSTCTL_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCtlMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�R���g���[���}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"Ctl�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstCtl_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "�R���g���[���}�X�^[%d]�����[�h���܂����B", MstCtl_cnt);
    fprintf(Dbg_fp,"�R���g���[���}�X�^[%d]�����[�h���܂����B\n", MstCtl_cnt);

    return(RTN_OK);
}

/**/
static int sFncKmMstLoad()
/******************************************************************************
*  �� �� ���@�FsFncKmMstLoad()                                                *
*  �@�\�T�v�@�F���ڃ}�X�^���[�h����                                           *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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
            "���ڃ}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"���ڃ}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
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

            if(c_dl == 1)                             /* �����O���[�v */
                sprintf(MstKm[mm].kengrp,"%s", buff);
            else if(c_dl == 2)                        /* ���ڃR�[�h */
                MstKm[mm].kmcode = atoi(buff);
            else if(c_dl == 16) {                     /* �����_���� */
                MstKm[mm].place = atoi(buff);
                break;
            }
        }
        mm++;

        if(mm > MSTKM_MAX) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKmMstLoad", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "���ڃ}�X�^�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
            fprintf(Dbg_fp,"���ڃ}�X�^�}�X�^�̔z��MAX���𒴂��܂����BFile[%s]\n", fpth);
            fclose(fp);
            return(RTN_NG);
        }
    }
    fclose(fp);
    MstKm_cnt = mm;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "���ڃ}�X�^[%d]�����[�h���܂����B", MstKm_cnt);
    fprintf(Dbg_fp,"���ڃ}�X�^[%d]�����[�h���܂����B\n", MstKm_cnt);

    return(RTN_OK);
}

/**/
static int sFncGetUdate()
/******************************************************************************
*  �� �� ���@�FsFncGetUdate()                                                 *
*  �@�\�T�v�@�F�V�X�e���Ǘ��}�X�^����̏������擾����                         *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    fpth[101], fbuf[512], buff[21];
    int     ii, jj, len, c_st, c_en, c_dl;
    FILE    *fp;

    sprintf(fpth,"%s/sysknrmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetUdate", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�V�X�e���Ǘ��}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�V�X�e���Ǘ��}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    /* 1���R�[�h�擾 */
    if(NULL == fgets(fbuf, 512, fp)) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetUdate", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�V�X�e���Ǘ��}�X�^�t�@�C���̓Ǎ��݂Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�V�X�e���Ǘ��}�X�^�t�@�C���̓Ǎ��݂Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);

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
*  �� �� ���@�FsFncGetMemSave()                                               *
*  �@�\�T�v�@�F�������̃��C�����ʏo�͑҂��ޔ����̓Ǎ���/���f����            *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
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
                   "�������ޔ��t�@�C����������܂���B(�������) File[%s]", fpth);
        fprintf(Dbg_fp,"�������ޔ��t�@�C����������܂���BFile[%s]\n", fpth);
        return;
    }

    if(st.st_size < sizeof(KEKFL_STR))
        return;


    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
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
                "�������ޔ��t�@�C���̓Ǎ��݂Ɏ��s�BFile[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"�������ޔ��t�@�C���̓Ǎ��݂Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
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
           "[%d]���̃������ޔ��������[�h���܂����B", KekFL_cnt);
    fprintf(Dbg_fp,"[%d]���̃������ޔ��������[�h...\n", KekFL_cnt);

    return;
}

/**/
static void sFncPutMemSave()
/******************************************************************************
*  �� �� ���@�FsFncPutMemSave()                                               *
*  �@�\�T�v�@�F�������̃��C�����ʏo�͑҂��ޔ����̏����ݏ���                 *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
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
            "�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
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
*  �� �� ���@�FsFncGetFilelst()                                               *
*  �@�\�T�v�@�F���ʂ��������t�@�C���ꗗ�̃��������[�h����                     *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    fpth[101], fnm[51], fbuf[101];
    char    wk_rack[30 +1];
    int     ii, jj, len;
    short   wk_pos, wk_ch;
    FILE    *fp;
    struct stat  st;

    /* �t�@�C�����X�g�̃I�[�v�� */
    if(NULL == (fp = fopen(Temp_fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetFilelst", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "���ʈꎞ�t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", Temp_fpth, errno);
        fprintf(Dbg_fp,"���ʈꎞ�t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", Temp_fpth, errno);
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

        /* �t�@�C������胉�b�NID�A���b�NPOS�A�`���l��No.���擾 */
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

        /* �������ڂ��ǂ������� */
        if(FLrec[ii].chnum == sAppEnv.seisyk_ch)
            FLrec[ii].f_kessei = 2;
        else if(FLrec[ii].chnum == sAppEnv.nyubi_ch ||
                FLrec[ii].chnum == sAppEnv.youkets_ch ||
                FLrec[ii].chnum == sAppEnv.oudan_ch) {
            FLrec[ii].f_kessei = 1;
        }
        else  FLrec[ii].f_kessei = 0;


        ii++;
        if(ii >= FLARRY_MAX)  break;                  /* �z��MAX���ɒB�����Ƃ� */
    }
    fclose(fp);

    fprintf(Dbg_fp,"[%d]���̌��ʈꎞ�t�@�C����Ǎ���...\n", ii);
    if(ii == 0)  return;                              /* 0���̂Ƃ��͂����Ń��^�[�� */

    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "[%d]���̌��ʈꎞ�t�@�C����Ǎ���...", ii);
    FLrec_cnt = ii;


    /* �X�̌��ʏ��ɑ΂���˗����Ƃ̏ƍ����� */
    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].qcflg == 1)  continue;           /* Ctl���ʂ̓`�F�b�N�̑ΏۊO */
        if(FLrec[ii].sts != 0)    continue;           /* �ƍ����s�ς݃f�[�^�͑ΏۊO */

        /* �˗����Ƃ̏ƍ� */
        if(sFncMatchIrai(&FLrec[ii]) != RTN_OK)
            sFncSetFlstSts(&FLrec[ii], -1);           /* NG�̏ꍇ��sts��"-1"�ɐݒ� */
    }

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].sts > 0) {
            sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "���荀�ڑ����ς� fnm[%s] Rack[%s] Pos[%d] CH[%d] KM[%07d] Ckens[%d] ken[%s] CAL[%d] STS[%d]",
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
*  �� �� ���@�FsFncGetRackChPos()                                             *
*  �@�\�T�v�@�F�t�@�C��������̃��b�NID, POS, CH�ԍ��擾����                  *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
******************************************************************************/
{
    char    buff[51];
    int     mm, c_st, c_en, c_dl;

    if(strncmp(fnm,"QCK", 3) == 0) {                  /* �R���g���[�����ʂ̂Ƃ� */
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
    else {                                            /* ��ʌ��̂̂Ƃ� */
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
*  �� �� ���@�FsFncMatchIrai()                                                *
*  �@�\�T�v�@�F�˗��t�@�C���Ƃ̃`���l��No.�ƍ�����                            *
*  ���@�@�́@�F                                                               *
*  ��    ��      KEKFL_STR *flst                                              *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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

    /* �˗��t�@�C���̃T�[�` */
    for(ii = 0 ; ii < 2 ; ii++) {
        if(ii == 0)       strcpy(b_tmp, NEWFL_SUFFIX);
        else if(ii == 1)  strcpy(b_tmp, SKNIRAI_SUFFIX);

        sprintf(fnm,"%s%s_____%03d.%s", IRAI_PREFIX, flst->rackid, flst->pos, b_tmp);
        sprintf(fpth,"%s/%s", IRAINEW_PATH, fnm);
        fprintf(Dbg_fp,"�˗��t�@�C���T�[�`: [%s]...", fnm);

        if(stat(fpth, &st) == 0 && st.st_size > 0) {
            fprintf(Dbg_fp,"���݊m�F!!!\n");
            break;
        }
        else { fprintf(Dbg_fp,"����!!!\n"); }
    }

    /* �˗��t�@�C����������Ȃ��Ƃ� */
    if(ii >= 2) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�˗��t�@�C����������܂���BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�˗��t�@�C����������܂���BFile[%s] ERR[%d]\n", fpth, errno);

        /* #01 �G���[���͌��ʈꎞ�t�@�C����"end"Dir�Ƀ��l�[�� */
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, flst->rackid) != 0)  continue;
            if(FLrec[jj].pos != flst->pos)  continue;

            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "���ʈꎞ�t�@�C����err Dir�Ɉړ����܂��BFile[%s]", FLrec[jj].fname);
            fprintf(Dbg_fp,"���ʈꎞ�t�@�C����err Dir�Ɉړ����܂��BFile[%s]\n", FLrec[jj].fname);
            sprintf(rnmfpth,"%s/%s", KEKKAERR_PATH, FLrec[jj].fname);
            rename(FLrec[jj].path, rnmfpth);
        }

        return(RTN_NG);
    }

    /* �˗��t�@�C���I�[�v�� */
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);

        /* #01 �G���[���͌��ʈꎞ�t�@�C����"end"Dir�Ƀ��l�[�� */
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, flst->rackid) != 0)  continue;
            if(FLrec[jj].pos != flst->pos)  continue;

            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMatchIrai", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "���ʈꎞ�t�@�C����err Dir�Ɉړ����܂��BFile[%s]", FLrec[jj].fname);
            fprintf(Dbg_fp,"���ʈꎞ�t�@�C����err Dir�Ɉړ����܂��BFile[%s]\n", FLrec[jj].fname);
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

        /* �e�t�B�[���h�̏��� */
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
            else if(c_dl == 5) {                      /* �����O���[�v */
                memcpy(wk_kengrp, (fbuf+c_st), (c_en-c_st));  wk_kengrp[(c_en-c_st)] = '\0';
                sFncTrim(wk_kengrp);
            }
            else if(c_dl == 6) {                      /* ����(CH)�ݒ� */
                memcpy(wk_kmcode, (fbuf+c_st), (c_en-c_st));
                wk_kmcode[(c_en-c_st)] = '\0';
                sFncTrim(wk_kmcode);

                /* �`���l��No.���擾 */
                jj = 0;

                /* �������ڂɑ΂��鏈�� */
                if(strcmp(wk_kmcode, sAppEnv.nyubi_km) == 0)         wk_chnum = sAppEnv.nyubi_ch;
                else if(strcmp(wk_kmcode, sAppEnv.youkets_km) == 0)  wk_chnum = sAppEnv.youkets_ch;
                else if(strcmp(wk_kmcode, sAppEnv.oudan_km) == 0)    wk_chnum = sAppEnv.oudan_ch;
                else if(strcmp(wk_kmcode, sAppEnv.seisyk_km) == 0)   wk_chnum = sAppEnv.seisyk_ch;
                else {

                    /* ���̑��̍��ڂ̏��� */
                    for(jj = 0 ; jj < MstChanl_cnt ; jj++) {
                        if(MstChanl[jj].kmcode == atoi(wk_kmcode))
                            break;
                    }
                    if(jj >= MstChanl_cnt) {
                        fprintf(Dbg_fp,"�`���l���ԍ����}�X�^�Ɍ�����܂���B(�񑪒荀��) KM[%s]\n", wk_kmcode);

                        /* �v�Z���ڂ̏��𐶐� */
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

                    /* ���ʈꎞ�t�@�C���ƈ˗��t�@�C���̏ƍ� */
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
                        fprintf(Dbg_fp,"CH�s���� CH[%d] fbuf[%s]\n", wk_chnum, fbuf);
                    }
                }
            }
            else if(c_dl == 7) {                      /* ������ */
                memcpy(wk_kensacnt, (fbuf+c_st), (c_en-c_st));  wk_kensacnt[(c_en-c_st)] = '\0';
                sFncTrim(wk_kensacnt);
            }
            else if(c_dl == 11) {                     /* �����H���敪 */
                memcpy(wk_kensaphs, (fbuf+c_st), (c_en-c_st));  wk_kensaphs[(c_en-c_st)] = '\0';
                sFncTrim(wk_kensaphs);
            }
            else if(c_dl == 13) {                     /* �˗���No. */
                memcpy(wk_ino, (fbuf+c_st), (c_en-c_st));  wk_ino[(c_en-c_st)] = '\0';
                sFncTrim(wk_ino);
            }
            else if(c_dl == 16) {                     /* �{�݃R�[�h */
                memcpy(wk_usercode, (fbuf+c_st), (c_en-c_st));  wk_usercode[(c_en-c_st)] = '\0';
                sFncTrim(wk_usercode);
            }
            else if(c_dl == 27) {                     /* �ޗ��R�[�h */
                memcpy(wk_zaicode, (fbuf+c_st), (c_en-c_st));  wk_zaicode[(c_en-c_st)] = '\0';
                sFncTrim(wk_zaicode);
            }
            else if(c_dl == 44) {                     /* ���� */
                memcpy(wk_sex, (fbuf+c_st), (c_en-c_st));  wk_sex[(c_en-c_st)] = '\0';
                sFncTrim(wk_sex);
                break;
            }
        }

        /* �˗����̃`���l��No�ɊY�������Ƃ� */
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

        /* �˗����̃`���l��No�ɊY�����錋�ʈꎞ�t�@�C���������Ƃ� */
        sFncSetFlstSts(flst, -1);                     /* sts��"-1"�ɐݒ� */
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "���荀��(�`���l��)�̌��ʂ������Ă��܂���BRack[%s] Pos[%d]", flst->rackid, flst->pos);
        fprintf(Dbg_fp,"���荀��(�`���l��)�̌��ʂ������Ă��܂���BRack[%s] Pos[%d]\n", flst->rackid, flst->pos);
        break;
    }
    fclose(fp);

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
    return(RTN_OK);
}

/**/
static void sFncSetFlstSts(KEKFL_STR *flst, int val)
/******************************************************************************
*  �� �� ���@�FsFncSetFlstSts()                                               *
*  �@�\�T�v�@�F���ʈꎞ�t�@�C�����X�g�ւ̃X�e�[�^�X�ݒ菈��                   *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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
*  �� �� ���@�FsFncKekkaProc()                                                *
*  �@�\�T�v�@�F��ʌ��̑��茋�ʊ֘A����                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
******************************************************************************/
{
    int     ii;

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {

        if(FLrec[ii].qcflg == 1)  continue;           /* Ctl���ʂ͑ΏۊO */
        if(FLrec[ii].sts != 1)    continue;           /* ���荀�ڌ��ʂ������Ă��Ȃ��ꍇ���ΏۊO */

        /* ���茋�ʂ̓Ǎ��� */
        if(FLrec[ii].f_calc != 1) {
            if(sFncGetRsltTmp(&FLrec[ii]) != RTN_OK) {
                sFncSetFlstSts(&FLrec[ii], -1);       /* NG�̏ꍇ��sts��"-1"�ɐݒ� */
            }
        }

        /* �v�Z���ڏ��� */
        if(FLrec[ii].f_calc == 1) {
            sFncCalcKmProc(&FLrec[ii], ii);
        }
                                                      /* CH�}�X�^�A�v�ZKM�}�X�^�ɑ��݂��Ȃ��ꍇ */
        if(FLrec[ii].f_calc == 2)  { FLrec[ii].sts = 3;  continue; }


        /* ���͋@�G���[�`�F�b�N���� */
        strcpy(FLrec[ii].kisyak_sts," ");
        if(strncmp(FLrec[ii].errcd2,"  ", 2) != 0 || FLrec[ii].errcd2[0] != '\0')
            sFncMeErrorChk(&FLrec[ii]);


        /* �������ڂ͈ȉ��̃`�F�b�N�̑ΏۊO�Ƃ��� */
        if(FLrec[ii].f_kessei > 0)  { FLrec[ii].sts = 3;  continue; }


        /* ��߃`�F�b�N���� */
        sFncKisyakChk(&FLrec[ii]);


        /* �͈̓`�F�b�N���� */
        sFncRngChkProc(&FLrec[ii]);

        fprintf(Dbg_fp,"�ŏISTS MEerr[%s] MEPRC[%d] KISYAK[%s] CHK[%s]\n",
                FLrec[ii].meerrsts, FLrec[ii].meerrprc, FLrec[ii].kisyak_sts, FLrec[ii].cksts);
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----A */
    return;
}

/**/
static int sFncGetRsltTmp(KEKFL_STR *flst)
/******************************************************************************
*  �� �� ���@�FsFncGetRsltTmp()                                               *
*  �@�\�T�v�@�F���茋�ʈꎞ�t�@�C���̌��ʎ擾����                             *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    fbuf[101], buff[256];
    int     ii, len, c_st, c_en, c_dl, wk_place;
    double  wk_bias, dbl_kekka;
    FILE    *fp;

    if(NULL == (fp = fopen(flst->path,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetRsltTmp", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "���ʈꎞ�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", flst->fname, errno);
        fprintf(Dbg_fp,"���ʈꎞ�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", flst->fname, errno);

        return(RTN_NG);
    }

    if(NULL == fgets(fbuf, 101, fp)) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetRsltTmp", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "���ʈꎞ�t�@�C���̓Ǎ��݂Ɏ��s���܂����BFile[%s] ERR[%d]", flst->fname, errno);
        fprintf(Dbg_fp,"���ʈꎞ�t�@�C���̓Ǎ��݂Ɏ��s���܂����BFile[%s] ERR[%d]\n", flst->fname, errno);

        fclose(fp);
        return(RTN_NG);
    }
    fclose(fp);

    len = strlen(fbuf);
    if(fbuf[len-1] == '\n')  fbuf[len-1] = '\0';
    len = strlen(fbuf);

    /* ���ʃf�[�^�擾 */
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

    /* ���ڃ}�X�^���Y�����擾 */
    wk_place = 0;
    for(ii = 0 ; ii < MstKm_cnt ; ii++) {
        if(strcmp(MstKm[ii].kengrp, flst->kengrp) != 0)  continue;
        if(MstKm[ii].kmcode != flst->kmcode)             continue;

        wk_place = MstKm[ii].place;  break;
    }

    /* �������ڂ�Ctl���ʂ͊ۂ߂Ȃ� */
    if(flst->f_kessei > 0 || flst->qcflg == 1 || flst->raw[0] == '\0')
        return(RTN_OK);


    /* ���ڃ}�X�^�̏����_�����ɂ��ۂߏ��� */
    dbl_kekka = (double)atof(flst->raw);
    if(wk_place == 0)      wk_bias = (double)0.5;
    else if(wk_place > 0)  wk_bias = (double)(0.5/(pow(10, wk_place)));

    if(dbl_kekka > 0 ||                               /* ���ʒl��0�ȏォ���f */
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

    fprintf(Dbg_fp,"���ʒl�ۂߏ��� FNM[%s] RAW[%s] PLC[%d] KEK[%s]\n",
            flst->fname, flst->raw, wk_place, flst->kekka);

    return(RTN_OK);
}

/**/
static void sFncCalcKmProc(KEKFL_STR *flst, int idx)
/******************************************************************************
*  �� �� ���@�FsFncCalcKmProc()                                               *
*  �@�\�T�v�@�F�v�Z���ڂ̎Z�o����                                             *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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

    /* ���ڃ}�X�^���Y�����擾 */
    wk_place = 0;
    for(ii = 0 ; ii < MstKm_cnt ; ii++) {
        if(strcmp(MstKm[ii].kengrp, flst->kengrp) != 0)      continue;
        if(MstKm[ii].kmcode != flst->kmcode)                 continue;

        wk_place = MstKm[ii].place;  break;
    }
    fprintf(Dbg_fp,"�����_����[%d]\n",wk_place);


    /* �˗����̎擾 */
    sprintf(buff,"%07d", flst->kmcode);
    rtn = chkInfoRead(1, buff, flst->irfnm, pFldOD, pBuffOD);


    /* �v�Z���ڂ̌v�Z�����}�X�^���擾 */
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

        /* �v�Z�������s�֐��̌ďo�� */
        rtn = KeisanChk(wk_calc, flst, idx, pFldOD, &kekkabuf[0]);
        calkek[mch_ucd][mch_zai].kmcode = flst->kmcode;


        /* ���ڃ}�X�^�̏����_�����ɂ��ۂߏ��� */
        if(kekkabuf[0].flgRawNone != MY_FLG_ON) {     /* ���ʂ������Ă���ꍇ�̂� */
            if(wk_place == 0)      wk_bias = 0.5;
            else if(wk_place > 0)  wk_bias = (0.5/(pow(10, wk_place)));
            fprintf(Dbg_fp,"raw[%f]...bias[%f]\n",kekkabuf[0].raw,wk_bias);

            if(kekkabuf[0].raw > 0 ||                     /* ���ʒl��0�ȏォ���f */
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

        /* �v�Z���ڂ̍��@�ݒ� */
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
            "�v�Z���ڌ���(�Z�o��) UCD[%d] ZAI[%d] KEKKA[%s] FRML[%s]",
            mch_ucd, mch_zai, calkek[mch_ucd][mch_zai].kekka, MstCalc[ii].calc);
        fprintf(Dbg_fp,"�v�Z���ڌ���(�Z�o��) UCD[%d] ZAI[%d] KEKKA[%s] FRML[%s]\n",
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
        "�v�Z���ڌ��� KM[%d] UCD[%s] ZAI[%s] KEK[%s] ME[%d] CTL[%d]",
        flst->kmcode, flst->usercode, flst->zaicode, flst->kekka, flst->mecd, flst->ctlno);
    fprintf(Dbg_fp,"�v�Z���ڌ��� KM[%d] UCD[%s] ZAI[%s] KEK[%s] ME[%d] CTL[%d]\n",
            flst->kmcode, flst->usercode, flst->zaicode, flst->kekka, flst->mecd, flst->ctlno);

    return;
}

/**/
static void sFncMeErrorChk(KEKFL_STR *flst)
/******************************************************************************
*  �� �� ���@�FsFncMeErrorChk()                                               *
*  �@�\�T�v�@�F���͋@�G���[�`�F�b�N���� (�G���[�X�e�[�^�X10���܂őΉ�)        *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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

    /* �G���[�X�e�[�^�X�𕪊� */
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


    /* �}�X�^�Ƃ̏ƍ� */
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
        if(jj >= MstMeSts_cnt) {                      /* �G���[���}�X�^�ɖ����Ƃ��͖������� */
            strcpy(mests[ii].trcode,"?");
            mests[ii].procf = 3;
        }
        fprintf(Dbg_fp,"���͋@Err(��) FNM[%s] ER[%s] TR[%s] PRC[%d] SKN[%s] PRI[%d]\n",
                flst->fname, mests[ii].erbuf, mests[ii].trcode, mests[ii].procf, mests[ii].skncond, mests[ii].pri);
    }

    /* �D��x�̍���2�̃X�e�[�^�X�𒊏o */
    dsppri[0] = dsppri[1] = 0;
    dspidx[0] = dspidx[1] = 0;
    for(ii = 0 ; ii < dcnt ; ii++) {
        if(mests[ii].procf > 2)  continue;
        if(dsppri[0] == 0)  { dsppri[0] = mests[ii].pri;  dspidx[0] = ii;  continue; }

        if(dsppri[0] > mests[ii].pri) {               /* ��荂���D��x���������Ƃ� */
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
        "���͋@Err(����) FNM[%s] ER[%s] PRC[%d] SKN[%s]",
        flst->fname, flst->meerrsts, flst->meerrprc, mests[ii].skncond);
    fprintf(Dbg_fp,"���͋@Err(����) FNM[%s] ER[%s] PRC[%d] SKN[%s]\n",
            flst->fname, flst->meerrsts, flst->meerrprc, mests[ii].skncond);

    return;
}

/**/
static void sFncKisyakChk(KEKFL_STR *flst)
/******************************************************************************
*  �� �� ���@�FsFncKisyakChk()                                                *
*  �@�\�T�v�@�F��߃`�F�b�N����                                               *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
******************************************************************************/
{
    int     ii;
    short   f_bound;
    double  dbl_kekka;

    if(flst->qcflg == 1)  return;                     /* Ctl���ʂ͑ΏۊO */
    if(flst->sts != 1)    return;                     /* ���荀�ڂ������Ă��Ȃ��ꍇ���ΏۊO */

    /* ���ʒl�������ꍇ�̓��^�[�� */
    if(flst->kekka[0] == '\0') {
        flst->sts = 2;  return;
    }

    /* �Č��A�p��̏ꍇ�̓`�F�b�N���̂��s�v */
    if(flst->c_kensa > 1 && flst->kensaphs[0] == 'K') {
        flst->sts = 2;  return;
    }

    dbl_kekka = (double)atof(flst->kekka);
    flst->kisyak_err = 0;

    /* �Y�������ߔ{���}�X�^�Ƃ̏ƍ� */
    f_bound = 0;
    for(ii = 0 ; ii < MstKisyk_cnt ; ii++) {
        if(strcmp(MstKisyk[ii].kengrp, flst->kengrp) != 0)  continue;
        if(MstKisyk[ii].kmcode != flst->kmcode)             continue;

        f_bound = 0;

        /* �����l�͈͓̔��`�F�b�N */
        if(strncmp((MstKisyk[ii].kisyk_low +1),"999999999999",12) != 0) {
                                                      /* Double�^�̌덷���l��������r */
            if(dbl_kekka > MstKisyk[ii].dbksk_low ||
              (fabs(dbl_kekka - MstKisyk[ii].dbksk_low) <=
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstKisyk[ii].dbksk_low)))))) {

                f_bound = 1;
            }
        }
        else  f_bound = 1;

        /* ���l�`�F�b�N */
        if(strncmp((MstKisyk[ii].kisyk_hi +1),"999999999999",12) != 0) {
                                                      /* Double�^�̌덷���l��������r */
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
            "��߃`�F�b�N(����) FNM[%s] KM[%d] ER[%s]",
            flst->fname, flst->kmcode, flst->kisyak_sts);
        fprintf(Dbg_fp,"��߃`�F�b�N(����) FNM[%s] KM[%d] ER[%s]\n",
                        flst->fname, flst->kmcode, flst->kisyak_sts);
    }

    flst->sts = 2;
    return;
}

/**/
static void sFncRngChkProc(KEKFL_STR *flst)
/******************************************************************************
*  �� �� ���@�FsFncRngChkProc()                                               *
*  �@�\�T�v�@�F�͈̓`�F�b�N����                                               *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
******************************************************************************/
{
    char    chksts[2][2][2][3];
    int     ii;
    short   mch_ucd, mch_sex, mch_zai, f_mch;
    double  dbl_kekka;

    if(flst->qcflg == 1)  return;                     /* Ctl���ʂ͑ΏۊO */
    if(flst->sts != 2)    return;                     /* ���CHK���o�߂��Ă��Ȃ��ꍇ���ΏۊO */

    /* ���ʒl�������ꍇ�̏��� */
    if(flst->kekka[0] == '\0') {
        if(flst->meerrprc == 1 ||
          (flst->cksts[1] == ' ' && flst->meerrprc == 2)) {

            sFncKanrenChk(flst);                      /* ���͋@ERR�L��̏ꍇ�͊֘A����CHK�ďo�� */
        }
        flst->sts = 3;
        return;
    }


    dbl_kekka = (double)atof(flst->kekka);

    /* �Y������͈̓`�F�b�N�}�X�^�̎擾 */
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


        /* �Y����񂪂���Δ͈̓`�F�b�N���s */
        f_mch = 1;
        if(MstRange[ii].uplow == 1) {                 /* ���l�`�F�b�N */
            if(dbl_kekka > MstRange[ii].dbrng_hi &&
              (fabs(dbl_kekka - MstRange[ii].dbrng_hi) >
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstRange[ii].dbrng_hi)))))) {

                if(chksts[mch_ucd][mch_sex][mch_zai][0] == '\0') {
                    chksts[mch_ucd][mch_sex][mch_zai][0] = 'H'; /* �`�F�b�NSTS��ݒ� */
                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "�͈�CHK�G���[(High) McUCD[%d] McSEX[%d] McZAI[%d]", mch_ucd, mch_sex, mch_zai);
                    fprintf(Dbg_fp,"�͈�CHK�G���[(High) McUCD[%d] McSEX[%d] McZAI[%d]\n", mch_ucd, mch_sex, mch_zai);
                }
            }
        }
        else if(MstRange[ii].uplow == 2) {            /* ��l�`�F�b�N */
            if(dbl_kekka < MstRange[ii].dbrng_low &&
              (fabs(dbl_kekka - MstRange[ii].dbrng_low) >
              (DBL_EPSILON * fmax(1, fmax(fabs(dbl_kekka), fabs(MstRange[ii].dbrng_low)))))) {

                if(chksts[mch_ucd][mch_sex][mch_zai][0] == '\0') {
                    chksts[mch_ucd][mch_sex][mch_zai][0] = 'L'; /* �`�F�b�NSTS��ݒ� */
                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "�͈�CHK�G���[(Low) McUCD[%d] McSEX[%d] McZAI[%d]", mch_ucd, mch_sex, mch_zai);
                    fprintf(Dbg_fp,"�͈�CHK�G���[(Low) McUCD[%d] McSEX[%d] McZAI[%d]\n", mch_ucd, mch_sex, mch_zai);
                }
            }
        }
    }

    if(f_mch == 0) {
        fprintf(Dbg_fp,"�Y������͈̓`�F�b�N�}�X�^��������܂���B(���툵��)Rack[%s] KM[%d] USRCD[%s] SEX[%s]\n",
                flst->rackid, flst->kmcode, flst->usercode, flst->sex);
    }

    if(chksts[1][1][1][0] != '\0')       flst->cksts[0] = chksts[1][1][1][0];
    else if(chksts[1][0][1][0] != '\0')  flst->cksts[0] = chksts[1][0][1][0];
    else if(chksts[1][0][0][0] != '\0')  flst->cksts[0] = chksts[1][0][0][0];
    else if(chksts[0][0][1][0] != '\0')  flst->cksts[0] = chksts[0][0][1][0];
    else if(chksts[0][0][0][0] != '\0')  flst->cksts[0] = chksts[0][0][0][0];


    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
        "�͈̓`�F�b�N(����) FNM[%s] KM[%d] ER[%s]", flst->fname, flst->kmcode, flst->cksts);
    fprintf(Dbg_fp,"�͈̓`�F�b�N(����) FNM[%s] KM[%d] ER[%s]\n",
            flst->fname, flst->kmcode, flst->cksts);


    /* �֘A���ڃ`�F�b�N */
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
*  �� �� ���@�FsFncKanrenChk()                                                *
*  �@�\�T�v�@�F�֘A�`�F�b�N����                                               *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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

    /* �֘AERR�ŕ��͋@ERR��"�ƍ��̂�"�̍��ڂ�����ꍇ�ɂ́A */
    /* ���̕��͋@ERR��STS���֘A���ڂɐݒ肷�� */
    for(ii = 0 ; ii < pp ; ii++) {
        jj = idx[ii];
        fprintf(Dbg_fp,"[%s]--[%d]...KM[%d] MESTS[%s] CALC[%d]\n",
                __FILE__,__LINE__,FLrec[jj].kmcode,wk_mests,FLrec[jj].f_calc);
        if(FLrec[jj].f_calc == 1)                     /* �v�Z���ڂɑ΂���"�ƍ��̂�"ERR��STS��ݒ� */
            strcpy(FLrec[jj].meerrsts, wk_mests);
        FLrec[jj].meerrprc = 1;
    }

    return;
}

/**/
static void sFncMKSatKekka()
/******************************************************************************
*  �� �� ���@�FsFncMKSatKekka()                                               *
*  �@�\�T�v�@�F��ʌ��̕��̃T�e���C�g�����������ʃt�@�C���쐬����             *
*              (�����ɍČ��p����˗��t�@�C���쐬)                             *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
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

    /* ���ݓ������擾 */
    time(&tlsec);
    if(NULL != (tms = localtime(&tlsec))) {
        sprintf(tmbuf,"%d%02d%02d%02d%02d%02d", (tms->tm_year +1900),
            (tms->tm_mon +1), tms->tm_mday, tms->tm_hour, tms->tm_min, tms->tm_sec);
    }

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].qcflg == 1)  continue;           /* Ctl���ʂ͑ΏۊO */
        if(FLrec[ii].sts != 3)    continue;           /* �͈̓`�F�b�N�܂Œʂ��Ă��Ȃ��ꍇ���ΏۊO */

        /* �˗��t�@�C���I�[�v�� */
        for(jj = 0 ; jj < 2 ; jj++) {
            if(jj == 0)       strcpy(b_tmp, SKNIRAI_SUFFIX);
            else if(jj == 1)  strcpy(b_tmp, NEWFL_SUFFIX);

            sprintf(irfnm,"%s%s_____%03d.%s", IRAI_PREFIX, FLrec[ii].rackid, FLrec[ii].pos, b_tmp);
            sprintf(irfpth,"%s/%s", IRAINEW_PATH, irfnm);
            if(stat(irfpth, &st) == 0 && st.st_size > 0)  break;
        }
        if(jj >= 2) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMKSatKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "�˗��t�@�C����������܂���BFile[%s] ERR[%d]", irfpth, errno);
            fprintf(Dbg_fp,"�˗��t�@�C����������܂���BFile[%s] ERR[%d]\n", irfpth, errno);
            sFncSetFlstSts(&FLrec[ii], -1);  continue;
        }

        if(NULL == (fp_ir = fopen(irfpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMKSatKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "�˗��t�@�C���̃t�@�C���I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", irfpth, errno);
            fprintf(Dbg_fp,"�˗��t�@�C���t�@�C���I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", irfpth, errno);
            sFncSetFlstSts(&FLrec[ii], -1);  continue;
        }

        /* ���̒P�ʂ̃T�e���C�g�������ʃt�@�C���I�[�v�� */
        sprintf(kkfnm,"%s_____%03d_%s.tmp", FLrec[ii].rackid, FLrec[ii].pos, tmbuf);
        sprintf(kkfpth,"%s/%s", SATKEKKA_PATH, kkfnm);

        if(NULL == (fp_kk = fopen(kkfpth,"w"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMKSatKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "���ʃt�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", kkfpth, errno);
            fprintf(Dbg_fp,"���ʃt�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", kkfpth, errno);
            sFncSetFlstSts(&FLrec[ii], -1);  continue;

        }


        f_saiken = 0;
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, FLrec[ii].rackid) != 0)  continue; 
            if(FLrec[jj].pos != FLrec[ii].pos)                   continue;


            /* �T�e���C�g�������ʃt�@�C�������� */
            if(FLrec[jj].f_kessei != 2 && FLrec[jj].f_calc < 2) {
                rtn = sFncWriteSatKekka(fp_ir, fp_kk, &FLrec[jj]);
                if(rtn != RTN_OK)  { sFncSetFlstSts(&FLrec[jj], -1);  break; }
            }

            /* ���͋@�G���[�A�`�F�b�N�G���[�L��̏ꍇ�͍Č��˗��𐶐�(�p��̊�߈ȊO) */
            if(FLrec[jj].kensaphs[0] != 'K' && FLrec[jj].f_kessei == 0) {  /* �����Ŕ񌌐����ڂ̂ݑΏ� */
                if(FLrec[jj].meerrprc != 1) {         /* ���͋@Err��"�ƍ��̂�"�ȊO�̂Ƃ� */
                    if(FLrec[jj].meerrprc == 2 ||
                      (FLrec[jj].kisyak_sts[0] != 'M' &&
                      (FLrec[jj].kisyak_sts[0] != ' ' || strcmp(FLrec[jj].cksts,"  ") != 0))) {

                        rtn = sFncWriteSaiIrai(fp_ir, &FLrec[jj]);   /* �Č��˗��𐶐� */
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

        /* ���ʍ쐬�ςݏ��̍\����MAX���𒴂����Ƃ� */
        if(KekFL_cnt >= FLARRY_MAX) {
            fclose(fp_kk);  unlink(kkfpth);           /* ���ʃt�@�C���̍폜 */
            break;
        }

        /* Sat�p���ʃt�@�C�����̃��l�[������ */
        len = strlen(kkfnm);
        if(strncmp((kkfnm+len-3),"tmp", 3) == 0)  strcpy((kkfnm+len-3),"dat");
        sprintf(rnmfpth,"%s/%s", SATKEKKA_PATH, kkfnm);
        rename(kkfpth, rnmfpth);                      /* Sat�p���ʃt�@�C�������l�[�� */

        /* ���ʈꎞ�t�@�C���̃��l�[������(end���ֈړ�) */
        for(jj = 0 ; jj < FLrec_cnt ; jj++) {
            if(strcmp(FLrec[jj].rackid, FLrec[ii].rackid) != 0)  continue;
            if(FLrec[jj].pos != FLrec[ii].pos)                   continue;

            len = strlen(FLrec[jj].fname);
            if(strncmp((FLrec[jj].fname+len-3),"dat", 3) == 0)
                strcpy((FLrec[jj].fname+len-3),"end");
            sprintf(rnmfpth,"%s/%s", KEKKAEND_PATH, FLrec[jj].fname);

            mm = 0;
            if(stat(rnmfpth, &st) == 0) {             /* �t�@�C�������ɑ��݂���Ƃ� */
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

        sFncSetFlstSts(&FLrec[ii], 4);                /* �X�e�[�^�X��"4"�ɐݒ� */

        /* Line�p�������ʏo�͂̔z��ɃR�s�[ (���b�NID,POS�P��) */
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
*  �� �� ���@�FsFncWriteSatKekka()                                            *
*  �@�\�T�v�@�F�T�e���C�g�����������ʃt�@�C���쐬����                         *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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

            if(c_dl == 2)                             /* �����J�n���Ə������o�� */
                sprintf(wk_buff,"%.*s,", c_en, fbuf);

            else if(c_dl == 3)  c_bg = c_st;

            else if(c_dl == 6) {
                if(flst->f_kessei > 0) {              /* �������ڂɊւ��鏈�� */
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
                fprintf(kkfp,"%s", wk_buff);          /* ��Őݒ肵�������J�n���Ə��������o�� */
            }

            else if(c_dl == 24) {                     /* No.28�̕��͋@SEQ�܂ŏo�� */
                fprintf(kkfp,"%.*s,%s,%02d,%02d0000,%d,%s,", (c_en-c_bg), (fbuf+c_bg), ME_KUBUN,
                        flst->mecd, flst->mecd, flst->meseqno, flst->meerrsts);
                fprintf(kkfp,"%s,%03d,R,", flst->rstime, flst->chnum);
            }
            else if(c_dl == 27)  c_bg = c_st;
            else if(c_dl == 40) {                     /* No.27�̍ޗ��R�[�h����No.40�ً̋}�˗����b�gNo.�܂ŏo�� */
                fprintf(kkfp,"%.*s,", (c_en-c_bg), (fbuf+c_bg));
                fprintf(kkfp," , , ,%8s,,,,,%s,,,,3,0,0,0,0, , , , , , ,,,,,,,%d,",
                        flst->raw, flst->kekka, flst->ctlno);
            }
            else if(c_dl == 55)  c_bg = c_st;
            else if(c_dl == 56) {                     /* ���ʂ�No.77�̌���SEQ�`No.94�����t���O���o�� */
                if(flst->f_kessei > 0)               strcpy(wk_buff,"H"); /* �������ڂ�"H"�Œ� */
                else if(flst->kisyak_sts[0] == 'M')  strcpy(wk_buff,"R"); /* ��ߍČ�(�p��)�̏ꍇ */
                else if(flst->meerrprc == 1)         strcpy(wk_buff,"R"); /* "�ƍ��̂�"�̕��͋@ERR�̏ꍇ */
                else if(flst->meerrprc == 2 ||
                        strcmp(flst->cksts,"  ") != 0 || flst->kisyak_sts[0] != ' ') {
                      strcpy(wk_buff,"A");            /* ���̑������Č��̏ꍇ */
                }
                else  strcpy(wk_buff,"X");            /* ���펞 */

                fprintf(kkfp,"%.*s,,,,,,,,,,,,1,1,,1,%s,", (c_en-c_bg), (fbuf+c_bg), wk_buff);
                /* ���͋@����ł͕␳�t���O��"1"�ɐݒ� */
                /* �����č̗p�t���O�A���ʗD��t���O��"1"�Œ�ɐݒ� */


                if(flst->cksts[0] == 'H')       strcpy(buff,"3,0,");
                else if(flst->cksts[0] == 'L')  strcpy(buff,"4,0,");
                else                            strcpy(buff,"1,0,");

                if(flst->cksts[1] != ' ')       strcat(buff,"2,0,0,0,0,0,0,0,");
                else                            strcat(buff,"1,0,0,0,0,0,0,0,");
                if(flst->kisyak_err == 1)       strcat(buff,"2,0,0,0,0,");
                else                            strcat(buff,"1,0,0,0,0,");
                if(flst->meerrsts[0] != ' ')    strcat(buff,"2,0,0,0,0,,,,");  /* �\���t���O�ݒ� */
                else                            strcat(buff,"1,0,0,0,0,,,,");

                time(&tlsec);
                if(NULL != (tms = localtime(&tlsec))) {
                    fprintf(kkfp,"%s%d-%02d-%02d %02d:%02d:%02d\n",
                        buff, (tms->tm_year +1900), (tms->tm_mon +1), tms->tm_mday,
                        tms->tm_hour, tms->tm_min, tms->tm_sec);
                }
                fflush(kkfp);

                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "�T�e���C�g�������ʃt�@�C���o�� Rack[%s] POS[%d] CH[%d] KEK[%s]",
                    flst->rackid, flst->pos, flst->chnum, flst->kekka);
                fprintf(Dbg_fp,"Sat�������ʃt�@�C���o�� Rack[%s] POS[%d] CH[%d] KEK[%s]\n",
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
*  �� �� ���@�FsFncWriteSaiIrai()                                             *
*  �@�\�T�v�@�F�Č��p����˗��t�@�C���쐬����                                 *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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
            "�Č��p�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        fprintf(Dbg_fp,"�Č��p�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
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

            /* �����̈˗������擾���ĕҏW */
            if(c_dl == 6) {
                wk_kmcode = atoi(buff);
                if(wk_kmcode != flst->kmcode)  break;
            }
            else if(c_dl == 7) {
                wk_kenkaisu = (short)atoi(buff) +1;
                sprintf(b_tmp,"%d", wk_kenkaisu);
                fbuf[c_st] = b_tmp[0];                /* �����񐔂�ݒ� */
            }
            else if(c_dl == 11)  fbuf[c_st] = 'K';    /* �����H���敪��ݒ� */
            else if(c_dl == 37) {
                if(flst->kisyak_sts[0] != ' ')
                    fbuf[c_st] = flst->kisyak_sts[0]; /* ��ߏ�����ݒ� */
                break;
            }
        }
        if(wk_kmcode != flst->kmcode)  continue;


        /* �Č��˗����̃t�@�C���o�� */
        fprintf(sknfp,"%s", fbuf);
        flst->f_saiken = 1;                           /* �Č����{�t���O�ݒ� */


        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�Č��˗����̃t�@�C���o�� Rack[%s] POS[%d] CH[%d] MEerr[%s] MEPRC[%d] KISYAK[%s] CHK[%s]",
            flst->rackid, flst->pos, flst->chnum, flst->meerrsts, flst->meerrprc, flst->kisyak_sts, flst->cksts);
        fprintf(Dbg_fp,"�Č��˗����̃t�@�C���o�� Rack[%s] POS[%d] CH[%d] MEerr[%s] MEPRC[%d] KISYAK[%s] CHK[%s]\n",
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
*  �� �� ���@�FsFncCtlKekkaProc()                                             *
*  �@�\�T�v�@�F�T�e���C�g�����R���g���[�����ʃt�@�C���쐬����                 *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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

    /* ���ݓ������擾 */
    time(&tlsec);
    if(NULL != (tms = localtime(&tlsec))) {
        sprintf(tmbuf,"%d%02d%02d%02d%02d%02d", (tms->tm_year +1900),
            (tms->tm_mon +1), tms->tm_mday, tms->tm_hour, tms->tm_min, tms->tm_sec);
    }

    for(ii = 0 ; ii < FLrec_cnt ; ii++) {
        if(FLrec[ii].qcflg != 1)  continue;           /* Ctl���ʈȊO�͑ΏۊO */
        if(FLrec[ii].sts > 0)     continue;           /* ���Ɍ��ʃt�@�C���쐬�ς݂̂��̂͑ΏۊO */

        /* ���茋�ʂ̓Ǎ��� */
        if(sFncGetRsltTmp(&FLrec[ii]) != RTN_OK)
            sFncSetFlstSts(&FLrec[ii], 10);       /* NG�̏ꍇ��sts��"10"�ɐݒ� */

        /* �T�e���C�g����Ctl���ʃt�@�C���I�[�v�� */
        sprintf(qkfnm,"CT_%.10s_%s%d.tmp", (FLrec[ii].fname +5), tmbuf, FLrec[ii].chnum);
        sprintf(qkfpth,"%s/%s", SATKEKKA_PATH, qkfnm);

        if(NULL == (fp_qk = fopen(qkfpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncCtlKekkaProc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Ctl���ʃt�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", qkfpth, errno);
            fprintf(Dbg_fp,"Ctl���ʃt�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", qkfpth, errno);
            continue;

        }

        /* Ctl�}�X�^�̊Y�����T�[�` */
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
                "Ctl�}�X�^�ɐݒ肳��Ă��܂���BFNM[%s] CH[%d] CTLKND[%.3s]", FLrec[ii].fname, FLrec[ii].chnum, (FLrec[ii].kenid +2));
            fprintf(Dbg_fp,"Ctl�}�X�^�ɐݒ肳��Ă��܂���BFNM[%s] CH[%d] CTLKND[%.3s]\n",
                               FLrec[ii].fname, FLrec[ii].chnum, (FLrec[ii].kenid +2));
            continue;
        }

        /* SD�l�̎Z�o */
        wk_sd = (double)atof(FLrec[ii].kekka);
fprintf(Dbg_fp,"QCkek[%f]...", wk_sd);
        wk_sd = (wk_sd - wk_valuex) / wk_mstsd;
        wk_dbl = wk_sd-(int)(wk_sd/1);
        sprintf(buf1,"%f", (wk_sd-(int)(wk_sd/1)));
fprintf(Dbg_fp,"SDdbl[%f] RST[%f]\n", wk_sd, wk_dbl);

        if(fabs(wk_dbl -(double)0) <=                 /* �����_�ȉ���0�̂Ƃ� */
           (DBL_EPSILON * fmax(1, fmax(fabs(wk_dbl), fabs((double)0))))) {
            sprintf(buff,"%d", (int)(wk_sd/1));
        }
        else if(strncmp(buf1,"0.000000", 8) == 0)     /* �����_�ȉ���0�̂Ƃ�(��̏����ɊY�����Ȃ��Ƃ�) */
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


        /* �`���l��No.�ɊY�����鍀�ڃR�[�h���̃��R�[�h�o�� */
        for(jj = 0 ; jj < MstChanl_cnt ; jj++) {
            if(MstChanl[jj].chnum != FLrec[ii].chnum) /* �`���l���}�X�^�Ƃ̃`���l��No.�ƍ� */
                continue;

            /* ���ʃ��R�[�h�o�� */
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


        /* Sat�p���ʃt�@�C���̃��l�[������ */
        len = strlen(qkfnm);
        strcpy((qkfnm+len-4),".dat");
        sprintf(rnmfpth,"%s/%s", SATKEKKA_PATH, qkfnm);

        if(stat(rnmfpth, &st) == 0) {                 /* �t�@�C������������Ƃ� */
            sprintf(cmd,"/usr/bin/cp -p %s %s", qkfpth, rnmfpth);
            system(cmd);
            unlink(qkfpth);
        }
        else  rename(qkfpth, rnmfpth);

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�T�e���C�g����Ctl���ʃt�@�C���o�� FNM[%s] CTLSBT[%.3s] CH[%d] CTLNO[%d] KEK[%s] SD[%s]",
            qkfnm, (FLrec[ii].kenid +2), FLrec[ii].chnum, FLrec[ii].ctlno, FLrec[ii].kekka, buff);
        fprintf(Dbg_fp,"Sat����Ctl���ʃt�@�C���o�� FNM[%s] CTLSBT[%.3s] CH[%d] CTLNO[%d] KEK[%s] SD[%s]\n",
                qkfnm, (FLrec[ii].kenid +2), FLrec[ii].chnum, FLrec[ii].ctlno, FLrec[ii].kekka, buff);


        /* Ctl���ʈꎞ�t�@�C���̃��l�[�� */
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
*  �� �� ���@�FsFncMkLineKekka()                                              *
*  �@�\�T�v�@�FLine���ւ̌������ʏ��쐬����                                 *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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
        if(KekFL[ii].sts != 4)  continue;             /* ���ɃX�e�[�^�X�ω��������̂͑ΏۊO */

        /* �Č��p�̈˗��t�@�C���Q�Ƃ��ǂ����̔��� */
        f_sknirai = 0;
        len = strlen(KekFL[ii].irfnm);
        if(strncmp((KekFL[ii].irfnm+len-6),"dat_01",6) == 0)
            f_sknirai = 1;


        /* �����Č����ʂ̏ꍇ�̓��b�N���̍Č����������Ă��邩�m�F */
        /* (�āX���̏ꍇ�͑ΏۊO) */
        if(KekFL[ii].c_kensa > 1 && KekFL[ii].kensaphs[0] == 'K' && f_sknirai == 1) {

            sprintf(cmd,"/usr/bin/ls -t %s/%s*end* > %s 2>&1", LANEKEKEND_PATH, KekFL[ii].rackid, Temp_fpth);
            system(cmd);

            if(NULL == (fp = fopen(Temp_fpth,"r"))) {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "Line�p�������ʃt�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", Temp_fpth, errno);
                fprintf(Dbg_fp,"Line�p�������ʃt�@�C���I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", Temp_fpth, errno);
                continue;
            }

            if(NULL == fgets(fbuf, 256, fp)) {        /* �擪�̍ŐV�t�@�C�����擾 */
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetRsltTmp", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "Line�p�������ʃt�@�C�����X�g�̓Ǎ��݂Ɏ��s���܂����BFile[%s] ERR[%d]", Temp_fpth, errno);
                fprintf(Dbg_fp,"Line�p�������ʃt�@�C���̓Ǎ��݂Ɏ��s���܂����BFile[%s] ERR[%d]\n", Temp_fpth, errno);

                fclose(fp);
                continue;
            }
            fclose(fp);

            len = strlen(fbuf);
            if(fbuf[len-1] == '\n')  { fbuf[len-1] = '\0';  len = strlen(fbuf); }
            if(NULL != strstr(fbuf,"/usr/bin/ls"))  continue;

            if(NULL == (fp = fopen(fbuf,"r"))) {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "Line�p�������ʃt�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fbuf, errno);
                fprintf(Dbg_fp,"Line�p�������ʃt�@�C���I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fbuf, errno);
                continue;
            }

            for( ; ; ) {
                if(NULL == fgets(buff, 101, fp))  break;
                if(buff[0] == '\n' || buff[0] == ' ' || buff[0] == '\0')
                    continue;
                if(buff[14] != '1')  continue;        /* �Č����ȊO�͑ΏۊO */

                sprintf(wk_pos,"%.3s", buff);
                f_mch = 0;
                for(jj = 0 ; jj < KekFL_cnt ; jj++) {
                    if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;

                    KekFL[jj].sts = 6;
                    if(KekFL[jj].pos == atoi(wk_pos)) {
                        f_mch = 1;  break;
                    }
                }
                if(f_mch == 0)  break;                /* �Č�POS�̌��ʂ�����M�̂Ƃ� */
            }
            fclose(fp);
            if(f_mch == 0) {
                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                    "���b�N�̌��̌��ʂ������Ă��܂���BRackID[%s] POS[%.3s]", KekFL[ii].rackid, wk_pos);
                fprintf(Dbg_fp,"���b�N�̌��̌��ʂ������Ă��܂���BRackID[%s] POS[%.3s]\n", KekFL[ii].rackid, wk_pos);
                for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                    if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                    KekFL[mm].sts = 10;               /* ���b�N���������Ă��Ȃ��ꍇ��"10"��ݒ� */
                }
                continue;
            }

            /* �Č����ʂ�1���b�N���������Ƃ� */
            for(jj = 0 ; jj < KekFL_cnt ; jj++) {
                if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;
                KekFL[jj].sts = 7;
            }

            continue;                                 /* �����Č����͂����Ŗ߂� */
        }


        /* �ȍ~�͏����A�āX�����̏ꍇ�̏��� */
        sprintf(fpth,"%s/%s.end", LANEIRAI_PATH, KekFL[ii].rackid);
        if(NULL == (fp_ir = fopen(fpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line�p�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line�p�˗��t�@�C���I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
            continue;
        }

        saiken_flg = 0;
        for(jj = 0 ; ; jj++) {
            if(NULL == fgets(fbuf, 256, fp_ir))  break;
            if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
                continue;
            len = strlen(fbuf);
            if(len < 10)  continue;

            /* �w�b�_���̃��C��No.�`�F�b�N */
            if(jj == 0) {
                sprintf(rcvudate,"%.8s", fbuf);       /* Line�˗��̎�t���t�擾 */

                sprintf(buff,"%d", sAppEnv.lineno);
                if(isdigit(fbuf[len-3]) && fbuf[len-3] != buff[0]) {
                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "Line�p�˗��t�@�C������LineNo.�s��v RackID[%s]", KekFL[ii].rackid);
                    fprintf(Dbg_fp,"Line�p�˗��t�@�C������LineNo.�s��v RackID[%s]\n", KekFL[ii].rackid);
                    break;                            /* �s��v�̏ꍇ��break */
                }
                continue;
            }

            f_mch = 0;
            for(mm = 0 ; mm < KekFL_cnt ; mm++) {     /* RackPos����v���邩�ǂ����`�F�b�N */
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
                    "���b�N�̌��̌��ʂ������Ă��܂���BRackID[%s] POS[%.3s]", KekFL[ii].rackid, buff);
                fprintf(Dbg_fp,"���b�N�̌��̌��ʂ������Ă��܂���BRackID[%s] POS[%.3s]\n", KekFL[ii].rackid, buff);
                for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                    if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                    KekFL[mm].sts = 10;               /* ���b�N���������Ă��Ȃ��ꍇ��"10"��ݒ� */
                }
                break;
            }
        }
        fclose(fp_ir);

        if(f_mch == 0)  continue;


        /* �āX���A�p��Č��̏ꍇ�ALine�����������ʂ͍쐬�ς݂Ƃ��Ĉ��� */
        /* ("sFncMkReSknKekka()"�̊֐��ɂĕʓr�쐬����) */
        if(KekFL[ii].kensaphs[0] == 'K' && f_sknirai == 0) {
            for(jj = 0 ; jj < KekFL_cnt ; jj++) {
                if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;
                KekFL[jj].sts = 5;
            }
            continue;
        }


        /* Line������̌��ʗv���t�@�C���L���m�F */
        fprintf(Dbg_fp,"Line������̌��ʗv���t�@�C���T�[�`...Rack[%s]...", KekFL[ii].rackid);
        sprintf(fpth,"%s/%s.dat", LANERSREQNEW_PATH, KekFL[ii].rackid);
        if(stat(fpth, &st) != 0) {
            for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;

                KekFL[mm].sts = 10;
            }
            fprintf(Dbg_fp,"����\n");
            continue;                                 /* �t�@�C���������ꍇ�̓��[�v�擪�ɖ߂� */
        }

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "Line������̌��ʗv���t�@�C�����o FNM[%s.dat]", KekFL[ii].rackid);
        fprintf(Dbg_fp,"���݊m�F\n");
        sprintf(rnmfpth,"%s/%s.end", LANERSREQEND_PATH, KekFL[ii].rackid);
        rename(fpth, rnmfpth);
        

        /* Line�����������ʃt�@�C���쐬 */
        sprintf(fpth,"%s/%s_%d.tmp", LANEKEKKA_PATH, KekFL[ii].rackid, saiken_flg);
        if(NULL == (fp_kk = fopen(fpth,"w"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkLineKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line�p�������ʃt�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line�p�������ʃt�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);

            for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                KekFL[mm].sts = 10;                   /* ���̏ꍇ��"10"��ݒ� */
            }
            continue;
        }

        /* �w�b�_�o�� */
        fprintf(fp_kk,"%s%s%d%c%c", rcvudate, KekFL[ii].rackid, sAppEnv.lineno, 0x0d, 0x0a);

        /* �f�[�^���o�� */
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


        /* Line�p�������ʃt�@�C�����̃��l�[�� (.tmp -> .dat) */
        sprintf(rnmfpth,"%s/%s_%d.dat", LANEKEKKA_PATH, KekFL[ii].rackid, saiken_flg);
        rename(fpth, rnmfpth);

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "Line�p�������ʃt�@�C���̏o�� FNM[%s_%d.dat]", KekFL[ii].rackid, saiken_flg);
        fprintf(Dbg_fp,"Line�p�������ʃt�@�C���̏o�� FNM[%s_%d.dat]\n", KekFL[ii].rackid, saiken_flg);

        /* �Č������A�āX���A�p��Č��̏ꍇ�͂����Ń��[�v�擪�ɖ߂� */
        if(saiken_flg == 0 ||
          (KekFL[ii].c_kensa > 1 && KekFL[ii].kensaphs[0] == 'K')) {
            continue;
        }


        /* �Č��L��̏ꍇ�͈˗��t�@�C�������l�[�� */
        /* (�Č��̖⍇�����ɍČ��ȊO�̌��̂̑���˗�����΂Ȃ��悤�ɂ���) */
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
            "�Č������̂��ߏ����˗������l�[�� Rack[%s]", KekFL[ii].rackid);
        fprintf(Dbg_fp,"�Č������̂��ߏ����˗������l�[�� Rack[%s]\n", KekFL[ii].rackid);
    }


    /* �������������\���̂���폜 */
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
*  �� �� ���@�FsFncRnmStray()                                                 *
*  �@�\�T�v�@�FLine�p���[�g���[��񃊃l�[���y�ш˗���񃊃l�[������           *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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

    /* ���ݓ������擾 */
    time(&tlsec);
    if(NULL != (tms = localtime(&tlsec))) {
        sprintf(tmbuf,"%d%02d%02d%02d%02d%02d", (tms->tm_year +1900),
            (tms->tm_mon +1), tms->tm_mday, tms->tm_hour, tms->tm_min, tms->tm_sec);
    }

    /* �ꎞ�t�@�C�����̐��� */
    sprintf(tmpth,"/tmp/MD102_%d_%s", getpid(), tmbuf);


    /* �t�@�C�����X�g�̃I�[�v�� */
    if(NULL == (fp = fopen(Temp_fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "Line�����[�g���[�t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", Temp_fpth, errno);
        fprintf(Dbg_fp,"Line�����[�g���[�t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", Temp_fpth, errno);
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


        /* Line�����[�g���[�t�@�C���̃��l�[������ */
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
              "[%d]����Line�����[�g���[�t�@�C�������l�[�����܂����B", nn);
        fprintf(Dbg_fp,"[%d]����Line�����[�g���[�t�@�C�������l�[��\n", nn);
    }

    if(KekFL_cnt <= 0)  return;


    /* �ȍ~�͍Č����b�N�ɑ΂��鏈�� */
    for(ii = 0 ; ii < KekFL_cnt ; ii++) {
        if(KekFL[ii].sts != 7)  continue;             /* �Č����ʎ�M�ς݈ȊO�͑ΏۊO */

/************************
        if(NULL == (dp = opendir(LANESTRYEND_PATH))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "���[�g���C���i�[Dir�̃I�[�v���Ɏ��s���܂����BDir[%s] ERR[%d]", LANESTRYEND_PATH, errno);
            if(DbgFlg)  printf("���[�g���C���i�[Dir�̃I�[�v���Ɏ��s���܂����BDir[%s] ERR[%d]\n", LANESTRYEND_PATH, errno);
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


        /* �Y�����b�N���������ꍇ�̈˗���񃊃l�[������ */
        for(jj = 0 ; jj < 2 ; jj++) {
            if(jj == 0)
                  sprintf(cmd,"/usr/bin/ls %s/*%s*tmp > %s 2>&1", IRAINEW_PATH, KekFL[ii].rackid, tmpth);
            else  sprintf(cmd,"/usr/bin/ls %s/*%s*dat_01 > %s 2>&1", IRAINEW_PATH, KekFL[ii].rackid, tmpth);
            system(cmd);

            /* �t�@�C�����X�g�̃I�[�v�� */
            if(NULL == (irifp = fopen(tmpth,"r"))) {
                sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                       "�Č��Ώۈ˗��t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", tmpth, errno);
                fprintf(Dbg_fp,"�Č��Ώۈ˗��t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", tmpth, errno);
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

                /* �˗��t�@�C���̃��l�[������ */
                if(rename(fpth, rnmfpth) < 0) {
                    if(jj == 0) {
                        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRnmStray", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "�Č��˗��t�@�C���̃��l�[���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
                        fprintf(Dbg_fp,"�Č��˗��t�@�C���̃��l�[���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);

                        for(mm = 0 ; mm < KekFL_cnt ; mm++) {
                            if(strcmp(KekFL[mm].rackid, KekFL[ii].rackid) != 0)  continue;
                            KekFL[mm].sts = 10;       /* ���̏ꍇ��"10"��ݒ� */
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
                      "�Č��Ώۂ̈˗��t�@�C��(������)�����l�[�����܂����BRackID[%s]", KekFL[ii].rackid);
                fprintf(Dbg_fp,"�Č��Ώۂ̈˗��t�@�C��(������)�����l�[���BRackID[%s]\n", KekFL[ii].rackid);
            }
            else {
                sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                      "�Č��˗��t�@�C����end���Ƀ��l�[�����܂����B�BRackID[%s]", KekFL[ii].rackid);
                fprintf(Dbg_fp,"�Č��˗��t�@�C����end���Ƀ��l�[���BRackID[%s]\n", KekFL[ii].rackid);
            }
        }

        for(jj = 0 ; jj < KekFL_cnt ; jj++) {
            if(strcmp(KekFL[jj].rackid, KekFL[ii].rackid) != 0)  continue;
            KekFL[jj].sts = 8;
        }
    }


    /* �������������\���̂���폜 */
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
*  �� �� ���@�FsFncMkReSknKekka()                                             *
*  �@�\�T�v�@�F�āX���˗��̌��ʗv��(Line�������)�t�@�C�����o�A               *
*              Line�����������ʃt�@�C���쐬����                               *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
* �@�@�@�@�@�@�@                                                              *
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


    /* �t�@�C�����X�g�̃I�[�v�� */
    if(NULL == (fp = fopen(Temp_fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "Line�����ʗv���t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", Temp_fpth, errno);
        fprintf(Dbg_fp,"Line�����ʗv���t�@�C�����X�g�̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", Temp_fpth, errno);
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

        /* �Y�����b�N�̈˗��t�@�C�����݊m�F */
        sprintf(wk_rack,"%.5s", fnm);
        for(ii = 1 ; ii <= 5 ; ii++) {
            sprintf(fnm,"%s%s_____%03d.dat", IRAI_PREFIX, wk_rack, ii);   /* �����̃t�@�C�����ŃT�[�` */
            sprintf(fpth,"%s/%s", IRAINEW_PATH, fnm);
            if(stat(fpth, &st) != 0)  continue;

            break;
        }
        if(ii > 5)  continue;


        /* �˗��t�@�C���̃I�[�v�� */
        if(NULL == (irifp = fopen(fpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
            continue;
        }

        f_saisai = 0;
        for( ; ; ) {
            if(NULL == fgets(iribuf, 512, irifp))  break;
            if(iribuf[0] == '\n' || iribuf[0] == ' ' || iribuf[0] == '#')
                continue;
            if(strlen(iribuf) < 50)  continue;

            /* �e�t�B�[���h�̏��� */
            c_st = c_en = c_dl = 0;
            for(ii = 0 ; ii < strlen(iribuf) ; ii++) {
                if(iribuf[ii] == ',')  {
                    if(c_en > 0)  c_st = c_en +1;
                    c_en = ii;  c_dl++;
                }
                else  continue;

                memcpy(buff, (iribuf+c_st), (c_en-c_st));  buff[(c_en-c_st)] = '\0';
                sFncTrim(buff);

                if(c_dl == 11) {                      /* �����H���敪 */
                    if(buff[0] == 'K')  f_saisai = 1;
                    break;
                }
            }
            break;                                    /* 1���R�[�h�݂̂Ŕ��� */
        }
        fclose(irifp);
        if(f_saisai == 0)  continue;                  /* �āX���A�p��Č��ȊO�̏ꍇ�͑ΏۊO */


        /* �āX���A�p��Č��̌��ʗv���t�@�C�����o */
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "�āX���A�p��Č��̌��ʗv���t�@�C�����o Rack[%s]", wk_rack);
        fprintf(Dbg_fp,"�āX���A�p��Č��̌��ʗv���t�@�C�����o Rack[%s]\n", wk_rack);

        /* �ȍ~�͍āX���A�p��Č�����Line�����������ʃt�@�C���쐬���� */
        sprintf(fpth,"%s/%s.end", LANEIRAI_PATH, wk_rack);
        if(NULL == (irifp = fopen(fpth,"r"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line�p�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line�p�˗��t�@�C���I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
            continue;
        }

        /* Line�����������ʃt�@�C���I�[�v�� */
        sprintf(fpth,"%s/%s_0.tmp", LANEKEKKA_PATH, wk_rack);
        if(NULL == (kekfp = fopen(fpth,"w"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncMkReSknKekka", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Line�p�������ʃt�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
            fprintf(Dbg_fp,"Line�p�������ʃt�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
            fclose(irifp);
            continue;
        }

        for(ii = 0 ; ; ii++) {
            if(NULL == fgets(iribuf, 512, irifp))  break;
            if(iribuf[0] == '\n' || iribuf[0] == ' ' || iribuf[0] == '#')
                continue;
            len = strlen(iribuf);
            if(len < 10)  continue;

            /* �w�b�_���̃��C��No.�`�F�b�N */
            if(ii == 0) {
                sprintf(buff,"%d", sAppEnv.lineno);
                if(isdigit(iribuf[len-3]) && iribuf[len-3] != buff[0]) {
                    fprintf(Dbg_fp,"Line�p�˗��t�@�C������LineNo.�s��v RackID[%s]\n", wk_rack);
                    break;                            /* �s��v�̏ꍇ��break */
                }
                fprintf(kekfp,"%s", iribuf);          /* CR,LF�R�[�h���ꏏ�ɏo�� */
                continue;
            }

            /* �f�[�^���o�� */
            iribuf[len-2] = '\0';
            fprintf(kekfp,"%s0%c%c", iribuf, 0x0d, 0x0a);
        }
        fclose(irifp);
        fclose(kekfp);
        if(ii == 0)  { unlink(fpth);  continue; }

        /* Line�p�������ʃt�@�C�����̃��l�[�� (.tmp -> .dat) */
        sprintf(rnmfpth,"%s/%s_0.dat", LANEKEKKA_PATH, wk_rack);
        rename(fpth, rnmfpth);

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "Line�p�������ʃt�@�C��(�āX���A�p��Č���)�̏o�� FNM[%s_0.dat]", wk_rack);
        fprintf(Dbg_fp,"Line�p�������ʃt�@�C��(�āX���A�p��Č���)�̏o�� FNM[%s_0.dat]\n", wk_rack);


        /* Line�����ʗv���t�@�C���̃��l�[�� */
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
/*  �� �� ���@�FsFncTrim()                                                    */
/*  �@�\�T�v�@�F������O��̃X�y�[�X���폜����                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *      �ҏW������                                        */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
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
/*  �� �� ���@�FsFncShmCrt()                                                  */
/*  �@�\�T�v�@�F���L����������                                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *     �v���O�������\����                      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK     : ����                                            */
/* �@�@�@�@�@�@�@RTN_NG     : ���s                                            */
/******************************************************************************/
{
    int     *shmData ;

    //  �擾
    pAppEnv->shm_Id = shmget(pAppEnv->shm_Key, sizeof(int), (0666 | IPC_CREAT));
    if ( pAppEnv->shm_Id < 0 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̑���Ɏ��s���܂���[shmget]" ) ;
        fprintf(Dbg_fp,"���L�������̑���Ɏ��s���܂���[shmget]\n");
        return ( RTN_NG ) ;
    }

    //  �A�^�b�`
    shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃A�^�b�`�Ɏ��s���܂���" ) ;
        fprintf(Dbg_fp,"���L�������̃A�^�b�`�Ɏ��s���܂���\n");
        return ( RTN_NG ) ;
    }

    //  �l�ݒ�
    *shmData = 0 ;

    //  �f�^�b�`
    if ( shmdt ( shmData ) == -1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃f�^�b�`�Ɏ��s���܂���" ) ;
        fprintf(Dbg_fp,"���L�������̃f�^�b�`�Ɏ��s���܂���\n");
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static int sFncShmGet(struct appEnv *pAppEnv, int *pshmData)
/*****************************************************************************
*  �� �� ���@�FsFncShmGet()                                                  *
*  �@�\�T�v�@�F���L�������擾                                                *
*  ���@�@�́@�F                                                              *
*�@ ��P���� �F                                                              *
*  ���A���@�F RTN_OK     : ����                                            *
* �@�@�@�@�@�@�@RTN_NG     : ���s                                            *
******************************************************************************/
{
    int     *shmData ;

    pAppEnv->shm_Id = shmget(pAppEnv->shm_Key, sizeof(int), 0666);
    if(pAppEnv->shm_Id == -1) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "shmget", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̎擾�Ɏ��s���܂��� ERR[%d]", errno);
        fprintf(Dbg_fp,"���L�������̎擾�Ɏ��s���܂��� ERR[%d]\n", errno);
        return(RTN_NG);
    }

    //  �A�^�b�`
    shmData = ( int * )shmat(pAppEnv->shm_Id, 0 , 0);
    if ( shmData == ( int * )-1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̑���Ɏ��s���܂��� ERR[%d]", errno ) ;
        fprintf(Dbg_fp,"���L�������̑���Ɏ��s���܂��� ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  �l�ݒ�
    *pshmData = *shmData ;

/*************
    fprintf(Dbg_fp,"���L������[GET] shmKey[%d] ID[%d] Data[%d] Add[%x]\n",
            pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData);
*************/

    //  �f�^�b�`
    if ( shmdt ( shmData ) == -1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃f�^�b�`�Ɏ��s���܂��� ERR[%d]", errno ) ;
        fprintf(Dbg_fp,"���L�������̃f�^�b�`�Ɏ��s���܂��� ERR[%d]", errno);
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static int sFncShmDel(struct appEnv *pAppEnv)
/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()                                                  */
/*  �@�\�T�v�@�F���L�������폜                                                */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct appEnv *     �v���O�������\���́B                    */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F RTN_OK     : ����                                            */
/* �@�@�@�@�@�@�@RTN_NG     : ���s                                            */
/******************************************************************************/
{
    int     *shmData ;

    fprintf(Dbg_fp,"���L������[DEL] shmKey[%d]-ID[%d]\n", pAppEnv->shm_Key, pAppEnv->shm_Id);

    //  �폜
    if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static void sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName,
            int plLineNo, char *pcExeFlg, char *pcErrCode, char *pcfmt, ... )
/******************************************************************************/
/*  �� �� ���@�FsFncPutLog()                                                  */
/*  �@�\�T�v�@�F�A�v���P�[�V�������O�o��                                      */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *      �ҏW������                                        */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�F����                                                          */
/******************************************************************************/
{
    va_list  ap ;
    char     cMsg[1024] ;

    /***
     ***    ���O�����l�ݒ�
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
     ***    ���O�o��
     ***/
    _ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;

    return ;
}

/**/
/******************************************************************************/
/*  �� �� ��  �FKeisanChk()                                                   */
/*  �@�\�T�v  �F�v�Z�`�F�b�N(WS��)                                            */
/*  ��    ��  �F                                                              */
/*   ��P���� �FchkPara :   �`�F�b�N�p�p�����[�^                              */
/*   ��Q���� �FpKekka  :   ���ʏ��\���̔z��                                */
/*   ��R���� �FKekkaCnt:   ���ʏ��\���̐�                                  */
/*   ��R���� �FlCnt    :   �������ʒu                                        */
/*   ��R���� �FODFld   :   �I�[�_�[���                                      */
/*  �o    ��  �F                                                              */
/*  ���A���  �Fint                                                           */
/*                  0:�Č�����                                                */
/*                  1:�Č�����                                                */
/******************************************************************************/
int KeisanChk(char *chkPara, KEKFL_STR *pKekka, int lCnt, char **ODFld, STKEISANCHK *calbuf)
{
    int         ret = 0;
    int         ret2;
    char        calBuff[256];
    char        buff[51];
    struct stKEISANCHK {
        char    KMKCD[7+1];    // ���ڃR�[�h
        char    KSNSK[128];    // �v�Z��
    } sKEISANCHK;
    int         iCnt;   // ���[�v�J�E���^
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
                                        /* IF ���W�J��̌v�Z��              */
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
            // �I�[�_�[�Ɍv�Z���ږ���
            continue;
        }
*********/

        //--------------------------------------------------------
        // ���ʒl�̒l������𐔒l������
        //  ���ʒl���u�����N�̏ꍇ�A�v�Z�͍s�킸�A�v�Z���ڂɂ�
        //  �u�����N��ݒ肷��
        //--------------------------------------------------------
        memset(tmp, 0, sizeof(tmp));
        strncpy(tmp, pKekka->kekka, 12);

        myFlg_RawNone = MY_FLG_OFF ;

        // �����̍��ڃR�[�h�𐔒l�ɒu��������B
        memset(calBuff, 0, sizeof(calBuff));
        for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
            // ���ڃR�[�h�̎n�܂�'['����������B
            if (sKEISANCHK.KSNSK[iCnt] == '[') {
                // ���ڒl������
                memset(tmp, 0, sizeof(tmp));
                tmpCnt = 0;
                iCnt++;
                // ���ڃR�[�h��]���i�I���ʒu��]��Null�܂Łj
                while (sKEISANCHK.KSNSK[iCnt] != ']' && sKEISANCHK.KSNSK[iCnt] != '\0') {
                    tmp[tmpCnt++] = sKEISANCHK.KSNSK[iCnt++];
                }
                // ���ʏ�񂩂�w��̍��ڃR�[�h���������A�u��������B
fprintf(Dbg_fp,"�v�ZKM[%s]\n",tmp);
                for (tmpCnt = 0; tmpCnt < FLrec_cnt; tmpCnt++) {
                    if(strcmp(FLrec[tmpCnt].rackid, pKekka->rackid) != 0)  continue;
                    if(FLrec[tmpCnt].pos != pKekka->pos)                   continue;

                    sprintf(buff,"%07d", FLrec[tmpCnt].kmcode);
                    if (strncmp(buff, tmp, strlen(tmp)) == 0) {
                        strcpy ( lc_RawBuf, FLrec[tmpCnt].kekka ) ;
                        lcp_RawBuf = strtok ( lc_RawBuf, " " ) ;
                        if ( lcp_RawBuf == NULL || lcp_RawBuf[0] == '/' ||
                             lcp_RawBuf[0] == '\0' || lcp_RawBuf[0] == '?' ) {
                            //  �l���u�����N�ꍇ
                            myFlg_RawNone = MY_FLG_ON ;
                        }
                        else {
                            //  �l���ݒ肳��Ă���ꍇ
                            strncat(calBuff, FLrec[tmpCnt].kekka, 12);
                            setCnt = strlen(calBuff);

                        }
                        break;
                    }
                }
                if (tmpCnt == FLrec_cnt) {
                    // �֘A���ڂ�������Ȃ��B
                    break;
                }
            }
            else if (KSNSK_SC == (int) sKEISANCHK.KSNSK[iCnt]) {
                // �g��
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
                // POW�Ƌ�ʂ��邽�߁A�O�̕�����O�Ŗ������`�F�b�N����B
                if (0 < iCnt &&
                    (sKEISANCHK.KSNSK[iCnt - 1] == 'o' ||
                     sKEISANCHK.KSNSK[iCnt - 1] == 'O')) {
                    break;
                }
                else {
                    // �̏d
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
                // �~�A����
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
                // �~�A��
                // ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ���
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
                /* ���ʋ敪                                                 */
                if (_VALUE_SBTKBN_MALE == (int) ODFld[FLDIDX_SBTKBN][0] ||
                        _VALUE_SBTKBN_FEMALE == (int) ODFld[FLDIDX_SBTKBN][0]) {
                    calBuff[setCnt++] = ODFld[FLDIDX_SBTKBN][0];
                    calBuff[setCnt] = (char) '\0';
                }
                else {
                    calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
                    calBuff[setCnt] = (char) '\0';
                                        /* �W�J�s��                         */
                }
            }
            else if (KSNSK_AGE == (int) sKEISANCHK.KSNSK[iCnt]) {
                /* �N��                                                     */
                if (_VALUE_AGEKBN_YEAR != (int) ODFld[FLDIDX_AGEKBN][0]) {
                    calBuff[setCnt++] = (char) '0';
                    calBuff[setCnt] = (char) '\0';
                                        /* �W�J�s��                         */
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
        // �v�Z���ڂ�z��ɑޔ�����
        //  �v�Z���̍��ڂ̂����ꂩ���u�����N�̏ꍇ��
        //  ���ʒl�t���O��ݒ肵�A��ʂŌ��ʒl�Ƀu�����N��ݒ肷��
        //--------------------------------------------------------
        if (iCnt == 128 || iCnt == strlen ( sKEISANCHK.KSNSK ) ) {
            //  �����擾
            li_Keta = 8;

            //  ���ڃR�[�h�ݒ�
            sprintf(buff,"%07d", pKekka->kmcode);
            memcpy(calbuf[ret].motoKMKCD, buff, 8);
            memcpy(calbuf[ret].KMKCD, sKEISANCHK.KMKCD, 8);

            /* �v�Z���Ɋ܂܂�� IF ���̓W�J                                     */
            if (NULL != (pszExpandKSNSK = OperateKSNSK(calBuff))) {
                if ('\0' != (int) *pszExpandKSNSK) {
                    strcpy(calBuff, pszExpandKSNSK);
                }
                free(pszExpandKSNSK);
                pszExpandKSNSK = (char *) NULL;
            }

            // ������̌v�Z�����v�Z����B
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
/*  �� �� ��  �FStringCal_sub()                                               */
/*  �@�\�T�v  �F�w�肳�ꂽ���Z�q�ƒl�Ŏl�����Z�s��                            */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fenzan   :   ���Z�q                                            */
/*   ��Q���� �Fval1    :   �l�P                                              */
/*   ��R���� �Fval2    :   �l�Q                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �Fdouble  �v�Z����                                              */
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
/*  �� �� ��  �FStringCal()                                                     */
/*  �@�\�T�v  �F�n���ꂽ������̌v�Z�����s��                                    */
/*  ��    ��  �F                                                                */
/*   ��P���� �FCalStr  :   �v�Z������                                          */
/*  �o    ��  �F                                                                */
/*  ���A���  �Fdouble  �v�Z����                                                */
/*                                                                              */
/*  ���ӁF  �Ή����鉉�Z�q�́u+ - / *�v���\�ł���B                           */
/*          ����ȊO��LOG�ALOG10�APOW��3�̌v�Z���s���B                        */
/*          �v�Z�̗D�揇�ʂ́A�l�����Z�̗D�揇�ʂɏ]��*��/���D�悳���B        */
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
            // ���l�̎�
            break;

        case '+': case '-': case '/': case '*':
            // ���Z�q�̎�
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
            // LOG�y��LOG10�̎�
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
            // POW�̎�
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
/*  �� �� ��  �FchkInfoRead()                                                 */
/*  �@�\�T�v  �F�t�@�C�����ǂݏo��                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �F���[�h  : 0:�����`�F�b�N�t�@�C��/ 1:�I�[�_�[�t�@�C��          */
/*   ��Q���� �Fkmkcd   :   ���ڃR�[�h                                        */
/*   ��R���� �FfName   :   �t�@�C����                                        */
/*  �o    ��  �FData    :   ���i�w�荀�ڃR�[�h�j                            */
/*            �Fbuff    :   �o�͗p�o�b�t�@                                    */
/*  ���A���  �Fint                                                           */
/*                  0:����                                                    */
/*                  1:�ُ�(���ڃR�[�h����)                                    */
/*                  2:�ُ�i���̑��j                                          */
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
        // �J���}��؂�̃��R�[�h�𕪊����A
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
                // CSV�t�B�[���h���s���i�ǂݔ�΂��j
                continue;
            }
            if (strncmp(kmkcd, pFld[5], 7) == 0) {
                // �w�荀�ڃR�[�h��������
                memcpy(Data, pFld, sizeof(char *) * 118);
                ret = 0;
                break;
            }
        }
        else {
            if (cnt != 58) {
                // CSV�t�B�[���h���s���i�ǂݔ�΂��j
                continue;
            }
fprintf(Dbg_fp,"del cnt[%d] ret[%d]\n",cnt,ret);
            if (strncmp(kmkcd, pFld[5], 7) == 0) {
fprintf(Dbg_fp,"[%s]--[%d]...\n",__FILE__,__LINE__);
                // �w�荀�ڃR�[�h��������
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
 * �v�Z�������񒆂Ɋ܂܂�� IF �u���b�N�̓W�J
 *
 * Paramter(s):
 *  pszKSNSK            NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A IF �u���b�N���܂ތv�Z���̕�
 *                      ����ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�AIF �u���b�N������W�J��̕����񂪊i�[���Ă����
 *  ��̐擪�|�C���^�C���^��Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
static char *OperateKSNSK(char *pszKSNSK)
{
    static char szBlank[] = " ";
    static char szNE[] = STR_NE;

    char *pszFormular;                  /* �߂�l (�����Ώۂ̌v�Z��)        */
    char *pszReplace;                   /* IF �u���b�N�W�J����              */
    char *pszIFBlock = (char *) NULL;   /* IF �u���b�N������                */
    struct _IFBLOCK *pstItems = (struct _IFBLOCK *) NULL;
                                        /* IF �u���b�N�����ڗv�f���ɕ���    */
    double dblLeft;                     /* ���������Ӓl                     */
    double dblRight;                    /* �������E�Ӓl                     */
    BOOL nCompared = FALSE;             /* ���������茋��                   */
    BOOL nErrorOccured = FALSE;         /* �G���[�����t���O                 */
    static char szConvert[32];

    if (NULL != (pszFormular = _touppercase(_replace(pszKSNSK, szBlank, NULL)))) {

fprintf(Dbg_fp,"KSNSK: [%s]\n", pszFormular);

        if (!nErrorOccured && NULL != pszFormular) {
            if (!IsFormula(pszFormular)) {
                fprintf(Dbg_fp,"Invalid formular - \"%s\"\n", pszFormular);
                nErrorOccured = TRUE;   /* �v�Z���Ƃ��Ĉُ�                 */
                free(pszFormular);
                pszFormular = (char *) NULL;
            }
        }

        while (!nErrorOccured &&
               NULL !=  (pszIFBlock = GetIFBlock(pszFormular))) {

            if (NULL == (pstItems = SplitIFBlockItems(pszIFBlock))) {
                fprintf(Dbg_fp,"Invalid IF block items - \"%s\"\n", pszFormular);
                nErrorOccured = TRUE;   /* IF �u���b�N���̗v�f�������s      */
                free(pszFormular);
                pszFormular = (char *) NULL;
            }
            else if (NULL == pstItems->pszConditionLeft ||
                     NULL == pstItems->pszOperator ||
                     NULL == pstItems->pszConditionRight ||
                     NULL == pstItems->pszValueTrue ||
                     NULL == pstItems->pszValueFalse) {
                fprintf(Dbg_fp,"Analize error - \"%s\"\n", pszFormular);
                nErrorOccured = TRUE;   /* IF �u���b�N���̗v�f�������s      */
                free(pszFormular);
                pszFormular = (char *) NULL;
            }
            else {
                /* �����������e������ IF �u���b�N������
                    (������ IF �u���b�N�̓W�J�G���W��)                      */
                dblLeft = StringCal(pstItems->pszConditionLeft);
                dblRight = StringCal(pstItems->pszConditionRight);

                /* ��x������ɕϊ����Ȃ��Ƃ��܂���r�ł��Ȃ�               */
                sprintf(szConvert, "%f", dblLeft);
                dblLeft = strtod(szConvert, (char **) NULL);
                sprintf(szConvert, "%f", dblRight);
                dblRight = strtod(szConvert, (char **) NULL);

                switch ((int) *(pstItems->pszOperator)) {
                case OPERATOR_EQ:       /* ������: ��v                     */
                   nCompared = ((dblLeft == dblRight) ? TRUE : FALSE);
                    break;

                case OPERATOR_LT:       /* ������: ���� or �s��v           */
                    if (strcmp(pstItems->pszOperator, szNE)) {
                        nCompared = ((dblLeft < dblRight) ? TRUE : FALSE);
                    } else {
                        nCompared = ((dblLeft != dblRight) ? TRUE : FALSE);
                    }
                    break;

                case OPERATOR_GT:       /* ������: �z����                   */
                    nCompared = ((dblLeft > dblRight) ? TRUE : FALSE);
                    break;

                default:                /* �ُ�Ȕ�r���Z�q                 */
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
                                         /* IF �u���b�N �� �K�p�l�ϊ����s    */
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
 * �����񒆂̔��p�p�������𔼊p�p�啶���ɕϊ�����������̐���
 *
 * Parameter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�ϊ����̕�����ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A�ϊ���̕�������i�[���Ă���̈�̐擪�|�C���^��
 *  �Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
static char *_touppercase(char *pszOrigin)
{
    char *pszResult = (char *) NULL;    /* �߂�l                           */
    size_t ulIndex;                     /* �����ʒu                         */

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
 * ������̒u��
 *
 * Parameter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�u���ΏۂƂȂ镶����ł��B
 *  pszTarget           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�u���ɂ���Ēu���������镶
 *                      ����ł��B
 *  pszReplace          NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      NULL ���w�肳�ꂽ�ꍇ�A�󕶎��񂪎w�肳�ꂽ���̂Ƃ�
 *                      �Ĉ����܂��B
 *                      �����Ŏw�肷�镶����́A�u���ɂ���Ēu�������镶��
 *                      ��ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A�u����̕�������i�[���Ă���̈�̐擪�|�C���^��
 *  �Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
static char *_replace(char *pszOrigin, char *pszTarget, char *pszReplace)
{
    char *pszResult = (char *) NULL;    /* �߂�l                           */
    char *pszFind;                      /* �u���Ώی���                     */
    int nFindCount;                     /* �u���Ώی���                     */
    size_t ulOrigin;                    /* ���̕�����̃o�C�g �T�C�Y        */
    size_t ulTarget;                    /* ���̕�����̃o�C�g �T�C�Y        */
    size_t ulSource;                    /* �u���Ώۂ̃o�C�g �T�C�Y          */
    size_t ulReplace;                   /* �u�������镶����̃o�C�g �T�C�Y  */
    size_t ulDestination;               /* �u���㕶���ʒu                   */

    if (NULL != pszOrigin && NULL != pszTarget) {
        if ((size_t) 0 < (ulTarget = strlen(pszTarget))) {
            if ((size_t) 1 > (ulOrigin = strlen(pszOrigin))) {
                pszResult = strdup(pszOrigin);
                                        /* �u���ΏۂȂ�                     */
            }
            else {
                for (nFindCount = 0, pszFind = (char *) pszOrigin;
                     NULL != (pszFind = strstr(pszFind, pszTarget));
                     nFindCount++, pszFind++);
                if (0 == nFindCount) {
                    pszResult = strdup(pszOrigin);
                                        /* �u���ΏۂȂ�                     */
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
 * �v�Z���Ɋ܂܂�� IF �u���b�N������𒊏o���܂��B
 *
 * Paramter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B

 *
 * Return value:
 *  �֐�������I�������ꍇ�A���o���� IF �u���b�N��������i�[����̈�̐擪�|
 *  �C���^��Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
static char *GetIFBlock(char *pszOriginal)
{
    static char szIFBlock[] = STR_BEGIN_IFBLOCK;

    char *pszResult = NULL;             /* �߂�l                           */
    char *pszIFBlock;                   /* IF �u���b�N�J�n�ʒu              */
    size_t ulOriginal;                  /* ���̕�����̒���                 */
    char *pszFind;                      /* IF �u���b�N�I�[����              */
    int nParenthesis = 0;               /* ���ʂ̊K�w�k�x                   */
    int nComma;                         /* �J���}�̐�                       */
    BOOL nTarminate;                    /* IF �u���b�N�I�[���o              */

    if (NULL != pszOriginal) {
        if ((size_t) 0 <= (ulOriginal = strlen(pszOriginal))) {
            if (NULL != (pszIFBlock = _strrstr(pszOriginal, szIFBlock))) {
                for (pszFind = (pszIFBlock + strlen(szIFBlock)),
                         nTarminate = FALSE, nParenthesis = 0, nComma = 0;
                     !nTarminate; pszFind++) {

                    switch ((int) *pszFind) {
                    case PARENT_BEGIN:  /* �J�b�R (�J�n)                    */
                        nParenthesis++;
                        break;

                    case _EOS:
                    case PARENT_END:    /* �J�b�R (�I��)                    */
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
                                        /* �v�f�̋�؂�������J���}         */
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
 * IF �u���b�N����������ڒP�ʂɕ������܂��B
 *
 * Paramater(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�v�f���Ƃɕ�������v�Z���� 
 *                      IF �u���b�N������ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A������̍��ڕ�������i�[���� _IFBLOCK �\���̂̐�
 *  ���|�C���^��Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ freeIFBLOCK() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
struct _IFBLOCK *SplitIFBlockItems(char *pszOrigin)
{
    static char szNE[] = STR_NE;

    struct _IFBLOCK *pstResult = (struct _IFBLOCK *) NULL;
                                        /* �߂�l                           */
    BOOL nErrorOccured = FALSE;         /* �G���[���o�t���O                 */
    BOOL nTerminate = FALSE;            /* �����I���t���O                   */
    char *pszTarget;                    /* ���蕶��                         */
    char *pszBegin;                     /* ����Ώۂ̍��ڂ̐擪             */
    int nParenthesis;                   /* �J�b�R�̓���q�[�x               */
    int nIndex;                         /* �������ڂ̍��ڃC���f�b�N�X       */

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
            case PARENT_BEGIN:          /* �J�b�R (�J�n)                    */
                nParenthesis++;
                break;

            case PARENT_END:            /* �J�b�R (�I��)                    */
                nParenthesis--;
                if (0 > nParenthesis) {
                    if (NULL == pstResult->pszValueTrue ||
                        NULL == pstResult->pszConditionRight) {
                        nErrorOccured = TRUE;
                                        /* IF �u���b�N�̏I�������� ')' ����
                                           �o�������A�K�{���ڂ��s�����Ă��� */
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

            case OPERATOR_LT:           /* ���������Z�q                     */
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

            case SPLITTER_COMMA:    /* �v�f�̋�؂�������J���}             */
                if (nParenthesis) {
                    break;
                }
                else if (NULL == pstResult->pszConditionRight) {
                    /* �������E�� - ���������^�̏ꍇ�ɓK�p����l            */
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
                    /* ���������^�̏ꍇ�ɓK�p����l - 
                       �U�̏ꍇ�ɓK�p����l                                 */
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

            default:                    /* �����ł̏����̑ΏۊO             */
                break;
            }
        }
    }

    /* �G���[�������́A (�r���܂�) �m�ۂ������e���N���A                     */
    if (nErrorOccured && NULL != pstResult) {
        freeIFBLOCK(pstResult);
        pstResult = (struct _IFBLOCK *) NULL;
    }
    return (pstResult);
}

/*--------------------------------------------------------------------------*
 * freeIFBLOCK
 *
 * IF �u���b�N���v�f�����\���̗̂v�f��S�ĊJ��
 *
 * Parameter(s):
 *  pstTarget           IF �u���b�N���v�f�����\���̂̐擪�|�C���^���w�肵��
 *                      ���B
 *
 * Return value:
 *  Nothing
 *--------------------------------------------------------------------------*/
static void freeIFBLOCK(struct _IFBLOCK *pstTarget)
{
    int nIndex;                         /* ���ڃC���f�b�N�X                 */

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
 * ������̌��� (������������)
 *
 * Parameter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A��������镶����ł��B
 *  pszTarget           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�������镶����ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A���o������������i�[���Ă���̈�̐擪�|�C���^��
 *  �Ԃ��܂��B
 *  �G���[�����������ꍇ�A�w�肵�������񂪌��o�ł��Ȃ������ꍇ�A NULL ��Ԃ�
 *  �܂��B
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
 * �w��T�C�Y���̂ݕ�����𕡐�
 *
 * Parameter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�������ƂȂ镶����ł��B
 *  ulSize              �������镶����̃T�C�Y���w�肵�܂��B
 *                      ���̃T�C�Y�ɏ�L�p�����[�^�Ŏw�肵��������̒������
 *                      �傫���T�C�Y���w�肵���ꍇ�A�P�ɕ����񂪕��ʂ���邾
 *                      ���ł��B
 *
 * Return value:
 *  �֐�������I�������ꍇ�A����������������i�[���Ă���̈�̐擪�|�C���^��
 *  �Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
static char *_strndup(char *pszOrigin, size_t ulSize)
{
    char *pszResult = (char *) NULL;    /* �߂�l                           */
    size_t ulOrigin;                    /* ���̕�����̃o�C�g �T�C�Y        */
    size_t ulTruth;                     /* ���o���镶����̃o�C�g �T�C�Y    */

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
 * 10 �i�@�\�L�̐��l������`�F�b�N
 *
 * Parameter(s):
 *  pszTarget           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�`�F�b�N�Ώۂ̐��l�������
 *                      ���B
 *
 * Return value:
 *  �w�肵�������񂪁A 10 �i�@�\�L�̐��l������ (�����A�����A���̒l���܂�) ��
 *  �ꍇ�A 0 �ȊO�̒l��Ԃ��܂��B
 *  10 �i�@�\�L�̐��l������ȊO�A�܂��̓G���[�����������ꍇ�A�l 0 ��Ԃ���
 *  ���B
 *
 * Comment:
 *  10 �i�@�\�L�̐��l������
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
 * �v�Z���̏����`�F�b�N
 *
 * Paramter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A�v�Z���̕�����ł��B
 *
 * Return value:
 *  �w�肳�ꂽ�����񂪁A�v�Z���Ƃ��Đ������Ă���ꍇ�A 0 �ȊO�̒l��Ԃ���
 *  ���B
 *  �v�Z���ȊO�̏ꍇ�A�܂��̓G���[�����������ꍇ�A�l 0 ��Ԃ��܂��B
 *--------------------------------------------------------------------------*/
static int IsFormula(char *pszKSNSK)
{
    BOOL bResult = FALSE;
    char *pszFormular;
    char *pszReplace;
    int nIndex;
    int nParenthesis = 0;               /* ���ʂ̊K�w�k�x                   */

    if (NULL != (pszFormular = 
                          _touppercase(_replace(pszKSNSK,
                                                " ",
                                                (char *) NULL)))) {

        /* �Z�p�֋�                                                   */
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

            /* ���������̔�r���Z�q����                                     */
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

        /* ������ (�����_���܂�) �A���Z�L������                             */
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

        /* ���ʑΉ��`�F�b�N                                                 */
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

