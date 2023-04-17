
<?php
class Nsfr
{
	private		$conn;
	private		$type;
	private		$udate;
	private		$ino;
	private		$sdate;
	private		$kenno;
	private		$barcd;
	private		$ino_flg;
	private		$kenno_flg;
	private		$sdt1ran;
	private		$bar1ran;

	public	$zokusei;
	public	$irai;
	public	$kkentai;
	public	$kentai;
	public	$cansel;
	public	$hibunchu;
	public	$erkentai;
	public	$fusoku;
	public	$jizen;
	public	$bunchu;
	public	$bunkentai;
	public	$bunkeka;
	public	$pakipaki;

	public	function __construct($conn = NULL)
		{
		$this->conn = $conn;
		$this->type = PDO::FETCH_NUM;
		$this->ino_flg = 0;
		$this->kenno_flg = 0;
		unset($this->udate,$this->sdate,$this->ino,$this->kenno,$this->barcd);
		unset($this->bar1ran,$this->sdt1ran);
		unset($this->zokusei,$this->irai,$this->kentai);
		unset($this->hibunchu,$this->erkentai,$this->fusoku);
		unset($this->bunchu,$this->bunkentai,$this->bunkeka,$this->pakipaki);
		}

	public	function Clear()
		{
		$this->type = PDO::FETCH_NUM;
		$this->ino_flg = 0;
		$this->kenno_flg = 0;
		unset($this->udate,$this->sdate,$this->ino,$this->kenno,$this->barcd);
		unset($this->bar1ran,$this->sdt1ran);
		unset($this->zokusei,$this->irai,$this->kentai);
		unset($this->hibunchu,$this->erkentai,$this->fusoku);
		unset($this->bunchu,$this->bunkentai,$this->bunkeka,$this->pakipaki);
		}

	public	function SetDBConn($conn)
		{
		$this->conn = $conn;
		}
	public	function SetType($type)
		{
		if  ($type == 1)
			$this->tyep = PDO::FETCH_ASSOC;
		}
	public	function SetUdate($udate)
		{
		if  ($udate != "")
			$this->udate = $udate;
		$this->CheckArg();
		}
	public	function SetSdate($sdate)
		{
		if  ($sdate != "")
			$this->sdate = $sdate;
		$this->CheckArg();
		}

	public	function SetIno($ino)
		{
		if  ($ino != "")
			$this->ino = "00" . substr(trim($ino),0,7) . "00";
		$this->CheckArg();
		}
	public	function SetKenno($kenno)
		{
		if  ($kenno != "")
			$this->kenno = "00" . trim($kenno);
		$this->CheckArg();
		}
	public	function SetBarcd($barcd)
		{
		if  ($barcd != "")
			$this->barcd = "00" . trim($barcd);
		$this->CheckArg();
		}

	private	function CheckArg()
		{
		$this->ino_flg = 0;
		$this->kenno_flg = 0;
		if  (isset($this->udate) && isset($this->ino))
			{
			$this->ino_flg = 1;
			}
		if  (isset($this->sdate))
			{
			if  (isset($this->kenno))
				{
				$this->kenno_flg = 1;
				}
			else
				{
				if  (isset($this->barcd))
					{
					$this->kenno_flg = 2;
					}
				}
			}
		}

	public	function GetCheck()
		{
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(FALSE);
		return(TRUE);
		}

	public	function GetZokusei()
		{
		if (isset($this->zokusei))
			return($this->zokusei);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			{
			$this->GetUdateIno();
			}
		$this->GetZokuRec();
		return($this->zokusei);
		}

	public	function GetZokuseiCount()
		{
		if (!isset($this->zokusei))
			$this->GetZokusei();
		return((int)(count($this->zokusei)/33));
		}


	public	function GetIrai()
		{
		if (isset($this->irai))
			return($this->irai);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetIraiRec();
		return($this->irai);
		}

	public	function GetIraiCount()
		{
		if (!isset($this->irai))
			$this->GetIrai();
		return(count($this->irai));
		}

	public	function GetKKentai()
		{
		if (isset($this->kkentai))
			return($this->kkentai);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetKKRec();
		return($this->kkentai);
		}

	public	function GetKKentaiCount()
		{
		if (!isset($this->kkentai))
			$this->GetKKRec();
		return(count($this->kkentai));
		}

	public	function GetKentai()
		{
		if (isset($this->kentai))
			return($this->kentai);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetKenRec();
		return($this->kentai);
		}

	public	function GetKentaiCount()
		{
		if (!isset($this->kentai))
			$this->GetKenRec();
		return(count($this->kentai));
		}

	public	function GetCansel()
		{
		if (isset($this->cansel))
			return($this->cansel);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetCanRec();
		return($this->cansel);
		}

