
<?php
function ninsiki_head_output($title)
{
print <<<__HEADOUT__
<HEAD>
<TITLE>$title</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
<style type="text/css">
<!--
table {
empty-cells: show
}
-->
</style>

</HEAD>

__HEADOUT__;
}
?>

