#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>

#define	LOG_BUFMAX		(4096*2)
#define	LOG_LOW_MODE	(1)

void
my_loging ( char * fmt, ... )
{
#if defined ( _TRACE )
	va_list				 ap ;
	//char				*fmt ;
	char				 logfmt[ LOG_BUFMAX ] ;

	static int			 first_call		= 0 ;
	static FILE			*outfp			= NULL ;

	struct tm		*timepos ;
	struct timeb	 timebuf ;

#if	LOG_LOW_MODE == 1
	outfp		= fopen ( "/var/tmp/DD203.log", "a" ) ;
#else
	if ( first_call != 1 ) {
		first_call	= 1 ;
		outfp		= fopen ( "/var/tmp/DD203.log", "a" ) ;
		if ( outfp != NULL ) {
			chmod ( "/var/tmp/log.log", 0666 ) ;
		}
	}
#endif
	if ( outfp == NULL ) {
		return ;
	}

	ftime ( &timebuf ) ;
	timepos			= ( struct tm * ) localtime ( &( timebuf.time ) ) ;

	va_start ( ap, fmt ) ;
//	fmt		= ( char * ) va_arg ( ap, char * ) ;
	sprintf ( logfmt, "[%05d %02d/%02d-%02d:%02d:%02d.%03d] %s",
				getpid(),
				timepos->tm_mon + 1, timepos->tm_mday,
				timepos->tm_hour, timepos->tm_min, timepos->tm_sec,
				timebuf.millitm,
				fmt ) ;
	vfprintf ( outfp, logfmt, ap ) ;
#if	LOG_LOW_MODE == 1
	fclose ( outfp ) ;
#else
	fflush ( outfp ) ;
#endif

	va_end ( ap ) ;
#endif
}
