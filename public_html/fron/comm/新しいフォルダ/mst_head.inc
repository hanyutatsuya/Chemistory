
<?php
function master_head_output($title)
{
print <<<__HEADOUT__
<HEAD>
<TITLE>$title</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
<META http-equiv="Content-Style-Type" content="text/css">

<style type="text/css">
<!--
table {
empty-cells: show
/*border-collapse:collapse;*/
}
/*
th,td,tr {
border:1px solid #000000;
}
*/
-->
</style>
</HEAD>

__HEADOUT__;
}
?>

