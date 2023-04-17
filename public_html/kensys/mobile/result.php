<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>

<?php
$stlid = $_GET['stlid'];
$jobno = $_GET['jobno'];
$seq = $_GET['seq'];
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select convert(ryaku using euc_jp_to_sjis) as rname from mst_satellite where stlid = '$stlid'";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("<TITLE>%s実行結果</TITLE>\n",$rec['rname']);
?>

<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>

<?php
printf("%s実行結果\n",$rec['rname']);
$sql = "select convert(jobname using euc_jp_to_sjis) as jname from mst_job where stlid = '{$stlid}' and jobno = {$jobno}";
$result = pg_query($conn,$sql);
$rec = pg_fetch_array($result,0);
printf("%s\n",$rec['jname']);
?>

実行日時:

<?php
$sql = "select to_char(stamp,'MM/DD HH24:MI') as tm,resno,"
. "convert(keyword using euc_jp_to_sjis) as kwd,convert(result using euc_jp_to_sjis) as res from dat_result "
. "where stlid = '{$stlid}' and jobno = {$jobno} and seq = {$seq} order by resno";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	if  ($i == 0)
		{
		printf("実行日時:%s\n<HR>\n",$rec['tm']);
		}
	printf("<LI>\n");
	printf("%s:\n",$rec['kwd']);
	printf("%s\n",$rec['res']);
//	printf("</LI>\n");
	}
pg_close($conn);
?>
<HR>
<P>
<?php
printf("<A href=res1ran.php?stlid=%s&jobno=%s>実行結果一覧に戻る</A>\n",
            $stlid,$jobno);
?>
<BR>
<?php
printf("<A href=jobview.php?stlid=%s>ジョブ一覧に戻る</A>\n",$stlid);
?>
<BR>
<A href=satellite.php>サテライト一覧に戻る</A>
<BR>
<A href=../index.php>トップに戻る</A>
</P>
</BODY>
</HTML>
