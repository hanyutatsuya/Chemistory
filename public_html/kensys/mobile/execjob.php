<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>

<?php
$stlid = trim($_GET['stlid']);
$jobno = $_GET['jobno'];
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select name from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%s �W���u���s</TITLE>\n",trim($rec['name']));
?>

<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>

<?php
printf("<center><h2>%s �W���u���s</h2></center>\n",trim($rec['name']));
$sql = "select jobname from mst_job where stlid = '{$stlid}' and jobno = {$jobno}";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<center><h3>�W���u����:%s �����s���܂����H</h3></center>\n",$rec['jobname']);
pg_close($conn);
?>

<FORM ACTION="execjob1.php" METHOD="POST">
<?php
printf("<INPUT TYPE=hidden NAME=stlid value=\"%s\">\n",$stlid);
printf("<INPUT TYPE=hidden NAME=jobno value=\"%d\">\n",$jobno);
?>
<P>
<center>
���[�U�[�h�c
<INPUT TYPE=text NAME="usrid" SIZE=10 MAXLENGTH=10>
</center>
</P>
<P>
<center>
�@�p�X���[�h
<INPUT TYPE=password NAME="passwd" SIZE=10 MAXLENGTH=10>
</center>
</P>
<center>
<BUTTON name="submit" value="submit" type="submit">
<h2>���s</H2>
</BUTTON>
</center>
</FORM>

<HR>
<P>
<center>

<?php
printf("<A href=exec1ran.php>�W���u�ꗗ�ɖ߂�</A></center>\n",$stlid);
?>

</center>
</P>
<P>
<center><A href=maint.html>�����e�i���X�ꗗ�ɖ߂�</A></center>
</P>
<P>
<center><A href=../index.html>�g�b�v�ɖ߂�</A></center>
</P>
</BODY>
</HTML>
