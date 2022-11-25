/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����Fbmllog.h                                                     */
/* �@�T�@�@�@�v�F���O�o�͊֐��w�b�_                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2005/12/26     �F��O�K       �V�K                               */
/******************************************************************************/
#ifndef _bmllog_h
#define _bmllog_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
//	INI�t�@�C�����ϐ�
#define 	BML_LOGINIPATH	"BML_LOGINIPATH"		// ���OINI�t�@�C��PATH

//	INI�t�@�C����`����
#define 	BML_LOGINI_ENV1	"logOutLv"				// ���O�o�̓��x��
#define 	BML_LOGINI_ENV2	"logdbOutLv"			// ���O�e�[�u���o�̓��x��
#define 	BML_LOGINI_ENV3	"logdbConnect"			// �c�a�o�̓f�[�����ڑ���
#define 	BML_LOGINI_ENV4	"logPath"				// ���O�o�̓p�X 
#define 	BML_LOGINI_ENV5	"logdbPort"			    // �c�a�o�̓f�[�����|�[�g
#define 	BML_LOGINI_ENV6	"logdbOutFilePath"		// �c�a�o�^�t�@�C���o�͐�
#define 	BML_LOGINI_INFO	"logInfo"				// ���O���

//	�c�a�o�^�t�@�C���o�͐�֘A
#define		BML_SFX_DBFILE	".log"

#define 	ZbmlPutLog(p)     _ZbmlPutLog(p, __FILE__, __LINE__)

//	���s�t���O
#define		EXEFLG_SEL		"S" 
#define		EXEFLG_INS		"I" 
#define		EXEFLG_UPD		"U" 
#define		EXEFLG_DEL		"D" 
#define		EXEFLG_NON		" " 

//	�g���[�X���
typedef	enum {
	TRCKIND_DEBUG	= 'D',
	TRCKIND_TRACE	= 'T',
	TRCKIND_OPT		= 'O',
	TRCKIND_WARNING	= 'W',
	TRCKIND_ERROR   = 'E',
	TRCKIND_SYSERR  = 'A'
} LOG_TRCKIND ;		


/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// ���O�\����
struct stcLogInfo {
	LOG_TRCKIND			 eTrcKind ;					// �g���[�X���
	int		 			 iLogLv ;					// ���O�o�̓��x��
	char	 			 pcLogName[256] ;			// ���O�t�@�C����
	struct stcLogInfo	*next ;						// �����O���	
} ;

// ���O���\����
struct stcLogEnv {
	//	�h�m�h�t�@�C���p
	int				 	 iLogOutLv ;				// ���O�o�̓��x��
	int				 	 iDBOutLv ;					// ���O�e�[�u���o�̓��x��
	char				 pcDBConnect[32] ;			// ���O�e�[�u���o�͐ڑ���
	int					 pcDBPort ;				    // ���O�e�[�u���o�̓|�[�g
	char				 pcLogPath[256] ;			// ���O�o�̓p�X
	char				 pcDBOutFilePath[256] ;		// �c�a�o�^�t�@�C���o�͐�
	struct stcLogInfo	*topLoginfo ;
	//	�t�@�C���w��p
	char				 pcLogFile[256] ;			// ���O�t�@�C����
} ;

// ���O�o�͏��\����
struct stcLogMember {
	LOG_TRCKIND	 eTrcKind ;							// �g���[�X���
	long		 lPid ;								// �v���Z�X�h�c
    char		 pcLoginId[8+1] ;					// ���O�C���h�c
    char		 pcAppName[32+1] ;					// �A�v���P�[�V������
    char	 	 pcSrcName[32+1] ;					// �\�[�X��
    char		 pcFncName[32+1] ;					// �֐���
	long		 lLineNo ;							// ���C����
    char		 pcExeFlg[2+1] ;					// ���s�t���O
    char		 pcErrCode[8+1] ;					// �G���[�R�[�h
    char		 pcMsg[1024+1] ;					// �ڍ׃��b�Z�[�W
} ;

// �A�v���P�[�V�������O���\����
struct stcLogAPLLOG
{
  char sydate[11];
  char sytime[9];
  char tracekbn[2];
  char pcname[33];
  //sqlint32 proccessid;
  char proccessid[33];
  char loginid[9];
  char wkupapp[33];
  char srcname[33];
  char funcname[33];
  //sqlint32 getline;
  char getline[33];
  char procflg[3];
  char errcode[9];
  char message[1024];
  //struct
  //{
  //  short length;
  //  char  data[1024];
  //} message;
} ;


/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
//extern struct stcLogEnv *gpstLogEnv ;			// ���O���\����
static struct stcLogEnv *gpstLogEnv = NULL;			// ���O���\����

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
// ���O�I�[�v���֐�
int ZbmlOpenLog( char * ) ;

// ���O�I�[�v���֐�
int _ZbmlPutLog( struct stcLogMember *, char *, long ) ;

// ���O�I�[�v���֐�
void ZbmlCloseLog() ;

#endif
/** End of File ***************************************************************/
