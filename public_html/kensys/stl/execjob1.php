<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>

<?php
$stlid = trim($_POST['stlid']);
$jobno = $_POST['jobno'];
$usrid = trim($_POST['usrid']);
$passwd = trim($_POST['passwd']);
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select name from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%s ����ּ¹�</TITLE>\n",trim($rec['name']));
?>

<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>

<?php
printf("<center><h2>%s ����ּ¹�</h2></center>\n",trim($rec['name']));

$sql = "select jobname from mst_job where stlid = '{$stlid}' "
		. "and jobno = {$jobno}";
$result = pg_query($conn,$sql);
$db_jobname = pg_fetch_result($result,0,0);

$sql = "select pass from mst_password where usrid = '{$usrid}' ";
$result = pg_query($conn,$sql);
if  (pg_num_rows($result) == 0)
	{
	$passok = 0;
	}
else
	{
	$db_pass = trim(pg_fetch_result($result,0,0));
	$crypt_pass = crypt($passwd,$db_pass);
	if  (strcmp($db_pass,$crypt_pass) == 0)
		$passok = 1;
	else
		$passok = 0;
	}

if  ($passok == 1)
	{
	printf("<center><h3>�����̾��:%s ��¹Ԥ��ޤ���</h3></center>\n",
			$db_jobname);
	$cmd = "/home/hanyu/bin/stl_exec.exe " . $stlid . " " . $jobno;
	shell_exec($cmd);
	}
else
	{
	printf("<center><h3>�����̾��:%s ���¹ԤǤ��ޤ���Ǥ���</h3></center>\n",
			$db_jobname);
	}
pg_close($conn);
?>

<P>
</P>

<HR>
<P>
<center>

<?php
printf("<A href=exec1ran.php>����ְ��������</A></center>\n",$stlid);
?>

</center>
</P>
<P>
<center><A href=maint.html>���ƥʥ󥹰��������</A></center>
</P>
<P>
<center><A href=../index.php>�ȥåפ����</A></center>
</P>
</BODY>
</HTML>
