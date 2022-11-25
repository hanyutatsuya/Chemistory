/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�Fbml_base.h									*/
/*		�T�v		�F������v���W�F�N�g�̃x�[�X�w�b�_�[�t�@�C��	*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2005/06/14		E.Osada			Create					*/
/*  		2006/02/20		H.Haga			define�ǉ�				*/
/*											�֐����^�[���l			*/
/*											���t�����l				*/
/********************************************************************/
#ifndef _bml_base_h
#define _bml_base_h

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef DEBUG
#include <unistd.h>
#endif
#include <time.h>
#include <fcntl.h>
#include <sql.h>

/********************************************************************/
/*	�������������錾												*/
/********************************************************************/
#define FALSE  0
#define TRUE   1
#define DLLEXPORT
#define DLLIMPORT
#define STRDUP(s) (s) ? strdup(s) : NULL
#define STRFREE(s) if (s) free(s)
#define HNEW(type)   (type*)huCalloc(sizeof(type), 1)
#define HDELETE(ptr) huFree(ptr)

/*	<< �֐����^�[���l >>	*/
#define	RTN_OK			  0							/* ����I��     */
#define	RTN_NG			 -1							/* �ُ�I��     */
#define	RTN_SKIP		 -2							/* �����X�L�b�v */
#define	RTN_DBERR		-10							/* �c�a�G���[   */
#define	RTN_MEMERR		-20							/* �������G���[ */
#define	RTN_ZERO		100							/* �O��         */

/*	<< ���t�����l >>	*/
#define	INIT_DATE		"1000-01-01"				/* DATE�@�����l */
#define	INIT_TIME		"00:00:01"					/* TIME  �����l */
#define	INIT_TIMESTAMP	"1000-01-01 00:00:01"	 	/* TIMESTAMP�����l */

//  ���ʋ敪
#define	SEX_MALE		"0"							// �j��
#define	SEX_FEMALE		"1"							// ����
#define	SEX_UNKNOWN		"9"							// �s��

//  �N��敪
#define	AGEKBN_YEAR		"Y"							// �N��
#define	AGEKBN_MONTH	"M"							// ����
#define	AGEKBN_WEEK		"W"							// �T��
#define	AGEKBN_DAY		"D"							// ����
#define	AGEKBN_UNKNOWN	"Z"							// �s��

/********************************************************************/
/*	���������������錾												*/
/********************************************************************/
typedef char					CHAR;
typedef unsigned char			BYTE;
typedef short					SHORT;
typedef unsigned short			USHORT;
typedef int						INT;
typedef unsigned int			UINT;
typedef long					LONG;
typedef unsigned long			ULONG;
typedef long long				LONGLONG;
typedef unsigned long long		ULONGLONG;
typedef float					FLOAT;
typedef double					DOUBLE;
typedef long double				DDOUBLE;
typedef _Bool					BOOL;
typedef void*					HANDLE;

#endif
/** End of File *****************************************************/
