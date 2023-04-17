<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("非分注結果送信処理",60);
NsfrLogOut("非分注結果送信処理");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>非分注結果送信処理</h2></center>

<?php
$sdate = $_REQUEST[SDATE];
$send1 = $_REQUEST[SEND1];
$send2 = $_REQUEST[SEND2];
$start = $_REQUEST[START];

printf("<h2>\n");
printf("<center>処理日：%s</center>\n",$sdate);
printf("</h2>\n");


$conn = Get_DBConn();
if  ($conn)
	{
	$updflg = 0;
	if  (!empty($send1))
		{
		$sql = "";
		$sql = $sql . "update nsetuptbl set setkbnnm = '1',kouhm = current timestamp ";
		$sql = $sql . "where setkbn = '38' and kmkkbn = '04' and setkbnnm = '0' " ;
		$conn->beginTransaction();
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == TRUE)
			{
			$conn->commit();
			printf("<center><P><FONT color=red>非分注結果送信指示をしました。</FONT></P></center>\n");
			NsfrLogOut(sprintf("非分注結果送信指示"));
			}
		else
			{
			printf("<center><P><FONT color=red>非分注結果送信指示を失敗しました。</FONT></P></center>\n");
			NsfrLogOut(sprintf("非分注結果送信指示失敗"));
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			}
		}

	if  (!empty($send2))
		{
		$sql = "";
		$sql = $sql . "update nsetuptbl set setkbnnm = '$start',kouhm = current timestamp ";
		$sql = $sql . "where setkbn = '38' and kmkkbn = '03' " ;
		$conn->beginTransaction();
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == TRUE)
			{
			$conn->commit();
			printf("<center><P><FONT color=red>自動送信開始時刻を変更しました。</FONT></P></center>\n");
			NsfrLogOut(sprintf("自動送信開始時刻変更"));
			}
		else
			{
			printf("<center><P><FONT color=red>自動送信開始時刻変更を失敗しました。</FONT></P></center>\n");
			NsfrLogOut(sprintf("自動送信開始時刻変更失敗"));
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			}
		}

	if  (empty($send1) && empty($send2))
		{
		printf("<center><P>　</P></center>\n");
		}

	$sql = "select * from nsetuptbl where setkbn = '38' order by setkbn,kmkkbn for read only";
	$i=0;
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$setup[$i] = $row[2];
		$i++;
		}

	}
else
	{
	echo "Connection failed";
	}
$conn = null;

$SetHH = (int)substr($setup[3],0,2);
$SetMM = (int)substr($setup[3],2,4);
$CurHH = (int)date("H");
$CurMM = (int)date("i");

if ($SetHH < 12)
	$SetHH = $SetHH + 24;
if ($CurHH < 12)
	$CurHH = $CurHH + 24;


printf("<FORM ACTION=\"hibunchu.php?SDATE=%s\" METHOD=\"POST\">\n",$sdate);
//printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
if ($SetHH > $CurHH || ($SetHH == $CurHH && $SetMM > $CurMM))
	{
	printf("<DIV><BIG>\n");
	printf("<center>\n");
	printf("<INPUT type=submit name=SEND1 value=\" 非分注結果送信 \">\n");
	printf("</center>\n");
	printf("</BIG></DIV>\n");
	}

printf("<BR>\n");

printf("<DIV align=right>\n");
printf("自動送信時刻\n");
printf("<INPUT TYPE=text NAME=START SIZE=6 MAXLENGTH=4 value=%s>\n",$setup[3]);

if ($SetHH > $CurHH || ($SetHH == $CurHH && $SetMM > $CurMM))
	{
	printf("<INPUT type=submit name=SEND2 value=\"変　更\">\n");
	}
printf("</DIV>\n");

printf("</FORM>\n");

if (count($setup) > 5)
	{
	printf("<table align=center bgcolor=white border>\n");
	printf("<tr>\n");
	printf("<th>送信処理時刻</th>\n");
	printf("</tr>\n");

	for ($i=5;$i<count($setup);$i++)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$setup[$i]);
		printf("</tr>\n");
		}
	printf("</table>\n");
	}

?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>フロンティアシステムシステム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
