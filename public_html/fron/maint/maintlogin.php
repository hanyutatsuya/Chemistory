<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<HEAD>
<TITLE>�����e�i���X���O�C��</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
</HEAD>

<BODY background="../img/loginback.gif">
<?php
require_once("../comm/nsfr_html.inc");
NsfrTimeStamp();
?>
<center><h2>�����e�i���X���O�C��</h2></center>

<?php
$usrid  = trim($_POST['USRID']);
$passwd = trim($_POST['PASSWD']);
$uname  = trim($_POST['UNAME']);

if  (strlen($uname) == 0)
	{
	printf("<FORM ACTION=\"maintlogin.php\" METHOD=\"POST\">\n");
	printf("<P>\n");
	printf("<center>\n");
	printf("���[�U�[�h�c\n");
	printf("<INPUT TYPE=text NAME=\"USRID\" SIZE=10 MAXLENGTH=10>\n");
	printf("</center>\n");
	printf("</P>\n");
	printf("<P>\n");
	printf("<center>\n");
	printf("�@�p�X���[�h\n");
	printf("<INPUT TYPE=password NAME=\"PASSWD\" SIZE=10 MAXLENGTH=10>\n");
	printf("</center>\n");
	printf("</P>\n");
	printf("<center>\n");
	printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">\n");
	printf("���O�C��\n");
	printf("</BUTTON>\n");
	printf("</center>\n");

	if  (strlen($usrid) != 0)
		{
		if  (strlen($passwd) != 0)
			{
			$conn = new PDO('odbc:NSFRDB1','nsfr','nsfr');
			if  ($conn)
				{
				$id = 
				$sql = "";
				$sql = $sql . "select pw,usrnm from m_usr ";
				$sql = $sql . "where usrid = '$usrid' ";
				$sql = $sql . "for read only";
				$pdst = $conn->prepare($sql);
				$pdst->execute();
				$row = $pdst->fetch();
				$pw   = trim($row[0]);
				$name = $row[1];
				$pdst->closeCursor();
				if  (strcmp($passwd,$pw) == 0)
					{
					printf("<center><P>���O�C�����܂���</P></center>\n");
					printf("<center><P><A href=maint.php>�����e�i���X���j���[</A></P></center>\n");
					printf("<INPUT TYPE=hidden NAME=\"UNAME\" value=\"%s\">\n",$name);
					}
				else
					{
					printf("<center><P>�p�X���[�h������Ă��܂�</P></center>\n");
					}
				}
			else
				{
				echo "Connection failed";
				}
			$conn = null;
			}
		else
			{
			printf("<center><P>�p�X���[�h����͂��Ă�������</P></center>\n");
			}
		}
	printf("</FORM>\n");
	}
else
	{
	printf("<FORM ACTION=\"maintlogin.php\" METHOD=\"POST\">\n");
	printf("<INPUT TYPE=hidden NAME=\"UNAME\" value=\"%s\">\n",$uname);
	printf("</FORM>\n");

	printf("<center><P>���O�C�����܂���</P></center>\n");
	printf("<center><P><A href=maint.php>�����e�i���X���j���[</A></P></center>\n");

	}
?>



<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
</BODY>
</HTML>

