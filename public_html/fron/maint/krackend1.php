<?php
//==============================================================================
// Name     :    krackend1.php
// Function :    検体ラック完了強制登録処理
// Return   :    無し
// Remark   :    処理概要
//               指定されたラックの強制ラック完了を実施
//---History--------------------------------------------------------------------
// Ver.  Date        Name                  Note
//------+-----------+---------------------+-------------------------------------
// 1.00  2008.08.16  hanyu@bml.co.jp       新規作成
// 1.01  2008.10.15  k-yokota@bml.co.jp    障害対応(H-313)
//==============================================================================
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "検体ラック完了強制登録処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];
$rack  = trim($_REQUEST['RACK']);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<center>\n");
printf("<P>処理日：%s</P>\n",ymd_edit($sdate));
printf("<P>ラックＩＤ：%s</P>\n",$rack);
printf("</center>\n");

printf("<HR>\n");

unset($devno);

if  ($rack != NULL)
	{
	$conn = Get_DBConn();
	if  ($conn)
		{
		$sql = "select count(*) from nfktbl where sriymd = '$sdate' and lckid = '$rack' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt = $row[0];
		$pdst->closeCursor();


		if ($cnt == 0)
			{
			printf("<center>\n");
			printf("<P>ラックは未登録です</P>\n");
			printf("</center>\n");
			}
		else
			{
//2008/10/15 k-yokota@bml.co.jp H-313 mod start ----->  
			$sql = "select trayid,devno,sskflg from nfktbl where sriymd = '$sdate' and lckid = '$rack' order by sskflg fetch first row only for read only";
			$pdst = $conn->prepare($sql);
			$pdst->execute();
			$row = $pdst->fetch(PDO::FETCH_NUM);
			$trayid = $row[0];
			$devno  = $row[1];
			$sskflg = $row[2];
			$pdst->closeCursor();
			if ($sskflg != '0')
				{
				printf("<center><P>指定されたラックが格納されているトレイ：%s には認識処理中ラックが存在しません</P></center>\n",$trayid);
				unset($devno);
				}
//			$sql = "select trayid,devno from nfktbl where sriymd = '$sdate' and lckid = '$rack' fetch first row only for read only";
//			$pdst = $conn->prepare($sql);
//			$pdst->execute();
//			$row = $pdst->fetch(PDO::FETCH_NUM);
//			$trayid = $row[0];
//			$devno  = $row[1];
//			$pdst->closeCursor();
//2008/10/15 k-yokota@bml.co.jp H-313 mod end <-----  
			}
		}
	$conn = NULL;
	}

	if (isset($devno))
		{
		$ret =File_Send($sdate,$trayid,$devno);
		if ($ret == TRUE)
			printf("<center><P><FONT COLOR=RED>ラックＩＤ：%s のラック完了を登録しました</FONT></P></center>\n",$rack);
		else
			printf("<center><P><FONT COLOR=RED>ラックＩＤ：%s のラック完了が失敗しました</FONT></P></center>\n",$rack);
		}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=krackend.php?SDATE=%s>ラックＩＤ入力に戻る</A></center>\n",$sdate);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=maint.php?SDATE=%s>メンテナンス処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
<?php
function File_Send($sdate,$trayid,$devno)
	{
	$ret = TRUE;
	$stamp = date("YmdGis000_") . $devno;
	$localfile = "/tmp/" . $stamp;
	$fp = fopen($localfile,"w");
	if ($fp == FALSE)
		{
		NsfrLogOut("FILE OPEN FALSE");
		return FALSE;
		}
	fprintf($fp,"%s,%s,,,,,,,,,,,,,,,,,,,,,,,,%-10.10s,,,,\n",$sdate,$devno,$trayid);
	fclose($fp);

	switch ($devno)
		{
		case "2101":
			$ftphost = "ninrx101";
			break;
		case "2102":
			$ftphost = "ninrx102";
			break;
		case "2103":
			$ftphost = "ninrx103";
			break;
		case "2201":
			$ftphost = "ninrx104";
			break;
		case "2202":
			$ftphost = "ninrx105";
			break;
		case "2203":
			$ftphost = "ninrx106";
			break;
		case "2301":
			$ftphost = "ninrx107";
			break;
		case "2302":
			$ftphost = "ninrx108";
			break;
		case "3101":
			$ftphost = "ninrx101";
			break;
		case "3102":
			$ftphost = "ninrx102";
			break;
		case "3103":
			$ftphost = "ninrx103";
			break;
		case "3104":
			$ftphost = "ninrx104";
			break;
		case "3105":
			$ftphost = "ninrx105";
			break;
		case "3106":
			$ftphost = "ninrx106";
			break;
		case "3107":
			$ftphost = "ninrx107";
			break;
		default:
			$ftphost = "ninrx109";
			break;
		}

	$ftp_conn = ftp_connect($ftphost);
	if ($ftp_conn == FALSE)
		{
		NsfrLogOut("Coudn't connect ftp server");
		return FALSE;
		}

	if (ftp_login($ftp_conn,"nsfr","nsfr"))
		{
		NsfrLogOut("FTP Connect OK");
		$remotefile = "/home/data/CSV/" . $stamp;
		if (ftp_put($ftp_conn,$remotefile,$localfile,FTP_BINARY))
			{
			$logmsg = sprintf("FTP File Put [%s] OK",$remotefile);
			NsfrLogOut($logmsg);
			}
		else
			{
			$logmsg = sprintf("FTP File Put [%s] NG",$remotefile);
			NsfrLogOut($logmsg);
			$ret = FALSE;
			}
		if ($ret == TRUE)
			{
			$newfile = $remotefile . ".csv";
			if (ftp_rename($ftp_conn,$remotefile,$newfile))
				{
				$logmsg = sprintf("FTP File Rename [%s] OK",$newfile);
				NsfrLogOut($logmsg);
				}
			else
				{
				$logmsg = sprintf("FTP File Rename [%s] NG",$newfile);
				NsfrLogOut($logmsg);
				$ret = FALSE;
				}
			}
		}
	else
		{
		NsfrLogOut("FTP Connect NG");
		$ret = FALSE;
		}

	ftp_close($ftp_conn);
	unlink($localfile);

	return $ret;

	}
?>