	public	function GetCanselCount()
		{
		if (!isset($this->cansel))
			$this->GetCanRec();
		return(count($this->cansel));
		}

	public	function GetHiBunchu()
		{
		if (isset($this->hibunchu))
			return($this->hibunchu);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		if (!isset($this->bar1ran))
			$this->GetBar1ran();
		$this->GetHiBunRec();
		return($this->hibunchu);
		}

	public	function GetHiBunchuCount()
		{
		if (!isset($this->hibunchu))
			$this->GetHiBunRec();
		return(count($this->hibunchu));
		}

	public	function GetErKentai()
		{
		if (isset($this->erkentai))
			return($this->erkentai);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetErKenRec();
		return($this->erkentai);
		}

	public	function GetErKentaiCount()
		{
		if (!isset($this->erkentai))
			$this->GetErKenRec();
		return(count($this->erkentai));
		}

	public	function GetFusoku()
		{
		if (isset($this->fusoku))
			return($this->fusoku);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetFusokuRec();
		return($this->fusoku);
		}

	public	function GetFusokuCount()
		{
		if (!isset($this->fusoku))
			$this->GetFusokuRec();
		return(count($this->fusoku));
		}

	public	function GetJizen()
		{
		if (isset($this->jizen))
			return($this->jizen);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		$this->GetJRec();
		return($this->jizen);
		}

	public	function GetJizenCount()
		{
		if (!isset($this->jizen))
			$this->GetJRec();
		return(count($this->jizen));
		}

	public	function GetBunchu()
		{
		if (isset($this->bunchu))
			return($this->bunchu);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		if (!isset($this->bar1ran))
			$this->GetBar1ran();
		$this->GetBunRec();
		return($this->bunchu);
		}

	public	function GetBunchuCount()
		{
		if (!isset($this->bunchu))
			$this->GetBunRec();
		return(count($this->bunchu));
		}

	public	function GetBunKentai()
		{
		if (isset($this->bunkentai))
			return($this->bunkentai);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		if (!isset($this->bar1ran))
			$this->GetBar1ran();
		$this->GetBunKenRec();
		return($this->bunkentai);
		}

	public	function GetBunKentaiCount()
		{
		if (!isset($this->bunkentai))
			$this->GetBunKenRec();
		return(count($this->bunkentai));
		}

	public	function GetBunKeka()
		{
		if (isset($this->bunkeka))
			return($this->bunkeka);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		if (!isset($this->bar1ran))
			$this->GetBar1ran();
		$this->GetBunKekaRec();
		return($this->bunkeka);
		}

	public	function GetBunKekaCount()
		{
		if (!isset($this->bunkeka))
			$this->GetBunKekaRec();
		return(count($this->bunkeka));
		}

	public	function GetBunPaki()
		{
		if (isset($this->pakipaki))
			return($this->pakipaki);
		if  ($this->ino_flg == 0 && $this->kenno_flg == 0)
			return(NULL);
		if  ($this->ino_flg == 0)
			$this->GetUdateIno();
		if (!isset($this->bar1ran))
			$this->GetBar1ran();
		$this->GetPakiRec();
		return($this->pakipaki);
		}

	public	function GetBunPakiCount()
		{
		if (!isset($this->pakipaki))
			$this->GetPakiRec();
		return(count($this->pakipaki));
		}

	private	function GetUdateIno()
		{
		$sql = "";
		$sql = $sql . "select utkymd,irino from nkktbl ";
		$sql = $sql . "where sriymd = '$this->sdate' ";
		if  ($this->kenno_flg == 1)
			$wk_kenno = substr($this->kenno,0,9) . "%";
		else
			$wk_kenno = substr($this->barcd,0,9) . "%";
		$sql = $sql . "and kntno like '$wk_kenno' ";
		$sql = $sql . "and kntkbn = 0 for read only";
		$pdst = $this->conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch();
		$this->udate = $row[0];
		$this->ino = $row[1];
		$pdst->closeCursor();
		$this->ino_flg = 1;
		}

	private	function GetBar1ran()
		{
		$i = 0;
		$sql = "";
		$sql = $sql . "select sriymd,barcd from nfktbl ";
		$sql = $sql . "where utkymd = '$this->udate' ";
		$sql = $sql . "and irino =  '$this->ino' ";
		$sql = $sql . "order by sriymd,barcd for read only ";
		foreach ($this->conn->query($sql,$this->type) as $row)
			{
			$this->sdt1ran[$i] = $row[0];
			$this->bar1ran[$i] = $row[1];
			$i++;
			}
		}

	private	function GetZokuRec()
		{
		$sql = "";
		$sql = $sql . "select * from nfztbl ";
		$sql = $sql . "where utkymd = '$this->udate' ";
		$sql = $sql . "and irino = '$this->ino' for read only";
		$pdst = $this->conn->prepare($sql);
		$pdst->execute();
		$this->zokusei = $pdst->fetch($this->type);
		$pdst->closeCursor();
		}

