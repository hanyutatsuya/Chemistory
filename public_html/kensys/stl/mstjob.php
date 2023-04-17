<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>ジョブマスタ</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>
<center><h2>ジョブマスタ</h2></center>
<table align="center" border>

<tr>
<th>STLID</th>
<th>JOB No.</th>
<th>ジョブ名称</th>
<th>USER</th>
<th>TYPE</th>
<th>モジュール名</th>
<th>実行曜日</th>
<th>実行間隔</th>
<th>実行時刻</th>
<th>登録年月日</th>
<th>開始年月日</th>
<th>変更年月日</th>
</tr>

<?php
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select * from mst_job order by stlid,jobno";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	printf("<tr>\n");
	for ($j=0;$j<pg_num_fields($result);$j++)
		{
		$rec = pg_fetch_result($result,$i,$j);
		printf("<td>%s</td>\n",$rec);
		}
	printf("</tr>\n");
	}
pg_close($conn);
?>

</table>
<HR>
<P>
<center><A href=mst1ran.html>マスター一覧に戻る</A></center>
</P>
</BODY>
</HTML>
