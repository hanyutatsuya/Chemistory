
<?php
function NsfrHeadOutput($title,$refresh=0)
{
print <<<__HEADOUT__
<HEAD>
<TITLE>$title</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
<META http-equiv="Content-Style-Type" content="text/css">

<style type="text/css">
<!--
table {
empty-cells: show
}
-->
</style>

__HEADOUT__;

if ($refresh == 0)
	printf("<META http-equiv=\"refresh\" content=\"1800,/~nsfr/index.php\">\n");
if ($refresh > 0)
	{
	if ($refresh < 9999)
		printf("<META http-equiv=\"refresh\" content=\"%d\">\n",$refresh);
	}

printf("</HEAD>\n");
}

function NinsikiTailOut()
{
print <<<__TAILOUT__
<HR>
<P>
<center><A href=ninsiki.php>認識システム照会処理一覧に戻る</A></center>
</P>

__TAILOUT__;
}

function BunchuTailOut()
{
print <<<__TAILOUT__
<HR>
<P>
<center><A href=bunchu.php>フロンティアシステム照会処理一覧に戻る</A></center>
</P>

__TAILOUT__;
}

function MasterTailOut()
{
print <<<__TAILOUT__
<HR>
<P>
<center><A href=master.php>マスター一覧に戻る</A></center>
</P>

__TAILOUT__;
}

function NsfrBackPage()
{
	$prev_page = $_SERVER['HTTP_REFERER'];
	printf("<center><P>\n");
	printf("<A href=%s>戻る</A>\n",$prev_page);
	printf("</P></center>\n");
}

function NsfrTimeStamp()
{
	$dbname = $_SESSION['dbname'];
	printf("<DIV align=right>\n");
	printf("[%s] \n",$dbname);
	printf("%s\n",date("Y-m-d H:i:s"));
	printf("</DIV>\n");
}

function NsfrLogOut($msg)
{
	$logfile = "/home/data/log/php_log";

	if (file_exists($logfile) == TRUE)
		$fsz = filesize($logfile);
	else
		$fsz = 0;
	if ($fsz > 10000000)
		{
		$old_log = sprintf("%s.30",$logfile);
		if (file_exists($old_log) == TRUE)
			{
			unlink($old_log);
			}
		for ($i=29;$i>=0;$i--)
			{
			$old_log = sprintf("%s.%02d",$logfile,$i);
			$new_log = sprintf("%s.%02d",$logfile,$i+1);
			if (file_exists($old_log) == TRUE)
				{
				rename($old_log,$new_log);
				}
			}
		$new_log = sprintf("%s.00",$logfile);
		rename($logfile,$new_log);
		}

	$ip = $_SERVER['REMOTE_ADDR'];
	$page = $_SERVER['SCRIPT_NAME'];
	$stamp = strftime("%Y/%m/%d %T");
	
	$logmsg = sprintf("%s [%s][%s] %s\n",$stamp,$ip,$page,$msg);
	error_log($logmsg,3,$logfile);

}

?>

