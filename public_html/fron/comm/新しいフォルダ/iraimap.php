<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<HEAD>
<TITLE>�˗����Ɖ�</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
</HEAD>

<BODY>
<center><h2>�˗����Ɖ�</h2></center>

<?php
require_once("../comm/kenno_edit.inc");
$udate = trim($_GET['UDATE']);
$ino   = trim($_GET['INO']);
$sdate = trim($_GET['SDATE']);
$kenno = trim($_GET['KENNO']);
$barcd = trim($_GET['BARCD']);

$para_flg = 0;

if  ($udate != "" && $ino != "")
	{
	printf("<center><P>��t���@�F%s</P></center>\n",$sdate);
	printf("<center><P>�˗����ԍ��F%s</P></center>\n",barcode_edit($barcd));
	$para_flg = 1;
	}
else
	{
	if  ($sdate != "" && ($kenno != "" || $barcd != ""))
		{
		printf("<center>   <h2>�������@�F%s</h2></center>\n",$sdate);
		if  ($barcd != "")
			{
			printf("<center><P>���̔ԍ��F%s</P></center>\n",barcode_edit($barcd));
			$para_flg = 2;
			}
		else
			{
			printf("<center><P>���̔ԍ��F%s</P></center>\n",kenno_edit($kenno));
			$para_flg = 3;
			}
		}
	}

if  ($para_flg != 0)
	{
	$conn = new PDO('odbc:NSFRDB1','nsfr','nsfr');

	if  ($conn)
		{
		if  (para_flg == 1)
			{
			$sql = "";
			$sql = $sql . "select utkymd,irino from nfktbl ";
			$sql = $sql . "where sriymd = '$sdate' ";
			$sql = $sql . "and barcd = '$barcd' ";
			$sql = $sql . "for read only";
			foreach ($conn->query($sql) as $row)
				{
				$udate = trim($row[0]);
				$ino   = trim($row[1]);
				break;
				}
			}

		printf("<table align=\"center\" border>\n");
		printf("<tr>\n");
		printf("<th>��t��</th>\n");
		printf("<th>�˗���No.</th>\n");
		printf("<th>����No.</th>\n");
		printf("<th>�o�[�R�[�h</th>\n");
		printf("<th>�d�������</th>\n");
		printf("<th>�g���[ID:POS</th>\n");
		printf("<th>���b�NID:POS</th>\n");
		printf("<th>���̗�</th>\n");
		printf("</tr>\n");

		$sql = "";
		$sql = $sql . "select kn.utkymd,kn.irino,kn.kntno,kn.barcd,ss.zrnmr,";
		$sql = $sql . "kn.trayid,traypos,kn.lckid,kn.lckpos,kn.erstktr ";
		$sql = $sql . "from nfktbl kn,nfssmst ss ";
		$sql = $sql . "where kn.utkymd = '$udate' ";
		$sql = $sql . "and kn.irino = '$ino' ";
		$sql = $sql . "and ss.sskbn = kn.sskbn ";
		$sql = $sql . "and ss.ukflg = '1' ";
		$sql = $sql . "order by kn.kntno for read only";
		foreach ($conn->query($sql) as $row)
			{
			printf("<tr>\n");
			printf("<td>%s</td>\n",ymd_edit($row[0]));
			printf("<td>%s</td>\n",ino_edit($row[1]));
			printf("<td>%s</td>\n",kenno_edit($row[2]));
			printf("<td>%s</td>\n",barcode_edit($row[3]));
			printf("<td>%s</td>\n",$row[4]);
			printf("<td>%s-%s</td>\n",$row[5],$row[6]);
			printf("<td>%s-%s</td>\n",$row[7],$row[8]);
			printf("<td>%s</td>\n",$row[9]);
			printf("</tr>\n");
			}
		}
		printf("</table>\n");
		printf("<HR>\n");

		printf("<table align=\"center\" border>\n");
		printf("<tr>\n");
		printf("<th>WSCD</th>\n");
		printf("<th>W/S��</th>\n");
		printf("<th>����CD</th>\n");
		printf("<th>���ږ�</th>\n");
		printf("<th>�T�e���C�g</th>\n");
		printf("</tr>\n");

		if  ($barcd != "")
			{
			$sql = "";
			$sql = $sql . "select ir.smpcd,ws.smpcdnm,ir.kmkcd,km.kmknmr,ir.stid,km.oyakmkcd ";
			$sql = $sql . "from nfktbl kn,nfjtbl jj,nfitbl ir,nfsmpmst ws,nfkmkmst km ";
			$sql = $sql . "where kn.sriymd = '$sdate' ";
			$sql = $sql . "and kn.barcd = '$barcd' ";
			$sql = $sql . "and jj.sriymd = kn.sriymd ";
			$sql = $sql . "and jj.barcd = kn.barcd ";
			$sql = $sql . "and jj.kntkbn = kn.kntkbn ";
			$sql = $sql . "and ir.sriymd = jj.sriymd ";
			$sql = $sql . "and ir.kntno = jj.kntno ";
			$sql = $sql . "and ir.kmkcd = jj.kmkcd ";
			$sql = $sql . "and ws.smpcd = ir.smpcd ";
			$sql = $sql . "and ws.ukflg = '1' ";
			$sql = $sql . "and km.kmkcd = ir.kmkcd ";
			$sql = $sql . "and km.ukflg = '1' ";
			$sql = $sql . "order by ir.smpcd,km.oyakmkcd,ir.kmkcd for read only";
			foreach ($conn->query($sql) as $row)
				{
				printf("<tr>\n");
				for ($i=0;$i<5;$i++)
					{
					printf("<td>%s</td>\n",$row[$i]);
					}
				printf("</tr>\n");
				}
			}
		printf("</table>\n");
		}
	else
		{
		echo "Connection failed";
		}
	$conn = null;
	}

printf("<HR>\n");
require_once("backpage.inc");
?>
<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
