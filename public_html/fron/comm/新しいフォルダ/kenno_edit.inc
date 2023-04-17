
<?php
function ino_edit($ino)
{
	$ed_ino = "";
	$ed_ino = substr($ino,2,3) . "-" . substr($ino,5,4);
	return $ed_ino;
}

function kenno_edit($kenno)
{
	$ed_kenno = "";
	$ed_kenno = substr($kenno,2,3) . "-" . substr($kenno,5,4) . "-" . substr($kenno,9,2);
	return $ed_kenno;
}

function barcode_edit($barcd)
{
	$ed_barcd = "";
	$ed_barcd = substr($barcd,2,3) . "-" . substr($barcd,5,4) . "-" . substr($barcd,9,2);
	return $ed_barcd;
}

function ymd_edit($ymd)
{
	$ed_ymd = "";
	$ed_ymd = substr($ymd,0,4) . "/" . substr($ymd,4,2) . "/" . substr($ymd,6,2);
	return $ed_ymd;
}

function ymd_check($ymd)
{
	$yy = (int)substr($ymd,0,4);
	$mm = (int)substr($ymd,4,2);
	$dd = (int)substr($ymd,6,2);
	return checkdate($mm,$dd,$yy);
}

function ino_conv($ino)
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

function barcode_conv($barcode)
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

