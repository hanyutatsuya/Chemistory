<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("PG1/PG2比チェック");
LaboLogOut("PG1/PG2比チェック");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>PG1/PG2比チェック</h2></center>

<?php

printf("<HR>\n");

$conn = GetDBConn();

if ($conn) {

	try {
		printf("<table align=\"center\" bgcolor = white border>\n");
			printf("<tr>\n");
				printf("<th nowarp>処理日</th>\n");
				printf("<th nowarp>依頼書No.</th>\n");
				printf("<th nowarp>項目CD</th>\n");
				printf("<th nowarp>項目名</th>\n");
				printf("<th nowarp>　結果　</th>\n");
				printf("<th nowarp>FLG</th>\n");
				printf("<th nowarp>号機</th>\n");
				printf("<th nowarp>ME-SEQ</th>\n");
			printf("</tr>\n");

			$sql = "";
			$sql = $sql . "select ";
			$sql = $sql . "k1.utkymd as utkymd,k1.irino as irino, ";
			$sql = $sql . "k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,case when k1.bskgok = '' then '0' else k1.bskgok end,k1.bskseq, ";
			$sql = $sql . "k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg,case when k2.bskgok = '' then '0' else k2.bskgok end,k2.bskseq, ";
			$sql = $sql . "k3.kmkcd,m3.kmkrs,k3.hjkka,k3.knsflg,case when k3.bskgok = '' then '0' else k3.bskgok end,k3.bskseq, ";
			$sql = $sql . "'0000000' as kmkcd,'XXXXX' as kmkrs,'XXXXXXXX' as kjkka,'Z' as knsflg,'0' as bskgok,'0' as bskseq ";
			$sql = $sql . "from kekka k1,kekka k2,kekka k3, ";
			$sql = $sql . "kmkmst m1,kmkmst m2,kmkmst m3,sysknrmst s ";
			$sql = $sql . "where s.lbcd = '001' ";
			$sql = $sql . "and k1.sriymd = s.kjnsriymd ";
			$sql = $sql . "and k1.kmkcd = '0003734' ";
			$sql = $sql . "and k1.knsflg in ('E','X','S') ";
			$sql = $sql . "and k1.siyflg = '1' ";
			$sql = $sql . "and k2.utkymd = k1.utkymd ";
			$sql = $sql . "and k2.irino = k1.irino ";
			$sql = $sql . "and k2.kmkcd = '0003735' ";
			$sql = $sql . "and k2.knsflg in ('E','X','S') ";
			$sql = $sql . "and k2.siyflg = '1' ";
			$sql = $sql . "and k3.utkymd = k1.utkymd ";
			$sql = $sql . "and k3.irino = k1.irino ";
			$sql = $sql . "and k3.kmkcd = '0003736' ";
			$sql = $sql . "and k3.knsflg in ('E','X','S') ";
			$sql = $sql . "and k3.siyflg = '1' ";
			$sql = $sql . "and (k1.bskseq != k2.bskseq or k2.bskseq != k3.bskseq) ";
			$sql = $sql . "and k1.bskseq > 0 ";
			$sql = $sql . "and k2.bskseq > 0 ";
			$sql = $sql . "and k3.bskseq > 0 ";
			$sql = $sql . "and m1.knsgrp = k1.knsgrp ";
			$sql = $sql . "and m1.kmkcd = k1.kmkcd ";
			$sql = $sql . "and m2.knsgrp = k2.knsgrp ";
			$sql = $sql . "and m2.kmkcd = k2.kmkcd ";
			$sql = $sql . "and m3.knsgrp = k3.knsgrp ";
			$sql = $sql . "and m3.kmkcd = k3.kmkcd ";
			$sql = $sql . "union all ";
			$sql = $sql . "select ";
			$sql = $sql . "k1.utkymd as utkymd,k1.irino as irino, ";
			$sql = $sql . "k1.kmkcd,m1.kmkrs,k1.hjkka,k1.knsflg,case when k1.bskgok = '' then '0' else k1.bskgok end,k1.bskseq, ";
			$sql = $sql . "k2.kmkcd,m2.kmkrs,k2.hjkka,k2.knsflg,case when k2.bskgok = '' then '0' else k2.bskgok end,k2.bskseq, ";
			$sql = $sql . "k3.kmkcd,m3.kmkrs,k3.hjkka,k3.knsflg,case when k3.bskgok = '' then '0' else k3.bskgok end,k3.bskseq, ";
			$sql = $sql . "k4.kmkcd,m4.kmkrs,k4.hjkka,k4.knsflg,case when k4.bskgok = '' then '0' else k4.bskgok end,k4.bskseq ";
			$sql = $sql . "from kekka k1,kekka k2,kekka k3,kekka k4, ";
			$sql = $sql . "kmkmst m1,kmkmst m2,kmkmst m3,kmkmst m4,sysknrmst s ";
			$sql = $sql . "where s.lbcd = '001' ";
			$sql = $sql . "and k1.sriymd = s.kjnsriymd ";
			$sql = $sql . "and k1.kmkcd = '0003734' ";
			$sql = $sql . "and k1.knsflg in ('E','X','S') ";
			$sql = $sql . "and k1.siyflg = '1' ";
			$sql = $sql . "and k2.utkymd = k1.utkymd ";
			$sql = $sql . "and k2.irino = k1.irino ";
			$sql = $sql . "and k2.kmkcd = '0003735' ";
			$sql = $sql . "and k2.knsflg in ('E','X','S') ";
			$sql = $sql . "and k2.siyflg = '1' ";
			$sql = $sql . "and k3.utkymd = k1.utkymd ";
			$sql = $sql . "and k3.irino = k1.irino ";
			$sql = $sql . "and k3.kmkcd in ('0021644','0021996','0022672','0022679') ";
			$sql = $sql . "and k3.knsflg in ('E','X','S') ";
			$sql = $sql . "and k3.siyflg = '1' ";
			$sql = $sql . "and k4.utkymd = k1.utkymd ";
			$sql = $sql . "and k4.irino = k1.irino ";
			$sql = $sql . "and k4.kmkcd in ('0021645','0021993','0022669','0022676') ";
			$sql = $sql . "and k4.knsflg in ('E','X','S') ";
			$sql = $sql . "and k4.siyflg = '1' ";
			$sql = $sql . "and (k1.bskseq != k2.bskseq or k2.bskseq != k3.bskseq or k3.bskseq != k4.bskseq) ";
			$sql = $sql . "and k1.bskseq > 0 ";
			$sql = $sql . "and k2.bskseq > 0 ";
			$sql = $sql . "and k3.bskseq > 0 ";
			$sql = $sql . "and k4.bskseq > 0 ";
			$sql = $sql . "and m1.knsgrp = k1.knsgrp ";
			$sql = $sql . "and m1.kmkcd = k1.kmkcd ";
			$sql = $sql . "and m2.knsgrp = k2.knsgrp ";
			$sql = $sql . "and m2.kmkcd = k2.kmkcd ";
			$sql = $sql . "and m3.knsgrp = k3.knsgrp ";
			$sql = $sql . "and m3.kmkcd = k3.kmkcd ";
			$sql = $sql . "and m4.knsgrp = k4.knsgrp ";
			$sql = $sql . "and m4.kmkcd = k4.kmkcd ";
			$sql = $sql . "order by utkymd,irino ";
			$sql = $sql . "for read only with ur ";

			foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
				if ($row[7] > 0) {
					printf("<tr>\n");
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
						printf("<td nowrap>%s-%s</td>\n",SjToUtfConv(substr($row[1],2,3)),SjToUtfConv(substr($row[1],5,4)));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[2]));
						printf("<td nowrap>%-10.10s</td>\n",str_replace(' ','',SjToUtfConv($row[3])));
						printf("<td nowrap align=right>%8.8s</td>\n",SjToUtfConv($row[4]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[5]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv(substr($row[6],0,2)));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[7]));
					printf("</tr>\n");

					if ($row[13] > 0) {
						printf("<tr>\n");
							printf("<td nowrap></td>\n");
							printf("<td nowrap></td>\n");
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[8]));
							printf("<td nowrap>%-10.10s</td>\n",str_replace(' ','',SjToUtfConv($row[9])));
							printf("<td nowrap align=right>%s</td>\n",SjToUtfConv($row[10]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[11]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv(substr($row[12],0,2)));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[13]));
						printf("</tr>\n");
					}
					if ($row[19] > 0) {
						printf("<tr>\n");
							printf("<td nowrap></td>\n");
							printf("<td nowrap></td>\n");
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[14]));
							printf("<td nowrap>%-10.10s</td>\n",str_replace(' ','',SjToUtfConv($row[15])));
							printf("<td nowrap align=right>%s</td>\n",SjToUtfConv($row[16]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[17]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv(substr($row[18],0,2)));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[19]));
						printf("</tr>\n");
					}
					if ($row[25] > 0) {
						printf("<tr>\n");
							printf("<td nowrap></td>\n");
							printf("<td nowrap></td>\n");
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[20]));
							printf("<td nowrap>%-10.10s</td>\n",str_replace(' ','',SjToUtfConv($row[21])));
							printf("<td nowrap align=right>%s</td>\n",SjToUtfConv($row[22]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[23]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv(substr($row[24],0,2)));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[25]));
						printf("</tr>\n");
					}
				}
			}

		printf("</table>\n");

		printf("<BR clear=all>\n");
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}

} else {
	echo "Connection failed";
}
$conn = null;
printf("<br clear=all>\n");

printf("<HR>\n");
LaboBackPage();
CheckTailOut();

?>

<HR>
</BODY>
</HTML>

