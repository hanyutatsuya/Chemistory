<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���ڃ}�X�^");
NsfrLogOut("���ڃ}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>���ڃ}�X�^</h2></center>

<?php
$kcode = trim($_REQUEST['KMKCD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"kmkmst.php\" METHOD=POST>\n");
printf("���ڃR�[�h\n");
printf("<INPUT TYPE=text NAME=KMKCD SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$kcode);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">����\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/nfkmkmst_tbl.inc");

if  (strlen($kcode) != 0)
	{
	$conn = Get_DBConn();

	if  ($conn)
		{
		nfkmkmst_table($conn,$kcode);
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
