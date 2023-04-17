<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("nsfr_html.inc");
require_once("nsfr_comm.inc");
require_once("nsfr_db.inc");
require_once("nsfr_class.inc");

$title = "認識・フロンティアＤＢ照会";
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

printf("<FORM ACTION=\"nsfrshokai.php\" METHOD=GET>\n");
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
		$iri = &$nsfr->GetIrai();
		$kri = &$nsfr->GetKKentai();
		$ken = &$nsfr->GetKentai();
		$can = &$nsfr->GetCansel();
		$hbn = &$nsfr->GetHiBunchu();
		$ekn = &$nsfr->GetErKentai();
		$fsk = &$nsfr->GetFusoku();
		$jzn = &$nsfr->GetJizen();
		$bun = &$nsfr->GetBunchu();
		$bkn = &$nsfr->GetBunKentai();
		$bka = &$nsfr->GetBunKeka();
		$pkp = &$nsfr->GetBunPaki();

		printf("<center>患者情報(%d)件</center>\n",$nsfr->GetZokuseiCount());
		printf("<table align=left frame=box border>\n");

		printf("<tr>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
		printf("<th nowrap>桁</th>\n");
		printf("<th nowrap>受付</th>\n");
		printf("<th nowrap>世代</th>\n");
		printf("<th nowrap>患者ID</th>\n");
		printf("<th nowrap>患者名</th>\n");
		printf("<th nowrap>患者名ID</th>\n");
		printf("<th nowrap>性別</th>\n");
		printf("<th nowrap>生年月日</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>年齢</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>施設CD</th>\n");
		printf("<th nowrap>SUBCD</th>\n");
		printf("<th nowrap>施設名</th>\n");
		printf("<th nowrap>営業所CD</th>\n");
		printf("<th nowrap>新営CD</th>\n");
		printf("<th nowrap>理由</th>\n");
		printf("<th nowrap>検体本数</th>\n");
		printf("<th nowrap>CMT1</th>\n");
		printf("<th nowrap>CMT2</th>\n");
		printf("<th nowrap>CMT3</th>\n");
		printf("<th nowrap>CMTF1</th>\n");
		printf("<th nowrap>CMTF2</th>\n");
		printf("<th nowrap>治</th>\n");
		printf("<th nowrap>集</th>\n");
		printf("<th nowrap>特緊</th>\n");
		printf("<th nowrap>POOL</th>\n");
		printf("<th nowrap>特注</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>更新時刻</th>\n");
		printf("</tr>\n");

		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",ymd_edit($kan[0]));
		printf("<td nowrap>%s</td>\n",ino_edit($kan[1]));
		printf("<td nowrap>%s</td>\n",$kan[2]);
		printf("<td nowrap>%s</td>\n",$kan[3]);
		printf("<td nowrap>%d</td>\n",$kan[4]);
		printf("<td nowrap>%s</td>\n",$kan[5]);
		printf("<td nowrap>%s</td>\n",$kan[6]);
		printf("<td nowrap>%s</td>\n",$kan[7]);
		printf("<td nowrap>%s</td>\n",$kan[8]);
		printf("<td nowrap>%s</td>\n",$kan[9]);
		printf("<td nowrap>%s</td>\n",$kan[10]);
		printf("<td nowrap>%s</td>\n",$kan[11]);
		printf("<td nowrap>%s</td>\n",$kan[12]);
		printf("<td nowrap>%s</td>\n",$kan[13]);
		printf("<td nowrap>%s</td>\n",$kan[14]);
		printf("<td nowrap>%s</td>\n",$kan[15]);
		printf("<td nowrap>%s-%s</td>\n",$kan[16],$kan[17]);
		printf("<td nowrap>%s</td>\n",$kan[18]);
		printf("<td nowrap>%s</td>\n",$kan[19]);
		printf("<td nowrap>%s</td>\n",$kan[20]);
		printf("<td nowrap>%s</td>\n",$kan[21]);
		printf("<td nowrap>%s</td>\n",$kan[22]);
		printf("<td nowrap>%s</td>\n",$kan[23]);
		printf("<td nowrap>%s</td>\n",$kan[24]);
		printf("<td nowrap>%s</td>\n",$kan[25]);
		printf("<td nowrap>%s</td>\n",$kan[26]);
		printf("<td nowrap>%s</td>\n",$kan[27]);
		printf("<td nowrap>%s</td>\n",$kan[28]);
		printf("<td nowrap>%s</td>\n",$kan[29]);
		printf("<td nowrap>%s</td>\n",$kan[30]);
		printf("<td nowrap>%s</td>\n",substr($kan[31],0,19));
		printf("<td nowrap>%s</td>\n",substr($kan[32],0,19));
		printf("</tr>\n");
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("<center>依頼情報 (%d)件</center>\n",$nsfr->GetIraiCount());

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>検体No.</th>\n");
		printf("<th nowrap>項目CD</th>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>分区分</th>\n");
		printf("<th nowrap>WS単</th>\n");
		printf("<th nowrap>緊G</th>\n");
		printf("<th nowrap>優先LV</th>\n");
		printf("<th nowrap>理由</th>\n");
		printf("<th nowrap>材料</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetIraiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($iri[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($iri[$i][1]));
			printf("<td nowrap><A href=../master/kmkmst.php?KMKCD=%s>%s</A></td>\n",$iri[$i][2],$iri[$i][2]);
			printf("<td nowrap>%s</td>\n",ymd_edit($iri[$i][3]));
			printf("<td nowrap>%s</td>\n",ino_edit($iri[$i][4]));
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",$iri[$i][5],$iri[$i][5]);
			printf("<td nowrap>%s</td>\n",$iri[$i][6]);
			printf("<td nowrap>%s</td>\n",$iri[$i][7]);
			printf("<td nowrap>%s</td>\n",$iri[$i][8]);
			printf("<td nowrap>%s</td>\n",$iri[$i][9]);
			printf("<td nowrap>%s</td>\n",$iri[$i][10]);
			printf("<td nowrap>%s</td>\n",$iri[$i][11]);
			printf("<td nowrap>%s</td>\n",$iri[$i][12]);
			printf("<td nowrap>%s</td>\n",substr($iri[$i][13],0,19));
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("<center>仮検体情報 (%d)件</center>\n",$nsfr->GetKKentaiCount());

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>検体No.</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
		printf("<th nowrap>検体KEY</th>\n");
		printf("<th nowrap>桁</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>受付</th>\n");
		printf("<th nowrap>仕分</th>\n");
		printf("<th nowrap>検査</th>\n");
		printf("<th nowrap>状態</th>\n");
		printf("<th nowrap>分類</th>\n");
		printf("<th nowrap>緊急</th>\n");
		printf("<th nowrap>仕先</th>\n");
		printf("<th nowrap>分注</th>\n");
		printf("<th nowrap>通常量</th>\n");
		printf("<th nowrap>少量量</th>\n");
		printf("<th nowrap>小児量</th>\n");
		printf("<th nowrap>非定型負荷</th>\n");
		printf("<th nowrap>蓄尿時間</th>\n");
		printf("<th nowrap>単位</th>\n");
		printf("<th nowrap>蓄尿量</th>\n");
		printf("<th nowrap>単位</th>\n");
		printf("<th nowrap>採取年月日</th>\n");
		printf("<th nowrap>理由</th>\n");
		printf("<th nowrap>材料</th>\n");
		printf("<th nowrap>FCMT</th>\n");
		printf("<th nowrap>凍共用</th>\n");
		printf("<th nowrap>非分F</th>\n");
		printf("<th nowrap>複数F</th>\n");
		printf("<th nowrap>完了予定時刻</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetKKentaiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($kri[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($kri[$i][1]));
			printf("<td nowrap>%d</td>\n",$kri[$i][2]);
			printf("<td nowrap>%s</td>\n",ymd_edit($kri[$i][3]));
			printf("<td nowrap>%s</td>\n",ino_edit($kri[$i][4]));
			printf("<td nowrap>%s</td>\n",$kri[$i][5]);
			printf("<td nowrap>%s</td>\n",$kri[$i][6]);
			printf("<td nowrap>%s</td>\n",$kri[$i][7]);
			printf("<td nowrap>%d</td>\n",$kri[$i][8]);
			printf("<td nowrap>%s</td>\n",$kri[$i][9]);
			printf("<td nowrap>%s</td>\n",$kri[$i][10]);
			printf("<td nowrap>%s</td>\n",$kri[$i][11]);
			printf("<td nowrap>%s</td>\n",$kri[$i][12]);
			printf("<td nowrap>%s</td>\n",$kri[$i][13]);
			printf("<td nowrap>%s</td>\n",$kri[$i][14]);
			printf("<td nowrap>%s</td>\n",$kri[$i][15]);
			printf("<td nowrap>%s</td>\n",$kri[$i][16]);
			printf("<td nowrap>%d</td>\n",$kri[$i][17]);
			printf("<td nowrap>%d</td>\n",$kri[$i][18]);
			printf("<td nowrap>%d</td>\n",$kri[$i][19]);
			printf("<td nowrap>%s</td>\n",$kri[$i][20]);
			printf("<td nowrap>%s</td>\n",$kri[$i][21]);
			printf("<td nowrap>%s</td>\n",$kri[$i][22]);
			printf("<td nowrap>%s</td>\n",$kri[$i][23]);
			printf("<td nowrap>%s</td>\n",$kri[$i][24]);
			printf("<td nowrap>%s</td>\n",$kri[$i][25]);
			printf("<td nowrap>%s</td>\n",$kri[$i][26]);
			printf("<td nowrap>%s</td>\n",$kri[$i][27]);
			printf("<td nowrap>%s</td>\n",$kri[$i][28]);
			printf("<td nowrap>%s</td>\n",$kri[$i][29]);
			printf("<td nowrap>%s</td>\n",$kri[$i][30]);
			printf("<td nowrap>%s</td>\n",$kri[$i][31]);
			printf("<td nowrap>%s</td>\n",substr($kri[$i][32],0,19));
			printf("<td nowrap>%s</td>\n",substr($kri[$i][33],0,19));
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("<center>検体情報 (%d)件</center>\n",$nsfr->GetKentaiCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
		printf("<th nowrap>検体No.</th>\n");
		printf("<th nowrap>検体KEY</th>\n");
		printf("<th nowrap>桁</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>受付</th>\n");
		printf("<th nowrap>仕分</th>\n");
		printf("<th nowrap>検査</th>\n");
		printf("<th nowrap>状態</th>\n");
		printf("<th nowrap>属状</th>\n");
		printf("<th nowrap>分類</th>\n");
		printf("<th nowrap>容器</th>\n");
		printf("<th nowrap>緊急</th>\n");
		printf("<th nowrap>装置No.</th>\n");
		printf("<th nowrap>トレーID:POS</th>\n");
		printf("<th nowrap>ラックID:POS</th>\n");
		printf("<th nowrap>着確SEQ</th>\n");
		printf("<th nowrap>仕先</th>\n");
		printf("<th nowrap>分注</th>\n");
		printf("<th nowrap>処理</th>\n");
		printf("<th nowrap>測定</th>\n");
		printf("<th nowrap>検量</th>\n");
		printf("<th nowrap>通常量</th>\n");
		printf("<th nowrap>少量量</th>\n");
		printf("<th nowrap>小児量</th>\n");
		printf("<th nowrap>測定量</th>\n");
		printf("<th nowrap>参考量</th>\n");
		printf("<th nowrap>単位</th>\n");
		printf("<th nowrap>非定型負荷</th>\n");
		printf("<th nowrap>蓄尿時間</th>\n");
		printf("<th nowrap>単位</th>\n");
		printf("<th nowrap>蓄尿量</th>\n");
		printf("<th nowrap>単位</th>\n");
		printf("<th nowrap>採取年月日</th>\n");
		printf("<th nowrap>理由</th>\n");
		printf("<th nowrap>材料</th>\n");
		printf("<th nowrap>FCMT</th>\n");
		printf("<th nowrap>BCDF</th>\n");
		printf("<th nowrap>凍共用</th>\n");
		printf("<th nowrap>送可F</th>\n");
		printf("<th nowrap>複数F</th>\n");
		printf("<th nowrap>用手F</th>\n");
		printf("<th nowrap>完了予定時刻</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>更新時刻</th>\n");
		printf("<th nowrap>依頼展開時刻</th>\n");
		printf("<th nowrap>認識時刻</th>\n");
		printf("<th nowrap>患者名チェック時刻</th>\n");
		printf("<th nowrap>患者名チェック者</th>\n");
		printf("<th nowrap>送信ID</th>\n");
		printf("<th nowrap>更新ID</th>\n");
		printf("<th nowrap>認識ID</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetKentaiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($ken[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($ken[$i][1]));
			printf("<td nowrap>%d</td>\n",$ken[$i][2]);
			printf("<td nowrap>%s</td>\n",ymd_edit($ken[$i][3]));
			printf("<td nowrap>%s</td>\n",ino_edit($ken[$i][4]));
			printf("<td nowrap>%s</td>\n",$ken[$i][5]);
			printf("<td nowrap>%s</td>\n",$ken[$i][6]);
			printf("<td nowrap>%s</td>\n",$ken[$i][7]);
			printf("<td nowrap>%s</td>\n",$ken[$i][8]);
			printf("<td nowrap>%d</td>\n",$ken[$i][9]);
			printf("<td nowrap>%s</td>\n",$ken[$i][10]);
			printf("<td nowrap>%s</td>\n",$ken[$i][11]);
			printf("<td nowrap>%s</td>\n",$ken[$i][12]);
			printf("<td nowrap>%s</td>\n",$ken[$i][13]);
			printf("<td nowrap>%s</td>\n",$ken[$i][14]);
			printf("<td nowrap>%s</td>\n",$ken[$i][15]);
			printf("<td nowrap>%s</td>\n",$ken[$i][16]);
			printf("<td nowrap>%s</td>\n",$ken[$i][17]);
			printf("<td nowrap>%s</td>\n",$ken[$i][18]);
			printf("<td nowrap>%s-%02d</td>\n",$ken[$i][19],$ken[$i][20]);
			printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%02d</td>\n",$ken[$i][0],$ken[$i][21],$ken[$i][21],$ken[$i][22]);
			printf("<td nowrap>%d</td>\n",$ken[$i][23]);
			printf("<td nowrap>%s</td>\n",$ken[$i][24]);
			printf("<td nowrap>%s</td>\n",$ken[$i][25]);
			printf("<td nowrap>%s</td>\n",$ken[$i][26]);
			printf("<td nowrap>%s</td>\n",$ken[$i][27]);
			printf("<td nowrap>%s</td>\n",$ken[$i][28]);
			printf("<td nowrap>%d</td>\n",$ken[$i][29]);
			printf("<td nowrap>%d</td>\n",$ken[$i][30]);
			printf("<td nowrap>%d</td>\n",$ken[$i][31]);
			printf("<td nowrap>%d</td>\n",$ken[$i][32]);
			printf("<td nowrap>%d</td>\n",$ken[$i][33]);
			printf("<td nowrap>%s</td>\n",$ken[$i][34]);
			printf("<td nowrap>%s</td>\n",$ken[$i][35]);
			printf("<td nowrap>%s</td>\n",$ken[$i][36]);
			printf("<td nowrap>%s</td>\n",$ken[$i][37]);
			printf("<td nowrap>%s</td>\n",$ken[$i][38]);
			printf("<td nowrap>%s</td>\n",$ken[$i][39]);
			printf("<td nowrap>%s</td>\n",$ken[$i][40]);
			printf("<td nowrap>%s</td>\n",$ken[$i][41]);
			printf("<td nowrap>%s</td>\n",$ken[$i][42]);
			printf("<td nowrap>%s</td>\n",$ken[$i][43]);
			printf("<td nowrap>%s</td>\n",$ken[$i][44]);
			printf("<td nowrap>%s</td>\n",$ken[$i][45]);
			printf("<td nowrap>%s</td>\n",$ken[$i][46]);
			printf("<td nowrap>%s</td>\n",$ken[$i][47]);
			printf("<td nowrap>%s</td>\n",$ken[$i][48]);
			printf("<td nowrap>%s</td>\n",substr($ken[$i][49],0,19));
			printf("<td nowrap>%s</td>\n",substr($ken[$i][50],0,19));
			printf("<td nowrap>%s</td>\n",substr($ken[$i][51],0,19));
			printf("<td nowrap>%s</td>\n",substr($ken[$i][52],0,19));
			printf("<td nowrap>%s</td>\n",substr($ken[$i][53],0,19));
			printf("<td nowrap>%s</td>\n",substr($ken[$i][54],0,19));
			printf("<td nowrap>%s</td>\n",$ken[$i][55]);
			printf("<td nowrap>%d</td>\n",$ken[$i][56]);
			printf("<td nowrap>%s</td>\n",$ken[$i][57]);
			printf("<td nowrap>%s</td>\n",$ken[$i][58]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		if ($nsfr->GetCanselCount() > 0)
			{
			printf("<BR>\n");
			printf("<center>キャンセル検体情報 (%d)件</center>\n",$nsfr->GetCanselCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>バーコード</th>\n");
			printf("<th nowrap>区分</th>\n");
			printf("<th nowrap>受付日</th>\n");
			printf("<th nowrap>依頼No.</th>\n");
			printf("<th nowrap>検体No.</th>\n");
			printf("<th nowrap>検体KEY</th>\n");
			printf("<th nowrap>桁</th>\n");
			printf("<th nowrap>CH</th>\n");
			printf("<th nowrap>SEQ</th>\n");
			printf("<th nowrap>受付</th>\n");
			printf("<th nowrap>仕分</th>\n");
			printf("<th nowrap>検査</th>\n");
			printf("<th nowrap>状態</th>\n");
			printf("<th nowrap>属状</th>\n");
			printf("<th nowrap>分類</th>\n");
			printf("<th nowrap>容器</th>\n");
			printf("<th nowrap>緊急</th>\n");
			printf("<th nowrap>装置No.</th>\n");
			printf("<th nowrap>トレーID:POS</th>\n");
			printf("<th nowrap>ラックID:POS</th>\n");
			printf("<th nowrap>着確SEQ</th>\n");
			printf("<th nowrap>仕先</th>\n");
			printf("<th nowrap>分注</th>\n");
			printf("<th nowrap>処理</th>\n");
			printf("<th nowrap>測定</th>\n");
			printf("<th nowrap>検量</th>\n");
			printf("<th nowrap>通常量</th>\n");
			printf("<th nowrap>少量量</th>\n");
			printf("<th nowrap>小児量</th>\n");
			printf("<th nowrap>測定量</th>\n");
			printf("<th nowrap>参考量</th>\n");
			printf("<th nowrap>単位</th>\n");
			printf("<th nowrap>非定型負荷</th>\n");
			printf("<th nowrap>蓄尿時間</th>\n");
			printf("<th nowrap>単位</th>\n");
			printf("<th nowrap>蓄尿量</th>\n");
			printf("<th nowrap>単位</th>\n");
			printf("<th nowrap>採取年月日</th>\n");
			printf("<th nowrap>理由</th>\n");
			printf("<th nowrap>材料</th>\n");
			printf("<th nowrap>FCMT</th>\n");
			printf("<th nowrap>BCDF</th>\n");
			printf("<th nowrap>凍共用</th>\n");
			printf("<th nowrap>送可F</th>\n");
			printf("<th nowrap>複数F</th>\n");
			printf("<th nowrap>用手F</th>\n");
			printf("<th nowrap>完了予定時刻</th>\n");
			printf("<th nowrap>作成時刻</th>\n");
			printf("<th nowrap>更新時刻</th>\n");
			printf("<th nowrap>依頼展開時刻</th>\n");
			printf("<th nowrap>認識時刻</th>\n");
			printf("<th nowrap>患者名チェック時刻</th>\n");
			printf("<th nowrap>患者名チェック者</th>\n");
			printf("<th nowrap>送信ID</th>\n");
			printf("<th nowrap>更新ID</th>\n");
			printf("<th nowrap>認識ID</th>\n");
			printf("</tr>\n");

			for ($i=0;$i<$nsfr->GetCanselCount();$i++)
				{
				printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",ymd_edit($can[$i][0]));
				printf("<td nowrap>%s</td>\n",barcode_edit($can[$i][1]));
				printf("<td nowrap>%d</td>\n",$can[$i][2]);
				printf("<td nowrap>%s</td>\n",ymd_edit($can[$i][3]));
				printf("<td nowrap>%s</td>\n",ino_edit($can[$i][4]));
				printf("<td nowrap>%s</td>\n",$can[$i][5]);
				printf("<td nowrap>%s</td>\n",$can[$i][6]);
				printf("<td nowrap>%s</td>\n",$can[$i][7]);
				printf("<td nowrap>%s</td>\n",$can[$i][8]);
				printf("<td nowrap>%d</td>\n",$can[$i][9]);
				printf("<td nowrap>%s</td>\n",$can[$i][10]);
				printf("<td nowrap>%s</td>\n",$can[$i][11]);
				printf("<td nowrap>%s</td>\n",$can[$i][12]);
				printf("<td nowrap>%s</td>\n",$can[$i][13]);
				printf("<td nowrap>%s</td>\n",$can[$i][14]);
				printf("<td nowrap>%s</td>\n",$can[$i][15]);
				printf("<td nowrap>%s</td>\n",$can[$i][16]);
				printf("<td nowrap>%s</td>\n",$can[$i][17]);
				printf("<td nowrap>%s</td>\n",$can[$i][18]);
				printf("<td nowrap>%s-%02d</td>\n",$can[$i][19],$can[$i][20]);
				printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%02d</td>\n",$can[$i][0],$can[$i][21],$can[$i][21],$can[$i][22]);
				printf("<td nowrap>%d</td>\n",$can[$i][23]);
				printf("<td nowrap>%s</td>\n",$can[$i][24]);
				printf("<td nowrap>%s</td>\n",$can[$i][25]);
				printf("<td nowrap>%s</td>\n",$can[$i][26]);
				printf("<td nowrap>%s</td>\n",$can[$i][27]);
				printf("<td nowrap>%s</td>\n",$can[$i][28]);
				printf("<td nowrap>%d</td>\n",$can[$i][29]);
				printf("<td nowrap>%d</td>\n",$can[$i][30]);
				printf("<td nowrap>%d</td>\n",$can[$i][31]);
				printf("<td nowrap>%d</td>\n",$can[$i][32]);
				printf("<td nowrap>%d</td>\n",$can[$i][33]);
				printf("<td nowrap>%s</td>\n",$can[$i][34]);
				printf("<td nowrap>%s</td>\n",$can[$i][35]);
				printf("<td nowrap>%s</td>\n",$can[$i][36]);
				printf("<td nowrap>%s</td>\n",$can[$i][37]);
				printf("<td nowrap>%s</td>\n",$can[$i][38]);
				printf("<td nowrap>%s</td>\n",$can[$i][39]);
				printf("<td nowrap>%s</td>\n",$can[$i][40]);
				printf("<td nowrap>%s</td>\n",$can[$i][41]);
				printf("<td nowrap>%s</td>\n",$can[$i][42]);
				printf("<td nowrap>%s</td>\n",$can[$i][43]);
				printf("<td nowrap>%s</td>\n",$can[$i][44]);
				printf("<td nowrap>%s</td>\n",$can[$i][45]);
				printf("<td nowrap>%s</td>\n",$can[$i][46]);
				printf("<td nowrap>%s</td>\n",$can[$i][47]);
				printf("<td nowrap>%s</td>\n",$can[$i][48]);
				printf("<td nowrap>%s</td>\n",substr($can[$i][49],0,19));
				printf("<td nowrap>%s</td>\n",substr($can[$i][50],0,19));
				printf("<td nowrap>%s</td>\n",substr($can[$i][51],0,19));
				printf("<td nowrap>%s</td>\n",substr($can[$i][52],0,19));
				printf("<td nowrap>%s</td>\n",substr($can[$i][53],0,19));
				printf("<td nowrap>%s</td>\n",substr($can[$i][54],0,19));
				printf("<td nowrap>%s</td>\n",$can[$i][55]);
				printf("<td nowrap>%d</td>\n",$can[$i][56]);
				printf("<td nowrap>%s</td>\n",$can[$i][57]);
				printf("<td nowrap>%s</td>\n",$can[$i][58]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("<BR clear=all>\n");
			}

		printf("<BR>\n");
		printf("<center>非分注検体情報 (%d)件</center>\n",$nsfr->GetHiBunchuCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>作業者ID</th>\n");
		printf("<th nowrap>送信ID</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetHiBunchuCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($hbn[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($hbn[$i][1]));
			printf("<td nowrap>%d</td>\n",$hbn[$i][2]);
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",$hbn[$i][3],$hbn[$i][3]);
			printf("<td nowrap>%s</td>\n",$hbn[$i][4]);
			printf("<td nowrap>%s</td>\n",substr($hbn[$i][5],0,19));
			printf("<td nowrap>%s</td>\n",$hbn[$i][6]);
			printf("<td nowrap>%s</td>\n",$hbn[$i][7]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		if ($nsfr->GetErKentaiCount() > 0)
			{
			printf("<BR>\n");
			printf("<center>エラー検体情報 (%d)件</center>\n",$nsfr->GetErKentaiCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>バーコード</th>\n");
			printf("<th nowrap>区分</th>\n");
			printf("<th nowrap>ERID</th>\n");
			printf("<th nowrap>受付日</th>\n");
			printf("<th nowrap>依頼No.</th>\n");
			printf("<th nowrap>CMTID</th>\n");
			printf("<th nowrap>フリーコメント</th>\n");
			printf("<th nowrap>作成時刻</th>\n");
			printf("<th nowrap>作業者ID</th>\n");
			printf("<th nowrap>送信ID</th>\n");
			printf("<th nowrap>作成ID</th>\n");
			printf("</tr>\n");

			for ($i=0;$i<$nsfr->GetErKentaiCount();$i++)
				{
				printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",ymd_edit($ekn[$i][0]));
				printf("<td nowrap>%s</td>\n",barcode_edit($ekn[$i][1]));
				printf("<td nowrap>%d</td>\n",$ekn[$i][2]);
				printf("<td nowrap>%s</td>\n",$ekn[$i][3]);
				printf("<td nowrap>%s</td>\n",ymd_edit($ekn[$i][4]));
				printf("<td nowrap>%s</td>\n",ino_edit($ekn[$i][5]));
				printf("<td nowrap>%s</td>\n",$ekn[$i][6]);
				printf("<td nowrap>%s</td>\n",$ekn[$i][7]);
				printf("<td nowrap>%s</td>\n",substr($ekn[$i][8],0,19));
				printf("<td nowrap>%s</td>\n",$ekn[$i][9]);
				printf("<td nowrap>%s</td>\n",$ekn[$i][10]);
				printf("<td nowrap>%s</td>\n",$ekn[$i][11]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("<BR clear=all>\n");
			}

		if ($nsfr->GetFusokuCount() > 0)
			{
			printf("<BR>\n");
			printf("<center>不足検体情報 (%d)件</center>\n",$nsfr->GetFusokuCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>バーコード</th>\n");
			printf("<th nowrap>区分</th>\n");
			printf("<th nowrap>作成時刻</th>\n");
			printf("<th nowrap>作業者ID</th>\n");
			printf("<th nowrap>送信ID</th>\n");
			printf("</tr>\n");

			for ($i=0;$i<$nsfr->GetFusokuCount();$i++)
				{
				printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",ymd_edit($fsk[$i][0]));
				printf("<td nowrap>%s</td>\n",barcode_edit($fsk[$i][1]));
				printf("<td nowrap>%d</td>\n",$fsk[$i][2]);
				printf("<td nowrap>%s</td>\n",substr($fsk[$i][3],0,19));
				printf("<td nowrap>%s</td>\n",$fsk[$i][4]);
				printf("<td nowrap>%s</td>\n",$fsk[$i][5]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("<BR clear=all>\n");
			}

		if ($nsfr->GetJizenCount() > 0)
			{
			printf("<BR>\n");
			printf("<center>遅着登録情報 (%d)件</center>\n",$nsfr->GetJizenCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>検体No.</th>\n");
			printf("<th nowrap>SEQ</th>\n");
			printf("<th nowrap>コメント</th>\n");
			printf("<th nowrap>作成時刻</th>\n");
			printf("<th nowrap>解除時刻</th>\n");
			printf("<th nowrap>作業者ID</th>\n");
			printf("<th nowrap>解除者ID</th>\n");
			printf("</tr>\n");

			for ($i=0;$i<$nsfr->GetJizenCount();$i++)
				{
				printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",ymd_edit($jzn[$i][0]));
				printf("<td nowrap>%s</td>\n",barcode_edit($jzn[$i][1]));
				printf("<td nowrap>%d</td>\n",$jzn[$i][2]);
				printf("<td nowrap>%s</td>\n",$jzn[$i][3]);
				printf("<td nowrap>%s</td>\n",substr($jzn[$i][4],0,19));
				printf("<td nowrap>%s</td>\n",substr($jzn[$i][5],0,19));
				printf("<td nowrap>%s</td>\n",$jzn[$i][6]);
				printf("<td nowrap>%s</td>\n",$jzn[$i][7]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("<BR clear=all>\n");
			}

		printf("<BR>\n");
		printf("<center>分注検体情報 (%d)件</center>\n",$nsfr->GetBunKentaiCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
		printf("<th nowrap>分注処理日</th>\n");
		printf("<th nowrap>トレーID:POS</th>\n");
		printf("<th nowrap>ラックID:POS</th>\n");
		printf("<th nowrap>コンテナ</th>\n");
		printf("<th nowrap>看板ＩＤ</th>\n");
		printf("<th nowrap>投入回数</th>\n");
		printf("<th nowrap>投入CELL</th>\n");
		printf("<th nowrap>分注STS</th>\n");
		printf("<th nowrap>代表項目</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>更新時刻</th>\n");
		printf("<th nowrap>作業者ID</th>\n");
		printf("<th nowrap>送信ID</th>\n");
		printf("<th nowrap>BUNPOS</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunKentaiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($bkn[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($bkn[$i][1]));
			printf("<td nowrap>%d</td>\n",$bkn[$i][2]);
			printf("<td nowrap>%s</td>\n",ymd_edit($bkn[$i][3]));
			printf("<td nowrap>%s</td>\n",ino_edit($bkn[$i][4]));
			printf("<td nowrap>%s</td>\n",ymd_edit($bkn[$i][5]));
			printf("<td nowrap>%s-%2d</td>\n",$bkn[$i][6],$bkn[$i][7]);
			printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%2d</td>\n",$bkn[$i][0],$bkn[$i][8],$bkn[$i][8],$bkn[$i][9]);
			printf("<td nowrap>%s</td>\n",$bkn[$i][10]);
			printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A></td>\n",$bkn[$i][0],$bkn[$i][11],$bkn[$i][11]);
			printf("<td nowrap>%d</td>\n",$bkn[$i][12]);
			printf("<td nowrap>%s</td>\n",$bkn[$i][13]);
			printf("<td nowrap>%s</td>\n",$bkn[$i][14]);
			printf("<td nowrap>%s</td>\n",$bkn[$i][15]);
			printf("<td nowrap>%s</td>\n",substr($bkn[$i][16],0,19));
			printf("<td nowrap>%s</td>\n",substr($bkn[$i][17],0,19));
			printf("<td nowrap>%s</td>\n",$bkn[$i][18]);
			printf("<td nowrap>%d</td>\n",$bkn[$i][19]);
			printf("<td nowrap>%d</td>\n",$bkn[$i][20]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("<center>分注情報 (%d)件</center>\n",$nsfr->GetBunchuCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>受付日</th>\n");
		printf("<th nowrap>依頼No.</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>分注処理日</th>\n");
		printf("<th nowrap>ラックID:POS</th>\n");
		printf("<th nowrap>ITEM</th>\n");
		printf("<th nowrap>ITEM群</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>分注</th>\n");
		printf("<th nowrap>WS単</th>\n");
		printf("<th nowrap>分注量</th>\n");
		printf("<th nowrap>通常量</th>\n");
		printf("<th nowrap>少量量</th>\n");
		printf("<th nowrap>小児量</th>\n");
		printf("<th nowrap>吸引条件</th>\n");
		printf("<th nowrap>代替</th>\n");
		printf("<th nowrap>CELL区分</th>\n");
		printf("<th nowrap>分注STS</th>\n");
		printf("<th nowrap>検査</th>\n");
		printf("<th nowrap>治</th>\n");
		printf("<th nowrap>特</th>\n");
		printf("<th nowrap>量</th>\n");
		printf("<th nowrap>Fib</th>\n");
		printf("<th nowrap>BUNPOS</th>\n");
		printf("<th nowrap>強制</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>更新時刻</th>\n");
		printf("<th nowrap>送信ID</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunchuCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($bun[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($bun[$i][1]));
			printf("<td nowrap>%d</td>\n",$bun[$i][2]);
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",$bun[$i][3],$bun[$i][3]);
			printf("<td nowrap>%s</td>\n",ymd_edit($bun[$i][4]));
			printf("<td nowrap>%s</td>\n",ino_edit($bun[$i][5]));
			printf("<td nowrap>%d</td>\n",$bun[$i][6]);
			printf("<td nowrap>%s</td>\n",ymd_edit($bun[$i][7]));
			printf("<td nowrap><A href=../merits/krackmap.php?SDATE=%s&RACK=%s>%s</A>-%2d</td>\n",$bun[$i][0],$bun[$i][8],$bun[$i][8],$bun[$i][9]);
			printf("<td nowrap>%s</td>\n",$bun[$i][10]);
			printf("<td nowrap>%s</td>\n",$bun[$i][11]);
			printf("<td nowrap>%s</td>\n",$bun[$i][12]);
			printf("<td nowrap>%s</td>\n",$bun[$i][13]);
			printf("<td nowrap>%s</td>\n",$bun[$i][14]);
			printf("<td nowrap>%d</td>\n",$bun[$i][15]);
			printf("<td nowrap>%d</td>\n",$bun[$i][16]);
			printf("<td nowrap>%d</td>\n",$bun[$i][17]);
			printf("<td nowrap>%d</td>\n",$bun[$i][18]);
			printf("<td nowrap>%d</td>\n",$bun[$i][19]);
			printf("<td nowrap>%s</td>\n",$bun[$i][20]);
			printf("<td nowrap>%s</td>\n",$bun[$i][21]);
			printf("<td nowrap>%s</td>\n",$bun[$i][22]);
			printf("<td nowrap>%s</td>\n",$bun[$i][23]);
			printf("<td nowrap>%s</td>\n",$bun[$i][24]);
			printf("<td nowrap>%s</td>\n",$bun[$i][25]);
			printf("<td nowrap>%s</td>\n",$bun[$i][26]);
			printf("<td nowrap>%s</td>\n",$bun[$i][27]);
			printf("<td nowrap>%s</td>\n",$bun[$i][28]);
			printf("<td nowrap>%s</td>\n",$bun[$i][29]);
			printf("<td nowrap>%s</td>\n",substr($bun[$i][30],0,19));
			printf("<td nowrap>%s</td>\n",substr($bun[$i][31],0,19));
			printf("<td nowrap>%d</td>\n",$bun[$i][32]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("<center>分注結果情報 (%d)件</center>\n",$nsfr->GetBunKekaCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>分注処理日</th>\n");
		printf("<th nowrap>装置No.</th>\n");
		printf("<th nowrap>MODNo.</th>\n");
		printf("<th nowrap>AトレーID:POS</th>\n");
		printf("<th nowrap>AラックID:POS</th>\n");
		printf("<th nowrap>AラックSEQ</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>結果</th>\n");
		printf("<th nowrap>CELL区分</th>\n");
		printf("<th nowrap>NGCD</th>\n");
		printf("<th nowrap>NG詳</th>\n");
		printf("<th nowrap>NGコメント</th>\n");
		printf("<th nowrap>分注量F</th>\n");
		printf("<th nowrap>引渡</th>\n");
		printf("<th nowrap>乳び</th>\n");
		printf("<th nowrap>溶血</th>\n");
		printf("<th nowrap>移載</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>更新時刻</th>\n");
		printf("<th nowrap>分注時刻</th>\n");
		printf("<th nowrap>用手作業ID</th>\n");
		printf("<th nowrap>送信ID</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunKekaCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($bka[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($bka[$i][1]));
			printf("<td nowrap>%d</td>\n",$bka[$i][2]);
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",$bka[$i][3],$bka[$i][3]);
			printf("<td nowrap>%d</td>\n",$bka[$i][4]);
			printf("<td nowrap>%s</td>\n",ymd_edit($bka[$i][5]));
			printf("<td nowrap>%s</td>\n",$bka[$i][6]);
			printf("<td nowrap>%s</td>\n",$bka[$i][7]);
			printf("<td nowrap>%s-%s</td>\n",$bka[$i][8],$bka[$i][9]);
			printf("<td nowrap>%s-%s</td>\n",$bka[$i][10],$bka[$i][12]);
			printf("<td nowrap>%s</td>\n",$bka[$i][11]);
			printf("<td nowrap>%s</td>\n",$bka[$i][13]);
			printf("<td nowrap>%s</td>\n",$bka[$i][14]);
			printf("<td nowrap>%s</td>\n",$bka[$i][15]);
			printf("<td nowrap>%s</td>\n",$bka[$i][16]);
			printf("<td nowrap>%s</td>\n",$bka[$i][17]);
			printf("<td nowrap>%s</td>\n",$bka[$i][18]);
			printf("<td nowrap>%s</td>\n",$bka[$i][19]);
			printf("<td nowrap>%s</td>\n",$bka[$i][20]);
			printf("<td nowrap>%s</td>\n",$bka[$i][21]);
			printf("<td nowrap>%s</td>\n",$bka[$i][22]);
			printf("<td nowrap>%s</td>\n",$bka[$i][23]);
			printf("<td nowrap>%s</td>\n",substr($bka[$i][24],0,19));
			printf("<td nowrap>%s</td>\n",substr($bka[$i][25],0,19));
			printf("<td nowrap>%s</td>\n",substr($bka[$i][26],0,19));
			printf("<td nowrap>%s</td>\n",$bka[$i][27]);
			printf("<td nowrap>%d</td>\n",$bka[$i][28]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("<BR clear=all>\n");

		printf("<BR>\n");
		printf("<center>パキパキ情報 (%d)件</center>\n",$nsfr->GetBunPakiCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>処理日</th>\n");
		printf("<th nowrap>ITEM</th>\n");
		printf("<th nowrap>仕先</th>\n");
		printf("<th nowrap>仕先SEQ</th>\n");
		printf("<th nowrap>検体No.</th>\n");
		printf("<th nowrap>バーコード</th>\n");
		printf("<th nowrap>区分</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>AラックPOS</th>\n");
		printf("<th nowrap>ITEM SEQ</th>\n");
		printf("<th nowrap>RACK SEQ</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>MARK</th>\n");
		printf("<th nowrap>出力</th>\n");
		printf("<th nowrap>作成時刻</th>\n");
		printf("<th nowrap>更新時刻</th>\n");
		printf("</tr>\n");

		for ($i=0;$i<$nsfr->GetBunPakiCount();$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($pkp[$i][0]));
			printf("<td nowrap>%s</td>\n",$pkp[$i][1]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][2]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][3]);
			printf("<td nowrap>%s</td>\n",barcode_edit($pkp[$i][4]));
			printf("<td nowrap>%s</td>\n",barcode_edit($pkp[$i][5]));
			printf("<td nowrap>%d</td>\n",$pkp[$i][6]);
			printf("<td nowrap><A href=../master/smpkm.php?SMPCD=%s>%s</A></td>\n",$pkp[$i][7],$pkp[$i][7]);
			printf("<td nowrap>%d</td>\n",$pkp[$i][8]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][9]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][10]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][11]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][12]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][13]);
			printf("<td nowrap>%s</td>\n",$pkp[$i][14]);
			printf("<td nowrap>%s</td>\n",substr($pkp[$i][15],0,19));
			printf("<td nowrap>%s</td>\n",substr($pkp[$i][16],0,19));
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
