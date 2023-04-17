<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("nsfr_html.inc");
require_once("nsfr_comm.inc");
require_once("nsfr_db.inc");
require_once("nsfr_class.inc");

$title = "検体ポジション照会";
NsfrHeadOutput($title);
NsfrLogOut($title);

$udate = trim($_REQUEST['UDATE']);
$ino   = trim($_REQUEST['INO']);
$sdate = trim($_REQUEST['SDATE']);
$kenno = trim($_REQUEST['KENNO']);
$barcd = trim($_REQUEST['BARCD']);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<FORM ACTION=\"posshokai.php\" METHOD=GET>\n");
printf("<P>\n");
printf("<center>\n");
printf("受付日\n");
printf("<INPUT TYPE=text NAME=UDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$udate);
printf("依頼書No.\n");
printf("<INPUT TYPE=text NAME=INO SIZE=13 MAXLENGTH=11 value=\"%s\">\n",$ino);
printf("</center>\n");
printf("</P>\n");
printf("<P>\n");
printf("<center>\n");
printf("処理日\n");
printf("<INPUT TYPE=text NAME=SDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$sdate);
printf("検体No.\n");
printf("<INPUT TYPE=text NAME=KENNO SIZE=13 MAXLENGTH=11 value=\"%s\">\n",$kenno);
printf("バーコードNo.\n");
printf("<INPUT TYPE=text NAME=BARCD SIZE=13 MAXLENGTH=11 value=\"%s\">\n",$barcd);
printf("</center>\n");
printf("</P>\n");
printf("<P>\n");
printf("<center>\n");
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");


	$nsfr = new Nsfr();
	$nsfr->Clear();
	$nsfr->SetUdate($udate);
	$nsfr->SetIno($ino);
	$nsfr->SetSdate($sdate);
	$nsfr->SetKenno($kenno);
	$nsfr->SetBarcd($barcd);

if  ($nsfr->GetCheck() == FALSE)
	{
	if  ($udate != NULL || $ino != NULL || $sdate != NULL || $kenno != NULL || $barcd != NULL)
		printf("<center><P>入力エラーです</P></center>\n");
	}
else
	{
	$conn = Get_DBConn();

	if  ($conn)
		{
		$nsfr->SetDBConn($conn);

		$kan = &$nsfr->GetZokusei();
		$ken = &$nsfr->GetKentai();
		$can = &$nsfr->GetCansel();
		$jzn = &$nsfr->GetJizen();
		$bkn = &$nsfr->GetBunKentai();
		$bka = &$nsfr->GetBunKeka();
		$pkp = &$nsfr->GetBunPaki();

		printf("患者情報\n");
		printf("<table align=left frame=box border>\n");

		printf("<tr>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
//		printf("<th nowrap>桁</th>\n");
//		printf("<th nowrap>受付</th>\n");
//		printf("<th nowrap>世代</th>\n");
//		printf("<th nowrap>患者ID</th>\n");
		printf("<th nowrap>患者名</th>\n");
//		printf("<th nowrap>患者名ID</th>\n");
//		printf("<th nowrap>性別</th>\n");
//		printf("<th nowrap>生年月日</th>\n");
//		printf("<th nowrap>区分</th>\n");
//		printf("<th nowrap>年齢</th>\n");
//		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>施設CD</th>\n");
//		printf("<th nowrap>SUBCD</th>\n");
		printf("<th nowrap>施設名</th>\n");
		printf("<th nowrap>営業所CD</th>\n");
//		printf("<th nowrap>新営CD</th>\n");
		printf("<th nowrap>理由</th>\n");
//		printf("<th nowrap>検体本数</th>\n");
//		printf("<th nowrap>CMT1</th>\n");
//		printf("<th nowrap>CMT2</th>\n");
//		printf("<th nowrap>CMT3</th>\n");
//		printf("<th nowrap>CMTF1</th>\n");
//		printf("<th nowrap>CMTF2</th>\n");
//		printf("<th nowrap>治</th>\n");
//		printf("<th nowrap>集</th>\n");
//		printf("<th nowrap>特緊</th>\n");
//		printf("<th nowrap>POOL</th>\n");
//		printf("<th nowrap>特注</th>\n");
//		printf("<th nowrap>作成時刻</th>\n");
//		printf("<th nowrap>更新時刻</th>\n");
		printf("</tr>\n");

		printf("<tr>\n");
		printf("<td nowrap><A href=nsfrshokai.php?UDATE=%s&INO=%s>%s</A></td>\n",
					$kan[0],substr($kan[1],2,9),ymd_edit($kan[0]));
		printf("<td nowrap><A href=nsfrshokai.php?UDATE=%s&INO=%s>%s</A></td>\n",
					$kan[0],substr($kan[1],2,9),ino_edit($kan[1]));
//		printf("<td nowrap>%s</td>\n",$kan[2]);
//		printf("<td nowrap>%s</td>\n",$kan[3]);
//		printf("<td nowrap>%d</td>\n",$kan[4]);
//		printf("<td nowrap>%s</td>\n",$kan[5]);
		printf("<td nowrap>%s</td>\n",$kan[6]);
//		printf("<td nowrap>%s</td>\n",$kan[7]);
//		printf("<td nowrap>%s</td>\n",$kan[8]);
//		printf("<td nowrap>%s</td>\n",$kan[9]);
//		printf("<td nowrap>%s</td>\n",$kan[10]);
//		printf("<td nowrap>%s</td>\n",$kan[11]);
//		printf("<td nowrap>%s</td>\n",$kan[12]);
		printf("<td nowrap>%s</td>\n",$kan[13]);
//		printf("<td nowrap>%s</td>\n",$kan[14]);
		printf("<td nowrap>%s</td>\n",$kan[15]);
		printf("<td nowrap>%s-%s</td>\n",$kan[16],$kan[17]);
//		printf("<td nowrap>%s</td>\n",$kan[18]);
		printf("<td nowrap>%s</td>\n",$kan[19]);
//		printf("<td nowrap>%s</td>\n",$kan[20]);
//		printf("<td nowrap>%s</td>\n",$kan[21]);
//		printf("<td nowrap>%s</td>\n",$kan[22]);
//		printf("<td nowrap>%s</td>\n",$kan[23]);
//		printf("<td nowrap>%s</td>\n",$kan[24]);
//		printf("<td nowrap>%s</td>\n",$kan[25]);
//		printf("<td nowrap>%s</td>\n",$kan[26]);
//		printf("<td nowrap>%s</td>\n",$kan[27]);
//		printf("<td nowrap>%s</td>\n",$kan[28]);
//		printf("<td nowrap>%s</td>\n",$kan[29]);
//		printf("<td nowrap>%s</td>\n",$kan[30]);
//		printf("<td nowrap>%s</td>\n",substr($kan[31],0,19));
//		printf("<td nowrap>%s</td>\n",substr($kan[32],0,19));
		printf("</tr>\n");
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("認識ポジション情報 \n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>装置No.</th>\n");
		printf("<th nowrap>トレーID:POS</th>\n");
		printf("<th nowrap>ラックID:POS</th>\n");
		printf("<th nowrap>測定量</th>\n");
		printf("<th nowrap>複数F</th>\n");
		printf("<th nowrap>認識時刻</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetKentaiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$ken[$i][0],substr($ken[$i][1],2,9),ymd_edit($ken[$i][0]));
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$ken[$i][0],substr($ken[$i][1],2,9),barcode_edit($ken[$i][1]));
			printf("<td nowrap>%s</td>\n",$ken[$i][8]);
			printf("<td nowrap>%s</td>\n",$ken[$i][18]);
			printf("<td nowrap>%s-%02d</td>\n",$ken[$i][19],$ken[$i][20]);
			printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%02d</td>\n",
					$ken[$i][0],$ken[$i][21],$ken[$i][21],$ken[$i][22]);
			printf("<td nowrap>%d</td>\n",$ken[$i][32]);
			printf("<td nowrap>%s</td>\n",$ken[$i][47]);
			printf("<td nowrap>%s</td>\n",substr($ken[$i][53],0,19));
			printf("</tr>\n");
			}

		if ($nsfr->GetCanselCount() > 0)
			{
			for ($i=0;$i<$nsfr->GetCanselCount();$i++)
				{
				printf("<tr>\n");
				printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
						$can[$i][0],substr($can[$i][1],2,9),ymd_edit($can[$i][0]));
				printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
						$can[$i][0],substr($can[$i][1],2,9),barcode_edit($can[$i][1]));
				printf("<td nowrap>%s</td>\n",$can[$i][8]);
				printf("<td nowrap>%s</td>\n",$can[$i][18]);
				printf("<td nowrap>%s-%02d</td>\n",$can[$i][19],$can[$i][20]);
				printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%02d</td>\n",
						$can[$i][0],$can[$i][21],$can[$i][21],$can[$i][22]);
				printf("<td nowrap>%s</td>\n",$can[$i][47]);
				printf("<td nowrap>%s</td>\n",substr($can[$i][53],0,19));
				printf("</tr>\n");
				}
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		if ($nsfr->GetJizenCount() > 0)
			{
			printf("<BR>\n");
			printf("事前登録情報\n");
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>検体No.</th>\n");
//			printf("<th nowrap>SEQ</th>\n");
			printf("<th nowrap>コメント</th>\n");
			printf("<th nowrap>作成時刻</th>\n");
//			printf("<th nowrap>解除時刻</th>\n");
			printf("<th nowrap>作業者ID</th>\n");
//			printf("<th nowrap>解除者ID</th>\n");
			printf("</tr>\n");

			for ($i=0;$i<$nsfr->GetJizenCount();$i++)
				{
				printf("<tr>\n");
				printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
						$jzn[$i][0],substr($jzn[$i][1],2,9),ymd_edit($jzn[$i][0]));
				printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
						$jzn[$i][0],substr($jzn[$i][1],2,9),barcode_edit($jzn[$i][1]));
//				printf("<td nowrap>%d</td>\n",$jzn[$i][2]);
				printf("<td nowrap>%s</td>\n",$jzn[$i][3]);
				printf("<td nowrap>%s</td>\n",substr($jzn[$i][4],0,19));
//				printf("<td nowrap>%s</td>\n",substr($jzn[$i][5],0,19));
				printf("<td nowrap>%s</td>\n",$jzn[$i][6]);
//				printf("<td nowrap>%s</td>\n",$jzn[$i][7]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("<BR clear=all>\n");
			}

		printf("<BR>\n");
		printf("分注元ポジション情報\n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>３－ＩＤ</th>\n");
		printf("<th nowrap>ラックID:POS</th>\n");
		printf("<th nowrap>トレーID:POS</th>\n");
		printf("<th nowrap>コンテナ</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunKentaiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$bkn[$i][0],substr($bkn[$i][1],2,9),ymd_edit($bkn[$i][0]));
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$bkn[$i][0],substr($bkn[$i][1],2,9),barcode_edit($bkn[$i][1]));
			if (trim($bkn[$i][11])== "")
				{
				printf("<td nowrap></td>\n");
				}
			else
				{
				printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s-%02d</A></td>\n",
						$bkn[$i][0],$bkn[$i][11],$bkn[$i][11],(($bkn[$i][7]-1)%5)*10+$bkn[$i][9]);
				}
			printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%2d</td>\n",
					$bkn[$i][0],$bkn[$i][8],$bkn[$i][8],$bkn[$i][9]);
			printf("<td nowrap>%s-%2d</td>\n",$bkn[$i][6],$bkn[$i][7]);
			printf("<td nowrap>%s</td>\n",$bkn[$i][10]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("アッセイラック情報\n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>装置No.</th>\n");
		printf("<th nowrap>MODNo.</th>\n");
		printf("<th nowrap>AラックID:POS</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>結果</th>\n");
		printf("<th nowrap>分注時刻</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunKekaCount();$i++)
			{
			if (trim($bka[$i][10]) == "")
				continue;

			printf("<tr>\n");
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$bka[$i][0],substr($bka[$i][1],2,9),ymd_edit($bka[$i][0]));
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$bka[$i][0],substr($bka[$i][1],2,9),barcode_edit($bka[$i][1]));
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",
					$bka[$i][3],$bka[$i][3]);
			printf("<td nowrap>%s</td>\n",$bka[$i][6]);
			printf("<td nowrap>%s</td>\n",$bka[$i][7]);
			if ($bka[$i][23] == "1")
				printf("<td nowrap>%s-%s</td>\n",$bka[$i][8],$bka[$i][9]);
			else
				printf("<td nowrap>%s-%s</td>\n",$bka[$i][10],$bka[$i][12]);
			printf("<td nowrap>%s</td>\n",$bka[$i][13]);
			printf("<td nowrap>%s</td>\n",$bka[$i][14]);
			printf("<td nowrap>%s</td>\n",substr($bka[$i][26],0,19));
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("パキパキ情報\n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>分注No.</th>\n");
//		printf("<th nowrap>ITEM</th>\n");
		printf("<th nowrap>仕先</th>\n");
		printf("<th nowrap>仕先SEQ</th>\n");
