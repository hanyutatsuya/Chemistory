/* ��������
 2020.05.26 #01 ����  ���L��"KEKKAERR_PATH"�̐ݒ��ǉ�

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


/* �����I�[�_�[�Ɋ܂܂�鑮���Ɋւ��鍀�ڂ̃o�C�g �T�C�Y                    */
#define FLDSIZE_SC         ((size_t)5)  /* �g�� (cm)                        */
#define FLDSIZE_TJ         ((size_t)5)  /* �̏d                             */
#define FLDSIZE_TJTNI      ((size_t)1)  /* �̏d�敪                         */
#define FLDSIZE_TNTME      ((size_t)4)  /* �~�A����                         */
#define FLDSIZE_TNTNI      ((size_t)1)  /* �~�A���ԋ敪                     */
#define FLDSIZE_TNRYO      ((size_t)5)  /* �~�A��                           */
#define FLDSIZE_TNRYOTNI   ((size_t)1)  /* �~�A�ʋ敪                       */
#define FLDSIZE_SBTKBN     ((size_t)1)  /* ���ʋ敪                         */
#define FLDSIZE_AGE        ((size_t)3)  /* �N��                             */
#define FLDSIZE_AGEKBN     ((size_t)1)  /* �N��敪                         */

/* �����I�[�_�[�̃t�@�C�� (CSV �`��) �Ɋ܂܂�鑮�����̈ʒu               */
#define FLDIDX_SC                 (40)  /* �g�� (cm)                        */
#define FLDIDX_TJ                 (41)  /* �̏d                             */
#define FLDIDX_TJTNI              (42)  /* �̏d�敪                         */
#define FLDIDX_TNTME              (50)  /* �~�A����                         */
#define FLDIDX_TNTNI              (51)  /* �~�A���ԋ敪                     */
#define FLDIDX_TNRYO              (52)  /* �~�A��                           */
#define FLDIDX_TNRYOTNI           (53)  /* �~�A�ʋ敪                       */
#define FLDIDX_SBTKBN             (43)  /* ���ʋ敪                         */
#define FLDIDX_AGE                (46)  /* �N��                             */
#define FLDIDX_AGEKBN             (47)  /* �N��敪                         */

/* �P�ʓ����������ڂɊi�[����鎯�ʎq                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* �~�A����: ���ԒP��               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* �~�A����: ���P��                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* �~�A����: ���ԒP�ʕs��           */
#define _VALUE_TNRYO_MILLILITER ('0')   /* �~�A��: �~�� ���b�g���P��        */
#define _VALUE_TNRYO_LITER      ('1')   /* �~�A��: ���b�g���P��             */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* �~�A��: �ʒP�ʕs��               */
#define _VALUE_TJTNI_GRAM       ('1')   /* �̏d: �O�����P��                 */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* �̏d: �L���O�����P��             */
#define _VALUE_SBTKBN_MALE      ('0')   /* ����: �j��                       */
#define _VALUE_SBTKBN_FEMALE    ('1')   /* ����: ����                       */
#define _VALUE_SBTKBN_UNKNOWN   ('9')   /* ����: ���ʕs��                   */
#define _VALUE_AGEKBN_YEAR      ('Y')   /* �N��: �N��                       */

/* �v�Z���Ɋ܂܂�鑮�����̒l�ɒu������w��                               */
#define KSNSK_TNTME     ('N')           /* �~�A���� (���ԒP��)              */
#define KSNSK_TNRYO     ('R')           /* �~�A�� (�~�� ���b�g���P��)       */
#define KSNSK_SC        ('T')           /* �g��                             */
#define KSNSK_TJ        ('W')           /* �̏d (�O�����P��)                */
#define KSNSK_SBTKBN    ('S')           /* ���ʋ敪                         */
#define KSNSK_AGE       ('A')           /* �N��                             */


