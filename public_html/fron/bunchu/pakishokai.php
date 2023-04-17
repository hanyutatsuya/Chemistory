<?php
//==============================================================================
// Name     :    pakishokai.php
// Function :    パキパキ情報照会処理
// Return   :    無し
// Remark   :    処理概要
//               パキパキの仕分け情報を表示する
//---History--------------------------------------------------------------------
// Ver.  Date        Name                  Note
//------+-----------+---------------------+-------------------------------------
// 1.00  2008.08.16  hanyu@bml.co.jp       新規作成
// 1.01  2009.03.18  k-yokota@bml.co.jp    管理№200946 検体バーコード出力機能追加
//==============================================================================
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("パキパキ情報照会");
NsfrLogOut("パキパキ情報照会");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>パキパキ情報照会</h2></center>

<?php
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 mod start ----->  
$sdate = trim($_REQUEST['SDATE']);
$item = trim($_REQUEST['ITEM']);
$saki = mb_convert_kana(trim($_REQUEST['SAKI']),"k");
$fsend = $_REQUEST['FSEND'];
//$sdate = trim($_GET['SDATE']);
//$item = trim($_GET['ITEM']);
//$saki = trim($_GET['SAKI']);
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 mod end <-----  

printf("<center><P>処理日：%s</P></center>\n",$sdate);

//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 add start ----->  
if  ($saki != "")
	{
	printf("<FORM ACTION=\"pakishokai.php\" METHOD=\"POST\">\n");
	printf("<INPUT TYPE=hidden  NAME=SDATE VALUE=\"%s\">\n",$sdate);
	printf("<INPUT TYPE=hidden  NAME=ITEM VALUE=\"%s\">\n",$item);
	printf("<INPUT TYPE=hidden  NAME=SAKI VALUE=\"%s\">\n",$saki);
	printf("<center><BUTTON type=submit name=FSEND value=\"submit\"><BIG>バーコード情報作成</BIG></BUTTON><center>\n");
	printf("</FORM>\n");
	if (!empty($fsend) && $item != "" && $saki != "")
		{

		$ret = PakiFileCreate($sdate, $item, $saki);
		
		if ($ret == 0)
			{
			printf("<P><center>\n");
			printf("<center><P>バーコード作成対象の情報はありません。</P></center>\n");
			printf("</center></P>\n");
			}
		else if ($ret > 0)
			{
			$num = $ret;
			$ret = PakinoFtpPut();
			if ($ret == TRUE)
				{
				printf("<P><center>\n");
				printf("パキパキバーコード情報を作成しました。[%s件]\n", $num);
				printf("</center></P>\n");
				}
			else
				{
				printf("<P><center>\n");
				printf("パキパキバーコード情報の送信に失敗しました。\n");
				printf("</center></P>\n");
				printf("<P><center>\n");
				printf("仕分けシステムの端末が起動しているか確認して下さい。\n");
				printf("</center></P>\n");
				}
			}
		else
			{
			printf("<P><center>\n");
			printf("パキパキバーコード情報の作成に失敗しました。\n");
			printf("</center></P>\n");
			}
		}
	}
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 add end <-----  

