/**********************************************************************
 *                                                                    
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：bml_socket.c
 *     概要      ：socket関係関数
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2005/06/01     E.Osada        Create
 **********************************************************************/

/* include                                                            */
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include "bml_socket.h"
/**********************************************************************/

/* Define Word                                                        */
/**********************************************************************/
/**********************************************************************/

/* Extern Data	                                                      */
/**********************************************************************/
/**********************************************************************/

/* Extern Function prototype                                          */
/**********************************************************************/
/**********************************************************************/

/* Global Data                                                        */
/**********************************************************************/
/**********************************************************************/

/**********************************************************************
 *
 *      socket処理の初期化(サーバプロセス)
 *
 *      関数： int tcp_init(port_no, lisn, errno);
 *      引数： int port_no;     ポート番号 (R)
 *             int lisn;     listenサイズ (R)
 *             int *error;	エラー番号 (W)
 *      戻り値：
 *             >0               正常終了(socketで得たFD)
 *             FAILURE          引数指定エラー
 *             ERR0_SOCKET      socket()が異常終了
 *             ERR0_SOCKOPT	setsockopt()が異常終了
 *             ERR0_BIND	bind()が異常終了
 *             ERR0_LISTEN	listen()が異常終了
 *             ERR0_FCNTL_GET	fcntl(F_GETFL)が異常終了
 *             ERR0_FCNTL_SET	fcntl(F_SETFL)が異常終了
 *
 *      処理内容：
 *            socket接続を行うための初期処理を行う。
 **********************************************************************/
int
tcp_init(int port_no, int lisn, int *error)
{
	struct	sockaddr_in	srv_addr;
	int	fd_socket;
	int	on;

	/*
	 * 引数チェック
	 */
	if (port_no == 0) {
		return (FAILURE);
	}
	if (lisn < 0) {
		return (FAILURE);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	/* 
	 * データ設定 
	 */
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port_no);
	srv_addr.sin_addr.s_addr = INADDR_ANY;

	/* 
	 * socket() -> setsockopt() -> bind() -> listen() の実行 
	 */
	if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		*error = errno;
		return (ERR0_SOCKET);
	}
	on = 1;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1) {
		close( fd_socket );
		*error = errno;
		return (ERR0_SOCKOPT);
	}
	if (bind(fd_socket, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr_in)) == -1) {
		close( fd_socket );
		*error = errno;
		return (ERR0_BIND);
	}
	if (listen(fd_socket, lisn) == -1) {
		close( fd_socket );
		*error = errno;
		return (ERR0_LISTEN);
	}

	return (fd_socket);
}

/**********************************************************************
 *
 *	accept処理の実行(サーバプロセス用)
 *
 *	関数： int acpt_open(fd_socket, cli_addr, error);
 *	引数： int fd_sokcet;                   ソケットFD (R)
 *	       struct sockaddr_in *cli_addr;    acceptしたsockaddr (W)
 *	       int *error;                      エラー番号 (W)
 *	戻り値：
 *	       >0               正常終了(acceptで得たFD)
 *	       FAILURE          引数指定エラー
 *	       ERR0_ACCEPT      accept()が異常終了
 *
 *	処理内容：
 *	       クライアントとの接続を行う。
 **********************************************************************/
int
acpt_open(int fd_socket, struct sockaddr_in *cli_addr, int *error)
{
	int	fd_accept;
	unsigned long	len;
	int	status;
	int	fc;

	/* 
	 * 引数チェック
	 */
	if (fd_socket <= 0) {
		return (FAILURE);
	}
	*error = 0;
	memset(cli_addr, 0, sizeof(struct sockaddr_in));
	len = sizeof(struct sockaddr_in);

	/*
	 * accept() の実行
	 */
	for ( ; ; ) {
		if ((fd_accept = accept(fd_socket, (struct sockaddr *)cli_addr, &len)) != -1) {
			/* ノンブロッキングの設定 */
			if ((fc = fcntl(fd_accept, F_GETFL, 0)) == -1) {
				*error = errno;
				shutdown( fd_accept, 2 );
				close( fd_accept );
				return (ERR0_FCNTL_GET);
			}
			fc |= O_NONBLOCK;
			if (fcntl(fd_accept, F_SETFL, fc) == -1) {
				*error = errno;
				shutdown( fd_accept, 2 );
				close( fd_accept );
				return (ERR0_FCNTL_SET);
			}
			/*
			 * 正常終了時は、上位に取得したFDを返す
			 */
			return (fd_accept);
		}
		if (errno != EINTR) {
			close ( fd_accept );
			*error = errno;
			return (ERR0_ACCEPT);
		}
	}
}

