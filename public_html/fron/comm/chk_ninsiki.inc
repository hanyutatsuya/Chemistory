
<?php
function ninsiki_check($conn,$sdate,$kenno,$barcd)
{
//	指定検体が認識済みかどうかのチェック

	if  (trim($kenno) == "")
		{
	$sdate = "";
	$sql = "select setkbnnm from nsetuptbl where setkbn = '01' and kmkkbn = '01' for read only";
	foreach ($pdst = $conn->query($sql) as $row)
		{
		$sdate = $row['SETKBNNM'];
		break;
		}
	$pdst->closeCursor();
	
	return $sdate;
}
?>

