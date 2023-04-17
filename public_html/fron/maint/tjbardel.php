<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "ラック・バーコード情報削除（１０本ラック）";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);


$conn = Get_DBConn();

if  ($conn)
	{
	rack_1ran($conn,"10");
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<BR CLEAR=ALL>\n");
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

//	printf("<P><center>%s</center></P>\n",mb_convert_kana($id,"R"));
	printf("<P>\n");
	printf("<table align=center bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("<th nowrap>ラックID</th>\n");
	printf("</tr>\n");

	$sql = "";
//2009/01/19 k-yokota@bml.co.jp 10本ラックで２重登録エラーが発生した時に情報削除不可 mod start -----> 
	$sql = $sql . "select distinct lckid ";
	$sql = $sql . "from nbcdtbl where lckid like '1%' and lckid not like '1X%' ";
	$sql = $sql . "order by lckid for read only";
//	$sql = $sql . "select ck.lckid ";
//	$sql = $sql . "from nfkidctbl ck where ck.sskbn = '01' and lckid like '1%' and lckid not like '1X%' ";
//	$sql = $sql . "and not exists (select * from nfktbl where sriymd = '$sdate' and lckid = ck.lckid) ";
//	$sql = $sql . "order by ck.lckid for read only";
//2009/01/19 k-yokota@bml.co.jp 10本ラックで２重登録エラーが発生した時に情報削除不可 mod end -----> 
	$i=0;
	$j=0;
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		if  ($i == 0)
			printf("<tr>\n");
		printf("<td nowrap><A href=barcddel.php?SDATE=%s&RACK=%s>%s</A></td>\n",$sdate,$row[0],$row[0]);
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
