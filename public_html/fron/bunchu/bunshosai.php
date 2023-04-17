<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_class.inc");
?>

<?php
$sdate = $_GET['SDATE'];
$kenno = trim($_GET['KENNO']);
$barcd = trim($_GET['BARCD']);

$title = "�������ʏƉ�";


NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$conn = Get_DBConn();



if  ($conn)
	{

	$nsfr = new Nsfr($conn);
	$nsfr->Clear();
	$nsfr->SetSdate($sdate);
	$nsfr->SetKenno($kenno);
	$nsfr->SetBarcd($barcd);

	$kan = $nsfr->GetZokusei();
	$ken = $nsfr->GetKentai();
	$bun = $nsfr->GetBunKeka();

	printf("<center><P>���ҏ��</P></center>\n");

	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>��t��</th>\n");
	printf("<th>�˗���No.</th>\n");
	printf("<th>���Җ�</th>\n");
	printf("<th>�{�ݖ�</th>\n");
	printf("<th>�c�Ə�CD</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td>%s</td>\n",ymd_edit($kan[0]));
	printf("<td>%s</td>\n",ino_edit($kan[1]));
	printf("<td>%s</td>\n",$kan[6]);
	printf("<td>%s:%s</td>\n",$kan[13],$kan[15]);
	printf("<td>%s-%s</td>\n",$kan[16],$kan[17]);
	printf("</tr>\n");
	printf("</table>\n");

	printf("<center><P>���̏��</P></center>\n");

	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>������</th>\n");
	printf("<th>����No.</th>\n");
	printf("<th>�o�[�R�[�h</th>\n");
	printf("<th>CH</th>\n");
	printf("<th>�d����</th>\n");
	printf("<th>����</th>\n");
	printf("<th>�g���[ID:POS</th>\n");
	printf("<th>���b�NID:POS</th>\n");
	printf("<th>���̗�</th>\n");
	printf("</tr>\n");

	for ($i=0;$i<count($ken);$i++)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",ymd_edit($ken[$i][0]));
		printf("<td>%s</td>\n",kenno_edit($ken[$i][5]));
		printf("<td>%s</td>\n",barcode_edit($ken[$i][1]));
		printf("<td>%s</td>\n",$ken[$i][8]);
		printf("<td>%s</td>\n",$ken[$i][11]);
		printf("<td>%s</td>\n",$ken[$i][15]);
		printf("<td>%s-%02d</td>\n",$ken[$i][19],$ken[$i][20]);
		printf("<td>%s-%02d</td>\n",$ken[$i][21],$ken[$i][22]);
		printf("<td>%s</td>\n",$ken[$i][32]);
		printf("</tr>\n");
		}
	printf("</table>\n");
	
	printf("<center><P>��������</P></center>\n");

	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>������</th>\n");
	printf("<th>�o�[�R�[�h</th>\n");
	printf("<th>WSCD</th>\n");
	printf("<th>CELL</th>\n");
	printf("<th>MOD</th>\n");
	printf("<th>�g���[ID:POS</th>\n");
	printf("<th>���b�NID:POS</th>\n");
	printf("<th nowrap>NGCD</th>\n");
	printf("<th nowrap>NG��</th>\n");
	printf("<th nowrap>NG�R�����g</th>\n");

	printf("</tr>\n");

	for ($i=0;$i<count($bun);$i++)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",ymd_edit($bun[$i][0]));
		printf("<td>%s</td>\n",barcode_edit($bun[$i][1]));
		printf("<td>%s</td>\n",$bun[$i][3]);
		printf("<td>%s</td>\n",substr($bun[$i][6],2,2));
		printf("<td>%s</td>\n",$bun[$i][7]);
		printf("<td>%s-%s</td>\n",$bun[$i][8],$bun[$i][9]);
		printf("<td>%s-%s</td>\n",$bun[$i][10],$bun[$i][12]);
		printf("<td nowrap>%s</td>\n",$bun[$i][16]);
		printf("<td nowrap>%s</td>\n",$bun[$i][17]);
		printf("<td nowrap>%s</td>\n",$bun[$i][18]);
		printf("</tr>\n");
		}
	printf("</table>\n");


	}
else
	{
	echo "Connection failed";
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
