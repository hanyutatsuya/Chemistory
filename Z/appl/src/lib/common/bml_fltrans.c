/************************************************************************/
/*																		*/
/*		ＢＭＬ様向け検査システム										*/
/*																		*/
/*		システム名：次世代												*/
/*		ファイル名：bml_fltrans.c										*/
/*		概要      ：ファイルシェアIF関数								*/
/************************************************************************/

/************************************************************************/
/*	Ver.	日付			名前			修正内容					*/
/* --------------------------------------------------------------------	*/
/*	1.00	2005/07/20		E.Osada			Create						*/
/************************************************************************/

/************************************************************************/
/*	インクルード宣言
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
/*	ｄｅｆｉｎｅ定義
/************************************************************************/
#define		MAXFNAME	128

/************************************************************************/
/*	関数名		：ZbmlGetFile()											*/
/*	機能概要	：指定されたディレクトリ下にあるファイル一覧を取得する。*/
/*	入力																*/
/*	 第１引数	：char	*path		検索を行うディレクトリ名(R)			*/
/*	 第２引数	：char	*filelist	取得したファイル一覧(W)				*/
/*	 第３引数	：int	*err		システムエラーコード(W)				*/
/*	出力																*/
/*	 正常：>=０(取得したファイル名の数)									*/
/*	 異常：<０															*/
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

	/* パラメータチェック */
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
			fprintf(stderr, "%s  アクセスログのディレクトリ OPEN エラーまたは未存在\n\n", logdirpoint);
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
