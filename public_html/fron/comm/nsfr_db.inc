
<?php
function Get_DBConn($dbname="NSFRDB1")
{
	$ip = $_SERVER['REMOTE_ADDR'];
	if  ($ip == "172.17.10.155")
		$dsn = "odbc:NSFRDB1";
	else
		$dsn = "odbc:" . $dbname;

	$conn = new PDO($dsn,'nsfr','nsfr');

	if  ($conn)
		return($conn);
	else
		{
		printf("<FONT color=red>\n");
		printf("<P>ＤＢコネクションエラー</P>\n");
		printf("</FONT>\n");
		return(NULL);
		}
}

function SQL_Exec($conn,$sql)
{
//	$conn->beginTransaction();
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if  ($res == FALSE)
		{
		$errinfo = $pdst->errorInfo();
//		$conn->rollBack();
		printf("<FONT color=red>\n");
		printf("<P>SQL処理に失敗しました</P>\n");
		printf("<P>SQLSTATE[%s]</P>\n",$errinfo[0]);
		printf("<P>ERRCODE [%s]</P>\n",$errinfo[1]);
		printf("<P>%s</P>\n",$errinfo[2]);
		printf("</FONT>\n");
		return(NULL);
		}

//	$conn->commit();
	return($pdst);
}

function NsfrDBErrorMsg($sql,$errorinfo)
{
	printf("<FONT color=red>\n");
	printf("<P>SQL処理に失敗しました</P>\n");
	printf("<P>SQLCMD  [%s]</P>\n",$sql);
	printf("<P>SQLSTATE[%s]</P>\n",$errorinfo[0]);
	printf("<P>ERRCODE [%s]</P>\n",$errorinfo[1]);
	printf("<P>[%s]</P>\n",$errorinfo[2]);
	printf("</FONT>\n");
	NsfrLogOut(sprintf("SQL処理に失敗しました"));
	NsfrLogOut(sprintf("SQLCMD  [%s]",$sql));
	NsfrLogOut(sprintf("SQLSTATE[%s]",$errorinfo[0]));
	NsfrLogOut(sprintf("ERRCODE [%s]",$errorinfo[1]));
	NsfrLogOut(sprintf("[%s]",$errorinfo[2]));

	return(NULL);
}

function Get_Shoribi($conn)
{
	$sdate = "";
	$sql = "select setkbnnm from nsetuptbl where setkbn = '01' and kmkkbn = '01' for read only";
	$result = SQL_Exec($conn,$sql);
	if  ($result != NULL)
		{
		$row = $result->fetch(PDO::FETCH_NUM);
		$sdate = $row[0];
		}
	$result->closeCursor();
	return $sdate;
}

function Get_Username($conn,$usrid)
{
	$usrname = "";
	$sql = "select usrnm from m_usr where usrid = '$usrid' for read only";
	$result = SQL_Exec($conn,$sql);
	if  ($result != NULL)
		{
		$row = $result->fetch(PDO::FETCH_NUM);
		$usrname = $row[0];
		}
	$result->closeCursor();
	return $usrname;
}

?>
