<?php
function nfsmpmst_table($conn,$wscode)
{
if  (!is_numeric($wscode))
	{
	if  (strlen($wscode) == 0)
		{
		return 0;
		}
	else
		{
		printf("<center>\n");
		printf("<h2>�T���v�����O�R�[�h���̓G���[</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	}
else
	{
	$wscd = sprintf("%04d",$wscode);
	printf("<table align=\"left\" bgcolor = \"white\" border>\n");
	printf("<tr>\n");
	printf("<th>����</th>\n");
	printf("<th>���e</th>\n");
	printf("<th>���l</th>\n");
	printf("</tr>\n");

	$sql = "select * from nfsmpmst where smpcd = '$wscd' and ukflg = '1' for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�T���v�����O�R�[�h',$row['SMPCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�d�����於��',$row['SMPCDNM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�h�s�d�l�R�[�h',$row['ITMCD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�h�s�d�l�R�[�h�QNo.',$row['ITMCDGNO'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�T�e���C�g�h�c',$row['STID'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�d����敪',$row['SWKKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�d�������b�N�h�c',$row['SWKLCKID'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�d������h�c',$row['SWKSKID'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�����敪',$row['BCKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�Z���敪',$row['SELKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'���W���[���敪',$row['MDLKBN'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�ʏ�MAX�l',$row['TJMAXVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�ʏ�MIN�l',$row['TJMINVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�ʏ�BASE�l',$row['TJBSEVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'����MAX�l',$row['SRMAXVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'����MIN�l',$row['SRMINVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'����BASE�l',$row['SRBSEVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'����MAX�l',$row['SNMAXVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'����MIN�l',$row['SNMINVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'����BASE�l',$row['SNBSEVAL'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�r�����e',$row['SUPURUZTKFLG'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�J�n��',$row['STYMD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�I����',$row['EDYMD'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�쐬����',$row['SAKHM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'�X�V����',$row['KOUHM'],' ');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>\n",'��Ǝ҂h�c',$row['SAGYOID'],' ');
		}
	printf("</table>\n");
	}
	return 0;
}
?>