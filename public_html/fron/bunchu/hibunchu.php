<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("�񕪒����ʑ��M����",60);
NsfrLogOut("�񕪒����ʑ��M����");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�񕪒����ʑ��M����</h2></center>

<?php
$sdate = $_REQUEST[SDATE];
$send1 = $_REQUEST[SEND1];
$send2 = $_REQUEST[SEND2];
$start = $_REQUEST[START];

printf("<h2>\n");
printf("<center>�������F%s</center>\n",$sdate);
printf("</h2>\n");


$conn = Get_DBConn();
if  ($conn)
	{
	$updflg = 0;
	if  (!empty($send1))
		{
		$sql = "";
		$sql = $sql . "update nsetuptbl set setkbnnm = '1',kouhm = current timestamp ";
		$sql = $sql . "where setkbn = '38' and kmkkbn = '04' and setkbnnm = '0' " ;
		$conn->beginTransaction();
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == TRUE)
			{
			$conn->commit();
			printf("<center><P><FONT color=red>�񕪒����ʑ��M�w�������܂����B</FONT></P></center>\n");
			NsfrLogOut(sprintf("�񕪒����ʑ��M�w��"));
			}
		else
			{
			printf("<center><P><FONT color=red>�񕪒����ʑ��M�w�������s���܂����B</FONT></P></center>\n");
			NsfrLogOut(sprintf("�񕪒����ʑ��M�w�����s"));
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			}
		}

	if  (!empty($send2))
		{
		$sql = "";
		$sql = $sql . "update nsetuptbl set setkbnnm = '$start',kouhm = current timestamp ";
		$sql = $sql . "where setkbn = '38' and kmkkbn = '03' " ;
		$conn->beginTransaction();
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == TRUE)
			{
			$conn->commit();
			printf("<center><P><FONT color=red>�������M�J�n������ύX���܂����B</FONT></P></center>\n");
			NsfrLogOut(sprintf("�������M�J�n�����ύX"));
			}
		else
			{
			printf("<center><P><FONT color=red>�������M�J�n�����ύX�����s���܂����B</FONT></P></center>\n");
			NsfrLogOut(sprintf("�������M�J�n�����ύX���s"));
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			}
		}

	if  (empty($send1) && empty($send2))
		{
		printf("<center><P>�@</P></center>\n");
		}

	$sql = "select * from nsetuptbl where setkbn = '38' order by setkbn,kmkkbn for read only";
	$i=0;
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$setup[$i] = $row[2];
		$i++;
		}

	}
else
	{
	echo "Connection failed";
	}
$conn = null;

$SetHH = (int)substr($setup[3],0,2);
$SetMM = (int)substr($setup[3],2,4);
$CurHH = (int)date("H");
$CurMM = (int)date("i");

if ($SetHH < 12)
	$SetHH = $SetHH + 24;
if ($CurHH < 12)
	$CurHH = $CurHH + 24;


printf("<FORM ACTION=\"hibunchu.php?SDATE=%s\" METHOD=\"POST\">\n",$sdate);
//printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
if ($SetHH > $CurHH || ($SetHH == $CurHH && $SetMM > $CurMM))
	{
	printf("<DIV><BIG>\n");
	printf("<center>\n");
	printf("<INPUT type=submit name=SEND1 value=\" �񕪒����ʑ��M \">\n");
	printf("</center>\n");
	printf("</BIG></DIV>\n");
	}

printf("<BR>\n");

printf("<DIV align=right>\n");
printf("�������M����\n");
printf("<INPUT TYPE=text NAME=START SIZE=6 MAXLENGTH=4 value=%s>\n",$setup[3]);

if ($SetHH > $CurHH || ($SetHH == $CurHH && $SetMM > $CurMM))
	{
	printf("<INPUT type=submit name=SEND2 value=\"�ρ@�X\">\n");
	}
printf("</DIV>\n");

printf("</FORM>\n");

if (count($setup) > 5)
	{
	printf("<table align=center bgcolor=white border>\n");
	printf("<tr>\n");
	printf("<th>���M��������</th>\n");
	printf("</tr>\n");

	for ($i=5;$i<count($setup);$i++)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$setup[$i]);
		printf("</tr>\n");
		}
	printf("</table>\n");
	}

?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>�t�����e�B�A�V�X�e���V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
