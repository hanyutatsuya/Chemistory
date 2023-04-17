<?php

$dbname = "NSFRDB1";
$username = "nsfr";
$password = "nsfr";

$conn = DbConn($dbname,$username,$password);

if  ($conn){
	echo "Connection succeeded";
	}
	else
	{
	echo "Connection failed";
	}
DBDisconn($conn);
?>
