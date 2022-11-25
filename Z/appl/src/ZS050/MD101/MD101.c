
/* ��������
 2020.05.26 #01 ����  ����˗����M�̍ۂɁA�˗��t�@�C���Ɍ���ē������ڃR�[�h��
                      �����ݒ肳��Ă����ꍇ�ɁA�����`���l���̑���˗��𕡐�
                      �ݒ肵�Ȃ��悤�ɏC��

*/

/******************************************************************************
* �C���N���[�h�錾                                                            *
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
* �}�N���錾                                                                  *
******************************************************************************/
#define  GOKI_MAX                 (3)                 /* ���͋@�ڑ�MAX�� */
#define  SOCFRAME_MAXSIZE         (512)               /* �ő�t���[���� */
#define  SOCBUF_MAXSIZE           (2048)              /* SOC����M�o�b�t�@��MAX�T�C�Y */
#define  MSTCHANL_MAX             (800)               /* �`���l���}�X�^�̔z��MAX�� */
#define  RETRY_MAX1               (10)                /* �\�P�b�g�ڑ��G���[���̃��g���C�� */
#define  RETRY_MAX2               (2)                 /* �\�P�b�g�Đڑ����̃��g���C�� */
#define  MYAPP_LOG_ERRCODE_NON    "00000000"
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */

/******************************************************************************
* �O���[�o���錾                                                              *
******************************************************************************/
static char    LmName[25];                            /* �v���O������ */
struct stcLogMember  gstLogMem;                       /* ���O�o�͏�� */
struct appEnv  sAppEnv;
SVRINF         Svrinf[GOKI_MAX];                      /* ���͋@�ڑ���� */
CHLMST         MstChanl[MSTCHANL_MAX];                /* �`���l���}�X�^�i�[�\���� */
FILE           *SOCrcv_fp[GOKI_MAX];                  /* ��M�f�[�^�ޔ�p�t�@�C���|�C���^ */
FILE           *SOCsnd_fp[GOKI_MAX];                  /* ���M�f�[�^�ޔ�p�t�@�C���|�C���^ */
int            SOCrcv_fd[GOKI_MAX];                   /* ��M�f�[�^�ޔ�p�f�B�X�N���v�^ */
int            SOCsnd_fd[GOKI_MAX];                   /* ���M�f�[�^�ޔ�p�f�B�X�N���v�^ */
static char    FrmBuf[GOKI_MAX][SOCBUF_MAXSIZE];      /* ���M�t���[���o�b�t�@ */
static char    SndBuf[SOCBUF_MAXSIZE];                /* ���M�f�[�^�o�b�t�@ */
static char    RcvBuf[SOCFRAME_MAXSIZE +1];           /* ��M�t���[���o�b�t�@ */
static char    RBuf_rslt[GOKI_MAX][SOCBUF_MAXSIZE];   /* �������茋�ʒ~�ϗp��M�f�[�^�o�b�t�@ */
static int     Frbuf_len[GOKI_MAX];                   /* ���M�t���[���̃f�[�^�� */
static int     Svrinf_cnt;                            /* �L���ȕ��͋@�ڑ����̐� */
static int     MstChanl_cnt;                          /* �`���l���}�X�^�̃f�[�^�� */
static int     DbgFlg;                                /* �f�o�b�O�o�̓X�C�b�` */

