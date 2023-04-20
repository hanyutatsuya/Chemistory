<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("機能権限マスタ");
NsfrLogOut("機能権限マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>機能権限マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th nowrap>社員No.</th>
<th nowrap>システムID</th>
<th nowrap>操作レベル</th>
<th nowrap>親展F</th>
<th nowrap>患者名F</th>
<th nowrap>汎用フラグ</th>
<th nowrap>最終ログイン日時</th>
<th nowrap>権限設定F</th>
<th nowrap>履歴区分</th>
<th nowrap>変更区分</th>
<th nowrap>配信済みFLG</th>
<th nowrap>開始年月日</th>
<th nowrap>終了年月日</th>
<th nowrap>登録年月日</th>
<th nowrap>変更年月日</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from m_knkgn order by usrid for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row['USRID']);
		printf("<td nowrap>%s</td>\n",$row['STMID']);
		printf("<td nowrap>%d</td>\n",$row['SUSLBL']);
		printf("<td nowrap>%s</td>\n",$row['STERKGFLG']);
		printf("<td nowrap>%s</td>\n",$row['KNJSSKGFLG']);
		printf("<td nowrap>%s</td>\n",$row['HNYFLG']);
		printf("<td nowrap>%19.19s</td>\n",$row['SSLGINDH']);
		printf("<td nowrap>%s</td>\n",$row['KGSTFLG']);
		printf("<td nowrap>%s</td>\n",$row['RRKKBN']);
		printf("<td nowrap>%s</td>\n",$row['HKKBN']);
		printf("<td nowrap>%s</td>\n",$row['HSSFLG']);
		printf("<td nowrap>%s</td>\n",$row['KISYMD']);
		printf("<td nowrap>%s</td>\n",$row['ENDYMD']);
		printf("<td nowrap>%s</td>\n",$row['TRKYMD']);
		printf("<td nowrap>%s</td>\n",$row['HKYMD']);
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
