<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<TITLE>サテライト一覧</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>
サテライト一覧
<HR>
<?php
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select stlid,convert(ryaku using euc_jp_to_sjis) as sname from mst_satellite where stltype != 0 order by stlid";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<LI>\n");
	printf("%s\n",trim($rec['stlid']));
//	printf("<A href=jobview.php?stlid=%s>%s</A>\n",
//			trim($rec['stlid']),trim($rec['stlid']));
	printf("<A href=jobview.php?stlid=%s>%s</A>\n",
			trim($rec['stlid']),trim($rec['sname']));
//	printf("(%s)\n",$rec['sname']);
//	printf("</LI>\n");
	}
pg_close($conn);
?>
<HR>
<P>
<A href=../index.php>トップに戻る</A>
</P>
</BODY>
</HTML>
