
<?php
class SsMst
{
	private		$conn;
	private		$type;
	private		$mst;

	public	function __construct($conn)
		{
		$this->conn = $conn;
		$this->GetMst();
		}

	public	function GetName($sskbn)
		{
		return($this->GetSSMstValue($sskbn,1));
		}

	public	function GetRName($sskbn)
		{
		return($this->GetSSMstValue($sskbn,2));
		}

	private	function GetMst()
		{
		$i = 0;
		$sql = "select * from nfssmst where ukflg = '1' order by sskbn for read only";
		foreach ($this->conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			$this->mst[$i] = $row;
			$i++;
			}
		}

	private	function GetSSMstValue($sskbn,$col)
		{
		$ret = $this->GetSSMst($sskbn);
		if  ($ret == -1)
			return(NULL);
		return($this->mst[$ret][$col]);
		}

	private	function GetSSMst($sskbn)
		{
		for ($i=0;$i<count($this->mst);$i++)
			{
			if  (strcmp($this->mst[$i][0],$sskbn) == 0)
				return($i);
			}
		return(-1);
		}

}

?>

