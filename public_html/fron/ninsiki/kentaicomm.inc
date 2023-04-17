
<?php
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_class.inc");

$udate = trim($_POST['UDATE']);
$ino   = trim($_POST['INO']);
$sdate = trim($_POST['SDATE']);
$kenno = trim($_POST['KENNO']);
$barcd = trim($_POST['BARCD']);
?>

<FORM ACTION="../comm/nsfrshokai.php" METHOD="POST">
<P>
<center>
受付日
<INPUT TYPE=text NAME="UDATE" SIZE=10 MAXLENGTH=8>
依頼書No.
<INPUT TYPE=text NAME="INO" SIZE=13 MAXLENGTH=11>
</center>
</P>
<P>
<center>
処理日
<INPUT TYPE=text NAME="SDATE" SIZE=10 MAXLENGTH=8>
検体No.
<INPUT TYPE=text NAME="KENNO" SIZE=13 MAXLENGTH=11>
バーコードNo.
<INPUT TYPE=text NAME="BARCD" SIZE=13 MAXLENGTH=11>
</center>
</P>
<P>
<center>
<BUTTON name="submit" value="submit" type="submit">検索</BUTTON>
</FORM>
</center>
</P>
<HR>

<?php

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

		$kan = $nsfr->GetZokusei();
		$iri = $nsfr->GetIrai();
		$kri = $nsfr->GetKKentai();
		$ken = $nsfr->GetKentai();

		printf("<center><P>患者情報</P></center>\n");
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

		printf("<center><P>依頼情報 (%d)件</P></center>\n",count($iri));

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

		for ($i=0;$i<count($iri);$i++)
			{
			printf("<tr>\n");
			printf("<td nowrap>%s</td>\n",ymd_edit($iri[$i][0]));
			printf("<td nowrap>%s</td>\n",barcode_edit($iri[$i][1]));
			printf("<td nowrap>%s</td>\n",$iri[$i][2]);
			printf("<td nowrap>%s</td>\n",ymd_edit($iri[$i][3]));
			printf("<td nowrap>%s</td>\n",ino_edit($iri[$i][4]));
			printf("<td nowrap>%s</td>\n",$iri[$i][5]);
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

		printf("<center><P>仮検体情報 (%d)件</P></center>\n",count($kri));

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

		for ($i=0;$i<count($kri);$i++)
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

		printf("<center><P>検体情報 (%d)件</P></center>\n",count($ken));
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

		for ($i=0;$i<count($ken);$i++)
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
			printf("<td nowrap>%s-%02d</td>\n",$ken[$i][21],$ken[$i][22]);
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

