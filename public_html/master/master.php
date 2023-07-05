<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
LaboHeadOutput("マスター一覧");
LaboLogOut("マスター一覧");
?>

<BODY background="/~kea00sys/img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>マスター一覧</h2></center>

<HR>

<table align = center border=0>
	<tr valign=top>

	<td>
		<table bgcolor = white border>

			<tr>
				<th colspan = 2>共通</th>
			</tr>
			<tr>
				<th>テーブル名</th>
				<th>マスター名称</th>
			</tr>

			<tr>
				<td><A href=kjnmst.php>KJNMST</A></td>
				<td><A href=kjnmst.php>基準値マスタ</A></td>
			</tr>
			<tr>
				<td><A href=cmtmst.php>CMTMST</A></td>
				<td><A href=cmtmst.php>コメントマスタ</A></td>
			</tr>
			<tr>
				<td><A href=kkahskmst.php>KKAHSKMST</A></td>
				<td><A href=kkahskmst.php>結果補足マスタ</A></td>
			</tr>
		</table>
	</td>

	<td>
		<table bgcolor = white border>

			<tr>
				<th colspan = 2>一覧</th>
			</tr>
			<tr>
				<th>テーブル名</th>
				<th>マスター名称</th>
			</tr>

			<tr>
				<td><A href=wskmk.php>WSKMKMST</A></td>
				<td><A href=wskmk.php>WS・項目マスタ</A></td>
			</tr>
			<tr>
				<td><A href=check1ran.php>CHECK</A></td>
				<td><A href=check1ran.php>チェックマスタ一覧</A></td>
			</tr>
		</table>
	</td>

	<td>
		<table bgcolor = white border>

			<tr>
				<th colspan = 2>ローカル</th>
			</tr>
			<tr>
				<th>テーブル名</th>
				<th>マスター名称</th>
			</tr>

			<tr>
				<td><A href=knsgmst1ran.php>KNSGMST</A></td>
				<td><A href=knsgmst1ran.php>検査グループ一覧</A></td>
			</tr>
			<tr>
				<td><A href=knsgmst.php>KNSGMST</A></td>
				<td><A href=knsgmst.php>検査グループマスタ</A></td>
			</tr>
			<tr>
				<td><A href=kmkmst.php>KMKMST</A></td>
				<td><A href=kmkmst.php>項目マスタ</A></td>
			</tr>
			<tr>
				<td><A href=rngchkmst.php>RNGCHKMST</A></td>
				<td><A href=rngchkmst.php>レンジチェックマスタ</A></td>
			</tr>
			<tr>
				<td><A href=calckmkmst.php>CALCKMKMST</A></td>
				<td><A href=calckmkmst.php>計算項目マスタ</A></td>
			</tr>
			<tr>
				<td><A href=kkafltmst.php>KKAFLTMST</A></td>
				<td><A href=kkafltmst.php>結果フィルタマスタ</A></td>
			</tr>
			<tr>
				<td><A href=krkmkmst.php>KRKMKMST</A></td>
				<td><A href=krkmkmst.php>関連項目マスタ</A></td>
			</tr>
			<tr>
				<td><A href=skchkmst.php>SKCHKMST</A></td>
				<td><A href=skchkmst.php>相関項目マスタ</A></td>
			</tr>
			<tr>
				<td><A href=rrkchkmst.php>RRKCHKMST</A></td>
				<td><A href=rrkchkmst.php>履歴チェックマスタ</A></td>
			</tr>
			<tr>
				<td><A href=kskbrmst.php>KSKBRMST</A></td>
				<td><A href=kskbrmst.php>希釈倍率マスタ</A></td>
			</tr>
			<tr>
				<td><A href=jdkmkmst.php>JDKMKMST</A></td>
				<td><A href=jdkmkmst.php>自動発生項目マスタ</A></td>
			</tr>
			<tr>
				<td><A href=memst.php>MEMST</A></td>
				<td><A href=memst.php>分析機マスタ</A></td>
			</tr>
			<tr>
				<td><A href=mechmst.php>MECHMST</A></td>
				<td><A href=mechmst.php>分析機チャネルマスタ</A></td>
			</tr>
			<tr>
				<td><A href=zslinemst.php>ZSLINEMST</A></td>
				<td><A href=zslinemst.php>ZSライン制御マスタ</A></td>
			</tr>

		</table>
	</td>

	<td>
		<table bgcolor = white border>

			<tr>
				<th colspan = 2>システム使用</th>
			</tr>
			<tr>
				<th>テーブル名</th>
				<th>マスター名称</th>
			</tr>

			<tr>
				<td><A href=sysknrmst.php>SYSKNRMST</A></td>
				<td><A href=sysknrmst.php>システム管理マスタ</A></td>
			</tr>
			<tr>
				<td><A href=usermst.php>USERMST</A></td>
				<td><A href=usermst.php>ユーザーマスタ</A></td>
			</tr>
			<tr>
				<td><A href=knokgnmst.php>KNOKGNMST</A></td>
				<td><A href=knokgnmst.php>機能権限マスタ</A></td>
			</tr>

		</table>
	</td>

</table>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
