<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>ジョブ一覧</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>
<center><h2>ジョブ一覧</h2></center>

<table align="center" border>
<tr>
<th>STLID</th>
<th>サテライト名</th>
<th>JOB No.</th>
<th>ジョブ名称</th>
</tr>

<?php
$today = getdate();
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select s.stlid,s.ryaku,j.jobno,j.jobname,j.yobi "
. "from mst_satellite s,mst_job j where s.stlid = j.stlid "
. "order by s.stlid,j.jobno";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	if  (strcmp(substr($rec['yobi'],$today['wday'],1),"1") == 0)
		{
		printf("<tr>\n");
		printf("<td><A href=execjob.php?stlid=%s&jobno=%d>%s</A></td>\n",
						trim($rec['stlid']),$rec['jobno'],$rec['stlid']);
		printf("<td><A href=execjob.php?stlid=%s&jobno=%d>%s</A></td>\n",
						trim($rec['stlid']),$rec['jobno'],$rec['ryaku']);
		printf("<td><A href=execjob.php?stlid=%s&jobno=%d>%s</A></td>\n",
						trim($rec['stlid']),$rec['jobno'],$rec['jobno']);
		printf("<td><A href=execjob.php?stlid=%s&jobno=%d>%s</A></td>\n",
						trim($rec['stlid']),$rec['jobno'],$rec['jobname']);
		printf("</tr>\n");
		}
	}
pg_close($conn);
?>

</table>
<HR>
<P>
<center><A href=maint.html>メンテナンス一覧に戻る</A></center>
</P>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
