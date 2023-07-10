<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("機能権限マスタ");
LaboLogOut("機能権限マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>機能権限マスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th nowarp>ユーザーＩＤ</th>
		<th nowarp>システムＩＤ</th>
		<th nowarp>照会権限F</th>
		<th nowarp>入力権限F</th>
		<th nowarp>修正権限F</th>
		<th nowarp>親展閲覧権限F</th>
		<th nowarp>患者名参照権限F</th>
		<th nowarp>汎用F</th>
		<th nowarp>開始年月日</th>
		<th nowarp>終了年月日</th>
		<th nowarp>登録年月日</th>
		<th nowarp>変更年月日</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from knokgnmst order by userid for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['USERID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SYSTEMID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SYKIOKFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['NRYKOKFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SYSIOKFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SNTNOKFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNJAOKFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['GENERALFLG']));
				printf("<td nowarp>%10.10s</td>\n",SjToUtfConv($row['STAYMD']));
				printf("<td nowarp>%10.10s</td>\n",SjToUtfConv($row['ENDYMD']));
				printf("<td nowarp>%10.10s</td>\n",SjToUtfConv($row['TRKYMD']));
				printf("<td nowarp>%10.10s</td>\n",SjToUtfConv($row['HNKYMD']));
			printf("</tr>\n");
		}
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}

} else {
	echo "Connection failed";
}

$conn = null;

?>

</table>

<HR>
<P>
<center><A href=../master/master.php>マスター一覧に戻る</A></center>
</P>

<HR>
</BODY>
</HTML>
