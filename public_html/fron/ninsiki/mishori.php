<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("未処理チェック");
NsfrLogOut("未処理チェック");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>未処理チェック</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$hiki = hikiwatasi_check($conn,$sdate);
	$futeki = futekigou_check($conn,$sdate);
	$mikan = mikanryo_check($conn,$sdate);
	$kan = kanja_check($conn,$sdate);
	$jizen = jizen_check($conn,$sdate);
	$kaitou = kaitou_check($conn,$sdate);

	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>処　理　名</th>\n");
	printf("<th>件数</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	if ($hiki == 0)
		printf("<td bgcolor=skyblue>未引き渡しトレー</td>\n");
	else
		printf("<td bgcolor=pink><A href=hikitray.php?SDATE=%s>未引き渡しトレー</A></td>\n",$sdate);
	if ($hiki == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($hiki));
	else
		printf("<td bgcolor=pink align=right><A href=hikitray.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($hiki));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($futeki == 0)
		printf("<td bgcolor=skyblue>不適合登録もれ</td>\n");
	else
		printf("<td bgcolor=pink><A href=futekiken.php?SDATE=%s>不適合登録もれ</A></td>\n",$sdate);
	if ($futeki == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($futeki));
	else
		printf("<td bgcolor=pink align=right><A href=futekiken.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($futeki));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($mikan == 0)
		printf("<td bgcolor=skyblue>未完了ラック</td>\n");
	else
		printf("<td bgcolor=pink><A href=mrackmap.php?SDATE=%s>未完了ラック</A></td>\n",$sdate);
	if ($mikan == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($mikan));
	else
		printf("<td bgcolor=pink align=right><A href=mrackmap.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($mikan));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($kan == 0)
		printf("<td bgcolor=skyblue>患者名チェックリスト未出力</td>\n");
	else
		printf("<td bgcolor=pink><A href=kjrackmap.php?SDATE=%s>患者名チェックリスト未出力</A></td>\n",$sdate);
	if ($kan == 0)
		printf("<td bgcolor=skyblue align=right>%s</td>\n",number_format($kan));
	else
		printf("<td bgcolor=pink align=right><A href=kjrackmap.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($kan));
	printf("</tr>\n");

	printf("<tr>\n");
	if ($jizen != 0)
		printf("<td bgcolor=skyblue><A href=chichaku.php?SDATE=%s>遅着検体登録数</A></td>\n",$sdate);
	else
		printf("<td bgcolor=pink>遅着検体登録数</td>\n");
	if ($jizen != 0)
		printf("<td bgcolor=skyblue align=right><A href=chichaku.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($jizen));
	else
		printf("<td bgcolor=pink align=right>%s</td>\n",number_format($jizen));
	printf("</tr>\n");

	if ($kaitou < 100)
		printf("<td bgcolor=skyblue><A href=erackmap.php?SDATE=%s>解凍ラック検体数</A></td>\n",$sdate);
	else
		printf("<td bgcolor=pink><A href=erackmap.php?SDATE=%s>解凍ラック検体数</A></td>\n",$sdate);
	if ($kaitou < 100)
		printf("<td bgcolor=skyblue align=right><A href=erackmap.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($kaitou));
	else
		printf("<td bgcolor=pink align=right><A href=erackmap.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($kaitou));
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

<?php
function hikiwatasi_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct kn.trayid) from nfktbl kn ";
	$sql = $sql . "where kn.sriymd = '$sdate' ";
	$sql = $sql . "and kn.sskbn = '01' ";
	$sql = $sql . "and char(trayid,1) < 'A' ";
	$sql = $sql . "and not exists ";
	$sql = $sql . "(select * from nknthktbl h where h.sriymd = kn.sriymd and h.trayid = kn.trayid) ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function futekigou_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct m.barcd) from fbncmktbl m ";
	$sql = $sql . "where m.sriymd = '$sdate' ";
	$sql = $sql . "and char(m.knbnid,1) not in ('V','S') ";
	$sql = $sql . "and exists ( select * from fbncmktbl f ";
	$sql = $sql . "where f.sriymd = m.sriymd ";
	$sql = $sql . "and char(f.barcd,9) = char(m.barcd,9) ";
	$sql = $sql . "and f.bcngcd = '6') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function mikanryo_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct lckid) from nfktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and sskflg != '1' ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function kanja_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct lckid) from nfktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and substr(lckid,1,1) in ('T','K','V','Q','P','W') ";
	$sql = $sql . "and  (sakhm >= kjmckdh or kjmckdh is null) for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	$sql = "";
	$sql = $sql . "select count(distinct mk.knbnid) from nfktbl kn,fbncmktbl mk ";
	$sql = $sql . "where mk.sriymd = '$sdate' and kn.sriymd = '$sdate' ";
	$sql = $sql . "and mk.barcd = kn.barcd and mk.kntkbn = kn.kntkbn ";
	$sql = $sql . "and mk.knbnid != ' ' ";
	$sql = $sql . "and kn.sakhm >= kn.kjmckdh ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $cnt_t + $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function jizen_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(distinct kntno) from nccktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

function kaitou_check($conn,$sdate)
{
	$sql = "";
	$sql = $sql . "select count(*) from nfktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and substr(lckid,1,4) in ('EEEE','CCBB','MMBB') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	return($cnt_t);
}

?>

