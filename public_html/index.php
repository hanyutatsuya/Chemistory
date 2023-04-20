<?php

	require_once("comm/labo_html.inc");
	require_once("comm/labo_db.inc");

?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
	LaboHeadOutput("ケミストリー");
	LaboLogOut("ケミストリー");
?>

<BODY background="img/blue_p8b1.gif">

<DIV align=right><A href=mente/sysmente.php STYLE="text-decoration:none;">　</A></DIV>

<?php
	printf("<center><h1>ケミストリー照会</h1></center>\n");

	printf("<center><h2><A href=master/master.php>マスタ照会</A></h2></center>\n");
	printf("<center><h2><A href=data/data.php>データ照会</A></h2></center>\n");
	printf("<center><h2><A href=mente/mente.php>メンテナンス</A></h2></center>\n");
//	printf("<DIV align=right><A href=php/phpinfo.php>phpinfo</A></DIV>\n");
	printf("<HR>\n");

	try {
		$conn = GetDBConn();
		if ($conn) {
			$sql = "";
			$sql = $sql . "select knsgrp,kmkcd";
			$sql = $sql . " from kmkmst";
			$sql = $sql . " where knsgrp = '0054'";
			$sql = $sql . " order by kmkcd for read only";
	
		//	print $sql;
	
			$i = 0;
			foreach ($conn->query($sql) as $row) {
				printf("%s　%s<BR>\n",$row['KNSGRP'],$row['KMKCD']);
				$i += 1;
			}

//			foreach ($conn->query($sql) as $row) {
//				$Inform[$i][0] = $row['knsgrp'];
//				$Inform[$i][1] = $row['kmkcd'];
//				$i += 1;
//			}
	
//			if (count($Inform) != 0) {
//				printf("<center>\n");		
//				printf("<div>お知らせ</div>\n");
//				printf("<div>\n");

//				for ($i=0;$i<count($Inform);$i++) {
//						printf("%s　%s<BR>\n",date("Y-m-d",$Inform[$i][0]),$Inform[$i][1]);
//					printf("%s　%s<BR>\n",$Inform[$i][0],$Inform[$i][1]);
//				}
	
//				printf("</div>\n");
//				printf("</center>\n");		
//			}
	
//			odbc_close($conn);
		} else {
			printf("Connection failed\n");
		}
	}
	catch (ODBCException $PDOex) {
		LaboLogOut(sprintf("SQLMSG  [%s]",$PDOex->getMessage()));
		LaboLogOut(sprintf("SQLCODE  [%s]",$PDOex->getCode()));
	}
	catch (ODBCException $ex) {
		LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
		LaboLogOut(sprintf("ERRCODE  [%s]",$ex->getCode()));
	}

	$conn = null;


//	printf("<HR>\n");
	printf("<DIV align=right><A href=php/phpinfo.php>phpinfo</A></DIV>\n");

	LaboTimeStamp();

?>

</BODY>
</HTML>

