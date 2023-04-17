<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>認識・フロンティアＤＢテスト</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>

<?php

echo $_SERVER['LANG'];

$conn = new PDO('odbc:NSFRDB1','nsfr','nsfr');

if  ($conn){
	echo "Connection succeeded";
	$sql = 'select stid,stnm from nfstrmst for read only';
	foreach ($conn->query($sql) as $row) {
		print $row['STID'] ;
		print ("\t");
		print $row['STNM'] ;
		print ("\n");
		}
	}
	else
	{
	echo "Connection failed";
	}
$conn = null;
?>
