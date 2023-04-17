
<?php
function LaboHeadOutput($title,$refresh=0)
{
print <<<__HEADOUT__
<HEAD>
<TITLE>$title</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<META http-equiv="Content-Style-Type" content="text/css">
<link rel="stylesheet" href="/~labo/css/labo_html.css?
__HEADOUT__;
echo date('Ymd-Hi');
printf("\">\n");

if ($refresh == 0) {
	printf("<META http-equiv=\"refresh\" content=\"1800,/~labo/index.php\">\n");
}
if ($refresh > 0) {
	if ($refresh < 9999) {
		printf("<META http-equiv=\"refresh\" content=\"%d;URL=\">\n",$refresh);
	}
}

printf("</HEAD>\n");
}

function MenteTailOut()
{

print <<<__TAILOUT__
<HR>
<P>
<center><A href=sysmente.php>メンテナンス処理に戻る</A></center>
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

function LaboBackPage()
{
	$prev_page = $_SERVER['HTTP_REFERER'];
	printf("<center><P>\n");
	printf("<A href=%s>戻る</A>\n",$prev_page);
	printf("</P></center>\n");
}

function LaboTimeStamp()
{
	printf("<DIV align=right>\n");
	printf("%s\n",date("Y-m-d H:i:s"));
	printf("</DIV>\n");
}

function LaboLogOut($msg)
{
	$logfile = "/home/kea00sys/log/php_log";

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

function TextAreaGet($instr)
{
	$string = $instr;

	$string = trim(preg_replace('/[\x00-\x1F\x7F]/',' ', $string));
	$string = str_replace(" ","+",$string);
	$string = str_replace("++","+",$string);

	return $string;
}

function InoEdit($ino)
{
	$ed_ino = "";
	$ed_ino = substr($ino,2,3) . "-" . substr($ino,5,4);
	return $ed_ino;
}

function KennoEdit($kenno)
{
	$ed_kenno = "";
	$ed_kenno = substr($kenno,2,3) . "-" . substr($kenno,5,4) . "-" . substr($kenno,9,2);
	return $ed_kenno;
}

function BarCodeEdit($barcd)
{
	$ed_barcd = "";
	$ed_barcd = substr($barcd,2,3) . "-" . substr($barcd,5,4) . "-" . substr($barcd,9,2);
	return $ed_barcd;
}

function YmdEdit($ymd)
{
	$ed_ymd = "";
	$ed_ymd = substr($ymd,0,4) . "/" . substr($ymd,4,2) . "/" . substr($ymd,6,2);
	return $ed_ymd;
}

function YmdCheck($ymd)
{
	$yy = (int)substr($ymd,0,4);
	$mm = (int)substr($ymd,4,2);
	$dd = (int)substr($ymd,6,2);
	return checkdate($mm,$dd,$yy);
}

function InoConv($ino)
{
	$ed_ino = "";

	if (strlen($ino) < 6)
		return $ed_ino;

	if (strlen($ino) == 6)
		{
		$ed_ino = "000" . $ino;
		return $ed_ino;
		}

	if (strlen($ino) == 7)
		{
		$ed_ino = "00" . $ino;
		return $ed_ino;
		}

	$ed_ino = substr($ino,9);
	return $ed_ino;
}

function BarCcodeConv($barcode)
{
	$ed_bar = "";

	if (strlen($barcode) < 8)
		return $ed_bar;

	if (strlen($barcode) == 8)
		{
		$ed_bar = "000" . $barcode;
		return $ed_bar;
		}

	if (strlen($barcode) == 9)
		{
		$ed_bar = "00" . $barcode;
		return $ed_bar;
		}

	if (strlen($barcode) > 11)
		{
		$ketasum = 0;
		$keta9 = 0;
		for ($i=0;$i<11;$i++)
			$ketasum += substr($barcode,$i,1);

		if  ((int)substr($barcode,11,1) < 7)
			$c1 = $ketasum % 7;
		else
			{
			$c1 = $ketasum % 3;
			$keta9 = 1;
			}
		if  ($c1 != (int)substr($barcode,11,1))
			return $ed_bar;

		if  ($keta9 == 0)
			{
			//	現行バーコード
			if  (strcnmp(substr($barcode,8,3),"000",3) == 0)
				{
				//	６桁バーコード
				$ed_bar = "000" . substr($barcode,0,8);
				}
			else
				{
				//	７桁バーコード
				$ed_bar = "00" . substr($barcode,8,3) . substr($barcode,2,6);
				}
			}
		else
			{
			$ed_bar = substr($barcode,0,11);
			//	９桁バーコード
			}
		}
	else
		{
		$ed_bar = "00" . substr($barcode,0,9);
		return $ed_bar;
		}

	return $ed_bar;
}

?>

