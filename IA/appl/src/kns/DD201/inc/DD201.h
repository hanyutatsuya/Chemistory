/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：DD201.h                                                      */
/* 　概　　　要：BM8000通信・結果出力ヘッダ                                   */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M対応初版                        */
/******************************************************************************/
#ifndef _dd201_h
#define _dd201_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>


#include "bmllog.h"
#include "bmlprm.h"
#include "bml_base.h"

#include "Mechmst.h"
#include "Kmkmst.h"
#include "Ctrlmst.h"
#include "Sysknrmst.h"
#include "Knsgmst.h"	/* 060418 009 */
#include "Kekka.h"
#include "Ctrlkka.h"
#include "Kenorder.h"
#include "Xbarm.h"
#include "Kskbrmst2.h"	/* ADD Haga 2006-08-02 */
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
#include "Xbarmmst.h"	/* X-Mレンジチェック対応 add */
#include "Rngchkmst.h"	/* 血清レンジチェック対応 add */
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
#include "DD40101.h"
/**********************************************************************/
/*  定数宣言                                                          */
/**********************************************************************/

/***  ログが多すぎると通信エラーが発生する場合があるため ***/
/***  TESTの時だけONにしてください!!!                    ***/ 
//#define		_DEBUG_

/* フレーム制御文字 */
#define		SOH		0x01	/* <SOH> */
#define		STX		0x02	/* <STX> */
#define		ETX		0x03	/* <ETX> */
#define		EOT		0x04	/* <EOT> */
#define		ENQ		0x05	/* <ENQ> */
#define		ACK		0x06	/* <ACK> */
#define		ELE		0x10	/* <DLE> */
#define		DC1		0x11	/* <DC1> */
#define		DC2		0x12	/* <DC2> */
#define		DC3		0x13	/* <DC3> */
#define		DC4		0x14	/* <DC4> */
#define		NAK		0x15	/* <NAK> */
#define		SYN		0x16	/* <SYN> */
#define		ETB		0x17	/* <ETB> */
#define		CR		0x0d	/* <CR> */
#define		LF		0x0a	/* <LF> */

/* STATUS */
#define		STAT_IDLE			0x00	/* idle */
#define		STAT_AWAKE			0x01	/* Awake */
#define		STAT_RCV_WAIT		0x02	/* Receive Waiting */
#define		STAT_FRAME_RCV		0x03	/* Frame Received */
#define		STAT_HAVE_DATA_SND	0x04	/* Have Data to Send */
#define		STAT_DATA_SEND		0x05	/* Data to Send */
#define		STAT_SND_WAIT		0x06	/* Send Waiting */
#define		STAT_NEXT_FRAME		0x07	/* Next Frame */
#define		STAT_SND_WAIT2		0x08	/* Send Waiting2 */
#define		STAT_OLD_FRAME		0x09	/* Old Frame */

/* 最大受信バイト数 */
#define		MAX_RCV_NUM			512

/* データ送信時のウエイト時間 */
#define		SLEEP_USEC			30000	/* 30ms */

/* 受信メッセージの意味 */
#define		MSG_NON				0		/* なし */
#define		MSG_ORDER			1		/* 問い合わせ */
#define		MSG_RESULT			2		/* 結果送信 */
#define		MSG_ELC				3		/* 電解質測定データテキスト */

/* 通信ログ種別 */
#define		RCV_LOG				0		/* 受信データログ */
#define		SND_LOG				1		/* 送信データログ */

/* .datファイル種別 */
#define		RESULT_DAT			0		/* 検査結果ファイル */
#define		ORDER_DAT_1			1		/* 検査オーダーファイル1 */
#define		ORDER_DAT_2			2		/* 検査オーダーファイル2 */

/* フレームリトライカウンタ */
#define		FRAME_RETRY_MAX		3		/* 3回 */

/* 各タイマ設定値 */
#define		TM_WAIT_2			2		/* 2s */
#define		TM_WAIT_3			3		/* 3s */
#define		TM_WAIT_5			5		/* 5s */
#define		TM_WAIT_10			10		/* 10s */

