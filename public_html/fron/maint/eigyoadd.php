<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "営業所コード追加";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);


$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(egs.ecd) from nfegsmst egs ";
	$sql = $sql . "where not exists ";
	$sql = $sql . "(select * from nfegkmst egk where egk.ecd = egs.ecd) ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt = $row[0];
	$pdst->closeCursor();

	if  ($cnt == 0)
		{
		printf("<center><h2>追加する営業所コードはありません。</h2></center>\n");
		}
	else
		{
		printf("<table align=center bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th nowrap>営業所コード</th>\n");
		printf("<th nowrap>営業所名</th>\n");
		printf("<th nowrap>報告区分</th>\n");
		printf("</tr>\n");

		printf("<FORM ACTION=\"eigyoadd1.php\" METHOD=\"POST\">\n");
		$i = 0;
		$sql = "";
		$sql = $sql . "select egs.ecd,egs.egsnm from nfegsmst egs ";
		$sql = $sql . "where not exists ";
		$sql = $sql . "(select * from nfegkmst egk where egk.ecd = egs.ecd) ";
		$sql = $sql . "order by egs.ecd for read only";
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",$row[0]);
			printf("<td nowrap>%s</td>\n",$row[1]);
			printf("<td nowrap>\n");
			printf("<INPUT TYPE=radio NAME=EKBN[%d] VALUE=\"1\" checked>１回目\n",$i);
			printf("<INPUT TYPE=radio NAME=EKBN[%d] VALUE=\"2\">２回目\n",$i);
			printf("<INPUT TYPE=radio NAME=EKBN[%d] VALUE=\"9\">通常分\n",$i);
			printf("</td>\n");
			printf("<INPUT TYPE=hidden NAME=ECD[%d] VALUE=\"%s\">\n",$i,$row[0]);
			$i++;
			}
		printf("</table>\n");
		printf("<BR CLEAR=ALL>\n");

		printf("<center><BUTTON name=\"submit\" value=\"submit\" type=\"submit\">追加\n");
		printf("</BUTTON></center>\n");
		printf("</FORM>\n");
		}
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
