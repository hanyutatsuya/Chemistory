<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "仕分けラベル出力済みフラグリセット";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<center><P>処理日：%s の仕分けラベルを再出力可能にします</P></center>\n",ymd_edit($sdate));

$conn = Get_DBConn();

if  ($conn)
	{
	printf("<center><P>\n");
	printf("<FORM ACTION=\"pakiupd.php\" METHOD=\"POST\">\n");
	printf("<INPUT TYPE=radio NAME=ITEM VALUE=\"00\" checked><TT>全て　\n</TT><BR>\n");

	$sql = "";
	$sql = $sql . "select itmcd,itmnm,zrlcknm ";
	$sql = $sql . "from fitmcmst ";
	$sql = $sql . "where itmcd between '61' and '79' and ukflg = '1' ";
	$sql = $sql . "order by itmcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<INPUT TYPE=radio NAME=ITEM VALUE=\"%s\"><TT>%s:%s\n</TT><BR>\n",
				$row[0],substr(trim($row[1]),0,4),trim($row[2]));
		}

	printf("<BR>\n");
	printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
	printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">実行\n");
	printf("</BUTTON>\n");
	printf("</FORM>\n");
	printf("</P></center>\n");

	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<HR>\n");
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