/* �V�X�e���p�����[�^�i�[�\���� */
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
    char    path[101];                                /* ���ʈꎞ�t�@�C���̃t���p�X */
    char    fname[51];                                /* ���ʈꎞ�t�@�C���̃t�@�C���� */
    char    rackid[13];                               /* ���ʈꎞ�t�@�C��������擾�������b�NID */
    short   pos;                                      /* ���ʈꎞ�t�@�C��������擾�������b�N���ʒu */
    short   chnum;                                    /* ���ʈꎞ�t�@�C��������擾�����`���l��No. */
    char    irfnm[51];                                /* �Y������˗��t�@�C���� */
    char    kengrp[16 +1];                            /* ���肵���˗���񂩂�̌����O���[�v */
    int     kmcode;                                   /* ���肵���˗���񂩂�̍��ڃR�[�h */
    char    kessei_km[7 +1];                          /* ���肵���˗���񂩂�̌������ڃR�[�h */
    short   c_kensa;                                  /* ���肵���˗���񂩂�̌����� */
    char    kensaphs[1 +1];                           /* ���肵���˗���񂩂�̌����H���敪 */
    char    usercode[7 +1];                           /* ���肵���˗���񂩂�̎{�݃R�[�h */
    char    ino[11 +1];                               /* ���肵���˗���񂩂�̈˗���No. */
    char    kenno[13 +1];                             /* ���肵���˗���񂩂�̌���No. */
    char    line_kenno[11 +1];                        /* Line�p�˗������̌���No. */
    char    kenid[30 +1];                             /* ���ʈꎞ�t�@�C������擾��������ID (RackID+POS) */
    char    zaicode[4 +1];                            /* ���肵���˗���񂩂�̍ޗ��R�[�h */
    char    sex[1 +1];                                /* ���肵���˗���񂩂�̐��ʃR�[�h */
    char    rstime[21];                               /* ���ʈꎞ�t�@�C������擾�������ʎ�M���� */
    short   mecd;                                     /* ���ʈꎞ�t�@�C������擾�������͋@No. */
    int     meseqno;                                  /* ���ʈꎞ�t�@�C������擾�������͋@SEQNo. */
    char    kekka[12 +1];                             /* ���ʈꎞ�t�@�C������擾�������茋��(�ۂߌ�) */
    char    raw[12 +1];                               /* ���ʈꎞ�t�@�C������擾�������茋�� */
    char    errcd1[2 +1];
    char    errcd2[30 +1];
    int     ctlno;
    short   qcflg;
    short   sts;                                      /* 1:���荀�ڑ����ρA2:���CHK�ρA3:RNG CHK�ς� */
    char    meerrsts[2 +1];
    short   meerrprc;
    char    kisyak_sts[1 +1];
    short   kisyak_err;
    char    cksts[3];
    short   f_saiken;                                 /* �Č����{�t���O */
    short   f_calc;
    short   f_kessei;                                 /* �������ڃt���O (1:����, 2:���H) */
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
/* �`���l���}�X�^�i�[�\���� */
typedef struct {
    char    mekbn[4 +1];
    short   chnum;
    char    chname[16 +1];
    int     kmcode;
} CHLMST;

/* �v�Z���ڃ}�X�^�i�[�\���� */
typedef struct {
    char    kengrp[16 +1];
    int     kmcode;
    char    usercode[7 +1];
    char    zaicode[4 +1];
    char    calc[128 +1];
} CALCMST;

/* ��ߔ{���}�X�^�i�[�\���� */
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

/* �͈̓`�F�b�N�}�X�^�i�[�\���� */
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

/* �֘A���ڃ}�X�^�i�[�\���� */
typedef struct {
    int     kmcode;
    int     kanrenkm;
} KANRENMST;

/* ���͋@�X�e�[�^�X�i�[�\���� */
typedef struct {
    char    zscode[2 +1];
    char    trcode[1 +1];
    short   procf;
    char    skncond[1 +1];
    int     pri;
} MESTSMST;

/* ���ڃ}�X�^�i�[�\���� */
typedef struct {
    char    kengrp[16 +1];
    int     kmcode;
    int     place;                          /* �����_���� */
} KMMST;

/* �R���g���[���}�X�^�i�[�\���� */
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

/* IF �u���b�N���v�f�����\���� (char** �Ƃ��Ă��Q�Ɖ\)                    */
struct _IFBLOCK {
    char *pszConditionLeft;             /* ������ (��r���Z�q) ����         */
    char *pszOperator;                  /* �������̔�r���Z�q               */
    char *pszConditionRight;            /* ������ (��r���Z�q) �E��         */
    char *pszValueTrue;                 /* ���������^�̏ꍇ�ɓK�p����l     */
    char *pszValueFalse;                /* ���������U�̏ꍇ�ɓK�p����l     */
    char *pszEndOfList;                 /* ���̍\���̂� char** �Ƃ��ĎQ�Ƃ�
                                           ��ꍇ�� End Of List             */
};

