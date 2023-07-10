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
		<th nowarp>ユーザーＩＤ</th>
		<th nowarp>カードＩＤ</th>
		<th nowarp>パスワード</th>
		<th nowarp>ユーザー名</th>
		<th nowarp>旧パスワード</th>
		<th nowarp>パスワード有効期限</th>
		<th nowarp>最終ログイン日時</th>
		<th nowarp>ログイン有効期限</th>
		<th nowarp>SEC</th>
		<th nowarp>使用禁止区分</th>
		<th nowarp>使用禁止日時</th>
		<th nowarp>論理削除F</th>
		<th nowarp>開始年月日</th>
		<th nowarp>終了年月日</th>
		<th nowarp>登録年月日</th>
		<th nowarp>変更年月日</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from usermst order by userid for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['USERID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['CARDID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['PSWD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['USERNM']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['OLDPSWD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['PSWDYKKGN']));
				printf("<td nowarp>%20.20s</td>\n",SjToUtfConv($row['LOGINDH']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['LOGINYKKGN']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SYKISKBN']));
				printf("<td nowarp>%10.10s</td>\n",SjToUtfConv($row['SYKINDH']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['RNRDELFLG']));
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
