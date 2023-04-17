
<?php
function NsfrBackPage()
{
	$prev_page = $_SERVER['HTTP_REFERER'];
	printf("<center><P>\n");
	printf("<A href=%s>–ß‚é</A>\n",$prev_page);
	printf("</P></center>\n");
}
?>

