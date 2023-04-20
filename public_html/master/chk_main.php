<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
NsfrHeadOutput("マスターチェック");
NsfrLogOut("マスターチェック");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>マスターチェック</h2></center>

<HR>
<P>
<center><A href=chk_ss.php?WS999=1>仕分け種類チェック</A></center>
</P>
<P>
<center><A href=chk_ssok.php?WS999=1&CKFLG=0>仕分け種類・分注区分整合性</A></center>
</P>

<HR>
<P>
<center><A href=chk_item.php>ＩＴＥＭコードチェック</A></center>
</P>
<P>
<center><A href=chk_itemok.php>ＩＴＥＭコード整合性</A></center>
</P>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
