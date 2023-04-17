<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "ラック・バーコード情報削除";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];
$rack  = $_REQUEST['RACK'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);


$conn = Get_DBConn();

if  ($conn)
	{
	rack_1ran($conn,$rack);

	printf("<P>\n");
	printf("<center>データーを削除しますか？</center>\n");
	printf("<BR>\n");
	printf("<FORM ACTION=\"barcddel1.php\" METHOD=\"POST\">\n");
	printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
	printf("<INPUT TYPE=hidden NAME=RACK VALUE=\"%s\">\n",$rack);
	printf("<center><BUTTON name=submit value=\"submit\" type=submit>削　除\n");
	printf("</BUTTON></center>\n");
	printf("</FORM>\n");
	printf("</P>\n");

	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<BR CLEAR=ALL>\n");
printf("<HR>\n");
NsfrBackPage();
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

<?php
function rack_1ran($conn,$id)
{
	global $sdate;

	printf("<P><center>%s</center></P>\n",mb_convert_kana($id,"A"));
	printf("<P>\n");
	printf("<table align=center bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("<th nowrap>検体No</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select barcd ";
	$sql = $sql . "from nbcdtbl where lckid = '$id' ";
	$sql = $sql . "for read only";
	$i=0;
	$j=0;
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		if  ($i == 0)
			printf("<tr>\n");
		printf("<td nowrap>%s</A></td>\n",barcode_edit($row[0]));
		$i++;
		if ($i >= 10)
			{
			printf("</tr>\n");
			$i = 0;
			}
		}
	printf("</table>\n");
	printf("<P>\n");
}
?>