?>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>RACK</th>
<th>表示</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select itmcd,itmnm,zrlcknm ";
	$sql = $sql . "from fitmcmst ";
	$sql = $sql . "where itmcd between '61' and '79' and ukflg = '1' ";
	$sql = $sql . "order by itmcd for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td><A href=pakishokai.php?SDATE=%s&ITEM=%s>%s</A></td>\n",$sdate,$row[0],substr($row[1],0,4));
		printf("<td align=center><A href=pakishokai.php?SDATE=%s&ITEM=%s>%s</A></td>\n",$sdate,$row[0],$row[2]);
		printf("</tr>\n");
		}
	printf("</table>\n");

	if  ($item != "")
		{
		printf("<td>\n");
		printf("<table bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th>RACK</th>\n");
		printf("<th>記号</th>\n");
		printf("<th>WSCD</th>\n");
		printf("<th>ＷＳ名</th>\n");
		printf("</tr>\n");

		$sql = "";
		$sql = $sql . "select it.itmnm,ws.swkskid,ws.smpcd,ws.smpcdnm ";
		$sql = $sql . "from nfsmpmst ws,fitmcmst it ";
		$sql = $sql . "where it.itmcd = '$item' ";
		$sql = $sql . "and it.ukflg = '1' ";
		$sql = $sql . "and ws.itmcd = it.itmcd ";
		$sql = $sql . "and ws.ukflg = '1' ";
		$sql = $sql . "order by ws.swkskid,ws.smpcd for read only";
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			printf("<tr>\n");
			printf("<td>%s</td>\n",substr($row[0],0,4));
			printf("<td align=center>%s</td>\n",$row[1]);
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 mod start ----->  
			printf("<td align=right><A href=pakishokai.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,mb_convert_kana($row[1],"K"),$row[2]);
			printf("<td><A href=pakishokai.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,mb_convert_kana($row[1],"K"),$row[3]);
//			printf("<td align=right><A href=pakishokai.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,$row[1],$row[2]);
//			printf("<td><A href=pakishokai.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,$row[1],$row[3]);
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 mod end <-----  
			printf("</tr>\n");
			$rack = substr(trim($row[0]),0,4);
			}
		printf("</table>\n");
		printf("</td>\n");

		if  ($saki != "")
			{
			printf("<td>\n");
			printf("<table bgcolor = white border>\n");
			printf("<tr>\n");
			printf("<th>記号</th>\n");
			printf("<th>ＳＥＱ</th>\n");
			printf("<th>処理日</th>\n");
			printf("<th>検体No</th>\n");
			printf("<th>CH</th>\n");
			printf("<th>WSCD</th>\n");
			printf("<th>分注No</th>\n");
			printf("<th>アッセイラック</th>\n");
			printf("</tr>\n");

			$sql = "";
			$sql = $sql . "select sriymd,swkskid,ssseq,barcd,smpcd,aslckhno,itmseq,rckseq,chkchr ";
			$sql = $sql . "from fpkptbl ";
			$sql = $sql . "where sriymd = '$sdate' ";
			$sql = $sql . "and itmcd = '$item' ";
			$sql = $sql . "and swkskid = '$saki' ";
			$sql = $sql . "order by ssseq for read only";
			foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
				{
				printf("<tr>\n");
				printf("<td align=center>%s</td>\n",$row[1]);
				printf("<td align=right>%d</td>\n",$row[2]);
				printf("<td>%s</td>\n",ymd_edit($row[0]));
				printf("<td>%s</td>\n",barcode_edit($row[3]));
				printf("<td>%s</td>\n",$row[8]);
				printf("<td align=right>%s</td>\n",$row[4]);
				printf("<td align=right>%d</td>\n",$row[6]);
				printf("<td>%s%04d-%02d</td>\n",$rack,$row[7],$row[5]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("</td>\n");
			}
		}
	}
	else
	{
	echo "Connection failed";
	}

$conn = null;

?>
</td>
</table>

<br clear=all>

<?php
NsfrBackPage();
printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>フロンティアシステム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>

<HR>
</BODY>
</HTML>

<?php
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 add start ----->  
function PakiFileCreate($sdate, $item, $saki)
{
	$ret = -1;

	$fp = fopen("/tmp/pakino.txt","w");
	if ($fp == FALSE)
		{
		NsfrLogOut("PAKINO FILE OPEN FALSE");
		return $ret;
		}

	$conn = Get_DBConn();

	if  ($conn)
		{
		$sql = "";
		$sql = $sql . "select barcd ";
		$sql = $sql . "from fpkptbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "and itmcd = '$item' ";
		$sql = $sql . "and swkskid = '$saki' ";
		$sql = $sql . "order by ssseq for read only";
		$ret=0;
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			fprintf($fp,"%s\r\n",substr($row[0],2,9));
			$ret++;
			}
		}

	fclose($fp);
	$conn = null;

	return $ret;
}

function PakinoFtpPut()
{
	$ftphost = "virus011";
	$username = "bun";
	$passwd   = "bun";
	$remotefile = "/export/home/bun/dat/acos/pakino.txt";
	$localfile = "/tmp/pakino.txt";

	$ret = TRUE;

	$ftp_conn = ftp_connect($ftphost);
	if ($ftp_conn == FALSE)
		{
		NsfrLogOut("Coudn't connect ftp server");
		return FALSE;
		}

	if (ftp_login($ftp_conn,$username,$passwd))
		{
		NsfrLogOut("FTP Connect OK");
		if (ftp_put($ftp_conn,$remotefile,$localfile,FTP_BINARY))
			{
			$logmsg = sprintf("FTP File Put [%s] OK",$localfile);
			NsfrLogOut($logmsg);
			}
		else
			{
			$logmsg = sprintf("FTP File Put [%s] NG",$localfile);
			NsfrLogOut($logmsg);
			$ret = FALSE;
			}
		}
	else
		{
		NsfrLogOut("FTP Connect NG");
		$ret = FALSE;
		}

	ftp_close($ftp_conn);
	return $ret;
}
//2009/03/17 k-yokota@bml.co.jp バーコード出力指示 add end <-----  
?>