/******************************************************************************
* �֐��錾                                                                    *
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
    char    buff[256], lc_prmBuf[256];
    char    fpth[101];
    int     ii, mecd, portno, i_tmp;
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
        if(DbgFlg)  printf("�p�����[�^�t�@�C���̃I�[�v���Ɏ��s���܂���[%s]\n", argv[1]);
        return(RTN_NG);
    }


    memset(&Svrinf[0],'\0', (sizeof(SVRINF)*GOKI_MAX));
    for(ii = 0 ; ii < GOKI_MAX ; ii++)
        Svrinf[ii].sfd = -1;
    Svrinf_cnt = 0;

    /* �����Ώۂ̃��C��No.�擾 */
    if(ZbmlPrmGetVal(bp, "LINENO", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[LINENO]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[LINENO]\n");
        return(RTN_NG);
    }
    sAppEnv.lineno = atoi(lc_prmBuf);


    /* "GOKI_1"(���͋@1) �̏��擾 (������Ȃ��Ă��G���[�ɂ��Ȃ�) */
    if(ZbmlPrmGetVal(bp, "GOKI_1", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[GOKI_1]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[GOKI_1]\n");
    }
    else {
        sscanf(lc_prmBuf,"%d %s %d", &mecd, buff, &portno);
        sprintf(Svrinf[Svrinf_cnt].svhost,"%s", buff);
        Svrinf[Svrinf_cnt].mecd = mecd;
        Svrinf[Svrinf_cnt].svport = portno;
        Svrinf_cnt++;
    }

    /* "GOKI_2"(���͋@2) �̏��擾 (������Ȃ��Ă��G���[�ɂ��Ȃ�) */
    if(ZbmlPrmGetVal(bp, "GOKI_2", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[GOKI_2]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[GOKI_2]\n");
    }
    else {
        sscanf(lc_prmBuf,"%d %s %d", &mecd, buff, &portno);
        sprintf(Svrinf[Svrinf_cnt].svhost,"%s", buff);
        Svrinf[Svrinf_cnt].mecd = mecd;
        Svrinf[Svrinf_cnt].svport = portno;
        Svrinf_cnt++;
    }

    /* "GOKI_3"(���͋@3) �̏��擾 (������Ȃ��Ă��G���[�ɂ��Ȃ�) */
    if(ZbmlPrmGetVal(bp, "GOKI_3", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[GOKI_3]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[GOKI_3]\n");
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
                     "���͋@�ڑ�����MAX���𒴂��܂����BSvrinf_cnt[%d]", Svrinf_cnt);
        if(DbgFlg)  printf("���͋@�ڑ�����MAX���𒴂��܂����BSvrinf_cnt[%d]", Svrinf_cnt);
        return(RTN_NG);
    }

    /* ���̑��̃p�����[�^�擾 */
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    if(ZbmlPrmGetVal(bp, "SHM_KEY", lc_prmBuf) != 0) {          /* ���L�������L�[ */
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[SHM_KEY]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[SHM_KEY]\n");
        return(RTN_NG);
    }
    sAppEnv.shm_Key = atoi(lc_prmBuf);

    if(ZbmlPrmGetVal(bp, "TIMEOUT_SEC", lc_prmBuf) != 0) {      /* �^�C���A�E�g�l(sec) */
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[TIMEOUT_SEC]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[TIMEOUT_SEC]\n");
        return(RTN_NG);
    }
    sAppEnv.timeout_Sec = atoi(lc_prmBuf);

    if(ZbmlPrmGetVal(bp, "TIMEOUT_USEC", lc_prmBuf) != 0) {     /* �^�C���A�E�g�l(msec) */
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�p�����[�^���擾�ł��܂���ł���[TIMEOUT_USEC]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[TIMEOUT_USEC]\n");
        return(RTN_NG);
    }
    sAppEnv.timeout_uSec = atoi(lc_prmBuf);

    /* ��������(����)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "NYUBI_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[NYUBI_KM]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[NYUBI_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.nyubi_km,"%s", buff);
    sAppEnv.nyubi_ch = i_tmp;
    if(DbgFlg)  printf("��������(����) KM[%s] CH[%d]\n", sAppEnv.nyubi_km, sAppEnv.nyubi_ch);

    /* ��������(�n��)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "YOUKETSU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[YOUKETSU_KM]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[YOUKETSU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.youkets_km,"%s", buff);
    sAppEnv.youkets_ch = i_tmp;
    if(DbgFlg)  printf("��������(�n��) KM[%s] CH[%d]\n", sAppEnv.youkets_km, sAppEnv.youkets_ch);

    /* ��������(���t)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "OUDAN_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[OUDAN_KM]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[OUDAN_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.oudan_km,"%s", buff);
    sAppEnv.oudan_ch = i_tmp;
    if(DbgFlg)  printf("��������(���t) KM[%s] CH[%d]\n", sAppEnv.oudan_km, sAppEnv.oudan_ch);

    /* ��������(���H)�̍��ڃR�[�h�ƃ`���l��No. */
    if(ZbmlPrmGetVal(bp, "SEISYOKU_KM", lc_prmBuf) != 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON,
                   MYAPP_LOG_ERRCODE_NON, "�p�����[�^���擾�ł��܂���ł���[SEISYOKU_KM]");
        if(DbgFlg)  printf("�p�����[�^���擾�ł��܂���ł���[SEISYOKU_KM]\n");
        return(RTN_NG);
    }
    sscanf(lc_prmBuf,"%s %d", buff, &i_tmp);
    sprintf(sAppEnv.seisyk_km,"%s", buff);
    sAppEnv.seisyk_ch = i_tmp;
    if(DbgFlg)  printf("��������(���H) KM[%s] CH[%d]\n", sAppEnv.seisyk_km, sAppEnv.seisyk_ch);


    /* �p�����[�^�t�@�C���N���[�Y */
    ZbmlPrmClose(bp);


    /* ���L�������̎擾 */
    if(sFncShmCrt(&sAppEnv) != RTN_OK)  return(RTN_NG);


    /* �`���l���}�X�^�̃��������[�h */
    if(sFncChMstLoad() != RTN_OK)  return(RTN_NG);

    /* �������擾 */
    if(sFncGetUdate() != RTN_OK)  return(RTN_NG);
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "������ [%s]", sAppEnv.udate);
    if(DbgFlg)  printf("������ [%s]\n", sAppEnv.udate);


    /* �\�P�b�g�f�[�^�ޔ��t�@�C���I�[�v�� */
    for(ii = 0 ; ii < GOKI_MAX ; ii++) {              /* fd�A�|�C���^�̏����� */
        SOCrcv_fd[ii] = -1;    SOCsnd_fd[ii] = -1;
        SOCrcv_fp[ii] = NULL;  SOCsnd_fp[ii] = NULL;
    }

    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {

        /* ��MRaw�t�@�C���̃I�[�v�� */
        sprintf(fpth,"%s/ZS050_%02dRCV.raw", RCSDDATA_PATH, Svrinf[ii].mecd);
        SOCrcv_fd[ii] = open(fpth, (O_WRONLY|O_CREAT|O_APPEND), (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
        if(SOCrcv_fd[ii] == -1) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]\n", fpth, errno);
        }

        /* ��M�f�[�^�t�@�C���̃I�[�v�� */
        sprintf(fpth,"%s/ZS050_%02dRCV", RCSDDATA_PATH, Svrinf[ii].mecd);
        if(NULL == (SOCrcv_fp[ii] = fopen(fpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]\n", fpth, errno);
        }

        /* ���MRaw�t�@�C���̃I�[�v�� */
        sprintf(fpth,"%s/ZS050_%02dSND.raw", RCSDDATA_PATH, Svrinf[ii].mecd);
        SOCsnd_fd[ii] = open(fpth, (O_WRONLY|O_CREAT|O_APPEND), (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
        if(SOCsnd_fd[ii] == -1) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__,
                     EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]\n", fpth, errno);
        }

        /* ���M�f�[�^�t�@�C���̃I�[�v�� */
        sprintf(fpth,"%s/ZS050_%02dSND", RCSDDATA_PATH, Svrinf[ii].mecd);
        if(NULL == (SOCsnd_fp[ii] = fopen(fpth,"a"))) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]", fpth, errno);
            if(DbgFlg)  printf("�f�[�^�ޔ��t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]\n", fpth, errno);
        }
    }

    /* �������ޔ����̓Ǎ��� */
    sFncGetMemSave();

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
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
    char    fpth[101];
    int     ii, rtn, maxfd, li_stopFlg, ptr;
    short   f_snd;
    ssize_t blen;
    fd_set  rsds;
    struct  timeval  tv;
    struct  stat     st;

    /* �������� */
    tv.tv_sec  = sAppEnv.timeout_Sec;
    tv.tv_usec = sAppEnv.timeout_uSec;

    /* ���͋@�Ƃ̃\�P�b�g�ڑ����� */
    if(sFncConctSvr(1) != RTN_OK)
        return(RTN_NG);

    sprintf(fpth,"%s/%d_ME_RECONCT", ONLINE_PATH, sAppEnv.lineno);


    /* ���C�����[�v */
    for( ; ; ) {

        maxfd = -1;
        FD_ZERO(&rsds);
        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].sfd == -1)  continue;
            FD_SET(Svrinf[ii].sfd, &rsds);
            if(Svrinf[ii].sfd > maxfd)  maxfd = Svrinf[ii].sfd;
        }

        /* �\�P�b�g���M���� */
        f_snd = 0;
        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].sfd == -1)  continue;

            rtn = sFncSocSend(&Svrinf[ii], ii);       /* Ack�A�˗���񓙂̑��M���� */
            if(rtn > 0)  f_snd = 1;
        }

        /* �I���ʒm�̏�Ԋm�F */
        li_stopFlg = 0;
        sFncShmGet(&sAppEnv, &li_stopFlg);
        if(li_stopFlg == 1)  break;

        /* ����f��̍Đڑ����� */
        if(stat(fpth, &st) == 0) {
            rtn = sFncConctSvr(2);  unlink(fpth);
        }

        /* ���������̑ޔ�(CtlNo.�AMeSEQNo.) */
        sFncPutMemSave();

        if(f_snd > 0)  continue;


        /* �\�P�b�g��M���� */
        tv.tv_sec  = sAppEnv.timeout_Sec;
        tv.tv_usec = sAppEnv.timeout_uSec;

        rtn = select(maxfd+1, &rsds, NULL, NULL, &tv);
        if(rtn < 0) {
            if(errno == EINTR)  continue;
            sFncPutLog(TRCKIND_ERROR, __FILE__, "select", __LINE__,
                       EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                       "SOCKET��ԊĎ��Ɋ����݂��������܂����BERR[%d]", errno);
            if(DbgFlg)  printf("SOCKET��ԊĎ��Ɋ����݂��������܂����BERR[%d]\n", errno);
            break;
        }
        else if(rtn == 0) {
            if(DbgFlg)  printf("SOCKET�^�C���A�E�g...\n");
            continue;
        }

        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].sfd == -1)  continue;

            if(FD_ISSET(Svrinf[ii].sfd, &rsds)) {
                rtn = sFncSocRecv(&Svrinf[ii], ii);   /* �\�P�b�g�f�[�^��M */
            }
        }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    }

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
    char    buff[11];
    int     ii, blen;

    /* �V�O�i���n���h���̐ݒ� */
    signal(SIGINT, endFunction);
    signal(SIGKILL, endFunction);

    if(DbgFlg)  printf("�I��������.....");

    /* ���������̑ޔ�(CtlNo.) */
    sFncPutMemSave();

    /* �\�P�b�g�N���[�Y���� */
    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
        if(Svrinf[ii].sfd == -1)  continue;
        shutdown(Svrinf[ii].sfd, 2);
        close(Svrinf[ii].sfd);
    }


    /* ����M�f�[�^�ޔ��t�@�C���̃N���[�Y */
    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
        if(SOCrcv_fd[ii] > 0)      close(SOCrcv_fd[ii]);
        if(SOCsnd_fd[ii] > 0)      close(SOCsnd_fd[ii]);

        if(SOCrcv_fp[ii] != NULL)  fclose(SOCrcv_fp[ii]);
        if(SOCsnd_fp[ii] != NULL)  fclose(SOCsnd_fp[ii]);
    }


    /* ���L�������폜 */
    sFncShmDel(&sAppEnv);

    /* �I���̃��O�o�� */
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "�v���O�����I��");
    if(DbgFlg)  printf("�v���O�����I��\n");

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
    char    fpth[256], fbuf[256];
    char    wk_mekbn[5], wk_chname[21], wk_chnum[8], wk_kmcode[8];
    int     ii, mm, len, c_st, c_en, c_dl;
    FILE    *fp;

    MstChanl_cnt = 0;
    sprintf(fpth,"%s/mechmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncChMstLoad", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�`���l���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("�`���l���}�X�^�t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ERR[%d]\n", fpth, errno);
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
                   "�`���l���}�X�^�̔z��MAX���𒴂��܂����BFile[%s]", fpth);
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
    int     c_st, c_en, c_dl;
    int     ii, jj, len;
    FILE    *fp;

    sprintf(fpth,"%s/sysknrmst.del", MSTFILE_PATH);
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetUdate", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�V�X�e���Ǘ��}�X�^�t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("�V�X�e���Ǘ��}�X�^�t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    fgets(fbuf, 512, fp);                             /* 1�s�擾 */
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
*  �� �� ���@�FsFncGetMemSave()                                               *
*  �@�\�T�v�@�F�������ޔ����̓Ǎ���/���f����                                *
*  ���@�@�́@�F                                                               *
*  ��    ��                                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
******************************************************************************/
{
    char    fpth[101], fbuf[101], qctp[11];
    int     ii, mecd, ctlno, meseq;
    FILE    *fp;
    struct stat  st;

    sprintf(fpth,"%s/%d_MD101.sav", ONLINE_PATH, sAppEnv.lineno);
    if(stat(fpth, &st) != 0) {
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�������ޔ��t�@�C����������܂���BFile[%s]", fpth);
        if(DbgFlg)  printf("�������ޔ��t�@�C����������܂���BFile[%s]\n", fpth);
        return;
    }

    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
        return;
    }

    for( ; ; ) {
        if(NULL == fgets(fbuf,101, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;

        sscanf(fbuf,"%d %d %d", &mecd, &ctlno, &meseq);
        for(ii = 0 ; ii < Svrinf_cnt ; ii++) {
            if(Svrinf[ii].mecd == (short)mecd) {
                Svrinf[ii].ctlno = ctlno;             /* �Y�����@��CtlNo.�ݒ� */
                Svrinf[ii].meseqno = meseq;           /* �Y�����@��MeSEQNo.�ݒ� */
                if(DbgFlg)  printf("CtlNo�Ǎ��݊���   ME[%d] CtlNo[%d]   TP[%s]\n", mecd, ctlno, qctp);
                if(DbgFlg)  printf("MeSEQNo�Ǎ��݊��� ME[%d] MeSEQNo[%d]\n", mecd, meseq);
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
*  �� �� ���@�FsFncPutMemSave()                                               *
*  �@�\�T�v�@�F�������ޔ����̏����ݏ���                                     *
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

    sprintf(fpth,"%s/%d_MD101.sav", ONLINE_PATH, sAppEnv.lineno);
    if(NULL == (fp = fopen(fpth,"w"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncGetMemSave", __LINE__,
            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]", fpth, errno);
        if(DbgFlg)  printf("�������ޔ��t�@�C���̃I�[�v���Ɏ��s�BFile[%s] ERR[%d]\n", fpth, errno);
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
*  �� �� ���@�FsFncConctSvr()                                                 *
*  �@�\�T�v�@�F�\�P�b�g�ڑ�����                                               *
*  ���@�@�́@�F                                                               *
*  ��    ��    short  flg; (1; �S�ڑ��A2: �Đڑ�)                             *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    int     ii, jj, ertmp, try_max;
    struct  hostent  *server;
    struct  sockaddr_in sv_addr[GOKI_MAX];

    /* �\�P�b�gfd�̏����� */
    if(flg == 1) {
        for(ii = 0 ; ii < GOKI_MAX ; ii++) {
            Svrinf[ii].sfd = -1;
        }
    }

    if(flg == 1)  try_max = RETRY_MAX1;
    else          try_max = RETRY_MAX2;

    /* �ڑ����� */
    for(ii = 0 ; ii < Svrinf_cnt ; ii++) {

        if(flg == 2 && Svrinf[ii].sfd > 0)  continue;

        server = (struct hostent *)gethostbyname(Svrinf[ii].svhost);
        if(server == NULL) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncConctSvr", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�T�[�o��IP���擾�Ɏ��s���܂����BServer[%s]", Svrinf[ii].svhost);
            if(DbgFlg)  printf("�T�[�o��IP���擾�Ɏ��s���܂����BServer[%s]\n", Svrinf[ii].svhost);
            return(RTN_NG);
        }

        /* �\�P�b�g���� */
        Svrinf[ii].sfd = socket(AF_INET, SOCK_STREAM, 0);
        if(Svrinf[ii].sfd < 0) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncConctSvr", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET�����Ɏ��s���܂����BServer[%s] ME[%d] ERR[%d]", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
            if(DbgFlg)
                printf("SOCKET�����Ɏ��s���܂����BServer[%s] ME[%d] ERR[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
            return(RTN_NG);
        }

        memset(&sv_addr[ii], '\0', sizeof(struct sockaddr_in));
        sv_addr[ii].sin_family = AF_INET;
        sv_addr[ii].sin_port   = (u_short)htons((u_short)Svrinf[ii].svport);
        memcpy(&sv_addr[ii].sin_addr, server->h_addr, server->h_length);


        /* �\�P�b�g�ڑ� */
        for(jj = 0 ; jj < try_max ; jj++) {
            ertmp = 0;
            if((connect(Svrinf[ii].sfd, (struct sockaddr *)&sv_addr[ii], sizeof(struct  sockaddr_in))) < 0) {
                if(DbgFlg)  printf("SOCKET�ڑ��Ɏ��s���܂����BServer[%s] ME[%d] ERR[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
                ertmp = errno;
                sleep(1);  continue;
            }
            else  break;
        }
        if(ertmp != 0) {
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncConctSvr", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "SOCKET�ڑ��Ɏ��s���܂����BServer[%s] ME[%d] ERR[%d]", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);
            if(DbgFlg)  printf("SOCKET�ڑ��Ɏ��s���܂����BServer[%s] ME[%d] ERR[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd, errno);

            close(Svrinf[ii].sfd);
            Svrinf[ii].sfd = -1;
            continue;
        }

        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET�ڑ����܂����BServer[%s] ME[%d]", Svrinf[ii].svhost, Svrinf[ii].mecd);
        if(DbgFlg)  printf("SOCKET�ڑ����܂����BServer[%s] ME[%d]\n", Svrinf[ii].svhost, Svrinf[ii].mecd);
    }

    return(RTN_OK);
}

/**/
static int sFncSocSend(SVRINF *svif, int idx)
/******************************************************************************
*  �� �� ���@�FsFncSocSend()                                                  *
*  �@�\�T�v�@�F�\�P�b�g�f�[�^���M���䏈��                                     *
*  ���@�@�́@�F                                                               *
*  ��    ��    short  flg; (1; �S�ڑ��A2: �Đڑ�)                             *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    buff[SOCFRAME_MAXSIZE +1];
    int     f_sd, blen, ptr;
    time_t  tlsec;

    f_sd = 0;

    if(svif->sts == 1 ||
       svif->sts == 3 || svif->sts == 11) {           /* Ack���M */
        buff[0] = 0x06;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts++;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("Ack���M...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 5) {                         /* �˗����M�O��ENQ���M */
        buff[0] = 0x05;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts++;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("ENQ���M...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 7) {                         /* �˗���񑗐M */
        if(sFncIraiSend(svif, idx) != RTN_OK) {
            buff[0] = 0x15;                           /* �G���[����NAK���M */
            blen = send(svif->sfd, buff, 1, 0);
            svif->sts = 20;
            time(&tlsec);  svif->rstime = tlsec;
            sFncSocdatOut("SND", buff, blen, idx);
        }
        f_sd = 1;
    }
    /* �������ꂽ�˗��f�[�^�̑��M���� */
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
                   "�˗��f�[�^(��������)���M: ME[%d]", svif->mecd);
            if(DbgFlg)  printf("�˗��f�[�^(����)���M: ME[%d]\n", svif->mecd);
/* printf("ircnt[%d] irmax[%d]\n",svif->iraifrm_cnt,svif->iraifrm_max); */
        }
    }
    else if(svif->sts == 9 || svif->sts == 15) {      /* EOT���M */
        buff[0] = 0x04;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts = 0;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("EOT���M...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 20) {                        /* NAK���M */
        buff[0] = 0x15;
        blen = send(svif->sfd, buff, 1, 0);
        svif->sts++;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", buff, blen, idx);
        if(DbgFlg)  printf("NAK���M...ME[%d]\n", svif->mecd);
    }
    else if(svif->sts == 30) {                        /* NAK��M��A���O�̈˗��f�[�^�đ� */
        blen = send(svif->sfd, FrmBuf[idx], Frbuf_len[idx], 0);
        svif->sts = 8;
        f_sd = 1;
        time(&tlsec);  svif->rstime = tlsec;
        sFncSocdatOut("SND", FrmBuf[idx], blen, idx);
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "�˗��f�[�^(�đ���)���M: ME[%d]", svif->mecd);
        if(DbgFlg)  printf("�˗��f�[�^(�đ���)���M: ME[%d]\n", svif->mecd);
    }

    return(f_sd);
}

/**/
static int sFncIraiSend(SVRINF *svif, int idx)
/******************************************************************************
*  �� �� ���@�FsFncIraiSend()                                                 *
*  �@�\�T�v�@�F����˗��\�P�b�g���M����                                       *
*  ���@�@�́@�F                                                               *
*  ��    ��    SVRINF *svif                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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


    /* rackid,rackpos�ɂ��˗��t�@�C������ */
    for(ii = 0 ; ii < 2 ; ii++) {
        if(ii == 0)       strcpy(b_tmp, NEWFL_SUFFIX);
        else if(ii == 1)  strcpy(b_tmp, SKNIRAI_SUFFIX);

        sprintf(fpth,"%s/%s%s_____%03d.%s", IRAINEW_PATH, IRAI_PREFIX, svif->rackid, atoi(svif->pos), b_tmp);
        if(DbgFlg)  printf("�˗��t�@�C���T�[�`: [%s%s_____%03d.%s]...", IRAI_PREFIX, svif->rackid, atoi(svif->pos), b_tmp);

        if(stat(fpth, &st) == 0 && st.st_size > 0) {
            if(DbgFlg)  printf("���݊m�F!!!\n");
            break;
        }
        else { if(DbgFlg)  printf("����!!!\n"); }
    }

    /* �˗��t�@�C����������Ȃ��Ƃ� */
    if(ii >= 2) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncIraiSend", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�˗��t�@�C����������܂���B\"�˗�����\"�̈˗�MSG���M File[%s] ME[%d] ERR[%d]", fpth, svif->mecd, errno);
        if(DbgFlg)  printf("\"�˗�����\"�̈˗�MSG���M File[%s] ME[%d] ERR[%d]\n", fpth, svif->mecd, errno);

        memset(SndBuf,'\0', SOCBUF_MAXSIZE);
        strcpy(SndBuf,"H|\\^&|LIS||||||||O|P|1");     /* �w�b�_REC���� */
        dcnt = 22;
        SndBuf[dcnt] = 0x0d;  dcnt++;

        strcpy((SndBuf+dcnt),"P|1");  dcnt = dcnt+3;  /* ����REC���� */
        SndBuf[dcnt] = 0x0d;  dcnt++;

        /* �u�˗������v�̑���˗�REC���� */
        (svif->meseqno)++;                            /* ����meseqno���J�E���g�A�b�v */
        sprintf((SndBuf+dcnt),"O|1|%s|||||||||P||^^^^7||S|||%06d^^|||||||O", svif->kenid, svif->meseqno);
        dcnt = dcnt + (strlen(svif->kenid) +43);
        SndBuf[dcnt] = 0x0d;  dcnt++;

        goto IRAISND;
    }


    /* �˗��t�@�C���I�[�v�� */
    if(NULL == (fp = fopen(fpth,"r"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncIraiSend", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ME[%d] ERR[%d]", fpth, svif->mecd, errno);
        if(DbgFlg)  printf("�˗��t�@�C���̃I�[�v���Ɏ��s���܂����BFile[%s] ME[%d] ERR[%d]\n", fpth, svif->mecd, errno);
        return(RTN_NG);
    }

    /* �˗��t�@�C���̗L�����R�[�h�����J�E���g */
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


    /* ����˗�MSG�̐��� */
    svif->iraifrm_cnt = svif->iraifrm_max = 0;
    memset(SndBuf,'\0', SOCBUF_MAXSIZE);
    strcpy(SndBuf,"H|\\^&|LIS||||||||O|P|1");              /* �w�b�_REC���� */
    dcnt = 22;
    SndBuf[dcnt] = 0x0d;  dcnt++;

    strcpy((SndBuf+dcnt),"P|1");   dcnt = dcnt+3;          /* ����REC���� */
    SndBuf[dcnt] = 0x0d;  dcnt++;
    sprintf((SndBuf+dcnt),"O|1|%s||", svif->kenid);        /* ����˗�REC���� */
    dcnt = dcnt + (strlen(svif->kenid) +6);

    f_fend = reccnt = wk_kenkaisu = 0;
    wk_kenid[0] = wk_kmcode[0] = buff[0] = '\0';
    ch_rireki[0] = '\0';                                   /* #01 �ǉ� */
    for( ; ; ) {
        if(NULL == fgets(fbuf, 512, fp))  break;
        if(fbuf[0] == '\n' || fbuf[0] == ' ' || fbuf[0] == '#')
            continue;
        if(strlen(fbuf) < 50)  continue;

        reccnt++;
        if(reccnt >= recmax)  f_fend = 1;                  /* �����R�[�h���ŏI�f�[�^ */

        /* �e�t�B�[���h�̏��� */
        c_st = c_en = c_dl = 0;
        for(ii = 0 ; ii < strlen(fbuf) ; ii++) {
            if(fbuf[ii] == ',')  {
                if(c_en > 0)  c_st = c_en+1;
                c_en = ii;  c_dl++;
            }
            else  continue;

            if(c_dl == 6) {                                /* ����(CH)�ݒ� */
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

                    for(jj = 0 ; jj < MstChanl_cnt ; jj++) {
                        if(MstChanl[jj].kmcode == atoi(wk_kmcode))
                            break;
                    }
                    if(jj >= MstChanl_cnt) {
                        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncIraiSend", __LINE__,
                            EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                            "�`���l���ԍ����}�X�^�Ɍ�����܂���B(�񑪒荀��) KM[%s] ME[%d]", wk_kmcode, svif->mecd);
                        if(DbgFlg)  printf("�`���l���ԍ����}�X�^�Ɍ�����܂���B(�񑪒荀��) KM[%s] ME[%d]\n", wk_kmcode, svif->mecd);

                        if(f_fend == 0)  break;

                        blen = strlen(buff);
                        if(buff[blen-1] == '\\')  buff[blen-1] = '|';
                        break;
                    }
                    else  wk_chnum = MstChanl[jj].chnum;

                    /* #01 ����`���l��No�𕡐����o�����ꍇ�́A�ŏ��̂��̂�ΏۂƂ��� */
                    sprintf(b_tmp,"%d", wk_chnum);
                    if(NULL != strstr(ch_rireki, b_tmp)) {      /* #01 ���Ɍ��o�ς݂̏ꍇ��Break */
                        if(f_fend == 0)  break;

                        blen = strlen(buff);
                        if(buff[blen-1] == '\\')  buff[blen-1] = '|';
                        break;
                    }

                    if(ch_rireki[0] == '\0')  strcpy(ch_rireki, b_tmp);
                    else  { strcat(ch_rireki,",");  strcat(ch_rireki, b_tmp); }
                }

                /* ���荀��(�`���l��)�̑g���� (��ߏ���"M"�t���ŏ������瑗�M) */
                if(f_fend == 0)  sprintf(b_tmp,"^^^%03d^M\\", wk_chnum);
                else             sprintf(b_tmp,"^^^%03d^M|",  wk_chnum);
                strcat(buff, b_tmp);
            }

            if(c_dl == 7) {                                /* �Č����f(�����񐔎擾) */
                memcpy(b_tmp, (fbuf+c_st), (c_en-c_st));
                b_tmp[(c_en-c_st)] = '\0';
                if(wk_kenkaisu < (short)atoi(b_tmp))  wk_kenkaisu = (short)atoi(b_tmp);
            }

            if(c_dl == 11) {                               /* �Č����f(�����H���敪)�擾 */
                memcpy(wk_kensphs, (fbuf+c_st), (c_en-c_st));
                wk_kensphs[(c_en-c_st)] = '\0';
            }

            if(c_dl == 13) {                               /* �˗���No.�擾 */
                memcpy(wk_ino, (fbuf+c_st), (c_en-c_st));
                wk_ino[(c_en-c_st)] = '\0';
                sFncTrim(wk_ino);
            }

            if(c_dl == 37) {                               /* ��ߏ����擾 */
                memcpy(b_tmp, (fbuf+c_st), (c_en-c_st));
                b_tmp[(c_en-c_st)] = '\0';
                sFncTrim(b_tmp);
                if(wk_kenkaisu > 1 && b_tmp[0] != '\0' && b_tmp[0] != '1') {
                    if(islower(b_tmp[0]))  b_tmp[0] = toupper(b_tmp[0]);

                    /* �Č�(���)�̏ꍇ�͊�ߏ�����ݒ肵�Ȃ��� */
                    if(DbgFlg)  printf("�Č��̊�ߏ������Đݒ� [%s]\n", b_tmp);
                    blen = strlen(buff);
                    buff[blen-2] = b_tmp[0];
                }
            }
        }

        if(f_fend == 1)  break;
    }
    fclose(fp);


    /* �A�N�V�����R�[�h�A�e��`��A���̍ޗ�("����"("S")�Œ�)�A */
    /* ���|�[�g�^�C�v���Œ�Őݒ� */
    blen = strlen(buff);
    (svif->meseqno)++;                                /* ����meseqno���J�E���g�A�b�v */
    sprintf((buff+blen),"||||||A||^^^^7||S|||%06d^%s^|||||||O", svif->meseqno, wk_ino);

 /* strcat(buff,"||||||A||^^^^7||S||||||||||O"); */
    blen = strlen(buff);
    strcpy((SndBuf+dcnt), buff);
    dcnt = dcnt + blen;
    SndBuf[dcnt] = 0x0d;  dcnt++;


  IRAISND:
    /* �I��MSG���� */
    strcpy((SndBuf+dcnt),"L|1|N");   dcnt = dcnt+5;
    SndBuf[dcnt] = 0x0d;  dcnt++;
    SndBuf[dcnt] = '\0';

    /* ���M�t���[���������� */
    memset(FrmBuf[idx],'\0', SOCBUF_MAXSIZE);
