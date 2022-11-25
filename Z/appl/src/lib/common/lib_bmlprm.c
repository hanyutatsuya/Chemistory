/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����Flib_log.c                                                    */
/* �@�T�@�@�@�v�F���O�o�̓��C�u����                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2005/12/21     �F��O�K       �V�K�쐬                           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <fcntl.h>
#include <time.h>

#include "bmlprm.h" 

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

//  �t���O��`
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
static	void	 _ZbmlPrmDisp ( BMLPRM * ) ;

/******************************************************************************/
/*  �� �� ���@�FZbmlPrmOpen												  	  */
/*  �@�\�T�v�@�F���ݒ�t�@�C���ǂݍ���									  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FpfileName	���ݒ�t�@�C����								  */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F BMLPRM*                                                      */
/* �@�@�@�@�@�@�@NULL�ȊO : ����											  */
/* �@�@�@�@�@�@�@NULL     : ���s											  */
/******************************************************************************/
BMLPRM *
ZbmlPrmOpen ( pfileName )
char	*pfileName ;
{
	FILE				 *fp ;
	char				  buf[ 1024 ] ;
	char				 *p ;
	char				 *pToken ;
	struct prmMem		**makeMem ;
	struct prmVal		**makeVal ;
	struct prmMem		 *pTop ;
	struct prmMem		 *ret ;

	/***
	 ***	��������
	 ***/
	//	�h�m�h�t�@�C���I�[�v��
	fp	= fopen ( pfileName, "r" ) ;
	if ( fp == NULL ) {
		return ( NULL ) ;
	}
loging ( "START - ZbmlPrmOpen\n" ) ;

	/***
	 ***	�h�m�h�t�@�C���ǂݍ���
	 ***/
	makeMem = &pTop ;

	while ( fgets ( buf, sizeof ( buf ), fp ) != NULL ) {
		// �R�����g�ǂݔ�΂�
		if ( buf[ 0 ] == '#' || buf[ 0 ] == '\n' || buf[ 0 ] == '\0' ) {
			continue ;
		}

		//	�g�[�N������
		p = buf ;
		while ( ( pToken = strtok ( p,     " \t\n" ) ) != NULL ) {
			// �p�����[�^���擾�i�P��ڂ̂݁j
			if ( p != NULL ) {
				*makeMem = ( struct prmMem * ) malloc ( sizeof ( struct prmMem ) ) ;
				if ( *makeMem == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				memset ( *makeMem, '\0', sizeof ( struct prmMem ) ) ;

				(*makeMem)->name = ( char * ) malloc (  strlen ( pToken ) + 1 ) ;
				if ( (*makeMem)->name == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					ZbmlPrmClose ( pTop ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				strcpy ( (*makeMem)->name, pToken ) ;
				makeVal = & ( (*makeMem)->valTop ) ;
				p = NULL ;
			} 
			else {
				*makeVal = ( struct prmVal * ) malloc ( sizeof ( struct prmVal ) ) ;
				if ( *makeVal == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					ZbmlPrmClose ( pTop ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				memset ( *makeVal, '\0', sizeof ( struct prmVal ) ) ;
				(*makeVal)->val = ( char * ) malloc ( strlen ( pToken ) + 1 ) ;
				if ( (*makeVal)->val == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					ZbmlPrmClose ( pTop ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				strcpy ( (*makeVal)->val, pToken ) ;
				makeVal = & ( (*makeVal)->next ) ;
			}
		}
		makeMem = & ( (*makeMem)->next ) ;
	}

	/***
	 ***	�h�m�h�t�@�C���N���[�Y
	 ***/
	fclose ( fp ) ;
loging ( "END   - ZbmlPrmOpen\n" ) ;
_ZbmlPrmDisp ( pTop ) ;
	return ( pTop ) ;
}
/******************************************************************************/
/*  �� �� ���@�FZbmlPrmClose												  	  */
/*  �@�\�T�v�@�F���ݒ�t�@�C���i�[�̈���								  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FpMem	���ݒ�\���̃|�C���^								  */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F 															  */
/*   �Ȃ�                                                                     */
/******************************************************************************/
void
ZbmlPrmClose ( pMem )
struct prmMem	*pMem ;
{
	struct prmMem	*seeMem, *freeMem ;
	struct prmVal	*seeVal, *freeVal ;

loging ( "START - ZbmlPrmClose\n" ) ;
	seeMem = pMem ;
	while ( seeMem != NULL ) {
		free ( seeMem->name ) ;
		seeVal = seeMem->valTop ;
		while ( seeVal != NULL ) {
			free ( seeVal->val ) ;
			freeVal = seeVal ;
			seeVal = seeVal->next ;
			free ( freeVal ) ;
		}
		freeMem = seeMem ;
		seeMem = seeMem->next ;
		free ( freeMem ) ;
	}
loging ( "END   - ZbmlPrmClose\n" ) ;
	return ;
}
/******************************************************************************/
/*  �� �� ���@�FZbmlPrmGetVal     										  	  */
/*  �@�\�T�v�@�F���擾�֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FpMem	���ݒ�\���̃|�C���^								  */
/*�@ ��Q���� �Fname	�ϐ���												  */
/*  �o�@�@�́@�F                                                              */
/*�@ ��S���� �FVal		�ݒ�l												  */
/*  ���A���@�F 															  */
/*   �Ȃ�                                                                     */
/*  ���A���@�Fint				                                              */
/* �@�@�@�@�@�@�@0 : ����													  */
/* �@�@�@�@�@�@�@1 : �x���I���i�ϐ������j									  */
/******************************************************************************/
int 
ZbmlPrmGetVal ( pMem, name, Val )
struct prmMem	*pMem ;
char			*name ;
char			*Val ;
{
	struct prmMem	*seeMem ;
	struct prmVal	*seeVal ;
	char			*p ;
	LC_BOOLEAN		 firstFlg ;
	int				retSts ;

loging ( "START - ZbmlPrmGetVal\n" ) ;
	retSts = 1 ;
	seeMem = pMem ;
	while ( seeMem != NULL ) {
		if ( strcmp ( seeMem->name, name ) == 0 ) {
			seeVal = seeMem->valTop ;
			Val[0] = '\0' ;
			firstFlg = LC_true ;
			while ( seeVal != NULL ) {
				if ( firstFlg == LC_true ) {
					strcpy ( Val, seeVal->val ) ;
					firstFlg = LC_false ;
				}
				else {
					strcat ( Val, "\t" ) ;
					strcat ( Val, seeVal->val ) ;
				}
				seeVal = seeVal->next ;
			}
			retSts = 0 ;
			break ;
		}
		seeMem = seeMem->next ;
	}
loging ( "END   - ZbmlPrmGetVal\n" ) ;
	return retSts ;
}

/******************************************************************************/
/*  �� �� ���@�FZbmlPrmGetValList  										  	  */
/*  �@�\�T�v�@�F���擾�֐�												  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �FpMem	���ݒ�\���̃|�C���^								  */
/*�@ ��Q���� �Fname	�ϐ���												  */
/*  �o�@�@�́@�F                                                              */
/*�@ ��R���� �FVal		�ݒ�l												  */
/*  ���A���@�F 															  */
/*   �Ȃ�                                                                     */
/*  ���A���@�Fint				                                              */
/* �@�@�@�@�@�@�@0 : ����													  */
/* �@�@�@�@�@�@�@1 : �x���I���i�ϐ������j									  */
/* �@�@�@�@�@�@ -1 : �ُ�I��												  */
/******************************************************************************/
int 
ZbmlPrmGetValList ( pMem, name, cnt, Val )
struct prmMem	 *pMem ;
char			 *name ;
int				 *cnt ;
char			 ***Val ;
{
	struct prmMem	*seeMem ;
	struct prmVal	*seeVal ;
	char			*p ;
	LC_BOOLEAN		 firstFlg ;
	int				 retSts ;
	int				 idx ;

loging ( "START - ZbmlPrmGetValList\n" ) ;
	idx = 0 ;
	retSts = 1 ;
	seeMem = pMem ;
	*Val = NULL ;
	while ( seeMem != NULL ) {
		if ( strcmp ( seeMem->name, name ) == 0 ) {
			*Val = realloc ( *Val, sizeof ( char * ) * ( idx + 1 ) ) ;
			if ( *Val == NULL ) {
				return ( -1 ) ;
			}
			seeVal = seeMem->valTop ;
			(*Val)[idx] = ( char* )malloc ( sizeof ( char ) * 1024 ) ;
			if ( (*Val)[idx] == NULL ) {
				return ( -1 ) ;
			}
			memset ( (*Val)[idx], '\0', sizeof ( char ) * 1024 ) ; 
			firstFlg = LC_true ;
			while ( seeVal != NULL ) {
				if ( firstFlg == LC_true ) {
					strcpy ( (*Val)[idx], seeVal->val ) ;
					firstFlg = LC_false ;
				}
				else {
					strcat ( (*Val)[idx], "\t" ) ;
					strcat ( (*Val)[idx], seeVal->val ) ;
				}
				seeVal = seeVal->next ;
			}
			retSts = 0 ;
			idx ++ ;
		}
		seeMem = seeMem->next ;
	}
	*cnt = idx ;
loging ( "END   - ZbmlPrmGetValList\n" ) ;
	return retSts ;
}

/******************************************************************************/
/*  �� �� ���@�F_ZbmlPrmDisp	   										  	  */
/*  �@�\�T�v�@�F���ݒ�t�@�C���i�[�̈�\���y�f�o�b�O�p�z					  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct  prmMem*	���ݒ�\���̃|�C���^						  */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F 															  */
/*   �Ȃ�                                                                     */
/******************************************************************************/
void
_ZbmlPrmDisp ( pMem )
BMLPRM	*pMem ;
{
#if defined ( _TRACE )
	struct prmMem	*seeMem ;
	struct prmVal	*seeVal ;

loging ( "START - ZbmlPrmDisp\n" ) ;
	seeMem = pMem ;
	while ( seeMem != NULL ) {
loging ( "      - ##############################\n" ) ;
loging ( "        Name => [%s]\n", seeMem->name ) ;
		seeVal = seeMem->valTop ;
		while ( seeVal != NULL ) {
loging ( "        Val  => [%s]\n", seeVal->val ) ;
			seeVal = seeVal->next ;
		}
		seeMem = seeMem->next ;
	}
loging ( "END   - ZbmlPrmDisp\n" ) ;
#endif
	return ;
}
/** End of File ***************************************************************/
