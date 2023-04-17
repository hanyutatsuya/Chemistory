<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");

NsfrHeadOutput("メンテナンス処理一覧");
NsfrLogOut("メンテナンス処理一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>メンテナンス処理一覧</h2></center>

<?php
//$usrname = trim($_POST['UNAME']);
$shoribi = trim($_POST['sriymd']);

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
<FORM ACTION="maint.php" METHOD="POST">
処理日変更
<INPUT TYPE=text NAME="sriymd" SIZE=10 MAXLENGTH=8>
<BUTTON name="submit" value="submit" type="submit">変更
</BUTTON>

</FORM>
</center>
</P>

<?php

//	printf("<center><P>担当者：%s</P></center>\n",$usrname);
	printf("<HR>\n");

	printf("<center><P>複雑系受付対応</P></center>\n");
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>複雑系受付対応処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fukusu.php?SDATE=%s>複数検体登録処理</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tkhimo.php?SDATE=%s>凍結検体紐付け処理</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>認識装置ダウン時対応</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>認識装置ダウン処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tkbardel.php?SDATE=%s>ラック・バーコード情報削除（５０本ラック）</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tjbardel.php?SDATE=%s>ラック・バーコード情報削除（１０本ラック）</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mrack.php?SDATE=%s>未完了ラックチェック</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=krackend.php?SDATE=%s>ラック完了強制登録</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");


	printf("<center><P>分注機ダウン時対応</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>分注機ダウン処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=rackanryo.php?SDATE=%s>ラック完了強制登録</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=traykanryo.php?SDATE=%s>トレー完了強制登録</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>メンテナンス処理</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>メンテナンス処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=pakisai.php?SDATE=%s>仕分けラベル再出力</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=zpatmnt.php?SDATE=%s>仕分けラベルＺパターンメンテナンス</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>患者名チェックリスト処理</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>保守処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kjchk.php>検体ナンバー範囲設定</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>報告区分保守処理</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>保守処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=eigyo.php?SDATE=%s>営業所区分変更</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=eigyoadd.php?SDATE=%s>営業所区分追加</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=shuken.php?SDATE=%s>集検万台保守</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