/*********
    if(svif->frmno >= 7)  frmnum = 0;
    else                  frmnum = svif->frmno +1;
*********/
    frmnum = 1;
    svif->frmno = 1;


    /* ���M�o�b�t�@�T�C�Y���m�F */
    if((dcnt+7) > SOCFRAME_MAXSIZE) {                      /* �ő�t���[�����𒴂���ꍇ */
        dcntmax = dcnt;
        fptr = sptr = dcnt = 0;
        frmb = FrmBuf[idx];

        /* �t���[�����ɍ��킹�đ��M�o�b�t�@�𕪊� */
        for(ii = 1 ; (ii*(SOCFRAME_MAXSIZE -7)) <= dcntmax ; ii++) {
            sprintf((frmb+fptr),"%c%d", 0x02, frmnum);
            memcpy((frmb+fptr+2), (SndBuf+sptr), (SOCFRAME_MAXSIZE -7));
            dcnt = dcnt + 2 + (SOCFRAME_MAXSIZE -7);
            frmb[dcnt] = 0x17;  dcnt++;                    /* "ETB"��ݒ� */

            sFncGetChecksum((frmb+fptr), dcnt, cksum);     /* �`�F�b�N�T���Z�o */
            sprintf((frmb+dcnt),"%s%c%c", cksum, 0x0d, 0x0a);
            dcnt = dcnt +4;

/* printf("ii[%d] dcnt[%d]\n",ii,dcnt); */
            fptr = ii * SOCFRAME_MAXSIZE;
            sptr = ii * (SOCFRAME_MAXSIZE -7);
            if(frmnum >= 7)  frmnum = 0;
            else             frmnum++;
        }

        /* �ŏI���M�t���[������ */
        svif->iraifrm_max = ii;                            /* ���M�t���[������ݒ� */
        sprintf((frmb+fptr),"%c%d", 0x02, frmnum);
        memcpy((frmb+fptr+2), (SndBuf+sptr), (dcntmax - ((ii-1)*(SOCFRAME_MAXSIZE -7))));
        dcnt = dcnt + 2 + (dcntmax - ((ii-1)*(SOCFRAME_MAXSIZE -7)));
        frmb[dcnt] = 0x03;  dcnt++;                        /* "ETX"��ݒ� */

        sFncGetChecksum((frmb+fptr), dcnt, cksum);         /* �`�F�b�N�T���Z�o */
        sprintf((frmb+dcnt),"%s%c%c", cksum, 0x0d, 0x0a);
        dcnt = dcnt +4;
        Frbuf_len[idx] = dcnt;

        /* �����t���[���̃\�P�b�g���M����(1�t���[����) */
        blen = send(svif->sfd, FrmBuf[idx], SOCFRAME_MAXSIZE, 0);
        time(&tlsec);
        svif->rstime = tlsec;
        svif->sts = 8;
        svif->iraifrm_cnt = 1;
        sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "�˗��f�[�^(����)���M: RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);
        if(DbgFlg)  printf("�˗��f�[�^(����)���M: RackID[%s] Pos[%s] ME[%d]\n", svif->rackid, svif->pos, svif->mecd);

/* printf("irmax[%d] ircnt[%d]\n",svif->iraifrm_max,svif->iraifrm_cnt); */

        /* ���M�f�[�^�̑ޔ� */
        sFncSocdatOut("SND", FrmBuf[idx], SOCFRAME_MAXSIZE, idx);

        return(RTN_OK);
    }

    /* �ȉ��͍ő�t���[�����𒴂��Ȃ��ꍇ */
    /* STX�A�t���[��No�AETX��t�� */
    sprintf(FrmBuf[idx],"%c%d%s%c", 0x02, frmnum, SndBuf, 0x03);
    dcnt = dcnt+3;
    svif->frmno = frmnum;

    /* �`�F�b�N�T���Z�o */
    sFncGetChecksum(FrmBuf[idx], dcnt, cksum);
    sprintf((FrmBuf[idx]+dcnt),"%s%c%c", cksum, 0x0d, 0x0a);
    Frbuf_len[idx] = dcnt+4;

    /* �\�P�b�g���M���� */
    blen = send(svif->sfd, FrmBuf[idx], Frbuf_len[idx], 0);
    time(&tlsec);
    svif->rstime = tlsec;
    svif->iraifrm_cnt = svif->iraifrm_max = 1;
    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
           "�˗��f�[�^���M: RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);
    if(DbgFlg)  printf("�˗��f�[�^���M: RackID[%s] Pos[%s] ME[%d]\n", svif->rackid, svif->pos, svif->mecd);

    /* ��ԃX�e�[�^�X�ݒ� */
    svif->sts = 8;

    /* ���M�f�[�^�̑ޔ� */
    sFncSocdatOut("SND", FrmBuf[idx], Frbuf_len[idx], idx);


