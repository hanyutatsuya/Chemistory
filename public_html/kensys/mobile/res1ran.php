<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>

<?php
$stlid = trim($_GET['stlid']);
$jobno = $_GET['jobno'];
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select convert(ryaku using euc_jp_to_sjis) as rname from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%s実行結果一覧</TITLE>\n",$rec['rname']);
?>

<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>

<?php
printf("%s実行結果一覧\n",$rec['rname']);
$sql = "select convert(jobname using euc_jp_to_sjis) as jname from mst_job where stlid = '{$stlid}' and jobno = {$jobno}";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("%s\n",$rec['jname']);
?>

<HR>

<?php
$sql = "select distinct seq,to_char(stamp,'MM/DD HH24:MI') as tm "
. "from dat_result where stlid = '{$stlid}' and jobno = {$jobno} order by tm desc";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<LI>\n");
	printf("%s\n",$rec['seq']);
	printf("<A href=result.php?stlid=%s&jobno=%s&seq=%d>%s</A>\n",
			$stlid,$jobno,$rec['seq'],$rec['tm']);
//	printf("</LI>\n");
	}
pg_close($conn);
?>

<HR>
<P>
<?php
printf("<A href=jobview.php?stlid=%s>ジョブ一覧に戻る</A></center>\n",$stlid);
?>
<BR>
<A href=satellite.php>サテライト一覧に戻る</A>
<BR>
<A href=../index.php>トップに戻る</A>
</P>
</BODY>
</HTML>
