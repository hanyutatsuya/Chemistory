<?php
//==============================================================================
// Name     :    pakishokai2.php
// Function :    �p�L�p�L���Ɖ��(�W�v�L���)
// Return   :    ����
// Remark   :    �����T�v
//               �p�L�p�L�̎d���������W�v���ƍ��킹�ĕ\������
//---History--------------------------------------------------------------------
// Ver.  Date        Name                  Note
//------+-----------+---------------------+-------------------------------------
// 1.00  2008.08.16  hanyu@bml.co.jp       �V�K�쐬
// 1.01  2009.03.18  k-yokota@bml.co.jp    �Ǘ���200946 ���̃o�[�R�[�h�o�͋@�\�ǉ�
//==============================================================================
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("�p�L�p�L���Ɖ�");
NsfrLogOut("�p�L�p�L���Ɖ�");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�p�L�p�L���Ɖ�</h2></center>

<?php
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� mod start ----->  
$sdate = trim($_REQUEST['SDATE']);
$item = trim($_REQUEST['ITEM']);
$saki = mb_convert_kana(trim($_REQUEST['SAKI']),"k");
$fsend = $_REQUEST['FSEND'];
//$sdate = trim($_GET['SDATE']);
//$item = trim($_GET['ITEM']);
//$saki = trim($_GET['SAKI']);
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� mod end <-----  

printf("<center><P>�������F%s</P></center>\n",$sdate);

//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� add start ----->  
if  ($saki != "")
	{
	printf("<FORM ACTION=\"pakishokai2.php\" METHOD=\"POST\">\n");
	printf("<INPUT TYPE=hidden  NAME=SDATE VALUE=\"%s\">\n",$sdate);
	printf("<INPUT TYPE=hidden  NAME=ITEM VALUE=\"%s\">\n",$item);
	printf("<INPUT TYPE=hidden  NAME=SAKI VALUE=\"%s\">\n",$saki);
	printf("<center><BUTTON type=submit name=FSEND value=\"submit\"><BIG>�o�[�R�[�h���쐬</BIG></BUTTON><center>\n");
	printf("</FORM>\n");
	if (!empty($fsend) && $item != "" && $saki != "")
		{

		$ret = PakiFileCreate($sdate, $item, $saki);
		
		if ($ret == 0)
			{
			printf("<P><center>\n");
			printf("<center><P>�o�[�R�[�h�쐬�Ώۂ̏��͂���܂���B</P></center>\n");
			printf("</center></P>\n");
			}
		else if ($ret > 0)
			{
			$num = $ret;
			$ret = PakinoFtpPut();
			if ($ret == TRUE)
				{
				printf("<P><center>\n");
				printf("�p�L�p�L�o�[�R�[�h�����쐬���܂����B[%s��]\n", $num);
				printf("</center></P>\n");
				}
			else
				{
				printf("<P><center>\n");
				printf("�p�L�p�L�o�[�R�[�h���̑��M�Ɏ��s���܂����B\n");
				printf("</center></P>\n");
				printf("<P><center>\n");
				printf("�d�����V�X�e���̒[�����N�����Ă��邩�m�F���ĉ������B\n");
				printf("</center></P>\n");
				}
			}
		else
			{
			printf("<P><center>\n");
			printf("�p�L�p�L�o�[�R�[�h���̍쐬�Ɏ��s���܂����B\n");
			printf("</center></P>\n");
			}
		}
	}
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� add end <-----  