/**********************************************************************
 *
 *	connect処理の実行(クライアントプロセス用)
 *
 *	関数： conct_open(ip_addr, timer, tmout, port_no);
 *	引数： char	*ip_addr;             サーバのIPアドレス (R)
 *	       int port_no;               ポート番号 (R)
 *	       int timer;                 リトライ間隔(ms) (R)
 *	       int tmout;                 タイムアウト(s) (R)
 *	       int *error;                エラー番号 (W)
 *	戻り値：
 *	       >0               正常終了(connectで得たFD)
 *	       FAILURE          引数指定エラー
 *	       ERR0_SOCKET      socket()が異常終了
 *	       ERR0_CONNECT     connect()が異常終了
 *	       ERR0_FCNTL_GET   fcntl(F_GETFL)が異常終了
 *	       ERR0_FCNTL_SET	fcntl(F_SETFL)が異常終了
 *	       ERR2_TIMEOUT     タイムアウト
 *	処理内容：
 *	       サーバとの接続を行う。
 **********************************************************************/
int
conct_open(char *ip_addr, int port_no, int timer, int tout, int *error)
{
	struct sockaddr_in	srv_addr;
	struct timeval		tm_start;	/* タイムアウト開始時間 */
	struct timeval		tm_r_start;	/* リトライ間隔開始時間 */
	struct timeval		tm_end;		/* 現時刻取得 */
	struct pollfd		pfd1;		/* 他FDの切断監視用pollfd */
	int	fd_socket;			/* ソケットFD */
	int	status;				/* エラーステータス */
	int	p_sts1;				/* pollステータス */
	int	fc;				/* fcntlのモード取得/設定 */

	/* 
	 * 引数チェック 
	 */
	if (ip_addr == 0) {
		return (FAILURE);
	}
	if (port_no < 0) {
		return (FAILURE);
	}
	if (timer < 1) {
		return (FAILURE);
	}
	if (tout < 1) {
		return (FAILURE);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port_no);
	srv_addr.sin_addr.s_addr = inet_addr( ip_addr );

	gettimeofday(&tm_start, NULL);	/* 現在時刻の取得 */
	for ( ; ; ) {
		gettimeofday(&tm_r_start, NULL);	/* 現在時刻の取得 */
		/*
		 * socket()の実行
		 */
		if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			*error = errno;
			return (ERR0_SOCKET);
		}
		/* 
		 * ノンブロッキングモードの設定 
		 */
		if ((fc = fcntl(fd_socket, F_GETFL, 0)) == -1) {
			*error = errno;
			status  = ERR0_FCNTL_GET;
			goto ERREND;
		}
		fc |= O_NONBLOCK;
		if (fcntl(fd_socket, F_SETFL, fc) == -1) {
			*error = errno;
			status = ERR0_FCNTL_SET;
			goto ERREND;
		}
		/*
		 * connect処理の実行
		 */
		for ( ; ; ) {
			if (connect(fd_socket, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == 0) {
				/*
				 * 正常終了の場合取得したFDを上位に返す
				 */
				return (fd_socket);
			}
			if (errno == EINTR) {
				continue;
			}
			*error = errno;
			pfd1.fd = fd_socket;
			pfd1.events = POLLOUT;
			if (errno == EINPROGRESS) {
				for ( ; ; ) {
					if ((p_sts1 = poll(&pfd1, 1, 200)) == -1) {
						if (errno == EINTR) {
							continue;
						} else {
							*error = errno;
							status = ERR0_POLL;
							goto ERREND;
						}
					} else if (p_sts1 == 0) {
						gettimeofday(&tm_end, NULL);
						if (tm_start.tv_sec + tout < tm_end.tv_sec) {
							status = ERR2_TIMEOUT;
							goto ERREND;
						}
						continue;
					} else if (p_sts1 == 1){
						if (pfd1.revents == POLLOUT) {
							break;
						}
					}
					status = ERR0_POLL;
					goto ERREND;
				}
			} else if (errno == EISCONN) {
				return (fd_socket);
			} else {
				status = ERR0_CONNECT;
				goto ERREND;
			}
		}
	}
ERREND:
	for ( ; ; ) {
		if (close(fd_socket) == -1) {
			if (errno == EINTR) {
				continue;
			} else {
				return (ERR0_CLOSE);
			}
		}
		break;
	}
	return (status);
}

/**********************************************************************
 *
 *	単数FDのpoll処理
 *
 * 	関数： int sock_poll(fd, events);
 *	引数： int fd;               イベント待ちを行うFD
 *	       short events;         待ちのイベント
 *	戻り値：
 *	       1               正常終了
 *	       ERR0_POLL       pollが異常終了
 *	       ERR2_TIMEOUT    タイムアウト
 *	処理内容：
 *
 **********************************************************************/
int
sock_poll(int fd, short events)
{
	int	status;
	int	loop;
	struct	pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;
	for ( ; ; ) {
		if ((status = poll(&pfd, 1, 200)) == -1) {
			if (errno == EINTR) {
				continue;
			}
			return (ERR0_POLL);
		} else if (status == 0) {
			return (ERR2_TIMEOUT);
		} else if (status == 1) {
			return (status);
		} else {
			return (ERR0_POLL);
		}
	}
}

