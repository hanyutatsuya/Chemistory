<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("�x�����̏Ɖ�");
NsfrLogOut("�x�����̏Ɖ�");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�x�����̏Ɖ�</h2></center>

<?php
$sdate = $_REQUEST[SDATE];
$send1 = $_REQUEST['SEND1'];

$updflg = 0;
if  (!empty($send1))
	{
	$msg = "�x���o�^���̈ꗗ���X�g";
	$app = "/home/nsfr/bin/lst_chichaku.php $sdate";
	$updflg = 1;
	}

if ($updflg != 0)
	{
	$sret = shell_exec($app);
	printf("<P><center>\n");
	printf("%s���o�͂��܂����B\n",$msg);
	printf("</center></P>\n");
	printf("<HR>\n");
	}

printf("<h2>\n");
printf("<center>�������F%s</center>\n",$sdate);
printf("<DIV align=right>\n");
printf("<FORM ACTION=\"chichaku.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<BUTTON type=submit name=SEND1 value=\"submit\">��@��\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</DIV>\n");
printf("</h2>\n");

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");
	printf("<tr>\n");
	printf("<th>������</th>\n");
	printf("<th>���̔ԍ�</th>\n");
	printf("<th>�R�����g</th>\n");
	printf("<th>�ۊǏꏊ</th>\n");
	printf("</tr>\n");

	$del = array(",","�A","�","�C","�@"," ",";",":","/");

	$sql = "select distinct sriymd,char(kntno,9),freecmt  from nccktbl where sriymd = '$sdate' order by char(kntno,9) for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row[0]);
		printf("<td>%s</td>\n",ino_edit($row[1]));

		$len = mb_strlen($row[2]);
		$idx = 0;
		$pos = 0;
		for ($i=0;$i<count($del);$i++)
			{
			$pos = mb_strpos($row[2],$del[$i]);
			if ($pos != 0)
				{
				$idx = $i;
				break;
				}
			}
		if ($pos > 0)
			{
			$str1 = mb_substr($row[2],0,$pos);
			$str2 = mb_substr($row[2],$pos+1,$len-$pos-1);
			}
		else
			{
			$str1 = $row[2];
			$str2 = "";
			}
		printf("<td>%s</td>\n",$str1);
		printf("<td>%s</td>\n",$str2);
		printf("</tr>\n");
		}
	printf("</table>\n");

	}
else
	{
	echo "Connection failed";
	}
$conn = null;
?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>���̔F���V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