?>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>RACK</th>
<th>�\��</th>
<th>����</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$paki_cnt = 0;
	$sql = "";
	$sql = $sql . "select itmcd,itmnm,zrlcknm ";
	$sql = $sql . "from fitmcmst ";
	$sql = $sql . "where itmcd between '61' and '79' and ukflg = '1' ";
	$sql = $sql . "order by itmcd for read only";

	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$paki[$paki_cnt][0] = $row[0];
		$paki[$paki_cnt][1] = $row[1];
		$paki[$paki_cnt][2] = $row[2];
		$paki[$paki_cnt][3] = 0;
		$paki_cnt++;
		}

	for ($i=0;$i<$paki_cnt;$i++)
		{
		printf("<tr>\n");

		$pakicd = $paki[$i][0];
		$sql = "";
		$sql = $sql . "select count(*) ";
		$sql = $sql . "from fpkptbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "and itmcd = '$pakicd' ";
		$sql = $sql . "for read only";

		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$paki[$i][3] = $row[0];
		$pdst->closeCursor();

//		printf("<td>%s</td>\n",$row[0]);
		printf("<td><A href=pakishokai2.php?SDATE=%s&ITEM=%s>%s</A></td>\n",$sdate,$paki[$i][0],substr($paki[$i][1],0,4));
		printf("<td align=center><A href=pakishokai2.php?SDATE=%s&ITEM=%s>%s</A></td>\n",$sdate,$paki[$i][0],$paki[$i][2]);
		printf("<td align = right>%s</td>\n",number_format($paki[$i][3]));
		printf("</tr>\n");
		}

	printf("</table>\n");

	if  ($item != "")
		{
		printf("<td>\n");
		printf("<table bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th>RACK</th>\n");
		printf("<th>�L��</th>\n");
		printf("<th>WSCD</th>\n");
		printf("<th>�v�r��</th>\n");
		printf("<th>����</th>\n");
		printf("</tr>\n");

		$ws_cnt = 0;
		$sql = "";
		$sql = $sql . "select it.itmnm,ws.swkskid,ws.smpcd,ws.smpcdnm ";
		$sql = $sql . "from nfsmpmst ws,fitmcmst it ";
		$sql = $sql . "where it.itmcd = '$item' ";
		$sql = $sql . "and it.ukflg = '1' ";
		$sql = $sql . "and ws.itmcd = it.itmcd ";
		$sql = $sql . "and ws.ukflg = '1' ";
		$sql = $sql . "order by ws.swkskid,ws.smpcd for read only";

		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			$ws[$ws_cnt][0] = $row[0];
			$ws[$ws_cnt][1] = $row[1];
			$ws[$ws_cnt][2] = $row[2];
			$ws[$ws_cnt][3] = $row[3];
			$ws[$ws_cnt][4] = 0;
			$ws_cnt++;
			}

		for ($i=0;$i<$ws_cnt;$i++)
			{
			$wscd = $ws[$i][2];
			$sql = "";
			$sql = $sql . "select count(*) ";
			$sql = $sql . "from fpkptbl ";
			$sql = $sql . "where sriymd = '$sdate' ";
			$sql = $sql . "and itmcd = '$item' ";
			$sql = $sql . "and smpcd = '$wscd' ";
			$sql = $sql . "for read only";

			$pdst = $conn->prepare($sql);
			$pdst->execute();
			$row = $pdst->fetch(PDO::FETCH_NUM);
			$ws[$i][4] = $row[0];
			$pdst->closeCursor();

			printf("<tr>\n");
			printf("<td>%s</td>\n",substr($ws[$i][0],0,4));
			printf("<td align=center>%s</td>\n",$ws[$i][1]);
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� mod start ----->  
			printf("<td align=right><A href=pakishokai2.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,mb_convert_kana($ws[$i][1],"K"),$ws[$i][2]);
			printf("<td><A href=pakishokai2.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,mb_convert_kana($ws[$i][1],"K"),$ws[$i][3]);
//			printf("<td align=right><A href=pakishokai2.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,$ws[$i][1],$ws[$i][2]);
//			printf("<td><A href=pakishokai2.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,$ws[$i][1],$ws[$i][3]);
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� mod end <-----  
			printf("<td align = right>%s</td>\n",number_format($ws[$i][4]));
			printf("</tr>\n");
			$rack = substr(trim($ws[$i][0]),0,4);
			}
		printf("</table>\n");
		printf("</td>\n");

		if  ($saki != "")
			{
			printf("<td>\n");
			printf("<table bgcolor = white border>\n");
			printf("<tr>\n");
			printf("<th>�L��</th>\n");
			printf("<th>�r�d�p</th>\n");
			printf("<th>������</th>\n");
			printf("<th>����No</th>\n");
			printf("<th>CH</th>\n");
			printf("<th>WSCD</th>\n");
			printf("<th>����No</th>\n");
			printf("<th>�A�b�Z�C���b�N</th>\n");
			printf("</tr>\n");

			$sql = "";
			$sql = $sql . "select sriymd,swkskid,ssseq,barcd,smpcd,aslckhno,itmseq,rckseq,chkchr ";
			$sql = $sql . "from fpkptbl ";
			$sql = $sql . "where sriymd = '$sdate' ";
			$sql = $sql . "and itmcd = '$item' ";
			$sql = $sql . "and swkskid = '$saki' ";
			$sql = $sql . "order by ssseq for read only";
			foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
				{
				printf("<tr>\n");
				printf("<td align=center>%s</td>\n",$row[1]);
				printf("<td align=right>%d</td>\n",$row[2]);
				printf("<td>%s</td>\n",ymd_edit($row[0]));
				printf("<td>%s</td>\n",barcode_edit($row[3]));
				printf("<td>%s</td>\n",$row[8]);
				printf("<td align=right>%s</td>\n",$row[4]);
				printf("<td align=right>%d</td>\n",$row[6]);
				printf("<td>%s%04d-%02d</td>\n",$rack,$row[7],$row[5]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("</td>\n");
			}
		}
	}
	else
	{
	echo "Connection failed";
	}

$conn = null;

?>
</td>
</table>

<br clear=all>

<?php
NsfrBackPage();
printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>�t�����e�B�A�V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>

<HR>
</BODY>
</HTML>

<?php
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� add start ----->  
function PakiFileCreate($sdate, $item, $saki)
{
	$ret = -1;

	$fp = fopen("/tmp/pakino.txt","w");
	if ($fp == FALSE)
		{
		NsfrLogOut("PAKINO FILE OPEN FALSE");
		return $ret;
		}

	$conn = Get_DBConn();

	if  ($conn)
		{
		$sql = "";
		$sql = $sql . "select barcd ";
		$sql = $sql . "from fpkptbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "and itmcd = '$item' ";
		$sql = $sql . "and swkskid = '$saki' ";
		$sql = $sql . "order by ssseq for read only";
		$ret=0;
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			fprintf($fp,"%s\r\n",substr($row[0],2,9));
			$ret++;
			}
		}

	fclose($fp);
	$conn = null;

	return $ret;
}

function PakinoFtpPut()
{
	$ftphost = "virus011";
	$username = "bun";
	$passwd   = "bun";
	$remotefile = "/export/home/bun/dat/acos/pakino.txt";
	$localfile = "/tmp/pakino.txt";

	$ret = TRUE;

	$ftp_conn = ftp_connect($ftphost);
	if ($ftp_conn == FALSE)
		{
		NsfrLogOut("Coudn't connect ftp server");
		return FALSE;
		}

	if (ftp_login($ftp_conn,$username,$passwd))
		{
		NsfrLogOut("FTP Connect OK");
		if (ftp_put($ftp_conn,$remotefile,$localfile,FTP_BINARY))
			{
			$logmsg = sprintf("FTP File Put [%s] OK",$localfile);
			NsfrLogOut($logmsg);
			}
		else
			{
			$logmsg = sprintf("FTP File Put [%s] NG",$localfile);
			NsfrLogOut($logmsg);
			$ret = FALSE;
			}
		}
	else
		{
		NsfrLogOut("FTP Connect NG");
		$ret = FALSE;
		}

	ftp_close($ftp_conn);
	return $ret;
}
//2009/03/17 k-yokota@bml.co.jp �o�[�R�[�h�o�͎w�� add end <-----  
?>
