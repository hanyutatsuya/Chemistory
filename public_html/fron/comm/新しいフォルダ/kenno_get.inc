
<?php
function kenno_get($conn,$sdate,$kenno,$barcd,$ino_flg=0)
{
//	$ino_flg = 0  同一検体ナンバー
//	$ino_flg = 1  同一依頼書ナンバー




	$sql = $sql . "and ng.bcngscd = bn.bcngscd and ng.bcngsscd = bn.bcngsscd ";
	$sql = $sql . "order by bn.barcd for read only";
	$i = 0;
	foreach ($conn->query($sql) as $row)
		{
		$no_tbl[$i] = $row[0];
		$i++;
		}

	return $no_tbl;
}
?>

