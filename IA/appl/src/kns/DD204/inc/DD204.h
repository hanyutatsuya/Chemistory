/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：DD204.h                                                      */
/* 　概　　　要：LST008通信・結果出力ヘッダ                                   */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/31     A.Yamada       新規作成                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/25     K.Ameno        X-M対応初版                        */
/******************************************************************************/
#ifndef _dd203_h
#define _dd203_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "Knsgmst.h"		/* 060418 009 */
#include "Kskbrmst2.h"		/* ADD E.Osada 2006-07-13 */
#include "Kekka.h"
#include "Ctrlkka.h"
#include "Kenorder.h"
#include "Xbarm.h"
/*	2.00	2008/09/25		K.Ameno		   X-M対応初版 --> */
/*** X-Mレンジチェックのため追加 ***/
#include "Xbarmmst.h"
/*** 血清レンジチェックのため追加 ***/
#include "Rngchkmst.h"
/*	2.00	2008/09/25		K.Ameno		   X-M対応初版 <-- */

#include "DD40101.h"

/**********************************************************************/
/*  定数宣言                                                          */
/**********************************************************************/

/***  ログが多すぎると通信エラーが発生する場合があるため ***/
/***  TESTの時だけONにしてください!!!                    ***/
//#define		_DEBUG_		/* 通常ログ */

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

/* 希釈倍率 */
#define		MAXKSKBRT			"KSKBRT_1"	/* 最低希釈倍率 */
#define		MINKSKBRT			"KSKBRT_3"	/* 最高希釈倍率 */

/* 最大受信バイト数 */
#define		MAX_RCV_NUM			247

/* データ送信時のウエイト時間 */
#define		SLEEP_USEC			30000	/* 30ms */

/* 受信メッセージの意味 */
#define		MSG_NON				0		/* なし */
#define		MSG_ORDER			1		/* 問い合わせ */
#define		MSG_RESULT			2		/* 結果送信 */
#define		MSG_PCR				3		/* 比色キャリブ結果送信 */
#define		MSG_ICR				4		/* ISEキャリブ結果送信 */

/* 通信ログ種別 */
#define		RCV_LOG				0		/* 受信データログ */
#define		SND_LOG				1		/* 送信データログ */

/* .datファイル種別 */
#define		RESULT_DAT			0		/* 検査結果ファイル */
#define		ORDER_DAT_1			1		/* 検査オーダーファイル1 */
#define		ORDER_DAT_2			2		/* 検査オーダーファイル2 */

/* フレームリトライカウンタ */
#define		FRAME_RETRY_MAX		6		/* 3回 */

/* 各タイマ設定値 */
#define		TM_WAIT_10			10		/* 10s */
#define		TM_WAIT_15			15		/* 15s */
#define		TM_WAIT_20			20		/* 20s */
#define		TM_WAIT_30			30		/* 30s */

/* ソケット接続状態 */
#define		TM_SCK_CON			10		/* ソケット接続タイマ */
#define		SCK_CON_NG			0		/* ソケット未接続 */
#define		SCK_CON_OK			1		/* 全ソケット接続完了 */

/* 最大依頼項目数 */
#define		MAX_ITEM_NUM		100		/* 最大項目数 */

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
#define		INI_FILE_NAME		"DD204_"
#define		INI_FILE_PRM		"00"

/* 注釈レコード種別 */
#define		C_RES				0		/* 結果フラグ */
#define		C_CMM				1		/* コメント */

/* ISEキャリブレーション結果レコード項目 */
#define		ITEM_NA				0		/* Na */
#define		ITEM_K				1		/* K */
#define		ITEM_CL				2		/* Na */

