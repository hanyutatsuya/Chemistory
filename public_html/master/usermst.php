<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("ユーザーマスタ");
LaboLogOut("ユーザーマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>ユーザーマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th>ユーザーＩＤ</th>
		<th>カードＩＤ</th>
		<th>パスワード</th>
		<th>ユーザー名</th>
		<th>旧パスワード</th>
		<th>パスワード有効期限</th>
		<th>最終ログイン日時</th>
		<th>ログイン有効期限</th>
		<th>セクション</th>
		<th>使用禁止区分</th>
		<th>使用禁止日時</th>
		<th>論理削除フラグ</th>
		<th>開始年月日</th>
		<th>終了年月日</th>
		<th>登録年月日</th>
		<th>変更年月日</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from usermst order by userid for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",SjToUtfConv($row['USERID']));
				printf("<td>%s</td>\n",SjToUtfConv($row['CARDID']));
				printf("<td>%s</td>\n",SjToUtfConv($row['PSWD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['USERNM']));
				printf("<td>%s</td>\n",SjToUtfConv($row['OLDPSWD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['PSWDYKKGN']));
				printf("<td>%20.20s</td>\n",SjToUtfConv($row['LOGINDH']));
				printf("<td>%s</td>\n",SjToUtfConv($row['LOGINYKKGN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SYKISKBN']));
				printf("<td>%10.10s</td>\n",SjToUtfConv($row['SYKINDH']));
				printf("<td>%s</td>\n",SjToUtfConv($row['RNRDELFLG']));
				printf("<td>%10.10s</td>\n",SjToUtfConv($row['STAYMD']));
				printf("<td>%10.10s</td>\n",SjToUtfConv($row['ENDYMD']));
				printf("<td>%10.10s</td>\n",SjToUtfConv($row['TRKYMD']));
				printf("<td>%10.10s</td>\n",SjToUtfConv($row['HNKYMD']));
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
