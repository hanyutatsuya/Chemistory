<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>���ƥ饤�ȥޥ���</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>
<center><h2>���ƥ饤�ȥޥ���</h2></center>
<table align="center" border>

<tr>
<th>STLID</th>
<th>TYPE</th>
<th>���ƥ饤��̾��</th>
<th>ά��</th>
<th>�ۥ���̾</th>
<th>IP���ɥ쥹</th>
<th>��Ͽǯ����</th>
<th>����ǯ����</th>
<th>�ѹ�ǯ����</th>
</tr>

<?php
$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select * from mst_satellite order by stlid";
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
<center><A href=mst1ran.html>�ޥ��������������</A></center>
</P>
</BODY>
</HTML>
