<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
?>

<?php
NsfrHeadOutput("���̔F���V�X�e���Ɖ���ꗗ");
?>

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���̔F���V�X�e���Ɖ���ꗗ");
NsfrLogOut("���̔F���V�X�e���Ɖ���ꗗ");

?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>���̔F���V�X�e���Ɖ���ꗗ</h2></center>

<?php
$shoribi = trim($_REQUEST['SDATE']);

if  (!is_numeric($shoribi) || strlen($shoribi) == 0)
	{
	$conn = Get_DBConn();
	$sdate = Get_Shoribi($conn);

	$conn = null;
	}
else
	{
	$sdate = $shoribi;
	}

printf("<center><h2>�������F%s</h2></center>\n",$sdate);

?>

<P>
<center>
<FORM ACTION="ninsiki.php" METHOD="POST">
�������ύX
<INPUT TYPE=text NAME="SDATE" SIZE=10 MAXLENGTH=8>
<BUTTON name="submit" value="submit" type="submit">�ύX
</BUTTON>
</FORM>
</center>
</P>

<?php
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>�Ɖ������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mishori.php?SDATE=%s>�������`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=yellow><A href=irikensu.php?SDATE=%s>�˗������Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=ninkensu.php?SDATE=%s>�F���ό����Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tkhonsu.php?SDATE=%s>�������̖{���Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hikiwatasi.php?SDATE=%s>�������n���g���[�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=futeki.php?SDATE=%s>�s�K���o�^���ꌟ�̃`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mrack.php?SDATE=%s>���������b�N�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=krackmap.php?SDATE=%s>���b�N�}�b�v�Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kanjachk.php?SDATE=%s>���Җ��`�F�b�N���X�g�o�͊m�F</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=ninkentai.php?SDATE=%s>���̏��Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fusoku.php?SDATE=%s>�s�����̏Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=chichaku.php?SDATE=%s>�x�����̏Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=gunma.php?SDATE=%s>�Q�n�Տ��o�[�R�[�h���쐬����</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=aboend.php?SDATE=%s>���^�E�G���h�g�L�V�����̃��X�g�o�͏���</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");
?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
</BODY>
</HTML>
