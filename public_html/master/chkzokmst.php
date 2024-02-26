<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("属性チェックマスタ");
LaboLogOut("属性チェックマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>属性チェックマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th nowarp>検査G</th>
		<th nowarp>項目CD</th>
		<th nowarp>施設CD</th>
		<th nowarp>身長</th>
		<th nowarp>体重</th>
		<th nowarp>体重区分</th>
		<th nowarp>性別区分</th>
		<th nowarp>年齢</th>
		<th nowarp>年齢区分</th>
		<th nowarp>開始年月日</th>
		<th nowarp>廃止年月日</th>
		<th nowarp>変更担当者ＩＤ</th>
		<th nowarp>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from chkzokmst order by knsgrp,kmkcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SSTCD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SCFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['TJFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['TJTNIFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SBTKBNFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['AGEFLG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['AGEKBNFLG']));
				printf("<td nowarp>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowarp>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowarp>%s</td>\n",$row['HNKTNTID']);
				printf("<td nowarp>%10.10s</td>\n",$row['KSNDH']);
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
