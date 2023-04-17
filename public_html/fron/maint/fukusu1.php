<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_class.inc");
require_once("../comm/ssmst_class.inc");

$title = "�����{��茟�̓o�^����";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate  = $_POST['SDATE'];
$kenno  = $_POST['KENNO'];
$sskbn  = trim($_POST['SSKBN']);
$kenseq = (int)trim($_POST['KENSEQ']);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>������ �F%s</P>\n",ymd_edit($sdate));
printf("<P>����No.�F%s</P>\n",kenno_edit(barcode_conv($kenno)));

//$conn = new PDO('odbc:NSFRDB1','nsfr','nsfr');
$conn = Get_DBConn();
$nsfr = new Nsfr($conn);
$nsfr->Clear();
$nsfr->SetSdate($sdate);
$nsfr->SetKenno($kenno);

ShowResult($nsfr);

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=maint.php?SDATE=%s>�����e�i���X�����ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
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
		printf("<P>�Y������˗��͂���܂���B</P>\n");
		printf("<P>\n");
		printf("�����{�o�^���錟��No.����͂��Ă�������\n");
		printf("<FORM ACTION=\"fukusu1.php\" METHOD=\"POST\">\n");
		printf("<INPUT TYPE=text NAME=\"KENNO\" SIZE=14 MAXLENGTH=13>\n");

		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">����\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");

		return(FALSE);
		}

	//	���Җ��\��
	$kan = &$nsfr->GetZokusei();
	printf("<P>���Җ� �F%s</P>\n",$kan[6]);

	$ssmst = new SsMst($conn);

	$kri = &$nsfr->GetKKentai();

	//	�d������ޕ\��
	if  ($sskbn == "")
		{
		if  ($nsfr->GetKKentaiCount() == 1)
			{
			printf("<P>�ޗ���<FONT color=red><STRONG>(%s)</STRONG></FONT>�ł��B</P>\n",$ssmst->GetRName($kri[0][10]));
//			printf("<HR>\n");
			$kenseq = (int)$kri[0][2];
			}
		else
			{
			printf("<HR>\n");
			printf("<P>\n");
			printf("�ޗ��������˗�����Ă��܂��B<BR>\n");
			printf("�����o�^����ޗ���I�����Ă��������B<BR>\n");
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
			printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">�I��\n");
			printf("</BUTTON>\n");
			printf("</FORM>\n");
			printf("</P>\n");
			return(FALSE);
			}
		}
	else
		{
		printf("<P>�ޗ�<FONT color=red><STRONG>(%s)</STRONG></FONT>���I������Ă��܂��B</P>\n",$ssmst->GetRName($sskbn));
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

	//	�o�^�ςݕ����{�m�F�\��
	$cnt = 0;
	for ($i=0;$i<$nsfr->GetKKentaiCount();$i++)
		{
		if  ((int)$kri[$i][2] == $kenseq)
			$cnt++;
		}
	if  ($cnt > 1)
		{
		printf("<P>(%d)���̕����{���̂��o�^�ς݂ł��B</P>\n",$cnt);

		printf("<table align=left border>\n");
		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>�ʏ��</th>\n");
		printf("<th nowrap>���ʗ�</th>\n");
		printf("<th nowrap>������</th>\n");
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
		printf("�����{�o�^���錟��No.����͂��Ă�������\n");
		printf("<FORM ACTION=\"fukusu_add.php\" METHOD=\"POST\">\n");
		printf("<INPUT TYPE=text NAME=\"KENNO1\" SIZE=14 MAXLENGTH=13>\n");

		printf("<INPUT TYPE=hidden NAME=\"TYPE\" value=\"0\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
		printf("<INPUT TYPE=hidden NAME=\"SSKBN\" value=\"%s\">\n",$sskbn);
		printf("<INPUT TYPE=hidden NAME=\"KENSEQ\" value=\"%d\">\n",$kenseq);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">�o�^\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");
		return(FALSE);
		}

	//	�F���ς݌��̕\��
	$ken = &$nsfr->GetKentai();
	$cnt = 0;
	for ($i=0;$i<$nsfr->GetKentaiCount();$i++)
		{
		if  ((int)$ken[$i][9] == $kenseq)
			$cnt++;
		}

	if  ($cnt == 0)
		{
		printf("<P>���͖̂��F���ł��B</P>\n");
		printf("<HR>\n");
		printf("<P>\n");
		printf("�����{�o�^���錟��No.����͂��Ă�������\n");
		printf("<FORM ACTION=\"fukusu_add.php\" METHOD=\"POST\">\n");
		printf("����No. �P�{��<INPUT TYPE=text NAME=\"KENNO1\" SIZE=14 MAXLENGTH=13>\n");
		printf("<BR>\n");
		printf("����No. �Q�{��<INPUT TYPE=text NAME=\"KENNO2\" SIZE=14 MAXLENGTH=13>\n");
		printf("<BR>\n");

		printf("<INPUT TYPE=hidden NAME=\"TYPE\" value=\"2\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
		printf("<INPUT TYPE=hidden NAME=\"SSKBN\" value=\"%s\">\n",$sskbn);
		printf("<INPUT TYPE=hidden NAME=\"KENSEQ\" value=\"%d\">\n",$kenseq);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">�o�^\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");
		}
	else
		{
		printf("<P>(%d)���̌��̂��F���ς݂ł��B</P>\n",$cnt);

		printf("<table align=left border>\n");

		printf("<tr>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�o�[�R�[�h</th>\n");
		printf("<th nowrap>CH</th>\n");
		printf("<th nowrap>���uNo.</th>\n");
		printf("<th nowrap>�g���[ID:POS</th>\n");
		printf("<th nowrap>���b�NID:POS</th>\n");
		printf("<th nowrap>�ʏ��</th>\n");
		printf("<th nowrap>���ʗ�</th>\n");
		printf("<th nowrap>������</th>\n");
		printf("<th nowrap>�����</th>\n");
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
		printf("�����{�o�^���錟��No.����͂��Ă�������\n");
		printf("<FORM ACTION=\"fukusu_add.php\" METHOD=\"POST\">\n");
		printf("<INPUT TYPE=text NAME=\"KENNO1\" SIZE=14 MAXLENGTH=13>\n");

		printf("<INPUT TYPE=hidden NAME=\"TYPE\" value=\"1\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
		printf("<INPUT TYPE=hidden NAME=\"KENNO\" value=\"%s\">\n",$kenno);
		printf("<INPUT TYPE=hidden NAME=\"SSKBN\" value=\"%s\">\n",$sskbn);
		printf("<INPUT TYPE=hidden NAME=\"KENSEQ\" value=\"%d\">\n",$kenseq);
		printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">�o�^\n");
		printf("</BUTTON>\n");
		printf("</FORM>\n");
		printf("</P>\n");
		}

	return(TRUE);

};

?>