/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static int sFncSocRecv(SVRINF *svif, int idx)
/******************************************************************************
*  �� �� ���@�FsFncSocRecv()                                                  *
*  �@�\�T�v�@�F�\�P�b�g�f�[�^��M���䏈��                                     *
*  ���@�@�́@�F                                                               *
*  ��    ��    SVRINF *svif                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    buff[11];
    int     blen, rtn, ptr;
    short   frmnum;
    time_t  tlsec;

    /* �\�P�b�g��M */
    memset(RcvBuf,'\0', (SOCFRAME_MAXSIZE +1));
    blen = recv(svif->sfd, RcvBuf, SOCFRAME_MAXSIZE, 0);
    time(&tlsec);
    svif->rstime = tlsec;
    if(blen > 0)
        sFncSocdatOut("RCV", RcvBuf, blen, idx);      /* �\�P�b�g�f�[�^�ޔ� */

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    if(blen == 1) {
        if((RcvBuf[0] & 0xff) == 0x06) {              /* ACK��M */
            svif->sts++;
            if(DbgFlg)  printf("ACK recvd...Server PORT[%d]\n", svif->svport);
        }
        else if((RcvBuf[0] & 0xff) == 0x05) {         /* ENQ��M */
            svif->sts = 1;
            if(DbgFlg)  printf("ENQ recvd...Server PORT[%d]\n", svif->svport);
        }
        else if((RcvBuf[0] & 0xff) == 0x04) {         /* EOT��M */
            svif->sts++;
            if(DbgFlg)  printf("EOT recvd...Server PORT[%d]\n", svif->svport);
        }
        else if((RcvBuf[0] & 0xff) == 0x17) {         /* NAK��M */
            if(svif->sts == 6)  svif->sts = 5;
            else                svif->sts = 30;
            if(DbgFlg)  printf("NAK recvd...Server PORT[%d]\n", svif->svport);
        }
    }
    else if(blen == 0) {
        if(DbgFlg)  printf("NULL Break....Connection down Port[%d]\n", svif->svport);
        sFncPutLog(TRCKIND_ERROR, __FILE__, "recv", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET�ڑ����_�E�����܂����BPort[%d] ERR[%d]", svif->svport, errno);
        close(svif->sfd);
        svif->sfd = -1;
        return(RTN_NG);
    }
    else if(blen < 0) {
        if(DbgFlg)  printf("Read error....Connection down Port[%d]\n", svif->svport);
        sFncPutLog(TRCKIND_ERROR, __FILE__, "recv", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "SOCKET�Ǎ��݃G���[���������܂����BPort[%d] ERR[%d]", svif->svport, errno);
        close(svif->sfd);
        svif->sfd = -1;
        return(RTN_NG);
    }
    else if(blen < 7) {                              /* #01 ���̑��s��MSG��M */
        if(DbgFlg)  printf("Invalid msg received....ME[%d] Port[%d] Len[%d]\n", svif->mecd, svif->svport, blen);
        sFncPutLog(TRCKIND_ERROR, __FILE__, "recv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
            "�s����MSG����M���܂����BME[%d] Port[%d] Len[%d]", svif->mecd, svif->svport, blen);
        svif->sts = 20;                               /* NAK���M�̂��߂�sts�ݒ� */
    }

    else {
/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */

        /* "ETB"�t���̕���MSG��M���̏���(���茋��MSG�Ɣ��f) */
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
                /* �t���[��No.�`�F�b�N(����MSG��M���̂�) */
                buff[0] = RcvBuf[1];  buff[1] = '\0';
                frmnum = (short)atoi(buff);
                if((frmnum == 0 && svif->rsltfrm_no != 7) ||
                   (frmnum > 0  && frmnum != (svif->rsltfrm_no +1))) {
                    sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncSocRecv", __LINE__,
                        EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                        "�t���[��No.���s�����ł��BFRMNo[%d] PrevNo[%s]", frmnum, svif->rsltfrm_no);
                    if(DbgFlg)  printf("�t���[��No.���s�����ł��BFRMNo[%d] PrevNo[%s]\n", frmnum, svif->rsltfrm_no);
                    svif->sts = 20;                   /* NAK���M�̂��߂�sts�ݒ� */
                    return(RTN_NG);
                }

                ptr = svif->rsltlen;
                memcpy((RBuf_rslt[idx]+ptr), (RcvBuf+2), (blen-7));
                svif->rsltlen = svif->rsltlen + blen -7;
            }
            svif->sts = 11;                           /* ����MSG��M����STS�ɂ���ACK��Ԃ� */
            return(RTN_OK);
        }
        else if((RcvBuf[blen-5] & 0xff) == 0x03 && svif->rsltsts > 0) {
            ptr = svif->rsltlen;
            memcpy((RBuf_rslt[idx]+ptr), (RcvBuf+2), (blen-2));
            blen = svif->rsltlen + blen -2;
            svif->sts = 11;

            rtn = sFncRcvdatProc(svif, RBuf_rslt[idx], blen);   /* �A���t���[���f�[�^���� */
            svif->rsltsts = 0;
            svif->rsltlen = 0;
        }

        /* ���������̎�M�t���[���f�[�^���� */
        else  rtn = sFncRcvdatProc(svif, RcvBuf, blen);

        if(rtn == RTN_NG)  svif->sts = 20;            /* NAK���M�̂��߂�sts�ݒ� */
    }

