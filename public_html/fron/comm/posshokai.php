<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("nsfr_html.inc");
require_once("nsfr_comm.inc");
require_once("nsfr_db.inc");
require_once("nsfr_class.inc");

$title = "���̃|�W�V�����Ɖ�";
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
		$ken = &$nsfr->GetKentai();
		$can = &$nsfr->GetCansel();
		$jzn = &$nsfr->GetJizen();
		$bkn = &$nsfr->GetBunKentai();
		$bka = &$nsfr->GetBunKeka();
		$pkp = &$nsfr->GetBunPaki();

		printf("���ҏ��\n");
		printf("<table align=left frame=box border>\n");

		printf("<tr>\n");
		printf("<th nowrap>��t��</th>\n");
		printf("<th nowrap>�˗�No.</th>\n");
//		printf("<th nowrap>��</th>\n");
//		printf("<th nowrap>��t</th>\n");
//		printf("<th nowrap>����</th>\n");
//		printf("<th nowrap>����ID</th>\n");
		printf("<th nowrap>���Җ�</th>\n");
//		printf("<th nowrap>���Җ�ID</th>\n");
//		printf("<th nowrap>����</th>\n");
//		printf("<th nowrap>���N����</th>\n");
//		printf("<th nowrap>�敪</th>\n");
//		printf("<th nowrap>�N��</th>\n");
//		printf("<th nowrap>�敪</th>\n");
		printf("<th nowrap>�{��CD</th>\n");
//		printf("<th nowrap>SUBCD</th>\n");
		printf("<th nowrap>�{�ݖ�</th>\n");
		printf("<th nowrap>�c�Ə�CD</th>\n");
//		printf("<th nowrap>�V�cCD</th>\n");
		printf("<th nowrap>���R</th>\n");
//		printf("<th nowrap>���̖{��</th>\n");
//		printf("<th nowrap>CMT1</th>\n");
//		printf("<th nowrap>CMT2</th>\n");
//		printf("<th nowrap>CMT3</th>\n");
//		printf("<th nowrap>CMTF1</th>\n");
//		printf("<th nowrap>CMTF2</th>\n");
//		printf("<th nowrap>��</th>\n");
//		printf("<th nowrap>�W</th>\n");
//		printf("<th nowrap>����</th>\n");
//		printf("<th nowrap>POOL</th>\n");
//		printf("<th nowrap>����</th>\n");
//		printf("<th nowrap>�쐬����</th>\n");
//		printf("<th nowrap>�X�V����</th>\n");
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
		printf("�F���|�W�V������� \n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>���uNo.</th>\n");
		printf("<th nowrap>�g���[ID:POS</th>\n");
		printf("<th nowrap>���b�NID:POS</th>\n");
		printf("<th nowrap>�����</th>\n");
		printf("<th nowrap>����F</th>\n");
		printf("<th nowrap>�F������</th>\n");
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
			printf("���O�o�^���\n");
			printf("<table align=left border>\n");

			printf("<tr>\n");
			printf("<th nowrap>������</th>\n");
			printf("<th nowrap>����No.</th>\n");
//			printf("<th nowrap>SEQ</th>\n");
			printf("<th nowrap>�R�����g</th>\n");
			printf("<th nowrap>�쐬����</th>\n");
//			printf("<th nowrap>��������</th>\n");
			printf("<th nowrap>��Ǝ�ID</th>\n");
//			printf("<th nowrap>������ID</th>\n");
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
		printf("�������|�W�V�������\n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>�R�|�h�c</th>\n");
		printf("<th nowrap>���b�NID:POS</th>\n");
		printf("<th nowrap>�g���[ID:POS</th>\n");
		printf("<th nowrap>�R���e�i</th>\n");
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
		printf("�A�b�Z�C���b�N���\n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>���uNo.</th>\n");
		printf("<th nowrap>MODNo.</th>\n");
		printf("<th nowrap>A���b�NID:POS</th>\n");
		printf("<th nowrap>STID</th>\n");
		printf("<th nowrap>����</th>\n");
		printf("<th nowrap>��������</th>\n");
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
		printf("�p�L�p�L���\n");
		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>WSCD</th>\n");
		printf("<th nowrap>����No.</th>\n");
//		printf("<th nowrap>ITEM</th>\n");
		printf("<th nowrap>�d��</th>\n");
		printf("<th nowrap>�d��SEQ</th>\n");
//		printf("<th nowrap>����No.</th>\n");
//		printf("<th nowrap>�敪</th>\n");
//		printf("<th nowrap>SEQ</th>\n");
//		printf("<th nowrap>A���b�NPOS</th>\n");
//		printf("<th nowrap>RACK SEQ</th>\n");
//		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>MARK</th>\n");
//		printf("<th nowrap>�o��</th>\n");
//		printf("<th nowrap>�쐬����</th>\n");
//		printf("<th nowrap>�X�V����</th>\n");
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
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