/* データアラーム配列定義追加 2006.07.13 E.Osada */
typedef struct sndorder {	
	int		seqnum;
	char	kntno[13+1];
	int		knssu;
	int		knssueda;
	int		bskseq;							/* 検体番号 */
	char	racktype[2+1];					/* 検体種別 */
	char	kmkcd[MAX_ITEM_NUM][7+1];		/* No. 6 項目コード */
	char	zrcd[4+1];						/* No.27 材料コード */
	char	ytiksbr[MAX_ITEM_NUM][15+1];	/* No.37 予定希釈倍率 */
	char	sbtkbn[1+1];					/* No.44 性別区分 */
	char	age[3+1];						/* No.47 年齢 */
	char	agekbn[1+1];					/* No.48 年齢区分 */
	char	sstme[8+1];						/* No.49 採取時間 */
	char	ssymd[10+1];					/* No.50 採取年月日 */
}SNDORDER;


/* ソケット情報 */
typedef struct socket_inf {
 	int		iSd;					/* ソケット番号 */
 	char	aGouki[4];				/* 分析機号機 */
	char	aHostName[100];			/* ホスト名 */
	int		iPortNum;				/* ポート番号 */
	char	aRcvTmpMsgBuf[6000];	/* 受信メッセージコピーエリア */
	char	aSndAllMsgBuf[1700];	/* 全送信メッセージエリア */
	char	aSndTmpBuf[255];		/* 送信データ一時バッファ */
	char	cRcvFrameCtrlChar;		/* 受信フレーム制御文字 */
	char	cSndFrameCtrlChar;		/* 送信フレーム制御 */
	char	cFrameNum;				/* フレーム番号 */
	char	cChkRcvData;			/* 受信データあり/なし判定 */
	char	cSndDataReq;			/* 送信データ要求あり/なし判定 */
	char	cStatus;				/* STATUS管理 */
	char	cChkRcvMessage;			/* 受信メッセージ判定 */
	char	cChkNextFrame;			/* フレーム継続/終了判定 */
	char	cSndFrameSeqNum;		/* 次回送信フレームカウンタ */
	int		iRcvMsg;				/* 受信メッセージの意味 */
	char	cRackNum[8+1];			/* ラック番号 */
	char	cRackPosNum[2+1];		/* ラック位置番号 */
	int		iSndRetryCnt;			/* フレーム送信リトライカウンタ */
	int		iSndBlockCnt;			/* 送信テキストブロックカウンタ */
	int		iSndBlockNum;			/* フレーム送信リトライカウンタ */
	int		iSndAgainReq;			/* 再送要求 */
	char	aSndAgainBuf[1700];		/* 再送用バッファ */
	Kekka* 	pKekka;					/* 検査結果情報(csv登録項目) */
	Kekka*	pKkkaChk;				/* 検査結果情報(csv登録項目) 計算チェック用 */
	int	iKkkaChkNum;				/* 検査結果情報(csv登録項目) 計算チェック用 */
	Ctrlkka	sCtrlkka;				/* コントロール結果情報(csv登録項目) */
	Xbarm	sXbarm;					/* X-M結果情報(csv登録項目) */
	SaikenInfo*	pSaiken;			/* 再検依頼情報 */
	int			iKekkaNum;			/* 再検依頼件数 */
	int			iKekkaCnt;			/* 再検依頼件数カウンタ */
	int		iOrderNum;				/* 依頼項目数 */
	SNDORDER 	sSndorder;			/* 検査オーダー情報 */
	time_t	tStartTm;				/* 通信開始タイマ */ 
	float	fTmOutVal;				/* タイマ */
	int		aPltseq[7];				/* プロットSEQ */
	int			iCtrlSeq;
	int			iCtrlSeqCnt;
	int		iSendTimer;				/* 送信タイマ(msec) */
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
/* メッセージ定義 */
/* Universal Test ID フィールド*/
struct UNI_TEST_ID {	
	char	cAppCode[5+1];				/* Application Code */
	char	cDilution[3+1];				/* Dilution */
};

/* Message Header Record(メッセージ見出しレコード) */
struct MSG_HEADER_RCD {	
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cDelmtrDef[4+1];			/* Delimiter Definition */
	char	cDeviceName[30+1];			/* 送信側の装置名称 */
	char	cComPrgVer[5+1];			/* 通信プログラムバージョン */
	char	cRcvrId[30+1];				/* Receiver ID */
	char	cMessageMean[5+1];			/* メッセージの意味 */
	char	cGenerateFactor[5+1];		/* 発生要因 */
	char	cPrcssingId[1+1];			/* Processing ID */
	char	cVersionNo[1+1];			/* Version No. */
};

/* Patient information Record(患者情報レコード) */
struct PATIENT_INF_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cPatientSex[1+1];			/* Patient Sex */
	char	cAge[3+1];					/* Age */
	char	cAgeUnit[1+1];				/* Age Unit */

};

