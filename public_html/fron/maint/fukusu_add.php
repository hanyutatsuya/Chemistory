<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_class.inc");
require_once("../comm/ssmst_class.inc");

$title = "複数本取り検体登録処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$type   = $_POST['TYPE'];
$sdate  = $_POST['SDATE'];
$kenno  = $_POST['KENNO'];
$sskbn  = trim($_POST['SSKBN']);
$kenseq = (int)trim($_POST['KENSEQ']);
$kenno1 = $_POST['KENNO1'];
$kenno2 = $_POST['KENNO2'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>処理日 ：%s</P>\n",ymd_edit($sdate));
printf("<P>検体No.：%s</P>\n",kenno_edit(barcode_conv($kenno)));

if  (Input_Check() == TRUE)
	{
	$conn = Get_DBConn();
	$nsfr = new Nsfr($conn);
	$nsfr->Clear();
	$nsfr->SetSdate($sdate);
	$nsfr->SetKenno($kenno);

	switch ($type)
		{
		case "0":
			//	複雑系複数登録済みに追加登録
			$ret = Fukuzatsu_Add($nsfr);
			break;
		case "1":
			//	単純系認識済み検体に複数検体を追加登録
			$ret = Tanjun_Add($nsfr);
			break;
		case "2":
			//	単純系未認識検体に複数登録処理
			$ret = Tanjun_2Hon($nsfr);
			break;
		}

	if  ($ret == TRUE)
		{
		printf("<P><FONT color=blue>複数本取り登録を行いました。</FONT></P>\n");
		}
	else
		{
		printf("<P><FONT color=red>複数本取り登録ができませんでした。</FONT></P>\n");
		}
	}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=fukusu.php?SDATE=%s>複数本取り検体登録処理に戻る</A></center>\n",$sdate);
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

//	入力値チェック
function Input_Check()
{
	global $type,$sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;

	if  (ymd_check($sdate) != TRUE)
		{
		printf("<P><FONT color=red>処理日入力エラーです。</FONT></P>\n");
		return(FALSE);
		}

	if  ($type == 0 || $type == 1)
		{
		if (strlen(barcode_conv($kenno1)) < 9 ||
			strncmp(barcode_conv($kenno),barcode_conv($kenno1),9) != 0)
			{
			printf("<P>検体ナンバー [%s][%s]</P>\n",$kenno ,barcode_conv($kenno));
			printf("<P>検体ナンバー1[%s][%s]</P>\n",$kenno1,barcode_conv($kenno1));
			printf("<P><FONT color=red>検体ナンバー入力エラーです。</FONT></P>\n");
			return(FALSE);
			}
		}
	else
		{
		if (strlen(barcode_conv($kenno1)) < 9 ||
			strlen(barcode_conv($kenno2)) < 9 ||
			strncmp(barcode_conv($kenno),barcode_conv($kenno1),9) != 0 ||
			strncmp(barcode_conv($kenno),barcode_conv($kenno2),9) != 0)
			{
			printf("<P>検体ナンバー [%s][%s]</P>\n",$kenno ,barcode_conv($kenno));
			printf("<P>検体ナンバー1[%s][%s]</P>\n",$kenno1,barcode_conv($kenno1));
			printf("<P>検体ナンバー2[%s][%s]</P>\n",$kenno2,barcode_conv($kenno2));
			printf("<P><FONT color=red>検体ナンバー入力エラーです。</FONT></P>\n");
			return(FALSE);
			}
		}

	return(TRUE);
}

//	複雑系複数登録済みに追加登録
function Fukuzatsu_Add($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;


	printf("複雑系検体<BR>\n");
	printf("処理日 ：%s<BR>\n",ymd_edit($sdate));
	printf("検体No.：%s<BR>\n",kenno_edit(barcode_conv($kenno)));

	printf("検体No.：%s を複数本登録<BR>\n",kenno_edit(barcode_conv($kenno1)));

	return(TRUE);
}

//	単純系認識済み検体に複数検体を追加登録
function Tanjun_Add($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;

	printf("単純系検体<BR>\n");
	printf("処理日 ：%s<BR>\n",ymd_edit($sdate));
	printf("検体No.：%s<BR>\n",kenno_edit(barcode_conv($kenno)));

	printf("検体No.：%s を複数本追加<BR>\n",kenno_edit(barcode_conv($kenno1)));

	return(TRUE);
}

//	単純系未認識検体に複数登録処理
function Tanjun_2Hon($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;

	printf("単純系検体<BR>\n");
	printf("処理日 ：%s<BR>\n",ymd_edit($sdate));
	printf("検体No.：%s<BR>\n",kenno_edit(barcode_conv($kenno)));

	printf("検体No.：%s を複数本登録<BR>\n",kenno_edit(barcode_conv($kenno1)));
	printf("検体No.：%s を複数本登録<BR>\n",kenno_edit(barcode_conv($kenno2)));

	return(TRUE);
}



?>