	private	function GetIraiRec()
		{
		$i = 0;
		$sql = "";
		$sql = $sql . "select * from nfitbl ";
		$sql = $sql . "where utkymd = '$this->udate' ";
		$sql = $sql . "and irino = '$this->ino' order by smpcd,kmkcd for read only";
		foreach ($this->conn->query($sql,$this->type) as $row)
			{
			$this->irai[$i] = $row;
			$i++;
			}
		}

	private	function GetKKRec()
		{
		$i = 0;
		$sql = "";
		$sql = $sql . "select * from nkktbl ";
		$sql = $sql . "where utkymd = '$this->udate' ";
		$sql = $sql . "and irino = '$this->ino' order by kntno,kntseq for read only";
		foreach ($this->conn->query($sql,$this->type) as $row)
			{
			$this->kkentai[$i] = $row;
			$i++;
			}
		}

	private	function GetKenRec()
		{
		$i = 0;
		$sql = "";
		$sql = $sql . "select * from nfktbl ";
		$sql = $sql . "where utkymd = '$this->udate' ";
		$sql = $sql . "and irino = '$this->ino' order by kntno,kntseq for read only";
		foreach ($this->conn->query($sql,$this->type) as $row)
			{
			$this->kentai[$i] = $row;
			$i++;
			}
		}

	private	function GetCanRec()
		{
		$i = 0;
		$sql = "";
		$sql = $sql . "select * from nhcktbl ";
		$sql = $sql . "where utkymd = '$this->udate' ";
		$sql = $sql . "and irino = '$this->ino' order by kntno,kntseq for read only";
		foreach ($this->conn->query($sql,$this->type) as $row)
			{
			$this->cansel[$i] = $row;
			$i++;
			}
		}

	private	function GetHiBunRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from nhbnctbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd = '$wk_barcd' ";
			$sql = $sql . "and kntkbn = 0 ";
			$sql = $sql . "order by stid,smpcd for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->hibunchu[$j] = $row;
				$j++;
				}
			}
		}

	private	function GetErKenRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from nferrtbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd = '$wk_barcd' ";
			$sql = $sql . "and kntkbn = 0 ";
			$sql = $sql . "for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->erkentai[$j] = $row;
				$j++;
				}
			}
		}

	private	function GetFusokuRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from nfsktbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd = '$wk_barcd' ";
			$sql = $sql . "and kntkbn = 0 ";
			$sql = $sql . "for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->fusoku[$j] = $row;
				$j++;
				}
			}
		}

	private	function GetJRec()
		{
		$i = 0;
		$sql = "";
		$sql = $sql . "select c.* from nccktbl c,nkktbl k ";
		$sql = $sql . "where k.utkymd = '$this->udate' ";
		$sql = $sql . "and k.irino = '$this->ino' ";
		$sql = $sql . "and c.sriymd = k.sriymd ";
		$sql = $sql . "and c.kntno = k.kntno ";
		$sql = $sql . "order by c.kntno,c.kntseq for read only";
		foreach ($this->conn->query($sql,$this->type) as $row)
			{
			$this->jizen[$i] = $row;
			$i++;
			}
		}

	private	function GetBunRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from fbnctbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd = '$wk_barcd' ";
			$sql = $sql . "and kntkbn = 0 ";
			$sql = $sql . "order by itmcdgno,itmcd,smpcd for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->bunchu[$j] = $row;
				$j++;
				}
			}
		}

	private	function GetBunKenRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from fbncmktbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd =  '$wk_barcd' ";
			$sql = $sql . "and kntkbn= 0 ";
			$sql = $sql . "for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->bunkentai[$j] = $row;
				$j++;
				}
			}
		}

	private	function GetBunKekaRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from fbncjtbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd =  '$wk_barcd' ";
			$sql = $sql . "and kntkbn= 0 ";
			$sql = $sql . "order by smpcd for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->bunkeka[$j] = $row;
				$j++;
				}
			}
		}

	private	function GetPakiRec()
		{
		$j = 0;
		for ($i=0;$i<count($this->bar1ran);$i++)
			{
			$wk_sdate = $this->sdt1ran[$i];
			$wk_barcd = $this->bar1ran[$i];
			$sql = "";
			$sql = $sql . "select * from fpkptbl ";
			$sql = $sql . "where sriymd = '$wk_sdate' ";
			$sql = $sql . "and barcd =  '$wk_barcd' ";
			$sql = $sql . "order by smpcd,itmseq for read only";
			foreach ($this->conn->query($sql,$this->type) as $row)
				{
				$this->pakipaki[$j] = $row;
				$j++;
				}
			}
		}
}

?>

