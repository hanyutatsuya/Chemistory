/****************************************************************************
 * KSNSK_if.c : �v�Z�������� IF �u���b�N�W�J
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "KSNSK_if.h"

/* ���̃t�@�C�����ɑ��݂���֐�                                             */
char *OperateKSNSK(const char *);
char *GetIFBlock(const char *);
struct _IFBLOCK *SplitIFBlockItems(char *);
int IsFormula(const char *);
void freeIFBLOCK(struct _IFBLOCK *);

/* ���̃t�@�C���̊֐��Ăяo������ (�����炭) ���݂���֐�                   */
extern double StringCal(char *);

/* common_str.c ���̔ėp�֐�                                                */
extern char *_replace(const char *, const char *, const char *);
extern char *_strchain(const char *, const char *);
extern char *_strndup(const char *, size_t);
extern char *_touppercase(const char *);
extern char *_strrstr(char *, const char *);

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
char *OperateKSNSK(const char *pszKSNSK)
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

    if (NULL != (void *) (pszFormular = 
                          _touppercase(_replace(pszKSNSK,
                                                szBlank,
                                                (char *) NULL)))) {
        if (!nErrorOccured && NULL != (void *) pszFormular) {
            if (!IsFormula(pszFormular)) {
                nErrorOccured = TRUE;   /* �v�Z���Ƃ��Ĉُ�                 */
            }
        }

        while (!nErrorOccured && 
               NULL != (void *) (pszIFBlock = GetIFBlock(pszFormular))) {
            if (NULL == (void *) (pstItems = SplitIFBlockItems(pszIFBlock))) {
                nErrorOccured = TRUE;   /* IF �u���b�N���̗v�f�������s      */
            }
            else if (NULL == (void *) pstItems->pszConditionLeft ||
                     NULL == (void *) pstItems->pszOperator ||
                     NULL == (void *) pstItems->pszConditionRight ||
                     NULL == (void *) pstItems->pszValueTrue ||
                     NULL == (void *) pstItems->pszValueFalse) {
                nErrorOccured = TRUE;   /* IF �u���b�N���̗v�f�������s      */
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
                    nErrorOccured = TRUE;
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

                if (NULL == (void *) pszReplace) {
                    nErrorOccured = TRUE;
                                        /* IF �u���b�N �� �K�p�l�ϊ����s    */
                }
                else {
                    free((void *) pszFormular);
                    pszFormular = pszReplace;
                }
            }
            if (NULL != (void *) pszIFBlock) {
                free((void *) pszIFBlock);
            }
            freeIFBLOCK(pstItems);
        }
    }

    if (!nErrorOccured && NULL != (void *) pszFormular) {
        if (!IsFormula(pszFormular)) {
            nErrorOccured = TRUE;       /* �v�Z���Ƃ��Ĉُ�                 */
        }
    }

    if (nErrorOccured && NULL != pszFormular) {
        free((void *) pszFormular);
        pszFormular = (char *) NULL;
    }
    return (pszFormular);
}

