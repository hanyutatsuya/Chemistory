<?
printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n");
printf("<HTML lang=\"ja\">\n");
printf("<HEAD>\n");
printf("<TITLE>サテライト一覧</TITLE>\n");
printf("<META http-equiv=\"Content-Type\" content=\"text/html; charset=EUC-JP\">\n");
printf("</HEAD>\n");
printf("<BODY>\n");
printf("<center><h2>サテライト一覧</h2></center>\n");
printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th>サテライトＩＤ</th>\n");
printf("<th>サテライト名称</th>\n");
printf("</tr>\n");

$conn = pg_connect("dbname=kensys user=hanyu");
$sql = "select stlid,name from mst_satellite where stltype != 0 order by stlid";
$result = pg_query($conn,$sql);
for ($i=0;$i<pg_num_rows($result);$i++)
	{
	$rec = pg_fetch_array($result,$i);
	printf("<tr>\n");
	printf("<td>%s</td>\n",$rec['stlid']);
	printf("<td>%s</td>\n",$rec['name']);
	printf("</tr>\n");
	}
pg_close($conn);
printf("</table>\n");
printf("</BODY>\n");
printf("</HTML>\n");
?>
