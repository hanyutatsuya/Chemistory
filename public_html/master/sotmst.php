<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("uÇ}X^");
NsfrLogOut("uÇ}X^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>uÇ}X^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>uNo.</th>
<th>uíÞæª</th>
<th>u¼</th>
<th>uªÌ</th>
<th>IPAhX</th>
<th>PORTP</th>
<th>PORTQ</th>
<th>Jnú</th>
<th>I¹ú</th>
<th>ì¬</th>
<th>XV</th>
<th>ìÆÒhc</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfsotmst where ukflg = '1' order by devno for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['DEVNO']);
		printf("<td>%s</td>\n",$row['DEVKBN']);
		printf("<td>%s</td>\n",$row['DEVNM']);
		printf("<td>%s</td>\n",$row['DEVNMR']);
		printf("<td>%s</td>\n",$row['IPADD']);
		printf("<td>%s</td>\n",$row['PORT1']);
		printf("<td>%s</td>\n",$row['PORT2']);
		printf("<td>%s</td>\n",$row['STYMD']);
		printf("<td>%s</td>\n",$row['EDYMD']);
		printf("<td>%10.10s</td>\n",$row['SAKHM']);
		printf("<td>%10.10s</td>\n",$row['KOUHM']);
		printf("<td>%s</td>\n",$row['SAGYOID']);
		printf("</tr>\n");
		}
	}
	else
	{
	echo "Connection failed";
	}
$conn = null;

?>

</table>

<?php
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
