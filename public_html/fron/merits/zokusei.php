<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/bun_head.inc");
require_once("../comm/kenno_edit.inc");

$title = "新規属性登録処理";
bunchu_head_output($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$udate = trim($_POST['UDATE']);
$ino   = trim($_POST['INO']);

if  (Input_Check($udate,$ino) == TRUE)
	{
//	Get_Zoku();
	}
else
	{
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
	if  (strlen($ino) == 0)
		{
		input_udateino($udate,$ino);
		return(FALSE);
		}
	else
		{
		printf("<P>\n");
		printf("ＢＭＬ受付日：%s\n",ymd_edit($udate));
		printf("<BR>\n");
		printf("依頼書No. 　：%s\n",ino_edit(ino_conv($ino)));
		printf("</P>\n");
		return(TRUE);
		}
	};

function input_udateino($dd,$ino)
{
	printf("<P>\n");
	printf("受け日・依頼書No.を入力してください\n");


	printf("<FORM ACTION=\"zokusei.php\" METHOD=\"POST\">\n");
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



?>




