/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����Fbmlprm.h                                                     */
/* �@�T�@�@�@�v�F�p�����[�^�擾�w�b�_                                         */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2005/12/26     �F��O�K       �V�K                               */
/******************************************************************************/
#ifndef _bmlprm_h
#define _bmlprm_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �p�����[�^�ݒ�l�l�i�[�\����
struct prmVal {
	char			*val ;
	struct prmVal	*next ;
} ;

// �p�����[�^�����o�[�i�[�\����
struct prmMem {
	char			*name ;
	struct prmVal	*valTop ;
	struct prmMem	*next ;
} ;

typedef	struct prmMem	BMLPRM ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
// �p�����[�^�I�[�v���֐�
BMLPRM *	ZbmlPrmOpen ( char * ) ;
// �p�����[�^�N���[�Y�֐�
void	 	ZbmlPrmClose ( struct prmMem * ) ;
// �p�����[�^�擾�֐�
int 		ZbmlPrmGetVal ( struct prmMem * , char *, char *) ;
int			ZbmlPrmGetValList ( struct prmMem *, char *, int *, char *** ) ;

#endif
/** End of File ***************************************************************/