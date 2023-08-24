<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("件数一覧");
LaboLogOut("件数一覧");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>件数一覧</h2></center>

<?php
$utkymd = trim($_REQUEST['UTKYMD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"kensu.php\" METHOD=POST>\n");
printf("受付日\n");
printf("<INPUT TYPE=text NAME=UTKYMD SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$utkymd);
printf("　<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");

if (strlen($utkymd) != 0) {

	$udate = "";

	if (!is_numeric($utkymd)) {
		printf("<center>\n");
		printf("<h2>受付日入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
	} else {
		if (strlen($utkymd) != 8) {
			printf("<center>\n");
			printf("<h2>受付日入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
		} else {
			if (ymd_check($utkymd) == false) {
				printf("<center>\n");
				printf("<h2>受付日フォーマットエラー</h2>\n");
				printf("</center>\n");
				printf("<HR>\n");
			} else {
				$udate = ymd_edit($utkymd);
			}
		}
	}
}

printf("<HR>\n");

if (strlen($udate) != 0) {

	$conn = GetDBConn();

	if ($conn) {

		try {
			printf("<table align=\"center\" bgcolor = white border>\n");
			
				printf("<tr>\n");
					printf("<th nowarp> </th>\n");
					printf("<th nowarp>件数</th>\n");
				printf("</tr>\n");
			
				$sql = "select count(*) from kanjya where utkymd = '$udate' for read only with ur";
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					$cnt_kanja = $row[0];
					break;
				}
	
				printf("<tr>\n");
					printf("<td nowarp>患者数</td>\n");
					printf("<td  align=right nowarp>%s</td>\n",number_format($cnt_kanja));
				printf("</tr>\n");

				$sql = "";
				$sql = $sql . "select sum(cnt) from ( ";
				$sql = $sql . "select knsgrp as ws,count(distinct irino) as cnt ";
				$sql = $sql . "from irai ";
				$sql = $sql . "where utkymd = '$udate' ";
				$sql = $sql . "group by knsgrp )" ;
				$sql = $sql . "for read only with ur";

				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					$cnt_ws = $row[0];
					break;
				}

				printf("<tr>\n");
					printf("<td nowarp>依頼WS数</td>\n");
					printf("<td  align=right nowarp>%s</td>\n",number_format($cnt_ws));
				printf("</tr>\n");

				$sql = "select count(*) from irai where utkymd = '$udate' for read only with ur";
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					$cnt_irai = $row[0];
					break;
				}

				printf("<tr>\n");
					printf("<td nowarp>依頼項目数</td>\n");
					printf("<td  align=right nowarp>%s</td>\n",number_format($cnt_irai));
				printf("</tr>\n");
	
			printf("</table>\n");

			printf("<BR clear=all>\n");
			printf("<center>\n");
			printf("<p>検査グループ別依頼数\n</p>");
			printf("</center>\n");

			printf("<table align=\"center\" bgcolor = white border>\n");
				printf("<tr>\n");
					printf("<th nowrap>検査G</th>\n");
					printf("<th nowrap>検査G名</th>\n");
					printf("<th nowrap>件数</th>\n");
				printf("</tr>\n");
	
				$sql = "";
				$sql = $sql . "select g.knsgrp,g.knsgrprs,count(distinct i.irino) ";
				$sql = $sql . "from knsgmst g,irai i ";
				$sql = $sql . "where i.utkymd = '$udate' ";
				$sql = $sql . "and i.knsgrp = g.knsgrp ";
				$sql = $sql . "group by g.knsgrp,g.knsgrprs ";
				$sql = $sql . "order by g.knsgrp ";
				$sql = $sql . "for read only with ur ";
	
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					printf("<tr>\n");
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[1]));
						printf("<td  align=right nowarp>%s</td>\n",number_format($row[2]));
					printf("</tr>\n");
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
}

printf("<HR>\n");
LaboBackPage();
printf("<HR>\n");
DataTailOut();

?>

<HR>
</BODY>
</HTML>