/* ソケット接続状態 */
#define		TM_SCK_CON			10		/* ソケット接続タイマ */
#define		SCK_CON_NG			0		/* ソケット未接続 */
#define		SCK_CON_OK			1		/* 全ソケット接続完了 */

/* 最大フレーム長識別 */
#define		MAX_LEN_512			1		/* 512byte */
#define		MAX_LEN_256			2		/* 256byte */

/* 最大依頼項目数 */
#define		MAX_ITEM_NUM	(114+117*5)	/* 最大項目数 */

#define		NO_SND_REQ		0			/* 送信要求なし */
#define		SND_REQ			1			/* 送信要求あり */

/* 受信データチェック */
#define		NO_RCV_DATA		0			/* 受信データなし */
#define		RCV_DATA_OK		1			/* 受信データあり */
#define		RCV_DATA_NG		2			/* 受信データNG */

/* 受信メッセージチェック */
#define		MESSAGE_ERR			0		/* message error */
#define		MESSAGE_NO_ERR		1		/* message no error */
#define		MESSAGE_OK			2		/* message OK */
#define		MESSAGE_ALL_OK		3		/* message All OK */

/* フレーム状態設定 */
#define		FRAME_CONTINUE		0		/* 次フレームあり(<ETB>受信) */
#define		FRAME_END			1		/* フレーム終了(<ETX>受信>) */

/* 設定ファイル */
#define		INI_FILE_NAME		"DD201_"
#define		INI_FILE_PRM		"00"

typedef struct sndorder {	
	char	seqnum[13+1];
	int		seqnum2;
	char	kntno[13+1];
	char	racktype[2+1];				/* 検体種別 */
	char	kmkcd[MAX_ITEM_NUM][7+1];	/* No. 6 項目コード */
	char	zrcd[4+1];					/* No.27 材料コード */
	char	ytiksbr[MAX_ITEM_NUM][15+1];/* No.37 予定希釈倍率 */
	char	sbtkbn[1+1];				/* No.44 性別区分 */
	char	age[3+1];					/* No.47 年齢 */
	char	agekbn[1+1];				/* No.48 年齢区分 */
	char	sstme[8+1];					/* No.49 採取時間 */
	char	ssymd[10+1];				/* No.50 採取年月日 */
	char	ykcd[4+1];					/* 容器コード */		/* 060417 009 */
}SNDORDER;

/* ソケット情報 */
typedef struct socket_inf {
 	int		iSd;						/* ソケット番号 */
 	char	aGouki[4];					/* 分析機号機 */
	char	aHostName[100];				/* ホスト名 */
	int		iPortNum;					/* ポート番号 */
	char	aRcvTmpMsgBuf[1024];		/* 受信メッセージコピーエリア */
	char	aSndAllMsgBuf[6][520];		/* 全送信メッセージエリア */
	char	aSndTmpBuf[520];			/* 送信データ一時バッファ */
	char	cRcvFrameCtrlChar;			/* 受信フレーム制御文字 */
	char	cSndFrameCtrlChar;			/* 送信フレーム制御 */
	char	cFrameNum;					/* フレーム番号 */
	char	cChkRcvData;				/* 受信データあり/なし判定 */
	char	cSndDataReq;				/* 送信データ要求あり/なし判定 */
	char	cStatus;					/* STATUS管理 */
	char	cChkRcvMessage;				/* 受信メッセージ判定 */
	char	cChkNextFrame;				/* フレーム継続/終了判定 */
	char	cSndFrameSeqNum;			/* 次回送信フレームカウンタ */
	int		iRcvMsg;					/* 受信メッセージの意味 */
	char	cRackNum[8+1];				/* ラック番号 */
	char	cRackPosNum[2+1];			/* ラック位置番号 */
	int		iSndRetryCnt;				/* フレーム送信リトライカウンタ */
	int		iSndBlockCnt;				/* 送信テキストブロックカウンタ */
	int		iSndBlockNum;				/* フレーム送信リトライカウンタ */
	int		iSndAgainReq;				/* 再送要求 */
	char	aSndAgainBuf[6][520];		/* 再送用バッファ */
	Kekka* 	pKekka;						/* 検査結果情報(csv登録項目) */
	Ctrlkka	sCtrlkka;					/* コントロール結果情報(csv登録項目) */
	Xbarm	sXbarm;						/* X-M結果情報(csv登録項目) */
	SaikenInfo*	pSaiken;				/* 再検依頼情報 */
	int			iKekkaNum;				/* 再検依頼件数 */
	int			iKekkaCnt;				/* 再検依頼件数カウンタ */
	int		iOrderNum;					/* 依頼項目数 */
	SNDORDER	sSndorder;				/* 検査オーダー情報 */
	time_t	tStartTm;					/* 通信開始タイマ */ 
	float	fTmOutVal;					/* タイマ */
	int		aPltseq[7];					/* プロットSEQ */
	int			iCtrlSeq;
	int			iCtrlSeqCnt;
	/* ADD 2006-08-21 E.Osada 送信タイマ追加 */
	int		iSendTimer;					/* 送信タイマ(msec) */
	struct {
	/* UPD 2007-04-25 S.Nagata サイズを増やす 48 -> 5000 */
		int		cnt;
		int		Ctrl_no[5000];
		int		Bunseki_Seq[5000];
		time_t	KnsTime[5000];
	} CtrlInfo;
	struct	socket_inf* next;
	struct	socket_inf* prev;
}SOCKET_INF;

