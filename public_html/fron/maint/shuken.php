<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "集検万台保守";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];
$addbu = $_POST['ADDBU'];
$addno = trim($_POST['ADDNO']);
$delbu = $_POST['DELBU'];
$delrd = $_POST['DELRD'];
$man   = $_POST['MANDAI'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$conn = Get_DBConn();
$mandai = NULL;

if  ($conn)
	{
	if  (!empty($addbu) && !empty($addno))
		{
		$ret = AddMandai($conn,$man,$addno);
		}

	if  (!empty($delbu) && !empty($delrd))
		{
		$ret = DelMandai($conn,$man,(int)$delrd);
		}

	printf("<FORM ACTION=\"shuken.php\" METHOD=\"POST\">\n");
	$ret = MandaiGet($conn);
	sort($mandai,SORT_STRING);
	$ret = ShowItiran();

	printf("</FORM>\n");
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<BR CLEAR=ALL>\n");
printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=maint.php?SDATE=%s>メンテナンス処理一覧に戻る</A></center>\n",$sdate);
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
function AddMandai($conn,$man,$addno)
{
	$man[] = $addno;
	sort($man,SORT_STRING);

	$ret = MandaiUpdate($conn,$man);

	if  ($ret == TRUE)
		{
		printf("<center><P><FONT color=red>%s万台を集検範囲に追加しました。</FONT></P></center>\n",$addno);
		NsfrLogOut(sprintf("集検範囲へ[%s]万台追加",$addno));
		return(TRUE);
		}
	else
		return(FLASE);
}

function DelMandai($conn,$man,$i)
{
	$delno = $man[$i];

	$man[$i] = NULL;
	sort($man,SORT_STRING);
	array_shift($man);

	$ret = MandaiUpdate($conn,$man);

	if  ($ret == TRUE)
		{
		printf("<center><P><FONT color=red>%s万台を集検範囲から削除しました。</FONT></P></center>\n",$delno);
		NsfrLogOut(sprintf("集検範囲から[%s]万台削除",$delno));
		return(TRUE);
		}
	else
		return(FLASE);
}

function MandaiUpdate($conn,$man)
{
	$conn->beginTransaction();
	$sql = "delete from nsetuptbl where setkbn = '29' and kmkkbn != '00'";
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if  ($res == FALSE)
		{
		$errinfo = $pdst->errorInfo();
		$conn->rollBack();
		NsfrDBErrorMsg($sql,$errinfo);
		return(FALSE);
		}

	$wk = array_chunk($man,10);
	$cnt = count($wk);
	
	for ($i=0;$i<$cnt;$i++)
		{
		$str = implode($wk[$i]," ");
		$sql = sprintf("insert into nsetuptbl values('29','%02d','%s ',current timestamp,'NSFRINIT')",
			$i+1,$str);
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == FALSE)
			{
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			return(FALSE);
			}
		}
	$conn->commit();
	return(TRUE);

}

function MandaiGet($conn)
{
	global $mandai;

	$mandai = NULL;
	$sql = "select setkbnnm from nsetuptbl where setkbn = '29' and kmkkbn != '00' order by setkbn,kmkkbn for read only";
	$i=0;
	$str = "";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$str = $str . $row[0];
		}
	$mandai = explode(" ",chop($str));
}


function ShowItiran()
{
	global $mandai;

	printf("<table align=center bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>No.</th>\n");
	printf("<th nowrap>万台</th>\n");
	printf("<th nowrap colspan=2>削除</th>\n");
	printf("</tr>\n");

	for ($i=0;$i<count($mandai);$i++)
		{
		printf("<tr>\n");
		printf("<td nowrap>%d</td>\n",$i+1);
		printf("<td nowrap>%s</td>\n",$mandai[$i]);
		printf("<td nowrap>\n");
		printf("<INPUT TYPE=hidden  NAME=MANDAI[%d] VALUE=\"%s\">\n",$i,$mandai[$i]);
		printf("<INPUT TYPE=radio   NAME=DELRD value=\"%d\">削除\n",$i);
		printf("</td>\n");
		if  ($i == 0)
			{
			printf("<td nowrap rowspan=%d>\n",count($mandai));
			printf("<BUTTON TYPE=submit NAME=DELBU value=\"submit\">実行\n");
			printf("</BUTTON>\n");
			printf("</td>\n");
			}
		printf("</tr>\n");
		}
	printf("</table>\n");

	printf("<P><CENTER>\n");
	printf("追加する万台を入力してください<BR>\n");
	printf("<INPUT TYPE=text NAME=ADDNO SIZE=5 MAXLENGTH=3>\n");
	printf("<BUTTON TYPE=submit NAME=ADDBU value=\"submit\">追加\n");
	printf("</BUTTON>\n");
	printf("</CENTER></P>\n");


}


?>
