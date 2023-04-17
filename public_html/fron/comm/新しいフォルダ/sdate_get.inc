
<?php
function shoribi_get($conn)
{
	$sdate = "";
	$sql = "select setkbnnm from nsetuptbl where setkbn = '01' and kmkkbn = '01' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch();
	$sdate = $row['SETKBNNM'];
	$pdst->closeCursor();
	return $sdate;
}

function usrname_get($conn,$usrid)
{
	$usrname = "";
	$sql = "select usrnm from m_usr where usrid = '$usrid' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch();
	$usrname = $row['USRNM'];
	$pdst->closeCursor();
	return $usrname;
}

?>

