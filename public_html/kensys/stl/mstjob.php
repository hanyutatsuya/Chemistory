<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>����֥ޥ���</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=EUC-JP">
</HEAD>
<BODY>
<center><h2>����֥ޥ���</h2></center>
<table align="center" border>

<tr>
<th>STLID</th>
<th>JOB No.</th>
<th>�����̾��</th>
<th>USER</th>
<th>TYPE</th>
<th>�⥸�塼��̾</th>
<th>�¹�����</th>
<th>�¹Դֳ�</th>
<th>�¹Ի���</th>
<th>��Ͽǯ����</th>
<th>����ǯ����</th>
<th>�ѹ�ǯ����</th>
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
<center><A href=mst1ran.html>�ޥ��������������</A></center>
</P>
</BODY>
</HTML>
