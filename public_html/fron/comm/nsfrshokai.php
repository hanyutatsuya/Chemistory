<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("nsfr_html.inc");
require_once("nsfr_comm.inc");
require_once("nsfr_db.inc");
require_once("nsfr_class.inc");

$title = "�F���E�t�����e�B�A�c�a�Ɖ�";
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
printf("��t��\n");
printf("<INPUT TYPE=text NAME=UDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$udate);
printf("�˗���No.\n");
printf("<INPUT TYPE=text NAME=INO SIZE=13 MAXLENGTH=11 value=\"%s\">\n",$ino);
printf("</center>\n");
printf("</P>\n");
printf("<P>\n");
printf("<center>\n");
printf("������\n");
printf("<INPUT TYPE=text NAME=SDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$sdate);
printf("����No.\n");
printf("<INPUT TYPE=text NAME=KENNO SIZE=13 MAXLENGTH=11 value=\"%s\">\n",$kenno);
printf("�o�[�R�[�hNo.\n");
printf("<INPUT TYPE=text NAME=BARCD SIZE=13 MAXLENGTH=11 value=\"%s\">\n",$barcd);
printf("</center>\n");
printf("</P>\n");
printf("<P>\n");
printf("<center>\n");
printf("<BUTTON TYPE=submit name=submit value=\"submit\">����</BUTTON>\n");
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
		printf("<center><P>���̓G���[�ł�</P></center>\n");
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

		printf("<center>���ҏ��(%d)��</center>\n",$nsfr->GetZokuseiCount());
		printf("<table align=left frame=box border>\n");

		printf("<tr>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>��t</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>����ID</th>\n");
		printf("<th nowrap>���Җ�</th>\n");
		printf("<th nowrap>���Җ�ID</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>���N����</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>�N��</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>�{��CD</th>\n");
		printf("<th nowrap>SUBCD</th>\n");
		printf("<th nowrap>�{�ݖ�</th>\n");
		printf("<th nowrap>�c�Ə�CD</th>\n");
		printf("<th nowrap>�V�cCD</th>\n");
		printf("<th nowrap>���R</th>\n");
		printf("<th nowrap>���̖{��</th>\n");
		printf("<th nowrap>CMT1</th>\n");
		printf("<th nowrap>CMT2</th>\n");
		printf("<th nowrap>CMT3</th>\n");
		printf("<th nowrap>CMTF1</th>\n");
		printf("<th nowrap>CMTF2</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>�W</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>POOL</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>�X�V����</th>\n");
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
		printf("<center>�˗���� (%d)��</center>\n",$nsfr->GetIraiCount());

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>����No.</th>\n");
		printf("<th nowrap>����CD</th>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>���敪</th>\n");
		printf("<th nowrap>WS�P</th>\n");
		printf("<th nowrap>��G</th>\n");
		printf("<th nowrap>�D��LV</th>\n");
		printf("<th nowrap>���R</th>\n");
		printf("<th nowrap>�ޗ�</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
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
		printf("<center>�����̏�� (%d)��</center>\n",$nsfr->GetKKentaiCount());

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>����No.</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
		printf("<th nowrap>����KEY</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>��t</th>\n");
		printf("<th nowrap>�d��</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>���</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�ً}</th>\n");
		printf("<th nowrap>�d��</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�ʏ��</th>\n");
		printf("<th nowrap>���ʗ�</th>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>���^����</th>\n");
		printf("<th nowrap>�~�A����</th>\n");
		printf("<th nowrap>�P��</th>\n");
		printf("<th nowrap>�~�A��</th>\n");
		printf("<th nowrap>�P��</th>\n");
		printf("<th nowrap>�̎�N����</th>\n");
		printf("<th nowrap>���R</th>\n");
		printf("<th nowrap>�ޗ�</th>\n");
		printf("<th nowrap>FCMT</th>\n");
		printf("<th nowrap>�����p</th>\n");
		printf("<th nowrap>��F</th>\n");
		printf("<th nowrap>����F</th>\n");
		printf("<th nowrap>�����\�莞��</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
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
		printf("<center>���̏�� (%d)��</center>\n",$nsfr->GetKentaiCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
		printf("<th nowrap>����No.</th>\n");
		printf("<th nowrap>����KEY</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>��t</th>\n");
		printf("<th nowrap>�d��</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>���</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�e��</th>\n");
		printf("<th nowrap>�ً}</th>\n");
		printf("<th nowrap>���uNo.</th>\n");
		printf("<th nowrap>�g���[ID:POS</th>\n");
		printf("<th nowrap>���b�NID:POS</th>\n");
		printf("<th nowrap>���mSEQ</th>\n");
		printf("<th nowrap>�d��</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�ʏ��</th>\n");
		printf("<th nowrap>���ʗ�</th>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�����</th>\n");
		printf("<th nowrap>�Q�l��</th>\n");
		printf("<th nowrap>�P��</th>\n");
		printf("<th nowrap>���^����</th>\n");
		printf("<th nowrap>�~�A����</th>\n");
		printf("<th nowrap>�P��</th>\n");
		printf("<th nowrap>�~�A��</th>\n");
		printf("<th nowrap>�P��</th>\n");
		printf("<th nowrap>�̎�N����</th>\n");
		printf("<th nowrap>���R</th>\n");
		printf("<th nowrap>�ޗ�</th>\n");
		printf("<th nowrap>FCMT</th>\n");
		printf("<th nowrap>BCDF</th>\n");
		printf("<th nowrap>�����p</th>\n");
		printf("<th nowrap>����F</th>\n");
		printf("<th nowrap>����F</th>\n");
		printf("<th nowrap>�p��F</th>\n");
		printf("<th nowrap>�����\�莞��</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>�X�V����</th>\n");
		printf("<th nowrap>�˗��W�J����</th>\n");
		printf("<th nowrap>�F������</th>\n");
		printf("<th nowrap>���Җ��`�F�b�N����</th>\n");
		printf("<th nowrap>���Җ��`�F�b�N��</th>\n");
		printf("<th nowrap>���MID</th>\n");
		printf("<th nowrap>�X�VID</th>\n");
		printf("<th nowrap>�F��ID</th>\n");
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
			printf("<center>�L�����Z�����̏�� (%d)��</center>\n",$nsfr->GetCanselCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>������</th>\n");
			printf("<th nowrap>�o�[�R�[�h</th>\n");
			printf("<th nowrap>�敪</th>\n");
			printf("<th nowrap>��t��</th>\n");
			printf("<th nowrap>�˗�No.</th>\n");
			printf("<th nowrap>����No.</th>\n");
			printf("<th nowrap>����KEY</th>\n");
			printf("<th nowrap>��</th>\n");
			printf("<th nowrap>CH</th>\n");
			printf("<th nowrap>SEQ</th>\n");
			printf("<th nowrap>��t</th>\n");
			printf("<th nowrap>�d��</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>���</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>�e��</th>\n");
			printf("<th nowrap>�ً}</th>\n");
			printf("<th nowrap>���uNo.</th>\n");
			printf("<th nowrap>�g���[ID:POS</th>\n");
			printf("<th nowrap>���b�NID:POS</th>\n");
			printf("<th nowrap>���mSEQ</th>\n");
			printf("<th nowrap>�d��</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>����</th>\n");
			printf("<th nowrap>�ʏ��</th>\n");
			printf("<th nowrap>���ʗ�</th>\n");
			printf("<th nowrap>������</th>\n");
			printf("<th nowrap>�����</th>\n");
			printf("<th nowrap>�Q�l��</th>\n");
			printf("<th nowrap>�P��</th>\n");
			printf("<th nowrap>���^����</th>\n");
			printf("<th nowrap>�~�A����</th>\n");
			printf("<th nowrap>�P��</th>\n");
			printf("<th nowrap>�~�A��</th>\n");
			printf("<th nowrap>�P��</th>\n");
			printf("<th nowrap>�̎�N����</th>\n");
			printf("<th nowrap>���R</th>\n");
			printf("<th nowrap>�ޗ�</th>\n");
			printf("<th nowrap>FCMT</th>\n");
			printf("<th nowrap>BCDF</th>\n");
			printf("<th nowrap>�����p</th>\n");
			printf("<th nowrap>����F</th>\n");
			printf("<th nowrap>����F</th>\n");
			printf("<th nowrap>�p��F</th>\n");
			printf("<th nowrap>�����\�莞��</th>\n");
			printf("<th nowrap>�쐬����</th>\n");
			printf("<th nowrap>�X�V����</th>\n");
			printf("<th nowrap>�˗��W�J����</th>\n");
			printf("<th nowrap>�F������</th>\n");
			printf("<th nowrap>���Җ��`�F�b�N����</th>\n");
			printf("<th nowrap>���Җ��`�F�b�N��</th>\n");
			printf("<th nowrap>���MID</th>\n");
			printf("<th nowrap>�X�VID</th>\n");
			printf("<th nowrap>�F��ID</th>\n");
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
		printf("<center>�񕪒����̏�� (%d)��</center>\n",$nsfr->GetHiBunchuCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>��Ǝ�ID</th>\n");
		printf("<th nowrap>���MID</th>\n");
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
			printf("<center>�G���[���̏�� (%d)��</center>\n",$nsfr->GetErKentaiCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>������</th>\n");
			printf("<th nowrap>�o�[�R�[�h</th>\n");
			printf("<th nowrap>�敪</th>\n");
			printf("<th nowrap>ERID</th>\n");
			printf("<th nowrap>��t��</th>\n");
			printf("<th nowrap>�˗�No.</th>\n");
			printf("<th nowrap>CMTID</th>\n");
			printf("<th nowrap>�t���[�R�����g</th>\n");
			printf("<th nowrap>�쐬����</th>\n");
			printf("<th nowrap>��Ǝ�ID</th>\n");
			printf("<th nowrap>���MID</th>\n");
			printf("<th nowrap>�쐬ID</th>\n");
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
			printf("<center>�s�����̏�� (%d)��</center>\n",$nsfr->GetFusokuCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>������</th>\n");
			printf("<th nowrap>�o�[�R�[�h</th>\n");
			printf("<th nowrap>�敪</th>\n");
			printf("<th nowrap>�쐬����</th>\n");
			printf("<th nowrap>��Ǝ�ID</th>\n");
			printf("<th nowrap>���MID</th>\n");
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
			printf("<center>�x���o�^��� (%d)��</center>\n",$nsfr->GetJizenCount());
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>������</th>\n");
			printf("<th nowrap>����No.</th>\n");
			printf("<th nowrap>SEQ</th>\n");
			printf("<th nowrap>�R�����g</th>\n");
			printf("<th nowrap>�쐬����</th>\n");
			printf("<th nowrap>��������</th>\n");
			printf("<th nowrap>��Ǝ�ID</th>\n");
			printf("<th nowrap>������ID</th>\n");
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
		printf("<center>�������̏�� (%d)��</center>\n",$nsfr->GetBunKentaiCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
		printf("<th nowrap>����������</th>\n");
		printf("<th nowrap>�g���[ID:POS</th>\n");
		printf("<th nowrap>���b�NID:POS</th>\n");
		printf("<th nowrap>�R���e�i</th>\n");
		printf("<th nowrap>�Ŕh�c</th>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>����CELL</th>\n");
		printf("<th nowrap>����STS</th>\n");
		printf("<th nowrap>��\����</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>�X�V����</th>\n");
		printf("<th nowrap>��Ǝ�ID</th>\n");
		printf("<th nowrap>���MID</th>\n");
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
		printf("<center>������� (%d)��</center>\n",$nsfr->GetBunchuCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>����������</th>\n");
		printf("<th nowrap>���b�NID:POS</th>\n");
		printf("<th nowrap>ITEM</th>\n");
		printf("<th nowrap>ITEM�Q</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>WS�P</th>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�ʏ��</th>\n");
		printf("<th nowrap>���ʗ�</th>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�z������</th>\n");
		printf("<th nowrap>���</th>\n");
		printf("<th nowrap>CELL�敪</th>\n");
		printf("<th nowrap>����STS</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>��</th>\n");
		printf("<th nowrap>Fib</th>\n");
		printf("<th nowrap>BUNPOS</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>�X�V����</th>\n");
		printf("<th nowrap>���MID</th>\n");
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
		printf("<center>�������ʏ�� (%d)��</center>\n",$nsfr->GetBunKekaCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>����������</th>\n");
		printf("<th nowrap>���uNo.</th>\n");
		printf("<th nowrap>MODNo.</th>\n");
		printf("<th nowrap>A�g���[ID:POS</th>\n");
		printf("<th nowrap>A���b�NID:POS</th>\n");
		printf("<th nowrap>A���b�NSEQ</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>CELL�敪</th>\n");
		printf("<th nowrap>NGCD</th>\n");
		printf("<th nowrap>NG��</th>\n");
		printf("<th nowrap>NG�R�����g</th>\n");
		printf("<th nowrap>������F</th>\n");
		printf("<th nowrap>���n</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>�n��</th>\n");
		printf("<th nowrap>�ڍ�</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>�X�V����</th>\n");
		printf("<th nowrap>��������</th>\n");
		printf("<th nowrap>�p����ID</th>\n");
		printf("<th nowrap>���MID</th>\n");
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
		printf("<center>�p�L�p�L��� (%d)��</center>\n",$nsfr->GetBunPakiCount());
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>ITEM</th>\n");
		printf("<th nowrap>�d��</th>\n");
		printf("<th nowrap>�d��SEQ</th>\n");
		printf("<th nowrap>����No.</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>SEQ</th>\n");
		printf("<th nowrap>A���b�NPOS</th>\n");
		printf("<th nowrap>ITEM SEQ</th>\n");
		printf("<th nowrap>RACK SEQ</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>MARK</th>\n");
		printf("<th nowrap>�o��</th>\n");
		printf("<th nowrap>�쐬����</th>\n");
		printf("<th nowrap>�X�V����</th>\n");
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
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
