<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>

<?php
$stlid = $_GET['stlid'];
$jobno = $_GET['jobno'];
$seq = $_GET['seq'];
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select name from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%s����ּ¹Է��</TITLE>\n",$rec['name']);
?>

<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>

<?php
printf("<center><h2>%s����ּ¹Է��</h2></center>\n",$rec['name']);
$sql = "select jobname from mst_job where stlid = '{$stlid}' and jobno = {$jobno}";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<center><h3>�����̾��:%s</h3></center>\n",$rec['jobname']);
?>

<table align="center" border>
<tr>
<th>�¹�����</th>
<th>�������</th>
<th>����</th>
</tr>

<?php
$sql = "select stamp,resno,keyword,result from dat_result where stlid = '{$stlid}' and jobno = {$jobno} and seq = {$seq} order by resno";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<tr>\n");
	printf("<td>%s</td>\n",$rec['stamp']);
	printf("<td>%s</td>\n",$rec['keyword']);
	printf("<td>%s</td>\n",$rec['result']);
	printf("</tr>\n");
	}
pg_close($conn);
?>

</table>
<HR>
<P>
<center>

<?php
printf("<A href=res1ran.php?stlid=%s&amp;jobno=%s>�¹Է�̰��������</A>\n",
            $stlid,$jobno);
?>

</center>
</P>
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
