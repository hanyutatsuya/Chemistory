<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");

$title = "�v�������O�t�@�C���ꗗ";
NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$dir = opendir ("/home/data/log");
rewinddir($dir);
$i = 0;
while($fname = readdir($dir))
	{
	if  (strncmp($fname,"php_log",7) == 0)
		{
		$logname[$i] = $fname;
		$i++;
		}
	}
sort($logname,SORT_STRING);

printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th>�t�@�C����</th>\n");
printf("<th>�X�V����</th>\n");
printf("</tr>\n");

for ($i=0;$i<count($logname);$i++)
	{
	printf("<tr>\n");
	printf("<td><A href=weblog1.php?FNAME=%s>%s</A></td>\n",$logname[$i],$logname[$i]);
	$logpath = "/home/data/log/" . $logname[$i];
	printf("<td><A href=weblog1.php?FNAME=%s>%s</A></td>\n",$logname[$i],date("Y/m/d H:i:s",filectime($logpath)));
	printf("</tr>\n");
	}

printf("</table>\n");

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=merits.php>�����b�c�����ꗗ�ɖ߂�</A></center>\n");
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>


