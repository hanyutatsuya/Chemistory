<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("コメントマスタ");
LaboLogOut("コメントマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>コメントマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th>コメントコード</th>
		<th>コメント記号</th>
		<th>コメント名カナ</th>
		<th>コメント名漢字</th>
		<th>検査結果１</th>
		<th>検査結果補足</th>
		<th>赤伝フラグ</th>
		<th>異常値マーク</th>
		<th>開始年月日</th>
		<th>廃止年月日</th>
		<th>変更担当者ＩＤ</th>
		<th>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if  ($conn){

try {
	$sql = "select * from cmtmst order by cmcd for read only";
	foreach ($conn->query($sql) as $row) {
		printf("<tr>\n");
			printf("<td>%s</td>\n",$row['CMCD']);
			printf("<td>%s</td>\n",mb_convert_encoding($row['CMTKG'],"UTF-8","SJIS-WIN"));
			printf("<td>%s</td>\n",mb_convert_encoding($row['CMTNM'],"UTF-8","SJIS-WIN"));
			printf("<td>%s</td>\n",mb_convert_encoding($row['CMTNMJ'],"UTF-8","SJIS-WIN"));
			printf("<td>%s</td>\n",$row['KNSKKA1']);
			printf("<td>%s</td>\n",$row['KKAHSKCD']);
			printf("<td>%s</td>\n",$row['AKADEN']);
			printf("<td>%s</td>\n",$row['IJOUCHI']);
			printf("<td>%10.10s</td>\n",$row['KAIYMD']);
			printf("<td>%10.10s</td>\n",$row['HAIYMD']);
			printf("<td>%s</td>\n",$row['HNKTNTID']);
			printf("<td>%20.20s</td>\n",$row['KSNDH']);
		printf("</tr>\n");
	}
}
	catch (Exception $ex) {
		LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
		LaboLogOut(sprintf("ERRCODE [%s]",$ex->getCode()));
		printf("ERRMSG  [%s]<BR>",$ex->getMessage());
		printf("ERRCODE [%s]<BR>",$ex->getCode());
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
