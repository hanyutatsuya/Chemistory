<?php
function nfsmpkm_table($conn,$wscode)
{
if  (!is_numeric($wscode))
	{
	if  (strlen($wscode) == 0)
		{
		return 0;
		}
	else
		{
		printf("<center>\n");
		printf("<h2>サンプリングコード入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	}
else
	{
	$wscd = sprintf("%04d",$wscode);

	printf("<table align=left  border=0>\n");
	printf("<tr valign=top>\n");

	printf("<td>\n");
	printf("<table bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>項目</th>\n");
	printf("<th nowrap>内容</th>\n");
	printf("<th nowrap>備考</th>\n");
	printf("</tr>\n");

	$sql = "select * from nfsmpmst where smpcd = '$wscd' and ukflg = '1' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch();
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'サンプリングコード',$row['SMPCD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'仕分け先名称',$row['SMPCDNM'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'ＩＴＥＭコード',$row['ITMCD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'ＩＴＥＭコード群No.',$row['ITMCDGNO'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'サテライトＩＤ',$row['STID'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'仕分先区分',$row['SWKKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'仕分けラックＩＤ',$row['SWKLCKID'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'仕分け先ＩＤ',$row['SWKSKID'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'分注区分',$row['BCKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'セル区分',$row['SELKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'モジュール区分',$row['MDLKBN'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'通常MAX値',$row['TJMAXVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'通常MIN値',$row['TJMINVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'通常BASE値',$row['TJBSEVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'少量MAX値',$row['SRMAXVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'少量MIN値',$row['SRMINVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'少量BASE値',$row['SRBSEVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'小児MAX値',$row['SNMAXVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'小児MIN値',$row['SNMINVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'小児BASE値',$row['SNBSEVAL'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'Ｓ凍結Ｆ',$row['SUPURUZTKFLG'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'開始日',$row['STYMD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'終了日',$row['EDYMD'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'作成時刻',$row['SAKHM'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'更新時刻',$row['KOUHM'],' ');
	printf("<tr><td nowrap>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n",'作業者ＩＤ',$row['SAGYOID'],' ');
	$pdst->closeCursor();
	printf("</table>\n");
	printf("</td>\n");

	printf("<td>\n");
	printf("<table bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>親コード</th>\n");
	printf("<th nowrap>項目コード</th>\n");
	printf("<th nowrap>項目名</th>\n");
	printf("<th nowrap>TBF</th>\n");
	printf("<th nowrap>通常量</th>\n");
	printf("<th nowrap>少量量</th>\n");
	printf("<th nowrap>小児量</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select oyakmkcd,kmkcd,kmknmr,bkfkkbn,tjbncryo,srbncryo,snbncryo ";
	$sql = $sql . "from nfkmkmst where smpcd = '$wscd' and ukflg = '1' ";
	$sql = $sql . "order by oyakmkcd,kmkcd for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap><A href=kmkmst.php?KMKCD=%s>%s</A></td>\n",$row[0],$row[0]);
		printf("<td nowrap><A href=kmkmst.php?KMKCD=%s>%s</A></td>\n",$row[1],$row[1]);
		printf("<td nowrap>%s</td>\n",$row[2]);
		printf("<td nowrap>%s</td>\n",$row[3]);
		printf("<td nowrap>%s</td>\n",$row[4]);
		printf("<td nowrap>%s</td>\n",$row[5]);
		printf("<td nowrap>%s</td>\n",$row[6]);
		printf("</tr>\n");
		}
	printf("</table>\n");
	printf("</td>\n");

	printf("</table>\n");
	}
	return 0;
}
?>
