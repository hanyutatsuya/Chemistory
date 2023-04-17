<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("フロンティアシステム照会処理一覧");
NsfrLogOut("フロンティアシステム照会処理一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>フロンティアシステム照会処理一覧</h2></center>

<?php
$shoribi = trim($_REQUEST['SDATE']);

if  (!is_numeric($shoribi) || strlen($shoribi) == 0)
	{
	$conn = Get_DBConn();
	$sdate = Get_Shoribi($conn);

	$conn = null;
	}
else
	{
	$sdate = $shoribi;
	}

printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

?>

<P>
<center>
<FORM ACTION="bunchu.php" METHOD="POST">
処理日変更
<INPUT TYPE=text NAME="SDATE" SIZE=10 MAXLENGTH=8>
<BUTTON name="submit" value="submit" type="submit">変更
</BUTTON>
</FORM>
</center>
</P>

<?php
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>照会処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mishori.php?SDATE=%s>未処理チェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=uketori.php?SDATE=%s>未受け取りトレーチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hibunchu.php?SDATE=%s>非分注結果送信処理</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=white><A href=ngshori.php?SDATE=%s>ＮＧ復旧処理検体照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=miisai.php?SDATE=%s>移載未処理ラックチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=milabel.php?SDATE=%s>リライトラベル未出力チェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mipaki.php?SDATE=%s>パキパキラベル未出力チェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=white><A href=pakishokai.php?SDATE=%s>パキパキ仕分け検体照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=yellow><A href=pakishokai2.php?SDATE=%s>パキパキ仕分け検体照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=rfid1ran.php?SDATE=%s>パキパキ→ＲＦＩＤ照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fkanjachk.php?SDATE=%s>患者名チェックリスト出力確認</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fsend.php?SDATE=%s>ファイル送信処理</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kanban.php?SDATE=%s>看板ID未設定ラックチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hikiwatasi.php?SDATE=%s>未引き渡しラックチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");
?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
