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
printf("<TITLE>%s����ּ¹Է�̰���</TITLE>\n",$rec['name']);
?>

<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>

<?php
printf("<center><h2>%s����ּ¹Է�̰���</h2></center>\n",$rec['name']);
$sql = "select jobname from mst_job where stlid = '{$stlid}' and jobno = {$jobno}";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<center><h3>�����̾��:%s</h3></center>\n",$rec['jobname']);
?>

<table align="center" border>
<tr>
<th>SEQ No.</th>
<th>�¹�����</th>
</tr>

<?php
$sql = "select distinct seq,stamp from dat_result where stlid = '{$stlid}' and jobno = {$jobno} order by stamp desc";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<tr>\n");
	printf("<td><A href=result.php?stlid=%s&jobno=%s&seq=%d>%s</A></td>\n",
			$stlid,$jobno,$rec['seq'],$rec['seq']);
	printf("<td><A href=result.php?stlid=%s&jobno=%s&seq=%d>%s</A></td>\n",
			$stlid,$jobno,$rec['seq'],$rec['stamp']);
	printf("</tr>\n");
	}
pg_close($conn);
?>

</table>
<HR>
<P>
<center>

<?php
printf("<A href=jobview.php?stlid=%s>����ְ��������</A></center>\n",$stlid);
?>

</center>
</P>
<P>
<center><A href=satellite.php>���ƥ饤�Ȱ��������</A></center>
</P>
<P>
<center><A href=../index.php>�ȥåפ����</A></center>
</P>
</BODY>
</HTML>
