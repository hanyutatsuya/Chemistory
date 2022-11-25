/****************************************************************************
 * KSNSK_if.h : 計算式文字列 IF ブロック展開
 * Copyright(C)2008 INTEC Inc.
 *--------------------------------------------------------------------------
 * [History]
 *  Feb 14, 2008    H.Sato              Original
 ****************************************************************************/

typedef int BOOL;                       /* BOOLEAN (2 値)                   */

#ifndef TRUE
#define FALSE                      (0)  /* boolean false value              */
#ifndef TRUE
#define TRUE            (!FALSE)        /* boolean true value
                                           Microsoft Visual Basic のオブ
                                           ジェクト (タスク) を相手にすると
                                           きは、固定値 1 とすること！      */
#endif                                  /* !define TRUE                     */
#endif                                  /* !define FALSE                    */

#ifndef _EOS
#define _EOS            ('\0')          /* End Of String (文字列終端記号)   */
#endif                                  /* _EOS                             */

#ifndef _MAXBUF
#define _MAXBUF                 (4096)  /* バッファの最大サイズ (バイト)
                                            (stdio.h に 260 ぐらいの値で定
                                            義されているハズ)               */
#endif                                  /* _MAXBUF                          */

#define STR_BEGIN_IFBLOCK \
                        ("IF(")         /* IF 文開始を示す文字列            */
#define STR_BEGIN_POW	("POW(")
#define STR_BEGIN_LOG	("LOG(")
#define STR_BEGIN_LOG10	("LOG10(")

/* 以下、 IF 文中で意味を持つ文字                                           */
#define PARENT_BEGIN    ('(')
#define PARENT_END      (')')
#define SPLITTER_COMMA  (',')           /* 条件式と適用値の区切り           */
#define OPERATOR_LT     ('<')           /* 条件式: 未満                     */
#define OPERATOR_GT     ('>')           /* 条件式: 越える                   */
#define OPERATOR_EQ     ('=')           /* 条件式: 一致                     */
#define STR_NE          ("<>")          /* 条件式: 不一致                   */

#define MAXCNT_ITEM_IFBLOCK          5  /* IF ブロック内の要素数            */

/* IF ブロック内要素分解構造体 
   (char** としても参照可能)                                                */
struct _IFBLOCK {
    char *pszConditionLeft;             /* 条件式 (比較演算子) 左辺         */
    char *pszOperator;                  /* 条件式の比較演算子               */
    char *pszConditionRight;            /* 条件式 (比較演算子) 右辺         */
    char *pszValueTrue;                 /* 条件式が真の場合に適用する値     */
    char *pszValueFalse;                /* 条件式が偽の場合に適用する値     */
    char *pszEndOfList;                 /* この構造体を char** として参照す
                                           る場合の End Of List             */
};

