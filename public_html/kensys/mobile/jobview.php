<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>

<?php
$stlid = trim($_GET['stlid']);
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select convert(ryaku using euc_jp_to_sjis) as rname from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%sジョブ一覧</TITLE>\n",$rec['rame']);
?>

<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>

<?php
printf("%sジョブ一覧\n",$rec['rname']);
?>

<HR>

<?php
$sql = "select jobno,convert(jobname using euc_jp_to_sjis) as jname from mst_job where stlid = '{$stlid}' order by jobno";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<LI>\n");
	printf("%s\n",$rec['jobno']);
//	printf("<A href=res1ran.php?stlid=%s&jobno=%s>%s</A>\n",
//			$stlid,$rec['jobno'],$rec['jobno']);
	printf("<A href=res1ran.php?stlid=%s&jobno=%s>%s</A>\n",
			$stlid,$rec['jobno'],$rec['jname']);
//	printf("</LI>\n");
	}
pg_close($conn);
?>

<HR>
<P>
<A href=satellite.php>サテライト一覧に戻る</A>
<BR>
<A href=../index.php>トップに戻る</A>
</P>
</BODY>
</HTML>
