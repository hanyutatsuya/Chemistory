<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("依頼情報照会");
NsfrLogOut("依頼情報照会");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>依頼情報照会</h2></center>

<?php
$sdate = $_GET['SDATE'];
$type  = $_GET['TYPE'];
$rack  = $_GET['RACK'];
$barcd = $_GET['BARCD'];

$conn = Get_DBConn();

if  ($conn)
	{
	printf("<center><h2>処理日　：%s</h2></center>\n",$sdate);
	printf("<center><h2>検体番号：%s</h2></center>\n",barcode_edit($barcd));

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

	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>受付日</th>\n");
	printf("<th>依頼書No.</th>\n");
	printf("<th>検体No.</th>\n");
	printf("<th>バーコード</th>\n");
	printf("<th>仕分け種類</th>\n");
	printf("<th>トレーID:POS</th>\n");
	printf("<th>ラックID:POS</th>\n");
	printf("<th>検体量</th>\n");
	printf("</tr>\n");

	if  ($udate != "" && $ino != "")
		{
		$sql = "";
		$sql = $sql . "select kn.utkymd,kn.irino,kn.kntno,kn.barcd,ss.zrnmr,";
		$sql = $sql . "kn.trayid,traypos,kn.lckid,kn.lckpos,kn.tjhyktr ";
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
	printf("<th>W/S名</th>\n");
	printf("<th>項目CD</th>\n");
	printf("<th>項目名</th>\n");
	printf("<th>サテライト</th>\n");
	printf("<th>分注量</th>\n");
	printf("</tr>\n");

	if  ($barcd != "")
		{
		$sql = "";
		$sql = $sql . "select ir.smpcd,ws.smpcdnm,ir.kmkcd,km.kmknmr,ir.stid,km.tjbncryo,km.oyakmkcd ";
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
			for ($i=0;$i<6;$i++)
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

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=tkmap.php?SDATE=%s&TYPE=%d&RACK=%s>凍結検体ラックマップに戻る</A></center>\n",
		$sdate,$type,$rack);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=tk1ran.php?SDATE=%s&TYPE=%d>凍結検体ラック照会に戻る</A></center>\n",
		$sdate,$type);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=tkhonsu.php?SDATE=%s>凍結検体本数照会に戻る</A></center>\n",$sdate);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>検体認識システム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
