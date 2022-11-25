/****************************************************************************
 * common_str.c : �ėp�����񑀍�֐��Q
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
#define _MASK_TOUPPER   (0x00DF)        /* ���p�p���������啶���ϊ��̃}�X�N */
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
char *_replace(const char *pszOrigin,
               const char *pszTarget,
               const char *pszReplace)
{
    char *pszResult = (char *) NULL;    /* �߂�l                           */
    char *pszFind;                      /* �u���Ώی���                     */
    int nFindCount;                     /* �u���Ώی���                     */
    size_t ulOrigin;                    /* ���̕�����̃o�C�g �T�C�Y        */
    size_t ulTarget;                    /* ���̕�����̃o�C�g �T�C�Y        */
    size_t ulSource;                    /* �u���Ώۂ̃o�C�g �T�C�Y          */
    size_t ulReplace;                   /* �u�������镶����̃o�C�g �T�C�Y  */
    size_t ulDestination;               /* �u���㕶���ʒu                   */

    if (NULL != (void *) pszOrigin && NULL != (void *) pszTarget) {
        if ((size_t) 0 < (ulTarget = strlen(pszTarget))) {
            if ((size_t) 1 > (ulOrigin = strlen(pszOrigin))) {
                pszResult = strdup(pszOrigin);
                                        /* �u���ΏۂȂ�                     */
            }
            else {
                for (nFindCount = 0, pszFind = (char *) pszOrigin;
                     NULL != (void *) (pszFind = strstr(pszFind, pszTarget));
                     nFindCount++, pszFind++);
                if (0 == nFindCount) {
                    pszResult = strdup(pszOrigin);
                                        /* �u���ΏۂȂ�                     */
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
 * ������̌���
 *
 * Parameter(s):
 *  pszOrigin           NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      NULL ���w�肳�ꂽ�ꍇ�A�󕶎��񂪎w�肳�ꂽ���̂Ƃ�
 *                      �Ĉ����܂��B
 *                      �����Ŏw�肷�镶����͌�����ɐ擪�ɔz�u����镶����
 *                      �ł��B
 *  pszAdd              NULL �������I���R�[�h�Ƃ��镶������i�[���Ă���̈�
 *                      �̐擪�|�C���^���w�肵�܂��B
 *                      NULL ���w�肳�ꂽ�ꍇ�A�󕶎��񂪎w�肳�ꂽ���̂Ƃ�
 *                      �Ĉ����܂��B
 *                      �����Ŏw�肷�镶����͌�����ɖ����ɔz�u����镶����
 *                      �ł��B
 *
 * Return value:
 *  �֐������헲�������ꍇ�A������̕�������i�[���Ă���̈�̐擪�|�C���^��
 *  �Ԃ��܂��B
 *  �G���[�����������ꍇ�A NULL ��Ԃ��܂��B
 *
 * Comment:
 *  ���̊֐����Ԃ� (��������i�[���Ă���) �̈悪�s�v�ɂȂ����ꍇ�A���̊֐���
 *  �Ăяo������ free() ���g�p���ė̈���J�����Ă��������B
 *--------------------------------------------------------------------------*/
char *_strchain(const char *pszOrigin, const char *pszAdd)
{
    char *pszResult;                    /* �߂�l                           */
    size_t ulOrigin;                    /* �擪������̃o�C�g �T�C�Y        */
    size_t ulAdd;                       /* ����������̃o�C�g �T�C�Y        */

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
char *_strndup(const char *pszOrigin, size_t ulSize)
{
    char *pszResult = (char *) NULL;    /* �߂�l                           */
    size_t ulOrigin;                    /* ���̕�����̃o�C�g �T�C�Y        */
    size_t ulTruth;                     /* ���o���镶����̃o�C�g �T�C�Y    */

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
char *_touppercase(const char *pszOrigin)
{
    char *pszResult = (char *) NULL;    /* �߂�l                           */
    size_t ulIndex;                     /* �����ʒu                         */

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