/*--------------------------------------------------------------------------*
 * GetIFBlock
 *
 * �v�Z���Ɋ܂܂�� IF �u���b�N������𒊏o���܂��B
 *
 * Paramter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      �����Ŏw�肷�镶����́A IF �u���b�N���܂ތv�Z���̕�
 *                      ����ł��B
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
char *GetIFBlock(const char *pszOriginal)
{
    static char szIFBlock[] = STR_BEGIN_IFBLOCK;

    char *pszResult = NULL;             /* �߂�l                           */
    char *pszIFBlock;                   /* IF �u���b�N�J�n�ʒu              */
    size_t ulOriginal;                  /* ���̕�����̒���                 */
    char *pszFind;                      /* IF �u���b�N�I�[����              */
    int nParenthesis = 0;               /* ���ʂ̊K�w�k�x                   */
    int nComma;                         /* �J���}�̐�                       */
    BOOL nTarminate;                    /* IF �u���b�N�I�[���o              */

    if (NULL != (void *) pszOriginal) {
        if ((size_t) 0 <= (ulOriginal = strlen(pszOriginal))) {
            if (NULL != (void *) (pszIFBlock = _strrstr((char *) pszOriginal,
                                                        (const char *) szIFBlock))) {
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
int IsFormula(const char *pszKSNSK)
{
    BOOL bResult = FALSE;
    char *pszFormular;
    char *pszReplace;
    int nIndex;
    int nParenthesis = 0;               /* ���ʂ̊K�w�k�x                   */

    if (NULL != (void *) (pszFormular = 
                          _touppercase(_replace(pszKSNSK,
                                                " ",
                                                (char *) NULL)))) {

        /* �Z�p�֐��̏���                                                   */
        if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_IFBLOCK,
                                                    (char *) NULL))) {
            free((void *) pszFormular);
            pszFormular = pszReplace;

            if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                        ",",
                                                        (char *) NULL))) {
                free((void *) pszFormular);
                pszFormular = pszReplace;
            }

            /* ���������̔�r���Z�q����                                     */
            if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                        "<",
                                                        (char *) NULL))) {
                free((void *) pszFormular);
                pszFormular = pszReplace;
            }
            if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                        ">",
                                                        (char *) NULL))) {
                free((void *) pszFormular);
                pszFormular = pszReplace;
            }
            if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                        "=",
                                                        (char *) NULL))) {
                free((void *) pszFormular);
                pszFormular = pszReplace;
            }
        }
        if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_LOG10,
                                                    (char *) NULL))) {
            free((void *) pszFormular);
            pszFormular = pszReplace;
        }
        if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_LOG,
                                                    (char *) NULL))) {
            free((void *) pszFormular);
            pszFormular = pszReplace;
        }
        if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                    STR_BEGIN_POW,
                                                    (char *) NULL))) {
            free((void *) pszFormular);
            pszFormular = pszReplace;
            if (NULL != (void *) (pszReplace = _replace(pszFormular,
                                                        ",",
                                                        (char *) NULL))) {
                free((void *) pszFormular);
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
        free((void *) pszFormular);

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

    if (NULL == (void *) pszOrigin) {
        pstResult = (struct _IFBLOCK *) NULL;
    }
    else if (NULL != (void *) (pstResult = 
                               (struct _IFBLOCK *) malloc(sizeof(struct _IFBLOCK)))) {
        for (nIndex = 0; MAXCNT_ITEM_IFBLOCK >= nIndex; nIndex++) {
            *((void **) pstResult + nIndex) = NULL;
        }
        for (nErrorOccured = FALSE, nTerminate = FALSE, 
                 nIndex = 0, nParenthesis = 0,
                 pszBegin = pszTarget = (strchr(pszOrigin, '(') + 1);
             !nErrorOccured && !nTerminate && 
                 NULL != (void *) pszTarget && _EOS != (int) *pszTarget;
             pszTarget++) {

            switch ((int) *pszTarget) {
            case PARENT_BEGIN:          /* �J�b�R (�J�n)                    */
                nParenthesis++;
                break;

            case PARENT_END:            /* �J�b�R (�I��)                    */
                nParenthesis--;
                if (0 > nParenthesis) {
                    if (NULL == (void *) pstResult->pszValueTrue ||
                        NULL == (void *) pstResult->pszConditionRight) {
                        nErrorOccured = TRUE;
                                        /* IF �u���b�N�̏I�������� ')' ����
                                           �o�������A�K�{���ڂ��s�����Ă��� */
                    }
                    else if (NULL == (void *) (pstResult->pszValueFalse = 
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
                    NULL != (void *) pstResult->pszConditionLeft) {
                    nErrorOccured = TRUE;
                }
                else if (NULL == (void *) (pstResult->pszConditionLeft = 
                                           _strndup(pszBegin,
                                                    (size_t) (pszTarget - pszBegin)))) {
                    nErrorOccured = TRUE;
                }
                else if (OPERATOR_LT == (int) *pszTarget &&
                         OPERATOR_GT == (int) *(pszTarget + 1)) {
                    if (NULL == (void *) (pstResult->pszOperator = strdup(szNE))) {
                        nErrorOccured = TRUE;
                    }
                    else {
                        pszTarget++;
                        pszBegin = pszTarget;
                        pszBegin++;
                    }
                }
                else if (NULL == (void *) (pstResult->pszOperator =
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
                else if (NULL == (void *) pstResult->pszConditionRight) {
                    /* �������E�� - ���������^�̏ꍇ�ɓK�p����l            */
                    if (NULL == (void *) (pstResult->pszConditionRight = 
                                          _strndup(pszBegin,
                                                   (size_t) (pszTarget - pszBegin)))) {
                        nErrorOccured = TRUE;
                    }
                    else {
                        pszBegin = pszTarget;
                        pszBegin++;
                    }
                }
                else if (NULL == (void *) pstResult->pszValueTrue) {
                    /* ���������^�̏ꍇ�ɓK�p����l - 
                       �U�̏ꍇ�ɓK�p����l                                 */
                    if (NULL == (void *) (pstResult->pszValueTrue = 
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
    if (nErrorOccured && NULL != (void *) pstResult) {
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
void freeIFBLOCK(struct _IFBLOCK *pstTarget)
{
    int nIndex;                         /* ���ڃC���f�b�N�X                 */

    if (NULL != (void *) pstTarget) {
        for (nIndex = 0; MAXCNT_ITEM_IFBLOCK > nIndex; nIndex++) {
            if (NULL != *((void **) pstTarget + nIndex)) {
                free((void *) *((void **) pstTarget + nIndex));
            }
        }
        free((void *) pstTarget);
    }
    return;
}
