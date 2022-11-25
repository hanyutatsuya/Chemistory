/****************************************************************************
 * KSNSK_if.c : 計算式文字列 IF ブロック展開
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

/* このファイル内に存在する関数                                             */
char *OperateKSNSK(const char *);
char *GetIFBlock(const char *);
struct _IFBLOCK *SplitIFBlockItems(char *);
int IsFormula(const char *);
void freeIFBLOCK(struct _IFBLOCK *);

/* このファイルの関数呼び出し元に (おそらく) 存在する関数                   */
extern double StringCal(char *);

/* common_str.c 中の汎用関数                                                */
extern char *_replace(const char *, const char *, const char *);
extern char *_strchain(const char *, const char *);
extern char *_strndup(const char *, size_t);
extern char *_touppercase(const char *);
extern char *_strrstr(char *, const char *);

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
char *OperateKSNSK(const char *pszKSNSK)
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

    if (NULL != (void *) (pszFormular = 
                          _touppercase(_replace(pszKSNSK,
                                                szBlank,
                                                (char *) NULL)))) {
        if (!nErrorOccured && NULL != (void *) pszFormular) {
            if (!IsFormula(pszFormular)) {
                nErrorOccured = TRUE;   /* 計算式として異常                 */
            }
        }

        while (!nErrorOccured && 
               NULL != (void *) (pszIFBlock = GetIFBlock(pszFormular))) {
            if (NULL == (void *) (pstItems = SplitIFBlockItems(pszIFBlock))) {
                nErrorOccured = TRUE;   /* IF ブロック内の要素分解失敗      */
            }
            else if (NULL == (void *) pstItems->pszConditionLeft ||
                     NULL == (void *) pstItems->pszOperator ||
                     NULL == (void *) pstItems->pszConditionRight ||
                     NULL == (void *) pstItems->pszValueTrue ||
                     NULL == (void *) pstItems->pszValueFalse) {
                nErrorOccured = TRUE;   /* IF ブロック内の要素分解失敗      */
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
                                        /* IF ブロック → 適用値変換失敗    */
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
            nErrorOccured = TRUE;       /* 計算式として異常                 */
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
 * 計算式に含まれる IF ブロック文字列を抽出します。
 *
 * Paramter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      ここで指定する文字列は、 IF ブロックを含む計算式の文
 *                      字列です。
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
char *GetIFBlock(const char *pszOriginal)
{
    static char szIFBlock[] = STR_BEGIN_IFBLOCK;

    char *pszResult = NULL;             /* 戻り値                           */
    char *pszIFBlock;                   /* IF ブロック開始位置              */
    size_t ulOriginal;                  /* 元の文字列の長さ                 */
    char *pszFind;                      /* IF ブロック終端検索              */
    int nParenthesis = 0;               /* 括弧の階層震度                   */
    int nComma;                         /* カンマの数                       */
    BOOL nTarminate;                    /* IF ブロック終端検出              */

    if (NULL != (void *) pszOriginal) {
        if ((size_t) 0 <= (ulOriginal = strlen(pszOriginal))) {
            if (NULL != (void *) (pszIFBlock = _strrstr((char *) pszOriginal,
                                                        (const char *) szIFBlock))) {
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
int IsFormula(const char *pszKSNSK)
{
    BOOL bResult = FALSE;
    char *pszFormular;
    char *pszReplace;
    int nIndex;
    int nParenthesis = 0;               /* 括弧の階層震度                   */

    if (NULL != (void *) (pszFormular = 
                          _touppercase(_replace(pszKSNSK,
                                                " ",
                                                (char *) NULL)))) {

        /* 算術関数の除去                                                   */
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

            /* 条件式中の比較演算子除去                                     */
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
        free((void *) pszFormular);

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
            case PARENT_BEGIN:          /* カッコ (開始)                    */
                nParenthesis++;
                break;

            case PARENT_END:            /* カッコ (終了)                    */
                nParenthesis--;
                if (0 > nParenthesis) {
                    if (NULL == (void *) pstResult->pszValueTrue ||
                        NULL == (void *) pstResult->pszConditionRight) {
                        nErrorOccured = TRUE;
                                        /* IF ブロックの終了を示す ')' を検
                                           出したが、必須項目が不足している */
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

            case OPERATOR_LT:           /* 条件式演算子                     */
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

            case SPLITTER_COMMA:    /* 要素の区切りを示すカンマ             */
                if (nParenthesis) {
                    break;
                }
                else if (NULL == (void *) pstResult->pszConditionRight) {
                    /* 条件式右辺 - 条件式が真の場合に適用する値            */
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
                    /* 条件式が真の場合に適用する値 - 
                       偽の場合に適用する値                                 */
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

            default:                    /* ここでの処理の対象外             */
                break;
            }
        }
    }

    /* エラー発生時は、 (途中まで) 確保した内容をクリア                     */
    if (nErrorOccured && NULL != (void *) pstResult) {
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
void freeIFBLOCK(struct _IFBLOCK *pstTarget)
{
    int nIndex;                         /* 項目インデックス                 */

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
