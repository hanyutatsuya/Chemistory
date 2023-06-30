<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("システム管理マスタ");
LaboLogOut("システム管理マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>システム管理マスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th>フィールド</th>
		<th>内容</th>
	</tr>

<?php

$conn = GetDBConn();

if  ($conn){

try {
	$sql = "select * from sysknrmst fetch first 1 rows only for read only";
	foreach ($conn->query($sql) as $row) {

		printf("<tr>\n");
			printf("<td>ラボコード</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['LBCD']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>サテライトＩＤ</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['SATEID']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>基準処理年月日</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['KJNSRIYMD']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>緊急基準処理年月日</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['KKJNSRIYMD']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>次依頼処理年月日</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['NXIRISRIYMD']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>次認識処理年月日</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['NCNSKSRIYMD']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>次分注処理年月日</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['NXBCHSRIYMD']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>依頼ＥＮＤフラグ</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['IRIENDFLG']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>依頼ＥＮＤ日時</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['IRIENDDH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>認識ＥＮＤフラグ</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['NSKENDFLG']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>認識ＥＮＤ時刻</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['NSKENDDH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤフラグ</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHENDFLG']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－０時刻</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND0DH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－１時刻</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND1DH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－２時刻</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND2DH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－３時刻</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND3DH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－４時刻</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND4DH']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>運用フラグ</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['UNYFLG']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>送信通番</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['SSNTUBN']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>ラボ名称</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['LABONM']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>検査責任者</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['KNSMNGR']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>連絡先</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['TELNO']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ01</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ02</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG02']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ03</td>\n");
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG03']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ04</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG04']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ05</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG05']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ06</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG06']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ07</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG07']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ08</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG08']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ09</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG09']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ10</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG10']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ11</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG11']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ12</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG12']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ13</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG13']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ14</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG14']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ15</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG15']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ16</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG16']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ17</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG17']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ18</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG18']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ19</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG19']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ20</td>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row['SRIKNFLG20']));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>変更担当者ＩＤ</td>\n");
			printf("<td>%s</td>\n",$row['HNKTNTID']);
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>情報更新日時</td>\n");
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
