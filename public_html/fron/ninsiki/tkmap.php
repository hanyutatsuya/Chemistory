<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("�������̃��b�N�}�b�v");
NsfrLogOut("�������̃��b�N�}�b�v");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�������̃��b�N�}�b�v</h2></center>

<?php
$sdate = $_GET['SDATE'];
$type  = $_GET['TYPE'];
$rack  = $_GET['RACK'];

$conn = Get_DBConn();

if  ($conn)
	{
	printf("<center><h2>�������F%s</h2></center>\n",$sdate);
	printf("<center><h2>���b�N�h�c�F%s</h2></center>\n",$rack);

	if  ($rack != "")
		{
		for ($i=0;$i<50;$i++) {$rackmap[$i][0] = "";$rackmap[$i][1] = "";}
		$sql = "select barcd,ktichkmj,lckpos from nfktbl where sriymd = '$sdate' and lckid = '$rack' for read only";
		foreach ($conn->query($sql) as $row)
			{
			$rackmap[$row[2]-1][0] = $row[0];
			$rackmap[$row[2]-1][1] = $row[1];
			}
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<table align=\"center\" border>\n");

//printf("<tr>\n");
//for ($i=0;$i<10;$i++) {printf("<th>���b�N�h�c</th>\n");}
//printf("</tr>\n");

for ($i=0;$i<10;$i++)
	{
	printf("<tr>\n");
	for ($j=0;$j<5;$j++)
		{
		printf("<td>%02d</td>\n",$j*10+$i+1);
		if  ($rackmap[$i+$j*10][0] == "")
			{
			printf("<td>__________</td>\n");
			printf("<td>___</td>\n");
			}
		else
			{
			printf("<td><A href=tkirai.php?SDATE=%s&TYPE=%d&RACK=%s&BARCD=%s>%s</A></td>\n",
					$sdate,$type,$rack,$rackmap[$i+$j*10][0],barcode_edit($rackmap[$i+$j*10][0]));
			printf("<td><A href=tkirai.php?SDATE=%s&TYPE=%d&RACK=%s&BARCD=%s>%s</A></td>\n",
					$sdate,$type,$rack,$rackmap[$i+$j*10][0],$rackmap[$i+$j*10][1]);
			}
		}
	printf("</tr>\n");
	}

printf("</table>\n");

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=tk1ran.php?SDATE=%s&TYPE=%d>�������̃��b�N�Ɖ�ɖ߂�</A></center>\n",
		$sdate,$type);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=tkhonsu.php?SDATE=%s>�������̖{���Ɖ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
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
