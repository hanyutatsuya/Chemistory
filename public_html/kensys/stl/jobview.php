<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>

<?php
$stlid = trim($_GET['stlid']);
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select name from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%sジョブ一覧</TITLE>\n",$rec['name']);
?>

<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>

<?php
printf("<center><h2>%sジョブ一覧</h2></center>\n",$rec['name']);
?>

<table align="center" border>
<tr>
<th>ジョブNo.</th>
<th>ジョブ名称</th>
</tr>

<?php
$sql = "select jobno,jobname from mst_job where stlid = '{$stlid}' order by jobno";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<tr>\n");
	printf("<td><A href=res1ran.php?stlid=%s&jobno=%s>%s</A></td>\n",
			$stlid,$rec['jobno'],$rec['jobno']);
	printf("<td><A href=res1ran.php?stlid=%s&jobno=%s>%s</A></td>\n",
			$stlid,$rec['jobno'],$rec['jobname']);
	printf("</tr>\n");
	}
pg_close($conn);
?>

</table>
<HR>
<P>
<center><A href=satellite.php>サテライト一覧に戻る</A></center>
</P>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
