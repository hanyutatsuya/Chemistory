<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("検査グループマスタ");
LaboLogOut("検査グループマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>検査グループマスタ</h2></center>

<?php
$wscode = trim($_POST['knsgcd']);
?>


<P>
<center>
<FORM ACTION="knsgmst.php" METHOD="POST">
検査グループ
<INPUT TYPE=text NAME="knsgcd" SIZE=6 MAXLENGTH=4>
<BUTTON TYPE=submit name=submit value="submit">検索</BUTTON>
</FORM>
</center>
</P>

<?php
require_once("comm/knsgmst_tbl.inc");

if (strlen($wscode) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		printf("<HR>\n");
		knsgmst_table($conn,$wscode);
	} else {
		printf("Connection failed\n");
	}
	$conn = null;
	printf("<br clear=all>\n");

	printf("<HR>\n");
	LaboBackPage();
} else {

}
MasterTailOut();

?>

<HR>
</BODY>
</HTML>
