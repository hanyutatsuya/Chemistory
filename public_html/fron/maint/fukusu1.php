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

$sdate  = $_POST['SDATE'];
$kenno  = $_POST['KENNO'];
$sskbn  = trim($_POST['SSKBN']);
$kenseq = (int)trim($_POST['KENSEQ']);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>処理日 ：%s</P>\n",ymd_edit($sdate));
printf("<P>検体No.：%s</P>\n",kenno_edit(barcode_conv($kenno)));

//$conn = new PDO('odbc:NSFRDB1','nsfr','nsfr');
$conn = Get_DBConn();
$nsfr = new Nsfr($conn);
$nsfr->Clear();
$nsfr->SetSdate($sdate);
$nsfr->SetKenno($kenno);

ShowResult($nsfr);

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
function ShowResult($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq;

//	printf("[[%s]]<BR>\n",$nsfr->GetZokuseiCount());
	if  ($nsfr->GetZokuseiCount() == 0)
		{
		printf("<HR>\n");
		printf("<P>該当する依頼はありません。</P>\n");
		printf("<P>\n");
		printf("複数本登録する検体No.を入力してください\n");
		printf("<FORM ACTION=\"fukusu1.php\" METHOD=\"POST\">\n");
		printf("<INPUT TYPE=text NAME=\"KENNO\" SIZE=14 MAXLENGTH=13>\n");

		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">検索\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");

		return(FALSE);
		}

	//	患者名表示
	$kan = &$nsfr->GetZokusei();
	printf("<P>患者名 ：%s</P>\n",$kan[6]);

	$ssmst = new SsMst($conn);

	$kri = &$nsfr->GetKKentai();

	//	仕分け種類表示
	if  ($sskbn == "")
		{
		if  ($nsfr->GetKKentaiCount() == 1)
			{
			printf("<P>材料は<FONT color=red><STRONG>(%s)</STRONG></FONT>です。</P>\n",$ssmst->GetRName($kri[0][10]));
//			printf("<HR>\n");
			$kenseq = (int)$kri[0][2];
			}
		else
			{
			printf("<HR>\n");
			printf("<P>\n");
			printf("材料が複数依頼されています。<BR>\n");
			printf("複数登録する材料を選択してください。<BR>\n");
			printf("</P>\n");
			printf("<P>\n");
			printf("<FORM ACTION=\"fukusu1.php\" METHOD=\"POST\">\n");
			for ($i=0;$i<$nsfr->GetKKentaiCount();$i++)
				{
				printf("<INPUT TYPE=radio NAME=SSKBN VALUE=\"%s\" ",$kri[$i][10]);
				if  (strcmp($kri[$i][10],"01") == 0)
					printf("checked");
				printf("><TT>%s\n</TT><BR>\n",$ssmst->GetRName($kri[$i][10]));
				}
			printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
			printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
			printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">選択\n");
			printf("</BUTTON>\n");
			printf("</FORM>\n");
			printf("</P>\n");
			return(FALSE);
			}
		}
	else
		{
		printf("<P>材料<FONT color=red><STRONG>(%s)</STRONG></FONT>が選択されています。</P>\n",$ssmst->GetRName($sskbn));
//		printf("<HR>\n");
		for ($i=0;$i<$nsfr->GetKKentaiCount();$i++)
			{
			if  (strcmp($kri[$i][10],$sskbn) == 0)
				{
				$kenseq = $kri[$i][2];
				break;
				}
			}
		}

	//	登録済み複数本確認表示
	$cnt = 0;
	for ($i=0;$i<$nsfr->GetKKentaiCount();$i++)
		{
		if  ((int)$kri[$i][2] == $kenseq)
			$cnt++;
		}
	if  ($cnt > 1)
		{
		printf("<P>(%d)件の複数本検体が登録済みです。</P>\n",$cnt);

		printf("<table align=left border>\n");
		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>通常量</th>\n");
		printf("<th nowrap>少量量</th>\n");
		printf("<th nowrap>小児量</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetKKentaiCount();$i++)
			{
			if  ((int)$kri[$i][2] == $kenseq)
				{
				printf("<td nowrap>%s</td>\n",ymd_edit($kri[$i][0]));
				printf("<td nowrap>%s</td>\n",barcode_edit($kri[$i][1]));
				printf("<td nowrap>%s</td>\n",$ken[$i][7]);
				printf("<td nowrap>%d</td>\n",$ken[$i][17]);
				printf("<td nowrap>%d</td>\n",$ken[$i][18]);
				printf("<td nowrap>%d</td>\n",$ken[$i][19]);
				printf("</tr>\n");
				}
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");
		printf("<HR>\n");
		printf("<P>\n");
		printf("複数本登録する検体No.を入力してください\n");
		printf("<FORM ACTION=\"fukusu_add.php\" METHOD=\"POST\">\n");
		printf("<INPUT TYPE=text NAME=\"KENNO1\" SIZE=14 MAXLENGTH=13>\n");

		printf("<INPUT TYPE=hidden NAME=\"TYPE\" value=\"0\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
		printf("<INPUT TYPE=hidden NAME=\"SSKBN\" value=\"%s\">\n",$sskbn);
		printf("<INPUT TYPE=hidden NAME=\"KENSEQ\" value=\"%d\">\n",$kenseq);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">登録\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");
		return(FALSE);
		}

	//	認識済み検体表示
	$ken = &$nsfr->GetKentai();
	$cnt = 0;
	for ($i=0;$i<$nsfr->GetKentaiCount();$i++)
		{
		if  ((int)$ken[$i][9] == $kenseq)
			$cnt++;
		}

	if  ($cnt == 0)
		{
		printf("<P>検体は未認識です。</P>\n");
		printf("<HR>\n");
		printf("<P>\n");
		printf("複数本登録する検体No.を入力してください\n");
		printf("<FORM ACTION=\"fukusu_add.php\" METHOD=\"POST\">\n");
		printf("検体No. １本目<INPUT TYPE=text NAME=\"KENNO1\" SIZE=14 MAXLENGTH=13>\n");
		printf("<BR>\n");
		printf("検体No. ２本目<INPUT TYPE=text NAME=\"KENNO2\" SIZE=14 MAXLENGTH=13>\n");
		printf("<BR>\n");

		printf("<INPUT TYPE=hidden NAME=\"TYPE\" value=\"2\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
		printf("<INPUT TYPE=hidden NAME=\"SSKBN\" value=\"%s\">\n",$sskbn);
		printf("<INPUT TYPE=hidden NAME=\"KENSEQ\" value=\"%d\">\n",$kenseq);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">登録\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");
		}
	else
		{
		printf("<P>(%d)件の検体が認識済みです。</P>\n",$cnt);

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>装置No.</th>\n");
		printf("<th nowrap>トレーID:POS</th>\n");
		printf("<th nowrap>ラックID:POS</th>\n");
		printf("<th nowrap>通常量</th>\n");
		printf("<th nowrap>少量量</th>\n");
		printf("<th nowrap>小児量</th>\n");
		printf("<th nowrap>測定量</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetKentaiCount();$i++)
			{
			if  ((int)$ken[$i][9] == $kenseq)
				{
				printf("<td nowrap>%s</td>\n",ymd_edit($ken[$i][0]));
				printf("<td nowrap>%s</td>\n",barcode_edit($ken[$i][1]));
				printf("<td nowrap>%s</td>\n",$ken[$i][8]);
				printf("<td nowrap>%s</td>\n",$ken[$i][18]);
				printf("<td nowrap>%s-%02d</td>\n",$ken[$i][19],$ken[$i][20]);
				printf("<td nowrap>%s-%02d</td>\n",$ken[$i][21],$ken[$i][22]);
				printf("<td nowrap>%d</td>\n",$ken[$i][29]);
				printf("<td nowrap>%d</td>\n",$ken[$i][30]);
				printf("<td nowrap>%d</td>\n",$ken[$i][31]);
				printf("<td nowrap>%d</td>\n",$ken[$i][32]);
				printf("</tr>\n");
				}
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");
		printf("<HR>\n");

		printf("<P>\n");
		printf("複数本登録する検体No.を入力してください\n");
		printf("<FORM ACTION=\"fukusu_add.php\" METHOD=\"POST\">\n");
		printf("<INPUT TYPE=text NAME=\"KENNO1\" SIZE=14 MAXLENGTH=13>\n");

		printf("<INPUT TYPE=hidden NAME=\"TYPE\" value=\"1\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
		printf("<INPUT TYPE=hidden NAME=\"SSKBN\" value=\"%s\">\n",$sskbn);
		printf("<INPUT TYPE=hidden NAME=\"KENSEQ\" value=\"%d\">\n",$kenseq);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">登録\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");
		}

	return(TRUE);

};

?>

