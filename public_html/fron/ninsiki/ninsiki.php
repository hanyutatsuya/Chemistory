<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
?>

<?php
NsfrHeadOutput("検体認識システム照会処理一覧");
?>

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("検体認識システム照会処理一覧");
NsfrLogOut("検体認識システム照会処理一覧");

?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>検体認識システム照会処理一覧</h2></center>

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
<FORM ACTION="ninsiki.php" METHOD="POST">
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
	printf("<td bgcolor=yellow><A href=irikensu.php?SDATE=%s>依頼件数照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=ninkensu.php?SDATE=%s>認識済件数照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tkhonsu.php?SDATE=%s>凍結検体本数照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hikiwatasi.php?SDATE=%s>未引き渡しトレーチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=futeki.php?SDATE=%s>不適合登録もれ検体チェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mrack.php?SDATE=%s>未完了ラックチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=krackmap.php?SDATE=%s>ラックマップ照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kanjachk.php?SDATE=%s>患者名チェックリスト出力確認</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=ninkentai.php?SDATE=%s>検体情報照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fusoku.php?SDATE=%s>不足検体照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=chichaku.php?SDATE=%s>遅着検体照会</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=gunma.php?SDATE=%s>群馬臨床バーコード情報作成処理</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=aboend.php?SDATE=%s>血型・エンドトキシン検体リスト出力処理</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");
?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
