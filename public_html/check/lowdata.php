<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("低値再検検体確認");
LaboLogOut("低値再検検体確認");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>低値再検検体確認</h2></center>

<?php

printf("<HR>\n");


	$conn = GetDBConn();

	if ($conn) {

		try {
			$cnt = 0;
			printf("<table align=\"center\" bgcolor = white border>\n");
				printf("<tr>\n");
					printf("<th nowarp>　　</th>\n");
					printf("<th nowarp>BML受付年月日</th>\n");
					printf("<th nowarp>依頼書No</th>\n");
					printf("<th nowarp>項目CD</th>\n");
					printf("<th nowrap>項目名</th>\n");
					printf("<th nowrap>検査回数</th>\n");
					printf("<th nowrap>結果状況CD</th>\n");
					printf("<th nowrap>検査F</th>\n");
					printf("<th nowrap>照会結果</th>\n");
					printf("<th nowrap>再検理由A</th>\n");
				printf("</tr>\n");
	
				$sql = "";
				$sql = $sql . "select distinct ka.utkymd,ka.irino,ka.kmkcd,km.kmkrs,ka.knssu,ka.kkajkcd,ka.knsflg,ka.skkka,ka.skrycda ";
				$sql = $sql . "from kekka ka,kmkmst km ,sysknrmst s ";
				$sql = $sql . "where s.lbcd = '001' ";
				$sql = $sql . "and ka.sriymd = s.kjnsriymd ";
				$sql = $sql . "and exists (select * from kekka ks ";
				$sql = $sql . "where ks.sriymd = s.kjnsriymd ";
				$sql = $sql . "and ks.SKRYCDA in ('100','299') ";
				$sql = $sql . "and ka.utkymd = ks.utkymd ";
				$sql = $sql . "and ka.irino = ks.irino) ";
//				$sql = $sql . "and ka.SKRYCDA in ('100','299') ";
				$sql = $sql . "and km.knsgrp = ka.knsgrp ";
				$sql = $sql . "and km.kmkcd = ka.kmkcd ";
				$sql = $sql . "order by ka.utkymd,ka.irino,ka.kmkcd ";
				$sql = $sql . "for read only with ur ";
	
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					printf("<tr>\n");
						printf("<td nowrap> </td>\n");
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[1]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[2]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[3]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[4]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[5]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[6]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[7]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[8]));
					printf("</tr>\n");
					$cnt = $cnt + 1;
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
printf("<HR>\n");
CheckTailOut();

?>

<HR>
</BODY>
</HTML>

