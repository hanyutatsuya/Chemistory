<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");

$title = "依頼書ナンバー検索処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$udate = trim($_POST['UDATE']);
$ino   = trim($_POST['INO']);

if  (Input_Check($udate,$ino) == TRUE)
	{
	Get_Zoku($udate,$ino);
	}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=merits.php?SDATE=%s>メリッツ処理一覧に戻る</A></center>\n",$sdate);
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

function Input_Check($udate,$ino)
	{
	if  (strlen($udate) == 0)
		{
		$udate = date("Ymd");
		input_udateino($udate,$ino);
		return(FALSE);
		}
	if  (strlen($ino) < 3)
		{
		input_udateino($udate,$ino);
		return(FALSE);
		}
	else
		{
		printf("<P>\n");
		printf("ＢＭＬ受付日：%s\n",ymd_edit($udate));
		printf("<BR>\n");
		printf("依頼書No. 　：%s%%\n",$ino);
		printf("</P>\n");
		printf("<HR>\n");
		return(TRUE);
		}
	};

function input_udateino($dd,$ino)
{
	printf("<P>\n");
	printf("受け日・依頼書No.を入力してください\n");


	printf("<FORM ACTION=\"sel_ino.php\" METHOD=\"POST\">\n");
	printf("ＢＭＬ受付日：\n");
	printf("<INPUT TYPE=text NAME=\"UDATE\" value=\"%s\" SIZE=10 MAXLENGTH=8>\n",$dd);
	printf("<BR>\n");
	printf("<BR>\n");
	printf("依頼書No. 　：\n");
	printf("<INPUT TYPE=text NAME=\"INO\" value=\"%s\" SIZE=13 MAXLENGTH=11>\n",$ino);
	printf("<BR>\n");
	printf("<BR>\n");

	printf("　　　　　　<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">検索\n");
	printf("</BUTTON>\n");
	printf("</FORM>\n");
	printf("</P>\n");
};

function Get_Zoku($dd,$ino)
{
	$conn = Get_DBConn();

	if  ($conn)
		{
		$wk = "00" . $ino ."%";

		printf("<table align=\"center\" border>\n");
		$i = 0;
		$j = 0;

		$sql = $sql . "select irino from nfztbl ";
		$sql = $sql . "where utkymd = '$dd' ";
		$sql = $sql . "and irino like '$wk' order by irino for read only";
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			if  ($i == 0)
				printf("<tr>\n");
			printf("<td><A href=../comm/nsfrshokai.php?UDATE=%s&INO=%s>%s</A></td>\n",
					$dd,substr($row[0],2,7),ino_edit($row[0]));
			$i++;
			if  ($i >= 10)
				{
				printf("</tr>\n");
				$i = 0;
				}
			}
		if  ($i > 0)
			printf("</tr>\n");
		printf("</table>\n");
		}
	else
		{
		echo "Connection failed";
		}
	$conn = null;
	return(TRUE);
};

?>




