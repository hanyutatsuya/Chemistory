/****************************************************************************
 * KSNSK_if.h : �v�Z�������� IF �u���b�N�W�J
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

typedef int BOOL;                       /* BOOLEAN (2 �l)                   */

#ifndef TRUE
#define FALSE                      (0)  /* boolean false value              */
#ifndef TRUE
#define TRUE            (!FALSE)        /* boolean true value
                                           Microsoft Visual Basic �̃I�u
                                           �W�F�N�g (�^�X�N) �𑊎�ɂ����
                                           ���́A�Œ�l 1 �Ƃ��邱�ƁI      */
#endif                                  /* !define TRUE                     */
#endif                                  /* !define FALSE                    */

#ifndef _EOS
#define _EOS            ('\0')          /* End Of String (������I�[�L��)   */
#endif                                  /* _EOS                             */

#ifndef _MAXBUF
#define _MAXBUF                 (4096)  /* �o�b�t�@�̍ő�T�C�Y (�o�C�g)
                                            (stdio.h �� 260 ���炢�̒l�Œ�
                                            �`����Ă���n�Y)               */
#endif                                  /* _MAXBUF                          */

#define STR_BEGIN_IFBLOCK \
                        ("IF(")         /* IF ���J�n������������            */
#define STR_BEGIN_POW	("POW(")
#define STR_BEGIN_LOG	("LOG(")
#define STR_BEGIN_LOG10	("LOG10(")

/* �ȉ��A IF �����ňӖ���������                                           */
#define PARENT_BEGIN    ('(')
#define PARENT_END      (')')
#define SPLITTER_COMMA  (':')           /* �������ƓK�p�l�̋�؂�           */
#define OPERATOR_LT     ('<')           /* ������: ����                     */
#define OPERATOR_GT     ('>')           /* ������: �z����                   */
#define OPERATOR_EQ     ('=')           /* ������: ��v                     */
#define STR_NE          ("<>")          /* ������: �s��v                   */

#define MAXCNT_ITEM_IFBLOCK          5  /* IF �u���b�N���̗v�f��            */

/* IF �u���b�N���v�f�����\���� 
   (char** �Ƃ��Ă��Q�Ɖ\)                                                */
struct _IFBLOCK {
    char *pszConditionLeft;             /* ������ (��r���Z�q) ����         */
    char *pszOperator;                  /* �������̔�r���Z�q               */
    char *pszConditionRight;            /* ������ (��r���Z�q) �E��         */
    char *pszValueTrue;                 /* ���������^�̏ꍇ�ɓK�p����l     */
    char *pszValueFalse;                /* ���������U�̏ꍇ�ɓK�p����l     */
    char *pszEndOfList;                 /* ���̍\���̂� char** �Ƃ��ĎQ�Ƃ�
                                           ��ꍇ�� End Of List             */
};

