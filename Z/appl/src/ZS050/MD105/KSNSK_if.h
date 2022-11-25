/****************************************************************************
 * KSNSK_if.h : �׻���ʸ���� IF �֥�å�Ÿ��
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

typedef int BOOL;                       /* BOOLEAN (2 ��)                   */

#ifndef TRUE
#define FALSE                      (0)  /* boolean false value              */
#ifndef TRUE
#define TRUE            (!FALSE)        /* boolean true value
                                           Microsoft Visual Basic �Υ���
                                           �������� (������) �����ˤ����
                                           ���ϡ������� 1 �Ȥ��뤳�ȡ�      */
#endif                                  /* !define TRUE                     */
#endif                                  /* !define FALSE                    */

#ifndef _EOS
#define _EOS            ('\0')          /* End Of String (ʸ����ü����)   */
#endif                                  /* _EOS                             */

#ifndef _MAXBUF
#define _MAXBUF                 (4096)  /* �Хåե��κ��祵���� (�Х���)
                                            (stdio.h �� 260 ���餤���ͤ���
                                            ������Ƥ���ϥ�)               */
#endif                                  /* _MAXBUF                          */

#define STR_BEGIN_IFBLOCK \
                        ("IF(")         /* IF ʸ���Ϥ򼨤�ʸ����            */
#define STR_BEGIN_POW	("POW(")
#define STR_BEGIN_LOG	("LOG(")
#define STR_BEGIN_LOG10	("LOG10(")

/* �ʲ��� IF ʸ��ǰ�̣�����ʸ��                                           */
#define PARENT_BEGIN    ('(')
#define PARENT_END      (')')
#define SPLITTER_COMMA  (',')           /* ��Ｐ��Ŭ���ͤζ��ڤ�           */
#define OPERATOR_LT     ('<')           /* ��Ｐ: ̤��                     */
#define OPERATOR_GT     ('>')           /* ��Ｐ: �ۤ���                   */
#define OPERATOR_EQ     ('=')           /* ��Ｐ: ����                     */
#define STR_NE          ("<>")          /* ��Ｐ: �԰���                   */

#define MAXCNT_ITEM_IFBLOCK          5  /* IF �֥�å�������ǿ�            */

/* IF �֥�å�������ʬ��¤�� 
   (char** �Ȥ��Ƥ⻲�Ȳ�ǽ)                                                */
struct _IFBLOCK {
    char *pszConditionLeft;             /* ��Ｐ (��ӱ黻��) ����         */
    char *pszOperator;                  /* ��Ｐ����ӱ黻��               */
    char *pszConditionRight;            /* ��Ｐ (��ӱ黻��) ����         */
    char *pszValueTrue;                 /* ��Ｐ�����ξ���Ŭ�Ѥ�����     */
    char *pszValueFalse;                /* ��Ｐ�����ξ���Ŭ�Ѥ�����     */
    char *pszEndOfList;                 /* ���ι�¤�Τ� char** �Ȥ��ƻ��Ȥ�
                                           ����� End Of List             */
};