/* テキスト定義 */
/* 項目問い合わせテキスト(リアル項目選択) */
struct ITEM_INQ_TXT_REAL {	
	char	cStartCode[1+1];			/* 開始コード */
	char	cFrameNum[1+1];				/* フレーム番号 */
	char	cTextType[1+1];				/* テキスト種別 */
	char	cDevIdentifNum[1+1];		/* 装置識別番号 */
	char	cAllBlockNum[2+1];			/* 全ブロック数 */
	char	cBlockNum[2+1];				/* ブロック番号 */
	char	cSpecimenNumInBlk[2+1];		/* ブロック内問い合わせ検体数 */
	char	cIdType[1+1];				/* ID種別 */
	char	cRackNum[8+1];				/* ラック番号 */
	char	cRackPosNum[2+1];			/* ラック内位置番号 */
	char	cRackNumInf[13+1];			/* ラック番号情報 */
	char	cReserve[1+1];				/* 予備 */
	char	cEndCode[5+1];				/* 終了コード */
};

/* 測定データテキスト(再検問い合わせ有り) */
struct MEASURE_DAT_TXT {	
	char	cStartCode[1+1];			/* 開始コード */
	char	cFrameNum[1+1];				/* フレーム番号 */
	char	cTextType[1+1];				/* テキスト種別 */
	char	cDevIdentifNum[1+1];		/* 装置識別番号 */
	char	cAllBlockNum[2+1];			/* 全ブロック数 */
	char	cBlockNum[2+1];				/* ブロック番号 */
	char	cItemNumInBlk[2+1];			/* ブロック内項目数 */
	char	cInspectDay[8+1];			/* 検査日 */
	char	cInspectTm[6+1];			/* 検査時間 */
	char	cSpecimenDiv[1+1];			/* 検体区分 */
	char	cIdSpec[1+1];				/* ID仕様 */
	char	cIdSpecimenId[13+1];		/* 検体ID */
	char	cRackNum[8+1];				/* ラック番号 */
	char	cRackPosNum[2+1];			/* ラック内位置番号 */
	char	cTtNum[2+1];				/* TT番号 */
	char	cCupNum[2+1];				/* CUP位置番号 */
	char	cReserve[16+1];				/* 予備 */
	char	cCom1[16+1];				/* コメント１ */
	char	cCom2[16+1];				/* コメント２ */
	char	cSex[1+1];					/* 性別 */
	char	cAge[3+1];					/* 年齢 */
	char	cCollBlooddDay[8+1];		/* 採血日 */
	char	cDiltCoeff[4+1];			/* 希釈係数 */
	char	cSpecimenType[1+1];			/* 検体種別 */
	char	cCntnrType[1+1];			/* 容器種別 */
	char	cItemNum[3+1];				/* 項目番号 */
	char	cAnalysCond[1+1];			/* 分析条件 */
	char	cStndrdDensity[1+1];		/* 標準濃度 */
	char	cMeasureVal[8+1];			/* 測定値 */
	char	cMark[3+1];					/* マーク */
	char	cEditDatMark[1+1];			/* 編集データマーク */
	char	cRepeatNum[1+1];			/* 繰り返し数 */
	char	cUserCode[3+1];				/* ユーザーコード */
	char	cMeasureBlkNum[1+1];		/* 測定ブロック番号 */
	char	cEndCode[5+1];				/* 終了コード */
};