/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8 */
    return(RTN_OK);
}

/**/
static int sFncRcvdatProc(SVRINF *svif, char *rbuf, int blen)
/******************************************************************************
*  �� �� ���@�FsFncRcvdatProc()                                               *
*  �@�\�T�v�@�F�\�P�b�g��M�t���[���f�[�^��͏���                             *
*  ���@�@�́@�F                                                               *
*  ��    ��    SVRINF *svif                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
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

    /* ��M�o�b�t�@����STX�̈ʒu���T�[�` */
    if((rbuf[0] & 0xff) != 0x02) {                    /* �擪��STX���ǂ����𔻒f */
        for(ii = 0 ; ii < blen ; ii++) {
            if((rbuf[ii] & 0xff) == 0x02) {           /* STX�̈ʒu���T�[�` */
                rbuf = (rbuf +ii);  break;
            }
        }
    }
    buff[0] = rbuf[1];  buff[1] = '\0';
    svif->frmno = atoi(buff);

    /* CHKSUM�`�F�b�N (�A���t���[���ȊO�̏ꍇ�Ɏ��s) */
    if(blen <= SOCFRAME_MAXSIZE) {
        sFncGetChecksum(rbuf, blen, cksum);
        if(memcmp((rbuf+blen-4), cksum, 2) != 0) {
            memcpy(buff, (rbuf+blen-4), 2);  buff[2] = '\0';
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "�`�F�b�N�T�����s�����ł��BCKSUM[%s] Calc[%s]", buff, cksum);
            if(DbgFlg)  printf("�`�F�b�N�T�����s�����ł��BCKSUM[%s] Calc[%s]\n", buff, cksum);
            return(RTN_NG);
        }
    }


    /* �w�b�_���R�[�h��� */
    msgknd[0] = '\0';
    f_hdr = c_st = 0;
    for(ii = 2 ; ii < blen ; ii++) {
        if(rbuf[ii] == '|')  { c_dl++;  continue; }   /* �e���R�[�h���̃f���~�^���J�E���g */
        if(f_hdr == 0) {
            if(rbuf[ii] == 'H')  { f_hdr = 1;  c_dl = 0;  continue; }
        }
        else if(f_hdr == 1) {
            if(c_dl == 10 && msgknd[0] == '\0') {     /* MSG��ʂ��擾 */
                msgknd[0] = rbuf[ii];  continue;
            }
            if((rbuf[ii] & 0xff) == 0x0d)  { c_st = ii+1;  break; }
        }
    }
