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
				printf("</tr>\n");
	
				$sql = "";
				$sql = $sql . "select distinct ka.utkymd,ka.irino,ka.kmkcd,km.kmkrs,ka.knssu,ka.kkajkcd,ka.knsflg,ka.skkka ";
				$sql = $sql . "from kekka ka,kmkmst km ,sysknrmst s ";
				$sql = $sql . "where s.lbcd = '001' ";
				$sql = $sql . "and ka.sriymd = s.kjnsriymd ";
				$sql = $sql . "and ka.knsflg = 'M' ";
				$sql = $sql . "and ka.kkajkcd = '3' ";
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
					printf("</tr>\n");
					$cnt = $cnt + 1;
				}
	
			printf("</table>\n");
	
			printf("<BR clear=all>\n");
			
			if ($cnt > 0) {
				printf("<FORM ACTION=\"knsflgupd.php\" METHOD=POST>\n");
				printf("<table align=\"center\" bgcolor = white border>\n");
					printf("<tr>\n");
						printf("<th nowarp>CLR</th>\n");
						printf("<th nowarp>BML受付年月日</th>\n");
						printf("<th nowarp>依頼書No</th>\n");
						printf("<th nowarp>項目CD</th>\n");
						printf("<th nowrap>項目名</th>\n");
						printf("<th nowrap>検査回数</th>\n");
						printf("<th nowrap>結果状況CD</th>\n");
						printf("<th nowrap>検査F</th>\n");
						printf("<th nowrap>照会結果</th>\n");
					printf("</tr>\n");
		
					$sql = "";
					$sql = $sql . "select distinct ka.utkymd,ka.irino,ka.kmkcd,km.kmkrs,ka.knssu,ka.kkajkcd,ka.knsflg,ka.skkka ";
					$sql = $sql . "from kekka ka,kmkmst km ,sysknrmst s ";
					$sql = $sql . "where s.lbcd = '001' ";
					$sql = $sql . "and ka.sriymd = s.kjnsriymd ";
					$sql = $sql . "and km.knsgrp = ka.knsgrp ";
					$sql = $sql . "and km.kmkcd = ka.kmkcd ";
					$sql = $sql . "and exists (select * from kekka k1 ";
					$sql = $sql . "where k1.utkymd = ka.utkymd ";
					$sql = $sql . "and k1.irino = ka.irino ";
					$sql = $sql . "and k1.knsgrp = ka.knsgrp ";
					$sql = $sql . "and k1.kmkcd = ka.kmkcd ";
					$sql = $sql . "and k1.knsflg = 'M' ";
					$sql = $sql . "and k1.kkajkcd = '3') ";
					$sql = $sql . "order by ka.utkymd,ka.irino,ka.kmkcd ";
					$sql = $sql . "for read only with ur ";
		
					foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
						printf("<tr>\n");
							printf("<td nowrap>\n");
							if ($row[5] == '3' && $row[6] == 'M') {
								printf("<INPUT TYPE=RADIO NAME=KUBUN VALUE=\"0\">\n");
							}
							printf("</td>\n");
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[1]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[2]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[3]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[4]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[5]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[6]));
							printf("<td nowrap>%s</td>\n",SjToUtfConv($row[7]));
						printf("</tr>\n");
						$cnt = $cnt + 1;
					}
		
				printf("</table>\n");
				printf("<BR>\n");
				printf("<center>\n");
				printf("<BUTTON TYPE=submit name=upd value=\"upd\">更新\n");
				printf("</BUTTON>\n");
				printf("</center>\n");
				printf("</FORM>\n");
		
				printf("<BR clear=all>\n");
			}
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

