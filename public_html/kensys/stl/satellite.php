<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>���ƥ饤�Ȱ���</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>
<center><h2>���ƥ饤�Ȱ���</h2></center>
<table align="center" border>

<tr>
<th>���ƥ饤�ȣɣ�</th>
<th>���ƥ饤��̾��</th>
</tr>

<?php
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select stlid,name from mst_satellite where stltype != 0 order by stlid";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<tr>\n");
	printf("<td><A href=jobview.php?stlid=%s>%s</A></td>\n",
			trim($rec['stlid']),$rec['stlid']);
	printf("<td><A href=jobview.php?stlid=%s>%s</A></td>\n",
			trim($rec['stlid']),$rec['name']);
	printf("</tr>\n");
	}
pg_close($conn);
?>

</table>
<HR>
<P>
<center><A href=../index.php>�ȥåפ����</A></center>
</P>
</BODY>
</HTML>
