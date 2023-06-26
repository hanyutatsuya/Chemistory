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
			printf("<td>ラボコード</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['LBCD'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>サテライトＩＤ</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SATEID'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>基準処理年月日</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['KJNSRIYMD'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>緊急基準処理年月日</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['KKJNSRIYMD'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>次依頼処理年月日</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['NXIRISRIYMD'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>次認識処理年月日</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['NCNSKSRIYMD'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>次分注処理年月日</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['NXBCHSRIYMD'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>依頼ＥＮＤフラグ</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['IRIENDFLG'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>依頼ＥＮＤ日時</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['IRIENDDH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>認識ＥＮＤフラグ</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['NSKENDFLG'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>認識ＥＮＤ時刻</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['NSKENDDH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤフラグ</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHENDFLG'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－０時刻</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND0DH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－１時刻</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND1DH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－２時刻</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND2DH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－３時刻</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND3DH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>分注ＥＮＤ－４時刻</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['BCHEND4DH'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>運用フラグ</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['UNYFLG'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>送信通番</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SSNTUBN'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>ラボ名称</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['LABONM'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>検査責任者</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['KNSMNGR'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>連絡先</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['TELNO'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ01</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ02</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ03</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ04</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ05</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ06</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ07</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ08</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ09</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ10</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ11</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ12</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ13</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ14</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ15</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ16</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ17</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ18</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ19</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>処理確認フラグ20</td>
			printf("<td>%s</td>\n",mb_convert_encoding($row['SRIKNFLG01'],"UTF-8","SJIS-WIN"));
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>変更担当者ＩＤ</td>
			printf("<td>%s</td>\n",$row['HNKTNTID']);
		printf("</tr>\n");

		printf("<tr>\n");
			printf("<td>情報更新日時</td>
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