/* 測定データテキスト(再検問い合わせ無し) */
struct MEASURE_DAT_TXT_NO_INQ {	
	char	cStartCode[1+1];			/* 開始コード */
	char	cFrameNum[1+1];				/* フレーム番号 */
	char	cTextType[1+1];				/* テキスト種別 */
	char	cDevIdentifNum[1+1];		/* 装置識別番号 */
	char	cAllBlockNum[2+1];			/* 全ブロック数 */
	char	cBlockNum[2+1];				/* ブロック番号 */
	char	cItemNumInBlk[2+1];			/* ブロック内項目数 */
	char	cInspectDay[8+1];			/* 検査日 */
	char	cInspectTm[6+1];			/* 検査時間 */
	char	cSpecimenDiv[8+1];			/* 検体区分 */
	char	cIdSpec[1+1];				/* ID仕様 */
	char	cIdSpecimenId[13+1];		/* 検体ID */
	char	cRackNum[8+1];				/* ラック番号 */
	char	cRackPosNum[2+1];			/* ラック内位置番号 */
	char	cTtNum[2+1];				/* TT番号 */
	char	cCupNum[2+1];				/* CUP位置番号 */
	char	cReserve[16+1];				/* 予備 */
	char	cCom1[16+1];				/* コメント１ */
	char	cCom2[16+1];				/* コメント２ */
	char	cSex[1+1];					/* 性別 */
	char	cAge[3+1];					/* 年齢 */
	char	cCollBlooddDay[8+1];		/* 採血日 */
	char	cDiltCoeff[4+1];			/* 希釈係数 */
	char	cSpecimenType[1+1];			/* 検体種別 */
	char	cCntnrType[1+1];			/* 容器種別 */
	char	cItemNum[3+1];				/* 項目番号 */
	char	cAnalysCond[1+1];			/* 分析条件 */
	char	cStndrdDensity[1+1];		/* 標準濃度 */
	char	cMeasureVal[8+1];			/* 測定値 */
	char	cMark[3+1];					/* マーク */
	char	cEditDatMark[1+1];			/* 編集データマーク */
	char	cRepeatNum[1+1];			/* 繰り返し数 */
	char	cUserCode[3+1];				/* ユーザーコード */
	char	cMeasureBlkNum[1+1];		/* 測定ブロック番号 */
	char	cEndCode[5+1];				/* 終了コード */
};

/* 依頼項目 */
struct REQ_ITEM {	
	char	cItemNum[3+1];				/* 項目番号 */
	char	cAnalysCond[1+1];			/* 分析条件 */
};

/* 項目選択指示テキスト(前回値無し) */
struct ITEM_SEL_INST_TXT_NO_VAL {	
	char	cStartCode[1+1];			/* 開始コード */
	char	cFrameNum[1+1];				/* フレーム番号 */
	char	cTextType[1+1];				/* テキスト種別 */
	char	cDevIdentifNum[1+1];		/* 装置識別番号 */
	char	cAllBlockNum[2+1];			/* 全ブロック数 */
	char	cBlockNum[2+1];				/* ブロック番号 */
	char	cItemNumInBlk[2+1];			/* ブロック内項目数 */
	char	cSpecimenDiv[1+1];			/* 検体区分 */
	char	cRegstInf[1+1];				/* 登録情報 */
	char	cIdSpecimenId[13+1];		/* 検体ID */
	char	cRackNum[8+1];				/* ラック番号 */
	char	cRackPosNum[2+1];			/* ラック内位置番号 */
//	char	cPosNum[11+1];				/* 位置番号 */
	char	cCom1[16+1];				/* コメント１ */
	char	cCom2[16+1];				/* コメント２ */
	char	cSex[1+1];					/* 性別 */
	char	cAge[3+1];					/* 年齢 */
	char	cCollBlooddDay[8+1];		/* 採血日 */
	char	cDiltCoeff[4+1];			/* 希釈係数 */
	char	cSpecimenType[1+1];			/* 検体種別 */
	char	cCntnrType[1+1];			/* 容器種別 */
	struct REQ_ITEM	sReqItem[117];		/* 依頼項目 */
	char	cReserve[16+1];				/* 予備 */
	char	cEndCode[5+1];				/* 終了コード */
};