/* Request information Record(問い合わせレコード) */
struct REQ_INF_RCD {
 	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cSampleId[22+1];			/* Sample ID. */
	char	cSampleNo[5+1];				/* Sample No. */
	char	cRackId[5+1];				/* Rack ID */
	char	cPositionNo[1+1];			/* Position No. */
	char	cRackType[2+1];				/* Rack Type */
	char	cContainerType[2+1];		/* Container Type */
	char	cUniTestId[3+1];			/* Universal Test ID */
	char	cReqInfStatCode[1+1];		/* Request Information Status Codes */
};

/* Test Order Record(項目選択レコード) */
struct TEST_ORDER_RCD {
	char		cRcdTypeId[1+1];			/* Record Type ID */
	char		cSeqNum[6+1];				/* Sequence Number */
	char		cSampleId[22+1];			/* Sample ID */
	char		cSampleNo[5+1];				/* Sample No. */
	char		cRackId[5+1];				/* Rack ID */
	char		cPositionNo[1+1];			/* Position No. */
	char		cRackType[2+1];				/* Rack Type */
	char		cContainerType[2+1];		/* Container Type */
	struct UNI_TEST_ID	sUniTestId[406];			/* Universal Test ID */
	char		cPriority[1+1];				/* Priority */
	char		cSpecimenCollDateTm[14+1];	/* Specimen Collection Date and Time */
	char		cActionCode[1+1];			/* Action Code */
	char		cSpecimenDescriptor[1+1];	/* Specimen Descriptor */
	char		cDateTmResRep_LstMod[14+1];	/* Data/Time Results Reported or Last Modified */
	char		cReportTypes[1+1];			/* Report Types */
};

/* C-RES Record(注釈レコード:結果フラグ) */
struct COMMENT_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cCmntSrc[1+1];				/* Comment Source */
	char	cCmmTxt[3+1];				/* Comment Text */
	char	cCmm1[30+1];				/* Comment1 */
	char	cCmm2[25+1];				/* Comment2 */
	char	cCmm3[20+1];				/* Comment3 */
	char	cCmm4[15+1];				/* Comment4 */
	char	cCmm5[10+1];				/* Comment5 */
	char	cCmntType[1+1];				/* Comment Type */
};

/* Result Record(結果レコード) */
struct RESULT_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cAppCode[5+1];				/* Application Code */
	char	cDilution[3+1];				/* Dilution */
	char	cDat_MeasrmntVal[15+1];		/* Data or Measurement Value */
	char	cUnits[6+1];				/* Units */
	char	cResAbnmlFlg[2+1];			/* Result Abnormal Flags */
	char	cResStat[1+1];				/* Result Status */
	char	cOprtrIdentif[6+1];			/* Operator Identification */
	char	cInstIdentif[4+1];			/* Instrument Identification */
	char	cTestStarted[14+1];			/* Date Time Test Started */
};

/* STD Data フィールド*/
struct STD_DAT {	
	char	c1stDat[6+1];				/* 1回目の吸光度データ */
	char	c1stIni_LstDat[6+1];		/* 1回目の初期または最終吸光度データ */
	char	c2ndDat[6+1];				/* 2回目の吸光度データ */
	char	c2ndIni_LstDat[6+1];		/* 2回目の初期または最終吸光度データ */
	char	cDatAlarm[3+1];				/* データアラーム */
	char	cProZoneVal[6+1];			/* プロゾーン値 */
};

