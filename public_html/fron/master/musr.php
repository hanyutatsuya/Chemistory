<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("ユーザー管理マスタ");
NsfrLogOut("ユーザー管理マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>ユーザー管理マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th nowrap>社員No.</th>
<th nowrap>カードID</th>
<th nowrap>パスワード</th>
<th nowrap>ユーザー名</th>
<th nowrap>旧PW1</th>
<th nowrap>旧PW2</th>
<th nowrap>PW有効期限</th>
<th nowrap>最終ログイン日時</th>
<th nowrap>ログイン有効期限</th>
<th nowrap>使用禁止区分</th>
<th nowrap>職種CD</th>
<th nowrap>センターCD</th>
<th nowrap>営業所CD</th>
<th nowrap>ラボCD</th>
<th nowrap>SECCD</th>
<th nowrap>使用禁止日時</th>
<th nowrap>履歴区分</th>
<th nowrap>変更区分</th>
<th nowrap>配信済みFLG</th>
<th nowrap>開始年月日</th>
<th nowrap>終了年月日</th>
<th nowrap>登録年月日</th>
<th nowrap>変更年月日</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from m_usr order by usrid for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row['USRID']);
		printf("<td nowrap>%s</td>\n",$row['CDID']);
		printf("<td nowrap>********</td>\n");
		printf("<td nowrap>%s</td>\n",$row['USRNM']);
		printf("<td nowrap>********</td>\n");
		printf("<td nowrap>********</td>\n");
		printf("<td nowrap>%s</td>\n",$row['PWYKKGN']);
		printf("<td nowrap>%19.19s</td>\n",$row['SSLGINDH']);
		printf("<td nowrap>%s</td>\n",$row['LGINYKKGN']);
		printf("<td nowrap>%s</td>\n",$row['SYKNSKBN']);
		printf("<td nowrap>%s</td>\n",$row['SKSCD']);
		printf("<td nowrap>%s</td>\n",$row['CTCD']);
		printf("<td nowrap>%s</td>\n",$row['EGSCD']);
		printf("<td nowrap>%s</td>\n",$row['LBCD']);
		printf("<td nowrap>%s</td>\n",$row['SECCD']);
		printf("<td nowrap>%10.10s</td>\n",$row['SYKNSDH']);
		printf("<td nowrap>%s</td>\n",$row['RRKKBN']);
		printf("<td nowrap>%s</td>\n",$row['HKKBN']);
		printf("<td nowrap>%s</td>\n",$row['HSSFLG']);
		printf("<td nowrap>%s</td>\n",$row['KISYMD']);
		printf("<td nowrap>%s</td>\n",$row['ENDYMD']);
		printf("<td nowrap>%s</td>\n",$row['TRKYMD']);
		printf("<td nowrap>%s</td>\n",$row['HKYMD']);
		printf("</tr>\n");
		}
	}
	else
	{
	echo "Connection failed";
	}
$conn = null;

?>

</table>

<?php
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
