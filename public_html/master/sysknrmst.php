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
		<th nowarp>フィールド</th>
		<th nowarp>内容</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from sysknrmst fetch first 1 rows only for read only";
		foreach ($conn->query($sql) as $row) {
	
			printf("<tr>\n");
				printf("<td nowarp>ラボCD</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['LBCD']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>サテライトＩＤ</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SATEID']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>基準処理年月日</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KJNSRIYMD']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>緊急基準処理年月日</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KKJNSRIYMD']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>次依頼処理年月日</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['NXIRISRIYMD']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>次認識処理年月日</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['NCNSKSRIYMD']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>次分注処理年月日</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['NXBCHSRIYMD']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>依頼ＥＮＤF</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['IRIENDFLG']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>依頼ＥＮＤ日時</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['IRIENDDH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>認識ＥＮＤF</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['NSKENDFLG']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>認識ＥＮＤ時刻</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['NSKENDDH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>分注ＥＮＤF</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BCHENDFLG']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>分注ＥＮＤ－０時刻</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BCHEND0DH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>分注ＥＮＤ－１時刻</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BCHEND1DH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>分注ＥＮＤ－２時刻</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BCHEND2DH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>分注ＥＮＤ－３時刻</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BCHEND3DH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>分注ＥＮＤ－４時刻</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BCHEND4DH']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>運用F</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['UNYFLG']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>送信通番</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SSNTUBN']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>ラボ名称</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['LABONM']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>検査責任者</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSMNGR']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>連絡先</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['TELNO']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F01</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG01']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F02</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG02']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F03</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG03']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F04</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG04']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F05</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG05']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F06</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG06']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F07</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG07']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F08</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG08']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F09</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG09']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F10</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG10']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F11</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG11']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F12</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG12']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F13</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG13']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F14</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG14']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F15</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG15']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F16</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG16']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F17</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG17']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F18</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG18']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F19</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG19']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>処理確認F20</td>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SRIKNFLG20']));
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>変更担当者ＩＤ</td>\n");
				printf("<td nowarp>%s</td>\n",$row['HNKTNTID']);
			printf("</tr>\n");
	
			printf("<tr>\n");
				printf("<td nowarp>情報更新日時</td>\n");
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
