<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("マスター一覧");
NsfrLogOut("マスター一覧");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>マスター一覧</h2></center>


<table align = center border=0>
<tr valign=top>

<td>
<table bgcolor = white border>

<tr>
<th colspan = 2>基幹</th>
</tr>
<tr>
<th>テーブル名</th>
<th>マスター名称</th>
</tr>

<tr>
<td><A href=smpmst.php>NFSMPMST</A></td>
<td><A href=smpmst.php>サンプリングマスタ</A></td>
</tr>

<tr>
<td><A href=kmkmst.php>NFKMKMST</A></td>
<td><A href=kmkmst.php>項目マスタ</A></td>
</tr>

<tr>
<td><A href=smpkm.php>SMP-KMK</A></td>
<td><A href=smpkm.php>ＷＳ・項目マスタ</A></td>
</tr>

<tr>
<td><A href=chkmst.php>NFCHKMST</A></td>
<td><A href=chkmst.php>長期保管区分マスタ</A></td>
</tr>

<tr>
<td><A href=egsmst.php>NFEGSMST</A></td>
<td><A href=egsmst.php>営業所マスタ</A></td>
</tr>

<tr>
<td><A href=cmtmst.php>NFCMTMST</A></td>
<td><A href=cmtmst.php>検体コメントマスタ</A></td>
</tr>

</table>
</td>



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
<td><A href=setup.php>NSETUPTBL</A></td>
<td><A href=setup.php>システム設定情報</A></td>
</tr>

<tr>
<td><A href=ssmst.php>NFSSMST</A></td>
<td><A href=ssmst.php>仕分け種類マスタ</A></td>
</tr>

<tr>
<td><A href=srimst.php>NFSRIMST</A></td>
<td><A href=srimst.php>検査種類マスタ</A></td>
</tr>

<tr>
<td><A href=jyomst.php>NFJYOMST</A></td>
<td><A href=jyomst.php>状態マスタ</A></td>
</tr>

<tr>
<td><A href=bmrmst.php>NFBMRMST</A></td>
<td><A href=bmrmst.php>分類マスタ</A></td>
</tr>

<tr>
<td><A href=yokmst.php>NFYOKMST</A></td>
<td><A href=yokmst.php>容器マスタ</A></td>
</tr>

<tr>
<td><A href=strmst.php>NFSTRMST</A></td>
<td><A href=strmst.php>サテライトマスタ</A></td>
</tr>

<tr>
<td><A href=sismst.php>NFSISMST</A></td>
<td><A href=sismst.php>施設マスタ</A></td>
</tr>

<tr>
<td><A href=sotmst.php>NFSOTMST</A></td>
<td><A href=sotmst.php>装置管理マスタ</A></td>
</tr>

<tr>
<td><A href=musr.php>M_USR</A></td>
<td><A href=musr.php>ユーザー管理マスタ</A></td>
</tr>

<tr>
<td><A href=mknkgn.php>M_KNKGN</A></td>
<td><A href=mknkgn.php>機能権限マスタ</A></td>
</tr>

</table>
</td>

<td>
<table bgcolor = white border>

<tr>
<th colspan = 2>認識システム用</th>
</tr>
<tr>
<th>テーブル名</th>
<th>マスター名称</th>
</tr>

</table>
</td>


<td>
<table bgcolor = white border>

<tr>
<th colspan = 2>フロンティア用</th>
</tr>
<tr>
<th>テーブル名</th>
<th>マスター名称</th>
</tr>

<tr>
<td><A href=cjmst.php>FCJMST</A></td>
<td><A href=cjmst.php>セル情報マスタ</A></td>
</tr>

<tr>
<td><A href=mjmst.php>FMJMST</A></td>
<td><A href=mjmst.php>モジュール情報マスタ</A></td>
</tr>

<tr>
<td><A href=itmcmst.php>FITMCMST</A></td>
<td><A href=itmcmst.php>ＩＴＥＭコードマスタ</A></td>
</tr>

<tr>
<td><A href=ngsmst.php>FNGSMST</A></td>
<td><A href=ngsmst.php>分注ＮＧ処理マスタ</A></td>
</tr>

<tr>
<td><A href=zpatarn.php>FSIPTMST</A></td>
<td><A href=zpatarn.php>パキパキパターンマスタ</A></td>
</tr>

</table>
</td>

</table>


<HR>
<P>
<center><A href=bunmst.php>分注機マスター設定</A></center>
</P>
<HR>
<P>
<center><A href=chk_main.php>マスターチェック</A></center>
</P>
<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
