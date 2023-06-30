<?php
function nfkmkmst_table($conn,$kcode)
{
if  (!is_numeric($kcode))
	{
	if  (strlen($kcode) == 0)
		{
		return 0;
		}
	else
		{
		printf("<center>\n");
		printf("<h2>項目コード入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	}
else
	{
	$kmcd = sprintf("%07d",$kcode);
	printf("<table align=\"left\" bgcolor = \"white\" border>\n");
	printf("<tr>\n");
	printf("<th>項目</th>\n");
	printf("<th>内容</th>\n");
	printf("<th>備考</th>\n");
	printf("</tr>\n");

	$sql = "select * from nfkmkmst where kmkcd = '$kmcd' and ukflg = '1' for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'項目コード',$row['KMKCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'項目名',$row['KMKNM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'サンプリングコード',$row['SMPCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'仕分け種類区分',$row['SSKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'負荷SEQ',$row['FKSEQ'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'透析G',$row['TSKGRP'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'分注区分',$row['BCKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'ＳＥＣ',$row['SECCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'分画負荷区分',$row['BKFKKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'項目略称',$row['KMKNMR'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'親項目コード',$row['OYAKMKCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'代表材料コード',$row['DHZRCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'通常分注量',$row['TJBNCRYO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'少量分注量',$row['SRBNCRYO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'小児分注量',$row['SNBNCRYO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'透析Ｆ',$row['TSKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'凍結Ｆ',$row['TKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'絶対凍結Ｆ',$row['ZTKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'特別扱いＦ',$row['TBATFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'再遠心不可Ｆ',$row['SESFFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'開始日',$row['STYMD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'終了日',$row['EDYMD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'作成時刻',$row['SAKHM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'更新時刻',$row['KOUHM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'作業者ＩＤ',$row['SAGYOID'],' ');
		}
	printf("</table>\n");
	}
return 0;
}
?>