/* 電解質測定データテキスト */
struct MEASURE_ELEC_TXT {	
	char	cStartCode[1+1];			/* 開始コード */
	char	cFrameNum[1+1];				/* フレーム番号 */
	char	cTextType[1+1];				/* テキスト種別 */
	char	cDevIdentifNum[1+1];		/* 装置識別番号 */
	char	cAllBlockNum[2+1];			/* 全ブロック数 */
	char	cBlockNum[2+1];				/* ブロック番号 */
	char	cItemNumInBlk[2+1];			/* ブロック内項目数 */
	char	cInspectDay[8+1];			/* 検査日 */
	char	cInspectTm[6+1];			/* 検査時間 */
	char	cSpecimenDiv[1+1];			/* 検体区分 */
	char	cIdSpec[1+1];				/* ID仕様 */
	char	cIdSpecimenId[13+1];		/* 検体ID */
	char	cRackNum[8+1];				/* ラック番号 */
	char	cRackPosNum[2+1];			/* ラック内位置番号 */
	char	cTtNum[2+1];				/* TT番号 */
	char	cCupNum[2+1];				/* CUP位置番号 */
	char	cReserve[16+1];				/* 予備 */
	char	cCom1[16+1];				/* コメント１ */
	char	cCom2[16+1];				/* コメント２ */
	char	cSex[1+1];					/* 性別 */
	char	cAge[3+1];					/* 年齢 */
	char	cCollBlooddDay[8+1];		/* 採血日 */
	char	cDiltCoeff[4+1];			/* 希釈係数 */
	char	cSpecimenType[1+1];			/* 検体種別 */
	char	cCntnrType[1+1];			/* 容器種別 */
	char	cItemNum[3+1];				/* 項目番号 */
	char	cAnalysCond[1+1];			/* 分析条件 */
	char	cMeasureVal[8+1];			/* 測定値 */
	char	cMark[3+1];					/* マーク */
	char	cEditDatMark[1+1];			/* 編集データマーク */
	char	cUserCode[3+1];				/* ユーザーコード */
	char	cMeasureBlkNum[1+1];		/* 測定ブロック番号 */
	char	cEndCode[5+1];				/* 終了コード */
};

/* 分析機情報 */
typedef struct bunseki_inf {
	char	aIpAddr[100];				/* IPアドレス */
	int		iPortNum;					/* ポート番号 */
	char	aGouki[4];					/* 号機番号 */
	/* ADD 2006-08-21 E.Osada 送信タイマ追加 */
	int		iSendTimer;					/* 送信タイマ(msec) */
}BUNSEKI_INF;

/* X-M情報 */
typedef struct xbarm_inf {
	int		iGoukiNum;					/* 号機 */
	int		iModuleNum;					/* モジュール */
	char	kmkcd[8];					/* 項目番号 */
	int		iNumCnt;					/* カウンタ */
	int		knsseqst;					/* 検査SEQ-START */
	int		knsseqed;					/* 検査SEQ-END */
	int		bskseqst;					/* 分析機SEQ-START */
	int		bskseqed;					/* 分析機SEQ-END */
	int		pltseqst;					/* プロットSEQ-START */
	int		pltseqed;					/* プロットSEQ-END */
	double	xbarmkka;					/* X-M結果 */
	double	xbarmsum;					/* X-M合計値 */
	int		xmcount;					/* X-Mカウント */
	char	xmchk;						/* X-M結果出力許可フラグ */
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** X-M合計値だけでは計算が合わない場合がある ***/
	double  xmsub;						/* X-M結果との差分合計 */
	char    knsgrp[17];					/* 検査グループ */
	int		iXbarmCnt;					/* 復元時に必要 */
	int		iXbarmNum;					/* 復元時に必要 */
	int		saiken;						/* 再検制御     */
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
}XBARM_INF;