if(DbgFlg)  printf("msgknd[%c]\n",msgknd[0]);


    /* �⍇��MSG�̏��� */
    if(msgknd[0] == 'Q') {
        if(rbuf[c_st] != 'Q') {                       /* MSG��ʂ̕s������ */
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "MSG��ʂ��s�����ł��BMknd[%c] Mtyp[%c]", msgknd[0], rbuf[c_st]);
            if(DbgFlg)  printf("MSG��ʂ��s�����ł��BMknd[%c] Mtyp[%c]\n", msgknd[0], rbuf[c_st]);
            return(RTN_NG);
        }

        /* rackid, rackpos�擾 */
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
               "�⍇����M: RackID[%s] Pos[%s] ME[%d]", wk_rackid, wk_pos, svif->mecd);
        if(DbgFlg)  printf("�⍇����M: RackID[%s] Pos[%s] ME[%d]\n", wk_rackid, wk_pos, svif->mecd);
        sprintf(svif->rackid,"%s", wk_rackid);
        sprintf(svif->pos,"%03d", atoi(wk_pos));
        svif->sts = 3;
    }


    /* ���茋��MSG�̏��� */
    else if(msgknd[0] == 'R') {
        if(rbuf[c_st] == 'L') {                       /* ���ʂ���MSG�̂Ƃ� */
            sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "��̌���MSG����M: RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);
            if(DbgFlg)  printf("��̌���MSG����M RackID[%s] Pos[%s] ME[%d]", svif->rackid, svif->pos, svif->mecd);

            svif->sts = 11;
            return(RTN_OK);
        }
        else if(rbuf[c_st+4] != 'O') {                /* MSG��ʂ̕s������ */
            sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                   EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                   "MSG��ʂ��s�����ł��BMknd[%c] Mtyp[%c]", msgknd[0], rbuf[c_st]);
            if(DbgFlg)  printf("MSG��ʂ��s�����ł��BMknd[%c] Mtyp[%c]\n", msgknd[0], rbuf[c_st+4]);

            return(RTN_NG);
        }

        /* ����No.�擾 (O���R�[�h���) */
        c_st = c_st+8;                                /* ����ID�̐擪�ɃZ�b�g */
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
                   "����No.(���b�NID, POS)�̎擾�Ɏ��s���܂����BOrec[%s]", buff);
            if(DbgFlg)  printf("����No.(���b�NID, POS)�̎擾�Ɏ��s���܂����BOrec[%s]\n", buff);
            return(RTN_NG);
        }

        /* O���R�[�h�̃��[�U�t�B�[���h���MeSEQNo.�擾 */
        if(strncmp(wk_kenid,"QC", 2) != 0) {
            c_en = c_dl = 0;
            wk_usrfield[0] = buf2[0] = '\0';
            for(ii = c_st ; ii < blen ; ii++) {       /* ����ID�̐擪����X�^�[�g */
                if(rbuf[ii] == '|') {
                    if(c_en > 0)  c_st = c_en+1;
                    c_en = ii;  c_dl++;
                }
                else  continue;

                if(c_dl == 17) {                      /* ���[�U�t�B�[���h */
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
                    "����MSG����̕��͋@SEQ�擾�Ɏ��s�BUserField[%s]", wk_usrfield);
                if(DbgFlg)  printf("����MSG����̕��͋@SEQ�擾�Ɏ��s�BUserField[%s]\n", wk_usrfield);

                svif->sts = 11;
                return(RTN_SKIP);
            }
        }


        for(ii = c_st ; ii < blen ; ii++) {           /* R���R�[�h�̓��o�� */
            if((rbuf[ii] & 0xff) == 0x0d) {
                c_st = ii+1;  break;
            }
        }

        /* ���茋�ʂ̎擾 (�S�Ă�R���R�[�h���) */
        c_dl = c_en = rseq = 0;
        c_res = 1;
        for(ii = c_st ; ii < blen ; ii++) {
            if(rbuf[ii] == '|') {
                if(c_en > 0)  c_st = c_en+1;
                c_dl++;  c_en = ii;
            }
            else if((rbuf[ii] & 0xff) == 0x0d) {      /* �X��R���R�[�h�̍Ō�����o */
                if(rbuf[ii+1] == 'L')  break;
                c_res++;  c_dl = 0;  c_en = ii;  continue;
            }
            else  continue;

            if(c_dl == 2) {                           /* R���R�[�h��Seq�`�F�b�N */
                memcpy(buff, (rbuf+c_st), (c_en-c_st));
                buff[(c_en-c_st)] = '\0';  sFncTrim(buff);

                if(atoi(buff) != (rseq +1)) {
                    sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncRcvdatProc", __LINE__,
                           EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                           "R���R�[�h��SEQNo.���s�����ł��BKenid[%s] RSeq[%d] PrevNo[%d]", wk_kenid, atoi(buff), rseq);
                    if(DbgFlg)  printf("R���R�[�h��SEQNo.���s�����ł��BKenid[%s] RSeq[%d] PrevNo[%d]\n", wk_kenid, atoi(buff), rseq);
                }
                rseq = atoi(buff);
            }
            else if(c_dl == 3) {                      /* �`���l��No.�擾 */
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
            else if(c_dl == 4) {                      /* ���ʒl�擾 */
                memcpy(wk_kekka, (rbuf+c_st), (c_en-c_st));
                wk_kekka[(c_en-c_st)] = '\0';   sFncTrim(wk_kekka);
            }
            else if(c_dl == 5) {                      /* ���ʒl�P�ʎ擾 */
                memcpy(wk_unit, (rbuf+c_st), (c_en-c_st));
                wk_unit[(c_en-c_st)] = '\0';    sFncTrim(wk_unit);
            }
            else if(c_dl == 7) {                      /* ���ʈُ�t���O�擾 */
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

                /* �����̕��͋@�G���[��M�̍ۂ̕������� */
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


                /* �R���g���[�����̂̏ꍇ�A�R���g���[���t���O��ݒ� */
                if(strncmp(wk_kenid,"QC", 2) == 0) {
/******************
                    ctlnum = svif->ctlno;
                    if(svif->ctlflg == 0)  { svif->ctlflg = 1;  ctlnum++; }
******************/
                    (svif->ctlno)++;

                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                           EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                           "�R���g���[�����ʎ�M: KenID[%s] CH[%s] ME[%d] No[%d]", wk_kenid, wk_chnum, svif->mecd, svif->ctlno);
                    if(DbgFlg)  printf("Ctl���ʎ�M: KenID[%s] CH[%s] ME[%d] No[%d]\n", wk_kenid, wk_chnum, svif->mecd, svif->ctlno);
                }
                else {
                    /* �R���g���[���t���O��"1"�̂Ƃ���ctlno���J�E���g�A�b�v */
/******************
                    if(svif->ctlflg == 1)  { svif->ctlflg = 0;  (svif->ctlno)++; }
******************/

                    sFncPutLog(TRCKIND_TRACE, __FILE__, "", __LINE__,
                           EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                           "���茋�ʎ�M: KenID[%s] CH[%s] ME[%d]", wk_kenid, wk_chnum, svif->mecd);
                    if(DbgFlg)  printf("���茋�ʎ�M: KenID[%s] CH[%s] ME[%d]\n", wk_kenid, wk_chnum, svif->mecd);
                }
if(DbgFlg)  printf("KEN[%s] CH[%s]\n",wk_kenid,wk_chnum);


                /* ���ʃf�[�^���ꎞ�t�@�C���ɏo�� */
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
*  �� �� ���@�FsFncKekSave()                                                  *
*  �@�\�T�v�@�F���茋�ʂ̎�M�f�[�^�̃t�@�C���o�͏���                         *
*  ���@�@�́@�F                                                               *
*  ��    ��    SVRINF *svif                                                   *
*              char   *wk_ken;                                                *
*              char   *wk_ch;                                                 *
*              char   *wk_kek;                                                *
*              char   *err1;                                                  *
*              char   *err2;                                                  *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F  0     : ����                                                 *
* �@�@�@�@�@�@�@-1     : ���s                                                 *
******************************************************************************/
{
    char    fpth[256], fnm[101], buff[31];
    int     ii, ctlnum;
    FILE    *fp;
    struct stat st;
    struct tm  *tms;

    /* �ޔ��t�@�C�����̌��� */
    if(strncmp(wk_ken,"QC", 2) == 0) {                /* �R���g���[������ */
     /* ctlnum = svif->ctlno +1; */
        sprintf(fnm,"%d_QCK%.10s_%s_%d.dat", sAppEnv.lineno, wk_ken, wk_ch, svif->ctlno);
        sprintf(fpth,"%s/%s", KEKKATMP_PATH, fnm);
    }
    else {                                            /* ��ʌ��̂̏ꍇ */
        sprintf(fnm,"%d_KEK%s___%s_%s.dat", sAppEnv.lineno, wk_rack, wk_pos, wk_ch);
        sprintf(fpth,"%s/%s", KEKKATMP_PATH, fnm);
    }
if(DbgFlg)  printf("fpth[%s]\n",fpth);

    /* �o�̓t�@�C�����d�����đ��݂���ꍇ */
    if(stat(fpth, &st) == 0) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKekSave", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "���ʏo�͈ꎞ�t�@�C�������ɑ��݂��Ă��܂��BFILE[%s]", fnm);
        if(DbgFlg)  printf("���ʏo�͈ꎞ�t�@�C�������ɑ��݂��Ă��܂��BFILE[%s]\n", fnm);
        return(RTN_NG);
    }

    if(NULL == (fp = fopen(fpth,"w"))) {
        sFncPutLog(TRCKIND_ERROR, __FILE__, "sFncKekSave", __LINE__,
               EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
               "���ʏo�͈ꎞ�t�@�C���̃I�[�v���Ɏ��s�BFILE[%s] ERR[%d]", fnm, errno);
        if(DbgFlg)  printf("���ʏo�͈ꎞ�t�@�C���̃I�[�v���Ɏ��s�BPATH[%s] ERR[%d]\n", fpth, errno);
        return(RTN_NG);
    }

    /* �`���l��No.���獀�ڃR�[�h����� */
    for(ii = 0 ; ii < MstChanl_cnt ; ii++) {
        if(MstChanl[ii].chnum == atoi(wk_ch))
            break;
    }

    if(NULL != (tms = localtime(&(svif->rstime)))) {
        sprintf(buff,"%d-%02d-%02d %02d:%02d:%02d",
                (tms->tm_year +1900), (tms->tm_mon +1), tms->tm_mday,
                tms->tm_hour, tms->tm_min, tms->tm_sec);
    }


    /* ���茋�ʂ��ꎞ�t�@�C���ɏo�� */
    ctlnum = svif->ctlno;
    if(strncmp(wk_ken,"QC", 2) == 0) {
     /* ctlnum++; */                                  /* Ctl���ʂł̓J�E���g�A�b�v���Ȃ����߁A�����ŎZ�o */
        svif->rmsg_meseq = 0;                         /* Ctl���ʂł͕��͋@No.��"0" */
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
*  �� �� ���@�FsFncSocdatOut()                                                *
*  �@�\�T�v�@�F�\�P�b�g����M�f�[�^�ޔ�����                                   *
*  ���@�@�́@�F                                                               *
*  ��    ��    char   *svbuf;                                                 *
*              int    blen;                                                   *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
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

    /* Raw�f�[�^�̑ޔ� */
    memcpy((buff+len), svbuf, blen);
    buff[(blen+len)] = '\0';
    write(fd, buff, (blen+len));
    if(blen == 1)  write(fd,"\n", 1);

    /* �ҏW�f�[�^�̏o�� */
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
*  �� �� ���@�FsFncGetChecksum()                                              *
*  �@�\�T�v�@�F�`�F�b�N�T����������                                           *
*  ���@�@�́@�F                                                               *
*  ��    ��    char   *socbuf;                                                *
*              char   *cksum;                                                 *
*  �o�@�@�́@�F                                                               *
*  ���A���@�F                                                               *
******************************************************************************/
{
    int     calc, ii;

    calc = -1;
    for(ii = 0 ; ii < imax ; ii++) {
        if(sbuf[ii] == 0x02)  continue;               /* STX�͏��O */

        if(calc == -1) {
              calc = (int)sbuf[ii] + (int)sbuf[ii+1];  ii++;
        }
        else  calc = calc + (int)sbuf[ii];

        calc = calc % 256;

        if(sbuf[ii] == 0x03 || sbuf[ii] == 0x17)      /* ETB or ETX�܂ŏ���������break */
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
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̍쐬�Ɏ��s���܂��� ERR[%d]", errno ) ;
        if(DbgFlg)  printf("���L�������̍쐬�Ɏ��s���܂��� ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  �A�^�b�`
    shmData = ( int * ) shmat ( pAppEnv->shm_Id, 0 , 0 ) ;
    if ( shmData == ( int * )-1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃A�^�b�`�Ɏ��s���܂��� ERR[%d]", errno ) ;
        if(DbgFlg)  printf("���L�������̃A�^�b�`�Ɏ��s���܂��� ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  �l�ݒ�
    *shmData = 0 ;

    //  �f�^�b�`
    if ( shmdt ( shmData ) == -1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃f�^�b�`�Ɏ��s���܂��� ERR[%d]", errno ) ;
        if(DbgFlg)  printf("���L�������̃f�^�b�`�Ɏ��s���܂��� ERR[%d]\n", errno);
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
        if(DbgFlg)  printf("���L�������̎擾�Ɏ��s���܂��� ERR[%d]\n", errno);
        return(RTN_NG);
    }

    //  �A�^�b�`
    shmData = ( int * )shmat(pAppEnv->shm_Id, 0 , 0);
    if ( shmData == ( int * )-1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃A�^�b�`�Ɏ��s���܂��� ERR[%d]", errno ) ;
        if(DbgFlg)  printf("���L�������̃A�^�b�`�Ɏ��s���܂��� ERR[%d]\n", errno);
        return ( RTN_NG ) ;
    }

    //  �l�ݒ�
    *pshmData = *shmData ;

/****************
    if(DbgFlg) {
        printf("���L������[GET] shmKey[%d] ID[%d] Data[%d] Add[%x]\n",
               pAppEnv->shm_Key, pAppEnv->shm_Id, *shmData, shmData);
    }
****************/

    //  �f�^�b�`
    if ( shmdt ( shmData ) == -1 ) {
        //  �ُ�I��    LOG
        sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                     "���L�������̃f�^�b�`�Ɏ��s���܂��� ERR[%d]", errno ) ;
        if(DbgFlg)  printf("���L�������̃f�^�b�`�Ɏ��s���܂��� ERR[%d]\n", errno);
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

    if(DbgFlg)  printf("���L������[DEL] shmKey[%d] ID[%d]\n", pAppEnv->shm_Key, pAppEnv->shm_Id);

    //  �폜
    if ( shmctl ( pAppEnv->shm_Id, IPC_RMID, NULL) < 0 ) {
        return ( RTN_NG ) ;
    }
    return ( RTN_OK ) ;
}

/**/
static void sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName, int plLineNo, char *pcExeFlg, char *pcErrCode, char *pcfmt, ... )
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
