<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>�F���E�t�����e�B�A�Ɖ�TOP</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY background="img/a014bcg.gif">

<DIV align=right><A href=merits/merits.php STYLE="text-decoration:none;">�@</A></DIV>

<?php

	$dbname = $_SESSION['dbname'];
	if (empty($dbname))
		{
		$_SESSION['dbname'] = 'NSFRDB1';
		$dbname = $_SESSION['dbname'];
		}

	printf("<center><h1>�F���E�t�����e�B�A�Ɖ�TOP</h1></center>\n");
	printf("<center><h2><A href=master/master.php>�}�X�^�Ɖ�</A></h2></center>\n");
	printf("<center><h2><A href=comm/nsfrshokai.php>�m���D�Ή��Ɖ�</A></h2></center>\n");
	printf("<center><h2><A href=comm/posshokai.php>���̃|�W�V�����Ɖ�</A></h2></center>\n");
	printf("<center><h2><A href=ninsiki/ninsiki.php>�F���V�X�e���Ɖ�</A></h2></center>\n");
	printf("<center><h2><A href=bunchu/bunchu.php>�t�����e�B�A�V�X�e���Ɖ�</A></h2></center>\n");
	printf("<center><h2><A href=maint/maintlogin.php>�����e�i���X</A></h2></center>\n");
	printf("<HR>\n");
	printf("<center><h2><A href=mailto:nsfr-info@bml.co.jp>���[��</A></h2>\n");
	printf("<center><h2><A href=php/index.php>phpinfo</A></h2>\n");

	printf("<DIV align=right>\n");
	printf("[%s] %s\n",$dbname,date("Y-m-d H:i:s"));
	printf("</DIV>\n");

?>

</BODY>
</HTML>
