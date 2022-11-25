/************************************************************************/
/*																		*/
/*		�a�l�k�l���������V�X�e��										*/
/*																		*/
/*		�V�X�e�����F������												*/
/*		�t�@�C�����Fbml_fltrans.c										*/
/*		�T�v      �F�t�@�C���V�F�AIF�֐�								*/
/************************************************************************/

/************************************************************************/
/*	Ver.	���t			���O			�C�����e					*/
/* --------------------------------------------------------------------	*/
/*	1.00	2005/07/20		E.Osada			Create						*/
/************************************************************************/

/************************************************************************/
/*	�C���N���[�h�錾
/************************************************************************/
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/param.h>
#include	<dirent.h>
#include	<unistd.h>
#include	<time.h>

/************************************************************************/
/*	��������������`
/************************************************************************/
#define		MAXFNAME	128

/************************************************************************/
/*	�֐���		�FZbmlGetFile()											*/
/*	�@�\�T�v	�F�w�肳�ꂽ�f�B���N�g�����ɂ���t�@�C���ꗗ���擾����B*/
/*	����																*/
/*	 ��P����	�Fchar	*path		�������s���f�B���N�g����(R)			*/
/*	 ��Q����	�Fchar	*filelist	�擾�����t�@�C���ꗗ(W)				*/
/*	 ��R����	�Fint	*err		�V�X�e���G���[�R�[�h(W)				*/
/*	�o��																*/
/*	 ����F>=�O(�擾�����t�@�C�����̐�)									*/
/*	 �ُ�F<�O															*/
/************************************************************************/
int ZbmlGetFile( char *path, char **filelist, *err )
{
	DIR		*opendir(),		*dirptr;
	struct dirent			*readdir(), *direntry;
	char	*p, *array;
	char	dname[MAXPATHLEN];
	char	*argvv[6];

	int		i, iFcnt;

	unsigned int	status;

	/* �p�����[�^�`�F�b�N */
	if( path == NULL ) {
		*err = EAGAIN;
		return( FALSE );
	}
	if( (dirptr = opendir(path)) == (DIR *)NULL ) {
#ifdef DEBUG
		fprintf(stderr, "opendir(%s) error (%d)\n", path, errno);
#endif
		*err = errno;
		return(FAILURE);
	}

	iFcnt = 0;
	while( (direntry = readdir(dirptr)) != NULL ) {
		if( !strcmp(direntry->d_name, ".") || !strcmp(direntry->d_name, "..")
			continue;
		array = (char *)bmlRealloc( p, MAXFNAME * (iFcnt + 1) );
		p = array + (MAXFNAME * iFcnt++);
		bmlCharCpy( p, direntry->d_name, MAXFNAME );
	}
	closedir(dirptr);

	if( iFcnt )
		*filelist = array;

	return(SUCCESS);
}

/*
int		log_remove(logdirpoint)
char	*logdirpoint;
{
		DIR		*opendir(),		*dirptr;
		struct dirent			*readdir(), *direntry;

		char	*rmcmd = "/usr/bin/rm";
		char	dname[MAXPATHLEN];
		char	*argvv[6];

		int		i;

		unsigned int	status;

		if ((dirptr = opendir(logdirpoint)) == (DIR *)NULL){
			fprintf(stderr, "%s  �A�N�Z�X���O�̃f�B���N�g�� OPEN �G���[�܂��͖�����\n\n", logdirpoint);
			return(FAILURE);
		}
		
		while ((direntry = readdir(dirptr)) != NULL){
			if (strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0){
				if (strcmp(direntry->d_name, rm_faldate) < 0){

					sprintf(dname, "%s/%s", logdirpoint, direntry->d_name);
					i = 0;
					argvv[i++] = "rm";
					argvv[i++] = "-rf";
					argvv[i++] = dname;
					argvv[i++] = (char *)0;

					if (fork() == 0){
						execv(rmcmd, argvv);
						exit(1);
					}
					if (wait(&status) < 0 || status>>8 == 1)
						return(FAILURE);
				}
			}
		}
		closedir(dirptr);
		return(SUCCESS);
}
*/
/** End of File *********************************************************/
