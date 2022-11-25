/****************************************************************************
 * common_str.c : 汎用文字列操作関数群
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef _EOS
#define _EOS            ('\0')          /* End Of String                    */
#endif                                  /* _EOS                             */

#ifndef _MASK_TOUPPER
#define _MASK_TOUPPER   (0x00DF)        /* 半角英小文字→大文字変換のマスク */
#endif                                  /* !define _TOUPPER                 */

int _isnumeric(const char *);
char *_replace(const char *, const char *, const char *);
char *_strchain(const char *, const char *);
char *_strndup(const char *, size_t);
char *_strrstr(char *, const char *);
char *_touppercase(const char *);

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
int _isnumeric(const char *pszTarget)
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
char *_replace(const char *pszOrigin,
               const char *pszTarget,
               const char *pszReplace)
{
    char *pszResult = (char *) NULL;    /* 戻り値                           */
    char *pszFind;                      /* 置換対象検索                     */
    int nFindCount;                     /* 置換対象件数                     */
    size_t ulOrigin;                    /* 元の文字列のバイト サイズ        */
    size_t ulTarget;                    /* 元の文字列のバイト サイズ        */
    size_t ulSource;                    /* 置換対象のバイト サイズ          */
    size_t ulReplace;                   /* 置き換える文字列のバイト サイズ  */
    size_t ulDestination;               /* 置換後文字位置                   */

    if (NULL != (void *) pszOrigin && NULL != (void *) pszTarget) {
        if ((size_t) 0 < (ulTarget = strlen(pszTarget))) {
            if ((size_t) 1 > (ulOrigin = strlen(pszOrigin))) {
                pszResult = strdup(pszOrigin);
                                        /* 置換対象なし                     */
            }
            else {
                for (nFindCount = 0, pszFind = (char *) pszOrigin;
                     NULL != (void *) (pszFind = strstr(pszFind, pszTarget));
                     nFindCount++, pszFind++);
                if (0 == nFindCount) {
                    pszResult = strdup(pszOrigin);
                                        /* 置換対象なし                     */
                }
                else {
                    ulReplace = (NULL == (void *) pszReplace) ?
                                (size_t) 0 : strlen(pszReplace);
                    if (NULL != (void *) (pszResult =
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
                                    memcpy((void *) (pszResult + ulDestination),
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
 * _strchain
 *
 * 文字列の結合
 *
 * Parameter(s):
 *  pszOrigin           NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      NULL が指定された場合、空文字列が指定されたものとし
 *                      て扱います。
 *                      ここで指定する文字列は結合後に先頭に配置される文字列
 *                      です。
 *  pszAdd              NULL 文字を終了コードとする文字列を格納している領域
 *                      の先頭ポインタを指定します。
 *                      NULL が指定された場合、空文字列が指定されたものとし
 *                      て扱います。
 *                      ここで指定する文字列は結合後に末尾に配置される文字列
 *                      です。
 *
 * Return value:
 *  関数が正常隆昌した場合、結合後の文字列を格納している領域の先頭ポインタを
 *  返します。
 *  エラーが発生した場合、 NULL を返します。
 *
 * Comment:
 *  この関数が返す (文字列を格納している) 領域が不要になった場合、この関数の
 *  呼び出し元で free() を使用して領域を開放してください。
 *--------------------------------------------------------------------------*/
char *_strchain(const char *pszOrigin, const char *pszAdd)
{
    char *pszResult;                    /* 戻り値                           */
    size_t ulOrigin;                    /* 先頭文字列のバイト サイズ        */
    size_t ulAdd;                       /* 末尾文字列のバイト サイズ        */

    ulOrigin = (size_t) ((NULL == (void *) pszOrigin) ? 0 : strlen(pszOrigin));
    ulAdd = (size_t) ((NULL == (void *) pszAdd) ? 0 : strlen(pszAdd));

    if (NULL != (void *) (pszResult =
                          (char *) malloc(ulOrigin + ulAdd + (size_t) 1))) {
        if (ulOrigin) {
            memcpy((void *) pszResult, (void *) pszOrigin, ulOrigin);
        }
        if (ulAdd) {
            memcpy((void *) (pszResult + ulOrigin), (void *) pszAdd, ulAdd);
        }
        *(pszResult + ulOrigin + ulAdd) = (char) _EOS;
                                        /* EOS                               */
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
char *_strndup(const char *pszOrigin, size_t ulSize)
{
    char *pszResult = (char *) NULL;    /* 戻り値                           */
    size_t ulOrigin;                    /* 元の文字列のバイト サイズ        */
    size_t ulTruth;                     /* 抽出する文字列のバイト サイズ    */

    if (NULL != (void *) pszOrigin && (size_t) 0 < ulSize) {
        ulTruth = (ulSize < (ulOrigin = strlen(pszOrigin))) ? ulSize : ulOrigin;
        if (NULL != (void *) (pszResult =
                              (char *) malloc(ulTruth + (size_t) 1))) {
            memcpy((void *) pszResult, (void *) pszOrigin, ulTruth);
            *(pszResult + ulTruth) = (char) _EOS;
        }
    }
    return (pszResult);
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
char *_strrstr(char *pszOrigin, const char *pszTarget)
{
    char *pszResult = (char *) NULL;
    char *pszFind;

    if (NULL != (void *) pszOrigin && NULL != pszTarget) {
        for (pszFind = pszOrigin;
             NULL != (void *) (pszFind = strstr(pszFind, pszTarget));
             pszFind++) {
            pszResult = pszFind;
        }
    }
    return (pszResult);
}

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
char *_touppercase(const char *pszOrigin)
{
    char *pszResult = (char *) NULL;    /* 戻り値                           */
    size_t ulIndex;                     /* 文字位置                         */

    if (NULL != (void *) pszOrigin) {
        if (NULL != (void *) (pszResult = strdup(pszOrigin))) {
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