/* ISEキャリブレーション結果レコード項目(Na/K/Cl) */
struct ISE_CALB_ITEM {	
	/* Na/K/Cl calibration Alarm */
	char	cCalbAlarm[3+1];		/* Calibration Alarm */
	/* Na/K/Cl data Alarm */
	char	cAlmNaibuKiden[3+1];	/* 内部標準液起電力データアラーム */
	char	cAlmLow[3+1];			/* LOW液起電力データアラーム */
	char	cAlmHigh[3+1];			/* HIGH液起電力データアラーム */
	char	cAlmCalbKiden[3+1];		/* キャリブレーション液起電力データアラーム */
	char	cAlmSlpe[3+1];			/* 表示用スロープデータアラーム */
	char	cAlmNaibuNodo[3+1];		/* 内部標準液濃度データアラーム */
	char	cAlmCalbNodo[3+1];		/* キャリブレーション液濃度データアラーム */
	char	cAlmHosei[3+1];			/* 補正係数データアラーム */
	/* Na/K/Cl data */
	char	cDatNaibuKiden[6+1];	/* 内部標準液起電力データ */
	char	cDatLow[6+1];			/* LOW液起電力データ */
	char	cDatHigh[6+1];			/* HIGH液起電力データ */
	char	cDatCalbKiden[6+1];		/* キャリブレーション液起電力データ */
	char	cDatSlpe[6+1];			/* 表示用スロープデータ */
	char	cDatNaibu[6+1];			/* 内部標準液濃度データ */
	char	cDatCalb[6+1];			/* キャリブレーション液濃度データ */
	char	cDatHosei[6+1];			/* 補正係数データ */
};

/* Caliblation data Record */
struct CALB_RCD {
	char	cRcdTypeId[1+1];			/* Record Type ID */
	char	cSeqNum[6+1];				/* Sequence Number */
	char	cSubId[3+1];				/* Record Type Sub ID */
	char	cOperatorId[6+1];			/* Operator ID */
	char	cCellNo[3+1];				/* Cell No */
	char	cInputInf[1+1];				/* Input Information */
	char	cReactionTm[2+1];			/* Reaction Time */
	char	cPointNum[2+1];				/* Number of Points */
	char	cCellBlankDat1[6+1];		/* Cell Blank Data1 */
	char	cCellBlankDat2[6+1];		/* Cell Blank Data2 */
	char	cCellBlankDat3[6+1];		/* Cell Blank Data3 */
	char	cCellBlankDat4[6+1];		/* Cell Blank Data4 */
	char	cDeltaAbsDat[38][6+1];		/* Delta ABS Data */
	char	cTestCode[8+1];				/* Test Code */
	char	cModuleId[4+1];				/* Module ID */
	char	cCalbAlarm[3+1];			/* Caribration Alarm */
	char	cSdDatField[6+1];			/* SD Data Field */
	struct STD_DAT	sStdDat[6];					/* STD Data */
	struct ISE_CALB_ITEM	sIseCalbItem[3];	/* ISEキャリブレーション結果レコード項目 */
};

/* 分析機情報 */
typedef struct bunseki_inf {
	char	aIpAddr[100];			/* IPアドレス */
	int		iPortNum;				/* ポート番号 */
	char	aGouki[4];				/* 号機番号 */
	/* ADD 2006-08-21 E.Osada 送信タイマ追加 */
	int		iSendTimer;				/* 送信タイマ(msec) */
}BUNSEKI_INF;

