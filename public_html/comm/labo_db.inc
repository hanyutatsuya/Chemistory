
<?php
function GetDBConn()
{

	$dbname = $_SESSION['keadbname'];

	$dsn = "KEA00DB0";
	$user = "kea00dbt";
	$pass = "kea00dbt";

	try {
		if ($dbname == "KEA00DB0") {
			$user = "kea00dbt";
			$pass = "kea00dbt";
		} else {
			$user = "db2inst1";
			$pass = "db2inst1";
		}

		$dsn = "odbc:" . $dbname;
	
		$conn = new PDO($dsn,$user,$pass);
	
		if (!$conn) {
			printf("<FONT color=red>\n");
			printf("<P>ＤＢコネクションエラー</P>\n");
			printf("</FONT>\n");
		} else {
//			printf("<FONT color=blue>\n");
//			printf("<P>ＤＢコネクション ＯＫ</P>\n");
//			printf("</FONT>\n");
			$_SESSION['keadbname'] = $dbname;
		}
//		$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}

//	catch (PDOException $PDOex) {
//		LaboLogOut(sprintf("PDO:SQLMSG  [%s]",$PDOex->getMessage()));
//		LaboLogOut(sprintf("PDO:SQLCODE [%s]",$PDOex->getCode()));
//	}
//	catch (ODBCException $ODBCex) {
//		LaboLogOut(sprintf("ODBC:SQLMSG  [%s]",$ODBCex->getMessage()));
//		LaboLogOut(sprintf("ODBC:SQLCODE [%s]",$ODBCex->getCode()));
//	}
	catch (Exception $ex) {
		LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
		LaboLogOut(sprintf("ERRCODE [%s]",$ex->getCode()));
		printf("ERRMSG  [%s]<BR>",$ex->getMessage());
		printf("ERRCODE [%s]<BR>",$ex->getCode());
	}

	return($conn);
}

function SqlExec($conn,$sql)
{
//	$conn->beginTransaction();
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if ($res == FALSE) {
		$errinfo = $pdst->errorInfo();
//		$conn->rollBack();
		printf("<FONT color=red>\n");
		printf("<P>SQL処理に失敗しました</P>\n");
		printf("<P>SQL=[%s]</P>\n",$sql);
		printf("<P>SQLSTATE[%s]</P>\n",$errinfo[0]);
		printf("<P>ERRCODE [%s]</P>\n",$errinfo[1]);
		printf("<P>%s</P>\n",$errinfo[2]);
		printf("</FONT>\n");
		return(NULL);
	}

//	$conn->commit();
	return($pdst);
}

function LaboDBErrorMsg($sql,$errorinfo)
{
	printf("<FONT color=red>\n");
	printf("<P>SQL処理に失敗しました</P>\n");
	printf("<P>SQLCMD  [%s]</P>\n",$sql);
	printf("<P>SQLSTATE[%s]</P>\n",$errorinfo[0]);
	printf("<P>ERRCODE [%s]</P>\n",$errorinfo[1]);
	printf("<P>[%s]</P>\n",$errorinfo[2]);
	printf("</FONT>\n");
	LaboLogOut(sprintf("SQL処理に失敗しました"));
	LaboLogOut(sprintf("SQLCMD  [%s]",$sql));
	LaboLogOut(sprintf("SQLSTATE[%s]",$errorinfo[0]));
	LaboLogOut(sprintf("ERRCODE [%s]",$errorinfo[1]));
	LaboLogOut(sprintf("[%s]",$errorinfo[2]));

	return(NULL);
}

function GetUTF8String($instr)
{
	$outstr = mb_convert_encoding($instr,"UTF-8","SJIS-WIN");
	return $outstr;
}

function GetDBErrMsg($ex)
{
	LaboLogOut(sprintf("ERRMSG  [%s]",GetUTF8String($ex->getMessage())));
	LaboLogOut(sprintf("ERRCODE [%s]",GetUTF8String($ex->getCode())));
	printf("<P>ERRMSG  [%s]</P>\n",GetUTF8String($ex->getMessage()));
	printf("<P>ERRCODE [%s]</P>\n",GetUTF8String($ex->getCode()));
}


function GetShoribi($conn,$lbcode)
{
	$sdate = "";
	$sql = "select values from mst_setup where section = 1 and name = 1";
	$result = SqlExec($conn,$sql);
	if ($result != NULL) {
		$row = $result->fetch(PDO::FETCH_NUM);
		$sdate = $row[0];
	}
	$result->closeCursor();
	return $sdate;
}

function GetMaxKinno($conn,$lbcode,$udate)
{
	$kinno = 0;
	$sql = "";
	$sql = $sql . "select max(kinno) from dat_toroku";
	$sql = $sql . " where lbcode = '" . $lbcode . "'";
	$sql = $sql . " and udate = '" . $udate . "'";
	$result = SqlExec($conn,$sql);
	if ($result != NULL) {
		$row = $result->fetch(PDO::FETCH_NUM);
		$kinno = $row[0];
	}
	$result->closeCursor();
	return $kinno;
}

function GetLaboName($conn,$lbcode)
{
	$meisho = "";
	$sql = "";
	$sql = $sql . "select meisho from Mst_Labo";
	$sql = $sql . " where lbcode = '" . $lbcode . "'";
	$result = SqlExec($conn,$sql);
	if ($result != NULL) {
		$row = $result->fetch(PDO::FETCH_NUM);
		$meisho = $row[0];
	}
	$result->closeCursor();
	return $meisho;
}


function GetUsername($conn,$usrid)
{
	$usrname = "";
	$sql = "select usrnm from mst_user where shain = '$usrid' for read only";
	$result = SqlExec($conn,$sql);
	if ($result != NULL) {
		$row = $result->fetch(PDO::FETCH_NUM);
		$usrname = $row[0];
	}
	$result->closeCursor();
	return $usrname;
}

?>
