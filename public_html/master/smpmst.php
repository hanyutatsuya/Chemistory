<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�T���v�����O�}�X�^");
NsfrLogOut("�T���v�����O�}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�T���v�����O�}�X�^</h2></center>

<?php
$wscode = trim($_POST['smpcd']);
?>


<P>
<center>
<FORM ACTION="smpmst.php" METHOD="POST">
�T���v�����O�R�[�h
<INPUT TYPE=text NAME="smpcd" SIZE=6 MAXLENGTH=4>
<BUTTON name="submit" value="submit" type="submit">����
</BUTTON>
</FORM>
</center>
</P>
<HR>

<?php
require_once("comm/nfsmpmst_tbl.inc");

if  (strlen($wscode) != 0)
	{
	$conn = Get_DBConn();

	if  ($conn)
		{
		nfsmpmst_table($conn,$wscode);
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
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