/* X-M情報 */
typedef struct xbarm_inf {
	int		iGoukiNum;				/* 号機 */
	int		iModuleNum;				/* モジュール */
	char	kmkcd[8];				/* 項目番号 */
	int		iNumCnt;				/* カウンタ */
	int		knsseqst;				/* 検査SEQ-START */
	int		knsseqed;				/* 検査SEQ-END */
	int		bskseqst;				/* 分析機SEQ-START */
	int		bskseqed;				/* 分析機SEQ-END */
	int		pltseqst;				/* プロットSEQ-START */
	int		pltseqed;				/* プロットSEQ-END */
	double	xbarmkka;				/* X-M結果 */
	double	xbarmsum;				/* X-M合計値 */
	int		xmcount;				/* X-Mカウント */
	char	xmchk;					/* X-M結果出力許可フラグ */
/*	2.00	2008/09/25		K.Ameno		   X-M対応初版 --> */
/*** X-M合計値だけでは計算が合わない場合がある ***/
	double	xmsub;					/* X-M結果との差分合計 */
	char    knsgrp[17];             /* 検査グループ */
	int     iXbarmCnt;              /* 復元時に必要 */
	int     iXbarmNum;              /* 復元時に必要 */
	int		saiken;					/* 再検制御     */
/*	2.00	2008/09/25		K.Ameno		   X-M対応初版 <-- */
}XBARM_INF;

#define		XBARM_ITEM_NUM		(6*7*240)	/* 号機*モジュール*項目 */
#define		PLT_UNIT_DEF		10			/* プロット単位(default) */

/* X-M情報 */
typedef struct ctrl_inf {
	int		iGoukiNum;				/* 号機 */
	int		iModuleNum;				/* モジュール */
	char	nbkmkcd[8];				/* チャネル */
	int		ctrlno;					/* コントロールNo */
}CTRL_INF;

#define		CTRL_ITEM_NUM		(6*7*60)	/* 号機*モジュール*項目 */

/* X-M情報 */
typedef struct kinkyu_inf {
	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    nbkmkcd[8];
}KINKYU_INF;

/* ADD E.Osada デフォルト送信タイムアウト */
#define DEFSNDTIMER		0
/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int MakeFileName( char*, char* , int);		/* ファイル名作成処理 */
#define sFncSyslog(p, f, m) _sFncSyslog(p, f, m, "", EXEFLG_NON, __FILE__, __LINE__)
/*  システムログ出力 */
extern  void    _sFncSyslog (LOG_TRCKIND piPri, char * pcFncname,char * pcMsg , char * pcErrCode, char * pcExeFlg, char * file, long lineno) ;
int chkDataAlarm();		//ADD E.Osada 2006-07-13
extern int RealTimeChk(SOCKET_INF *p, SaikenInfo * fSaiken);
extern void GetModule (char *pFrom, int *pTo);
extern char GetXmSkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);
extern char GetXmChkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd);

/**********************************************************************/
/*  外部参照変数                                                      */
/**********************************************************************/
extern struct	stcLogMember sLog;		/* ログ出力情報構造体 */
extern char		aRcvBuf[255];			/* 受信データバッファ */
extern int		iSckConChk;				/* ソケット接続チェック */
extern time_t	tSckConTm;				/* ソケット接続タイマ */ 
extern int		iBunsekiNum;			/* 分析機号機数 */
extern int		iGouki;					/* 号機情報 */
extern char		aFileNameStr[64];		/* ファイル名エリア */
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
int getDataAm(  char *sBuf, char *sArm  );
extern Kskbrmst *pKskbrmst;
extern int iKskbrmstNum;
/*	2.00	2008/09/25		K.Ameno		   X-M対応初版 --> */
/*** X-Mレンジチェックのため追加 ***/
extern Xbarmmst *pXbarmmst;
extern int iXbarmmstNum;
/*** 血清レンジチェックのため追加 ***/
extern Rngchkmst *pRngchkmst;
extern int iRngchkmstNum;
/*	2.00	2008/09/25		K.Ameno		   X-M対応初版 <-- */

extern int iStartCtrlSeq;			/* コントロールＮＯの初期値 血清検体とのかぶり防止  */

#endif /* DD204.h */
