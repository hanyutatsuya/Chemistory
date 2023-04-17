<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�������`�F�b�N");
NsfrLogOut("�������`�F�b�N");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�������`�F�b�N</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$uke  = uketori_check($conn,$sdate);
	$isai = isai_check($conn,$sdate);
	$lbl  = label_check($conn,$sdate);
	$paki = pakipaki_check($conn,$sdate);
	$kan  = kanban_check($conn,$sdate);
	$hiki = hikiwatasi_check($conn,$sdate);

	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>���@���@��</th>\n");
	printf("<th>����</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	if ($uke == 0)
		printf("<td bgcolor=skyblue>���󂯎��g���[</td>\n");
	else
		printf("<td bgcolor=pink><A href=uketray.php?SDATE=%s>���󂯎��g���[</A></td>\n",$sdate);
	if ($uke == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($uke));
	else
		printf("<td bgcolor=pink align=right><A href=uketray.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($uke));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($isai == 0)
		printf("<td bgcolor=skyblue>�ڍږ��������b�N</td>\n");
	else
		printf("<td bgcolor=pink><A href=miisairack.php?SDATE=%s>�ڍږ��������b�N</A></td>\n",$sdate);
	if ($isai == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($isai));
	else
		printf("<td bgcolor=pink align=right><A href=miisairack.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($isai));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($lbl == 0)
		printf("<td bgcolor=skyblue>�����C�g���o��</td>\n");
	else
		printf("<td bgcolor=pink><A href=milabelrack.php?SDATE=%s>�����C�g���o��</A></td>\n",$sdate);
	if ($lbl == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($lbl));
	else
		printf("<td bgcolor=pink align=right><A href=milabelrack.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($lbl));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($paki == 0)
		printf("<td bgcolor=skyblue>�p�L�p�L���o��</td>\n");
	else
		printf("<td bgcolor=pink><A href=mipakirack.php?SDATE=%s>�p�L�p�L���o��</A></td>\n",$sdate);
	if ($paki == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($paki));
	else
		printf("<td bgcolor=pink align=right><A href=mipakirack.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($paki));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($kan == 0)
		printf("<td bgcolor=skyblue>�Ŕ��ݒ胉�b�N</td>\n");
	else
		printf("<td bgcolor=pink><A href=kanrack.php?SDATE=%s>�Ŕ��ݒ胉�b�N</A></td>\n",$sdate);
	if ($kan == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($kan));
	else
		printf("<td bgcolor=pink align=right><A href=kanrack.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($kan));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($hiki == 0)
		printf("<td bgcolor=skyblue>�������n�����b�N</td>\n");
	else
		printf("<td bgcolor=pink><A href=hikitray.php?SDATE=%s>�������n�����b�N</A></td>\n",$sdate);
	if ($hiki == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($hiki));
	else
		printf("<td bgcolor=pink align=right><A href=hikitray.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($hiki));
	printf("</tr>\n");

	printf("</table>\n");

	}
else
	{
	printf("Connection failed");
	}
$conn = null;
?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>�t�����e�B�A�V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>

<?php
function uketori_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct h.trayid) from nknthktbl h ";
	$sql = $sql . "where h.sriymd = '$sdate' ";
	$sql = $sql . "and char(h.trayid,4) != 'VVVV' ";
	$sql = $sql . "and not exists ";
	$sql = $sql . "(select * from fkntuktbl b where b.sriymd = h.sriymd and b.trayid = h.trayid) ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function isai_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct b.aslckid) ";
	$sql = $sql . "from fbncjtbl b,firkkmst i,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.smpcd = ws.smpcd ";
	$sql = $sql . "and ws.itmcd = i.itmcd ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "and b.isiflg = '0' ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function label_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct aslckid) from fbncjtbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and char(aslckid,1) in ('A','B') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function pakipaki_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct b.aslckid) ";
	$sql = $sql . "from fpkptbl pk,fbncjtbl b ";
	$sql = $sql . "where pk.sriymd = '$sdate' ";
	$sql = $sql . "and pk.outflg = '0' ";
	$sql = $sql . "and b.sriymd = pk.sriymd ";
	$sql = $sql . "and b.barcd  = pk.barcd ";
	$sql = $sql . "and b.kntkbn = pk.kntkbn ";
	$sql = $sql . "and b.smpcd  = pk.smpcd ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function kanban_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct lckid) from fbncmktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and knbnid = ' ' ";
	$sql = $sql . "and bcngcd != '6' ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function hikiwatasi_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct b.aslckid) ";
	$sql = $sql . "from fbncjtbl b,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.aslckid != ' ' ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "and b.hkwzflg = '0' ";
	$sql = $sql . "and ws.smpcd = b.smpcd ";
	$sql = $sql . "and char(ws.itmcd,1) not in ('6','7') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

?>

