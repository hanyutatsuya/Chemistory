<?php
function nfkmkmst_table($conn,$kcode)
{
if  (!is_numeric($kcode))
	{
	if  (strlen($kcode) == 0)
		{
		return 0;
		}
	else
		{
		printf("<center>\n");
		printf("<h2>���ڃR�[�h���̓G���[</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	}
else
	{
	$kmcd = sprintf("%07d",$kcode);
	printf("<table align=\"left\" bgcolor = \"white\" border>\n");
	printf("<tr>\n");
	printf("<th>����</th>\n");
	printf("<th>���e</th>\n");
	printf("<th>���l</th>\n");
	printf("</tr>\n");

	$sql = "select * from nfkmkmst where kmkcd = '$kmcd' and ukflg = '1' for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���ڃR�[�h',$row['KMKCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���ږ�',$row['KMKNM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�T���v�����O�R�[�h',$row['SMPCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�d������ދ敪',$row['SSKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'����SEQ',$row['FKSEQ'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'����G',$row['TSKGRP'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�����敪',$row['BCKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�r�d�b',$row['SECCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���敉�׋敪',$row['BKFKKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���ڗ���',$row['KMKNMR'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�e���ڃR�[�h',$row['OYAKMKCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'��\�ޗ��R�[�h',$row['DHZRCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�ʏ핪����',$row['TJBNCRYO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���ʕ�����',$row['SRBNCRYO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'����������',$row['SNBNCRYO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���͂e',$row['TSKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�����e',$row['TKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'��Γ����e',$row['ZTKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'���ʈ����e',$row['TBATFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�ĉ��S�s�e',$row['SESFFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�J�n��',$row['STYMD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�I����',$row['EDYMD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�쐬����',$row['SAKHM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'�X�V����',$row['KOUHM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%20.20s</td></tr>\n",'��Ǝ҂h�c',$row['SAGYOID'],' ');
		}
	printf("</table>\n");
	}
return 0;
}
?>