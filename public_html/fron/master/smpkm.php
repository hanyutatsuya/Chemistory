<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�T���v�����O�E���ڃ}�X�^");
NsfrLogOut("�T���v�����O�E���ڃ}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�T���v�����O�E���ڃ}�X�^</h2></center>

<?php
$wscode = trim($_REQUEST['SMPCD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"smpkm.php\" METHOD=POST>\n");
printf("�T���v�����O�R�[�h\n");
printf("<INPUT TYPE=text NAME=SMPCD SIZE=6 MAXLENGTH=4 value=\"%s\">\n",$wscode);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">����\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/nfsmpkm_tbl.inc");

if  (strlen($wscode) != 0)
	{
	$conn = Get_DBConn();

	if  ($conn)
		{
		nfsmpkm_table($conn,$wscode);
		}
	else
		{
		echo "Connection failed";
		}
	$conn = null;
	printf("<br clear=all>\n");
	}
?>

<?php
printf("<HR>\n");
NsfrBackPage();
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
