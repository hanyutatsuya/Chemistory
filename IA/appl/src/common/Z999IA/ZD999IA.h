/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FZD999IA.h                                                    */
/* �@�T�@�@�@�v�F�h�`�T�[�o�Ď��f�[����                                       */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2006/01/15     �F��O�K       �V�K�쐬                           */
/******************************************************************************/
#ifndef _dmlog_h
#define _dmlog_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"ZD999IA"
#define	MYAPP_APP_NAME_JP		"ZD999IA"

//	�p�����[�^������
#define	MYAPP_PRM_PORT				"PORT"
#define	MYAPP_PRM_TIMEOUT_SEC		"TIMEOUT_SEC"
#define	MYAPP_PRM_TIMEOUT_USEC		"TIMEOUT_USEC"

#define COMMAND_PS			'0'
#define COMMAND_EXEC_LABO	'1'
#define COMMAND_EXEC_LABO_NYOU	'5'
#define COMMAND_EXEC_BM		'2'
#define COMMAND_KILL		'3'
#define COMMAND_EXEC_BACK	'4'
#define COMMAND_KILL_DM		'Q'

#define	MYAPP_COM_KILL		"/home/kea00sys/bin/ZD999stop"
#define	MYAPP_COM_BACK		"/home/kea00sys/shell/data_back_del.sh"
#define	MYAPP_COM_EXEC_PATH	"/home/kea00sys/appl/bin"
//CHG E.Osada 2006-08-23
//#define	MYAPP_COM_EXEC_LABO	"DD203.a"
//#define	MYAPP_COM_EXEC_BM	"DD201.a"
#define	MYAPP_COM_EXEC_LABO		"DD203"
#define	MYAPP_COM_EXEC_BM		"DD201"
#define	MYAPP_COM_EXEC_LABO_NYOU	"DD204"

//	��M�f�[�^�T�C�Y
#define MY_COM_SIZE sizeof ( char )

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
struct	appEnv	{
	long				 timeout_Sec ;
	long				 timeout_uSec ;
	int				 Port ;
} ;
struct dataRec {
	char	command ;
	char	sts ;
	char	prmBuf[256] ;
} ;
/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
#endif
/** End of File ***************************************************************/
