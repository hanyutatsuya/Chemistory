
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
ótú
<INPUT TYPE=text NAME="UDATE" SIZE=10 MAXLENGTH=8>
ËNo.
<INPUT TYPE=text NAME="INO" SIZE=13 MAXLENGTH=11>
</center>
</P>
<P>
<center>
ú
<INPUT TYPE=text NAME="SDATE" SIZE=10 MAXLENGTH=8>
ÌNo.
<INPUT TYPE=text NAME="KENNO" SIZE=13 MAXLENGTH=11>
o[R[hNo.
<INPUT TYPE=text NAME="BARCD" SIZE=13 MAXLENGTH=11>
</center>
</P>
<P>
<center>
<BUTTON name="submit" value="submit" type="submit">õ</BUTTON>
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
		printf("<center><P>üÍG[Å·</P></center>\n");
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

		printf("<center><P>³Òîñ</P></center>\n");
		printf("<table align=left frame=box border>\n");

		printf("<tr>\n");
		printf("<th nowrap>ótú</th>\n");
		printf("<th nowrap>ËNo.</th>\n");
		printf("<th nowrap></th>\n");
		printf("<th nowrap>ót</th>\n");
		printf("<th nowrap>¢ã</th>\n");
		printf("<th nowrap>³ÒID</th>\n");
		printf("<th nowrap>³Ò¼</th>\n");
		printf("<th nowrap>³Ò¼ID</th>\n");
		printf("<th nowrap>«Ê</th>\n");
		printf("<th nowrap>¶Nú</th>\n");
		printf("<th nowrap>æª</th>\n");
		printf("<th nowrap>Nî</th>\n");
		printf("<th nowrap>æª</th>\n");
		printf("<th nowrap>{ÝCD</th>\n");
		printf("<th nowrap>SUBCD</th>\n");
		printf("<th nowrap>{Ý¼</th>\n");
		printf("<th nowrap>cÆCD</th>\n");
		printf("<th nowrap>VcCD</th>\n");
		printf("<th nowrap>R</th>\n");
		printf("<th nowrap>Ì{</th>\n");
		printf("<th nowrap>CMT1</th>\n");
		printf("<th nowrap>CMT2</th>\n");
		printf("<th nowrap>CMT3</th>\n");
		printf("<th nowrap>CMTF1</th>\n");
		printf("<th nowrap>CMTF2</th>\n");
		printf("<th nowrap>¡</th>\n");
		printf("<th nowrap>W</th>\n");
		printf("<th nowrap>ÁÙ</th>\n");
		printf("<th nowrap>POOL</th>\n");
		printf("<th nowrap>Á</th>\n");
		printf("<th nowrap>ì¬</th>\n");
		printf("<th nowrap>XV</th>\n");
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

		printf("<center><P>Ëîñ (%d)</P></center>\n",count($iri));

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>ú</th>\n");
		printf("<th nowrap>ÌNo.</th>\n");
		printf("<th nowrap>ÚCD</th>\n");
		printf("<th nowrap>ótú</th>\n");
		printf("<th nowrap>ËNo.</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>ªæª</th>\n");
		printf("<th nowrap>WSP</th>\n");
		printf("<th nowrap>ÙG</th>\n");
		printf("<th nowrap>DæLV</th>\n");
		printf("<th nowrap>R</th>\n");
		printf("<th nowrap>Þ¿</th>\n");
		printf("<th nowrap>ì¬</th>\n");
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

		printf("<center><P>¼Ìîñ (%d)</P></center>\n",count($kri));

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>ú</th>\n");
		printf("<th nowrap>ÌNo.</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>ótú</th>\n");
		printf("<th nowrap>ËNo.</th>\n");
		printf("<th nowrap>ÌKEY</th>\n");
		printf("<th nowrap></th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>æª</th>\n");
		printf("<th nowrap>ót</th>\n");
		printf("<th nowrap>dª</th>\n");
		printf("<th nowrap>¸</th>\n");
		printf("<th nowrap>óÔ</th>\n");
		printf("<th nowrap>ªÞ</th>\n");
		printf("<th nowrap>Ù}</th>\n");
		printf("<th nowrap>dæ</th>\n");
		printf("<th nowrap>ª</th>\n");
		printf("<th nowrap>ÊíÊ</th>\n");
		printf("<th nowrap>­ÊÊ</th>\n");
		printf("<th nowrap>¬Ê</th>\n");
		printf("<th nowrap>ñè^×</th>\n");
		printf("<th nowrap>~AÔ</th>\n");
		printf("<th nowrap>PÊ</th>\n");
		printf("<th nowrap>~AÊ</th>\n");
		printf("<th nowrap>PÊ</th>\n");
		printf("<th nowrap>ÌæNú</th>\n");
		printf("<th nowrap>R</th>\n");
		printf("<th nowrap>Þ¿</th>\n");
		printf("<th nowrap>FCMT</th>\n");
		printf("<th nowrap>¤p</th>\n");
		printf("<th nowrap>ñªF</th>\n");
		printf("<th nowrap>¡F</th>\n");
		printf("<th nowrap>®¹\è</th>\n");
		printf("<th nowrap>ì¬</th>\n");
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

		printf("<center><P>Ìîñ (%d)</P></center>\n",count($ken));
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>ú</th>\n");
		printf("<th nowrap>o[R[h</th>\n");
		printf("<th nowrap>æª</th>\n");
		printf("<th nowrap>ótú</th>\n");
		printf("<th nowrap>ËNo.</th>\n");
		printf("<th nowrap>ÌNo.</th>\n");
		printf("<th nowrap>ÌKEY</th>\n");
		printf("<th nowrap></th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>ót</th>\n");
		printf("<th nowrap>dª</th>\n");
		printf("<th nowrap>¸</th>\n");
		printf("<th nowrap>óÔ</th>\n");
		printf("<th nowrap>®ó</th>\n");
		printf("<th nowrap>ªÞ</th>\n");
		printf("<th nowrap>eí</th>\n");
		printf("<th nowrap>Ù}</th>\n");
		printf("<th nowrap>uNo.</th>\n");
		printf("<th nowrap>g[ID:POS</th>\n");
		printf("<th nowrap>bNID:POS</th>\n");
		printf("<th nowrap>mSEQ</th>\n");
		printf("<th nowrap>dæ</th>\n");
		printf("<th nowrap>ª</th>\n");
		printf("<th nowrap></th>\n");
		printf("<th nowrap>ªè</th>\n");
		printf("<th nowrap>Ê</th>\n");
		printf("<th nowrap>ÊíÊ</th>\n");
		printf("<th nowrap>­ÊÊ</th>\n");
		printf("<th nowrap>¬Ê</th>\n");
		printf("<th nowrap>ªèÊ</th>\n");
		printf("<th nowrap>QlÊ</th>\n");
		printf("<th nowrap>PÊ</th>\n");
		printf("<th nowrap>ñè^×</th>\n");
		printf("<th nowrap>~AÔ</th>\n");
		printf("<th nowrap>PÊ</th>\n");
		printf("<th nowrap>~AÊ</th>\n");
		printf("<th nowrap>PÊ</th>\n");
		printf("<th nowrap>ÌæNú</th>\n");
		printf("<th nowrap>R</th>\n");
		printf("<th nowrap>Þ¿</th>\n");
		printf("<th nowrap>FCMT</th>\n");
		printf("<th nowrap>BCDF</th>\n");
		printf("<th nowrap>¤p</th>\n");
		printf("<th nowrap>ÂF</th>\n");
		printf("<th nowrap>¡F</th>\n");
		printf("<th nowrap>pèF</th>\n");
		printf("<th nowrap>®¹\è</th>\n");
		printf("<th nowrap>ì¬</th>\n");
		printf("<th nowrap>XV</th>\n");
		printf("<th nowrap>ËWJ</th>\n");
		printf("<th nowrap>F¯</th>\n");
		printf("<th nowrap>³Ò¼`FbN</th>\n");
		printf("<th nowrap>³Ò¼`FbNÒ</th>\n");
		printf("<th nowrap>MID</th>\n");
		printf("<th nowrap>XVID</th>\n");
		printf("<th nowrap>F¯ID</th>\n");
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