//		printf("<th nowrap>検体No.</th>\n");
//		printf("<th nowrap>区分</th>\n");
//		printf("<th nowrap>SEQ</th>\n");
//		printf("<th nowrap>AラックPOS</th>\n");
//		printf("<th nowrap>RACK SEQ</th>\n");
//		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>MARK</th>\n");
//		printf("<th nowrap>出力</th>\n");
//		printf("<th nowrap>作成時刻</th>\n");
//		printf("<th nowrap>更新時刻</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunPakiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$pkp[$i][0],substr($pkp[$i][5],2,9),ymd_edit($pkp[$i][0]));
			printf("<td nowrap><A href=nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$pkp[$i][0],substr($pkp[$i][5],2,9),barcode_edit($pkp[$i][5]));
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",
					$pkp[$i][7],$pkp[$i][7]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][10]);
//			printf("<td nowrap>%s</td>\n",$pkp[$i][1]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][2]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][3]);
//			printf("<td nowrap>%s</td>\n",barcode_edit($pkp[$i][4]));
//			printf("<td nowrap>%d</td>\n",$pkp[$i][6]);
//			printf("<td nowrap>%d</td>\n",$pkp[$i][8]);
//			printf("<td nowrap>%s</td>\n",$pkp[$i][9]);
//			printf("<td nowrap>%s</td>\n",$pkp[$i][11]);
//			printf("<td nowrap>%s</td>\n",$pkp[$i][12]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][13]);
//			printf("<td nowrap>%s</td>\n",$pkp[$i][14]);
//			printf("<td nowrap>%s</td>\n",substr($pkp[$i][15],0,19));
//			printf("<td nowrap>%s</td>\n",substr($pkp[$i][16],0,19));
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		}
	else
		{
		echo "Connection failed";
		}

	}

$conn = null;
printf("<HR>\n");

NsfrBackPage();

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
