<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�d������ށE�����敪������");
NsfrLogOut("�d������ށE�����敪������");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�d������ށE�����敪������</h2></center>

<?php
$wsflg = trim($_GET['WS999']);
$ckflg = trim($_GET['CKFLG']);
$wscd = trim($_GET['WSCD']);
?>

<P>
<FORM ACTION="chk_ssok.php" METHOD="GET">
<?php
if  ($wsflg == "")
	printf("<INPUT TYPE=checkbox NAME=WS999 value=1>\n");
else
	printf("<INPUT TYPE=checkbox NAME=WS999 value=1 checked>\n");

printf("WS998,999���܂߂Ȃ��@\n");
if  ($ckflg == "0")
	{
	printf("<INPUT TYPE=radio NAME=CKFLG value=0 checked>�d������ރ`�F�b�N\n");
	printf("<INPUT TYPE=radio NAME=CKFLG value=1>�����敪�`�F�b�N\n");
	}
else
	{
	printf("<INPUT TYPE=radio NAME=CKFLG value=0>�d������ރ`�F�b�N\n");
	printf("<INPUT TYPE=radio NAME=CKFLG value=1 checked>�����敪�`�F�b�N\n");
	}

printf("<BUTTON name=submit value=submit type=submit>�ݒ�\n");
printf("</BUTTON>\n");
if  ($wscd != "")
	printf("<INPUT TYPE=hidden name=WSCD value=%s\n",$wscd);
?>

</FORM>
</P>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>�敪</th>
<th>�d������ޖ�</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "";
	if  ($ckflg == "0")
		$sql = $sql . "select distinct km.smpcd,ws.smpcdnm,km.sskbn ";
	else
		$sql = $sql . "select distinct km.smpcd,ws.smpcdnm,km.bckbn ";
	$sql = $sql . "from nfkmkmst km,nfsmpmst ws ";
	if  ($wsflg != "")
		$sql = $sql . "where km.smpcd not in ('0998','0999') and ";
	else
	$sql = $sql . "where ";
	$sql = $sql . "km.ukflg = '1' ";
	$sql = $sql . "and ws.smpcd = km.smpcd ";
	$sql = $sql . "and ws.ukflg = '1' ";
	if  ($ckflg == "0")
		$sql = $sql . "order by km.smpcd,km.sskbn ";
	else
		$sql = $sql . "order by km.smpcd,km.bckbn ";
	$sv_wscode = "";
	$sv_wsname = "";
	foreach ($conn->query($sql) as $row)
		{
		if  ($sv_wscode == "")
			{
			$sv_wscode = $row[0];
			$sv_wsname = $row[1];
			$sv_flg = 0;
			}
		else
			{
			if  ($sv_wscode == $row[0] && $sv_flg == 0)
				{
				printf("<tr>\n");
				printf("<td><A href=chk_ssok.php?WS999=%s&CKFLG=%s&WSCD=%s>%s</A></td>\n",$wsflg,$ckflg,$sv_wscode,$sv_wscode);
				printf("<td><A href=chk_ssok.php?WS999=%s&CKFLG=%s&WSCD=%s>%s</A></td>\n",$wsflg,$ckflg,$sv_wscode,$sv_wsname);
				printf("</tr>\n");
				$sv_flg = 1;
				}
			else
				{
				if  ($sv_wscode != $row[0])
					$sv_flg = 0;
				}
			$sv_wscode = $row[0];
			$sv_wsname = $row[1];
			}
		}
	printf("</table>\n");

	if  ($wscd != "")
		{
		printf("<td>\n");
		printf("<table bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th>WS�R�[�h</th>\n");
		printf("<th>�e�R�[�h</th>\n");
		printf("<th>���ڃR�[�h</th>\n");
		printf("<th>���ږ�</th>\n");
		printf("<th>TBF</th>\n");
		printf("<th>�d����</th>\n");
		printf("<th>�����敪</th>\n");
		printf("</tr>\n");

		$sql = "";
		$sql = $sql . "select smpcd,oyakmkcd,kmkcd,kmknmr,bkfkkbn,sskbn,bckbn ";
		$sql = $sql . "from nfkmkmst ";
		$sql = $sql . "where smpcd = '$wscd' ";
		$sql = $sql . "and ukflg = '1' ";
		$sql = $sql . "order by oyakmkcd,kmkcd for read only";
		foreach ($conn->query($sql) as $row)
			{
			printf("<tr>\n");
			printf("<td>%s</td>\n",$row[0]);
			printf("<td>%s</td>\n",$row[1]);
			printf("<td>%s</td>\n",$row[2]);
			printf("<td>%s</td>\n",$row[3]);
			printf("<td>%s</td>\n",$row[4]);
			printf("<td>%s</td>\n",$row[5]);
			printf("<td>%s</td>\n",$row[6]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("</td>\n");
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

?>
</td>
</table>

<br clear=all>

<?php
require_once("../comm/mstchk_tail.inc");
?>

<HR>
</BODY>
</HTML>