/**********************************************************************
 *
 *	データの読込み
 *
 * 	関数： int sock_read(fd, ptr, size, tout, error);
 *	引数： int fd;               FD (R)
 *	       char *ptr;	     読込みバッファアドレス (W)
 *	       int size;             読込みサイズ (R)
 *	       int tout;	     タイムアウト(秒) (R)
 *	       int *error;           エラー番号 (W)
 *	戻り値：
 *	       SUCCESS               正常終了
 *	       FAILURE               引数指定エラー
 *	       ERR0_POLL             poll()が異常終了
 *	       ERR0_READ             read()が異常終了
 *	       ERR2_TIMEOUT          処理がタイムアウト
 *	       ERR2_MYCLOSE	     自プロセスでのclose()が発生
 *             ERR2_TOCLOSE          相手側でclose()が発生
 *	処理内容：
 *	       接続先からデータを読み込む
 *	注意事項：
 *	       戻り値がERR2_MYCLOSE/ERR2_TOCLOSEの場合、上位で必ずclose()
 *	       を呼び出す。
 **********************************************************************/
int
sock_read(int fd, char *ptr, int size, int tout, int *error)
{
	int	status;
	int	p_sts;
	int	fmode;
	struct timeval	tm_start;
	struct timeval	tm_end;

	/* 引数チェック */
	if (fd < 0) {
		return (FAILURE);
	}
	if (ptr == NULL) {
		return (FAILURE);
	}
	if (tout < 1) {
		return (FAILURE);
	}
	if (size < 0) {
		return (FAILURE);
	}
	if (size == 0) {
		return (SUCCESS);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	gettimeofday(&tm_start, NULL);
	for ( ; ; ) {
		if ((p_sts = sock_poll(fd, POLLIN)) == ERR2_TIMEOUT) {
			gettimeofday(&tm_end, NULL);
			if (tm_start.tv_sec + tout < tm_end.tv_sec) {
				*error = errno;
				return (ERR2_TIMEOUT);
			} else {
				continue;
			}
		} else if (p_sts == ERR0_POLL) {
			*error = errno;
			return (ERR0_POLL);
		}
		if ((status = read(fd, ptr, size)) == -1) {
			if (errno == EINTR) {
				continue;
			}
			*error = errno;
			if (errno == EBADF) {
				return (ERR2_MYCLOSE);
			}
			if (errno == ECONNRESET) {
				return (ERR2_TOCLOSE);
			}
			return (ERR0_READ);
		}
		if (status == 0) {
			*error = errno;
			return (ERR2_TOCLOSE);
		}
		if (size - status == 0) {
			break;
		}
		ptr += status;
		size -= status;
	}
	return (SUCCESS);
}

/**********************************************************************
 *
 *	データの書込み
 *
 *	関数： int sock_write(fd, ptr, size, tout, error);
 *	引数： int fd;               FD	(R)
 *	       char *ptr;            バッファアドレス (R)
 *	       int size;             書込みサイズ (R)
 *	       int tout;             タイムアウト(秒)(R)
 *	       int *error;           エラー番号 (W)
 *	戻り値：
 *	       SUCCESS               正常終了
 *	       FAILURE               引数指定エラー
 *	       ERR0_POLL             poll()が異常終了
 *	       ERR0_WRITE            write()が異常終了
 *	       ERR1_0_WRITE          write()の戻り値が０
 *	       ERR2_TIMEOUT          処理がタイムアウト
 *	       ERR2_MYCLOSE          自プロセスでclose()が発生
 *	       ERR2_TOCLOSE          相手側でclose()が発生
 *	処理内容：
 *	       接続先へデータを書込む。
 *	注意事項：
 *	       戻り値がERR2_MYCLOSE/ERR2_TOCLOSEの場合、上位で必ずclose()
 *	       を呼び出す。
 **********************************************************************/
int
sock_write(int fd, char *ptr, int size, int tout, int *error)
{
	int	status;
	int	p_sts;
	int	fmode;
	struct timeval	tm_start;
	struct timeval	tm_end;

	/* 引数チェック */
	if (fd < 0) {
		return (FAILURE);
	}
	if (ptr == NULL) {
		return (FAILURE);
	}
	if (tout < 1) {
		return (FAILURE);
	}
	if (size < 0) {
		return (FAILURE);
	}
	if (size == 0) {
		return (SUCCESS);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	gettimeofday(&tm_start, NULL);
	for ( ; ; ) {
		if ((p_sts = sock_poll(fd, POLLOUT)) == ERR2_TIMEOUT) {
			gettimeofday(&tm_end, NULL);
			if (tm_start.tv_sec + tout < tm_end.tv_sec) {
				*error = errno;
				return (ERR2_TIMEOUT);
			} else {
				continue;
			}
		} else if (p_sts == ERR0_POLL) {
			*error = errno;
			return (ERR0_POLL);
		}
		if ((status = write(fd, ptr, size)) == -1) {
			if (errno == EINTR) {
				continue;
			}
			*error = errno;
			if (errno == EBADF) {
				return (ERR2_MYCLOSE);
			}
			if (errno == EPIPE || errno == ECONNRESET) {
				return (ERR2_TOCLOSE);
			}
			return (ERR0_WRITE);
		}
		if (status == 0) {
			*error = errno;
			return (ERR1_0_WRITE);
		}
		if (size - status == 0) {
			break;
		}
		ptr += status;
		size -= status;
	}
	return (SUCCESS);
}