#define		XBARM_ITEM_NUM		(6*7*240)	/* 号機*モジュール*項目 */
#define		PLT_UNIT_DEF		10			/* プロット単位(default) */

/* コントロール情報 */
typedef struct ctrl_inf {
	int		iGoukiNum;					/* 号機 */
	int		iModuleNum;					/* モジュール */
	char	nbkmkcd[8];					/* チャネル */
	int		ctrlno;						/* コントロールNo */
}CTRL_INF;

#define		CTRL_ITEM_NUM		(6*7*60)	/* 号機*モジュール*項目 */

/* 緊急STAT情報 */
typedef struct kinkyu_inf {
	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
}KINKYU_INF;

/* ADD E.Osada デフォルト送信タイムアウト */
#define DEFSNDTIMER		10
/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int MakeFileName( char*, char*, int );		/* ファイル名作成処理 */
extern int RealTimeChk(SOCKET_INF *p, SaikenInfo * fSaiken);
extern void GetModule (char *pFrom, int *pTo);
extern char GetXmSkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);
extern char GetXmChkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);
int chkDataAlarm(); 	/* ADD Haga 2006-08-02 */

#define sFncSyslog(p, f, m) _sFncSyslog(p, f, m, "", EXEFLG_NON, __FILE__, __LINE__)
/* システムログ出力 */
extern  void    _sFncSyslog (LOG_TRCKIND piPri, char * pcFncname,char * pcMsg , char * pcErrCode, char * pcExeFlg, char * file, long lineno) ;

/**********************************************************************/
/*  外部参照変数                                                      */
/**********************************************************************/
extern struct	stcLogMember sLog;		/* ログ出力情報構造体 */
extern char		aRcvBuf[550];			/* 受信データバッファ */
extern int		iSckConChk;				/* ソケット接続チェック */
extern time_t	tSckConTm;				/* ソケット接続タイマ */ 
extern int		iBunsekiNum;			/* 分析機号機数 */
extern int		iGouki;					/* 号機情報 */
extern char		aFileNameStr[256];		/* ファイル名エリア */
extern char		aKenorderFolder[256];	/* 検査オーダーファイル格納フォルダ名 */
extern char		aKenorderFolder2[256];	/* 検査オーダーファイル格納フォルダ２名 */
extern char		aKekkaFolder[256];		/* 検査結果格納出力先フォルダ名 */
extern char		aCtrlkkaFolder[256];	/* コントロール結果格納出力先フォルダ名 */
extern char		aMstFolder[256];		/* マスタファイル格納出力先フォルダ名 */
extern char		aKmkcdTblFolder[256];	/* 項目コード変換テーブルフォルダ名 */
extern char		aLogOutFolder[256];		/* 通信ログ出力先フォルダ名 */
extern Mechmst	*pMechmst;
extern int		iMechmstNum;
extern KINKYU_INF	*pKinkyu;
extern int		iKinkyuNum;
extern Sysknrmst	sSysknrmst;
extern Kmkmst	*pKmkmst;
extern int		iKmkmstNum;
extern Ctrlmst	*pCtrlmst;
extern int		iCtrlmstNum;
extern Knsgmst	*pKnsgmst;
extern int		iKnsgmstNum;
extern SOCKET_INF sSocketInf;			/* ソケット情報 */
extern BUNSEKI_INF *sBunsekiInf;		/* 分析機情報 */
extern Kenorder *pKenorder;				/* 検査オーダーワークエリアポインタ */
extern char		aMekbn[5];				/* 分析機区分 */
/* データアラーム処理追加 2006-07-13 E.Osada */
extern Kskbrmst *pKskbrmst;
extern int iKskbrmstNum;

/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
extern char     gXsaiken;				/* Xbarm再検制御のためのフラグ */
extern Xbarmmst *pXbarmmst;				/* X-Mレンジチェックのため追加 */
extern int iXbarmmstNum;
extern Rngchkmst *pRngchkmst;			/* 血清レンジチェックのため追加 */
extern int iRngchkmstNum;
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */

#endif /* DD201.h */
