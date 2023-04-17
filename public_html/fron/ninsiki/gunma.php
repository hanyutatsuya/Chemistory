<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("群馬臨床バーコード情報作成処理");
NsfrLogOut("群馬臨床バーコード情報作成処理");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>群馬臨床バーコード情報作成処理</h2></center>

<?php
$sdate = $_REQUEST['SDATE'];

$ret = GunmaFileCreate($sdate);

if ($ret == TRUE)
	{
	$ret = KennoFtpPut();
	if ($ret == TRUE)
		{
		$app = "/usr/bin/rsh virus011 -l bun gunma.sh";
		shell_exec($app);
		printf("<P><center>\n");
		printf("群馬臨床バーコード情報を作成しました。\n");
		printf("</center></P>\n");
		}
	else
		{
		printf("<P><center>\n");
		printf("群馬臨床バーコード情報を作成に失敗しました。\n");
		printf("</center></P>\n");
		}
	}
else
	{
	printf("<P><center>\n");
	printf("群馬臨床バーコード情報を作成に失敗しました。\n");
	printf("</center></P>\n");
	}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>検体認識システム照会処理一覧に戻る</A></center>\n",$sdate);
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
function GunmaFileCreate($sdate)
{
	$fp = fopen("/tmp/kenno.txt","w");
	if ($fp == FALSE)
		{
		NsfrLogOut("KENNO FILE OPEN FALSE");
		return FALSE;
		}

	$conn = Get_DBConn();

	if  ($conn)
		{
		$sql = "";
		$sql = $sql . "select distinct zk.irino,kn.kntno,zk.rucd ";
		$sql = $sql . "from nfztbl zk,nkktbl kn ";
		$sql = $sql . "where zk.utkymd = '$sdate' ";
		$sql = $sql . "and zk.irino like '00073%' ";
		$sql = $sql . "and kn.utkymd = zk.utkymd ";
		$sql = $sql . "and kn.irino = zk.irino ";
		$sql = $sql . "order by kn.kntno ";
		$sql = $sql . "for read only";
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			fprintf($fp,"%s01\r\n",substr($row[1],2,7));
			if ($row[2] == "F")
				fprintf($fp,"%s51\r\n",substr($row[1],2,7));
			}
		}

	fclose($fp);
	$conn = null;

	return TRUE;
}

function KennoFtpPut()
{
	$ftphost = "virus011";
	$username = "bun";
	$passwd   = "bun";
	$remotefile = "/tmp/kenno.txt";
	$localfile = "/tmp/kenno.txt";

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
?>
